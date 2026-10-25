"""Namespaces for the accepted cores (from RuffKing and Burn names), and neighbouring cores with related names.

usage: py -I tools/research/scaffold/names.py <work dir>      (writes <work dir>/cores_ns.json)
"""
import collections, json, os, re, sys

S = sys.argv[1]
BS = chr(92)
cores = json.load(open(os.path.join(S, 'cores.json')))
names = {c['name'] for c in cores}

# every mangled name in RuffKing and Burn that names one of the classes: ?member@Class@NS1@NS2@@...
ns = collections.defaultdict(collections.Counter)
rcn_ea = {}
for fn in ('ruff_funcs.jsonl', 'burn_funcs.jsonl'):
    p = os.path.join(S, fn)
    if not os.path.exists(p):
        print('missing', fn)
        continue
    for line in open(p):
        f = json.loads(line)
        n = f.get('name') or ''
        m = re.match(r'^\?(\w+)@(\w+)@((?:\w+@)*)@', n)
        if not m or m.group(2) not in names:
            continue
        ns[m.group(2)]['::'.join(reversed([x for x in m.group(3).split('@') if x]))] += 1
        if m.group(1) == 'RetClassName' and fn.startswith('ruff'):
            rcn_ea[m.group(2)] = f['ea']
have = sum(1 for c in cores if ns[c['name']])
print('%d of %d classes have a namespace from RuffKing/Burn names' % (have, len(cores)))
amb = [(c['name'], dict(ns[c['name']])) for c in cores if len(ns[c['name']]) > 1]
print('ambiguous namespaces: %d, e.g. %s' % (len(amb), amb[:5]))
top = collections.Counter(ns[c['name']].most_common(1)[0][0] if ns[c['name']] else '(none)' for c in cores)
print('namespaces:', top.most_common(25))

# neighbours with a shared stem (cX and cXPrototype, cX and cXBase, ...)
cores.sort(key=lambda c: c['lo'])
pairs = []
for a, b in zip(cores, cores[1:]):
    sa, sb = re.sub(r'(Prototype|Base|Info|Data|Manager)$', '', a['name']), re.sub(r'(Prototype|Base|Info|Data|Manager)$', '', b['name'])
    if sa == sb or a['name'] in b['name'] or b['name'] in a['name']:
        pairs.append((a['name'], b['name'], b['lo'] - a['hi']))
print('\nneighbouring cores with related names: %d' % len(pairs))
for p in pairs[:15]:
    print('  %-34s %-38s gap %5d bytes' % p)
json.dump(dict(ns={k: dict(v) for k, v in ns.items()}, rcn_ea=rcn_ea), open(os.path.join(S, 'cores_ns.json'), 'w'))
