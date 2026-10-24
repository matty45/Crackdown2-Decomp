import struct, sys, collections
exec(open(__file__.replace('textdiff2.py', 'textdiff.py')).read().split('a, b = sections')[0])
a, b = sections(sys.argv[1]), sections(sys.argv[2])
sec = sys.argv[3]; SH = 0x20
va, x = a[sec]; _, y = b[sec]
def sext(v, bits):
    return v - (1 << bits) if v & (1 << (bits - 1)) else v
cat = collections.Counter(); samples = collections.defaultdict(list)
for i in range(0, min(len(x), len(y)) - 3, 4):
    p, q = struct.unpack('>I', x[i:i + 4])[0], struct.unpack('>I', y[i:i + 4])[0]
    if p == q:
        continue
    op = p >> 26
    if op != q >> 26:
        k = 'opcode differs'
    elif op == 18 and (p & 3) == (q & 3) and ((sext(q & 0x03FFFFFC, 26) - sext(p & 0x03FFFFFC, 26)) & 0xFFFFFFFF) == i:
        k = 'REL24 encoding bug'
    elif op == 16 and (p & 0xFFFF0003) == (q & 0xFFFF0003):
        k = 'REL14 (cond branch)'
    elif (p & 0xFFFF0000) == (q & 0xFFFF0000):
        dlo = ((q & 0xFFFF) - (p & 0xFFFF)) & 0xFFFF
        if dlo == SH:
            k = '+0x20 rdata shift (lo16)'
        elif op == 15 and dlo == 1:
            k = '+0x20 rdata shift (lis carry)'
        else:
            k = 'lo16 other'
    else:
        k = 'other field'
    cat[k] += 1
    if len(samples[k]) < 3:
        samples[k].append('%08x: %08x->%08x' % (va + i, p, q))
tot = min(len(x), len(y)) // 4
print('%s words=%d differing=%d (%.3f%%)' % (sec, tot, sum(cat.values()), 100.0 * sum(cat.values()) / tot))
for k, v in cat.most_common():
    print('  %-30s %7d  %6.3f%%   e.g. %s' % (k, v, 100.0 * v / tot, '; '.join(samples[k])))
