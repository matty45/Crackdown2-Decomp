import json, sys, collections, random
# writes string-anchored pairs whose mnemonic sequence is identical but strict hash differs
a = [json.loads(l) for l in open(sys.argv[1])]
b = [json.loads(l) for l in open(sys.argv[2])]
sa = collections.Counter(tuple(r['strs']) for r in a if r['strs'])
sb = collections.defaultdict(list)
for r in b:
    if r['strs']:
        sb[tuple(r['strs'])].append(r)
pairs = []
for r in a:
    k = tuple(r['strs'])
    if r['strs'] and sa[k] == 1 and len(sb.get(k, [])) == 1 and r['n'] >= 6:
        o = sb[k][0]
        if r['hl'] == o['hl'] and r['hs'] != o['hs']:
            pairs.append((r['ea'], o['ea']))
random.seed(1)
random.shuffle(pairs)
json.dump(pairs[:400], open(sys.argv[3], 'w'))
print(len(pairs))
