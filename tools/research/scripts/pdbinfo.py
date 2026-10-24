import struct, sys, json, collections

class MSF:
    def __init__(self, path):
        self.f = open(path, 'rb')
        hdr = self.f.read(56)
        assert hdr[:24] == b'Microsoft C/C++ MSF 7.00', hdr[:32]
        self.bs, _, self.nblocks, dirbytes, _, bmap = struct.unpack('<IIIIII', hdr[32:56])
        nd = (dirbytes + self.bs - 1) // self.bs
        self.f.seek(bmap * self.bs)
        dblocks = struct.unpack('<%dI' % nd, self.f.read(4 * nd))
        d = b''.join(self.block(b) for b in dblocks)[:dirbytes]
        n = struct.unpack('<I', d[:4])[0]
        sizes = struct.unpack('<%dI' % n, d[4:4 + 4 * n])
        off = 4 + 4 * n
        self.streams = []
        for s in sizes:
            if s == 0xFFFFFFFF:
                self.streams.append((0, []))
                continue
            k = (s + self.bs - 1) // self.bs
            self.streams.append((s, struct.unpack('<%dI' % k, d[off:off + 4 * k])))
            off += 4 * k

    def block(self, b):
        self.f.seek(b * self.bs)
        return self.f.read(self.bs)

    def stream(self, i):
        size, blocks = self.streams[i]
        return b''.join(self.block(b) for b in blocks)[:size]

def cstr(d, o):
    e = d.index(b'\0', o)
    return d[o:e].decode('latin-1'), e + 1

def parse(path):
    msf = MSF(path)
    dbi = msf.stream(3)
    (vsig, vhdr, age, gsi, build, psi, pdbdll, symrec, rbld, modsz, scsz, smsz, srcsz, tsmsz,
     mfc, dbgsz, ecsz, flags, machine, _) = struct.unpack('<iIIHHHHHHiiiiiIiiHHI', dbi[:64])
    info = dict(dbi_version=vhdr, link_build='%d.%d' % ((build >> 8) & 0x7F, build & 0xFF),
                pdbdll=pdbdll, flags=flags, incremental=bool(flags & 1), machine=hex(machine))
    mods = []
    o = 64
    end = 64 + modsz
    while o < end:
        sc = struct.unpack('<HhiiIHhII', dbi[o + 4:o + 32])
        mflags, symstream, symsz, c11, c13, nsrc = struct.unpack('<HHIIIH', dbi[o + 32:o + 50])
        name, p = cstr(dbi, o + 64)
        obj, p = cstr(dbi, p)
        mods.append(dict(name=name, obj=obj, symstream=symstream, symsz=symsz))
        o = (p + 3) & ~3
    # section contributions
    o = end
    ver = struct.unpack('<I', dbi[o:o + 4])[0]
    esz = 32 if ver == 0xeffe0000 + 20140516 else 28
    contribs = []
    for p in range(o + 4, o + scsz, esz):
        sec, _, off, size, ch, mi = struct.unpack('<HhiiIH', dbi[p:p + 18])
        contribs.append((sec, off, size, ch, mi))
    return msf, info, mods, contribs

def module_compile_info(msf, mod):
    if mod['symstream'] == 0xFFFF or mod['symsz'] == 0:
        return {}
    d = msf.stream(mod['symstream'])[:mod['symsz']]
    o = 4
    res = {}
    while o + 4 <= len(d) and len(res) < 3:
        ln, kind = struct.unpack('<HH', d[o:o + 4])
        rec = d[o + 4:o + 2 + ln]
        if kind == 0x113C:  # S_COMPILE3
            fl, mach = struct.unpack('<IH', rec[:6])
            v = struct.unpack('<8H', rec[6:22])
            res['compile'] = dict(lang=fl & 0xFF, ltcg=bool(fl >> 10 & 1), pgo=bool(fl >> 18 & 1),
                                  fe='%d.%d.%d.%d' % v[:4], be='%d.%d.%d.%d' % v[4:], ver=cstr(rec, 22)[0])
        elif kind == 0x1116:  # S_COMPILE2
            fl, mach = struct.unpack('<IH', rec[:6])
            v = struct.unpack('<6H', rec[6:18])
            res['compile'] = dict(lang=fl & 0xFF, ltcg=bool(fl >> 10 & 1), fe='%d.%d.%d' % v[:3], be='%d.%d.%d' % v[3:], ver=cstr(rec, 18)[0])
        elif kind == 0x113D:  # S_ENVBLOCK
            p = 1; kv = []
            while p < len(rec) and rec[p] != 0:
                s, p = cstr(rec, p)
                kv.append(s)
            res['env'] = dict(zip(kv[0::2], kv[1::2]))
        elif kind == 0x1101:  # S_OBJNAME
            res['objname'] = cstr(rec, 4)[0]
        o += 2 + ln
    return res

if __name__ == '__main__':
    path, out = sys.argv[1], sys.argv[2]
    msf, info, mods, contribs = parse(path)
    print(info, 'modules:', len(mods), 'contribs:', len(contribs))
    rows = []
    for i, m in enumerate(mods):
        ci = module_compile_info(msf, m)
        rows.append(dict(i=i, name=m['name'], obj=m['obj'], **ci))
    json.dump(dict(info=info, mods=rows, contribs=contribs), open(out, 'w'))
    # summaries
    comp = collections.Counter((r.get('compile', {}).get('be'), r.get('compile', {}).get('ltcg')) for r in rows)
    print('compiler backend / ltcg :', comp.most_common(10))
    libs = collections.Counter(r['obj'] for r in rows if r['obj'].lower().endswith('.lib'))
    print('objs from libs:', sum(libs.values()), ' distinct libs:', len(libs))
    cmds = collections.Counter()
    for r in rows:
        e = r.get('env', {})
        if 'cmd' in e:
            cmds[e['cmd']] += 1
    print('distinct cmd lines:', len(cmds))
    for c, n in cmds.most_common(6):
        print(n, c[:700])
