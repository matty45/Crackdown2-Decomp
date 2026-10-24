import json, sys, collections, time, struct, re, bisect
S = sys.argv[1]
src = open(S + r'\fuzzy.py').read()
exec(src.split('# --- RuffKing module classification')[0].replace("S = sys.argv[1]", "S = %r" % S))
exec(src.split('# --- RuffKing module classification (game vs lib)\n')[1].split('# --- inverted index')[0])

def seqhash(b, strip):
    ws = [struct.unpack_from('>I', b, i)[0] for i in range(0, len(b) - 3, 4)]
    if strip:
        ws = [w for w in ws if not is_marker(w)]
    return hash(tuple(tok(w) for w in ws))

# full-sequence hashes for small-function identity
cseq = {}
for ea, sz in cfun:
    o = TEXT_RAW + ea - TEXT_VA
    cseq[ea] = seqhash(exe[o:o + sz], False)
rseq = {}
rby_seq = collections.defaultdict(list)
for l in open(S + r'\ruff_bytes.jsonl'):
    r = json.loads(l)
    h = seqhash(bytes.fromhex(r['b']), True)
    rseq[r['ea']] = h
    rby_seq[h].append(r['ea'])

df = collections.Counter()
for sh, n in ruff.values():
    df.update(sh)
inv = collections.defaultdict(list)
for ea, (sh, n) in ruff.items():
    for s in sh:
        if df[s] <= MAX_DF:
            inv[s].append(ea)

cache = {}
def cands(ea):
    """candidate RuffKing functions for a CD2 function: {ruff_ea: weight}"""
    if ea in cache:
        return cache[ea]
    out = {}
    same = rby_seq.get(cseq.get(ea), [])
    if 0 < len(same) <= 400:
        for r in same:
            out[r] = 1.0
    if ea in cd2:
        sh, n = cd2[ea]
        c = collections.Counter()
        for s in sh:
            if s in inv:
                c.update(inv[s])
        for r, _ in c.most_common(6):
            j = len(sh & ruff[r][0]) / len(sh | ruff[r][0])
            if j >= 0.4:
                out[r] = max(out.get(r, 0), j)
    cache[ea] = out
    return out

rvt = {int(k): v for k, v in json.load(open(S + r'\ruff_vtables.json')).items()}
idx = collections.defaultdict(list)
for va, v in rvt.items():
    for i, f in enumerate(v['slots']):
        idx[(i, f)].append(va)
cvt = json.load(open(S + r'\cd2_vtables.json'))
print('vtables: cd2=%d ruff=%d' % (len(cvt), len(rvt)), flush=True)

vt_match = {}
for va, slots in cvt:
    score = collections.Counter()
    for i, f in enumerate(slots):
        for r, w in cands(f).items():
            for W in idx.get((i, r), ()):
                score[W] += w
    if not score:
        continue
    top = score.most_common(2)
    W, s1 = top[0]
    s2 = top[1][1] if len(top) > 1 else 0
    L = max(len(slots), len(rvt[W]['slots']))
    if s1 >= 0.5 * L and s1 - s2 >= 0.15 * L:
        vt_match[va] = (W, s1 / L)
print('cd2 vtables matched: %d of %d' % (len(vt_match), len(cvt)), flush=True)

# names from vtable positions
lab = {int(k): v for k, v in json.load(open(S + r'\cd2_labels.json')).items()}
ida_starts = sorted(lab)
def label(ea):
    if ea in lab:
        return lab[ea]
    i = bisect.bisect_right(ida_starts, ea) - 1
    return lab[ida_starts[i]] if i >= 0 else 'UNKNOWN'
fz = {int(k): v for k, v in json.load(open(S + r'\fuzzy_matches.json')).items()}
fz_ok = {k for k, (bc, best, second) in fz.items() if best >= 0.5 and best - second >= 0.1}
named = {}
conflict = 0
for va, (W, sc) in vt_match.items():
    slots = [s for a, s in cvt if a == va][0] if False else None
vt_slots = {va: sl for va, sl in cvt}
for va, (W, sc) in vt_match.items():
    rs = rvt[W]['slots']
    for i, f in enumerate(vt_slots[va]):
        if i < len(rs):
            n = rname.get(rs[i])
            if f in named and named[f] != n:
                conflict += 1
            named[f] = n
by = collections.Counter()
for f in named:
    l = label(f)
    grp = 'game' if l in ('GAME', 'UNKNOWN') else 'lib'
    by[(grp, 'new' if f not in fz_ok else 'also-fuzzy')] += 1
print('functions named via vtable slots: %d (conflicting names %d)' % (len(named), conflict))
print('  breakdown (area, overlap with fuzzy):', dict(by))
ruff_game_vt = collections.Counter(rkind(W) for W, sc in vt_match.values())
print('  matched vtables by RuffKing kind (by vtable addr module - approximate):', dict(ruff_game_vt))
json.dump({str(k): v for k, v in named.items()}, open(S + r'\vt_names.json', 'w'))
