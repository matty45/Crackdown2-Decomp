import json, sys, collections, bisect
S = sys.argv[1]
pdb = json.load(open(S + r'\ruff_pdb.json'))
code = sorted((c for c in pdb['contribs'] if c[3] & 0x20 and c[0] == 3), key=lambda c: c[1]); st = [c[1] for c in code]
def mod(ea):
    off = ea - 0x822D0000; i = bisect.bisect_right(st, off) - 1
    return code[i][4] if i >= 0 and code[i][1] <= off < code[i][1] + code[i][2] else None
rname2ea = {}
for l in open(S + r'\ruff_bytes.jsonl'):
    r = json.loads(l); rname2ea[r['name']] = r['ea']
seq = []
for ea, name, src, conf in json.load(open(S + r'\name_apply_result.json'))['applied']:
    if src == 'RuffKing' and name in rname2ea:
        m = mod(rname2ea[name])
        if m is not None: seq.append((ea, m))
seq.sort()
win = collections.defaultdict(lambda: [0, 0])
for (a, m1), (b, m2) in zip(seq, seq[1:]):
    w = (a - 0x821D0000) // 0x40000
    win[w][0] += 1; win[w][1] += m1 == m2
print('256KB windows: matched pairs, same-object adjacency')
for w in sorted(win):
    n, same = win[w]
    if n >= 10:
        print('  0x%08X  n=%4d  adjacency=%.2f %s' % (0x821D0000 + w * 0x40000, n, same / n, '#' * int(20 * same / n)))
