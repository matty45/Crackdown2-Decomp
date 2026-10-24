import json, sys, re, collections
S = sys.argv[1]
pairs = json.load(open(S + r'\pairs_ruff.json'))
A = json.load(open(S + r'\pairs_cd2_insns.json'))
B = json.load(open(S + r'\pairs_ruff_insns.json'))
cat = collections.Counter()
regdiff_mn = collections.Counter()
ex = []
for ea, eb in pairs:
    ia, ib = A[str(ea)], B[str(eb)]
    if len(ia) != len(ib):
        cat['len-mismatch'] += 1
        continue
    kinds = set(); regmap = {}
    for x, y in zip(ia, ib):
        if x == y:
            continue
        tx, ty = x.split(' '), y.split(' ')
        for p, q in zip(tx[1:], ty[1:]):
            if p == q:
                continue
            if p.startswith('r') and q.startswith('r'):
                kinds.add('reg'); regdiff_mn[tx[0]] += 1
            elif p.startswith('d') and q.startswith('d'):
                rp = p[p.index('('):]; rq = q[q.index('('):]
                kinds.add('displ' if rp == rq else 'displ+reg')
            elif p.startswith('#') and q.startswith('#'):
                kinds.add('imm')
            else:
                kinds.add('other')
    if not kinds:
        k = 'identical(after addr mask)'
    elif kinds <= {'displ', 'imm'}:
        k = 'offsets/immediates only'
    else:
        k = 'register differences (+%s)' % ','.join(sorted(kinds - {'reg'})) if 'reg' in kinds or 'displ+reg' in kinds else ','.join(sorted(kinds))
    cat[k] += 1
    if k.startswith('register') and len(ex) < 4:
        d = [(x, y) for x, y in zip(ia, ib) if x != y][:6]
        ex.append((hex(ea), hex(eb), d))
for k, v in cat.most_common():
    print('%5d  %s' % (v, k))
print('mnemonics with reg diffs:', regdiff_mn.most_common(12))
for e in ex:
    print(e)
