import struct

ADDR32, PAIR = 0x02, 0x12


class Relocations(set):
    """Word offsets, with the absolute data relocations kept separate from instructions."""
    def __init__(self, records):
        records = list(records)
        super().__init__(off & ~3 for off, typ in records if typ != PAIR)
        self.absolute = {off for off, typ in records if typ == ADDR32 and off % 4 == 0}


def parse(path):
    d = open(path, 'rb').read()
    mach, nsec, _, symptr, nsym, opt, _ = struct.unpack('<HHIIIHH', d[:20])
    if mach == 0 and nsec == 0xFFFF:
        raise ValueError('anonymous/LTCG object: %s' % path)
    secs = []
    for i in range(nsec):
        o = 20 + opt + i * 40
        name, vs, va, size, praw, preloc, plin, nrel, nlin, ch = struct.unpack('<8sIIIIIIHHI', d[o:o + 40])
        relocs = []
        for r in range(nrel):
            ro = preloc + r * 10
            relocs.append(struct.unpack('<IIH', d[ro:ro + 10]))
        secs.append(dict(name=name.rstrip(b'\0'), data=d[praw:praw + size] if praw else b'', relocs=relocs, ch=ch))
    strtab = symptr + nsym * 18
    syms = []
    i = 0
    while i < nsym:
        o = symptr + i * 18
        raw, val, secno, typ, cls, naux = struct.unpack('<8sIhHBB', d[o:o + 18])
        if raw[:4] == b'\0\0\0\0':
            off = struct.unpack('<I', raw[4:])[0]
            nm = d[strtab + off:d.index(b'\0', strtab + off)]
        else:
            nm = raw.rstrip(b'\0')
        syms.append(dict(name=nm.decode('latin-1'), value=val, sec=secno, type=typ, cls=cls))
        i += 1 + naux
    return secs, syms

def functions(path):
    """yield (name, code_bytes, Relocations word offsets)"""
    secs, syms = parse(path)
    bysec = {}
    for s in syms:
        if s['sec'] > 0 and s['cls'] in (2, 3) and (s['type'] & 0x20 or secs[s['sec'] - 1]['ch'] & 0x20):
            if secs[s['sec'] - 1]['ch'] & 0x20 and not s['name'].startswith('.') and not s['name'].startswith('$'):
                bysec.setdefault(s['sec'], []).append(s)
    for secno, lst in bysec.items():
        sec = secs[secno - 1]
        lst.sort(key=lambda s: s['value'])
        for j, s in enumerate(lst):
            end = lst[j + 1]['value'] if j + 1 < len(lst) else len(sec['data'])
            rel = Relocations((off - s['value'], typ) for off, _, typ in sec['relocs']
                              if s['value'] <= off < end)
            yield s['name'], sec['data'][s['value']:end], rel

def compare(a, b, rel):
    """Compare code shape; ADDR32 destinations must also pass relocs.resolve. Returns (exact, ratio)."""
    n = max(len(a), len(b)) // 4
    if n == 0:
        return False, 0.0
    good = 0
    for w in range(min(len(a), len(b)) // 4):
        x, y = a[w * 4:w * 4 + 4], b[w * 4:w * 4 + 4]
        if x == y or w * 4 in getattr(rel, 'absolute', ()) or \
                (w * 4 in rel and (x[0] >> 2) == (y[0] >> 2)):
            good += 1
    return good == n and len(a) == len(b), good / n
