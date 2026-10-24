import json, sys, collections
S = sys.argv[1]
cd2 = sorted((json.loads(l) for l in open(S + r'\cd2_funcs.jsonl')), key=lambda r: r['ea'])
lab = {int(k): v for k, v in json.load(open(S + r'\cd2_labels.json')).items()}
runs = []; cur = []
prev = None
for r in cd2:
    l = lab.get(r['ea'])
    if l is None:
        if not cur:
            before = prev
        cur.append(r)
    else:
        if cur:
            runs.append((before, l, cur)); cur = []
        prev = l
if cur:
    runs.append((prev, None, cur))
tot = sum(sum(x['size'] for x in c) for _, _, c in runs)
runs.sort(key=lambda t: -sum(x['size'] for x in t[2]))
print('unknown runs:', len(runs), ' bytes: %.2f MB' % (tot / 1e6))
edge = collections.Counter()
for b, a, c in runs:
    edge[(b, a)] += sum(x['size'] for x in c)
print('bytes by (label before, label after):', [(k, round(v / 1e6, 2)) for k, v in edge.most_common(10)])
for b, a, c in runs[:12]:
    sz = sum(x['size'] for x in c)
    strs = [s for x in c for s in x['strs']][:6]
    names = [x['name'] for x in c if not x['name'].startswith('sub_')][:4]
    print('%s..%s %6.1fKB funcs=%4d  between %s | %s  names=%s strs=%s' % (hex(c[0]['ea']), hex(c[-1]['ea']), sz / 1e3, len(c), b, a, names, [s[:40] for s in strs]))
