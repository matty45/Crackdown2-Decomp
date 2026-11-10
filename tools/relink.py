"""Relink Crackdown 2 from jeff's split objects and compare the result with the original, word for word.

usage: py -I tools/relink.py <path to default_patched.xex> [workdir] [--resplit]
       py -I tools/relink.py <path to default_patched.xex> [workdir] --substitute <file or directory/> ... [--self-test]

The ultimate check: when the relinked image is byte-identical to the original, the splits, object order, relocations
and data layout are all right at once. Everything happens in <workdir> (default build/relink, ignored by git):
  1. verify the XEX is the title-update build (SHA1), copy it in, extract the reference exe with jeff
  2. jeff xex split (jeff built from source by tools/build_tools.ps1); --resplit forces a fresh split
  3. link with the XDK linker at the original base
  4. compare the linked memory image with the original's and classify .text differences

What is compared: the memory image from the first section up to the XEX resources. Beyond that address the original
image holds the resources the XEX packager placed there (localized text, listed in the XEX resource table); the
linker's .edata/.idata/.XBLD/.reloc that the section table still describes were consumed by the packager and are not
in the image, so their objects are not linked. Two kinds of words are not linker output and are checked separately:
  imports        the packager replaced each IAT entry and import thunk with an import record (listed in the XEX
                 import header); there the relinked image must hold exactly what the linker writes
  link metadata  the debug directory's time stamp and the CodeView record's GUID and age change with every link
Exit status 0 only when every other word is identical and both kinds check out. Also reported: whether jeff found as
many absolute relocations as the original link had (the size of its base relocation table).
Nothing from the game leaves <workdir>.

--substitute: the same round trip with OUR objects in place of the split's units for the given source files (or every
file under a directory ending in /), in <workdir>/substitute. Each must be a plain (non-LTCG) object, such as the
middleware's: its code and its data must land where CD2 has them, so an identical image proves the whole object (code,
data, its layout and every reference into and out of it), not only its matched functions. How: the unit takes the
object's text range and its contiguous .rdata contribution, located through the data its functions reference, the
data that data points at (a string only a table reaches), a string table through the strings it points at, and
read-only data nothing reaches through its bytes (lapi.c's lua_ident); jeff's symbols name every address the object
defines or uses; the pieces of each section link in address order. A section CD2 holds elsewhere (a pooled string, a
static it placed outside the unit, a function the order list moved) becomes a reference to the split's copy, and every
name the object reaches outside its units goes by an alias of its address (cd2_<address>), as CD2 has several copies
of some literals and of some library functions (two sprintf). Statics are exported, under a name of their own when
several units share one. Functions CD2 does not have are dropped (/OPT:REF); every function it has stays (/INCLUDE).
cd2.py verify runs it on src/middleware/ (zlib, libjpeg, Lua); --self-test changes one word of our code, then of our
data, and requires exactly that word to differ.
"""
import collections, hashlib, os, re, shutil, struct, subprocess, sys

TOOLS = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, TOOLS)
from verify_src import BIN, ROOT, check_toolchain

XEX_SHA1 = 'EC7B163617CD725F50B0CCA665AAF943F9BC6D8A'
# jeff's .pdata is a whole-binary function table, which the linker rejects (LNK1223); linked as plain data under a
# neutral name, its relocations are still checked
RENAMED = {'.pdata': '.pdatX'}
# sections the XEX packager consumed (exports, imports, build info, base relocations); the image holds resources there
PACKAGER_SECTIONS = {'.edata', '.idata', '.XBLD', '.reloc'}
# jeff's section list for CD2 (as jeff itself writes it into splits.txt)
JEFF_SECTIONS = [('.rdata', 'rodata'), ('.pdata', 'rodata'), ('.text', 'code'), ('PSFD00', 'code'), ('.data', 'data'),
                 ('.tls', 'data'), ('.XBMOVIE', 'data'), ('.edata', 'rodata'), ('.idata', 'data'), ('.XBLD', 'data'),
                 ('.reloc', 'data')]


def debug_layout(path):
    """(debug directory address, size, CodeView record address, size, .rdata start, .rdata end) of the original image.
    The linker always writes its own debug directory first in .rdata and its CodeView record in .rdata$debug; CD2's
    original link merged the data before its debug directory into .rdata (a section merged with /MERGE goes first),
    and the data after its CodeView record sorts after $debug."""
    d = open(path, 'rb').read()
    pe = struct.unpack_from('<I', d, 0x3C)[0]
    opt = pe + 24
    base = struct.unpack_from('<I', d, opt + 28)[0]
    dva, dsz = struct.unpack_from('<II', d, opt + 96 + 8 * 6)
    secs = sections(path)
    rva, rvs, rdata = secs['.rdata']
    entry = rdata[base + dva - rva: base + dva - rva + 28]
    cv_size, cv_rva = struct.unpack_from('<I', entry, 16)[0], struct.unpack_from('<I', entry, 20)[0]
    return base + dva, dsz, base + cv_rva, cv_size, rva, rva + rvs


def write_jeff_splits(path, lay):
    dbg, dsz, cv, cvsz, r0, r1 = lay
    dbg_end, cv_end = (dbg + dsz + 7) & ~7, (cv + cvsz + 7) & ~7
    lines = ['Sections:'] + ['\t%-11s type:%s align:65536' % s for s in JEFF_SECTIONS] + ['']
    for unit, (a, b) in (('relink_rdata_merged.cpp', (r0, dbg)), ('relink_rdata_debugdir.cpp', (dbg, dbg_end)),
                         ('relink_rdata_codeview.cpp', (cv, cv_end)), ('relink_rdata_tail.cpp', (cv_end, r1))):
        lines += ['%s:' % unit, '\t.rdata      start:0x%08X end:0x%08X' % (a, b), '']
    open(path, 'w').write('\n'.join(lines))


def write_jeff_symbols(path, lay, tls):
    """Explicit symbols at the cut points, so that jeff's automatic symbols do not span them."""
    dbg, dsz, cv, cvsz, r0, r1 = lay
    rows = [('cd2_debug_directory', dbg, ((dbg + dsz + 7) & ~7) - dbg), ('cd2_codeview_record', cv, ((cv + cvsz + 7) & ~7) - cv)]
    if tls and r0 <= tls[0] < r1:
        rows.append(('cd2_tls_directory', tls[0], tls[1]))
    open(path, 'w').write(''.join('%s = .rdata:0x%08X; // type:object size:0x%X\n' % r for r in rows))


