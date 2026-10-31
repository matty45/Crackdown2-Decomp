"""hashmatch for any reference build: usage: py -I hashref.py <exe> <pdb> <pdb json> <out ident json>
The code section's address comes from the PDB's section headers (the .text section)."""
import sys, json, os, hashlib, collections, struct
sys.path.insert(0, 'tools')
sys.path.insert(0, 'tools/research/scripts')
import cd2
import verify_ltcg as vl
from verify_src import pe_reader
from pdbinfo import MSF

exe, pdb_path, info, out = sys.argv[1:5]
msf = MSF(pdb_path)
dbi = msf.stream(3)
modi, secc, secm, srci, tsm, mfc, dbgsz, ecs = struct.unpack_from('<iiiiiIii', dbi, 24)
dbg = struct.unpack_from('<%dH' % (dbgsz // 2), dbi, 64 + modi + secc + secm + srci + tsm + ecs)
sh = msf.stream(dbg[5])
secs = {i + 1: struct.unpack_from('<8sII', sh, 40 * i) for i in range(len(sh) // 40)}
text = [(i, va) for i, (nm, vs, va) in secs.items() if nm.rstrip(b'\0') == b'.text']
TEXT_SEC, TEXT_VA = text[0][0], 0x82000000 + text[0][1]
print('.text is section %d at %08X' % (TEXT_SEC, TEXT_VA))
pdb = json.load(open(info))
read, _ = pe_reader(open(exe, 'rb').read())
MARKERS = {0x7DAD6B78, 0x7DCE7378}


def digest(rd, a, n):
    try:
        b = rd(a, n)
    except Exception:
        return None
    if len(b) < n or n < 12:
        return None
    ws = [w for w in struct.unpack('>%dI' % (n // 4), b[:n // 4 * 4]) if w not in MARKERS]
    while ws and ws[-1] == 0:
        ws.pop()
    if len(ws) < 3:
        return None
    return hashlib.sha1(struct.pack('>%dI' % len(ws), *vl.masked(ws, a))).hexdigest()


ref = collections.defaultdict(list)
for c in pdb['contribs']:
    if c[0] == TEXT_SEC and c[3] & 0x20:
        h = digest(read, TEXT_VA + c[1], c[2])
        if h:
            ref[h].append((TEXT_VA + c[1], c[4]))
syms = cd2.jeff_symbols()
cd = collections.defaultdict(list)
for a, (name, n) in syms.items():
    h = digest(cd2.read, a, n)
    if h:
        cd[h].append(a)
ident = {}
for h, cas in cd.items():
    rs = ref.get(h)
    if not rs:
        continue
    mods = {m for _, m in rs}
    if len(cas) == 1 and len(rs) == 1:
        ident['%08X' % cas[0]] = dict(mod=rs[0][1], ruff='%08X' % rs[0][0], grade='unique')
    elif len(mods) == 1:
        for a in cas:
            ident['%08X' % a] = dict(mod=next(iter(mods)), ruff='%08X' % rs[0][0], grade='same-object')
print('%d reference functions hashed; %d CD2 functions identified (%d unique pairs)' % (
    sum(len(v) for v in ref.values()), len(ident), sum(v['grade'] == 'unique' for v in ident.values())))
json.dump(ident, open(out, 'w'))
