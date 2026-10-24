import json, sys
S = sys.argv[1]
src = open(S + r'\fuzzy.py').read()
exec(src.split('# --- RuffKing module classification')[0].replace("S = sys.argv[1]", "S = %r" % S))
truth = json.load(open(S + r'\game_pairs_all.json'))
out = []
for a, b, n, name in truth:
    if a in cd2 and b in ruff:
        A, B = cd2[a], ruff[b]
        j = len(A[0] & B[0]) / len(A[0] | B[0])
        r = A[1] / max(1, B[1])
        if 0.3 <= j <= 0.6 and 1.25 <= r <= 2.0 and 25 <= B[1] <= 60:
            out.append((round(j, 2), A[1], B[1], hex(a), hex(b), name[:80]))
for o in sorted(out)[:10]: print(o)
