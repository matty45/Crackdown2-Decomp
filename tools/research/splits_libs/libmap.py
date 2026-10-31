"""Library object map, from the end of the game span to the end of .text.
Evidence per function: a code identity with a RuffKing function of >= 64 bytes (masked words unique in both builds, or
all copies in one RuffKing object), or a RuffKing name anchor of >= 64 bytes. Then:
  1. runs of <= 3 identified functions whose object has a run of >= 4 elsewhere are template/inline copies: relabelled
     to the surrounding object if both neighbours agree, otherwise dropped;
  2. contiguity: unidentified functions between two identified functions of one object belong to it;
  3. boundaries: the gap between two objects is walked from both sides by the sizes of the RuffKing functions after the
     first object's last match and before the second's first match.
Game files (config/splits.txt: text ranges, initializers and at-exit destructors) are fixed: nothing inside them is
assigned and no fill crosses them. usage: py -I libmap.py <work dir>   (writes libmap.json)"""
import sys, json, os, collections, bisect
sys.path.insert(0, 'tools')
import cd2
from check_integrity import load_splits

W = sys.argv[1]
LO = 0x82913700
MIN = 64
ident = json.load(open(os.path.join(W, 'ident.json')))
A = json.load(open(os.path.join(W, 'anchors.json')))
pdb = json.load(open(os.path.join(W, 'ruff_pdb.json')))
TEXT_SEC, TEXT_VA = 3, 0x822D0000
rk_by_mod = collections.defaultdict(list)
for c in pdb['contribs']:
    if c[0] == TEXT_SEC and c[3] & 0x20:
        rk_by_mod[c[4]].append((TEXT_VA + c[1], c[2]))
for m in rk_by_mod:
    rk_by_mod[m].sort()
rk_pos = {a: (m, i) for m, fs in rk_by_mod.items() for i, (a, n) in enumerate(fs)}
syms = cd2.jeff_symbols()
body = [a for a in sorted(syms) if a >= LO]
size = {a: syms[a][1] for a in body}
fixed = set()
for f, e in load_splits(cd2.SPLITS).items():
    if e['text']:
        fixed.update(a for a in body if e['text'][0] <= a < e['text'][1])
    fixed.update(e['init'] + e['atexit'] + e['hot'])
idn = {}
for a, v in A['anchors'].items():
    x = int(a, 16)
    if x >= LO and size.get(x, 0) >= MIN and x not in fixed:
        idn[x] = (v['mod'], None)
for a, v in ident.items():
    x = int(a, 16)
    if x >= LO and size.get(x, 0) >= MIN and x not in fixed:
        idn[x] = (v['mod'], int(v['ruff'], 16))
# only objects of .lib files: RuffKing's game objects match CD2 only on generic code (small initializers, helpers)
mods = A['mods']
idn = {a: v for a, v in idn.items() if mods[str(v[0])]['obj'].lower().endswith('.lib')}
seq = [a for a in body if a in idn]
lab = {a: idn[a][0] for a in seq}


def runs_of(seq):
    rs = []
    for a in seq:
        if rs and rs[-1][0] == lab[a]:
            rs[-1][1].append(a)
        else:
            rs.append([lab[a], [a]])
    return rs


for _ in range(3):
    rs = runs_of(seq)
    big = collections.defaultdict(int)
    for m, xs in rs:
        big[m] = max(big[m], len(xs))
    changed = 0
    for i, (m, xs) in enumerate(rs):
        if len(xs) <= 3 and big[m] >= 4 and big[m] > len(xs):
            # is this run the object's main run? no: another run of it is larger
            prev_m = rs[i - 1][0] if i else None
            next_m = rs[i + 1][0] if i + 1 < len(rs) else None
            for a in xs:
                if prev_m is not None and prev_m == next_m:
                    lab[a] = prev_m
                else:
                    del lab[a]
                changed += 1
    seq = [a for a in seq if a in lab]
    if not changed:
        break
assign = dict(lab)
how = {a: 'identified' for a in lab}
pos = {a: i for i, a in enumerate(body)}
known = [a for a in body if a in lab]
for a0, a1 in zip(known, known[1:]):
    m0, m1 = lab[a0], lab[a1]
    gap = body[pos[a0] + 1:pos[a1]]
    if not gap or any(a in fixed for a in gap):
        continue
    if m0 == m1:
        for a in gap:
            assign[a], how[a] = m0, 'contiguity'
        continue
    ra0, ra1 = idn.get(a0, (0, None))[1], idn.get(a1, (0, None))[1]
    tail = [n for _, n in rk_by_mod[m0][rk_pos[ra0][1] + 1:]] if ra0 in rk_pos and rk_pos[ra0][0] == m0 else []
    head = [n for _, n in rk_by_mod[m1][:rk_pos[ra1][1]]][::-1] if ra1 in rk_pos and rk_pos[ra1][0] == m1 else []
    k = 0
    while k < len(gap) and k < len(tail) and size[gap[k]] == tail[k]:
        k += 1
    l = 0
    while l < len(gap) - k and l < len(head) and size[gap[len(gap) - 1 - l]] == head[l]:
        l += 1
    for a in gap[:k]:
        assign[a], how[a] = m0, 'boundary-size'
    for a in gap[len(gap) - l:]:
        assign[a], how[a] = m1, 'boundary-size'
# consistency: objects in more than one block
blocks = []
for a in body:
    m = assign.get(a)
    if m is None:
        continue
    if blocks and blocks[-1][0] == m:
        blocks[-1][2] = a
    else:
        blocks.append([m, a, a])
per = collections.Counter(b[0] for b in blocks)
print('%d functions from %08X; %d fixed by game files; %d assigned (%.1f%%): %s' % (
    len(body), LO, len(fixed), len(assign), 100.0 * len(assign) / len(body), dict(collections.Counter(how.values()))))
print('%d objects; %d appear in more than one block' % (len(per), sum(1 for n in per.values() if n > 1)))
json.dump(dict(assign={('%08X' % a): dict(mod=m, how=how[a]) for a, m in assign.items()},
               multi=[str(m) for m, n in per.items() if n > 1]), open(os.path.join(W, 'libmap.json'), 'w'))
