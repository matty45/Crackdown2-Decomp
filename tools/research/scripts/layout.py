import json, sys, collections, bisect
S = sys.argv[1]
TEXT_BASE = int(sys.argv[2], 16)   # RuffKing .text start
pdb = json.load(open(S + r'\ruff_pdb.json'))
mods = pdb['mods']
code = [c for c in pdb['contribs'] if c[3] & 0x20]
secs = collections.Counter(c[0] for c in code)
tsec = secs.most_common(1)[0][0]
code = sorted((c for c in code if c[0] == tsec), key=lambda c: c[1])
starts = [c[1] for c in code]
def mod_of(ea):
    off = ea - TEXT_BASE
    i = bisect.bisect_right(starts, off) - 1
    if i >= 0 and code[i][1] <= off < code[i][1] + code[i][2]:
        return code[i][4]
    return None
load = lambda n: [json.loads(l) for l in open(S + '\\' + n + '_funcs.jsonl')]
cd2, ruff = load('cd2'), load('ruff')
print('text section index', tsec, 'contribs', len(code))
# validation sample
for r in ruff[5000:80000:15000]:
    m = mod_of(r['ea'])
    print('  ', r['name'][:60], '->', mods[m]['name'][-70:] if m is not None else None)
ia = collections.Counter(r['hl'] for r in cd2); ib = collections.Counter(r['hl'] for r in ruff)
rb = {r['hl']: r for r in ruff}
pairs = sorted((r['ea'], rb[r['hl']]['ea']) for r in cd2 if r['n'] >= 8 and ia[r['hl']] == 1 and ib[r['hl']] == 1)
seq = [(a, b, mod_of(b)) for a, b in pairs]
seq = [s for s in seq if s[2] is not None]
print('matched pairs with module:', len(seq))
def stats(order):
    same = sum(1 for x, y in zip(order, order[1:]) if x[2] == y[2])
    return same / max(1, len(order) - 1)
print('adjacent-same-module  in CD2 order: %.3f' % stats(seq))
print('adjacent-same-module  in RuffKing order: %.3f' % stats(sorted(seq, key=lambda s: s[1])))
# intra-module order agreement
bym = collections.defaultdict(list)
for a, b, m in seq:
    bym[m].append((a, b))
agree = tot = 0
for m, l in bym.items():
    l.sort()
    for (a1, b1), (a2, b2) in zip(l, l[1:]):
        tot += 1; agree += b1 < b2
print('intra-module consecutive order agreement: %.3f over %d pairs' % (agree / max(1, tot), tot))
# module contiguity in CD2: for each module, are its CD2 matches in one contiguous block (no other module's match in between)?
pos = {s[0]: i for i, s in enumerate(seq)}
contig = 0; multi = 0
for m, l in bym.items():
    if len(l) < 3:
        continue
    multi += 1
    idx = sorted(pos[a] for a, b in l)
    if idx[-1] - idx[0] + 1 == len(idx):
        contig += 1
print('modules (>=3 matches) fully contiguous in CD2: %d / %d' % (contig, multi))
# global module order agreement
first = {}
for i, (a, b, m) in enumerate(seq):
    first.setdefault(m, i)
mods_cd2 = sorted(first, key=first.get)
rfirst = {}
for a, b, m in sorted(seq, key=lambda s: s[1]):
    rfirst.setdefault(m, b)
rank = [rfirst[m] for m in mods_cd2]
inc = sum(1 for x, y in zip(rank, rank[1:]) if x < y)
print('consecutive module order agreement (CD2 vs RuffKing link order): %.3f' % (inc / max(1, len(rank) - 1)))