def tls_directory(path):
    d = open(path, 'rb').read()
    pe = struct.unpack_from('<I', d, 0x3C)[0]
    opt = pe + 24
    base = struct.unpack_from('<I', d, opt + 28)[0]
    va, sz = struct.unpack_from('<II', d, opt + 96 + 8 * 9)
    return (base + va, sz) if va else None


def xex_resource_start(path):
    """Lowest address in the XEX resource table (optional header 0x2FF)."""
    d = open(path, 'rb').read()
    for i in range(struct.unpack_from('>I', d, 20)[0]):
        key, val = struct.unpack_from('>II', d, 24 + 8 * i)
        if key == 0x2FF:
            n = (struct.unpack_from('>I', d, val)[0] - 4) // 16
            return min(struct.unpack_from('>I', d, val + 4 + 16 * j + 8)[0] for j in range(n))
    return None


def object_sections(obj_path):
    d = open(obj_path, 'rb').read(4096)
    nsec, opt = struct.unpack_from('<H', d, 2)[0], struct.unpack_from('<H', d, 16)[0]
    return {d[20 + opt + 40 * i: 28 + opt + 40 * i].rstrip(b'\0').decode('latin-1') for i in range(nsec)}


def xex_import_records(path):
    """[(record address, library index)] from the XEX import libraries header (optional header 0x103FF)."""
    d = open(path, 'rb').read()
    for i in range(struct.unpack_from('>I', d, 20)[0]):
        key, val = struct.unpack_from('>II', d, 24 + 8 * i)
        if key == 0x103FF:
            h = d[val + 4: val + struct.unpack_from('>I', d, val)[0]]
            strsize, nlib = struct.unpack_from('>II', h, 0)
            pos, out = 8 + strsize, []
            for lib in range(nlib):
                pos += 0x24  # size, digest, id, version, minimum version
                count = struct.unpack_from('>H', h, pos + 2)[0]
                pos += 4
                out += [(struct.unpack_from('>I', h, pos + 4 * k)[0], lib) for k in range(count)]
                pos += 4 * count
            return out
    return []


def linker_imports(img, lo, records):
    """{address: 4 bytes} that the linker wrote where the packager left import records. A record word is
    type << 24 | ordinal: type 0 marks an IAT entry, which the linker wrote as a PE import by ordinal (0x80000000 |
    ordinal, little-endian); type 1 marks the thunk of the library's preceding entry, whose first two instructions
    load that entry (lis r11 / lwz r11)."""
    out, entry = {}, {}
    for rec, lib in records:
        w = struct.unpack_from('>I', img, rec - lo)[0]
        kind, ordinal = w >> 24, w & 0xFFFF
        if kind == 0:
            out[rec] = struct.pack('<I', 0x80000000 | ordinal)
            entry[lib] = (rec, ordinal)
        elif kind == 1 and lib in entry and entry[lib][1] == ordinal:
            iat = entry[lib][0]
            out[rec] = struct.pack('>I', 0x3D600000 | ((iat + 0x8000) >> 16 & 0xFFFF))
            out[rec + 4] = struct.pack('>I', 0x816B0000 | (iat & 0xFFFF))
        else:
            sys.exit('import record at %08X (%08X) is neither an IAT entry nor the thunk of the preceding one' % (rec, w))
    return out


def rename_section(obj_path, old, new, align=None):
    """Rename a COFF section (8-byte names only); optionally set its alignment (IMAGE_SCN_ALIGN_* value)."""
    d = bytearray(open(obj_path, 'rb').read())
    nsec, opt = struct.unpack_from('<H', d, 2)[0], struct.unpack_from('<H', d, 16)[0]
    n = 0
    for i in range(nsec):
        o = 20 + opt + 40 * i
        if d[o:o + 8].rstrip(b'\0') == old.encode():
            d[o:o + 8] = new.encode().ljust(8, b'\0')
            if align is not None:
                ch = struct.unpack_from('<I', d, o + 36)[0]
                struct.pack_into('<I', d, o + 36, (ch & ~0x00F00000) | align)
            n += 1
    open(obj_path, 'wb').write(bytes(d))
    return n


JEFF = os.path.join(ROOT, 'build', 'tools', 'bin', 'jeff.exe')
# not /FIXED: the original link generated base relocations (its .reloc), whose size is checked below
LINK_FLAGS = ['/nologo', '/BASE:0x82000000', '/NODEFAULTLIB', '/ENTRY:mainCRTStartup', '/FORCE:MULTIPLE',
              '/FORCE:UNRESOLVED', '/XEX:NO']


def sections(path):
    d = open(path, 'rb').read()
    pe = struct.unpack_from('<I', d, 0x3C)[0]
    nsec = struct.unpack_from('<H', d, pe + 6)[0]
    opt = struct.unpack_from('<H', d, pe + 20)[0]
    base = struct.unpack_from('<I', d, pe + 24 + 28)[0]
    out = collections.OrderedDict()
    for i in range(nsec):
        o = pe + 24 + opt + 40 * i
        name = d[o:o + 8].rstrip(b'\0').decode('latin-1')
        vs, va, rs, ra = struct.unpack_from('<IIII', d, o + 8)
        out[name] = (base + va, vs, d[ra:ra + min(vs, rs)] if ra else b'')
    return out


def memory_image(secs, lo, hi):
    """The bytes a loader maps at [lo, hi): each section's data at its address, zeros elsewhere."""
    img = bytearray(hi - lo)
    for va, vs, data in secs.values():
        if va < hi and va + len(data) > lo:
            s, e = max(va, lo), min(va + len(data), hi)
            img[s - lo: e - lo] = data[s - va: e - va]
    return img


def word_diff(a, b, start, end):
    """(words, differing words) of two images over [start, end)."""
    n = (end - start) // 4
    diff = sum(1 for i in range(start, start + 4 * n, 4) if a[i:i + 4] != b[i:i + 4])
    return n, diff


