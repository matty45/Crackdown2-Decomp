"""Survey open functions that return the address of a string: is it the file's class name, in vtable slot 11, and is
the class declared in include/? usage: py -I survey.py <repo root> <tasks json> <out json>"""
import json, os, re, struct, sys

root, tasks_path, out_path = sys.argv[1], sys.argv[2], sys.argv[3]
sys.path.insert(0, os.path.join(root, 'tools'))
os.chdir(root)
import cd2  # noqa: E402

tasks = [t for t in json.load(open(tasks_path))['tasks'] if t['status'] == 'open']
refs = cd2.game_references()
decls = {}
for dp, _, fs in os.walk('include'):
    for f in fs:
        if f.endswith('.h'):
            p = os.path.join(dp, f).replace('\\', '/')
            for m in re.finditer(r'^\s*(?:class|struct)\s+(\w+)\s*(?::|\{)', open(p, errors='replace').read(), re.M):
                decls.setdefault(m.group(1), []).append(p)


def string_at(a):
    try:
        s = cd2.read(a, 64).split(b'\0')[0]
    except Exception:
        return None
    return s.decode('latin1') if len(s) >= 2 and all(32 <= c < 127 for c in s) else None


rows = []
for t in tasks:
    a, n = int(t['address'], 16), t['size']
    if n != 12:
        continue
    w = struct.unpack('>3I', cd2.read(a, 12))
    if not (w[0] >> 26 == 15 and w[1] >> 26 == 14 and (w[1] >> 21) & 31 == 3
            and (w[1] >> 16) & 31 == (w[0] >> 21) & 31 and w[2] == 0x4E800020):
        continue
    lo = w[1] & 0xFFFF
    target = (((w[0] & 0xFFFF) << 16) + (lo - 0x10000 if lo & 0x8000 else lo)) & 0xFFFFFFFF
    s = string_at(target)
    if not s:
        continue
    head = open(t['file'], errors='replace').read(1500)
    m = re.search(r'Class: (\w+) \(namespace: (\w+)\)', head) or re.search(r'Class: (\w+)', head)
    cls, ns = (m.group(1), m.group(2) if m.lastindex and m.lastindex >= 2 else None) if m else (None, None)
    slots = [v[1] for v in refs['vtables'].get(t['address'], [])]
    rows.append(dict(address=t['address'], file=t['file'], string=s, cls=cls, ns=ns, slots=slots,
                     declared=decls.get(cls or s, []), has_code=cd2.has_code(t['file'])))
json.dump(rows, open(out_path, 'w'), indent=1)
same = [r for r in rows if r['cls'] == r['string']]
print(len(rows), 'string returners;', len(same), 'return the file\'s class name;',
      sum(11 in r['slots'] for r in same), 'of those in slot 11;',
      sum(bool(r['declared']) for r in same), 'already declared;', sum(r['has_code'] for r in same), 'in files with code')
other = [r for r in rows if r['cls'] != r['string']]
print('others, e.g.:', [(r['string'], r['cls'], r['slots']) for r in other[:8]])
