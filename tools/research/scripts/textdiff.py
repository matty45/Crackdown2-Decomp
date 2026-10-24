import struct, sys, collections
def sections(path):
    d = open(path, 'rb').read()
    pe = struct.unpack('<I', d[0x3C:0x40])[0]
    nsec = struct.unpack('<H', d[pe + 6:pe + 8])[0]
    optsz = struct.unpack('<H', d[pe + 20:pe + 22])[0]
    base = struct.unpack('<I', d[pe + 24 + 28:pe + 24 + 32])[0]
    out = {}
    for i in range(nsec):
        o = pe + 24 + optsz + i * 40
        name = d[o:o + 8].rstrip(b'\0').decode()
        vs, va, rs, ra = struct.unpack('<IIII', d[o + 8:o + 24])
        out[name] = (base + va, d[ra:ra + min(vs, rs)] if ra else b'')
    return out
a, b = sections(sys.argv[1]), sections(sys.argv[2])
sec = sys.argv[3]; SH = int(sys.argv[4], 16) if len(sys.argv) > 4 else 0x20
va, x = a[sec]; _, y = b[sec]
cat = collections.Counter(); samples = collections.defaultdict(list)
for i in range(0, min(len(x), len(y)) - 3, 4):
    p, q = struct.unpack('>I', x[i:i + 4])[0], struct.unpack('>I', y[i:i + 4])[0]
    if p == q:
        continue
    op_p, op_q = p >> 26, q >> 26
    if op_p != op_q:
        k = 'opcode differs'
    elif (p & 0xFFFF0000) == (q & 0xFFFF0000):
        dlo = ((q & 0xFFFF) - (p & 0xFFFF)) & 0xFFFF
        k = 'lo16 +0x%x' % dlo if dlo in (SH,) else 'lo16 other'
    elif op_p == 15 and ((q - p) & 0xFFFF) == 1:
        k = 'lis carry (+1)'
    elif op_p in (16, 18):
        k = 'branch target'
    else:
        k = 'other field'
    cat[k] += 1
    if len(samples[k]) < 3:
        samples[k].append('%08x: %08x -> %08x' % (va + i, p, q))
tot = min(len(x), len(y)) // 4
print('%s words=%d differing=%d' % (sec, tot, sum(cat.values())))
for k, v in cat.most_common():
    print('  %-16s %7d  %6.3f%%   e.g. %s' % (k, v, 100.0 * v / tot, '; '.join(samples[k])))
