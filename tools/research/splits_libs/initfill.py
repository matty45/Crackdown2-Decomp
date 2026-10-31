"""Contiguity in the initializer region (from 0x82F00000). Each object's dynamic initializers are emitted together, and
so are its at-exit destructors, in object order. Anchors: game files' init/atexit entries (config/splits.txt), library
objects' init entries (libmap.json) and initmap.json (functions whose references point at one owner). A function
between two anchors of one owner, with no other owner's anchor between, belongs to that owner. Reports the fill and
checks the order: each owner's anchors should form one block. usage: py -I initfill.py <work dir>"""
import sys, json, os, collections, bisect
sys.path.insert(0, 'tools')
import cd2
from check_integrity import load_splits

W = sys.argv[1]
syms = cd2.jeff_symbols()
fns = [a for a in sorted(syms) if a >= 0x82F00000]
anchor = {}
for f, e in load_splits(cd2.SPLITS).items():
    for a in e['init'] + e['atexit']:
        anchor[a] = f
L = json.load(open(os.path.join(W, 'libmap.json')))
for a, m in L.get('init', {}).items():
    anchor[int(a, 16)] = 'lib:%s' % m
for a, o in json.load(open(os.path.join(W, 'initmap.json'))).items():
    anchor.setdefault(int(a, 16), o)
seq = [(a, anchor[a]) for a in fns if a in anchor]
runs = []
for a, o in seq:
    if runs and runs[-1][0] == o:
        runs[-1][2] = a
        runs[-1][3] += 1
    else:
        runs.append([o, a, a, 1])
blocks = collections.Counter(r[0] for r in runs)
print('%d anchors in %d runs over %d owners; %d owners in more than one run' % (
    len(seq), len(runs), len(blocks), sum(1 for n in blocks.values() if n > 1)))
fill = {}
pos = {a: i for i, a in enumerate(fns)}
for (a0, o0), (a1, o1) in zip(seq, seq[1:]):
    if o0 == o1:
        for a in fns[pos[a0] + 1:pos[a1]]:
            fill[a] = o0
print('contiguity adds %d functions; anchored + filled: %d of %d (%.1f%%)' % (
    len(fill), len(seq) + len(fill), len(fns), 100.0 * (len(seq) + len(fill)) / len(fns)))
json.dump({('%08X' % a): o for a, o in fill.items()}, open(os.path.join(W, 'initfill.json'), 'w'))
