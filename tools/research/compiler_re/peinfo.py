import re, struct, sys
d = open(sys.argv[1], 'rb').read()
pe = struct.unpack_from('<I', d, 0x3C)[0]
mach, nsec, ts = struct.unpack_from('<HHI', d, pe + 4)
opt = pe + 24
magic = struct.unpack_from('<H', d, opt)[0]
imgbase = struct.unpack_from('<I', d, opt + 28)[0]
ddir = opt + 96
secs = []
so = opt + struct.unpack_from('<H', d, pe + 20)[0]
for i in range(nsec):
    name, vs, va, rs, rp = struct.unpack_from('<8sIIII', d, so + 40 * i)
    secs.append((name.rstrip(b'\0').decode(), vs, va, rs, rp))
def off(rva):
    for n, vs, va, rs, rp in secs:
        if va <= rva < va + max(vs, rs): return rp + rva - va
print('machine %04X timestamp %08X imagebase %08X sections %s' % (mach, ts, imgbase, [s[0] for s in secs]))
dbg_rva, dbg_sz = struct.unpack_from('<II', d, ddir + 6 * 8)
for k in range(dbg_sz // 28):
    e = off(dbg_rva) + 28 * k
    typ, sz, rva, ptr = struct.unpack_from('<12xIIII', d, e)
    if typ == 2 and d[ptr:ptr+4] == b'RSDS':
        guid = d[ptr+4:ptr+20]; age = struct.unpack_from('<I', d, ptr + 20)[0]
        name = d[ptr+24:d.index(b'\0', ptr+24)].decode()
        g = struct.unpack('<IHH8s', guid)
        gs = '%08X%04X%04X%s' % (g[0], g[1], g[2], g[3].hex().upper())
        print('pdb %s  guid+age %s%X' % (name, gs, age))
    else:
        print('debug entry type', typ)
# export count
exp_rva = struct.unpack_from('<I', d, ddir)[0]
if exp_rva:
    e = off(exp_rva); nf, nn = struct.unpack_from('<II', d, e + 20)
    print('exports: %d functions, %d names' % (nf, nn))
strs = set(m.group().decode() for m in re.finditer(rb'[\x20-\x7e]{4,}', d))
wstrs = set(m.group().decode('utf-16le') for m in re.finditer(rb'(?:[\x20-\x7e]\x00){4,}', d))
open(sys.argv[2], 'w').write('\n'.join(sorted(strs)) + '\n')
open(sys.argv[3], 'w').write('\n'.join(sorted(wstrs)) + '\n')
print('%d ascii strings, %d utf-16 strings' % (len(strs), len(wstrs)))
