"""Check the functions in config/matched_functions.json under link-time code generation (LTCG).

usage: py -I tools/verify_ltcg.py <path to extracted default.exe> [source-substring] [--keep DIR] [--self-test]
       py -I tools/verify_ltcg.py <path to extracted default.exe> --whole [--keep DIR] [--self-test]
(--whole: the whole-program model, every /GL game source in one link; see "the whole-program model" below)

Crackdown 2's game code was compiled with /GL and linked with /LTCG (docs/feasibility.md section 4). Most functions
come out the same as a plain per-object compile, which tools/verify_src.py checks. This tool checks the LTCG build,
which matters for functions that use float constants or whose code depends on whole-program facts.

LTCG output depends on the rest of the program, so for each source file this builds a small model of it
(details in tools/research/compiler_re/README.md):
  - escapes: a copy of the source with an array appended that takes the address of every global the object refers to,
    since LTCG treats a global whose address no /GL code takes as unaliased. It is compiled with
    /Dprivate=public /Dprotected=public so non-public static members can be named; that changes symbol names only.
  - constant registrations: `const` globals holding every float/double constant that CD2 loads directly (not from
    its constant pool) in this file's functions, read by a function compiled first, so that the compiler loads
    those literals from a global instead of pooling them, as in CD2.
  - a pool seed, so that no real constant lands at offset 0 of the constant pool (offset 0 is addressed differently).
  - matched callees: another repository file is compiled with /GL and linked in when this file calls functions that
    file has matched, so that LTCG sees their bodies as it did in CD2's whole-program build (dependencies()). Only
    functions the gates prove exact are seen; every other external symbol is a stub.

Comparison masks address immediates only: halves derived from a `lis`, loads/stores through such registers, and
calls that leave the function. Everything else (offsets, registers, opcodes, intra-function branches) must match.
The build and comparison functions (build_ltcg, compare_ltcg, direct_constants) are also used by agent harnesses.
"""
import bisect, concurrent.futures, json, math, os, re, shutil, struct, subprocess, sys, time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import buildcache
import coff
import relocs
from verify_src import (pe_reader, FLAGS, XDK, BIN, ROOT, EXPECTED_ENTRY, WORKERS, MIDDLEWARE_ROOT, check_toolchain,
                        file_flags, plain_command, ltcg_built, symbol_matches, manifest_index, compile_sizes,
                        game_tables, game_data_check, data_splits, work_dir)

POOL_START, POOL_SIZE = 0x820F8C80, 0x8000  # CD2's LTCG constant pool (__pool@_0)
RDATA = (0x82000400, 0x8216F658)
LOADS = {32, 33, 34, 35, 40, 41, 42, 43, 46, 48, 49, 50, 51, 58}
STORES = {36, 37, 38, 39, 44, 45, 47, 52, 53, 54, 55, 62}
NO_GPR_WRITE = STORES | {16, 18, 19, 10, 11}  # stores, branches, compares
FLOAT_LOADS = {48: 4, 50: 8}  # lfs, lfd
LOGICAL_RA_DEST = {20, 21, 23, 24, 25, 26, 27, 28, 29, 30}  # rotates and logical immediates write rA, not rS


def masked(ws, start, absolute_offsets=()):
    """Mask address immediates; retain ADDR32 table destinations as function-relative offsets."""
    out, hi = [], set()
    end = start + 4 * len(ws)
    for i, w in enumerate(ws):
        if i * 4 in absolute_offsets:
            out.append((w - start) & 0xFFFFFFFF)  # compare the destination, relative to the function
            continue
        op, rt, ra = w >> 26, (w >> 21) & 31, (w >> 16) & 31
        m = w
        if op == 15 and ra == 0:
            m = w & 0xFFFF0000
            hi.add(rt)
        elif op == 14 and ra in hi and ra != 0:
            m = w & 0xFFFF0000
            hi.add(rt)
        elif (op in LOADS or op in STORES) and ra in hi and ra != 0:
            m = w & 0xFFFF0000
            if op in LOADS and op not in (48, 49, 50, 51):  # integer loads overwrite rt; float loads write an FPR
                hi.discard(rt)
        elif op == 18:
            disp = w & 0x03FFFFFC
            if disp & 0x02000000:
                disp -= 0x04000000
            tgt = disp if w & 2 else start + 4 * i + disp
            if not start <= tgt < end:
                m = w & 0xFC000003
        elif op in LOGICAL_RA_DEST:
            hi.discard(ra)
        elif op == 31:
            hi.discard(rt)
            hi.discard(ra)
        elif op not in NO_GPR_WRITE and op not in LOADS:
            hi.discard(rt)
        elif op in LOADS and op not in (48, 49, 50, 51):
            hi.discard(rt)
        out.append(m)
    return out