def classify_text(va, a, b, sec_starts):
    """Classify differing .text words of a (relinked) against b (original)."""
    cat = collections.Counter()
    for i in range(0, min(len(a), len(b)) - 3, 4):
        p, q = struct.unpack_from('>I', a, i)[0], struct.unpack_from('>I', b, i)[0]
        if p == q:
            continue
        op = p >> 26
        if op == 18 and q >> 26 == 18 and (p & 3) == (q & 3):
            def tgt(w):
                li = w & 0x03FFFFFC
                return li - 0x04000000 if li & 0x02000000 else li
            delta = (tgt(p) - tgt(q)) & 0xFFFFFFFF
            off = va + i - max(s for s in sec_starts if s <= va + i)
            cat['branch: target off by the branch\'s own section offset (REL24 encoding)' if delta == off else
                'branch: other target difference'] += 1
        elif op == q >> 26 and (p >> 16) == (q >> 16) and ((p & 0xFFFF) - (q & 0xFFFF)) & 0xFFFF == 0x20:
            cat['address low half +0x20 (shifted .rdata)'] += 1
        elif op == q >> 26 and (p >> 16) == (q >> 16):
            cat['same instruction, other immediate'] += 1
        else:
            cat['other'] += 1
    return cat


# ---------------------------------------------------------------------------------------------------- --substitute

REMOVE = 0x800  # IMAGE_SCN_LNK_REMOVE
PDATA = (0x8216F800, 0x53390)  # CD2's function table (.pdata): address, size
RDATA = (0x82000400, 0x8216F658)


def locate_sections(src, read, manifest, work):
    """Our plain object of src, and where CD2 holds its sections: {section index: CD2 address} from the manifest's
    functions and the data their resolved references reach, and {name: CD2 address} of every name they use. A table of
    strings nothing located references (zutil's z_errmsg) is a candidate list, settled by settle_tables."""
    import relocs
    from verify_src import flags_for, symbol_matches, XDK
    env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'],
               INCLUDE=os.path.join(XDK, 'include', 'xbox') + ';' + os.path.join(ROOT, 'include'))
    obj = os.path.join(work, 'ours', os.path.splitext(src)[0].replace('/', '_') + '.obj')
    os.makedirs(os.path.dirname(obj), exist_ok=True)
    r = subprocess.run([os.path.join(BIN, 'cl.exe')] + flags_for(src) + ['/Fo' + obj, os.path.join(ROOT, src)], env=env,
                       capture_output=True, text=True)
    if r.returncode:
        sys.exit('%s: compile error\n%s' % (src, r.stdout + r.stderr))
    robj = relocs.Obj(obj)
    funcs = robj.functions()
    base, names, tables, matched = {}, {}, [], []
    for f in manifest['files'][src]:
        name = next((n for n in funcs if symbol_matches(f['symbol'], n)), None)
        if name is None:
            sys.exit('%s: %s is not in the object' % (src, f['symbol']))
        va = int(f['address'], 16)
        sec, start, size = funcs[name]
        base[sec] = va - start
        names[name] = va
        matched.append(name)
        res, _ = relocs.resolve(robj, name, read(va, f['size']), va)
        for sym, addr, kind, off in res:
            names.setdefault(sym, addr)
            hits = [s for s in robj.symbols.values() if s['name'] == sym and s['sec'] > 0]
            if kind == 'data' and len(hits) == 1 and not robj.sections[hits[0]['sec'] - 1]['ch'] & relocs.CODE:
                base.setdefault(hits[0]['sec'], addr - hits[0]['value'])
    image = read(RDATA[0], RDATA[1] - RDATA[0])
    for i, s in enumerate(robj.sections, 1):
        if i in base or s['ch'] & (relocs.CODE | relocs.COMDAT) or s['name'] != '.rdata':
            continue
        if not s['relocs']:
            # read-only data nothing located reaches (lapi.c's lua_ident): where CD2 holds the same bytes
            found, at = [], image.find(s['data'])
            while at >= 0 and len(s['data']) >= 8:
                if at % 4 == 0:
                    found.append(RDATA[0] + at)
                at = image.find(s['data'], at + 1)
            tables.append((i, [], found))
            continue
        targets = [(off, robj.symbols[si]['name']) for off, si, t in s['relocs']]
        texts = [relocs.string_bytes(robj, n) if relocs.is_string(n) else None for _, n in targets]
        if not all(texts):
            continue
        found = []
        for c in range(0, len(image) - s['size'], 4):
            for (off, _), text in zip(targets, texts):
                w = struct.unpack_from('>I', image, c + off)[0]
                if not RDATA[0] <= w < RDATA[1] or image[w - RDATA[0]: w - RDATA[0] + len(text)] != text:
                    break
            else:
                found.append(RDATA[0] + c)
        tables.append((i, targets, found))
    return dict(obj=obj, robj=robj, base=base, names=names, tables=tables, matched=matched)


def settle_tables(plan, read):
    """Place each table locate_sections could not: at its one candidate, or (another copy of the library elsewhere in
    CD2) at the candidate nearest the other located data of the objects substituted together; its pointers place the
    strings it holds."""
    import relocs
    located = [b for p in plan.values() for i, b in p['base'].items()
               if not p['robj'].sections[i - 1]['ch'] & relocs.CODE and b < PDATA[0]]
    for p in plan.values():
        for i, targets, found in p['tables']:
            if not found or not located:
                continue
            at = min(found, key=lambda c: min(abs(c - x) for x in located))
            p['base'][i] = at
            for off, name in targets:
                hit = [x for x in p['robj'].symbols.values() if x['name'] == name and x['sec'] > 0]
                w = struct.unpack('>I', read(at + off, 4))[0]
                p['base'].setdefault(hit[0]['sec'], w - hit[0]['value'])
                p['names'].setdefault(name, w)


