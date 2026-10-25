r"""Turn the accepted class cores into source files: merge neighbouring cores whose classes come from the same RuffKing
object, pick each file's path, and write the splits entries (with their evidence) and the plan.

usage: py -I tools/research/scaffold/plan.py <work dir>       (writes <work dir>/plan.json and splits_new.txt;
                                                               changes nothing in the repository)
"""
import bisect, collections, json, os, re, sys

sys.path.insert(0, 'tools')
import importlib.util
spec = importlib.util.spec_from_file_location('cd2', 'tools/cd2.py')
cd2 = importlib.util.module_from_spec(spec)
spec.loader.exec_module(cd2)
from check_integrity import load_splits

S = sys.argv[1]
BS = chr(92)
CODE = 0x20
syms = cd2.jeff_symbols()
cores = sorted(json.load(open(os.path.join(S, 'cores.json'))), key=lambda c: c['lo'])
nsd = json.load(open(os.path.join(S, 'cores_ns.json')))
A = json.load(open(os.path.join(S, 'anchors.json')))
base, sect = A['base'], A['sect']
pdb = json.load(open(os.path.join(S, 'ruff_pdb.json')))
mods = {m['i']: m for m in pdb['mods']}
starts = sorted((c[1] + base, c) for c in pdb['contribs'] if c[3] & CODE and c[0] == sect)
keys = [s for s, _ in starts]


def module_of(ea):
    i = bisect.bisect_right(keys, ea) - 1
    if i < 0:
        return None
    s, c = starts[i]
    return c[4] if s <= ea < s + c[2] else None


def objname(m):
    return (mods[m].get('objname') or mods[m]['name']).split(BS)[-1]


for c in cores:
    ea = nsd['rcn_ea'].get(c['name'])
    c['ruff_mod'] = module_of(ea) if ea else None
    ns = collections.Counter(nsd['ns'].get(c['name'], {}))
    top = ns.most_common(2)
    # a namespace only when it is clear: the most common by a margin of two to one
    c['ns'] = top[0][0] if top and (len(top) == 1 or top[0][1] >= 2 * top[1][1]) else None

# merge consecutive cores from the same RuffKing object
files = []
for c in cores:
    if files and c['ruff_mod'] is not None and files[-1]['classes'][-1]['ruff_mod'] == c['ruff_mod']:
        files[-1]['classes'].append(c)
        files[-1]['hi'] = c['hi']
    else:
        files.append(dict(classes=[c], lo=c['lo'], hi=c['hi']))

existing = load_splits('config/splits.txt')
used = {f.lower() for f in existing}
plan = []
for f in files:
    cls = f['classes']
    primary = min(cls, key=lambda c: (len(c['name']), c['name']))
    ns = primary['ns']
    d = ('src/' + ns.split('::')[0] + '/') if ns and re.match(r'^\w+(::\w+)*$', ns) else 'src/'
    path = d + primary['name'] + '.cpp'
    if path.lower() in used:
        path = d + primary['name'] + '_%08X.cpp' % f['lo']
    used.add(path.lower())
    rm = primary['ruff_mod']
    plan.append(dict(path=path, lo=f['lo'], hi=f['hi'], classes=[c['name'] for c in cls],
                     namespaces=sorted({c['ns'] for c in cls if c['ns']}),
                     ruff_obj=objname(rm) if rm is not None else None,
                     inits=sorted(c['init'] for c in cls), atexits=sorted(c['atexit'] for c in cls),
                     markers=sum(len(c['markers']) for c in cls),
                     funcs=sum(1 for a in syms if f['lo'] <= a < f['hi'])))
merged = [p for p in plan if len(p['classes']) > 1]
print('%d files from %d classes (%d merged files: %s)' % (len(plan), len(cores), len(merged),
      '; '.join('+'.join(p['classes']) for p in merged[:8])))
print('functions in the new ranges: %d; files with a RuffKing object name: %d; at src/ top level (no namespace): %d'
      % (sum(p['funcs'] for p in plan), sum(1 for p in plan if p['ruff_obj']), sum(1 for p in plan if p['path'].count('/') == 1)))

out = []
for p in plan:
    ev = '%s; %d marker%s (RetClassName, MakeNew, own vtable slots)' % (
        'RuffKing ' + p['ruff_obj'] if p['ruff_obj'] else 'not in RuffKing', p['markers'], '' if p['markers'] == 1 else 's')
    out.append('%s\n  text 0x%08X 0x%08X   # auto: %s; %s\n' % (p['path'], p['lo'], p['hi'], ', '.join(p['classes']), ev)
               + ''.join('  init 0x%08X\n' % i for i in p['inits']) + ''.join('  atexit 0x%08X\n' % x for x in p['atexits']))
open(os.path.join(S, 'splits_new.txt'), 'w', newline='\n').write('\n'.join(out))
json.dump(plan, open(os.path.join(S, 'plan.json'), 'w'), indent=1)
print('\n'.join(out[:3]))
