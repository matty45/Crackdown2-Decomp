"""Align a RuffKing object file's functions (in address order) to a CD2 address region around an anchor match.

usage: tu_align.py <scratch> <obj-name-substring> [window]
Uses: ruff_pdb.json (contributions), ruff_bytes.jsonl, fz_ruff.json (anchors), name_apply_result.json (exact names),
      jeff function list + extracted exe for CD2 bytes.
Scores each pair by opcode-4-gram Jaccard plus size similarity; aligns with a monotone DP (gaps allowed both sides).
"""
import json, re, sys, struct, bisect, collections
S, KEY = sys.argv[1], sys.argv[2].lower()
WIN = int(sys.argv[3]) if len(sys.argv) > 3 else 60
src = open(S + r'\fuzzy.py').read()
exec(src.split('t0 = time.time()')[0].replace("S = sys.argv[1]", "S = %r" % S))  # tok, shingles, is_marker

pdb = json.load(open(S + r'\ruff_pdb.json'))
mods = pdb['mods']
code = sorted((c for c in pdb['contribs'] if c[3] & 0x20 and c[0] == 3), key=lambda c: c[1])
target_mods = {i for i, m in enumerate(mods) if KEY in m['name'].lower() and not m['obj'].lower().endswith('.lib')}
rfuncs = []
rb = {}
for l in open(S + r'\ruff_bytes.jsonl'):
    r = json.loads(l); rb[r['ea']] = r
starts = [c[1] for c in code]
for ea, r in rb.items():
    off = ea - 0x822D0000
    i = bisect.bisect_right(starts, off) - 1
    if i >= 0 and code[i][1] <= off < code[i][1] + code[i][2] and code[i][4] in target_mods:
        rfuncs.append(ea)
rfuncs.sort()
if not rfuncs:
    sys.exit('no RuffKing functions for %r' % KEY)
rsh = {ea: shingles(bytes.fromhex(rb[ea]['b']), True) for ea in rfuncs}

asm = open(S + r'\jeffwork2\out\asm\auto_02_821D0000_text.s').read()
cfun = sorted((int(m.group(1), 16), int(m.group(2), 16)) for m in re.finditer(r'# \.text:0x[0-9A-F]+ \| 0x([0-9A-F]{8}) \| size: 0x([0-9A-F]+)\n\.fn ', asm))
exe = open(S + r'\jeffwork2\orig\default.exe', 'rb').read()
cstarts = [ea for ea, sz in cfun]
csize = dict(cfun)

# anchors: CD2 functions confidently matched to any function of this object
fz = json.load(open(S + r'\fz_ruff.json'))
anch = [(int(k), v[0], v[1]) for k, v in fz.items() if v[0] in rsh and v[1] >= 0.5 and v[1] - v[2] >= 0.1]
for ea, name, s_, conf in json.load(open(S + r'\name_apply_result.json'))['applied']:
    for r in rfuncs:
        if rb[r]['name'] == name:
            anch.append((ea, r, 1.0))
if not anch:
    sys.exit('%s: %d RuffKing functions, no anchor in CD2' % (KEY, len(rfuncs)))
centre = sorted(a[0] for a in anch)[len(anch) // 2]
ci = bisect.bisect_left(cstarts, centre)
region = cstarts[max(0, ci - WIN): ci + WIN]

def csh(ea):
    o = 0x1C2C00 + ea - 0x821D0000
    return shingles(exe[o:o + csize[ea]], False)
cs = {ea: csh(ea) for ea in region}

def score(c, r):
    (a, na), (b, nb) = cs[c], rsh[r]
    j = len(a & b) / max(1, len(a | b))
    sz = min(na, nb) / max(1, na, nb)
    return 0.7 * j + 0.3 * sz if j > 0.05 or sz > 0.9 else 0.0

# monotone alignment DP (maximise total score; skipping either side costs 0)
R, C = rfuncs, region
dp = [[0.0] * (len(C) + 1) for _ in range(len(R) + 1)]
bt = [[0] * (len(C) + 1) for _ in range(len(R) + 1)]
for i in range(1, len(R) + 1):
    for j in range(1, len(C) + 1):
        s = score(C[j - 1], R[i - 1])
        best, how = dp[i - 1][j], 1
        if dp[i][j - 1] > best: best, how = dp[i][j - 1], 2
        if s > 0.35 and dp[i - 1][j - 1] + s > best: best, how = dp[i - 1][j - 1] + s, 3
        dp[i][j], bt[i][j] = best, how
pairs = []
i, j = len(R), len(C)
while i and j:
    if bt[i][j] == 3: pairs.append((C[j - 1], R[i - 1], score(C[j - 1], R[i - 1]))); i -= 1; j -= 1
    elif bt[i][j] == 1: i -= 1
    else: j -= 1
pairs.reverse()
print('%s: RuffKing functions=%d, anchors=%d, aligned=%d (%.0f%%)' % (KEY, len(R), len(anch), len(pairs), 100.0 * len(pairs) / len(R)))
if pairs:
    lo, hi = pairs[0][0], pairs[-1][0] + csize[pairs[-1][0]]
    print('  proposed CD2 range: 0x%08X-0x%08X (%d CD2 functions in range)' % (lo, hi, sum(1 for e in cstarts if lo <= e < hi)))
json.dump([[c, r, rb[r]['name'], s] for c, r, s in pairs], open(S + r'\tu_align_%s.json' % re.sub(r'\W', '_', KEY), 'w'))
for c, r, s in pairs[:40]:
    print('  %08X (%3d) <- %-70s %.2f' % (c, csize[c] // 4, rb[r]['name'][:70], s))
