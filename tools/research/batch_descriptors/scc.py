"""Census of StaticCreateClass-like functions: open functions that call the cClass constructor (0x8264A890), with the
class-name string they pass and their shape. usage: py -I scc.py <repo root> <tasks json> <out json>"""
import collections, json, os, struct, sys

root, tpath, out = sys.argv[1], sys.argv[2], sys.argv[3]
os.chdir(root)
sys.path.insert(0, 'tools')
import cd2  # noqa: E402

CCLASS = 0x8264A890
tasks = {int(t['address'], 16): t for t in json.load(open(tpath))['tasks'] if t['status'] == 'open'}
syms = cd2.jeff_symbols()
man = {int(e['address'], 16) for es in cd2.manifest()['files'].values() for e in es}
res = []
for a, (name, size) in syms.items():
    ws = struct.unpack('>%dI' % (size // 4), cd2.read(a, size))
    hit = None
    for i, w in enumerate(ws):
        if w >> 26 == 18 and w & 1:
            d = w & 0x03FFFFFC
            if (a + 4 * i + (d - 0x04000000 if d & 0x02000000 else d)) & 0xFFFFFFFF == CCLASS:
                hit = i
    if hit is None:
        continue
    # the string: the last lis/addi pair before the call that builds an identifier-like string
    s = None
    hi = {}
    for w in ws[:hit]:
        op = w >> 26
        if op == 15 and (w >> 16) & 31 == 0:
            hi[(w >> 21) & 31] = (w & 0xFFFF) << 16
        elif op == 14 and (w >> 16) & 31 in hi:
            lo = w & 0xFFFF
            t = (hi[(w >> 16) & 31] + (lo - 0x10000 if lo & 0x8000 else lo)) & 0xFFFFFFFF
            try:
                b = cd2.read(t, 48).split(b'\0')[0]
                if b and all(32 <= c < 127 for c in b):
                    s = b.decode('latin1')
            except Exception:
                pass
    counter = any(w >> 26 == 32 for w in ws[:hit]) and any(w >> 26 == 14 and w & 0xFFFF == 1 for w in ws[:hit])
    res.append(dict(address='0x%08X' % a, size=size, string=s, file=tasks[a]['file'] if a in tasks else None,
                    status='open' if a in tasks else ('matched' if a in man else 'unowned'), counter=counter))
json.dump(res, open(out, 'w'), indent=1)
c = collections.Counter((r['status'], r['size'], r['counter']) for r in res)
print(len(res), 'functions call the cClass constructor')
for k, n in c.most_common(12):
    print('  status %-8s size %4d counter-id %-5s : %d' % (k[0], k[1], k[2], n))