def words(b):
    return list(struct.unpack('>%dI' % (len(b) // 4), b[:len(b) // 4 * 4]))


def direct_constants(read, funcs):
    """float/double constants CD2 loads directly from .rdata (outside the pool) in the given functions.
    funcs: iterable of dicts with 'address' (hex string or int) and 'size'."""
    vals = set()
    for f in funcs:
        va = f['address'] if isinstance(f['address'], int) else int(f['address'], 16)
        lis = {}
        for i, w in enumerate(words(read(va, f['size']))):
            op, rt, ra, imm = w >> 26, (w >> 21) & 31, (w >> 16) & 31, w & 0xFFFF
            sx = imm - 0x10000 if imm & 0x8000 else imm
            if op == 15 and ra == 0:
                lis[rt] = imm << 16
            elif op in FLOAT_LOADS and ra in lis:
                a = (lis[ra] + sx) & 0xFFFFFFFF
                if RDATA[0] <= a < RDATA[1] and not POOL_START <= a < POOL_START + POOL_SIZE:
                    raw = read(a, FLOAT_LOADS[op])
                    v = struct.unpack('>f' if op == 48 else '>d', raw)[0]
                    if not (math.isinf(v) or math.isnan(v)):
                        vals.add((op, v))
            elif op not in NO_GPR_WRITE and op not in FLOAT_LOADS:
                lis.pop(rt, None)
    return sorted(vals)


def qualified(mangled):
    """'?name@s1@s2@@3...' -> '::s2::s1::name' for plain data symbols; None for templates, back-references, locals"""
    m = re.match(r'\?([A-Za-z_]\w*)@((?:[A-Za-z_]\w*@)*)@([0-3])', mangled)
    if not m:
        return None
    scopes = [s for s in m.group(2).split('@') if s]
    return '::' + '::'.join(list(reversed(scopes)) + [m.group(1)])


def function_symbols(obj):
    """Qualified names of the static member and free functions defined in the object, excluding overloaded names.
    LTCG rewrites the calling convention of a function whose callers are all known (e.g. drops an unused parameter);
    in CD2 such functions are often reached through pointers (factories, callbacks), so the model takes their address."""
    secs, syms = coff.parse(obj)
    seen = {}
    for s in syms:
        if s['cls'] != 2 or s['sec'] <= 0 or not secs[s['sec'] - 1]['ch'] & 0x20:
            continue
        m = re.match(r'\?([A-Za-z_]\w*)@((?:[A-Za-z_]\w*@)*)@([SKCY])', s['name'])
        if not m:
            continue
        scopes = [x for x in m.group(2).split('@') if x]
        q = '::' + '::'.join(list(reversed(scopes)) + [m.group(1)])
        seen.setdefault(q, set()).add(s['name'])
    return sorted(q for q, names in seen.items() if len(names) == 1)


def data_symbols(obj):
    secs, syms = coff.parse(obj)
    names = set()
    for s in syms:
        if s['cls'] != 2 or s['type'] & 0x20:
            continue
        if s['sec'] > 0 and secs[s['sec'] - 1]['ch'] & 0x20:
            continue
        q = qualified(s['name'])
        if q:
            names.add(q)
    return sorted(names)


def map_functions(path):
    """The functions of a link map with the object each came from: sorted [(address, symbol, object)]."""
    fs = []
    for l in open(path):
        m = re.match(r'\s*[0-9a-f]{4}:[0-9a-f]+\s+(\S+)\s+([0-9a-f]{8})\s+f\s', l)
        if m:
            fs.append((int(m.group(2), 16), m.group(1), l.split()[-1]))
    return sorted(fs)


def map_funcs(path, exclude=()):
    """The functions of a link map: sorted [(address, symbol)], without those of the objects named in exclude."""
    return [(a, n) for a, n, o in map_functions(path) if o not in exclude]


def image_reader(path):
    d = open(path, 'rb').read()
    pe = struct.unpack_from('<I', d, 0x3C)[0]
    nsec = struct.unpack_from('<H', d, pe + 6)[0]
    opt = struct.unpack_from('<H', d, pe + 20)[0]
    base = struct.unpack_from('<I', d, pe + 24 + 28)[0]
    secs = [struct.unpack_from('<8sIIII', d, pe + 24 + opt + 40 * i) for i in range(nsec)]

    def rd(va, n):
        rva = va - base
        for name, vs, vaddr, rs, rp in secs:
            if vaddr <= rva < vaddr + max(vs, rs):
                return d[rp + rva - vaddr: rp + rva - vaddr + n]
        return b''
    return rd


def undefined_symbols(plain_obj):
    o = relocs.Obj(plain_obj)
    return {x['name'] for x in o.symbols.values() if x['sec'] == 0 and x['cls'] == 2 and x['value'] == 0 and x['name']}


def defined_symbols(plain_obj):
    o = relocs.Obj(plain_obj)
    return {x['name'] for x in o.symbols.values() if x['sec'] > 0 and x['cls'] == 2 and x['name']}


def dependencies(src, plain_obj, d, env, manifest=None, override=None):
    """The other repository files linked with /GL into src's model: [(/GL object, symbols src takes from it)].

    CD2 was linked as one program, so LTCG saw the body of every function a file calls, and a callee's body can change
    the caller's code (VFX::cRopes::ShowRopeSegments has a 16-byte larger frame because LTCG sees GDb::ConsoleOutput's
    body). A file is linked in when src calls a function that file has matched (a manifest entry not marked work in
    progress, identified as the gates identify it), and only if every symbol src takes from it is such a function. So
    LTCG sees only bodies that the gates prove identical to CD2's; a file's data, unmatched functions and everything
    else stay stubs. The rule is the same for every file and nothing is listed by hand. It goes one level deep: the
    dependency's calls into other files are stubs, but its calls within its own file reach that file's /GL bodies,
    matched or not, since the whole file is linked in. Those bodies can shape only the dependency's code, and through
    it ours; the caller is still compared word for word with CD2. override: {repository path: path of a modified
    copy} (a branch under review)."""
    if manifest is None:
        manifest = json.load(open(os.path.join(ROOT, 'config', 'matched_functions.json')))
    override = override or {}
    needed = undefined_symbols(plain_obj)
    os.makedirs(d, exist_ok=True)
    deps = []
    index = manifest_index(manifest)
    calls_into = {other for n in needed for other, _ in index.naming(n)}  # files with a matched function src takes
    for other in sorted(calls_into):
        funcs = manifest['files'][other]
        prefixes = [f['symbol'] for f in funcs if f.get('matching', True)]
        if other == src or not ltcg_built(other):
            continue  # a plain object's bodies were not /GL code in CD2: they stay stubs
        tag = 'dep_' + re.sub(r'\W', '_', os.path.splitext(other)[0])

        def cl(extra, out):
            r = buildcache.compile(plain_command(other, out, override.get(other), extra), env)
            if r.returncode:
                raise RuntimeError('%s (a dependency): compile error\n%s' % (other, r.stdout + r.stderr))
            return out
        plain = cl([], os.path.join(d, tag + '_plain.obj'))
        compiled = [n for n, _, _ in coff.functions(plain)]
        proven = {hit[0] for hit in ([n for n in compiled if symbol_matches(p, n)] for p in prefixes) if hit}
        taken = needed & defined_symbols(plain)
        if taken and taken <= proven:
            deps.append((cl(['/GL'], os.path.join(d, tag + '.obj')), taken))
    return deps


def write_stubs(names, path):
    """A plain object that defines the given symbols, each at its own address. Unresolved references would all land on
    0; with the stubs every external call and global in the LTCG image has a distinct, nameable target. The stubs are
    not /GL code, so link-time code generation cannot look into them."""
    names = sorted(names)
    if not names:
        return None
    text = b'\x4e\x80\x00\x20' * len(names)  # blr
    strtab, syms = b'', b''
    for k, n in enumerate(names):
        nb = n.encode('latin-1')
        if len(nb) <= 8:
            raw = nb.ljust(8, b'\0')
        else:
            raw = b'\0\0\0\0' + struct.pack('<I', 4 + len(strtab))
            strtab += nb + b'\0'
        syms += struct.pack('<8sIhHBB', raw, 4 * k, 1, 0x20, 2, 0)
    head = struct.pack('<HHIIIHH', 0x1F2, 1, 0, 60 + len(text), len(names), 0, 0)
    head += struct.pack('<8sIIIIIIHHI', b'.text', 0, 0, len(text), 60, 0, 0, 0, 0, 0x60500020)
    open(path, 'wb').write(head + text + syms + struct.pack('<I', 4 + len(strtab)) + strtab)
    return path


def unresolved_symbols(stdout):
    """The symbols a link's errors call unresolved. A C++ symbol is printed as `"<undecorated>" (<decorated>)`, a C one
    (the compiler's __savegprlr_N, say) bare: LTCG code generation can call one the plain object never named."""
    return {cpp or c for cpp, c in re.findall(r'error LNK20(?:01|19): unresolved external symbol '
                                              r'(?:"[^"]*" \((\S+)\)|(\S+))', stdout)}


def map_symbols(path):
    """Every symbol of the LTCG link map (publics and statics): sorted [(address, name)]."""
    out = []
    for l in open(path):
        m = re.match(r'\s*[0-9a-f]{4}:[0-9a-f]+\s+(\S+)\s+([0-9a-f]{8})\s', l)
        if m:
            out.append((int(m.group(2), 16), m.group(1)))
    return sorted(out)


def pdb_streams(path):
    """The streams of an MSF 7.00 file (the link's PDB): [bytes]."""
    d = open(path, 'rb').read()
    if not d.startswith(b'Microsoft C/C++ MSF 7.00\r\n\x1aDS\0\0\0'):
        raise RuntimeError('%s is not an MSF 7.00 PDB' % path)
    bs, _, _, ndir, _, bmap = struct.unpack_from('<6I', d, 32)
    blocks = lambda idx: b''.join(d[i * bs:(i + 1) * bs] for i in idx)
    directory = blocks(struct.unpack_from('<%dI' % -(-ndir // bs), d, bmap * bs))[:ndir]
    n = struct.unpack_from('<I', directory)[0]
    sizes, pos, out = struct.unpack_from('<%dI' % n, directory, 4), 4 + 4 * n, []
    for size in sizes:
        k = 0 if size == 0xFFFFFFFF else -(-size // bs)
        out.append(blocks(struct.unpack_from('<%dI' % k, directory, pos))[:size] if k else b'')
        pos += 4 * k
    return out


S_LDATA32, S_END = 0x110C, 0x0006
SCOPE_OPEN = {0x1102, 0x1103, 0x1104, 0x110F, 0x1110, 0x1132, 0x1146, 0x1147, 0x114D}  # thunk, block, with, procs, ...
SCOPE_CLOSE = {S_END, 0x114E, 0x114F}


def pdb_static_data(path, module):
    """The static data (S_LDATA32) of one object in the link's PDB: [(section, offset, name)]. module: the object's
    basename. A static inside a function is named '<function>::<name>'."""
    st = pdb_streams(path)
    dbi = st[3]
    modsize = struct.unpack_from('<i', dbi, 24)[0]
    out, pos = [], 64
    while pos < 64 + modsize:
        stream, symsize = struct.unpack_from('<HI', dbi, pos + 34)
        p = pos + 64
        name = dbi[p:dbi.index(b'\0', p)].decode('latin-1')
        p += len(name) + 1
        p = dbi.index(b'\0', p) + 1  # the object file name
        pos = (p + 3) & ~3
        if stream == 0xFFFF or os.path.basename(name).lower() != module.lower():
            continue
        data, i, scopes = st[stream][:symsize], 4, []
        while i + 4 <= len(data):
            ln, kind = struct.unpack_from('<HH', data, i)
            body = data[i + 4:i + 2 + ln]
            if kind in SCOPE_OPEN:
                # procedures name themselves after their fixed fields; other scopes keep the enclosing name
                scopes.append(body[35:body.index(b'\0', 35)].decode('latin-1') if kind in (0x110F, 0x1110) else
                              (scopes[-1] if scopes else ''))
            elif kind in SCOPE_CLOSE and scopes:
                scopes.pop()
            elif kind == S_LDATA32:
                _, off, sec = struct.unpack_from('<IIH', body)
                nm = body[10:body.index(b'\0', 10)].decode('latin-1')
                out.append((sec, off, '%s::%s' % (scopes[-1], nm) if scopes else nm))
            if ln < 2:
                break
            i += 2 + ln
    return out


class StaticNames:
    """The names of a file's LTCG image for the reference check: the link map's symbols, and the file's static data
    from the link's PDB (the map lists no static data, so a reference to one would otherwise be credited to the symbol
    before it). A static takes the decorated name of the plain object's static with the same qualified name, else its
    PDB name. `internal` (for relocs.check_consistency) is every name with internal linkage: each file has its own.
    sizes (tools/cvtypes.py, compile_sizes) give data_symbol the exact extents relocs.identical_copies needs, so the
    shared copies it accepts (relocs.LTCG_SHARED_COPIES) are accepted for the functions exact only under LTCG too."""

    def __init__(self, d, plain_obj, sizes=None):
        o = self._obj = relocs.Obj(plain_obj, sizes)
        self.internal = set(o.internal)
        decorated = {}
        for s in o.symbols.values():
            if s['cls'] == 3 and s['sec'] > 0 and not o.sections[s['sec'] - 1]['ch'] & 0x20:
                q = qualified(s['name'])
                if q:
                    decorated.setdefault(q, set()).add(s['name'])
        image = open(os.path.join(d, 't.pe'), 'rb').read()
        pe = struct.unpack_from('<I', image, 0x3C)[0]
        nsec, opt = struct.unpack_from('<H', image, pe + 6)[0], struct.unpack_from('<H', image, pe + 20)[0]
        base = struct.unpack_from('<I', image, pe + 24 + 28)[0]
        vas = [struct.unpack_from('<I', image, pe + 24 + opt + 40 * k + 12)[0] for k in range(nsec)]
        statics = []
        for sec, off, nm in pdb_static_data(os.path.join(d, 't.pdb'), 'src.obj'):
            if not 1 <= sec <= nsec:
                continue
            names = decorated.get('::' + nm, ())
            name = next(iter(names)) if len(names) == 1 else nm
            self.internal.add(name)
            statics.append((base + vas[sec - 1] + off, name))
        self.symbols = sorted(map_symbols(os.path.join(d, 't.map')) + statics)
        self.statics = statics

    def symbol_bytes(self, name, n):
        return None  # strings are compared by check_references itself

    def data_symbol(self, name):
        """The plain object's data of name (relocs.Obj.data_symbol): the image's statics are the plain object's"""
        return self._obj.data_symbol(name)

def references(ws, start):
    """[(index, kind, address, opcode)] of every address a function uses: calls and branches leaving it, and data
    addresses built with lis (the addi that completes one, and loads/stores through it). Mirrors masked(): exactly
    the immediates it masks are the ones resolved here."""
    out, base = [], {}
    end = start + 4 * len(ws)
    for i, w in enumerate(ws):
        op, rt, ra = w >> 26, (w >> 21) & 31, (w >> 16) & 31
        sx = (w & 0xFFFF) - 0x10000 if w & 0x8000 else w & 0xFFFF
        if op == 15 and ra == 0:
            base[rt] = (w & 0xFFFF) << 16
        elif op == 14 and ra in base and ra != 0:
            base[rt] = (base[ra] + sx) & 0xFFFFFFFF
            out.append((i, 'address', base[rt], op))
        elif (op in LOADS or op in STORES) and ra in base and ra != 0:
            out.append((i, 'load' if op in LOADS else 'store', (base[ra] + sx) & 0xFFFFFFFF, op))
            if op in LOADS and op not in (48, 49, 50, 51):
                base.pop(rt, None)
        elif op == 18:
            disp = w & 0x03FFFFFC
            if disp & 0x02000000:
                disp -= 0x04000000
            tgt = (disp if w & 2 else start + 4 * i + disp) & 0xFFFFFFFF
            if not start <= tgt < end:
                out.append((i, 'call' if w & 1 else 'branch', tgt, op))
        elif op in LOGICAL_RA_DEST:
            base.pop(ra, None)
        elif op == 31:
            base.pop(rt, None)
            base.pop(ra, None)
        elif op not in NO_GPR_WRITE and op not in LOADS:
            base.pop(rt, None)
        elif op in LOADS and op not in (48, 49, 50, 51):
            base.pop(rt, None)
    return out


MODEL = re.compile(r'^(\?g_vl_c\d+@|__pool@|VerifyLtcg|\?VerifyLtcg|\?g_verify_ltcg)')


def cstring(read, addr, limit=4096):
    """The C string at addr in read's image (with its NUL; at most limit bytes), or None."""
    out = b''
    while len(out) < limit:
        try:
            b = read(addr + len(out), 64)
        except ValueError:
            return None
        if b'\0' in b:
            return out + b.split(b'\0', 1)[0] + b'\0'
        if not b:
            return None
        out += b
    return None


def check_references(ours, cd2, symbols, our_read, cd2_read, src, fname, cd2_bytes=None, cd2_string=None, obj=None):
    """Pair our references with CD2's (same positions, as the function is exact under LTCG). Returns (consistency
    entries [(file, function, symbol, CD2 address, kind, offset, None)], problems). Calls must reach a named symbol;
    float constants and strings are compared by content (the model's own constant symbols, g_vl_c* and the pool,
    only by content). cd2_bytes(address, n) and cd2_string(address) default to reading CD2 (the facts mode passes
    recorded values instead). obj: the file's StaticNames, whose `internal` names relocs.check_consistency keeps per
    file."""
    cd2_bytes = cd2_bytes or cd2_read
    cd2_string = cd2_string or (lambda addr: cstring(cd2_read, addr))
    starts = [a for a, _ in symbols]
    entries, problems = [], []
    theirs = {(i, k): (addr, op) for i, k, addr, op in cd2}
    for i, kind, addr, op in ours:
        if (i, kind) not in theirs:
            problems.append('%s %s+%X: reference not found in CD2\'s code' % (src, fname, 4 * i))
            continue
        caddr = theirs[(i, kind)][0]
        k = bisect.bisect_right(starts, addr) - 1
        name, off = (symbols[k][1], addr - symbols[k][0]) if k >= 0 else (None, 0)
        if kind in ('call', 'branch'):
            if name is None or off:
                problems.append('%s %s+%X: call to an unnamed address' % (src, fname, 4 * i))
            else:
                entries.append((src, fname, name, caddr, kind, 4 * i, obj))
            continue
        if op in FLOAT_LOADS:  # a float constant: the values must agree
            n = FLOAT_LOADS[op]
            theirs_v = cd2_bytes(caddr, n)
            if our_read(addr, n) != theirs_v:
                problems.append('%s %s+%X: float constant %s, CD2 holds %s at %08X' % (src, fname, 4 * i,
                                our_read(addr, n).hex(), (theirs_v or b'').hex(), caddr))
            if name is None or MODEL.match(name):
                continue
        if name is None or MODEL.match(name):
            continue
        if name.startswith('??_C@'):  # a string: compare the text
            if cstring(our_read, addr) != cd2_string(caddr):
                problems.append('%s %s+%X: string %s differs from CD2 at %08X' % (src, fname, 4 * i, name[:40], caddr))
            continue
        if name.startswith('__real@'):
            continue  # its value was compared above
        entries.append((src, fname, name, (caddr - off) & 0xFFFFFFFF, kind, 4 * i, obj))
    return entries, problems


def escape_copy(text, globs, name='g_verify_ltcg_escapes'):
    """A source's text with an array appended that takes the address of each of globs (the globals and static/free
    functions it refers to or defines): LTCG treats a global whose address no /GL code takes as unaliased"""
    return text + ('\n\n// ---- appended by tools/verify_ltcg.py: take the address of every global and every static/free\n'
                   '// function this file refers to or defines\n'
                   'void *%s[] = {\n%s\n    0\n};\n' % (name, ''.join('    (void *)&%s,\n' % g for g in globs)))


def env_source(what, consts):
    """The model's env.cpp: the entry stub, the pool seed, and a `const` global for each of consts (op, value), read by a
    function compiled first so that the compiler loads those literals from a global instead of pooling them"""
    lines = ['// generated by tools/verify_ltcg.py for %s' % what,
             'extern "C" void VerifyLtcgStub(void) {}',
             'float VerifyLtcgPoolSeed(float x) { return x * 12345.678f; }']
    terms = []
    for k, (op, v) in enumerate(consts):
        if op == 48:
            lines.append('extern const float g_vl_c%d = %sf;' % (k, repr(float(struct.unpack('>f', struct.pack('>f', v))[0]))))
        else:
            lines.append('extern const double g_vl_c%d = %s;' % (k, repr(v)))
        terms.append('(double)g_vl_c%d' % k)
    lines.append('double VerifyLtcgConstRegs(void) { return %s; }' % (' + '.join(terms) or '0.0'))
    return '\n'.join(lines) + '\n'


# CD2's inlining threshold. Under LTCG, c2.dll adjusts its threshold (-inlT, 104 by default) by the size of the program
# (sub_10B53857: IL size <= 50,000 +32, <= 100,000 +24, <= 500,000 +16, <= 1,500,000 -8, <= 2,500,000 -16, else -24),
# so whether a function is inlined depends on the size of the link. CD2's inline decisions fit only thresholds 136..147
# (a sweep over the whole-program model, 2026-11-23: below 136 the vector _Insert of cRopes and cCWWeapon's
# RetReloadDuration differ, from 148 cPlayer's SpawnFromPrototype), and 136, the smallest bracket's value, is the only
# bracket value among them. A model link passes the -inlT that brings its own bracket back to 136. c2 sizes the IL of
# the reachable functions, which no tool output reports, so the size is estimated from the plain objects' code (0.238
# IL per byte, measured against c2's value for the whole-program model, 556,430).
CD2_INLT = 136
INLT_BRACKETS = ((50000, 32), (100000, 24), (500000, 16), (1500000, -8), (2500000, -16))
IL_PER_CODE_BYTE = 0.238


def code_bytes(obj):
    secs, _ = coff.parse(obj)
    return sum(len(s['data']) for s in secs if s['ch'] & 0x20)


def inline_option(plain_objects):
    """The link option that gives a model made of these (plain) objects CD2's inlining threshold"""
    size = IL_PER_CODE_BYTE * sum(code_bytes(o) for o in plain_objects if os.path.exists(o))
    adjust = next((a for limit, a in INLT_BRACKETS if size <= limit), -24)
    return '/d2:-inlT%d' % (CD2_INLT - adjust)


def build_ltcg(srcpath, plain_obj, consts, d, env, extra_flags=(), deps=()):
    """Build an LTCG image of one source file with the generated program model (escapes, constant registrations,
    pool seed, and deps: the matched callees' files from dependencies()) in directory d. plain_obj is the file's
    plain-compiled object (for its data symbols).
    Returns (read function for the image, sorted [(address, symbol)] of the file's functions, number of escaped
    globals).
    The link's outputs (t.pe, t.map, t.pdb) of a repository file are cached (tools/buildcache.py), keyed by everything
    the model is built from: the toolchain, flags and environment, the generated copy and env.cpp, the stub names, the
    dependencies' /GL objects, and every file the copy's compile opened (checked again on each hit)."""
    flags = FLAGS + ['/I' + os.path.dirname(os.path.abspath(srcpath))] + list(extra_flags)
    included = []  # what the copy's compile opened (/showIncludes), for the cache

    def cl(extra, out, path):
        r = subprocess.run([os.path.join(BIN, 'cl.exe')] + flags + extra + ['/Fo' + out, path],
                           env=env, capture_output=True, text=True)
        files, stdout = buildcache.split_includes(r.stdout)
        included.extend(files)
        if r.returncode:
            raise RuntimeError('%s: compile error\n%s' % (path, stdout + r.stderr))
    os.makedirs(d, exist_ok=True)
    globs = data_symbols(plain_obj) + function_symbols(plain_obj)
    tag = os.path.splitext(os.path.basename(srcpath))[0]
    copy = os.path.join(d, tag + '_ltcg.cpp')
    text = escape_copy(open(srcpath).read(), globs)
    open(copy, 'w').write(text)
    envsrc = os.path.join(d, 'env.cpp')
    env_text = env_source(srcpath, consts)
    open(envsrc, 'w').write(env_text)
    for stale in ('t.pe', 't.map', 't.pdb'):
        if os.path.exists(os.path.join(d, stale)):
            os.remove(os.path.join(d, stale))
    # the file's external symbols get stubs, except what the dependencies define; the linker reports which of them the
    # LTCG build defines itself (drop those) and what else it needs (add those), so link at most three times. The
    # dependencies come after src.obj, so src.obj keeps the inline and template functions both define.
    names = undefined_symbols(plain_obj) - set().union(*[taken for _, taken in deps])
    outputs = {ext: os.path.join(d, 't' + ext) for ext in ('.pe', '.map', '.pdb')}
    # a dependency's plain object sits beside its /GL object (dependencies())
    inline = inline_option([plain_obj] + [os.path.splitext(obj)[0] + '_plain.obj' for obj, _ in deps])
    cached = None
    if buildcache.cacheable(srcpath):
        cached = buildcache.entry('ltcg', buildcache.digest(dict(
            buildcache.common(env, os.path.dirname(os.path.abspath(srcpath))), flags=flags, inline=inline,
            source=os.path.abspath(srcpath), model=buildcache.sha(text.encode('utf-8', 'surrogateescape')),
            env_model=buildcache.sha(env_text.encode('utf-8', 'surrogateescape')),
            stubs=sorted(names), deps=[[os.path.basename(obj), buildcache.file_sha(obj), sorted(taken)]
                                       for obj, taken in deps])))
        if buildcache.lookup(cached) is not None and buildcache.restore(cached, outputs):
            buildcache.count('ltcg_hits')
            return (image_reader(outputs['.pe']), map_funcs(outputs['.map'], {os.path.basename(obj) for obj, _ in deps}),
                    len(globs))
        buildcache.count('ltcg_misses')
    # /Z7: the file's debug records name its static data in the link's PDB (static_symbols); the code is the same
    cl(['/GL', '/Z7', '/Dprivate=public', '/Dprotected=public', '/showIncludes'], os.path.join(d, 'src.obj'), copy)
    cl(['/GL'], os.path.join(d, 'env.obj'), envsrc)
    for attempt in range(3):
        for stale in ('t.pe', 't.map', 't.pdb'):
            if os.path.exists(os.path.join(d, stale)):
                os.remove(os.path.join(d, stale))
        stubs = write_stubs(names, os.path.join(d, 'stubs.obj'))
        r = subprocess.run([os.path.join(BIN, 'link.exe'), '/nologo', '/LTCG', '/NODEFAULTLIB', '/FORCE:UNRESOLVED',
                            '/ENTRY:VerifyLtcgStub', '/OPT:NOREF', '/OPT:NOICF', '/MAP:' + os.path.join(d, 't.map'),
                            '/DEBUG', '/INCREMENTAL:NO', '/PDB:' + os.path.join(d, 't.pdb'), inline,
                            '/OUT:' + os.path.join(d, 't.exe'), os.path.join(d, 'env.obj'), os.path.join(d, 'src.obj')]
                           + [obj for obj, _ in deps] + ([stubs] if stubs else []), env=env, capture_output=True, text=True)
        dup = set(re.findall(r'stubs\.obj : error LNK2005: .*?\((\S+)\) already defined', r.stdout))
        unres = unresolved_symbols(r.stdout)
        if not dup and not unres:
            break
        names = (names - dup) | unres
    image = os.path.join(d, 't.pe')
    if not os.path.exists(image):
        raise RuntimeError('LTCG link failed\n%s' % r.stdout[-2000:])
    if cached and all(os.path.exists(p) for p in outputs.values()):
        buildcache.store(cached, outputs, dict(deps=buildcache.deps_of(included), source=srcpath))
    return (image_reader(image), map_funcs(os.path.join(d, 't.map'), {os.path.basename(obj) for obj, _ in deps}),
            len(globs))


def compare_ltcg(ltcg_read, fs, symbol, target, va, absolute_offsets=()):
    """Compare the LTCG image's function matching `symbol` with target bytes at CD2 address va.
    Returns (exact, good_words, target_words), or None if the symbol is not in the image."""
    lt = [a for a, n in fs if symbol_matches(symbol, n)]
    if not lt:
        return None
    a = lt[0]
    nxt = [x for x, _ in fs if x > a]
    return compare_at(ltcg_read, a, nxt[0] if nxt else None, target, va, absolute_offsets)


def compare_at(ltcg_read, a, nxt, target, va, absolute_offsets=()):
    """Compare the LTCG image's function at a (nxt: where the next function starts, or None) with target bytes at CD2
    address va. Returns (exact, good_words, target_words)."""
    lw = words(ltcg_read(a, (nxt if nxt else a + len(target) + 64) - a))
    while lw and lw[-1] == 0:
        lw.pop()
    tw = words(target)
    if len(lw) > len(tw) and ends_function(tw):
        # the map gives no end for the last function of a section; words after a target that cannot fall through
        # (and has no branch past its end) are not part of it
        lw = lw[:len(tw)]
    mt, ml = masked(tw, va, absolute_offsets), masked(lw, a, absolute_offsets)
    good = sum(1 for x, y in zip(ml, mt) if x == y)
    return len(lw) == len(tw) and good == len(tw), good, len(tw)


def ends_function(ws):
    """True if the code ends in an unconditional b/blr/bctr and no branch inside it targets beyond its end."""
    if not ws or not (ws[-1] in (0x4E800020, 0x4E800420) or (ws[-1] >> 26 == 18 and not ws[-1] & 3)):
        return False
    for i, w in enumerate(ws):
        op = w >> 26
        if op == 16 and not w & 2:
            disp = w & 0xFFFC
            disp = disp - 0x10000 if disp & 0x8000 else disp
        elif op == 18 and not w & 3:
            disp = w & 0x03FFFFFC
            disp = disp - 0x04000000 if disp & 0x02000000 else disp
        else:
            continue
        tgt = 4 * i + disp
        if 4 * len(ws) <= tgt < 4 * len(ws) + 64:  # a branch just past the end: the function continues
            return False
    return True


def check_file(src, funcs, read, env, d, srcpath=None, out=print, manifest=None):
    """Build one source file under LTCG (srcpath: a modified copy, for the self-test) and compare its functions.
    manifest: the one dependencies() reads (default: config/matched_functions.json).
    Returns dict(results [(entry, plain_exact, ltcg_exact)], entries, problems, known, nref) or None on a build error;
    entries/problems: the reference check of the functions exact only under LTCG."""
    os.makedirs(d, exist_ok=True)
    srcpath = srcpath or os.path.join(ROOT, src)
    plain = os.path.join(d, 'plain.obj')
    r = buildcache.compile(plain_command(src, plain, srcpath), env)
    if r.returncode:
        out('%s: COMPILE ERROR\n%s' % (src, r.stdout + r.stderr))
        return None
    consts = direct_constants(read, funcs)
    try:
        deps = dependencies(src, plain, d, env, manifest)
        ltcg_read, fs, nglobs = build_ltcg(srcpath, plain, consts, d, env,
                                           extra_flags=['/I' + os.path.dirname(os.path.join(ROOT, src))] + file_flags(src),
                                           deps=deps)
    except RuntimeError as e:
        out('%s: %s' % (src, e))
        return None
    compiled = list(coff.functions(plain))
    sizes = compile_sizes(src, d, env, srcpath)
    names = StaticNames(d, plain, sizes)
    syms = names.symbols
    robj = relocs.Obj(plain, sizes)
    res = dict(results=[], entries=[], problems=[], known={}, nref=0, reached=[])
    for f in funcs:
        hit = [n for n, _, _ in compiled if symbol_matches(f['symbol'], n)]
        if hit and f.get('matching', True):
            res['known'][relocs.known_key(src, hit[0], names)] = int(f['address'], 16)
    out('%s  (%d globals escaped, %d constants registered, %d matched callee(s) from %d file(s))'
        % (src, nglobs, len(consts), sum(len(taken) for _, taken in deps), len(deps)))
    for f in funcs:
        va, size = int(f['address'], 16), f['size']
        target = read(va, size)
        found = [(n, c, rel) for n, c, rel in compiled if symbol_matches(f['symbol'], n)]
        plain_exact = bool(found) and coff.compare(found[0][1], target, found[0][2])[0]
        absolute = getattr(found[0][2], 'absolute', ()) if found else ()
        cmp = compare_ltcg(ltcg_read, fs, f['symbol'], target, va, absolute)
        if cmp is None:
            lt_exact, status = False, 'not found in LTCG image'
        else:
            lt_exact, good, n = cmp
            status = 'EXACT' if lt_exact else '%d/%d words' % (good, n)
        if lt_exact and f.get('ltcg') and f.get('matching', True):
            # exact only under LTCG: the plain gate cannot check its references, so check them here
            a = [x for x, nm in fs if symbol_matches(f['symbol'], nm)][0]
            lw = words(ltcg_read(a, len(target)))
            e, pr = check_references(references(lw, a), references(words(target), va), syms, ltcg_read, read,
                                     src, f['symbol'], obj=names)
            res['entries'] += e
            res['problems'] += pr
            res['nref'] += 1
        res['results'].append((f, plain_exact, lt_exact))
        out('  %08X %4d bytes  plain %-5s  ltcg %-14s %s%s' % (va, size, 'EXACT' if plain_exact else 'diff', status,
            found[0][0][:70] if found else f['symbol'], '' if f.get('matching', True) else '   [work in progress]'))
    data_entries = plain_names(res['entries'], robj)
    n = len(data_entries)
    res['reached'], pr = relocs.check_all_data(data_entries, game_data_check(read), extents=False)
    res['entries'] += data_entries[n:]  # the pointers found in the data
    res['problems'] += pr
    return res


def plain_names(entries, plain_obj):
    """The references of the functions exact only under LTCG, with the plain object (whose names the link map uses)
    as the definer of the data they reach, for relocs.check_all_data"""
    return [(f, fn, sym, addr, kind, off, plain_obj) for f, fn, sym, addr, kind, off, _ in entries]


# ---- the whole-program model: every /GL game file in one /LTCG link
#
# CD2's LTCG saw the whole program at once. The per-file model (build_ltcg) sees one file, the stubs of everything else,
# and the matched callees of other files one level deep, so a verdict there can depend on which other functions happen
# to be matched. The whole-program model links every game source CD2 built with /GL into one image, each with its own
# escape array, one env.cpp with the constant registrations of every file's functions, and stubs only for the symbols
# no source defines; each function is then compared with CD2 as check_file compares it.

def whole_sources():
    """The repository's game sources CD2 built with /GL (ltcg_built), outside the middleware, in a stable order"""
    out = []
    for dirpath, _, files in os.walk(os.path.join(ROOT, 'src')):
        for n in files:
            src = os.path.relpath(os.path.join(dirpath, n), ROOT).replace(os.sep, '/')
            if src.endswith('.cpp') and not src.startswith(MIDDLEWARE_ROOT) and ltcg_built(src):
                out.append(src)
    return sorted(out)


def whole_tag(src):
    """The base name of src's objects in the whole-program model, unique in the link (its map and PDB name objects by
    their base name)"""
    return re.sub(r'\W', '_', os.path.splitext(src)[0])


def whole_object(src, d, env):
    """src's objects for the whole-program model, in d: its plain object (the plain gate's command, so usually from the
    cache) and the /GL object of a copy with an escape array of its own name, as build_ltcg compiles it. The /GL object
    is cached, keyed by the copy's text, the flags and every file its compile opened. Returns (plain, /GL object)."""
    tag = whole_tag(src)
    plain = os.path.join(d, tag + '_plain.obj')
    r = buildcache.compile(plain_command(src, plain), env)
    if r.returncode:
        raise RuntimeError('%s: compile error\n%s' % (src, r.stdout + r.stderr))
    path = os.path.join(ROOT, src)
    text = escape_copy(open(path).read(), data_symbols(plain) + function_symbols(plain), 'g_verify_ltcg_escapes_' + tag)
    copy, obj = os.path.join(d, tag + '.cpp'), os.path.join(d, tag + '.obj')
    open(copy, 'w').write(text)
    flags = (FLAGS + ['/I' + os.path.dirname(path)] + file_flags(src) +
             ['/GL', '/Z7', '/Dprivate=public', '/Dprotected=public'])
    cached = None
    if buildcache.cacheable(path):
        cached = buildcache.entry('whole', buildcache.digest(dict(
            buildcache.common(env, os.path.dirname(path)), flags=flags, source=path,
            model=buildcache.sha(text.encode('utf-8', 'surrogateescape')))))
        if buildcache.lookup(cached) is not None and buildcache.restore(cached, {'.obj': obj}):
            buildcache.count('whole_hits')
            return plain, obj
        buildcache.count('whole_misses')
    r = subprocess.run([os.path.join(BIN, 'cl.exe')] + flags + ['/showIncludes', '/Fo' + obj, copy],
                       env=env, capture_output=True, text=True)
    included, stdout = buildcache.split_includes(r.stdout)
    if r.returncode:
        raise RuntimeError('%s: compile error in the whole-program model\n%s' % (src, stdout + r.stderr))
    if cached:
        buildcache.store(cached, {'.obj': obj}, dict(deps=buildcache.deps_of(included), source=src))
    return plain, obj


def build_whole(sources, consts, d, env, inline=None):
    """Build the whole-program model in d: every source's objects (whole_object), one env.cpp (env_source) with the
    constant registrations consts, and stubs for the symbols no source defines, linked with /LTCG as one program.
    inline: the inlining-threshold option (default inline_option(); '' leaves c2's own, for the self-test).
    Returns (read function for the image, sorted [(address, symbol, object)] of its functions, {source: plain object},
    {'compile': seconds, 'link': seconds}). Raises RuntimeError on a compile error, and when two sources define the same
    symbol: that is an ownership error (AGENTS.md rule 5), never something to force through the link."""
    os.makedirs(d, exist_ok=True)
    t0 = time.time()
    with concurrent.futures.ThreadPoolExecutor(max_workers=WORKERS) as pool:
        built = dict(zip(sources, pool.map(lambda s: whole_object(s, d, env), sources)))
    envsrc, envobj = os.path.join(d, 'env.cpp'), os.path.join(d, 'env.obj')
    open(envsrc, 'w').write(env_source('the whole program', consts))
    r = subprocess.run([os.path.join(BIN, 'cl.exe')] + FLAGS + ['/GL', '/Fo' + envobj, envsrc],
                       env=env, capture_output=True, text=True)
    if r.returncode:
        raise RuntimeError('env.cpp: compile error\n%s' % (r.stdout + r.stderr))
    t1 = time.time()
    defined = set().union(*(defined_symbols(p) for p, _ in built.values()))
    names = set().union(*(undefined_symbols(p) for p, _ in built.values())) - defined
    outputs = {ext: os.path.join(d, 't' + ext) for ext in ('.pe', '.map', '.pdb')}
    if inline is None:
        inline = inline_option([p for p, _ in built.values()])
    # the link is cached, keyed by everything it reads: its objects (each cached by its own inputs), env.cpp, the stub
    # names and the options
    cached = None
    if buildcache.enabled():
        cached = buildcache.entry('whole', buildcache.digest(dict(
            buildcache.common(env, os.path.join(ROOT, 'src')), inline=inline, stubs=sorted(names),
            env_model=buildcache.file_sha(envsrc),
            objects=[[os.path.basename(o), buildcache.file_sha(o)] for _, o in built.values()])))
        if buildcache.lookup(cached) is not None and buildcache.restore(cached, {'.pe': outputs['.pe'], '.map': outputs['.map']}):
            buildcache.count('whole_hits')
            return (image_reader(outputs['.pe']), map_functions(outputs['.map']), {s: p for s, (p, _) in built.items()},
                    dict(compile=round(t1 - t0, 1), link=0.0, inline=inline or 'c2 default'))
        buildcache.count('whole_misses')
    for attempt in range(3):
        for stale in list(outputs.values()) + [os.path.join(d, 't.exe')]:
            if os.path.exists(stale):
                os.remove(stale)
        stubs = write_stubs(names, os.path.join(d, 'stubs.obj'))
        args = ['/nologo', '/LTCG', '/NODEFAULTLIB', '/FORCE:UNRESOLVED', '/ENTRY:VerifyLtcgStub', '/OPT:NOREF',
                '/OPT:NOICF', '/MAP:' + outputs['.map'], '/DEBUG', '/INCREMENTAL:NO', '/PDB:' + outputs['.pdb']] + (
                    [inline] if inline else []) + [
                '/OUT:' + os.path.join(d, 't.exe'), envobj] + [o for _, o in built.values()] + ([stubs] if stubs else [])
        rsp = os.path.join(d, 'link.rsp')
        open(rsp, 'w').write('\n'.join('"%s"' % a for a in args) + '\n')  # 491 objects overrun a command line
        r = subprocess.run([os.path.join(BIN, 'link.exe'), '@' + rsp], env=env, capture_output=True, text=True)
        clash = sorted(set(m for m in re.findall(r'^\s*(\S+\.obj) : error LNK2005: (.*?) already defined in (\S+\.obj)',
                                                    r.stdout, re.M) if m[0] != 'stubs.obj'))
        if clash:
            raise RuntimeError('whole-program link: %d symbol(s) defined by two sources\n%s' % (
                len(clash), '\n'.join('  %s and %s: %s' % (a, c, s[:160]) for a, s, c in clash[:40])))
        dup = set(re.findall(r'stubs\.obj : error LNK2005: .*?\((\S+)\) already defined', r.stdout))
        unres = unresolved_symbols(r.stdout)
        if not dup and not unres:
            break
        names = (names - dup) | unres
    if not os.path.exists(outputs['.pe']):
        raise RuntimeError('whole-program link failed\n%s' % r.stdout[-3000:])
    if cached:
        buildcache.store(cached, {'.pe': outputs['.pe'], '.map': outputs['.map']}, dict(deps=[], source='whole program'))
    return (image_reader(outputs['.pe']), map_functions(outputs['.map']), {s: p for s, (p, _) in built.items()},
            dict(compile=round(t1 - t0, 1), link=round(time.time() - t1, 1), inline=inline or 'c2 default'))


def game_judge(read):
    """check_whole's judge from CD2's bytes"""
    def judge(f, ltcg_read, a, nxt, absolute):
        va = int(f['address'], 16)
        exact, good, n = compare_at(ltcg_read, a, nxt, read(va, f['size']), va, absolute)
        return exact, '%d/%d words' % (good, n)
    return judge


def whole_constants(read, manifest):
    """The constant registrations of the whole-program model: those of every source's functions"""
    return direct_constants(read, [f for s in whole_sources() for f in manifest['files'].get(s, [])])


def check_whole(env, d, manifest, consts, judge, inline=None):
    """Build the whole-program model and judge every manifest function of its sources: judge(entry, read function for
    our image, our address, the next function's address or None, absolute offsets) -> (exact, words). Returns
    dict(rows [dict(source, address, size, symbol, tracked, ltcg_only, whole, words, object)], times, sources,
    constants)."""
    sources = whole_sources()
    ltcg_read, fs, plains, times = build_whole(sources, consts, d, env, inline)
    starts = sorted({a for a, _, _ in fs})
    rows = []
    for src in sources:
        own = (whole_tag(src) + '.obj').lower()
        compiled = list(coff.functions(plains[src]))
        for f in manifest['files'].get(src, []):
            found = [(n, c, rel) for n, c, rel in compiled if symbol_matches(f['symbol'], n)]
            absolute = getattr(found[0][2], 'absolute', ()) if found else ()
            # a COMDAT appears once, under the object whose copy the linker kept: the file's own copy first
            hits = ([(a, o) for a, n, o in fs if o.lower() == own and symbol_matches(f['symbol'], n)] or
                    [(a, o) for a, n, o in fs if symbol_matches(f['symbol'], n)])
            row = dict(source=src, address=f['address'], size=f['size'], symbol=f['symbol'],
                       tracked=f.get('matching', True), ltcg_only=bool(f.get('ltcg')))
            if hits:
                a, obj = hits[0]
                k = bisect.bisect_right(starts, a)
                exact, words_ = judge(f, ltcg_read, a, starts[k] if k < len(starts) else None, absolute)
                row.update(whole=exact, words=words_, object=obj)
            else:
                row.update(whole=False, words='not in image', object=None)
            rows.append(row)
    return dict(rows=rows, times=times, sources=len(sources), constants=len(consts))


def whole_main(read, env, manifest, keep=None, report=None):
    """`verify_ltcg.py <exe> --whole`: every matched function must be exact in the whole-program model too (the
    per-file gate checks their references and data). Writes the rows as JSON to report (default
    build/cd2/whole_ltcg.json). Returns the exit status."""
    work = keep or work_dir('whole_')
    try:
        res = check_whole(env, work, manifest, whole_constants(read, manifest), game_judge(read))
    except RuntimeError as e:
        print(str(e))
        return 1
    finally:
        if not keep:
            shutil.rmtree(work, ignore_errors=True)
    rows = res['rows']
    tracked = [r for r in rows if r['tracked']]
    flips = [r for r in tracked if not r['whole']]
    newly = [r for r in rows if not r['tracked'] and r['whole']]
    print('whole-program model: %d sources, %d constants registered, %s; compile %.0f s, link %.0f s'
          % (res['sources'], res['constants'], res['times']['inline'], res['times']['compile'], res['times']['link']))
    for r in flips:
        print('  FLIP   %s  %-12s %s  %s%s' % (r['address'], r['words'], r['source'], r['symbol'][:70],
                                              '  [ltcg]' if r['ltcg_only'] else ''))
    for r in newly:
        print('  NEW    %s  %s  %s   [work in progress, exact here]' % (r['address'], r['source'], r['symbol'][:70]))
    print('%d functions: %d of %d matched functions exact in the whole-program model (%d not: %d exact only under '
          'LTCG); %d work-in-progress function(s) exact here' % (
              len(rows), len(tracked) - len(flips), len(tracked), len(flips),
              sum(1 for r in flips if r['ltcg_only']), len(newly)))
    report = report or os.path.join(ROOT, 'build', 'cd2', 'whole_ltcg.json')
    os.makedirs(os.path.dirname(report), exist_ok=True)
    with open(report, 'w') as fh:
        json.dump(res, fh, indent=1)
    print('report: %s' % report)
    return 1 if flips else 0


def whole_self_test(read, env, manifest):
    """The whole-program gate can fail: with c2's own inlining threshold the model is a program of a larger size
    bracket than CD2's, and cCharacterEntityIF::AddEquipment (0x823EC070), where CD2 expands the inline by-name
    cCharacterInterface::AddEquipment, calls it out of line; with the threshold inline_option() gives, it is exact."""
    work = work_dir('whole_selftest_')
    consts = whole_constants(read, manifest)
    ok = True
    for what, inline, want in (('the CD2 inlining threshold', None, True), ("c2's own inlining threshold", '', False)):
        res = check_whole(env, os.path.join(work, 'default' if inline == '' else 'pinned'), manifest, consts,
                          game_judge(read), inline)
        exact = any(r['whole'] for r in res['rows'] if r['address'] == '0x823EC070')
        good = exact == want
        ok &= good
        print('self-test %-30s %s' % (what, ('accepted' if want else 'caught') if good else
                                      ('WRONGLY REJECTED' if want else 'NOT CAUGHT')))
    shutil.rmtree(work, ignore_errors=True)
    return ok


def self_test(read, env):
    """Plant changes in a function that is exact only under LTCG; its bytes stay exact, each change must be caught."""
    src = 'src/VFX/cAmbientVFXSpawner.cpp'
    manifest = json.load(open(os.path.join(ROOT, 'config', 'matched_functions.json')))
    funcs = manifest['files'][src]
    text = open(os.path.join(ROOT, src), newline='').read()
    anchor = text.index('void cAmbientVFXSpawner::CalcRandInitSpawnTime()')
    # RetGameTime() is inline: g_bUseStoredTime ? g_nStoredTime : CalcGameTime(). The plants spell it out with another
    # function or global of the same type, so the code stays the same and only a reference changes.
    other = ('namespace RWS { namespace Time { unsigned int VerifyLtcgOtherTime(); extern unsigned int g_nVerifyLtcgOther; } }\n')
    cases = [('a different float constant', '(unsigned int)(f * -1000.0f)', '(unsigned int)(f * -2000.0f)', ''),
             ('a call to the wrong function', 'RWS::Time::RetGameTime()',
              '(RWS::Time::g_bUseStoredTime ? RWS::Time::g_nStoredTime : RWS::Time::VerifyLtcgOtherTime())', other),
             ('a read of the wrong global', 'RWS::Time::RetGameTime()',
              '(RWS::Time::g_bUseStoredTime ? RWS::Time::g_nVerifyLtcgOther : RWS::Time::CalcGameTime())', other)]
    aliases = relocs.load_aliases(os.path.join(ROOT, 'config', 'symbol_aliases.txt'))
    ok = True
    work = work_dir('ltcg_selftest_')
    for what, old, new, decl in cases:
        i = text.index(old, anchor)
        mod = decl + text[:i] + new + text[i + len(old):]
        path = os.path.join(work, 'case.cpp')
        open(path, 'w', newline='').write(mod)
        res = check_file(src, funcs, read, env, os.path.join(work, 'build'), srcpath=path, out=lambda m: None)
        exact = res and any(lt for f, _, lt in res['results'] if 'CalcRandInitSpawnTime' in f['symbol'])
        problems = (res['problems'] + relocs.check_consistency(res['entries'], read, aliases, res['known'])) if res else []
        caught = bool(exact) and bool(problems)
        ok &= caught
        print('self-test %-30s %s' % (what, 'caught' if caught else ('NOT CAUGHT' if exact else 'NOT A VALID PLANT (bytes differ)')))
    res = check_file(src, funcs, read, env, os.path.join(work, 'clean'), out=lambda m: None)
    clean = res is not None and not res['problems'] and not relocs.check_consistency(res['entries'], read, aliases, res['known'])
    print('self-test %-30s %s' % ('the unmodified file', 'accepted' if clean else 'WRONGLY REJECTED'))
    # static data: the link map lists none, so StaticNames names it from the link's PDB. cAiPlayer's LTCG-only
    # fPhysicsSimulationTick and nPART_PERCENT_WEIGHT initializers both read the object's own g_GlobalConstants; a
    # shadowing copy of cRagdollProfile.h (found first, beside the copied source) makes nPART read another static of
    # the same type. The code stays the same, and CD2's one address then has two names in the file.
    src2 = 'src/AI/cAiPlayer.cpp'
    funcs2 = manifest['files'][src2]
    hdr = open(os.path.join(ROOT, 'include', 'CHARACTER', 'cRagdollProfile.h'), newline='').read()
    old2, decl2 = 'Fun_Runtime::g_GlobalConstants.CONST_FLOAT_1 / 12.0f', 'static const float nPART_PERCENT_WEIGHT'
    planted = os.path.join(work, 'static')
    os.makedirs(os.path.join(planted, 'CHARACTER'))
    open(os.path.join(planted, 'CHARACTER', 'cRagdollProfile.h'), 'w', newline='').write(
        hdr.replace(old2, 'g_VerifyLtcgOtherConstants.CONST_FLOAT_1 / 12.0f').replace(
            decl2, 'static Fun_Runtime::tGlobalConstants g_VerifyLtcgOtherConstants;\n' + decl2))
    copy2 = os.path.join(planted, os.path.basename(src2))
    shutil.copy(os.path.join(ROOT, src2), copy2)
    # data: the same initializer reads the file's own g_GlobalConstants copy, initialized data; a shadowing copy of
    # fun_runtime/class.h changes one of its values (the constructor keeps the members opaque, so the code stays)
    cls = open(os.path.join(ROOT, 'include', 'fun_runtime', 'class.h'), newline='').read()
    data_dir = os.path.join(work, 'data')
    os.makedirs(os.path.join(data_dir, 'fun_runtime'))
    open(os.path.join(data_dir, 'fun_runtime', 'class.h'), 'w', newline='').write(
        cls.replace('CONST_FLOAT_0d25(0.25f)', 'CONST_FLOAT_0d25(0.5f)'))
    copy3 = os.path.join(data_dir, os.path.basename(src2))
    shutil.copy(os.path.join(ROOT, src2), copy3)
    clean_problems = None
    for what, path, planted_case in (('the unmodified static readers', None, False), ('a read of the wrong static', copy2, True),
                                     ('a changed initial value', copy3, True)):
        res = check_file(src2, funcs2, read, env, os.path.join(work, 'static_%d' % len(what)), srcpath=path,
                         out=lambda m: None)
        exact = bool(res) and any(lt for f, _, lt in res['results'] if 'nPART_PERCENT_WEIGHT' in f['symbol'])
        problems = (res['problems'] + relocs.check_consistency(res['entries'], read, aliases, res['known'])) if res else []
        if clean_problems is None:
            clean_problems = set(problems)
            good = exact and not problems
        else:  # a plant must add a problem to the unmodified file's
            good = exact and bool(set(problems) - clean_problems)
        ok &= good
        print('self-test %-30s %s' % (what, ('caught' if planted_case else 'accepted') if good else
                                      'NOT A VALID PLANT (bytes differ)' if not exact else
                                      'NOT CAUGHT' if planted_case else 'WRONGLY REJECTED'))
    if 'CONST_FLOAT_0d25(0.25f)' not in cls:
        print('self-test %-30s cannot plant it in fun_runtime/class.h (update the self-test)' % 'a changed initial value')
        ok = False
    # dependencies(): ShowRopeSegments is exact only when LTCG sees GDb::ConsoleOutput's body, so it must match while
    # ConsoleOutput is a matched function and must not once ConsoleOutput is work in progress (then it is a stub)
    rope, callee = 'src/VFX/cRopes.cpp', 'src/GDb/ConsoleOutput.cpp'
    unproven = dict(manifest, files=dict(manifest['files'], **{callee: [dict(f, matching=False)
                                                                        for f in manifest['files'][callee]]}))
    for what, man, want in (('a matched callee is seen', manifest, True), ('an unmatched callee is a stub', unproven, False)):
        res = check_file(rope, manifest['files'][rope], read, env, os.path.join(work, 'dep_%d' % want), out=lambda m: None,
                         manifest=man)
        exact = bool(res) and any(lt for f, _, lt in res['results'] if 'ShowRopeSegments' in f['symbol'])
        ok &= exact == want
        print('self-test %-30s %s' % (what, 'ok' if exact == want else 'WRONG (ShowRopeSegments %s)'
                                      % ('exact' if exact else 'differs')))
    ok &= cache_self_test(read, env, manifest, os.path.join(work, 'cache'))
    shutil.rmtree(work, ignore_errors=True)
    return ok and clean


def verdicts(res):
    """What the gate concludes from a check_file result, without our image's own addresses (which move with the length
    of the build folder's name, so that two fresh builds differ there too)"""
    if res is None:
        return None
    return ([(f['address'], plain, lt) for f, plain, lt in res['results']], sorted(res['problems']),
            sorted(e[:6] for e in res['entries']), sorted((repr(k), v) for k, v in res['known'].items()),
            sorted((f, sym, addr, d['size']) for f, sym, addr, _, d in res['reached']))


def cache_self_test(read, env, manifest, work):
    """The LTCG cache (build_ltcg): a model built once is reused, a reused model gives the gate the same verdicts as a
    fresh build, and a changed header the model's compile read is not reused."""
    src = 'src/VFX/cAmbientVFXSpawner.cpp'
    saved = buildcache.CACHE, os.environ.pop('CD2_NO_CACHE', None)
    buildcache.CACHE = os.path.join(work, 'store')

    def run(n):
        return verdicts(check_file(src, manifest['files'][src], read, env, os.path.join(work, 'build_%d' % n),
                                   out=lambda m: None))
    try:
        before = dict(buildcache.stats)
        first, second = run(1), run(2)
        reused = (buildcache.stats['ltcg_misses'] == before['ltcg_misses'] + 1 and
                  buildcache.stats['ltcg_hits'] == before['ltcg_hits'] + 1)
        os.environ['CD2_NO_CACHE'] = '1'
        fresh = run(3)
        del os.environ['CD2_NO_CACHE']
        same = first is not None and first == second == fresh
        real = buildcache.file_sha  # a header the model's compile read now hashes differently
        buildcache.file_sha = lambda p: 'changed' if p.lower().endswith('cambientvfxspawner.h') else real(p)
        try:
            run(4)
        finally:
            buildcache.file_sha = real
        missed = buildcache.stats['ltcg_misses'] == before['ltcg_misses'] + 2
    finally:
        buildcache.CACHE = saved[0]
        if saved[1] is not None:
            os.environ['CD2_NO_CACHE'] = saved[1]
    for what, good, word in (('LTCG cache reuses a model', reused, 'accepted'),
                             ('reused model, same verdicts', same, 'accepted'),
                             ('LTCG cache misses a header', missed, 'caught')):
        print('self-test %-30s %s' % (what, word if good else 'WRONGLY REJECTED' if word == 'accepted' else 'NOT CAUGHT'))
    return reused and same and missed


def main():
    args = sys.argv[1:]
    keep = None
    if '--keep' in args:
        i = args.index('--keep')
        keep = args[i + 1]
        del args[i:i + 2]
    test = '--self-test' in args
    whole = '--whole' in args
    args = [x for x in args if x not in ('--self-test', '--whole')]
    if not args:
        print(__doc__)
        sys.exit(2)
    check_toolchain()
    exe = open(args[0], 'rb').read()
    only = args[1] if len(args) > 1 else ''
    read, entry = pe_reader(exe)
    if entry != EXPECTED_ENTRY:
        sys.exit('This executable has entry %08X, not the title-update build (%08X). Use the patched XEX only.' % (entry, EXPECTED_ENTRY))
    env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'],
               INCLUDE=os.path.join(XDK, 'include', 'xbox') + ';' + os.path.join(ROOT, 'include'))
    manifest = json.load(open(os.path.join(ROOT, 'config', 'matched_functions.json')))
    if test:
        sys.exit(0 if (whole_self_test(read, env, manifest) if whole else self_test(read, env)) else 1)
    if whole:
        sys.exit(whole_main(read, env, manifest, keep))
    work = keep or work_dir('ltcg_')
    totals = dict(n=0, plain=0, ltcg=0, tracked=0, tracked_ok=0)
    ref_entries, ref_problems, known, nref, reached = [], [], {}, 0, []

    def one(job):
        """One file's build, in its own directory, with its output kept for printing in manifest order."""
        src, funcs = job
        lines = []
        res = check_file(src, funcs, read, env, os.path.join(work, re.sub(r'\W', '_', os.path.splitext(src)[0])),
                         out=lines.append)
        return lines, res
    jobs = [(src, funcs) for src, funcs in manifest['files'].items() if only in src and ltcg_built(src)]
    plain_objects = [src for src in manifest['files'] if only in src and not ltcg_built(src)]
    pool = concurrent.futures.ThreadPoolExecutor(max_workers=WORKERS)
    for lines, res in pool.map(one, jobs):
        for line in lines:
            print(line)
        if res is None:
            continue
        ref_entries += res['entries']
        ref_problems += res['problems']
        known.update(res['known'])
        nref += res['nref']
        reached += res['reached']
        for f, plain_exact, lt_exact in res['results']:
            tracked = f.get('matching', True)
            totals['n'] += 1
            totals['plain'] += plain_exact
            totals['ltcg'] += lt_exact
            totals['tracked'] += bool(tracked)
            totals['tracked_ok'] += bool(tracked) and lt_exact
    print('\n%(n)d functions: %(plain)d exact in a plain build, %(ltcg)d exact under LTCG; '
          '%(tracked_ok)d of %(tracked)d matched functions exact under LTCG' % totals
          + ('; %d plain object(s), which have no LTCG build (ltcg_built())' % len(plain_objects) if plain_objects else ''))
    ref_problems += relocs.check_extents(reached, ref_entries)
    ref_problems += relocs.check_tables(reached, *game_tables(read)[1])
    ref_problems += relocs.check_ownership(reached, data_splits())
    ref_problems += relocs.check_consistency(ref_entries, read, relocs.load_aliases(os.path.join(ROOT, 'config', 'symbol_aliases.txt')), known)
    print('LTCG relocation targets: %d references in %d LTCG-only functions checked, %d data symbols they reach; %s' % (
        len(ref_entries), nref, len(reached), 'all consistent' if not ref_problems else '%d PROBLEM(S):' % len(ref_problems)))
    for pr in ref_problems:
        print('  ' + pr)
    if not keep:
        shutil.rmtree(work, ignore_errors=True)
    sys.exit(0 if totals['tracked_ok'] == totals['tracked'] and not ref_problems else 1)


if __name__ == '__main__':
    main()
