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
        out[name] = (base + va, d[ra:ra + min(vs, rs)] if ra else b'')
    return out
a, b = sections(sys.argv[1]), sections(sys.argv[2])
sec = sys.argv[3]
va, x = a[sec]; _, y = b[sec]
print('orig  +000:', x[:48].hex(' ', 4))
print('relnk +000:', y[:48].hex(' ', 4))
# runs of differing words, coarse histogram by 64KB
diffs = [i for i in range(0, min(len(x), len(y)) - 3, 4) if x[i:i + 4] != y[i:i + 4]]
print('differing words:', len(diffs), 'of', min(len(x), len(y)) // 4)
# try to detect a constant shift
for sh in (0x20, -0x20, 0xD8, -0xD8):
    same = sum(1 for i in range(0x1000, 0x20000, 4) if 0 <= i + sh < len(y) and x[i:i + 4] == y[i + sh:i + sh + 4])
    print('shift %+#x: %d/%d words equal in sample' % (sh, same, (0x20000 - 0x1000) // 4))
