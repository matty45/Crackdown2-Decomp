"""For each matched StaticCreateClass: the initializer that calls it and stores the result (the descriptor pointer),
and the open RetClass (lis / lwz r3, pointer / blr) in the same file. usage: py -I rc_plan.py <repo root> <tasks json> <out>"""
import json, os, re, struct, sys

root, tpath, out = sys.argv[1], sys.argv[2], sys.argv[3]
os.chdir(root)
sys.path.insert(0, 'tools')
import cd2  # noqa: E402

syms = cd2.jeff_symbols()
man = cd2.manifest()['files']
matched = {int(e['address'], 16): (f, e['symbol']) for f, es in man.items() for e in es}
scc = {a: v for a, v in matched.items() if 'StaticCreateClass@' in v[1]}
open_tasks = {int(t['address'], 16): t for t in json.load(open(tpath))['tasks'] if t['status'] == 'open'}
claimed = cd2.claims()


def words(a):
    return struct.unpack('>%dI' % (syms[a][1] // 4), cd2.read(a, syms[a][1]))


# initializers: a call to a StaticCreateClass, then `stw r3, lo(rX)` with rX = lis hi
inits = {}
for a, (name, size) in syms.items():
    if size > 64:
        continue
    ws = words(a)
    hi, target = {}, None
    for i, w in enumerate(ws):
        op = w >> 26
        if op == 15 and (w >> 16) & 31 == 0:
            hi[(w >> 21) & 31] = (w & 0xFFFF) << 16
        elif op == 18 and w & 1:
            d = w & 0x03FFFFFC
            t = (a + 4 * i + (d - 0x04000000 if d & 0x02000000 else d)) & 0xFFFFFFFF
            target = t if t in scc else None
        elif op == 36 and target and (w >> 21) & 31 == 3 and (w >> 16) & 31 in hi:
            lo = w & 0xFFFF
            g = (hi[(w >> 16) & 31] + (lo - 0x10000 if lo & 0x8000 else lo)) & 0xFFFFFFFF
            inits[target] = (a, g)
            break
plan = []
for s, (f, sym) in scc.items():
    if s not in inits:
        continue
    ia, g = inits[s]
    rc = None
    for a, t in open_tasks.items():
        if t['file'] != f or t['size'] != 12:
            continue
        ws = words(a)
        if ws[0] >> 26 == 15 and ws[1] >> 26 == 32 and (ws[1] >> 21) & 31 == 3 and ws[2] == 0x4E800020:
            lo = ws[1] & 0xFFFF
            if (((ws[0] & 0xFFFF) << 16) + (lo - 0x10000 if lo & 0x8000 else lo)) & 0xFFFFFFFF == g:
                rc = a
    m = re.match(r'\?StaticCreateClass@(\w+)@(?:(\w+)@)?@', sym)
    plan.append(dict(file=f, cls=m.group(1), ns=m.group(2), scc='0x%08X' % s, init='0x%08X' % ia, pointer='0x%08X' % g,
                     init_open=ia in open_tasks, init_matched=ia in matched, retclass='0x%08X' % rc if rc else None,
                     src_has_ptr=bool(re.search(r'\bms_p\w*Class\b', open(f, errors='replace').read()))))
json.dump(plan, open(out, 'w'), indent=1)
print(len(scc), 'matched StaticCreateClass;', len(plan), 'with an initializer;',
      sum(p['init_open'] for p in plan), 'initializers open;', sum(bool(p['retclass']) for p in plan), 'with an open RetClass;',
      sum(not p['src_has_ptr'] for p in plan), 'whose source has no descriptor pointer yet')
