import glob, os, struct, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(sys.argv[0])))
d = open(sys.argv[1], 'rb').read()
pe = struct.unpack_from('<I', d, 0x3C)[0]
nsec = struct.unpack_from('<H', d, pe + 6)[0]
opt = struct.unpack_from('<H', d, pe + 20)[0]
base = struct.unpack_from('<I', d, pe + 24 + 28)[0]
secs = [struct.unpack_from('<8sIIII', d, pe + 24 + opt + 40 * i) for i in range(nsec)]
def word(va):
    rva = va - base
    for name, vs, vaddr, rs, rp in secs:
        if vaddr <= rva < vaddr + max(vs, rs):
            return struct.unpack_from('>I', d, rp + rva - vaddr)[0]
for pk in sys.argv[2:]:
    for t in sorted(glob.glob(os.path.join(pk, 'targets', 'F*'))):
        k, a = os.path.basename(t).split('_')
        a = int(a, 16)
        h = open(os.path.join(t, 'target.hex')).read().strip()
        end = a + len(h) // 2
        last = int(h[-8:], 16)
        # trailing words up to and including the first blr, if the slice did not end in blr/bctr
        if last in (0x4E800020, 0x4E800420):
            continue
        tail, p = [], end
        while len(tail) < 8:
            w = word(p); tail.append(w); p += 4
            if w in (0x4E800020, 0x4E800420) or w == 0:
                break
        if tail and tail[-1] in (0x4E800020, 0x4E800420):
            print('%-20s %s %08X  slice ends %08X, missing %d word(s): %s' % (os.path.basename(pk), k, a, last, len(tail), ' '.join('%08X' % w for w in tail)))
