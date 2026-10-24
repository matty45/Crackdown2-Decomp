import json, sys, collections
S = sys.argv[1]
exec(open(S + r'\fuzzy.py').read().split('# --- RuffKing module classification')[0].replace("S = sys.argv[1]", "S = %r" % S))
truth = json.load(open(S + r'\game_pairs_all.json'))
sims = []
for a, b, n, name in truth:
    if a in cd2 and b in ruff:
        A, B = cd2[a][0], ruff[b][0]
        sims.append((len(A & B) / len(A | B), cd2[a][1], ruff[b][1], hex(a), hex(b), name[:70]))
sims.sort()
buck = collections.Counter(int(s[0] * 10) for s in sims)
print('jaccard decile histogram:', sorted(buck.items()))
mid = [s for s in sims if 30 <= s[1] <= 70][:8]
for s in mid:
    print('%.2f cd2_n=%d ruff_n=%d %s %s %s' % s)
