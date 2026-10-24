import json, sys, collections, bisect
S = sys.argv[1]
pdb = json.load(open(S + r'\ruff_pdb.json'))
mods = pdb['mods']
code = sorted((c for c in pdb['contribs'] if c[3] & 0x20 and c[0] == 3), key=lambda c: c[1])
starts = [c[1] for c in code]
def mod(ea):
    off = ea - 0x822d0000
    i = bisect.bisect_right(starts, off) - 1
    return code[i][4] if i >= 0 and code[i][1] <= off < code[i][1] + code[i][2] else None
load = lambda n: [json.loads(l) for l in open(S + '\\' + n + '_funcs.jsonl')]
cd2, ruff = load('cd2'), load('ruffnm')
isgame = lambda mi: mi is not None and not mods[mi]['obj'].lower().endswith('.lib')
sa = collections.Counter(tuple(r['strs']) for r in cd2 if r['strs'])
sb = collections.defaultdict(list)
for r in ruff:
    if r['strs']:
        sb[tuple(r['strs'])].append(r)
seq = []
for r in sorted(cd2, key=lambda r: r['ea']):
    k = tuple(r['strs'])
    if r['strs'] and sa[k] == 1 and len(sb.get(k, [])) == 1:
        o = sb[k][0]; m = mod(o['ea'])
        if isgame(m):
            seq.append((r['ea'], o['ea'], m))
print('game anchors:', len(seq))
adj = sum(1 for x, y in zip(seq, seq[1:]) if x[2] == y[2]) / (len(seq) - 1)
rs = sorted(seq, key=lambda s: s[1])
adj_r = sum(1 for x, y in zip(rs, rs[1:]) if x[2] == y[2]) / (len(rs) - 1)
print('adjacent same-module: CD2 order %.3f  RuffKing order %.3f' % (adj, adj_r))
bym = collections.defaultdict(list)
for a, b, m in seq:
    bym[m].append((a, b))
agree = tot = 0
for l in bym.values():
    l.sort()
    for (a1, b1), (a2, b2) in zip(l, l[1:]):
        tot += 1; agree += b1 < b2
print('intra-module order agreement %.3f over %d' % (agree / max(1, tot), tot))
# span check: max CD2 distance between functions of the same module (KB)
spans = sorted((max(a for a, b in l) - min(a for a, b in l)) / 1024 for l in bym.values() if len(l) >= 3)
print('per-module CD2 address span (KB) for modules with >=3 anchors: median=%.0f p90=%.0f n=%d' % (spans[len(spans)//2], spans[9*len(spans)//10], len(spans)))
