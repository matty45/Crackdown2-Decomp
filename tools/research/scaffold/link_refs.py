"""Add each class's reference dump (or its absence) to the set-up source files (after ref_dumps.py).

usage: py -I tools/research/scaffold/link_refs.py <work dir>
"""
import json, os, re, sys, textwrap

S = sys.argv[1]
n_ref = n_none = 0
for p in json.load(open(os.path.join(S, 'plan.json'))):
    ns = p['namespaces'][0] if len(p['namespaces']) == 1 else None
    refs, none = [], []
    for c in p['classes']:
        names = ([ns + '::' + c] if ns else []) + [c]
        found = None
        for pdb in ('ruffking', 'burn'):
            for name in names:
                f = 'include/ref/%s/%s.h' % (pdb, re.sub(r'[<>,* ]', '_', name.replace('::', '_')))
                if os.path.exists(f):
                    found = f
                    break
            if found:
                break
        (refs.append(found) if found else none.append(c))
    t = open(p['path'], encoding='utf-8').read()
    marker = '// Declare the class'
    assert marker in t and 'Reference layout' not in t, p['path']
    if refs:
        para = ('Reference layout from a later build of the same codebase (a starting point, not CD2\'s: verify it against '
                'CD2\'s code): %s.' % ', '.join(refs))
        n_ref += 1
    else:
        para = ('No reference layout: the class is in neither later build, so its layout comes from CD2\'s code alone.')
        n_none += 1
    if refs and none:
        para += ' None for %s.' % ', '.join(none)
    block = '\n'.join('// ' + l for l in textwrap.wrap(para, 117)) + '\n//\n'
    t = t.replace(marker, block + marker, 1)
    open(p['path'], 'w', encoding='utf-8', newline='\n').write(t)
print('files with a reference layout: %d; without: %d' % (n_ref, n_none))
