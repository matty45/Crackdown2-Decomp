"""Bring batch-2 work into the repo: copy header/source, compile, and add manifest entries for verified functions."""
import glob, json, os, re, subprocess, sys
ROOT = r'<repo>'
sys.path.insert(0, os.path.join(ROOT, 'tools'))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'research', 'scripts'))
import coff
from verify_src import FLAGS, XDK, BIN, pe_reader

S, exe = sys.argv[1], sys.argv[2]
read, _ = pe_reader(open(exe, 'rb').read())
ITEMS = [('cChaseBehaviour', 'AI', S + r'\batch2\cChaseBehaviour_r2\cChaseBehaviour'),
         ('cFlocket', 'Equip', S + r'\batch2\cFlocket\cFlocket'),
         ('cHelicopterController', 'VEHICLE_CONTROL', S + r'\batch2\cHelicopterController\cHelicopterController')]
env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'], INCLUDE=os.path.join(XDK, 'include', 'xbox') + ';' + os.path.join(ROOT, 'include'))
mpath = os.path.join(ROOT, 'config', 'matched_functions.json')
manifest = json.load(open(mpath))
for cls, ns, p in ITEMS:
    res = json.load(open(os.path.join(p, 'results.json')))
    info = {f['id']: f for f in res['functions']}
    h = open(os.path.join(p, 'work', cls + '.h')).read()
    c = open(os.path.join(p, 'work', cls + '.cpp')).read()
    c = c.replace('#include "%s.h"' % cls, '#include "%s/%s.h"' % (ns, cls))
    rel_src = 'src/%s/%s.cpp' % (ns, cls)
    os.makedirs(os.path.join(ROOT, 'include', ns), exist_ok=True)
    os.makedirs(os.path.join(ROOT, 'src', ns), exist_ok=True)
    mapping = {}
    for l in open(os.path.join(p, 'work', 'map.txt')):
        q = l.split()
        if len(q) >= 2 and not l.startswith('#'):
            mapping[q[0]] = q[1]
    obj = os.path.join(p, 'work', 'repo_check.obj')
    # write the files, compile the repo copy
    open(os.path.join(ROOT, 'include', ns, cls + '.h'), 'w', newline='\n').write(h)
    open(os.path.join(ROOT, rel_src), 'w', newline='\n').write(c)
    r = subprocess.run([os.path.join(BIN, 'cl.exe')] + FLAGS + ['/Fo' + obj, os.path.join(ROOT, rel_src)], env=env, capture_output=True, text=True)
    if r.returncode:
        print(cls, 'COMPILE ERROR', (r.stdout + r.stderr)[-800:])
        continue
    funcs = list(coff.functions(obj))
    entries, used, n_exact, n_wip = [], set(), 0, 0
    for d in sorted(glob.glob(os.path.join(p, 'targets', 'F*_*'))):
        k, addr = os.path.basename(d).split('_')
        f = info.get(k)
        if not f or f.get('belongs') is not True:
            continue
        va = int(addr, 16)
        tgt = bytes.fromhex(open(os.path.join(d, 'target.hex')).read().strip())
        cands = [i for i, (n, code, rl) in enumerate(funcs) if k in mapping and mapping[k] in n]
        if not cands:  # unmapped or unresolved map entry: only accept a byte-exact, otherwise unused function
            cands = [i for i, (n, code, rl) in enumerate(funcs) if i not in used and coff.compare(code, tgt, rl)[0]]
        if not cands:
            continue
        i = cands[0]
        name, code, rl = funcs[i]
        exact, ratio = coff.compare(code, tgt, rl)
        prefix = name[:name.index('@@') + 2] if '@@' in name else name
        sym = prefix if sum(1 for n, _, _ in funcs if prefix in n) == 1 else name
        e = {'address': '0x%08X' % va, 'size': len(tgt), 'symbol': sym}
        if exact:
            used.add(i)
            n_exact += 1
        elif ratio >= 0.4:
            e['matching'] = False
            e['note'] = '%.0f%%: %s' % (100 * ratio, (f.get('notes') or '').replace('"', "'")[:140])
            n_wip += 1
        else:
            continue
        entries.append(e)
    entries.sort(key=lambda e: ('matching' in e, e['address']))
    manifest['files'][rel_src] = entries
    head = ('// %s/%s.cpp: %s of Crackdown 2.\n// Measurement batch 2 (2026-10-23, Sonnet 5.5): %d functions byte-exact, %d tracked as work in progress\n'
            '// (config/matched_functions.json). Unknown bases and callees are stand-ins named in the header; out-of-line\n'
            '// callees without a known name are declared as Ext_<address>.\n') % (ns, cls, cls, n_exact, n_wip)
    open(os.path.join(ROOT, rel_src), 'w', newline='\n').write(head + c)
    print('%-22s -> %s: %d exact, %d work in progress' % (cls, rel_src, n_exact, n_wip))

# write the manifest in its one-entry-per-line style
out = ['{', '  "comment": %s,' % json.dumps(manifest['comment']), '  "files": {']
files = list(manifest['files'].items())
for fi, (src, entries) in enumerate(files):
    out.append('    %s: [' % json.dumps(src))
    for ei, e in enumerate(entries):
        out.append('      ' + json.dumps(e) + (',' if ei + 1 < len(entries) else ''))
    out.append('    ]' + (',' if fi + 1 < len(files) else ''))
out += ['  }', '}']
open(mpath, 'w', newline='\n').write('\n'.join(out) + '\n')
print('manifest: %d files, %d entries' % (len(files), sum(len(v) for _, v in files)))
