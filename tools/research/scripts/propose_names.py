"""Name proposals for CD2 from unique 1:1 exact hash matches against RuffKing (markers stripped) and Burn."""
import json, sys, collections
S = sys.argv[1]
load = lambda n: [json.loads(l) for l in open(S + '\\' + n + '_funcs.jsonl')]
cd2 = load('cd2v2')
BAD = ('sub_', 'nullsub', 'j_', 'loc_', 'unknown_libname', 'def_', 'off_', 'locret_')

def unique_pairs(ref, key, min_n, same_n):
    ia = collections.Counter(r[key] for r in cd2)
    ib = collections.Counter(r[key] for r in ref)
    rb = {r[key]: r for r in ref}
    out = {}
    for r in cd2:
        if r['n'] >= min_n and ia[r[key]] == 1 and ib.get(r[key]) == 1:
            o = rb[r[key]]
            if same_n and o['n'] != r['n']:
                continue
            if o['name'].startswith(BAD):
                continue
            out[r['ea']] = o['name']
    return out

props = {}
for refname in ('ruffnm', 'burn'):
    ref = load(refname)
    src = 'RuffKing' if refname == 'ruffnm' else 'Burn'
    for key, min_n, same_n, conf in (('hs', 6, False, 'exact-strict'), ('hl', 8, True, 'exact-loose')):
        for ea, name in unique_pairs(ref, key, min_n, same_n).items():
            props.setdefault(ea, (name, src, conf))
# a reference name must not be proposed for two different CD2 functions
byname = collections.Counter(v[0] for v in props.values())
props = {ea: v for ea, v in props.items() if byname[v[0]] == 1}
json.dump({str(k): v for k, v in props.items()}, open(S + r'\name_proposals.json', 'w'))
c = collections.Counter((v[1], v[2]) for v in props.values())
print('proposals:', len(props), dict(c))
