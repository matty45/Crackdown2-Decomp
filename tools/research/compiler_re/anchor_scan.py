import struct, sys, collections
d = open(sys.argv[1], 'rb').read()
pe = struct.unpack_from('<I', d, 0x3C)[0]
nsec = struct.unpack_from('<H', d, pe + 6)[0]
opt = struct.unpack_from('<H', d, pe + 20)[0]
base = struct.unpack_from('<I', d, pe + 24 + 28)[0]
secs = {}
for i in range(nsec):
    name, vs, va, rs, rp = struct.unpack_from('<8sIIII', d, pe + 24 + opt + 40 * i)
    secs[name.rstrip(b'\0').decode()] = (base + va, vs, rp, rs)
tva, tvs, trp, trs = secs['.text']
rva_, rvs, rrp, rrs = secs['.rdata']
words = struct.unpack_from('>%dI' % (min(tvs, trs) // 4), d, trp)
def sx(v): return v - 0x10000 if v & 0x8000 else v
LIS, ADDI, LFS, LFD = 15, 14, 48, 50
direct = collections.Counter(); anchored = collections.Counter(); anchors = collections.Counter()
lis = {}; anc = {}
fa_direct = set(); fa_anch = set()
def page(a): return a >> 16
for i, w in enumerate(words):
    pc = tva + 4 * i
    op = w >> 26; rt = (w >> 21) & 31; ra = (w >> 16) & 31; imm = w & 0xFFFF
    if w in (0x4E800020,):  # blr: reset tracking at function ends
        lis.clear(); anc.clear(); continue
    if op == LIS and ra == 0:
        lis[rt] = imm << 16; anc.pop(rt, None); continue
    if op == ADDI and ra in lis and ra != 0:
        a = (lis[ra] + sx(imm)) & 0xFFFFFFFF
        if rva_ <= a < rva_ + rvs:
            anc[rt] = a; anchors[a] += 1
        lis.pop(rt, None); continue
    if op in (LFS, LFD):
        if ra in lis:
            a = (lis[ra] + sx(imm)) & 0xFFFFFFFF
            direct[page(a)] += 1
        elif ra in anc and imm != 0:
            anchored[page(anc[ra] + sx(imm))] += 1
        continue
    # any other write to rt invalidates (rough: most instructions write rt; stores do not)
    if op not in (36, 37, 38, 39, 44, 45, 52, 53, 54, 55, 62, 31) and op != 18 and op != 16:
        lis.pop(rt, None); anc.pop(rt, None)
print('float loads by 64 KB page of the constant: direct lis+lfs vs anchored base+disp')
for p in sorted(set(direct) | set(anchored)):
    if direct[p] + anchored[p] >= 50:
        print('  %04X0000  direct %6d  anchored %6d' % (p, direct[p], anchored[p]))
print('top anchors:', ', '.join('%08X x%d' % (a, n) for a, n in anchors.most_common(8)))
