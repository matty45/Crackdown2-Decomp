import json, sys, collections, re
S = sys.argv[1]
def load(n):
    return [json.loads(l) for l in open(S + '\\' + n + '_funcs.jsonl')]
cd2 = load('cd2')
pat = re.compile(r'^(lua[A-Z_]\w*|luaL_\w+|luaV_\w+|luaD_\w+|luaO_\w+|luaS_\w+|luaZ_\w+|luaU_\w+|luaY_\w+|luaX_\w+|luaG_\w+|luaE_\w+|luaF_\w+|luaC_\w+|luaM_\w+|luaT_\w+|luaA_\w+|luaopen_\w+|lua_\w+|adler32|crc32|inflate\w*|deflate\w*|zcalloc|zcfree|inflate_fast|inflate_table|zlibVersion|uncompress|compress2?)$')
ia = collections.Counter(r['hl'] for r in cd2)
cd2_by_h = {r['hl']: r for r in cd2}
res = {}
for refn in ('ruff', 'burn', 'skate'):
    ref = load(refn)
    ib = collections.Counter(r['hl'] for r in ref)
    lib = [r for r in ref if pat.match(r['name'])]
    m = [(r['name'], cd2_by_h[r['hl']]['ea'], r['n']) for r in lib if ia.get(r['hl']) == 1 and ib[r['hl']] == 1]
    print(refn, 'lib funcs in ref:', len(lib), ' unique-hash-matched into CD2:', len(m))
    for name, ea, n in m:
        res.setdefault(name, (ea, n, refn))
json.dump(res, open(S + r'\libfunc_map.json', 'w'), indent=0)
print(len(res), sorted(res.items(), key=lambda x: -x[1][1])[:30])
