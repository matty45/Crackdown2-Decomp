import json, re, sys, bisect
S = sys.argv[1]
asm = open(S + r'\jeffwork2\out\asm\auto_02_821D0000_text.s').read()
cfun = sorted((int(m.group(1), 16), int(m.group(2), 16)) for m in re.finditer(r'# \.text:0x[0-9A-F]+ \| 0x([0-9A-F]{8}) \| size: 0x([0-9A-F]+)\n\.fn ', asm))
lab = {int(k): v for k, v in json.load(open(S + r'\cd2_labels.json')).items()}
ist = sorted(lab)
def label(ea):
    if ea in lab: return lab[ea]
    i = bisect.bisect_right(ist, ea) - 1
    return lab[ist[i]] if i >= 0 else 'UNKNOWN'
g = sorted(sz // 4 for ea, sz in cfun if label(ea) in ('GAME', 'UNKNOWN'))
tot = sum(g)
def pct(p): return g[int(len(g) * p)]
print('game-area functions: %d, instructions: %d' % (len(g), tot))
print('size (insns) p25=%d median=%d p75=%d p90=%d p99=%d max=%d' % (pct(.25), pct(.5), pct(.75), pct(.9), pct(.99), g[-1]))
for lo, hi in ((0, 10), (10, 30), (30, 60), (60, 150), (150, 400), (400, 10**9)):
    sel = [x for x in g if lo <= x < hi]
    print('  %5d-%-6s funcs=%6d (%4.1f%%)  insns=%7d (%4.1f%%)' % (lo, hi if hi < 10**9 else 'inf', len(sel), 100.0 * len(sel) / len(g), sum(sel), 100.0 * sum(sel) / tot))
