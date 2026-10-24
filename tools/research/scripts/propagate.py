"""Call-site propagation from confident matches: pair i-th call targets when call sequences have equal length."""
import json, sys, struct, re, collections, bisect
S = sys.argv[1]

def calls(b, base):
    out = []
    for i in range(0, len(b) - 3, 4):
        w = struct.unpack_from('>I', b, i)[0]
        if w >> 26 == 18 and (w & 3) == 1 and i != 4:  # bl, skip prologue __savegprlr at +4
            li = w & 0x03FFFFFC
            if li & 0x02000000:
                li -= 0x04000000
            out.append((base + i + li) & 0xFFFFFFFF)
    return out

asm = open(S + r'\jeffwork2\out\asm\auto_02_821D0000_text.s').read()
cfun = sorted((int(m.group(1), 16), int(m.group(2), 16)) for m in
              re.finditer(r'# \.text:0x[0-9A-F]+ \| 0x([0-9A-F]{8}) \| size: 0x([0-9A-F]+)\n\.fn ', asm))
exe = open(S + r'\jeffwork2\orig\default.exe', 'rb').read()
ccalls = {ea: calls(exe[0x1C2C00 + ea - 0x821D0000:0x1C2C00 + ea - 0x821D0000 + sz], ea) for ea, sz in cfun}
size = dict(cfun)
lab = {int(k): v for k, v in json.load(open(S + r'\cd2_labels.json')).items()}
ist = sorted(lab)
def label(ea):
    if ea in lab: return lab[ea]
    i = bisect.bisect_right(ist, ea) - 1
    return lab[ist[i]] if i >= 0 else 'UNKNOWN'
game = {ea for ea in ccalls if label(ea) in ('GAME', 'UNKNOWN')}

named_any = set()
for refname, bfile, mfile in (('ruff', 'ruff_bytes.jsonl', 'fz_ruff.json'), ('burn', 'burn_bytes.jsonl', 'fz_burn.json')):
    rcalls, rname = {}, {}
    for l in open(S + '\\' + bfile):
        r = json.loads(l)
        rcalls[r['ea']] = calls(bytes.fromhex(r['b']), r['ea'])
        rname[r['ea']] = r['name']
    fz = json.load(open(S + '\\' + mfile))
    pair = {}
    for k, (bc, best, second, nm) in fz.items():
        if best >= 0.5 and best - second >= 0.1:
            pair[int(k)] = bc
    seeds = dict(pair)
    rev = {}
    for c, r in pair.items():
        rev.setdefault(r, c)
    queue = list(pair)
    conflicts = 0
    while queue:
        c = queue.pop()
        r = pair[c]
        a, b = ccalls.get(c, []), rcalls.get(r, [])
        if not a or len(a) != len(b):
            continue
        for x, y in zip(a, b):
            if x not in ccalls or y not in rcalls:
                continue
            if x in pair:
                if pair[x] != y and rname.get(pair[x]) != rname.get(y):
                    conflicts += 1
                continue
            if y in rev and rev[y] != x:
                continue
            pair[x] = y; rev[y] = x
            queue.append(x)
    g_seed = sum(1 for c in seeds if c in game)
    g_all = sum(1 for c in pair if c in game)
    print('%s: seeds=%d (game %d) -> after propagation=%d (game %d), conflicts=%d' % (refname, len(seeds), g_seed, len(pair), g_all, conflicts), flush=True)
    named_any |= {c for c in pair if c in game}
gb = sum(size[e] for e in game)
print('union game-area functions named: %d of %d (%.1f%%), bytes %.1f%%' % (len(named_any), len(game), 100.0 * len(named_any) / len(game), 100.0 * sum(size[e] for e in named_any) / gb))
json.dump(sorted(named_any), open(S + r'\named_game.json', 'w'))
