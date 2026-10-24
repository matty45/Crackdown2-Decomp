import json, sys, collections
p = json.load(open(sys.argv[1] + r'\ruff_pdb.json'))
code = sorted((c for c in p['contribs'] if c[3] & 0x20 and c[0] == 3), key=lambda c: c[1])
same = collections.Counter(); change = collections.Counter(); al_same = collections.Counter(); al_change = collections.Counter()
for a, b in zip(code, code[1:]):
    gap = b[1] - (a[1] + a[2])
    k = gap if gap < 32 else '32+'
    if a[4] == b[4]:
        same[k] += 1; al_same[b[1] % 32] += 1
    else:
        change[k] += 1; al_change[b[1] % 32] += 1
print('gap between consecutive code contributions (same module):', sorted(same.items(), key=str)[:8])
print('gap between consecutive code contributions (module change):', sorted(change.items(), key=str)[:8])
print('start mod 32, same module:', sorted(al_same.items())[:8])
print('start mod 32, module change:', sorted(al_change.items())[:8])
print('contribution alignment flags (IMAGE_SCN_ALIGN) on code:', collections.Counter((c[3] >> 20) & 0xF for c in code).most_common(5))
