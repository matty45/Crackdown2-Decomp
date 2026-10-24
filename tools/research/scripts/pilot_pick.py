import json, sys, collections, bisect, random
S = sys.argv[1]
pdb = json.load(open(S + r'\ruff_pdb.json'))
mods = pdb['mods']
code = sorted((c for c in pdb['contribs'] if c[3] & 0x20 and c[0] == 3), key=lambda c: c[1])
starts = [c[1] for c in code]
def mod_of(ea):
    off = ea - 0x822d0000
    i = bisect.bisect_right(starts, off) - 1
    return mods[code[i][4]] if i >= 0 and code[i][1] <= off < code[i][1] + code[i][2] else None
load = lambda n: [json.loads(l) for l in open(S + '\\' + n + '_funcs.jsonl')]
cd2, ruff = load('cd2'), load('ruff')
ia = collections.Counter(r['hs'] for r in cd2); ib = collections.Counter(r['hs'] for r in ruff)
rb = {r['hs']: r for r in ruff}
out = []
for r in cd2:
    if 14 <= r['n'] <= 45 and ia[r['hs']] == 1 and ib.get(r['hs']) == 1:
        o = rb[r['hs']]; m = mod_of(o['ea'])
        if m and not m['obj'].lower().endswith('.lib') and o['name'].startswith('?') and 1 <= len(o['calls']) <= 3:
            out.append((r['ea'], o['ea'], r['n'], o['name'], m['name'].split('\\')[-1]))
random.seed(7); random.shuffle(out)
print(len(out))
for x in out[:25]:
    print(hex(x[0]), hex(x[1]), x[2], x[3][:90], x[4])
