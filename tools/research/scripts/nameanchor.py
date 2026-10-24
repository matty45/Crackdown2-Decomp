"""Class-name-anchored vtable naming: CD2 RetClassName-style functions (return a class-name string) identify vtables."""
import json, sys, struct, re, collections, bisect
S = sys.argv[1]
exe = open(S + r'\jeffwork2\orig\default.exe', 'rb').read()
TEXT_VA, TEXT_RAW = 0x821D0000, 0x1C2C00
RDATA_VA, RDATA_RAW = 0x82000400, 0x400
DATA_VA, DATA_RAW = 0x83050000, 0x1041000
asm = open(S + r'\jeffwork2\out\asm\auto_02_821D0000_text.s').read()
cfun = sorted((int(m.group(1), 16), int(m.group(2), 16)) for m in
              re.finditer(r'# \.text:0x[0-9A-F]+ \| 0x([0-9A-F]{8}) \| size: 0x([0-9A-F]+)\n\.fn ', asm))

def cstr_at(va):
    for base, raw, size in ((RDATA_VA, RDATA_RAW, 0x16F258), (DATA_VA, DATA_RAW, 0x267400)):
        if base <= va < base + size:
            o = raw + va - base
            e = exe.find(b'\0', o, o + 128)
            if e > o:
                try:
                    return exe[o:e].decode('ascii')
                except UnicodeDecodeError:
                    return None
    return None

# functions shaped: lis rX,hi ; addi r3,rX,lo ; blr   (returns constant string)
retname = {}
for ea, sz in cfun:
    if sz != 12:
        continue
    o = TEXT_RAW + ea - TEXT_VA
    w0, w1, w2 = struct.unpack_from('>III', exe, o)
    if w0 >> 26 == 15 and w1 >> 26 == 14 and w2 == 0x4E800020 and (w1 >> 21) & 31 == 3:
        hi = w0 & 0xFFFF; lo = w1 & 0xFFFF
        va = ((hi << 16) + (lo - 0x10000 if lo & 0x8000 else lo)) & 0xFFFFFFFF
        s = cstr_at(va)
        if s and re.match(r'^[A-Za-z_]\w{2,80}$', s):
            retname[ea] = s
print('CD2 constant-string-returning functions with identifier strings:', len(retname))
cvt = json.load(open(S + r'\cd2_vtables.json'))
rvt = {int(k): v for k, v in json.load(open(S + r'\ruff_vtables.json')).items()}
rname = {}
for l in open(S + r'\ruff_bytes.jsonl'):
    r = json.loads(l); rname[r['ea']] = r['name']
# RuffKing vtables by class short name (??_7Name@ns@@6B@ -> Name)
rv_by_class = collections.defaultdict(list)
for va, v in rvt.items():
    m = re.match(r'\?\?_7([^@]+)@', v['name'])
    if m:
        rv_by_class[m.group(1)].append(va)
# RuffKing: which slot index holds RetClassName for each vtable
anch = 0; named = {}; samelen = 0; diff = collections.Counter()
for va, slots in cvt:
    cls = [retname[f] for f in slots if f in retname]
    if not cls:
        continue
    # the most-derived class name: the one unique to this vtable (others may be inherited)
    cname = cls[-1]
    cands = rv_by_class.get(cname, [])
    if not cands:
        continue
    anch += 1
    # choose the RuffKing vtable with RetClassName at the same slot index and closest length
    idx = [i for i, f in enumerate(slots) if f in retname and retname[f] == cname][0]
    best = None
    for W in cands:
        rs = rvt[W]['slots']
        ok = idx < len(rs) and 'RetClassName' in rname.get(rs[idx], '')
        key = (ok, -abs(len(rs) - len(slots)))
        if best is None or key > best[0]:
            best = (key, W)
    W = best[1]; rs = rvt[W]['slots']
    diff[len(slots) - len(rs)] += 1
    if len(rs) == len(slots):
        samelen += 1
    n = min(len(rs), len(slots))
    for i in range(n):
        named.setdefault(slots[i], rname.get(rs[i]))
print('CD2 vtables anchored by class name: %d (same slot count as RuffKing: %d)' % (anch, samelen))
print('slot-count difference CD2-RuffKing (top):', diff.most_common(8))
print('distinct CD2 functions named from anchored vtables:', len(named))
json.dump({str(k): v for k, v in named.items()}, open(S + r'\anchor_names.json', 'w'))
