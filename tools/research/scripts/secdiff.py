import struct, sys
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
        out[name] = (base + va, d[ra:ra + min(vs, rs)] if ra else b'', vs)
    return out
a, b = sections(sys.argv[1]), sections(sys.argv[2])
for n in a:
    if n not in b:
        print('%-8s only in original' % n); continue
    va1, d1, vs1 = a[n]; va2, d2, vs2 = b[n]
    m = min(len(d1), len(d2))
    same = sum(1 for i in range(0, m - 3, 4) if d1[i:i + 4] == d2[i:i + 4])
    first = next((i for i in range(0, m - 3, 4) if d1[i:i + 4] != d2[i:i + 4]), None)
    print('%-8s orig va=%08x size=%08x | relink va=%08x size=%08x | identical words %.4f%%  first diff +%s' % (
        n, va1, vs1, va2, vs2, 100.0 * same / max(1, m // 4), hex(first) if first is not None else '-'))
