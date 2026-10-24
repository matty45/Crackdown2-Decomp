"""best containment similarity of CD2 game-area functions vs RuffKing and Burn (game modules only)"""
import json, sys, collections, bisect
S = sys.argv[1]
src = open(S + r'\fuzzy2.py').read()
pre = src.split('ref, rname = {}, {}')[0].replace('S, REF, PDB, BASE, OUT = sys.argv[1], sys.argv[2], sys.argv[3], int(sys.argv[4], 16), sys.argv[5]', 'S = %r' % S)
exec(pre)

def load_ref(path, pdbp, base):
    ref = {}
    for l in open(path):
        r = json.loads(l)
        ref[r['ea']] = shingles(bytes.fromhex(r['b']), True)
    pdb = json.load(open(pdbp)); mods = pdb['mods']
    codec = [c for c in pdb['contribs'] if c[3] & 0x20]
    tsec = collections.Counter(c[0] for c in codec).most_common(1)[0][0]
    code = sorted((c for c in codec if c[0] == tsec), key=lambda c: c[1]); st = [c[1] for c in code]
    def game(ea):
        off = ea - base; i = bisect.bisect_right(st, off) - 1
        return i >= 0 and code[i][1] <= off < code[i][1] + code[i][2] and not mods[code[i][4]]['obj'].lower().endswith('.lib')
    ref = {ea: v for ea, v in ref.items() if game(ea) and v[1] >= 6}
    df = collections.Counter()
    for sh, n in ref.values():
        df.update(sh)
    inv = collections.defaultdict(list)
    for ea, (sh, n) in ref.items():
        for s in sh:
            if df[s] <= 60:
                inv[s].append(ea)
    return ref, inv

lab = {int(k): v for k, v in json.load(open(S + r'\cd2_labels.json')).items()}
ist = sorted(lab)
def label(ea):
    if ea in lab: return lab[ea]
    i = bisect.bisect_right(ist, ea) - 1
    return lab[ist[i]] if i >= 0 else 'UNKNOWN'
game = {ea: v for ea, v in cd2.items() if v[1] >= 6 and label(ea) in ('GAME', 'UNKNOWN')}
best = {}
for name, path, pdbp, base in (('ruff', S + r'\ruff_bytes.jsonl', S + r'\ruff_pdb.json', 0x822d0000),
                               ('burn', S + r'\burn_bytes.jsonl', S + r'\burn_pdb.json', 0x82470000)):
    ref, inv = load_ref(path, pdbp, base)
    for ea, (sh, n) in game.items():
        c = collections.Counter()
        for s in sh:
            if s in inv:
                c.update(inv[s])
        b = 0.0
        for r, _ in c.most_common(8):
            rs = ref[r][0]
            b = max(b, len(sh & rs) / max(1, min(len(sh), len(rs))))
        best[(name, ea)] = b
    print(name, 'done', flush=True)
tot_bytes = sum(cfun_d for cfun_d in [])
size = dict(cfun)
for thr in (0.5, 0.6, 0.7, 0.8):
    r = sum(1 for ea in game if best[('ruff', ea)] >= thr)
    b = sum(1 for ea in game if best[('burn', ea)] >= thr)
    u = [ea for ea in game if max(best[('ruff', ea)], best[('burn', ea)]) >= thr]
    print('containment>=%.1f: ruff=%d burn=%d union=%d of %d game-area funcs (%.1f%%; bytes %.1f%%)' % (
        thr, r, b, len(u), len(game), 100.0 * len(u) / len(game), 100.0 * sum(size[e] for e in u) / sum(size[e] for e in game)))
