"""Derive CD2 source-file ranges from RuffKing's PDB: every CD2 function matched by name to a RuffKing function inherits
that function's object; a non-COMDAT (ordinary member) function is strong evidence of its object. Outside the hot
region the linker lays out each object contiguously, so an object's strong anchors in CD2 span part of its file.

usage: py -I tools/research/scaffold/anchors.py <work dir>      (writes <work dir>/anchors.json)
"""
import bisect, collections, csv, json, os, re, sys

S = sys.argv[1]
OUT = os.path.join(S, 'anchors.json')
HOT = (0x821D0000, 0x823D0000)
INIT_REGION = 0x82F00000          # dynamic initializers and at-exit destructors from here on
COMDAT = 0x1000                   # IMAGE_SCN_LNK_COMDAT
CODE = 0x20                       # IMAGE_SCN_CNT_CODE

pdb = json.load(open(os.path.join(S, 'ruff_pdb.json')))
mods = {m['i']: m for m in pdb['mods']}
code = [c for c in pdb['contribs'] if c[3] & CODE]          # [section, offset, size, characteristics, module]

# RuffKing functions (IDB with PDB names)
rfun, rname = {}, collections.defaultdict(list)
for line in open(os.path.join(S, 'ruff_funcs.jsonl')):
    f = json.loads(line)
    rfun[f['ea']] = f
    if f.get('name'):
        rname[f['name']].append(f['ea'])

# the code section's address: the most common (function address - contribution offset) over equal sizes
by_size = collections.defaultdict(list)
for c in code:
    by_size[c[2]].append(c)
votes = collections.Counter()
for ea, f in list(rfun.items())[::50]:
    for c in by_size.get(f['size'], [])[:40]:
        votes[(c[0], ea - c[1])] += 1
(sect, base), n = votes.most_common(1)[0]
print('code section %d at %08X (%d votes; next %s)' % (sect, base, n, votes.most_common(3)[1:]))

starts = sorted((c[1] + base, c) for c in code if c[0] == sect)
keys = [s for s, _ in starts]


def contrib_of(ea):
    i = bisect.bisect_right(keys, ea) - 1
    if i < 0:
        return None
    s, c = starts[i]
    return c if s <= ea < s + c[2] else None


# check the mapping: a function's contribution should start at the function (one COMDAT per function under /Gy)
ok = sum(1 for ea in list(rfun)[::25] if (contrib_of(ea) or [0, -1])[1] + base == ea)
print('mapping check: %d of %d sampled functions start their own contribution' % (ok, len(list(rfun)[::25])))

BS = chr(92)
game = lambda m: any(BS + k + BS in (mods[m].get('objname') or mods[m]['name']) for k in ('Projects', 'Game'))

# CD2 functions with a RuffKing name -> (module, comdat)
anchors = {}
amb = 0
for row in csv.DictReader(open('data/symbols/auto_names_2026-10-23.csv')):
    if row['source'] != 'RuffKing':
        continue
    eas = rname.get(row['name'], [])
    found = {(c[4], bool(c[3] & COMDAT)) for c in (contrib_of(e) for e in eas) if c}
    if len(found) != 1:
        amb += 1
        continue
    mod, comdat = found.pop()
    anchors[int(row['address'], 16)] = dict(mod=mod, comdat=comdat, name=row['name'], match=row['match'])
print('%d CD2 functions anchored to a RuffKing object (%d ambiguous or unmapped)' % (len(anchors), amb))
json.dump(dict(base=base, sect=sect, anchors={'%08X' % k: v for k, v in anchors.items()},
               mods={i: dict(name=m['name'], objname=m.get('objname') or m['name']) for i, m in mods.items()}),
          open(OUT, 'w'))
