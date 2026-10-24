import struct, sys
d = open(sys.argv[1], 'rb').read()
pe = struct.unpack('<I', d[0x3C:0x40])[0]
opt = pe + 24
base = struct.unpack('<I', d[opt + 28:opt + 32])[0]
dd = opt + 96
names = ['export','import','resource','exception','security','basereloc','debug','arch','gp','tls','loadcfg','bound','iat','delay','clr','res']
for i in range(16):
    rva, sz = struct.unpack('<II', d[dd + i * 8:dd + i * 8 + 8])
    if rva or sz:
        print('%-10s va=%08x size=%x' % (names[i], base + rva, sz))
