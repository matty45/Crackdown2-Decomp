"""Identify CD2's functions with the XDK's own library code (XDK 9328, the build CD2 was made with).

Every function of every object of every library in <XDK>/lib/xbox is hashed with its relocated words masked, as is
every CD2 function (verify_ltcg.masked: address immediates and calls leaving the function); a hash that names CD2
functions is then confirmed word by word with coff.compare, which masks exactly the library's relocation sites.
Libraries with LTCG (IL) objects and import members are skipped. Nothing from the libraries is written to the
repository: the result goes to <out json> (CD2 address -> [library, object, symbol, size]).

usage: py -I tools/research/splits_libs/xdk_libmatch.py <out json> [--min-size N] [--libs substring,...]
       [--libdir DIR]   (another folder of PowerPC libraries, searched recursively; default <XDK>/lib/xbox)
"""
import collections, hashlib, json, os, struct, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
import cd2, coff, verify_ltcg as vl  # noqa: E402

out_path = sys.argv[1]
min_size = int(sys.argv[sys.argv.index('--min-size') + 1]) if '--min-size' in sys.argv else 16
only = sys.argv[sys.argv.index('--libs') + 1].split(',') if '--libs' in sys.argv else None
libdir = sys.argv[sys.argv.index('--libdir') + 1] if '--libdir' in sys.argv else os.path.join(cd2.XDK, 'lib', 'xbox')


def members(path):
    """[(member name, bytes)] of an ar archive (MS .lib)."""
    data = open(path, 'rb').read()
    if data[:8] != b'!<arch>\n':
        return []
    pos, longnames, out = 8, b'', []
    while pos + 60 <= len(data):
        hdr = data[pos:pos + 60]
        name = hdr[:16].decode('latin-1').strip()
        size = int(hdr[48:58].decode('latin-1').strip() or 0)
        body = data[pos + 60:pos + 60 + size]
        pos += 60 + size + (size & 1)
        if name == '//':
            longnames = body
            continue
        if name == '/' or name == '':
            continue
        if name.startswith('/') and name[1:].isdigit():
            off = int(name[1:])
            name = longnames[off:longnames.find(b'\0', off)].decode('latin-1')
        name = name.rstrip('/')
        if body[:4] == b'\0\0\xff\xff':  # short import member
            continue
        out.append((name.replace('\\', '/').split('/')[-1], body))
    return out


def lib_digest(code, rel):
    ws = list(struct.unpack('>%dI' % (len(code) // 4), code[:len(code) // 4 * 4]))
    for off in rel:  # relocated words: mask as an external reference
        i = off // 4
        if i < len(ws):
            w = ws[i]
            ws[i] = (w & 0xFC000003) if w >> 26 == 18 else (w & 0xFFFF0000)
    m = vl.masked(ws, 0x10000000)
    for off in rel:
        i = off // 4
        if i < len(m):
            m[i] = (ws[i] & 0xFC000003) if ws[i] >> 26 == 18 else (ws[i] & 0xFFFF0000)
    return hashlib.sha1(struct.pack('>%dI' % len(m), *m)).hexdigest()


def cd2_digest(a, n):
    ws = list(struct.unpack('>%dI' % (n // 4), cd2.read(a, n // 4 * 4)))
    m = vl.masked(ws, a)
    return hashlib.sha1(struct.pack('>%dI' % len(m), *m)).hexdigest()


syms = cd2.jeff_symbols()
print('hashing %d CD2 functions' % len(syms), flush=True)
cd2_by_hash = collections.defaultdict(list)
for a, (_, n) in syms.items():
    if n >= min_size:
        cd2_by_hash[(n, cd2_digest(a, n))].append(a)

tmp = tempfile.mkdtemp(prefix='xdklib_', dir=cd2.scratch_dir('xdklib'))
found = collections.defaultdict(list)
stats = collections.Counter()
libs = sorted(os.path.relpath(os.path.join(dp, f), libdir) for dp, _, fs in os.walk(libdir) for f in fs)
for lib in libs:
    if not lib.lower().endswith('.lib') or (only and not any(s in lib for s in only)):
        continue
    for k, (mname, body) in enumerate(members(os.path.join(libdir, lib))):
        p = os.path.join(tmp, 'm.obj')
        open(p, 'wb').write(body)
        try:
            fns = list(coff.functions(p))
        except Exception:
            stats['skipped objects'] += 1
            continue
        stats['objects'] += 1
        for name, code, rel in fns:
            if len(code) < min_size or len(code) % 4:
                continue
            stats['library functions'] += 1
            hits = cd2_by_hash.get((len(code), lib_digest(code, rel)), [])
            for a in hits:
                if coff.compare(code, cd2.read(a, len(code)), rel)[0]:
                    found['0x%08X' % a].append([lib, mname, name, len(code)])
    print('%-28s done (%d CD2 functions identified so far)' % (lib, len(found)), flush=True)
import shutil  # noqa: E402
shutil.rmtree(tmp, ignore_errors=True)
json.dump(found, open(out_path, 'w'), indent=0)
print(dict(stats), '; CD2 functions identified:', len(found))
