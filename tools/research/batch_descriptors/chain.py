"""CD2's base chain for classes: a class's constructor (the code that installs the vtable holding its slot-11
RetClassName) first calls its base's constructor; that constructor installs the base's vtable, whose slot 11 returns
the base's name. Walks up to a known root. usage: py -I chain.py <repo root> <bases json> <out json>"""
import bisect, collections, json, os, struct, sys

root, bpath, out = sys.argv[1], sys.argv[2], sys.argv[3]
os.chdir(root)
sys.path.insert(0, 'tools')
import cd2  # noqa: E402

refs = cd2.game_references()
syms = cd2.jeff_symbols()
starts = sorted(syms)
ROOTS = {0x82653588: 'cNonGameBase', 0x82654118: 'GOM::cObjectPrototype'}


def func_of(a):
    return starts[bisect.bisect_right(starts, a) - 1]


def words(f):
    return struct.unpack('>%dI' % (syms[f][1] // 4), cd2.read(f, syms[f][1]))


def calls(f):
    out = []
    for i, w in enumerate(words(f)):
        if w >> 26 == 18 and w & 1:
            d = w & 0x03FFFFFC
            out.append((f + 4 * i + (d - 0x04000000 if d & 0x02000000 else d)) & 0xFFFFFFFF)
    return out


def ret_string(f):
    ws = words(f)
    if len(ws) != 3 or ws[0] >> 26 != 15 or ws[1] >> 26 != 14 or ws[2] != 0x4E800020:
        return None
    lo = ws[1] & 0xFFFF
    a = (((ws[0] & 0xFFFF) << 16) + (lo - 0x10000 if lo & 0x8000 else lo)) & 0xFFFFFFFF
    try:
        s = cd2.read(a, 64).split(b'\0')[0]
    except Exception:
        return None
    return s.decode('latin1') if s and all(32 <= c < 127 for c in s) else None


# tables installed by each function, and the slot-11 function of each table
installs = collections.defaultdict(set)
slot11 = {}
for fn, entries in refs['vtables'].items():
    for table, slot, at in entries:
        installs[func_of(int(at, 16))].add(table)
        if slot == 11:
            slot11[table] = int(fn, 16)


def class_of_ctor(f):
    """The name the class whose constructor is f returns from slot 11 of a table f installs."""
    for t in installs.get(f, ()):
        if t in slot11:
            s = ret_string(slot11[t])
            if s:
                return s
    return None


def chain(retclassname):
    """[(class, constructor)] from the class up to a root, or None."""
    vt = [v for v in refs['vtables'].get('0x%08X' % retclassname, []) if v[1] == 11]
    if not vt:
        return None
    path = []
    ctors = [func_of(int(at, 16)) for _, _, at in [v for v in refs['vtables']['0x%08X' % retclassname] if v[1] == 11]]
    seen = set()
    f = None
    for c in ctors:  # the installer that calls a constructor-like function first
        if calls(c):
            f = c
            break
    while f and f not in seen and len(path) < 12:
        seen.add(f)
        cs = calls(f)
        if not cs:
            return None
        base = cs[0]
        if base in ROOTS:
            path.append((ROOTS[base], '0x%08X' % base))
            return path
        name = class_of_ctor(base)
        if not name:
            return path + [('?', '0x%08X' % base)]
        path.append((name, '0x%08X' % base))
        f = base
    return path


rows = json.load(open(bpath))
res = []
for r in rows:
    if r['declared'] or r['has_code']:
        continue
    c = chain(int(r['address'], 16))
    res.append(dict(r, cd2_chain=c))
json.dump(res, open(out, 'w'), indent=1)
ok = [x for x in res if x['cd2_chain'] and x['cd2_chain'][-1][0] in ROOTS.values()]
print(len(res), 'classes;', len(ok), 'with a CD2 chain to a root')
for x in res[:12]:
    print(' ', x['cls'], '<-', ' <- '.join(n for n, _ in (x['cd2_chain'] or [])), '| RuffKing:', x['rk_base'])
