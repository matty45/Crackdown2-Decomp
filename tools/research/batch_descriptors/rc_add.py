"""Add RetClass (`return *ms_p<X>Class;`) where CD2's is open, the source already defines the descriptor pointer, and
the class's header declares a base. usage: py -I rc_add.py <repo root> <plan json> [--write]"""
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
items, skipped = [], []
for p in json.load(open(ppath)):
    if not p['retclass']:
        continue
    d = decl.get(p['cls'], [])
    if len(d) != 1 or not d[0][1]:
        skipped.append((p['cls'], 'no single declaration with a base'))
        continue
    hdr = d[0][0]
    s = open(p['file'], encoding='utf-8-sig', newline='').read()
    m = re.search(r'\b%s::(ms_p\w*Class)\s*=' % re.escape(p['cls']), s)
    if not m or re.search(r'\b%s::RetClass\(\)' % re.escape(p['cls']), s):
        skipped.append((p['cls'], 'no pointer definition or RetClass already defined'))
        continue
    ptr = m.group(1)
    h = open(hdr, encoding='utf-8', newline='').read()
    hm = re.search(r'class\s+%s\b[^{;]*\{' % re.escape(p['cls']), h)
    close = h.find('};', hm.end())
    pub = h.find('public:', hm.end())
    if pub < 0 or pub > close:
        skipped.append((p['cls'], 'no public section'))
        continue
    items.append(dict(p, header=hdr, ptr=ptr))
    if not write:
        continue
    nl = '\r\n' if '\r\n' in h else '\n'
    if 'RetClass()' not in h[hm.end():close]:
        le = h.find('\n', pub) + 1
        indent = re.match(r'[ \t]*', h[h.rfind('\n', 0, pub) + 1:]).group(0) + '    '
        h = h[:le] + indent + 'virtual const Fun_Runtime::cClass &RetClass() const;' + nl + h[le:]
        open(hdr, 'w', encoding='utf-8', newline='').write(h)
    snl = '\r\n' if '\r\n' in s else '\n'
    bom = open(p['file'], 'rb').read(3) == b'\xef\xbb\xbf'
    fn = ['const Fun_Runtime::cClass &%s::RetClass() const' % p['cls'], '{', '    return *%s;' % ptr, '}']
    add = [''] + ((['namespace %s' % p['ns'], '{'] + ['    ' + l for l in fn] + ['}']) if p['ns'] else fn)
    open(p['file'], 'w', encoding='utf-8-sig' if bom else 'utf-8', newline='').write(s.rstrip('\r\n') + snl + snl.join(add) + snl)
out = [dict(source=i['file'], address=i['retclass'],
            symbol='?RetClass@%s@%s' % (i['cls'], (i['ns'] + '@@') if i['ns'] else '@')) for i in items]
json.dump(out, open(os.path.join(os.path.dirname(ppath), 'rc_add.json'), 'w'), indent=1)
print(len(items), 'planned' if not write else 'written', '; skipped', len(skipped), sorted(set(r for _, r in skipped)))
