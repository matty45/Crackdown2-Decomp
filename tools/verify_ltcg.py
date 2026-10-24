"""Check the functions in config/matched_functions.json under link-time code generation (LTCG).

usage: py -I tools/verify_ltcg.py <path to extracted default.exe> [source-substring] [--keep DIR] [--self-test]

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

Comparison masks address immediates only: halves derived from a `lis`, loads/stores through such registers, and
calls that leave the function. Everything else (offsets, registers, opcodes, intra-function branches) must match.
The build and comparison functions (build_ltcg, compare_ltcg, direct_constants) are also used by agent harnesses.
"""
import bisect, json, math, os, re, shutil, struct, subprocess, sys, tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import coff
import relocs
from verify_src import pe_reader, FLAGS, XDK, BIN, ROOT, EXPECTED_ENTRY, check_toolchain

POOL_START, POOL_SIZE = 0x820F8C80, 0x8000  # CD2's LTCG constant pool (__pool@_0)
RDATA = (0x82000400, 0x8216F658)
LOADS = {32, 33, 34, 35, 40, 41, 42, 43, 46, 48, 49, 50, 51, 58}
STORES = {36, 37, 38, 39, 44, 45, 47, 52, 53, 54, 55, 62}
NO_GPR_WRITE = STORES | {16, 18, 19, 10, 11}  # stores, branches, compares
FLOAT_LOADS = {48: 4, 50: 8}  # lfs, lfd
LOGICAL_RA_DEST = {20, 21, 23, 24, 25, 26, 27, 28, 29, 30}  # rotates and logical immediates write rA, not rS


def masked(ws, start):
    """Mask address immediates: lis halves, addi/loads/stores based on lis-derived registers, calls out of the function."""
    out, hi = [], set()
    end = start + 4 * len(ws)
    for i, w in enumerate(ws):
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


def map_funcs(path):
    fs = []
    for l in open(path):
        m = re.match(r'\s*[0-9a-f]{4}:[0-9a-f]+\s+(\S+)\s+([0-9a-f]{8})\s+f\s', l)
        if m:
            fs.append((int(m.group(2), 16), m.group(1)))
    return sorted(fs)


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


def map_symbols(path):
    """Every symbol of the LTCG link map (publics and statics): sorted [(address, name)]."""
    out = []
    for l in open(path):
        m = re.match(r'\s*[0-9a-f]{4}:[0-9a-f]+\s+(\S+)\s+([0-9a-f]{8})\s', l)
        if m:
            out.append((int(m.group(2), 16), m.group(1)))
    return sorted(out)


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


def cstring(read, addr):
    """The C string at addr in read's image (with its NUL; at most 64 bytes), or None."""
    try:
        b = read(addr, 64)
    except ValueError:
        return None
    return b.split(b'\0', 1)[0] + b'\0' if b'\0' in b else None


def check_references(ours, cd2, symbols, our_read, cd2_read, src, fname, cd2_bytes=None, cd2_string=None):
    """Pair our references with CD2's (same positions, as the function is exact under LTCG). Returns (consistency
    entries [(file, function, symbol, CD2 address, kind, offset, None)], problems). Calls must reach a named symbol;
    float constants and strings are compared by content (the model's own constant symbols, g_vl_c* and the pool,
    only by content). cd2_bytes(address, n) and cd2_string(address) default to reading CD2 (the facts mode passes
    recorded values instead)."""
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
                entries.append((src, fname, name, caddr, kind, 4 * i, None))
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
        entries.append((src, fname, name, (caddr - off) & 0xFFFFFFFF, kind, 4 * i, None))
    return entries, problems


