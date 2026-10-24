"""Fuzzy function matcher: CD2 (jeff function list, bytes from the extracted exe) vs RuffKing (IDA dump, trace markers stripped).
Register-free opcode tokens -> 4-gram shingles -> inverted index on rare shingles -> Jaccard ranking."""
import json, re, struct, sys, collections, bisect, time

S = sys.argv[1]
K = 4
MAX_DF = 40

def tok(w):
    op = w >> 26
    if op == 31:
        return (31 << 16) | ((w >> 1) & 0x3FF)
    if op in (59, 63):
        xo5 = (w >> 1) & 31
        return (op << 16) | (xo5 if xo5 >= 16 else 0x100 | ((w >> 1) & 0x3FF))
    if op == 19:
        return (19 << 16) | ((w >> 1) & 0x3FF)
    if op == 30:
        return (30 << 16) | ((w >> 2) & 7)
    if op in (58, 62, 16, 18):
        return (op << 16) | (w & 3)
    if op == 4:
        return (4 << 16) | (w & 0x7FF)
    return op << 16

def is_marker(w):
    if (w >> 26) == 31 and ((w >> 1) & 0x3FF) == 444:
        rs = (w >> 21) & 31
        return rs == (w >> 16) & 31 == (w >> 11) & 31 and rs in (13, 14)
    return False

def shingles(b, strip):
    ws = [struct.unpack_from('>I', b, i)[0] for i in range(0, len(b) - 3, 4)]
    if strip:
        ws = [w for w in ws if not is_marker(w)]
    t = [tok(w) for w in ws]
    if len(t) < K:
        return frozenset([hash(tuple(t))]), len(t)
    return frozenset(hash(tuple(t[i:i + K])) for i in range(len(t) - K + 1)), len(t)

t0 = time.time()
# --- CD2 functions from jeff
asm = open(S + r'\jeffwork2\out\asm\auto_02_821D0000_text.s').read()
cfun = sorted((int(m.group(1), 16), int(m.group(2), 16)) for m in
              re.finditer(r'# \.text:0x[0-9A-F]+ \| 0x([0-9A-F]{8}) \| size: 0x([0-9A-F]+)\n\.fn ', asm))
exe = open(S + r'\jeffwork2\orig\default.exe', 'rb').read()
TEXT_VA, TEXT_RAW = 0x821D0000, 0x1C2C00
cd2 = {}
for ea, sz in cfun:
    o = TEXT_RAW + ea - TEXT_VA
    cd2[ea] = shingles(exe[o:o + sz], False)
# --- RuffKing
ruff, rname = {}, {}
for l in open(S + r'\ruff_bytes.jsonl'):
    r = json.loads(l)
    ruff[r['ea']] = shingles(bytes.fromhex(r['b']), True)
    rname[r['ea']] = r['name']
print('loaded cd2=%d ruff=%d in %.0fs' % (len(cd2), len(ruff), time.time() - t0), flush=True)

# --- RuffKing module classification (game vs lib)
pdb = json.load(open(S + r'\ruff_pdb.json'))
mods = pdb['mods']
code = sorted((c for c in pdb['contribs'] if c[3] & 0x20 and c[0] == 3), key=lambda c: c[1])
starts = [c[1] for c in code]
def rmod(ea):
    off = ea - 0x822D0000
    i = bisect.bisect_right(starts, off) - 1
    return code[i][4] if i >= 0 and code[i][1] <= off < code[i][1] + code[i][2] else None
def rkind(ea):
    m = rmod(ea)
    return None if m is None else ('lib' if mods[m]['obj'].lower().endswith('.lib') else 'game')

# --- inverted index on rare RuffKing shingles
df = collections.Counter()
for sh, n in ruff.values():
    df.update(sh)
inv = collections.defaultdict(list)
for ea, (sh, n) in ruff.items():
    for s in sh:
        if df[s] <= MAX_DF:
            inv[s].append(ea)
print('index built in %.0fs' % (time.time() - t0), flush=True)

def jac(a, b):
    return len(a & b) / len(a | b) if a or b else 0.0

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
    scored = sorted(((jac(sh, ruff[c][0]), c) for c, _ in cand.most_common(8)), reverse=True)
    best, bc = scored[0]
    second = scored[1][0] if len(scored) > 1 else 0.0
    # treat identical-name runner-up (folded/duplicated code) as non-ambiguous
    if len(scored) > 1 and rname[scored[1][1]] == rname[bc]:
        second = 0.0
    matches[ea] = (bc, best, second)
print('scored in %.0fs' % (time.time() - t0), flush=True)
json.dump({str(k): v for k, v in matches.items()}, open(S + r'\fuzzy_matches.json', 'w'))

# --- evaluation against string-anchored game pairs
truth = {a: b for a, b, n, name in json.load(open(S + r'\game_pairs_all.json'))}
def accepted(m, thr, margin):
    bc, best, second = m
    return best >= thr and best - second >= margin
for thr, margin in ((0.5, 0.1), (0.6, 0.1), (0.7, 0.1), (0.8, 0.05)):
    tp = fp = miss = 0
    for a, b in truth.items():
        m = matches.get(a)
        if m and accepted(m, thr, margin):
            if m[0] == b or rname[m[0]] == rname[b]:
                tp += 1
            else:
                fp += 1
        else:
            miss += 1
    acc = [m for m in matches.values() if accepted(m, thr, margin)]
    kinds = collections.Counter(rkind(m[0]) for m in acc)
    print('thr=%.1f margin=%.2f | ground truth: correct=%d wrong=%d unmatched=%d (precision %.1f%%, recall %.1f%%) | accepted total=%d -> ruff game=%d lib=%d' % (
        thr, margin, tp, fp, miss, 100.0 * tp / max(1, tp + fp), 100.0 * tp / len(truth), len(acc), kinds['game'], kinds['lib']), flush=True)
