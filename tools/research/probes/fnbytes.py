import struct, sys, re
# usage: fnbytes.py exe map symbol -> prints hex bytes of the function (until next map symbol)
exe, mp, sym = sys.argv[1:4]
d = open(exe, 'rb').read()
pe = struct.unpack('<I', d[0x3C:0x40])[0]
nsec = struct.unpack('<H', d[pe + 6:pe + 8])[0]
optsz = struct.unpack('<H', d[pe + 20:pe + 22])[0]
base = struct.unpack('<I', d[pe + 24 + 28:pe + 24 + 32])[0]
secs = []
for i in range(nsec):
    o = pe + 24 + optsz + i * 40
    vs, va, rs, ra = struct.unpack('<IIII', d[o + 8:o + 24])
    secs.append((base + va, rs, ra))
funcs = sorted((int(m.group(2), 16), m.group(1)) for m in re.finditer(r'\s0003:[0-9a-f]+\s+(\S+)\s+([0-9a-f]{8})\s+f', open(mp).read()))
for i, (ea, n) in enumerate(funcs):
    if n == sym:
        end = funcs[i + 1][0]
        for va, rs, ra in secs:
            if va <= ea < va + rs:
                print(d[ra + ea - va: ra + end - va].hex())
