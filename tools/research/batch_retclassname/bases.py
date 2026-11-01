"""For the slot-11 RetClassName candidates: RuffKing's base class (from the header the file comment names) and whether
that base is modelled in include/. usage: py -I bases.py <repo root> <survey json> <out json>"""
import collections, json, os, re, sys

root, survey, out = sys.argv[1], sys.argv[2], sys.argv[3]
os.chdir(root)
rows = [r for r in json.load(open(survey)) if r['cls'] == r['string'] and 11 in r['slots']]
modelled = {}
for dp, _, fs in os.walk('include'):
    for f in fs:
        if f.endswith('.h'):
            p = os.path.join(dp, f).replace('\\', '/')
            t = open(p, errors='replace').read()
            for m in re.finditer(r'^\s*(?:class|struct)\s+(\w+)\s*(?::[^{;]*)?\{', t, re.M):
                modelled.setdefault(m.group(1), p)
res = []
for r in rows:
    head = open(r['file'], errors='replace').read(2500)
    m = re.search(r'(refs/\S+\.h)\.', head)
    ref = m.group(1) if m else None
    base = None
    if ref and os.path.exists(ref):
        t = open(ref, errors='replace').read()
        m = re.search(r'class %s\s*:\s*public\s+([\w:]+)' % re.escape(r['cls']), t)
        base = m.group(1) if m else None
    short = base.split('::')[-1] if base else None
    res.append(dict(r, ref=ref, rk_base=base, base_modelled=modelled.get(short)))
json.dump(res, open(out, 'w'), indent=1)
c = collections.Counter(x['rk_base'] for x in res)
print(len(res), 'candidates; RuffKing bases:', c.most_common(15))
print('base modelled in include/:', sum(bool(x['base_modelled']) for x in res), '; no RuffKing header/base:',
      sum(x['rk_base'] is None for x in res))
print('already declared:', [(x['cls'], x['declared']) for x in res if x['declared']])
