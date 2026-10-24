"""Relink Crackdown 2 from jeff's split objects and compare the result with the original, word for word.

usage: py -I tools/relink.py <path to default_patched.xex> [workdir] [--resplit]

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
"""
import collections, hashlib, os, shutil, struct, subprocess, sys

TOOLS = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, TOOLS)
from verify_src import XDK, BIN, ROOT, check_toolchain

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


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    if not args:
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
    image = os.path.join(work, 'relink.exe')
    rsp = os.path.join(work, 'link.rsp')
    open(rsp, 'w').write('\n'.join('"%s"' % o for o in link_objs) + '\n')
    env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'])
    # CodeView record path: the original build's (same length, so the record has the original size)
    dbg, dsz, cv, cvsz, r0, r1 = lay
    cvrec = orig['.rdata'][2][cv - r0: cv - r0 + cvsz]
    pdb_path = cvrec[24:].split(b'\0', 1)[0].decode('latin-1')
    extra = ['/MERGE:.rdatA=.rdata', '/PDB:' + os.path.join(work, 'relink.pdb'), '/PDBALTPATH:' + pdb_path]
    r = subprocess.run([os.path.join(BIN, 'link.exe')] + LINK_FLAGS + extra + ['/OUT:' + image,
                       '/MAP:' + os.path.join(work, 'relink.map'), '@' + rsp], env=env, capture_output=True, text=True)
    open(os.path.join(work, 'link.log'), 'w').write(r.stdout + r.stderr)
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
    identical = diff == 0 and not bad_imports
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
    sys.exit(0 if identical else 1)


if __name__ == '__main__':
    main()
