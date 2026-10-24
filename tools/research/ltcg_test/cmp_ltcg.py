import struct, re, json, sys, os
S = os.path.dirname(os.path.abspath(__file__))

def load_pe(path):
    d = open(path, 'rb').read()
    pe = struct.unpack('<I', d[0x3C:0x40])[0]
    mach, nsec = struct.unpack('<HH', d[pe + 4:pe + 8])
    optsz = struct.unpack('<H', d[pe + 20:pe + 22])[0]
    base = struct.unpack('<I', d[pe + 24 + 28:pe + 24 + 32])[0]
    secs = []
    for i in range(nsec):
        o = pe + 24 + optsz + i * 40
        vs, va, rs, ra = struct.unpack('<IIII', d[o + 8:o + 24])
        secs.append((base + va, rs, ra))
    def read(ea, n):
        for va, rs, ra in secs:
            if va <= ea < va + rs:
                return d[ra + ea - va: ra + ea - va + n]
    return read, hex(mach)

def load_map(path):
    funcs = []
    for l in open(path):
        m = re.match(r'\s*0003:[0-9a-f]+\s+(\S+)\s+([0-9a-f]{8})\s+f\s+(\S+)', l)
        if m:
            funcs.append((int(m.group(2), 16), m.group(1), m.group(3)))
    funcs.sort()
    return funcs

def bodies(mode):
    read, mach = load_pe(S + r'\out_%s\test.pe' % mode)
    fs = load_map(S + r'\out_%s\test.map' % mode)
    out = {}
    for i, (ea, name, obj) in enumerate(fs):
        end = fs[i + 1][0] if i + 1 < len(fs) else ea + 4
        out[name] = (ea, read(ea, end - ea), obj)
    return out, [f[1] for f in fs]

def norm(b):
    """mask branch displacements and D-form immediates; keep opcode + register fields"""
    ws = []
    for w in range(len(b) // 4):
        x = struct.unpack('>I', b[w * 4:w * 4 + 4])[0]
        op = x >> 26
        if op in (16, 18):
            x &= 0xFC000003 if op == 18 else 0xFFFF0003
        elif op in (14, 15, 24, 25, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 44, 45, 48, 49, 50, 51, 52, 53, 54, 55):
            x &= 0xFFFF0000
        ws.append(x)
    while ws and ws[-1] == 0:
        ws.pop()
    return ws

gl, gl_order = bodies('gl')
pl, pl_order = bodies('plain')
cd2 = {k: bytes.fromhex(v['bytes']) for k, v in json.load(open(S + r'\..\cd2_lua_bytes.json')).items()}
lua = [n for n in pl if pl[n][2] not in ('main.obj',) and re.match(r'lua|luaB_|luaK_|luaG_|luaV_|luaT_|luaL_', n)]
print('lua API/internal funcs: plain=%d  ltcg=%d  (missing in ltcg: %d)' % (len(lua), sum(1 for n in lua if n in gl), sum(1 for n in lua if n not in gl)))
same = diff = 0; diffs = []
for n in lua:
    if n in gl:
        if norm(gl[n][1]) == norm(pl[n][1]): same += 1
        else: diff += 1; diffs.append((n, len(pl[n][1]), len(gl[n][1])))
print('present in both: identical(masked)=%d  different=%d' % (same, diff))
print('  examples of LTCG-changed functions (name, plain size, ltcg size):', diffs[:10])
cs = cg = 0
for n, b in cd2.items():
    c = norm(b)
    if n in pl and norm(pl[n][1]) == c: cs += 1
    if n in gl and norm(gl[n][1]) == c: cg += 1
print('CD2 33 reference funcs: match plain build=%d  match LTCG build=%d  (LTCG missing %d of them)' % (cs, cg, sum(1 for n in cd2 if n not in gl)))
# layout: is per-obj grouping kept under LTCG?
def runs(order, d):
    objs = [d[n][2] for n in order]
    return sum(1 for a, b in zip(objs, objs[1:]) if a != b)
print('obj switches along .text: plain=%d  ltcg=%d' % (runs(pl_order, pl), runs(gl_order, gl)))