def follow_pointers(plan, read):
    """Place what located data points at, from the addresses CD2's copy holds: a string only a table reaches
    (lbaselib's function names), which is the unit's own or one the linker pooled with another object's. jeff names
    such a string itself, as a local symbol; unplaced, the object's copy would link beside it."""
    import relocs
    for p in plan.values():
        robj, base = p['robj'], p['base']
        todo = [i for i in base if not robj.sections[i - 1]['ch'] & relocs.CODE]
        while todo:
            i = todo.pop()
            s = robj.sections[i - 1]
            for off, si, t in s['relocs']:
                sym = robj.symbols[si]
                at = struct.unpack('>I', read(base[i] + off, 4))[0] - struct.unpack_from('>I', s['data'], off)[0]
                if not sym['name'].startswith(('.', '$')):
                    p['names'].setdefault(sym['name'], at)
                if sym['sec'] > 0 and sym['sec'] not in base and not robj.sections[sym['sec'] - 1]['ch'] & relocs.CODE:
                    base[sym['sec']] = at - sym['value']
                    todo.append(sym['sec'])


def unit_of(src, p, splits):
    """(text range, contiguous .rdata contribution or None, kept section indices): the object's text range from
    config/splits.txt, and its non-COMDAT .rdata with the located sections that adjoin it on either side in their order
    in the object (the linker lays an object's sections out in that order)"""
    import relocs
    robj, base = p['robj'], p['base']
    lo, hi = splits[src]['text']
    data = sorted((b, b + robj.sections[i - 1]['size'], i) for i, b in base.items()
                  if not robj.sections[i - 1]['ch'] & relocs.CODE and robj.sections[i - 1]['name'] == '.rdata')
    run = []
    anchor = next((k for k, (b, e, i) in enumerate(data) if not robj.sections[i - 1]['ch'] & relocs.COMDAT), None)
    if anchor is not None:
        a = z = anchor
        while a > 0 and data[a - 1][2] < data[a][2] and ((data[a - 1][1] + 3) & ~3) >= data[a][0]:
            a -= 1
        while z + 1 < len(data) and data[z + 1][2] > data[z][2] and data[z + 1][0] <= ((data[z][1] + 3) & ~3):
            z += 1
        run = data[a:z + 1]
    keep = {i for i, b in base.items() if lo <= b < hi} | {i for _, _, i in run}
    return (lo, hi), ((run[0][0], (run[-1][1] + 3) & ~3) if run else None), keep


def aliases(p, keep, defined):
    """{symbol index: name} for what the object defines in a section CD2 holds outside the unit: the name the unit
    defining that address gives it (defined: {address: name}), else cd2_<address>. Not the symbol's own name: CD2 has
    several copies of some literals ("" at 82001050 and 8216E274), and a static's name is not unique."""
    robj, base = p['robj'], p['base']
    return {k: defined.get(base[s['sec']] + s['value'], 'cd2_%08X' % (base[s['sec']] + s['value']))
            for k, s in robj.symbols.items() if s['sec'] in base and s['sec'] not in keep and s['cls'] in (2, 3)}


def rewrite_object(p, keep, rows, alias, dst):
    """Our object as the unit links it: its .pdata linked as data under the split's name for CD2's table (RENAMED);
    statics of the kept sections made external (the split's code reaches into the unit by their names, symbols.txt);
    a section CD2 holds elsewhere (a string the linker pooled with another object's, a function the order list moved,
    a static CD2 placed outside the unit, a name CD2 holds outside the unit) dropped, and what it defined made
    references to the split's copy, under its alias (aliases) or its own name. A dropped definition keeps a name of its
    own, as the linker requires of every COMDAT section; a section symbol keeps its name. A name the object only
    references takes its alias too (alias holds both kinds, by symbol index)."""
    robj = p['robj']
    d = bytearray(open(p['obj'], 'rb').read())
    nsec, opt = struct.unpack_from('<H', d, 2)[0], struct.unpack_from('<H', d, 16)[0]
    away = {i for i in p['base'] if i not in keep}
    away |= {s['sec'] for s in robj.symbols.values()
             if s['sec'] > 0 and s['cls'] == 2 and s['sec'] not in keep and s['name'] in rows}
    symptr, nsym = struct.unpack_from('<II', d, 8)
    strtab = bytearray(d[symptr + 18 * nsym:])

    def put_name(rec, name):
        raw = name.encode()
        if len(raw) <= 8:
            rec[0:8] = raw.ljust(8, b'\0')
        else:
            rec[0:8] = struct.pack('<II', 0, len(strtab))
            strtab.extend(raw + b'\0')
    new_syms, remap, k = [], {}, 0
    while k < nsym:
        so = symptr + 18 * k
        sec, cls, naux = struct.unpack_from('<h', d, so + 12)[0], d[so + 16], d[so + 17]
        name = robj.symbols[k]['name'] if k in robj.symbols else ''
        if sec in keep and cls == 3 and not name.startswith(('.', '$')):
            d[so + 16] = 2
            if k in alias:
                rec = bytearray(d[so:so + 18])
                put_name(rec, alias[k])
                d[so:so + 18] = rec
        if sec == 0 and cls == 2 and k in alias:
            rec = bytearray(d[so:so + 18])
            put_name(rec, alias[k])
            d[so:so + 18] = rec
            struct.pack_into('<I', d, so + 8, 0)  # a common (an uninitialized C global) becomes a plain reference
        if sec in away and (cls == 2 or k in alias):
            ref = bytearray(d[so:so + 18])
            struct.pack_into('<IhHBB', ref, 8, 0, 0, struct.unpack_from('<H', d, so + 14)[0], 2, 0)
            if k in alias:
                put_name(ref, alias[k])
            remap[k] = nsym + len(new_syms)
            new_syms.append(bytes(ref))
            if not name.startswith('.'):
                d[so:so + 8] = ('rm%06d' % k).encode()
                d[so + 16] = 3
        k += 1 + naux
    for i in range(1, nsec + 1):
        o = 20 + opt + 40 * (i - 1)
        if d[o:o + 8].rstrip(b'\0') == b'.pdata':
            d[o:o + 8] = RENAMED['.pdata'].encode().ljust(8, b'\0')
        if i in away:
            struct.pack_into('<I', d, o + 36, struct.unpack_from('<I', d, o + 36)[0] | REMOVE)
            continue
        preloc, nrel = struct.unpack_from('<I', d, o + 24)[0], struct.unpack_from('<H', d, o + 32)[0]
        for r in range(nrel):
            si = struct.unpack_from('<I', d, preloc + 10 * r + 4)[0]
            if si in remap:
                struct.pack_into('<I', d, preloc + 10 * r + 4, remap[si])
    struct.pack_into('<I', strtab, 0, len(strtab))
    out = bytes(d[:symptr + 18 * nsym]) + b''.join(new_syms) + bytes(strtab)
    open(dst, 'wb').write(out[:12] + struct.pack('<I', nsym + len(new_syms)) + out[16:])


