import json, sys
S = sys.argv[1]
cd2 = json.load(open(S + r'\cd2_classnames.json'))
def short(n):
    return n.split('::')[-1]
ruff = {short(n) for n in json.load(open(S + r'\ruff_types.json'))}
burn = {short(n) for n in json.load(open(S + r'\burn_types.json'))}
inr = [c for c in cd2 if c in ruff]; inb = [c for c in cd2 if c in burn]
either = [c for c in cd2 if c in ruff or c in burn]
neither = [c for c in cd2 if c not in ruff and c not in burn]
print('CD2 class-like strings: %d | in RuffKing types: %d | in Burn types: %d | either: %d (%.0f%%)' % (len(cd2), len(inr), len(inb), len(either), 100.0 * len(either) / len(cd2)))
print('examples missing from both:', neither[:30])
print('examples present:', either[:20])
