import struct, sys
def imports(path):
    d = open(path, 'rb').read()
    pe = struct.unpack('<I', d[0x3C:0x40])[0]
    nsec = struct.unpack('<H', d[pe + 6:pe + 8])[0]
    optsz = struct.unpack('<H', d[pe + 20:pe + 22])[0]
    opt = pe + 24
    magic = struct.unpack('<H', d[opt:opt + 2])[0]
    ddoff = opt + (96 if magic == 0x10b else 112)
    imp_rva = struct.unpack('<I', d[ddoff + 8:ddoff + 12])[0]
    secs = []
    for i in range(nsec):
        o = opt + optsz + i * 40
        vs, va, rs, ra = struct.unpack('<IIII', d[o + 8:o + 24])
        secs.append((va, max(vs, rs), ra))
    def off(rva):
        for va, sz, ra in secs:
            if va <= rva < va + sz:
                return rva - va + ra
    has_manifest = b'<assembly' in d and b'Microsoft.VC' in d
    out = []
    o = off(imp_rva)
    while True:
        ilt, ts, fc, name, iat = struct.unpack('<IIIII', d[o:o + 20])
        if name == 0:
            break
        n = off(name)
        out.append(d[n:d.index(b'\0', n)].decode())
        o += 20
    return out, has_manifest
for p in sys.argv[1:]:
    print(p.split('\\')[-1], imports(p))
