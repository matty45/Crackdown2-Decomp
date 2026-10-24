import json, sys, collections, bisect
S = sys.argv[1]
pdb = json.load(open(S + r'\ruff_pdb.json'))
mods = pdb['mods']
code = sorted((c for c in pdb['contribs'] if c[3] & 0x20 and c[0] == 3), key=lambda c: c[1])
starts = [c[1] for c in code]
def mod(ea):
    off = ea - 0x822d0000
    i = bisect.bisect_right(starts, off) - 1
    return code[i][4] if i >= 0 and code[i][1] <= off < code[i][1] + code[i][2] else None
load = lambda n: [json.loads(l) for l in open(S + '\\' + n + '_funcs.jsonl')]
cd2, ruff = load('cd2'), load('ruffnm')
rmod = {r['ea']: mod(r['ea']) for r in ruff}
isgame = lambda mi: mi is not None and not mods[mi]['obj'].lower().endswith('.lib')
sa = collections.Counter(tuple(r['strs']) for r in cd2 if r['strs'])
sb = collections.defaultdict(list)
for r in ruff:
    if r['strs']:
        sb[tuple(r['strs'])].append(r)
fewer = more = same = 0
xmod_inl = samemod_inl = 0
rby = {r['ea']: r for r in ruff}
for r in cd2:
    k = tuple(r['strs'])
    if r['strs'] and sa[k] == 1 and len(sb.get(k, [])) == 1 and r['n'] >= 8:
        o = sb[k][0]
        if not isgame(rmod[o['ea']]):
            continue
        a, b = len(r['calls']), len(o['calls'])
        fewer += a < b; more += a > b; same += a == b
        # which RuffKing callees are "missing" in CD2: classify by whether callee lives in same module
        if a < b:
            for c in o['calls']:
                cm = rmod.get(c)
                if cm is None: continue
                if cm == rmod[o['ea']]: samemod_inl += 1
                else: xmod_inl += 1
print('GAME pairs: CD2 fewer callees=%d more=%d same=%d' % (fewer, more, same))
print('callees of the "fewer" ruff funcs: same-module=%d cross-module=%d' % (samemod_inl, xmod_inl))
