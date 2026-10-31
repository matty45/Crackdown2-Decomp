"""CD2 functions -> RuffKing object, through names: data/symbols/auto_names (CD2 address -> RuffKing name), RuffKing's
public symbols (name -> section:offset) and its section contributions (section:offset -> module, COMDAT flag).
usage: py -I anchors2.py <ruffking pdb> <ruff_pdb.json> <out anchors.json>"""
import sys, struct, json, bisect, csv, collections, os
sys.path.insert(0, 'tools/research/scripts')
from pdbinfo import MSF

pdb_path, info, out = sys.argv[1:4]
msf = MSF(pdb_path)
dbi = msf.stream(3)
symrec = struct.unpack_from('<H', dbi, 20)[0]
recs = msf.stream(symrec)
pubs = {}
o = 0
while o + 4 <= len(recs):
    ln, kind = struct.unpack_from('<HH', recs, o)
    if kind == 0x110E:  # S_PUB32
        flags, off, seg = struct.unpack_from('<IIH', recs, o + 4)
        name = recs[o + 14:recs.index(b'\0', o + 14)].decode('latin-1')
        pubs[name] = (seg, off)
    o += 2 + ln
print('%d public symbols' % len(pubs))

pdb = json.load(open(info))
mods = pdb['mods']
code = [c for c in pdb['contribs'] if c[3] & 0x20]
by_sec = collections.defaultdict(list)
for c in code:
    by_sec[c[0]].append(c)
for s in by_sec:
    by_sec[s].sort(key=lambda c: c[1])
keys = {s: [c[1] for c in v] for s, v in by_sec.items()}


def contrib(seg, off):
    v = by_sec.get(seg)
    if not v:
        return None
    i = bisect.bisect_right(keys[seg], off) - 1
    if i >= 0 and v[i][1] <= off < v[i][1] + v[i][2]:
        return v[i]
    return None


anchors, miss = {}, collections.Counter()
for row in csv.DictReader(open('data/symbols/auto_names_2026-10-23.csv')):
    if row['source'] != 'RuffKing':
        continue
    p = pubs.get(row['name'])
    if not p:
        miss['no public'] += 1
        continue
    c = contrib(*p)
    if not c:
        miss['no contribution'] += 1
        continue
    m = mods[c[4]]
    anchors['%08X' % int(row['address'], 16)] = dict(mod=c[4], comdat=bool(c[3] & 0x1000), name=row['name'],
                                                     match=row['match'], ruff='%d:%08X' % p)
print('%d anchors; missing: %s' % (len(anchors), dict(miss)))
json.dump(dict(anchors=anchors, mods={i: dict(name=m['name'], obj=m.get('obj') or m.get('objname') or m['name'])
                                      for i, m in enumerate(mods)}), open(out, 'w'))
strong = sum(1 for a in anchors.values() if not a['comdat'])
print('%d strong (non-COMDAT), %d COMDAT' % (strong, len(anchors) - strong))
