import json, sys, collections
# usage: cmp2.py target.jsonl ref1.jsonl [ref2.jsonl ...]
def load(p):
    return [json.loads(l) for l in open(p)]
tgt = load(sys.argv[1])
refs = {p.split('\\')[-1].split('_')[0]: load(p) for p in sys.argv[2:]}
MIN = 6

def strpairs(a, b):
    sa = collections.Counter(tuple(r['strs']) for r in a if r['strs'])
    sb = collections.defaultdict(list)
    for r in b:
        if r['strs']:
            sb[tuple(r['strs'])].append(r)
    out = []
    for r in a:
        k = tuple(r['strs'])
        if r['strs'] and sa[k] == 1 and len(sb.get(k, [])) == 1 and r['n'] >= MIN:
            out.append((r, sb[k][0]))
    return out

covered = collections.defaultdict(set)
for name, ref in refs.items():
    pairs = strpairs(tgt, ref)
    same_hs = sum(1 for a, b in pairs if a['hs'] == b['hs'])
    same_hl = sum(1 for a, b in pairs if a['hl'] == b['hl'])
    same_n = sum(1 for a, b in pairs if a['n'] == b['n'])
    print('%-10s string-anchored pairs=%d  strict-identical=%.1f%%  loose-identical=%.1f%%  same-insn-count=%.1f%%' % (
        name, len(pairs), 100.0 * same_hs / max(1, len(pairs)), 100.0 * same_hl / max(1, len(pairs)), 100.0 * same_n / max(1, len(pairs))))
    ib = collections.Counter(r['hl'] for r in ref)
    ia = collections.Counter(r['hl'] for r in tgt)
    for r in tgt:
        if r['n'] >= MIN and ia[r['hl']] == 1 and ib.get(r['hl']) == 1:
            covered[name].add(r['ea'])
    print('%-10s unique 1:1 loose-hash matches (n>=%d): %d' % (name, MIN, len(covered[name])))
allc = set().union(*covered.values()) if covered else set()
print('union of unique matches across refs:', len(allc), '/', sum(1 for r in tgt if r['n'] >= MIN), 'target funcs with n>=%d' % MIN)
names = list(covered)
for i, x in enumerate(names):
    others = set().union(*(covered[y] for y in names if y != x)) if len(names) > 1 else set()
    print('  only-from %-10s %d' % (x, len(covered[x] - others)))