def pdata_start(read, lo, hi):
    """CD2's address of the first function-table record of a function in [lo, hi), or None"""
    table = read(PDATA[0], PDATA[1])
    for k in range(len(table) // 8):
        if lo <= struct.unpack_from('>I', table, 8 * k)[0] < hi:
            return PDATA[0] + 8 * k
    return None


def link_order(objs, starts):
    """objs in an order that lays out each section's pieces by address (starts: {object: {section: address}}), the
    split's own order otherwise: the linker places a section's contributions in object order"""
    after, indeg = collections.defaultdict(set), collections.Counter()
    for sec in {s for d in starts.values() for s in d}:
        chain = sorted((d[sec], o) for o, d in starts.items() if sec in d)
        for (_, a), (_, b) in zip(chain, chain[1:]):
            if b not in after[a]:
                after[a].add(b)
                indeg[b] += 1
    ready, ordered = [o for o in objs if not indeg[o]], []
    while ready:
        ready.sort(key=lambda o: (min(starts.get(o, {'': 0}).values()), objs.index(o)))
        o = ready.pop(0)
        ordered.append(o)
        for n in after[o]:
            indeg[n] -= 1
            if not indeg[n]:
                ready.append(n)
    if len(ordered) != len(objs):
        sys.exit('no link order lays out every section\'s pieces by address')
    return ordered


def substitute_units(work, files, lay, orig_exe, local_xex, self_test=False):
    """The round trip with our own objects in place of the split's units for files (paths or directories under
    src/): each a plain (non-LTCG) object, whose code and data must land where CD2 has them. Returns whether the
    relinked image is identical (self_test: whether a word changed in our code, then in our data, is caught)."""
    import json
    import relocs
    from verify_src import pe_reader, data_splits, ltcg_built
    read, _ = pe_reader(open(orig_exe, 'rb').read())
    manifest = json.load(open(os.path.join(ROOT, 'config', 'matched_functions.json')))
    splits = data_splits()
    chosen = [f for f in splits if any(f == x or (x.endswith('/') and f.startswith(x)) for x in files)]
    for f in chosen:
        if ltcg_built(f) or f not in manifest['files']:
            sys.exit('%s: only plain (non-LTCG) objects with matched functions can stand in for their units' % f)
    if not chosen:
        sys.exit('no source file in config/splits.txt matches %s' % ' '.join(files))
    # (the self-test in a folder of its own: verify runs it beside the gate; compared by prefix below)
    sub = os.path.normpath(os.path.abspath(os.path.join(work, 'selftest' if self_test else 'substitute')))
    os.makedirs(sub, exist_ok=True)
    plan = {src: locate_sections(src, read, manifest, sub) for src in chosen}
    settle_tables(plan, read)
    follow_pointers(plan, read)
    units = {src: unit_of(src, p, splits) for src, p in plan.items()}
    # jeff's splits: relink's cut units and ours; its symbols: every name our objects define or use, under our names
    write_jeff_splits(os.path.join(sub, 'splits.txt'), lay)
    with open(os.path.join(sub, 'splits.txt'), 'a') as fh:
        for src, ((lo, hi), rdata, keep) in units.items():
            fh.write('\n%s:\n\t.text       start:0x%08X end:0x%08X\n' % (src, lo, hi))
            if rdata:
                fh.write('\t.rdata      start:0x%08X end:0x%08X\n' % rdata)
    write_jeff_symbols(os.path.join(sub, 'symbols.txt'), lay, tls_directory(orig_exe))
    rows = {}  # name -> (address, size)
    # jeff needs the size of every function it is told of: its own analysis (cd2.py setup) has them
    analysed = {}
    for line in open(os.path.join(ROOT, 'build', 'cd2', 'symbols.txt')):
        m = re.match(r'^\S+ = \.text:0x([0-9A-Fa-f]+); // type:function size:0x([0-9A-Fa-f]+)', line)
        if m:
            analysed[int(m.group(1), 16)] = int(m.group(2), 16)
    def literal(robj, sec, value):
        # jeff renames a string it finds to its literal's mangled name unless the row gives its kind
        names = [x['name'] for x in robj.symbols.values() if x['sec'] == sec and x['value'] == value]
        return 'string' if any(n.startswith('??_C@_0') for n in names) else             'wstring' if any(n.startswith('??_C@_1') for n in names) else None
    def exported(robj, keep):
        return {k: s for k, s in robj.symbols.items()
                if s['sec'] in keep and s['cls'] in (2, 3) and not s['name'].startswith(('.', '$'))}
    statics = collections.Counter(s['name'] for src, p in plan.items()
                                  for s in exported(p['robj'], units[src][2]).values() if s['cls'] == 3)
    defined = {}  # address -> the name a unit defines there
    unique = {}  # src -> {symbol index: name}: a static exported under a name of its own
    for src, p in plan.items():
        robj, keep = p['robj'], units[src][2]
        funcs = robj.functions()
        unique[src] = {}
        for k, s in exported(robj, keep).items():
            a = p['base'][s['sec']] + s['value']
            name = s['name']
            if s['cls'] == 3 and statics[name] > 1:
                # statics of one name in several units (libjpeg's start_input_pass in jdcoefct.c and jdinput.c):
                # under one exported name the linker would keep one and drop the others as duplicate COMDATs
                name = unique[src][k] = '%s@%08X' % (name, a)
            size = funcs[s['name']][2] if s['name'] in funcs else (robj.data_symbol(s['name']) or {}).get('size')
            rows[name] = (a, size, literal(robj, s['sec'], s['value']))
            defined.setdefault(a, name)
    alias = {src: aliases(p, units[src][2], defined) for src, p in plan.items()}
    for src, p in plan.items():
        robj = p['robj']
        held = {robj.symbols[k]['name'] for k in alias[src]}
        referenced = {s['name']: k for k, s in robj.symbols.items() if s['sec'] == 0 and s['cls'] == 2}
        for n, a in p['names'].items():
            # the register save/restore helpers jeff names itself, under the names our objects use
            if n.startswith(('$', '.', '__save', '__rest')) or n in robj.internal or n in held:
                continue
            if n in referenced:
                # a name the object only references: the name a unit defines there, else its alias (CD2 has two
                # sprintf, 82F1A300 for Lua and 8304878C, which jeff names sprintf)
                alias[src][referenced[n]] = defined.get(a, 'cd2_%08X' % a)
                rows.setdefault(alias[src][referenced[n]], (a, analysed.get(a), None))
            else:
                rows.setdefault(n, (a, analysed.get(a), None))
        funcs = robj.functions()
        for k, n in alias[src].items():
            s = robj.symbols[k]
            if not s['sec']:
                continue
            sec, a = robj.sections[s['sec'] - 1], p['base'][s['sec']] + s['value']
            size = (funcs[s['name']][2] if s['name'] in funcs else analysed.get(a) if sec['ch'] & relocs.CODE else
                    sec['size'] - s['value'] if s['name'].startswith('.') or sec['ch'] & relocs.COMDAT else
                    (robj.data_symbol(s['name']) or {}).get('size'))
            rows.setdefault(n, (a, size, literal(robj, s['sec'], s['value'])))
        alias[src].update(unique[src])
    with open(os.path.join(sub, 'symbols.txt'), 'a') as fh:
        for n, (a, size, kind) in sorted(rows.items(), key=lambda x: x[1][0]):
            sec = '.text' if 0x821D0000 <= a < 0x83049200 else '.rdata' if a < PDATA[0] else '.data'
            fh.write('%s = %s:0x%08X; // type:%s%s%s\n' % (n, sec, a, 'function' if sec == '.text' else 'object',
                                                            ' size:0x%X' % size if size else '',
                                                            ' data:%s' % kind if kind else ''))
    open(os.path.join(sub, 'config.yml'), 'w').write('object: ../orig/default_patched.xex\nsplits: splits.txt\n'
                                                     'symbols: symbols.txt\n')
    out = os.path.join(sub, 'out')
    if os.path.exists(out):
        shutil.rmtree(out)
    r = subprocess.run([JEFF, 'xex', 'split', 'config.yml', 'out'], cwd=sub, capture_output=True, text=True)
    open(os.path.join(sub, 'split.log'), 'w').write(r.stdout + r.stderr)
    if r.returncode:
        sys.exit('jeff split failed; see %s' % os.path.join(sub, 'split.log'))
    objdir = os.path.join(out, 'obj')
    rename_section(os.path.join(objdir, 'relink_rdata_merged.obj'), '.rdata', '.rdatA')
    rename_section(os.path.join(objdir, 'relink_rdata_tail.obj'), '.rdata', '.rdata$x', 0x00400000)
    starts, objs = {}, []
    for u in json.load(open(os.path.join(out, 'config.json')))['units']:
        path = os.path.normpath(os.path.join(sub, u['object']))
        if u['name'] in plan:
            (lo, hi), rdata, keep = units[u['name']]
            path = os.path.join(sub, 'ours', os.path.splitext(u['name'])[0].replace('/', '_') + '.sub.obj')
            rewrite_object(plan[u['name']], keep, rows, alias[u['name']], path)
            starts[path] = {'.text': lo}
            if rdata:
                starts[path]['.rdata'] = rdata[0]
            if pdata_start(read, lo, hi):
                starts[path][RENAMED['.pdata']] = pdata_start(read, lo, hi)
        else:
            for old, new in RENAMED.items():
                rename_section(path, old, new)
            parts = u['name'].split('_')
            if u.get('autogenerated') and len(parts) >= 4:
                start, name = int(parts[2], 16), '.' + parts[3]
                starts[path] = {RENAMED.get(name, name): start}
                # jeff aligns a piece by its contents; it must land at its address, and as each piece follows the
                # previous one without a gap, the largest alignment its address allows (up to 16) adds no padding
                rename_section(path, RENAMED.get(name, name), RENAMED.get(name, name), min(start & -start, 16).bit_length() << 20)
        objs.append(path)
    dropped = {os.path.join(objdir, 'relink_rdata_debugdir.obj'), os.path.join(objdir, 'relink_rdata_codeview.obj')}
    link_objs = [p for p in link_order(objs, starts) if p not in dropped
                 and not (p.startswith(objdir) and object_sections(p) & PACKAGER_SECTIONS)]
    print('substituted %d unit(s)%s' % (len(plan), ': ' + ', '.join(sorted(plan)) if len(plan) <= 4 else
                                        ' from ' + ', '.join(sorted({os.path.dirname(f) + '/' for f in plan}))))
    # /OPT:REF: our objects' functions CD2 does not have are referenced by nothing, and dropped; /INCLUDE: but every
    # function CD2 has stays, referenced or not (lapi.c's luaA_index); /OPT:NOICF: identical functions stay apart, as
    # CD2 keeps them (/OPT:REF alone would fold jcapimin's jpeg_destroy_compress into jdapimin's
    # jpeg_destroy_decompress)
    keep = ['/INCLUDE:' + {robj.symbols[k]['name']: n for k, n in unique[src].items()}.get(n, n)
            for src, p in plan.items() for robj in [p['robj']] for n in p['matched']]
    flags = ['/OPT:REF', '/OPT:NOICF'] + keep
    ours = {p for p in link_objs if p.endswith('.sub.obj')}
    if not self_test:
        return link_and_compare(sub, link_objs, lay, sections(orig_exe), local_xex, flags, ours).identical
    # self-test: one word changed in one of our objects must be the one word of the image that differs
    caught_all = True
    for what, code in (('code word', True), ('data word', False)):
        at = None
        for src in sorted(plan):
            path = os.path.join(sub, 'ours', os.path.splitext(src)[0].replace('/', '_') + '.sub.obj')
            planted = os.path.join(sub, 'plant', os.path.basename(path))
            at = plant(plan[src], units[src][2], path, planted, code)
            if at is not None:
                break
        if at is None:
            print('self-test %-40s cannot plant it: no unit has one (update the self-test)' % what)
            caught_all = False
            continue
        res = link_and_compare(sub, [planted if o == path else o for o in link_objs], lay, sections(orig_exe), local_xex,
                               flags, ours - {path} | {planted})
        caught = res.words == 1 and res.first == at
        caught_all &= caught
        print('self-test %-40s %s' % ('%s at %08X (%s)' % (what, at, src), 'caught' if caught else 'NOT CAUGHT'))
    return caught_all


def plant(p, keep, path, dst, code):
    """A copy (dst) of our object as the unit links it (path) with one word changed, and that word's address in CD2:
    the first word of the unit's code (code) or of its kept data that no relocation covers. None if it has none."""
    import relocs
    robj = p['robj']
    d = bytearray(open(path, 'rb').read())
    opt = struct.unpack_from('<H', d, 16)[0]
    for i in sorted(keep, key=lambda i: p['base'][i]):
        s = robj.sections[i - 1]
        if bool(s['ch'] & relocs.CODE) != code or not s['data']:
            continue
        covered = {o + k for o, _, _ in s['relocs'] for k in range(-3, 4)}
        off = next((o for o in range(0, len(s['data']) - 3, 4) if o not in covered), None)
        if off is None:
            continue
        raw = struct.unpack_from('<I', d, 20 + opt + 40 * (i - 1) + 20)[0]
        d[raw + off + 3] ^= 1
        os.makedirs(os.path.dirname(dst), exist_ok=True)
        open(dst, 'wb').write(d)
        return p['base'][i] + off
    return None


def main():
    argv = sys.argv[1:]
    substitute = ([x for x in argv[argv.index('--substitute') + 1:] if not x.startswith('--')]
                  if '--substitute' in argv else None)
    if substitute is not None:
        argv = argv[:argv.index('--substitute')]
    args = [a for a in argv if not a.startswith('--')]
    if not args or substitute == []:
        print(__doc__)
        sys.exit(2)
    check_toolchain()
    xex = args[0]
    work = args[1] if len(args) > 1 else os.path.join(ROOT, 'build', 'relink')
    resplit = '--resplit' in sys.argv
    if hashlib.sha1(open(xex, 'rb').read()).hexdigest().upper() != XEX_SHA1:
        sys.exit('%s is not the title-update default_patched.xex (SHA1 %s); refusing.' % (xex, XEX_SHA1))
    if not os.path.exists(JEFF):
        sys.exit('jeff is not built: powershell -File tools\\build_tools.ps1 jeff')
    os.makedirs(os.path.join(work, 'orig'), exist_ok=True)
    local_xex = os.path.join(work, 'orig', 'default_patched.xex')
    if not os.path.exists(local_xex):
        shutil.copy(xex, local_xex)
    orig_exe = os.path.join(work, 'orig', 'default_patched.exe')
    if not os.path.exists(orig_exe):
        subprocess.run([JEFF, 'xex', 'extract', local_xex], cwd=os.path.join(work, 'orig'), check=True, capture_output=True)
        produced = [f for f in os.listdir(os.path.join(work, 'orig')) if f.endswith('.exe')]
        os.replace(os.path.join(work, 'orig', produced[0]), orig_exe)
    out = os.path.join(work, 'out')
    lay = debug_layout(orig_exe)
    if substitute is not None:
        sys.exit(0 if substitute_units(work, substitute, lay, orig_exe, local_xex, '--self-test' in sys.argv) else 1)
    if resplit and os.path.exists(out):
        shutil.rmtree(out)
    if not os.path.exists(os.path.join(out, 'obj')):
        write_jeff_splits(os.path.join(work, 'splits.txt'), lay)
        write_jeff_symbols(os.path.join(work, 'symbols.txt'), lay, tls_directory(orig_exe))
        open(os.path.join(work, 'config.yml'), 'w').write('object: orig/default_patched.xex\nsplits: splits.txt\n'
                                                          'symbols: symbols.txt\n')
        r = subprocess.run([JEFF, 'xex', 'split', 'config.yml', 'out'], cwd=work, capture_output=True, text=True)
        open(os.path.join(work, 'split.log'), 'w').write(r.stdout + r.stderr)
        if r.returncode:
            sys.exit('jeff split failed; see %s' % os.path.join(work, 'split.log'))
        # data before the original debug directory: merged into .rdata so it lands before the linker's directory;
        # data after the original CodeView record: sorts after the linker's .rdata$debug
        objdir0 = os.path.join(out, 'obj')
        if not rename_section(os.path.join(objdir0, 'relink_rdata_merged.obj'), '.rdata', '.rdatA'):
            sys.exit('relink_rdata_merged.obj has no .rdata section')
        # (8-byte aligned, as the split's cut after the CodeView record)
        if not rename_section(os.path.join(objdir0, 'relink_rdata_tail.obj'), '.rdata', '.rdata$x', 0x00400000):
            sys.exit('relink_rdata_tail.obj has no .rdata section')
        # sections the linker treats specially when they carry these names: as data, under neutral names
        for f in os.listdir(objdir0):
            for old, new in RENAMED.items():
                rename_section(os.path.join(objdir0, f), old, new)
    objdir = os.path.join(out, 'obj')
    objs = sorted(f for f in os.listdir(objdir) if f.endswith('.obj'))
    # the linker writes its own debug directory and CodeView record in their place
    dropped = {'relink_rdata_debugdir.obj', 'relink_rdata_codeview.obj'}
    dropped |= {f for f in objs if object_sections(os.path.join(objdir, f)) & PACKAGER_SECTIONS}
    orig = sections(orig_exe)
    link_objs = [os.path.join(objdir, f) for f in objs if f not in dropped]
    sys.exit(0 if link_and_compare(work, link_objs, lay, orig, local_xex).identical else 1)


Result = collections.namedtuple('Result', 'identical words first')  # first: the first differing word's address


def link_and_compare(work, link_objs, lay, orig, local_xex, extra_flags=(), strict=()):
    """Link link_objs (in this order) with the XDK linker at the original base and compare the memory image with the
    original's, printing the result. Returns a Result. A name the objects in strict leave unresolved
    fails the result (the split's own objects may: /FORCE:UNRESOLVED)."""
    image = os.path.join(work, 'relink.exe')
    for old in (image, os.path.join(work, 'relink.pe')):
        if os.path.exists(old):
            os.remove(old)
    rsp = os.path.join(work, 'link.rsp')
    open(rsp, 'w').write('\n'.join(list(extra_flags) + ['"%s"' % o for o in link_objs]) + '\n')
    env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'])
    # CodeView record path: the original build's (same length, so the record has the original size)
    dbg, dsz, cv, cvsz, r0, r1 = lay
    cvrec = orig['.rdata'][2][cv - r0: cv - r0 + cvsz]
    pdb_path = cvrec[24:].split(b'\0', 1)[0].decode('latin-1')
    extra = ['/MERGE:.rdatA=.rdata', '/PDB:' + os.path.join(work, 'relink.pdb'), '/PDBALTPATH:' + pdb_path]
    r = subprocess.run([os.path.join(BIN, 'link.exe')] + LINK_FLAGS + extra + ['/OUT:' + image,
                       '/MAP:' + os.path.join(work, 'relink.map'), '@' + rsp], env=env, capture_output=True, text=True)
    open(os.path.join(work, 'link.log'), 'w').write(r.stdout + r.stderr)
    # _fltused: the compiler's marker that pulls in the C library's floating-point support; nothing relocates to it
    unresolved = sorted({m.group(2) for m in re.finditer(r'^(.+?) : error LNK20(?:01|19): unresolved external symbol (\S+)',
                                                        r.stdout + r.stderr, re.M)
                         if os.path.normcase(m.group(1)) in {os.path.normcase(os.path.basename(o)) for o in strict}
                         and m.group(2) != '_fltused'})
    pe = os.path.join(work, 'relink.pe') if os.path.exists(os.path.join(work, 'relink.pe')) else image
    if not os.path.exists(pe):
        sys.exit('link failed; see %s' % os.path.join(work, 'link.log'))
    new = sections(pe)
    lo = min(v[0] for v in orig.values())
    hi = xex_resource_start(local_xex)
    a, b = memory_image(orig, lo, hi), memory_image(new, lo, hi)
    print('memory image %08X-%08X (up to the XEX resources)' % (lo, hi))

    # words that are not linker output: verify what the linker wrote there, then take the packaged words
    imports = linker_imports(a, lo, xex_import_records(local_xex))
    bad_imports = sorted(va for va, w in imports.items() if bytes(b[va - lo: va - lo + 4]) != w)
    for va in imports:
        b[va - lo: va - lo + 4] = a[va - lo: va - lo + 4]
    print('  imports: %d words; %s' % (len(imports), 'all hold what the linker writes' if not bad_imports else
          '%d do NOT hold what the linker writes, first at %08X' % (len(bad_imports), bad_imports[0])))
    meta = [(dbg + 4, 4, 'debug directory time stamp'), (cv + 4, 20, 'CodeView GUID and age')]
    for va, n, what in meta:
        same = a[va - lo: va - lo + n] == b[va - lo: va - lo + n]
        b[va - lo: va - lo + n] = a[va - lo: va - lo + n]
        print('  link metadata: %s at %08X %s' % (what, va, 'identical' if same else 'differs (normalised)'))
    regions = sorted((va, va + max(vs, len(data)), name) for name, (va, vs, data) in orig.items() if va < hi)
    in_sections = 0
    for va, end, name in regions:
        n, diff = word_diff(a, b, va - lo, min(end, hi) - lo)
        in_sections += diff
        print('  %-9s %08X-%08X  %7.3f%% identical  (%d words differ)' % (name, va, end, 100.0 * (n - diff) / max(n, 1), diff))
    n, diff = word_diff(a, b, 0, hi - lo)
    print('  between sections: %d words differ' % (diff - in_sections))
    print('  whole image: %d of %d words differ' % (diff, n))
    if unresolved:
        print('  unresolved in the substituted objects: %d (%s)' % (len(unresolved), ', '.join(unresolved[:8])))
    identical = diff == 0 and not bad_imports and not unresolved
    # Relocation completeness (reported, not part of the result): the packager overwrote the base relocation table, but
    # the section table keeps its size. The linker writes one entry per absolute fixup, grouped by page, so the sizes
    # agree only when jeff found the same absolute relocations as the original objects had. A reference jeff missed
    # still relinks identically (its bytes are copied); it would only break a build in which objects move.
    breloc = orig.get('.reloc', (0, 0, b''))[1], new.get('.reloc', (0, 0, b''))[1]
    print('  relocation completeness: base relocation table %X bytes, original %X%s' % (breloc[1], breloc[0],
          ' (complete)' if breloc[0] == breloc[1] else ' (%+d bytes: jeff found a different set of absolute references)'
          % (breloc[1] - breloc[0])))
    print('RESULT: %s' % ('IDENTICAL' if identical else 'DIFFERENT'))
    print('section table: original %s' % ', '.join('%s@%08X' % (k, v[0]) for k, v in orig.items()))
    print('               relinked %s' % ', '.join('%s@%08X' % (k, v[0]) for k, v in new.items()))

    def read_new(va, n):
        return bytes(b[va - lo: va - lo + n])
    if '.text' in new and not identical:
        starts = sorted(v[0] for v in orig.values())
        cat = classify_text(orig['.text'][0], read_new(orig['.text'][0], len(orig['.text'][2])), orig['.text'][2], starts)
        n = len(orig['.text'][2]) // 4
        print('.text differences by cause:')
        for k, v in cat.most_common():
            print('  %6.2f%%  %8d  %s' % (100.0 * v / n, v, k))
    first = None
    if diff:
        chunk = 0x10000
        at = next(i for i in range(0, hi - lo, chunk) if a[i:i + chunk] != b[i:i + chunk])
        first = lo + next(i for i in range(at, min(at + chunk, hi - lo), 4) if a[i:i + 4] != b[i:i + 4])
    return Result(identical, diff, first)


if __name__ == '__main__':
    main()
