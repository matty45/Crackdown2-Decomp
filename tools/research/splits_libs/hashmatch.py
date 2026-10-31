"""Identify CD2 functions with RuffKing functions by code: masked words (address immediates masked as the LTCG checker
does; RuffKing's trace markers removed) hashed per function. A hash unique in both builds pairs the two functions, and
the RuffKing function's module (its PDB section contribution) is the CD2 function's object.
usage: py -I hashmatch.py <work dir>   (writes ident.json: CD2 address -> {mod, ruff, size})"""
import sys, json, os, hashlib, collections, struct
sys.path.insert(0, 'tools')
import cd2
import verify_ltcg as vl
from verify_src import pe_reader

W = sys.argv[1]
pdb = json.load(open(os.path.join(W, 'ruff_pdb.json')))
rk_read, _ = pe_reader(open(os.path.join(W, 'RuffKing_Release.exe'), 'rb').read())
TEXT_SEC, TEXT_VA = 3, 0x822D0000
MARKERS = {0x7DAD6B78, 0x7DCE7378}


def digest(read, a, n):
    try:
        b = read(a, n)
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


rk = collections.defaultdict(list)
for c in pdb['contribs']:
    if c[0] == TEXT_SEC and c[3] & 0x20:
        h = digest(rk_read, TEXT_VA + c[1], c[2])
        if h:
            rk[h].append((TEXT_VA + c[1], c[4]))
print('RuffKing: %d hashed functions, %d distinct' % (sum(len(v) for v in rk.values()), len(rk)))
syms = cd2.jeff_symbols()
cd = collections.defaultdict(list)
for a, (name, n) in syms.items():
    h = digest(cd2.read, a, n)
    if h:
        cd[h].append(a)
print('CD2: %d hashed functions, %d distinct' % (sum(len(v) for v in cd.values()), len(cd)))
ident, multi = {}, 0
for h, cas in cd.items():
    rs = rk.get(h)
    if not rs:
        continue
    mods = {m for _, m in rs}
    if len(cas) == 1 and len(rs) == 1:
        ident['%08X' % cas[0]] = dict(mod=rs[0][1], ruff='%08X' % rs[0][0], grade='unique')
    elif len(mods) == 1:
        for a in cas:  # several copies, one RuffKing object: the object is still known
            ident['%08X' % a] = dict(mod=next(iter(mods)), ruff='%08X' % rs[0][0], grade='same-object')
    else:
        multi += len(cas)
print('%d CD2 functions identified (%d unique pairs); %d match several RuffKing objects' % (
    len(ident), sum(v['grade'] == 'unique' for v in ident.values()), multi))
json.dump(ident, open(os.path.join(W, 'ident.json'), 'w'))
