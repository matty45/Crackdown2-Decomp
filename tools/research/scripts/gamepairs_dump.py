import json, sys, collections, bisect
S = sys.argv[1]
pdb = json.load(open(S + r'\ruff_pdb.json'))
mods = pdb['mods']
code = sorted((c for c in pdb['contribs'] if c[3] & 0x20 and c[0] == 3), key=lambda c: c[1])
starts = [c[1] for c in code]
def mod(ea):
    off = ea - 0x822d0000
    i = bisect.bisect_right(starts, off) - 1
    return mods[code[i][4]] if i >= 0 and code[i][1] <= off < code[i][1] + code[i][2] else None
load = lambda n: [json.loads(l) for l in open(S + '\\' + n + '_funcs.jsonl')]
cd2, ruff = load('cd2'), load('ruffnm')
sa = collections.Counter(tuple(r['strs']) for r in cd2 if r['strs'])
sb = collections.defaultdict(list)
for r in ruff:
    if r['strs']:
        sb[tuple(r['strs'])].append(r)
pairs = []
for r in cd2:
    k = tuple(r['strs'])
    if r['strs'] and sa[k] == 1 and len(sb.get(k, [])) == 1 and r['n'] >= 8:
        o = sb[k][0]; m = mod(o['ea'])
        if m and not m['obj'].lower().endswith('.lib'):
            pairs.append((r, o))
print('game string-anchored pairs:', len(pairs))
same_l = sum(1 for a, b in pairs if a['hl'] == b['hl'])
ratio = sorted(a['n'] / b['n'] for a, b in pairs)
print('loose identical: %d   insn ratio CD2/Ruff: p25=%.2f median=%.2f p75=%.2f' % (same_l, ratio[len(ratio)//4], ratio[len(ratio)//2], ratio[3*len(ratio)//4]))
json.dump([(a['ea'], b['ea'], a['n'], b['name']) for a, b in pairs], open(S + r'\game_pairs_all.json', 'w'))
print('saved', len(pairs))
