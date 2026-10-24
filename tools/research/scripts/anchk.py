import json, sys, re
S = sys.argv[1]
an = {int(k): v for k, v in json.load(open(S + r'\anchor_names.json')).items()}
fz = {int(k): v for k, v in json.load(open(S + r'\fz_ruff.json')).items()}
agree = dis = 0; ex = []
def base(n):  # method name part of a mangled name
    m = re.match(r'\?+([^@]+)@', n or '')
    return m.group(1) if m else n
for f, n in an.items():
    m = fz.get(f)
    if m and m[1] >= 0.6 and m[1] - m[2] >= 0.1:
        if m[3] == n or base(m[3]) == base(n): agree += 1
        else:
            dis += 1
            if len(ex) < 6: ex.append((hex(f), n[:60], m[3][:60], round(m[1], 2)))
print('vtable-slot names vs independent similarity names: agree=%d disagree=%d' % (agree, dis))
for e in ex: print(e)
