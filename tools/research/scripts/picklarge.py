import json, re, sys, bisect, collections
S = sys.argv[1]
asm = open(S + r'\jeffwork2\out\asm\auto_02_821D0000_text.s').read()
cfun = {int(m.group(1), 16): int(m.group(2), 16) for m in re.finditer(r'# \.text:0x[0-9A-F]+ \| 0x([0-9A-F]{8}) \| size: 0x([0-9A-F]+)\n\.fn ', asm)}
lab = {int(k): v for k, v in json.load(open(S + r'\cd2_labels.json')).items()}
ist = sorted(lab)
def label(ea):
    if ea in lab: return lab[ea]
    i = bisect.bisect_right(ist, ea) - 1
    return lab[ist[i]] if i >= 0 else 'UNKNOWN'
fr = {int(k): v for k, v in json.load(open(S + r'\fz_ruff.json')).items()}
fb = {int(k): v for k, v in json.load(open(S + r'\fz_burn.json')).items()}
cd2 = {json.loads(l)['ea']: json.loads(l) for l in open(S + r'\cd2_funcs.jsonl')}
ref, cold = [], []
for ea, sz in cfun.items():
    n = sz // 4
    if not (150 <= n <= 460) or label(ea) not in ('GAME', 'UNKNOWN'):
        continue
    r = fr.get(ea); b = fb.get(ea)
    if r and r[1] >= 0.55 and r[1] - r[2] >= 0.1 and r[3].startswith('?'):
        ref.append((n, hex(ea), round(r[1], 2), r[3][:80]))
    elif (not r or r[1] < 0.2) and (not b or b[1] < 0.2) and ea in cd2 and cd2[ea]['strs']:
        cold.append((n, hex(ea), cd2[ea]['strs'][:3]))
print('with RuffKing reference:', len(ref))
for x in sorted(ref)[::max(1, len(ref) // 12)][:12]: print(' ', x)
print('cold:', len(cold))
for x in sorted(cold)[::max(1, len(cold) // 12)][:12]: print(' ', x)
