"""Fuzzy matcher against an arbitrary reference: fuzzy2.py <scratch> <ref_bytes.jsonl> <ref_pdb.json> <ref_text_base_hex> <out.json>"""
import json, re, struct, sys, collections, bisect, time
S, REF, PDB, BASE, OUT = sys.argv[1], sys.argv[2], sys.argv[3], int(sys.argv[4], 16), sys.argv[5]
src = open(S + r'\fuzzy.py').read()
# reuse tokeniser + CD2 loading only
head = src.split('# --- RuffKing\n')[0].replace("S = sys.argv[1]", "S = %r" % S)
exec(head)
ref, rname = {}, {}
for l in open(REF):
    r = json.loads(l)
    ref[r['ea']] = shingles(bytes.fromhex(r['b']), True)
    rname[r['ea']] = r['name']
pdb = json.load(open(PDB))
mods = pdb['mods']
codec = [c for c in pdb['contribs'] if c[3] & 0x20]
tsec = collections.Counter(c[0] for c in codec).most_common(1)[0][0]
code = sorted((c for c in codec if c[0] == tsec), key=lambda c: c[1])
starts = [c[1] for c in code]
def rkind(ea):
    off = ea - BASE
    i = bisect.bisect_right(starts, off) - 1
    if i < 0 or not (code[i][1] <= off < code[i][1] + code[i][2]):
        return None
    return 'lib' if mods[code[i][4]]['obj'].lower().endswith('.lib') else 'game'
df = collections.Counter()
for sh, n in ref.values():
    df.update(sh)
inv = collections.defaultdict(list)
for ea, (sh, n) in ref.items():
    for s in sh:
        if df[s] <= MAX_DF:
            inv[s].append(ea)
lab = {int(k): v for k, v in json.load(open(S + r'\cd2_labels.json')).items()}
ist = sorted(lab)
def label(ea):
    if ea in lab:
        return lab[ea]
    i = bisect.bisect_right(ist, ea) - 1
    return lab[ist[i]] if i >= 0 else 'UNKNOWN'
matches = {}
for ea, (sh, n) in cd2.items():
    if n < 6:
        continue
    cand = collections.Counter()
    for s in sh:
        if s in inv:
            cand.update(inv[s])
    if not cand:
        continue
    scored = sorted(((len(sh & ref[c][0]) / len(sh | ref[c][0]), c) for c, _ in cand.most_common(8)), reverse=True)
    best, bc = scored[0]
    second = scored[1][0] if len(scored) > 1 and rname[scored[1][1]] != rname[bc] else 0.0
    matches[ea] = (bc, best, second, rname[bc])
json.dump({str(k): v for k, v in matches.items()}, open(OUT, 'w'))
cd2_game = [ea for ea, (sh, n) in cd2.items() if n >= 6 and label(ea) in ('GAME', 'UNKNOWN')]
print('CD2 game-area functions (n>=6):', len(cd2_game))
for thr in (0.4, 0.5, 0.6, 0.7):
    c = collections.Counter()
    for ea in cd2_game:
        m = matches.get(ea)
        if m and m[1] >= thr and m[1] - m[2] >= 0.1:
            c[rkind(m[0])] += 1
    print('  thr=%.1f: matched game-area funcs -> ref game=%d lib=%d other=%d' % (thr, c['game'], c['lib'], c[None]))
