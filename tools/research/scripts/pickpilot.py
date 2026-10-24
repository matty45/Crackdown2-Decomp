import json, sys, collections, bisect, re
S = sys.argv[1]
cd2 = {json.loads(l)['ea']: json.loads(l) for l in open(S + r'\cd2_funcs.jsonl')}
ruff = [json.loads(l) for l in open(S + r'\ruffnm_funcs.jsonl')]
pdb = json.load(open(S + r'\ruff_pdb.json')); mods = pdb['mods']
code = sorted((c for c in pdb['contribs'] if c[3] & 0x20 and c[0] == 3), key=lambda c: c[1]); st = [c[1] for c in code]
def game(ea):
    off = ea - 0x822d0000; i = bisect.bisect_right(st, off) - 1
    return i >= 0 and code[i][1] <= off < code[i][1] + code[i][2] and not mods[code[i][4]]['obj'].lower().endswith('.lib')
ia = collections.Counter(r['hl'] for r in cd2.values()); ib = collections.Counter(r['hl'] for r in ruff); rb = {r['hl']: r for r in ruff}
c1 = [(r['n'], hex(r['ea']), hex(rb[r['hl']]['ea']), rb[r['hl']]['name'][:70]) for r in cd2.values() if ia[r['hl']] == 1 and ib.get(r['hl']) == 1 and game(rb[r['hl']]['ea']) and 35 <= r['n'] <= 90]
print('identical-modulo-markers candidates:'); [print(' ', x) for x in sorted(c1)[:8]]
fr = json.load(open(S + r'\fz_ruff.json')); fb = json.load(open(S + r'\fz_burn.json'))
lab = {int(k): v for k, v in json.load(open(S + r'\cd2_labels.json')).items()}
cold = [(r['n'], hex(r['ea']), r['strs'][:2]) for r in cd2.values() if lab.get(r['ea'], 'UNKNOWN') == 'UNKNOWN' and 30 <= r['n'] <= 60 and fr.get(str(r['ea']), [0, 0])[1] < 0.3 and fb.get(str(r['ea']), [0, 0])[1] < 0.3 and r['strs'] and len(r['calls']) >= 2]
print('cold candidates:'); [print(' ', x) for x in sorted(cold, key=lambda x: x[1])[:12]]

