import struct, sys, collections, json
sys.argv += []
exec(open(__file__.replace('brdiff.py', 'textdiff.py')).read().split('a, b = sections')[0])
a, b = sections(sys.argv[1]), sections(sys.argv[2])
va, x = a['.text']; _, y = b['.text']
def tgt(w, ea):
    li = w & 0x03FFFFFC
    if li & 0x02000000:
        li -= 0x04000000
    return (ea + li) & 0xFFFFFFFF if not (w & 2) else li & 0xFFFFFFFF
pairs = collections.Counter()
hyp = collections.Counter()
for i in range(0, min(len(x), len(y)) - 3, 4):
    p, q = struct.unpack('>I', x[i:i + 4])[0], struct.unpack('>I', y[i:i + 4])[0]
    if p != q and p >> 26 == 18 and q >> 26 == 18:
        t, t2 = tgt(p, va + i), tgt(q, va + i)
        pairs[(t, t2)] += 1
        delta = (t2 - t) & 0xFFFFFFFF
        hyp['T2 = T + site_off + 0x10000' if delta == i + 0x10000 else ('T2 = T + site_off' if delta == i else 'other')] += 1
print('hypothesis check:', dict(hyp))
print('distinct (orig target, relink target) pairs:', len(pairs))
json.dump([[k[0], k[1], v] for k, v in pairs.most_common(4000)], open(sys.argv[3], 'w'))
for (o, r), n in pairs.most_common(12):
    print('%08x -> %08x  x%d' % (o, r, n))
