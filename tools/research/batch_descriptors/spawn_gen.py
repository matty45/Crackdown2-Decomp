"""Batch: SpawnFromPrototype of the tail-call shape (`if (memory) return new (memory) X; return 0;` with X's
out-of-line default constructor) for classes declared once. usage: py -I spawn_gen.py <repo root> <plan json> [--write]"""
import json, os, re, sys

root, ppath = sys.argv[1], sys.argv[2]
write = '--write' in sys.argv
os.chdir(root)
decl = {}
for dp, _, fs in os.walk('include'):
    for f in fs:
        if f.endswith('.h'):
            p = os.path.join(dp, f).replace('\\', '/')
            for m in re.finditer(r'^\s*class\s+(\w+)\s*(:[^{;]*)?\{', open(p, errors='replace').read(), re.M):
                decl.setdefault(m.group(1), []).append((p, bool(m.group(2))))
items = []
for p in json.load(open(ppath)):
    d = decl.get(p['cls'] or '', [])
    if len(d) != 1 or not d[0][1]:
        continue
    hdr, cls, ns = d[0][0], p['cls'], p['ns']
    s = open(p['file'], encoding='utf-8-sig', newline='').read()
    if '%s::SpawnFromPrototype' % cls in s:
        continue
    h = open(hdr, encoding='utf-8', newline='').read()
    hm = re.search(r'class\s+%s\b[^{;]*\{' % re.escape(cls), h)
    close = h.find('};', hm.end())
    pub = h.find('public:', hm.end())
    if pub < 0 or pub > close:
        continue
    body = h[hm.end():close]
    nsq = (ns + '@@') if ns else '@'
    items.append(dict(source=p['file'], address=p['address'], symbol='?SpawnFromPrototype@%s@%s' % (cls, nsq)))
    if not write:
        continue
    nl = '\r\n' if '\r\n' in h else '\n'
    le = h.find('\n', pub) + 1
    indent = re.match(r'[ \t]*', h[h.rfind('\n', 0, pub) + 1:]).group(0) + '    '
    add_h = ''
    if not re.search(r'\b%s\s*\(' % re.escape(cls), body):
        add_h += indent + '%s();' % cls + nl
    if 'SpawnFromPrototype' not in body:
        add_h += indent + 'static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);' + nl
    h = h[:le] + add_h + h[le:]
    if 'gom/object_prototype.h' not in h and 'non_game_base.h' not in h:
        incs = list(re.finditer(r'^#include [^\n]*\n', h, re.M))
        at = incs[-1].end() if incs else re.search(r'^#define [^\n]*\n', h, re.M).end()
        h = h[:at] + '#include "gom/object_prototype.h"' + nl + h[at:]
    open(hdr, 'w', encoding='utf-8', newline='').write(h)
    snl = '\r\n' if '\r\n' in s else '\n'
    bom = open(p['file'], 'rb').read(3) == b'\xef\xbb\xbf'
    fn = ['RWS::CAttributeHandler *%s::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)' % cls, '{',
          '    if (memory)', '        return new (memory) %s;' % cls, '    return 0;', '}']
    add = []
    if not re.search(r'operator new\(size_t, void \*', s) and '<new>' not in s:
        add += ['', 'inline void *operator new(size_t, void *memory) { return memory; }']
    add += [''] + ((['namespace %s' % ns, '{'] + ['    ' + l for l in fn] + ['}']) if ns else fn)
    open(p['file'], 'w', encoding='utf-8-sig' if bom else 'utf-8', newline='').write(s.rstrip('\r\n') + snl + snl.join(add) + snl)
json.dump(items, open(os.path.join(os.path.dirname(ppath), 'spawn_items.json'), 'w'), indent=1)
print(len(items), 'written' if write else 'planned')
