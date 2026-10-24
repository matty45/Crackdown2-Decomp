"""Classify CD2 functions by how they load float constants from the merged constant pool.
  anchored : at least one load through a base register set to the pool start (LTCG-only form)
  direct2  : no anchored loads, but 2+ distinct pool constants each loaded with its own lis (non-LTCG signature,
             assuming LTCG always anchors in that case, as our LTCG test build did)
Function boundaries come from .pdata. Output: counts per 1 MB region of .text, and per-function CSV.
usage: py -I ltcg_map.py <default.exe> <out.csv>
"""
import collections, struct, sys

d = open(sys.argv[1], 'rb').read()
pe = struct.unpack_from('<I', d, 0x3C)[0]
nsec = struct.unpack_from('<H', d, pe + 6)[0]
opt = struct.unpack_from('<H', d, pe + 20)[0]
base = struct.unpack_from('<I', d, pe + 24 + 28)[0]
secs = {}
for i in range(nsec):
    name, vs, va, rs, rp = struct.unpack_from('<8sIIII', d, pe + 24 + opt + 40 * i)
    secs[name.rstrip(b'\0').decode()] = (base + va, vs, rp, rs)


def word(va):
    for n, (sva, vs, rp, rs) in secs.items():
        if sva <= va < sva + min(vs, rs):
            return struct.unpack_from('>I', d, rp + va - sva)[0]


pva, pvs, prp, prs = secs['.pdata']
funcs = []
for k in range(min(pvs, prs) // 8):
    start, packed = struct.unpack_from('>II', d, prp + 8 * k)
    n = (packed >> 8) & 0x3FFFFF
    if start and n:
        funcs.append((start, n))
POOL_LO, POOL_HI = 0x820F8C80, 0x820F8C80 + 0x8000


def sx(v):
    return v - 0x10000 if v & 0x8000 else v


stats = collections.defaultdict(collections.Counter)
rows = []
for start, n in funcs:
    lis, anc = {}, {}
    direct, anchored = set(), 0
    for i in range(n):
        w = word(start + 4 * i)
        if w is None:
            break
        op, rt, ra, imm = w >> 26, (w >> 21) & 31, (w >> 16) & 31, w & 0xFFFF
        if op == 15 and ra == 0:
            lis[rt] = imm << 16
            anc.pop(rt, None)
            continue
        if op == 14 and ra in lis and ra != 0:
            a = (lis[ra] + sx(imm)) & 0xFFFFFFFF
            lis.pop(rt, None)
            if a == POOL_LO:
                anc[rt] = a
            else:
                anc.pop(rt, None)
            continue
        if op in (48, 50):  # lfs / lfd
            if ra in lis:
                a = (lis[ra] + sx(imm)) & 0xFFFFFFFF
                if POOL_LO <= a < POOL_HI:
                    direct.add(a)
            elif ra in anc:
                anchored += 1
            continue
        if op in (36, 37, 38, 39, 44, 45, 52, 53, 54, 55, 62, 16, 18, 19, 11, 10):  # stores, branches, compares: no GPR write
            continue
        lis.pop(rt, None)
        anc.pop(rt, None)
    kind = 'anchored' if anchored else ('direct2' if len(direct) >= 2 else ('direct1' if direct else 'none'))
    stats[start >> 20][kind] += 1
    rows.append('%08X,%d,%s,%d,%d' % (start, n, kind, anchored, len(direct)))
open(sys.argv[2], 'w').write('start,insns,kind,anchored_loads,direct_pool_consts\n' + '\n'.join(rows) + '\n')
print('%d functions from .pdata' % len(funcs))
print('region     anchored  direct2  direct1     none')
tot = collections.Counter()
for r in sorted(stats):
    c = stats[r]
    tot.update(c)
    print('%03X00000  %8d %8d %8d %8d' % (r, c['anchored'], c['direct2'], c['direct1'], c['none']))
print('total      %8d %8d %8d %8d' % (tot['anchored'], tot['direct2'], tot['direct1'], tot['none']))
