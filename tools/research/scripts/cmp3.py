import json, sys, collections, re
S = sys.argv[1]
def load(n):
    return [json.loads(l) for l in open(S + '\\' + n + '_funcs.jsonl')]
cd2 = load('cd2'); refs = {n: load(n) for n in ('ruff', 'burn', 'skate')}
ia = collections.Counter(r['hl'] for r in cd2)
cov = {}
for n, ref in refs.items():
    ib = collections.Counter(r['hl'] for r in ref)
    byh = {r['hl']: r for r in ref}
    cov[n] = {r['ea']: byh[r['hl']]['name'] for r in cd2 if r['n'] >= 6 and ia[r['hl']] == 1 and ib.get(r['hl']) == 1}
only_sk = {k: v for k, v in cov['skate'].items() if k not in cov['ruff'] and k not in cov['burn']}
print('skate unique 1:1:', len(cov['skate']), ' only-from-skate:', len(only_sk))
ns = collections.Counter()
for v in cov['skate'].values():
    m = re.match(r'\?+\w*?@?([A-Za-z_]\w*)@@', v)
    ns[(v.split('@')[1] if v.startswith('?') and '@' in v else v.split('_')[0])[:24]] += 1
print('skate-matched name namespaces:', ns.most_common(25))
print('examples only-from-skate:', list(only_sk.values())[:25])
