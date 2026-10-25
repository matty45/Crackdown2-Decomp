"""Apply plan.json: merge the new entries into config/splits.txt (address order, existing entries verbatim) and create
the source files. Refuses to overwrite an existing source file.

usage: py -I tools/research/scaffold/apply.py <work dir>
"""
import json, os, re, sys, textwrap

S = sys.argv[1]
plan = json.load(open(os.path.join(S, 'plan.json')))
text = open('config/splits.txt', encoding='utf-8').read()
lines = text.split('\n')
first = next(i for i, l in enumerate(lines) if l.startswith('src/'))
header = lines[:first]
blocks, cur = [], None
for l in lines[first:]:
    if l.startswith('src/'):
        cur = [l]
        blocks.append(cur)
    elif cur is not None and l.strip():
        cur.append(l)


def start_of(block):
    m = re.search(r'text 0x([0-9A-Fa-f]+)', '\n'.join(block))
    return int(m.group(1), 16)


existing_paths = {b[0].strip() for b in blocks}
for p in plan:
    assert p['path'] not in existing_paths, p['path']
    assert not os.path.exists(p['path']), p['path']
    ev = '%s; %d marker%s (RetClassName, MakeNew, own vtable slots)' % (
        'RuffKing ' + p['ruff_obj'] if p['ruff_obj'] else 'not in RuffKing', p['markers'], '' if p['markers'] == 1 else 's')
    b = [p['path'], '  text 0x%08X 0x%08X   # auto: %s; %s' % (p['lo'], p['hi'], ', '.join(p['classes']), ev)]
    b += ['  init 0x%08X' % i for i in p['inits']] + ['  atexit 0x%08X' % x for x in p['atexits']]
    blocks.append(b)
blocks.sort(key=start_of)

note = '''#
# Entries whose text comment starts with "auto:" were set up automatically from CD2's own structure (scripts and method:
# tools/research/scaffold/). Per registered class: its RetClassName (which returns the registrar's class-name string)
# identifies its primary vtable; its markers are RetClassName, MakeNew and the vtable functions no other registered
# class shares. The range runs from the first marker to the end of the last, so it never goes past the evidence:
# functions just before or after it stay unassigned until a maintainer extends it. Every auto entry passed these checks:
# no other class's marker and no function of another RuffKing object inside; no overlap; initializers in text order.
# Classes whose RetClassName comes from the same RuffKing object are one file.'''
out = '\n'.join(header).rstrip('\n') + '\n' + note + '\n\n' + '\n\n'.join('\n'.join(b) for b in blocks) + '\n'
open('config/splits.txt', 'w', encoding='utf-8', newline='\n').write(out)

for p in plan:
    ns = ', '.join(p['namespaces']) if p['namespaces'] else 'unknown'
    para1 = ('Class%s: %s (namespace: %s). Set up automatically: no function is matched yet. The address range and the '
             'evidence for it are in config/splits.txt; %s.' % (
                 'es' if len(p['classes']) > 1 else '', ', '.join(p['classes']), ns,
                 'RuffKing\'s object for it is ' + p['ruff_obj'] if p['ruff_obj'] else 'the class is not in RuffKing'))
    para2 = ('Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared '
             'headers in include/ for any of its bases already declared there; read docs/matching-notes.md first. '
             'The open functions:')
    out = ['// ' + p['path'], '//'] + ['// ' + l for l in textwrap.wrap(para1, 117)] + ['//']
    out += ['// ' + l for l in textwrap.wrap(para2, 117)] + ['//     py -I tools/cd2.py tasks ' + p['path'], '']
    os.makedirs(os.path.dirname(p['path']), exist_ok=True)
    open(p['path'], 'w', encoding='utf-8', newline='\n').write('\n'.join(out))
print('splits.txt: %d entries; %d source files created' % (len(blocks), len(plan)))
