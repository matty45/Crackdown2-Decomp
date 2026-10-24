"""For each source in config/matched_functions.json: build it normally and with /GL + /LTCG (stub entry,
unresolved externals forced), then compare every listed function three ways:
  plain-vs-ltcg : does LTCG change our own code? (mask = the plain object's relocations)
  plain-vs-cd2  : the normal verify_src.py result
  ltcg-vs-cd2   : LTCG code against CD2, masking address immediates (D-form low halves whose base is not r1,
                  where the high half/opcode/registers agree), since our constant pool layout differs from CD2's.
usage: py -I ltcg_check.py <default.exe> <workdir> [source-substring] [--inc DIR] [--escape FILE.cpp]
  --inc DIR       : extra include directory searched first (both builds)
  --escape FILE   : extra /GL source linked into every LTCG image; it should take the address of the globals the
                    sources use, because LTCG treats a global whose address no /GL code takes as unaliased.
"""
import json, os, re, struct, subprocess, sys
ROOT = r'<repo>'
sys.path.insert(0, os.path.join(ROOT, 'tools', 'research', 'scripts'))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
import coff
from verify_src import pe_reader, FLAGS, XDK, BIN

DFORM = {14, 15, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 58, 62}


def read_image(path):
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
    return rd


def map_funcs(path):
    fs = []
    for l in open(path):
        m = re.match(r'\s*[0-9a-f]{4}:[0-9a-f]+\s+(\S+)\s+([0-9a-f]{8})\s+f\s', l)
        if m:
            fs.append((int(m.group(2), 16), m.group(1)))
    fs.sort()
    return fs


def words(b):
    return list(struct.unpack('>%dI' % (len(b) // 4), b[:len(b) // 4 * 4]))


def lenient_equal(a, b):
    """equal, or both D-form with the same opcode/registers, base not r1, differing only in the immediate"""
    if a == b:
        return True, False
    if a >> 16 == b >> 16 and a >> 26 in DFORM and (a >> 16) & 31 != 1:
        return True, True
    if a >> 26 == 18 and b >> 26 == 18 and a & 3 == b & 3:  # b/bl to (relocated) targets
        return True, True
    return False, False


def main():
    args = sys.argv[1:]
    inc = esc = None
    if '--inc' in args:
        i = args.index('--inc'); inc = args[i + 1]; del args[i:i + 2]
    if '--escape' in args:
        i = args.index('--escape'); esc = args[i + 1]; del args[i:i + 2]
    exe, work = args[0], args[1]
    only = args[2] if len(args) > 2 else ''
    flags = FLAGS + (['/I' + inc] if inc else [])
    target_read, _ = pe_reader(open(exe, 'rb').read())
    manifest = json.load(open(os.path.join(ROOT, 'config', 'matched_functions.json')))
    env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'],
               INCLUDE=os.path.join(XDK, 'include', 'xbox') + ';' + os.path.join(ROOT, 'include'))
    os.makedirs(work, exist_ok=True)
    stub = os.path.join(work, 'stub.c')
    open(stub, 'w').write('void __cdecl Stub(void) {}\n')
    totals = {'same': 0, 'n': 0, 'plain_exact': 0, 'ltcg_exact': 0}
    for src, funcs in manifest['files'].items():
        if only not in src:
            continue
        tag = os.path.splitext(os.path.basename(src))[0]
        d = os.path.join(work, tag)
        os.makedirs(d, exist_ok=True)
        plain = os.path.join(d, 'plain.obj')
        subprocess.run([os.path.join(BIN, 'cl.exe')] + flags + ['/Fo' + plain, os.path.join(ROOT, src)],
                       env=env, capture_output=True, text=True, check=True)
        subprocess.run([os.path.join(BIN, 'cl.exe')] + flags + ['/GL', '/Fo' + d + '\\', os.path.join(ROOT, src), stub] + ([esc] if esc else []),
                       env=env, capture_output=True, text=True, check=True)
        objs = [os.path.join(d, tag + '.obj'), os.path.join(d, 'stub.obj')]
        if esc:
            objs.append(os.path.join(d, os.path.splitext(os.path.basename(esc))[0] + '.obj'))
        r = subprocess.run([os.path.join(BIN, 'link.exe'), '/nologo', '/LTCG', '/NODEFAULTLIB', '/FORCE:UNRESOLVED',
                            '/ENTRY:Stub', '/OPT:NOREF', '/OPT:NOICF', '/MAP:' + os.path.join(d, 't.map'),
                            '/OUT:' + os.path.join(d, 't.exe')] + objs, env=env, capture_output=True, text=True)
        rd = read_image(os.path.join(d, 't.pe'))
        fs = map_funcs(os.path.join(d, 't.map'))
        compiled = list(coff.functions(plain))
        print(src)
        for f in funcs:
            va, size = int(f['address'], 16), f['size']
            target = target_read(va, size)
            found = [(n, c, rel) for n, c, rel in compiled if f['symbol'] in n]
            lt = [(a, n) for a, n in fs if f['symbol'] in n]
            if not found or not lt:
                print('  %08X  missing (plain %d, ltcg %d)' % (va, len(found), len(lt)))
                continue
            name, code, rel = found[0]
            a = lt[0][0]
            nxt = [x for x, _ in fs if x > a]
            lcode = rd(a, (nxt[0] if nxt else a + len(code) + 64) - a)
            lw = words(lcode)
            while lw and lw[-1] == 0:
                lw.pop()
            lcode = struct.pack('>%dI' % len(lw), *lw)
            same = coff.compare(lcode, code, rel)[0]
            plain_exact = coff.compare(code, target, rel)[0]
            tw = words(target)
            res = [lenient_equal(x, y) for x, y in zip(lw, tw)]
            lt_exact = len(lw) == len(tw) and all(ok for ok, _ in res)
            good = sum(1 for ok, _ in res if ok)
            masked = sum(1 for ok, m in res if ok and m)
            totals['n'] += 1
            totals['same'] += same
            totals['plain_exact'] += plain_exact
            totals['ltcg_exact'] += lt_exact
            print('  %08X %4dB  ltcg==plain:%-3s  plain-vs-cd2:%-5s  ltcg-vs-cd2:%s (%d/%d words, %d address-masked)%s'
                  % (va, size, 'yes' if same else 'NO', 'EXACT' if plain_exact else 'diff',
                     'EXACT' if lt_exact else 'diff', good, len(tw), masked,
                     '' if f.get('matching', True) else '  [wip]'))
    print('\n%(n)d functions: LTCG identical to plain for %(same)d; plain exact %(plain_exact)d; LTCG exact %(ltcg_exact)d'
          % totals)


if __name__ == '__main__':
    main()
