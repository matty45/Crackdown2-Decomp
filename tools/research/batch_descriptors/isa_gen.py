"""Batch: IsA (`return ms_p<X>Class->IsA(c);`) for classes whose header declares a base and whose source defines the
descriptor pointer. usage: py -I isa_gen.py <repo root> <isa plan json> [--write]"""
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
    d = decl.get(p['cls'], [])
    if len(d) != 1 or not d[0][1] or p['defined']:
        continue
    hdr = d[0][0]
    s = open(p['file'], encoding='utf-8-sig', newline='').read()
    ptr = re.search(r'\b%s::(ms_p\w*Class)\s*=' % re.escape(p['cls']), s).group(1)
    h = open(hdr, encoding='utf-8', newline='').read()
    hm = re.search(r'class\s+%s\b[^{;]*\{' % re.escape(p['cls']), h)
    close = h.find('};', hm.end())
    pub = h.find('public:', hm.end())
    if pub < 0 or pub > close:
        continue
    items.append(dict(source=p['file'], address=p['isa'],
                      symbol='?IsA@%s@%s' % (p['cls'], (p['ns'] + '@@') if p['ns'] else '@')))
    if not write:
        continue
    nl = '\r\n' if '\r\n' in h else '\n'
    if 'IsA(' not in h[hm.end():close]:
        le = h.find('\n', pub) + 1
        indent = re.match(r'[ \t]*', h[h.rfind('\n', 0, pub) + 1:]).group(0) + '    '
        h = h[:le] + indent + 'virtual bool IsA(const Fun_Runtime::cClass &) const;' + nl + h[le:]
        open(hdr, 'w', encoding='utf-8', newline='').write(h)
    snl = '\r\n' if '\r\n' in s else '\n'
    bom = open(p['file'], 'rb').read(3) == b'\xef\xbb\xbf'
    fn = ['bool %s::IsA(const Fun_Runtime::cClass &c) const' % p['cls'], '{', '    return %s->IsA(c);' % ptr, '}']
    add = [''] + ((['namespace %s' % p['ns'], '{'] + ['    ' + l for l in fn] + ['}']) if p['ns'] else fn)
    open(p['file'], 'w', encoding='utf-8-sig' if bom else 'utf-8', newline='').write(s.rstrip('\r\n') + snl + snl.join(add) + snl)
json.dump(items, open(os.path.join(os.path.dirname(ppath), 'isa_items.json'), 'w'), indent=1)
print(len(items), 'written' if write else 'planned')
