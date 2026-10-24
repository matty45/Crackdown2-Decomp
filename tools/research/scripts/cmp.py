import json, sys, collections
def load(p):
    return [json.loads(l) for l in open(p)]
a = load(sys.argv[1]); b = load(sys.argv[2])
def idx(recs, k):
    d = collections.defaultdict(list)
    for r in recs:
        d[r[k]].append(r)
    return d
small = 6  # ignore tiny funcs for uniqueness stats
for k in ('hs', 'hl'):
    ia = idx(a, k); ib = idx(b, k)
    uniq = sum(1 for h, l in ia.items() if len(l) == 1 and len(ib.get(h, [])) == 1 and l[0]['n'] >= small)
    anym = sum(len(l) for h, l in ia.items() if h in ib)
    print(k, 'unique 1:1 (n>=%d):' % small, uniq, ' any-match funcs:', anym, '/', len(a))
# string-set anchors
sb = collections.defaultdict(list)
for r in b:
    if r['strs']:
        sb[tuple(r['strs'])].append(r)
sa = collections.Counter(tuple(r['strs']) for r in a if r['strs'])
s1 = sum(1 for r in a if r['strs'] and sa[tuple(r['strs'])] == 1 and len(sb.get(tuple(r['strs']), [])) == 1)
print('funcs with strings:', sum(1 for r in a if r['strs']), ' unique string-set 1:1:', s1)
# size distribution of unmatched
ia = idx(a, 'hl'); ib = idx(b, 'hl')
um = [r for r in a if r['hl'] not in ib]
print('unmatched (loose):', len(um), ' insn total unmatched:', sum(r['n'] for r in um), ' of', sum(r['n'] for r in a))
