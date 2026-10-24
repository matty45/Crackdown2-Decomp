import json, sys, collections
S = sys.argv[1]
load = lambda n: [json.loads(l) for l in open(S + '\\' + n + '_funcs.jsonl')]
cd2, ruff = load('cd2'), load('ruff')
sa = collections.Counter(tuple(r['strs']) for r in cd2 if r['strs'])
sb = collections.defaultdict(list)
for r in ruff:
    if r['strs']:
        sb[tuple(r['strs'])].append(r)
fewer = more = same = 0; dn = []
for r in cd2:
    k = tuple(r['strs'])
    if r['strs'] and sa[k] == 1 and len(sb.get(k, [])) == 1 and r['n'] >= 8:
        o = sb[k][0]
        if r['hl'] == o['hl']:
            continue
        a, b = len(r['calls']), len(o['calls'])
        if a < b: fewer += 1
        elif a > b: more += 1
        else: same += 1
        dn.append(r['n'] - o['n'])
print('string-anchored non-identical pairs: CD2 fewer callees=%d  more=%d  same=%d' % (fewer, more, same))
dn.sort()
print('insn-count delta CD2-Ruff: median=%d  p10=%d  p90=%d' % (dn[len(dn)//2], dn[len(dn)//10], dn[9*len(dn)//10]))
