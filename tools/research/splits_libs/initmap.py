"""Initializer region (from 0x82F00000): each small function's code references (bl/b targets, addresses built with
lis/addi) -> the owner of the referenced function (a game file from config/splits.txt, or a library object from
libmap.json). A function whose references point at exactly one owner (ignoring shared runtime helpers referenced from
many owners) is assigned to it. usage: py -I initmap.py <work dir>"""
import sys, json, os, collections, bisect, struct
sys.path.insert(0, 'tools')
import cd2
from check_integrity import load_splits

W = sys.argv[1]
INIT = 0x82F00000
L = {int(a, 16): 'lib:%s' % v['mod'] for a, v in json.load(open(os.path.join(W, 'libmap.json')))['assign'].items()}
syms = cd2.jeff_symbols()
starts = sorted(syms)
owner = dict(L)
for f, e in load_splits(cd2.SPLITS).items():
    if e['text']:
        i = bisect.bisect_left(starts, e['text'][0])
        while i < len(starts) and starts[i] < e['text'][1]:
            owner[starts[i]] = f
            i += 1
    for k in ('hot', 'init', 'atexit'):
        for a in e[k]:
            owner[a] = f
fns = [a for a in starts if a >= INIT]


def refs(a):
    n = syms[a][1]
    ws = struct.unpack('>%dI' % (n // 4), cd2.read(a, n // 4 * 4))
    hi, out = {}, set()
    for i, w in enumerate(ws):
        op = w >> 26
        if op == 15 and (w >> 16) & 31 == 0:
            hi[(w >> 21) & 31] = (w & 0xFFFF) << 16
        elif op == 14 and (w >> 16) & 31 in hi:
            lo = w & 0xFFFF
            out.add((hi[(w >> 16) & 31] + (lo - 0x10000 if lo & 0x8000 else lo)) & 0xFFFFFFFF)
        elif op == 18:
            d = w & 0x03FFFFFC
            out.add((a + 4 * i + (d - 0x04000000 if d & 0x02000000 else d)) & 0xFFFFFFFF)
    return {r for r in out if r in syms}


targets = {a: refs(a) for a in fns}
# shared helpers: referenced from functions of many different owners
popular = collections.Counter(r for rs in targets.values() for r in rs)
helpers = {r for r, n in popular.items() if n >= 50}
got, multi, none = {}, 0, 0
for a, rs in targets.items():
    if a in owner:
        continue
    os_ = {owner[r] for r in rs if r not in helpers and r in owner}
    if len(os_) == 1:
        got[a] = os_.pop()
    elif os_:
        multi += 1
    else:
        none += 1
print('%d functions from %08X; %d already owned (game files); %d assigned by references, %d point at several owners, '
      '%d at none known' % (len(fns), INIT, sum(1 for a in fns if a in owner), len(got), multi, none))
print('helpers ignored: %d (referenced from 50+ functions)' % len(helpers))
json.dump({('%08X' % a): o for a, o in got.items()}, open(os.path.join(W, 'initmap.json'), 'w'))
