import struct, sys, collections
d = open(sys.argv[1], 'rb').read()
pe = struct.unpack('<I', d[0x3C:0x40])[0]
mach, nsec = struct.unpack('<HH', d[pe + 4:pe + 8])
optsz = struct.unpack('<H', d[pe + 20:pe + 22])[0]
opt = pe + 24
base = struct.unpack('<I', d[opt + 28:opt + 32])[0]
dd = opt + 96
dirs = [struct.unpack('<II', d[dd + i * 8:dd + i * 8 + 8]) for i in range(16)]
print('machine', hex(mach), 'base', hex(base), 'basereloc dir', [hex(x) for x in dirs[5]])
secs = []
for i in range(nsec):
    o = opt + optsz + i * 40
    name = d[o:o + 8].rstrip(b'\0').decode()
    vs, va, rs, ra = struct.unpack('<IIII', d[o + 8:o + 24])
    secs.append((name, va, vs, rs, ra))
    print('  %-10s va=%08x vsize=%08x raw=%08x' % (name, base + va, vs, rs))
rva, size = dirs[5]
print('file size %x, raw ptrs %s' % (len(d), [hex(s[4]) for s in secs]))
IMAGE_LAYOUT = False
E = sys.argv[2] if len(sys.argv) > 2 else '>'
def off(r):
    if IMAGE_LAYOUT:
        return r
    for n, va, vs, rs, ra in secs:
        if va <= r < va + max(vs, rs):
            return r - va + ra
types = collections.Counter(); bysec = collections.Counter()
o = off(rva); end = o + size
while o < end:
    page, bsz = struct.unpack(E + 'II', d[o:o + 8])
    if bsz == 0 or bsz > 0x10000:
        print('bad block size', hex(bsz), 'at', hex(o)); break
    for k in range((bsz - 8) // 2):
        e = struct.unpack(E + 'H', d[o + 8 + k * 2:o + 10 + k * 2])[0]
        t = e >> 12
        types[t] += 1
        if t:
            r = page + (e & 0xFFF)
            for n, va, vs, rs, ra in secs:
                if va <= r < va + vs:
                    bysec[n] += 1
    o += bsz
print('reloc types:', dict(types), ' by section:', dict(bysec))
