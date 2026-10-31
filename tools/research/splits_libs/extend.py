"""Extend game files (config/splits.txt) over adjacent unassigned functions that only that file uses.
A function's users: the functions that call it or build its address, and the installers of every vtable that holds
it (the code that builds the table's address). A file's range is extended forward from its end, and backward from its
start, while the next function is unassigned and all its users (at least one) lie in that file. The library map
(libmap.json) counts as assigned. usage: py -I extend.py <work dir>   (writes extend.json: file -> new [start, end))"""
import sys, json, os, collections, bisect, struct
sys.path.insert(0, 'tools')
import cd2
from check_integrity import load_splits

W = sys.argv[1]
syms = cd2.jeff_symbols()
starts = sorted(syms)
pos = {a: i for i, a in enumerate(starts)}
sp = load_splits(cd2.SPLITS)
owner = {}
for f, e in sp.items():
    if e['text']:
        i = bisect.bisect_left(starts, e['text'][0])
        while i < len(starts) and starts[i] < e['text'][1]:
            owner[starts[i]] = f
            i += 1
    for k in ('hot', 'init', 'atexit'):
        for a in e[k]:
            owner[a] = f
L = json.load(open(os.path.join(W, 'libmap.json')))
lib_owned = {int(a, 16) for a in L['assign']} | {int(a, 16) for a in L.get('hot', {})} | {int(a, 16) for a in L.get('init', {})}


def func_of(addr):
    i = bisect.bisect_right(starts, addr) - 1
    return starts[i] if i >= 0 and addr < starts[i] + syms[starts[i]][1] else None


# users from code: calls and built addresses
users = collections.defaultdict(set)
exe = open(cd2.EXE, 'rb').read()
for a in starts:
    n = syms[a][1]
    try:
        b = cd2.read(a, n // 4 * 4)
    except Exception:
        continue
    ws = struct.unpack('>%dI' % (len(b) // 4), b)
    hi = {}
    for i, w in enumerate(ws):
        op = w >> 26
        if op == 15 and (w >> 16) & 31 == 0:
            hi[(w >> 21) & 31] = (w & 0xFFFF) << 16
        elif op == 14 and (w >> 16) & 31 in hi:
            lo = w & 0xFFFF
            t = (hi[(w >> 16) & 31] + (lo - 0x10000 if lo & 0x8000 else lo)) & 0xFFFFFFFF
            if t in syms and t != a:
                users[t].add(a)
        elif op == 18:
            d = w & 0x03FFFFFC
            t = (a + 4 * i + (d - 0x04000000 if d & 0x02000000 else d)) & 0xFFFFFFFF
            if t in syms and t != a:
                users[t].add(a)
# users from vtables: the installer of the table
refs = cd2.game_references()
for fn, slots in refs['vtables'].items():
    for table, slot, inst in slots:
        u = func_of(int(inst, 16))
        if u is not None:
            users[int(fn, 16)].add(u)


def sole_owner(a):
    us = users.get(a)
    if not us:
        return None
    os_ = {owner.get(u) for u in us}
    return os_.pop() if len(os_) == 1 and None not in os_ else None


ext, added = {}, 0
for f, e in sp.items():
    if not e['text']:
        continue
    s, t = e['text']
    i = pos.get(s)
    j = bisect.bisect_left(starts, t)
    if i is None:
        continue
    k = j
    while k < len(starts) and starts[k] not in owner and starts[k] not in lib_owned and sole_owner(starts[k]) == f \
            and not (0x821D0000 <= starts[k] < 0x823D0000) and starts[k] < 0x82F00000:
        k += 1
    h = i
    while h > 0 and starts[h - 1] not in owner and starts[h - 1] not in lib_owned and sole_owner(starts[h - 1]) == f \
            and starts[h - 1] >= 0x823D0000:
        h -= 1
    if k > j or h < i:
        new_s, new_t = starts[h], (starts[k - 1] + syms[starts[k - 1]][1]) if k > j else t
        ext[f] = ['0x%08X' % new_s, '0x%08X' % new_t, (i - h), (k - j)]
        added += (i - h) + (k - j)
print('%d files extended by %d functions in all (heads and tails used only by the file)' % (len(ext), added))
json.dump(ext, open(os.path.join(W, 'extend.json'), 'w'), indent=1)
for f, v in list(ext.items())[:8]:
    print('  %-55s %s..%s  +%d before, +%d after' % (f, v[0], v[1], v[2], v[3]))
