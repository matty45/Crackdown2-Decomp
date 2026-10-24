"""Candidate low-level game TUs: RuffKing game objects for base namespaces, with how many functions are locatable in CD2."""
import json, sys, collections, bisect, re
S = sys.argv[1]
pdb = json.load(open(S + r'\ruff_pdb.json'))
mods = pdb['mods']
code = sorted((c for c in pdb['contribs'] if c[3] & 0x20 and c[0] == 3), key=lambda c: c[1])
starts = [c[1] for c in code]
def mod(ea):
    off = ea - 0x822D0000
    i = bisect.bisect_right(starts, off) - 1
    return code[i][4] if i >= 0 and code[i][1] <= off < code[i][1] + code[i][2] else None
ruff = {}
for l in open(S + r'\ruff_bytes.jsonl'):
    r = json.loads(l); ruff[r['ea']] = (r['name'], len(r['b']) // 8)
# CD2 locators: exact names applied + fuzzy matches (accepted)
applied = {}
for ea, name, src, conf in json.load(open(S + r'\name_apply_result.json'))['applied']:
    applied[name] = ea
fz = json.load(open(S + r'\fz_ruff.json'))
fz_inv = {}
for k, (bc, best, second, nm) in fz.items():
    if best >= 0.5 and best - second >= 0.1:
        fz_inv[bc] = (int(k), best)
per = collections.defaultdict(lambda: [0, 0, 0, 0, set()])
for ea, (name, n) in ruff.items():
    m = mod(ea)
    if m is None or mods[m]['obj'].lower().endswith('.lib'):
        continue
    ns = re.match(r'\?+[^@]+@(\w+)@', name)
    p = per[m]
    p[0] += 1; p[1] += n
    if name in applied: p[2] += 1
    elif ea in fz_inv: p[3] += 1
    if ns: p[4].add(ns.group(1))
rows = []
for m, (nf, ninsn, ex, fu, nss) in per.items():
    name = mods[m]['name'].split('\\')[-1]
    rows.append((name, nf, ninsn, ex, fu, sorted(nss)[:4]))
want = re.compile(r'(?i)(eventhandler|attribute|fun_runtime|funruntime|vec|matrix|list|allocator|string|hash|registrar|classfactory|cclass|rws)')
cand = [r for r in rows if want.search(r[0]) or any(want.search(x) for x in r[5])]
cand.sort(key=lambda r: (-(r[3] + r[4]) / max(1, r[1]), r[2]))
print('%-40s %5s %6s %6s %6s  %s' % ('object', 'funcs', 'insns', 'exact', 'fuzzy', 'classes'))
for r in cand[:30]:
    print('%-40s %5d %6d %6d %6d  %s' % r)