def build_ltcg(srcpath, plain_obj, consts, d, env, extra_flags=()):
    """Build an LTCG image of one source file with the generated program model (escapes, constant registrations,
    pool seed) in directory d. plain_obj is the file's plain-compiled object (for its data symbols).
    Returns (read function for the image, sorted [(address, symbol)], number of escaped globals)."""
    flags = FLAGS + ['/I' + os.path.dirname(os.path.abspath(srcpath))] + list(extra_flags)

    def cl(extra, out, path):
        r = subprocess.run([os.path.join(BIN, 'cl.exe')] + flags + extra + ['/Fo' + out, path],
                           env=env, capture_output=True, text=True)
        if r.returncode:
            raise RuntimeError('%s: compile error\n%s' % (path, r.stdout + r.stderr))
    os.makedirs(d, exist_ok=True)
    globs = data_symbols(plain_obj) + function_symbols(plain_obj)
    tag = os.path.splitext(os.path.basename(srcpath))[0]
    copy = os.path.join(d, tag + '_ltcg.cpp')
    text = open(srcpath).read()
    text += ('\n\n// ---- appended by tools/verify_ltcg.py: take the address of every global and every static/free\n'
             '// function this file refers to or defines\n'
             'void *g_verify_ltcg_escapes[] = {\n%s\n    0\n};\n' % ''.join('    (void *)&%s,\n' % g for g in globs))
    open(copy, 'w').write(text)
    cl(['/GL', '/Dprivate=public', '/Dprotected=public'], os.path.join(d, 'src.obj'), copy)
    lines = ['// generated by tools/verify_ltcg.py for %s' % srcpath,
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
    envsrc = os.path.join(d, 'env.cpp')
    open(envsrc, 'w').write('\n'.join(lines) + '\n')
    cl(['/GL'], os.path.join(d, 'env.obj'), envsrc)
    for stale in ('t.pe', 't.map'):
        if os.path.exists(os.path.join(d, stale)):
            os.remove(os.path.join(d, stale))
    # the file's external symbols get stubs; the linker reports which of them the LTCG build defines itself (drop
    # those) and what else it needs (add those), so link at most three times
    names = undefined_symbols(plain_obj)
    for attempt in range(3):
        for stale in ('t.pe', 't.map'):
            if os.path.exists(os.path.join(d, stale)):
                os.remove(os.path.join(d, stale))
        stubs = write_stubs(names, os.path.join(d, 'stubs.obj'))
        r = subprocess.run([os.path.join(BIN, 'link.exe'), '/nologo', '/LTCG', '/NODEFAULTLIB', '/FORCE:UNRESOLVED',
                            '/ENTRY:VerifyLtcgStub', '/OPT:NOREF', '/OPT:NOICF', '/MAP:' + os.path.join(d, 't.map'),
                            '/OUT:' + os.path.join(d, 't.exe'), os.path.join(d, 'env.obj'), os.path.join(d, 'src.obj')]
                           + ([stubs] if stubs else []), env=env, capture_output=True, text=True)
        dup = set(re.findall(r'stubs\.obj : error LNK2005: .*?\((\S+)\) already defined', r.stdout))
        unres = set(re.findall(r'error LNK20(?:01|19): unresolved external symbol .*?\((\S+)\)', r.stdout))
        if not dup and not unres:
            break
        names = (names - dup) | unres
    image = os.path.join(d, 't.pe')
    if not os.path.exists(image):
        raise RuntimeError('LTCG link failed\n%s' % r.stdout[-2000:])
    return image_reader(image), map_funcs(os.path.join(d, 't.map')), len(globs)


def compare_ltcg(ltcg_read, fs, symbol, target, va):
    """Compare the LTCG image's function matching `symbol` with target bytes at CD2 address va.
    Returns (exact, good_words, target_words), or None if the symbol is not in the image."""
    lt = [a for a, n in fs if symbol in n]
    if not lt:
        return None
    a = lt[0]
    nxt = [x for x, _ in fs if x > a]
    lw = words(ltcg_read(a, (nxt[0] if nxt else a + len(target) + 64) - a))
    while lw and lw[-1] == 0:
        lw.pop()
    tw = words(target)
    if len(lw) > len(tw) and ends_function(tw):
        # the map gives no end for the last function of a section; words after a target that cannot fall through
        # (and has no branch past its end) are not part of it
        lw = lw[:len(tw)]
    mt, ml = masked(tw, va), masked(lw, a)
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


def check_file(src, funcs, read, env, d, srcpath=None, out=print):
    """Build one source file under LTCG (srcpath: a modified copy, for the self-test) and compare its functions.
    Returns dict(results [(entry, plain_exact, ltcg_exact)], entries, problems, known, nref) or None on a build error;
    entries/problems: the reference check of the functions exact only under LTCG."""
    os.makedirs(d, exist_ok=True)
    srcpath = srcpath or os.path.join(ROOT, src)
    plain = os.path.join(d, 'plain.obj')
    r = subprocess.run([os.path.join(BIN, 'cl.exe')] + FLAGS + ['/I' + os.path.dirname(os.path.join(ROOT, src)),
                        '/Fo' + plain, srcpath], env=env, capture_output=True, text=True)
    if r.returncode:
        out('%s: COMPILE ERROR\n%s' % (src, r.stdout + r.stderr))
        return None
    consts = direct_constants(read, funcs)
    try:
        ltcg_read, fs, nglobs = build_ltcg(srcpath, plain, consts, d, env,
                                           extra_flags=['/I' + os.path.dirname(os.path.join(ROOT, src))])
    except RuntimeError as e:
        out('%s: %s' % (src, e))
        return None
    compiled = list(coff.functions(plain))
    syms = map_symbols(os.path.join(d, 't.map'))
    res = dict(results=[], entries=[], problems=[], known={}, nref=0)
    for f in funcs:
        hit = [n for n, _, _ in compiled if f['symbol'] in n]
        if hit and f.get('matching', True):
            res['known'][hit[0]] = int(f['address'], 16)
    out('%s  (%d globals escaped, %d constants registered)' % (src, nglobs, len(consts)))
    for f in funcs:
        va, size = int(f['address'], 16), f['size']
        target = read(va, size)
        found = [(n, c, rel) for n, c, rel in compiled if f['symbol'] in n]
        plain_exact = bool(found) and coff.compare(found[0][1], target, found[0][2])[0]
        cmp = compare_ltcg(ltcg_read, fs, f['symbol'], target, va)
        if cmp is None:
            lt_exact, status = False, 'not found in LTCG image'
        else:
            lt_exact, good, n = cmp
            status = 'EXACT' if lt_exact else '%d/%d words' % (good, n)
        if lt_exact and f.get('ltcg') and f.get('matching', True):
            # exact only under LTCG: the plain gate cannot check its references, so check them here
            a = [x for x, nm in fs if f['symbol'] in nm][0]
            lw = words(ltcg_read(a, len(target)))
            e, pr = check_references(references(lw, a), references(words(target), va), syms, ltcg_read, read,
                                     src, f['symbol'])
            res['entries'] += e
            res['problems'] += pr
            res['nref'] += 1
        res['results'].append((f, plain_exact, lt_exact))
        out('  %08X %4d bytes  plain %-5s  ltcg %-14s %s%s' % (va, size, 'EXACT' if plain_exact else 'diff', status,
            found[0][0][:70] if found else f['symbol'], '' if f.get('matching', True) else '   [work in progress]'))
    return res


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
    work = tempfile.mkdtemp(prefix='cd2ltcg_selftest_')
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
    shutil.rmtree(work, ignore_errors=True)
    return ok and clean


def main():
    args = sys.argv[1:]
    keep = None
    if '--keep' in args:
        i = args.index('--keep')
        keep = args[i + 1]
        del args[i:i + 2]
    test = '--self-test' in args
    args = [x for x in args if x != '--self-test']
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
    if test:
        sys.exit(0 if self_test(read, env) else 1)
    manifest = json.load(open(os.path.join(ROOT, 'config', 'matched_functions.json')))
    work = keep or tempfile.mkdtemp(prefix='cd2ltcg_')
    totals = dict(n=0, plain=0, ltcg=0, tracked=0, tracked_ok=0)
    ref_entries, ref_problems, known, nref = [], [], {}, 0
    for src, funcs in manifest['files'].items():
        if only not in src:
            continue
        res = check_file(src, funcs, read, env, os.path.join(work, os.path.splitext(os.path.basename(src))[0]))
        if res is None:
            continue
        ref_entries += res['entries']
        ref_problems += res['problems']
        known.update(res['known'])
        nref += res['nref']
        for f, plain_exact, lt_exact in res['results']:
            tracked = f.get('matching', True)
            totals['n'] += 1
            totals['plain'] += plain_exact
            totals['ltcg'] += lt_exact
            totals['tracked'] += bool(tracked)
            totals['tracked_ok'] += bool(tracked) and lt_exact
    print('\n%(n)d functions: %(plain)d exact in a plain build, %(ltcg)d exact under LTCG; '
          '%(tracked_ok)d of %(tracked)d matched functions exact under LTCG' % totals)
    ref_problems += relocs.check_consistency(ref_entries, read, relocs.load_aliases(os.path.join(ROOT, 'config', 'symbol_aliases.txt')), known)
    print('LTCG relocation targets: %d references in %d LTCG-only functions checked; %s' % (
        len(ref_entries), nref, 'all consistent' if not ref_problems else '%d PROBLEM(S):' % len(ref_problems)))
    for pr in ref_problems:
        print('  ' + pr)
    if not keep:
        shutil.rmtree(work, ignore_errors=True)
    sys.exit(0 if totals['tracked_ok'] == totals['tracked'] and not ref_problems else 1)


if __name__ == '__main__':
    main()
