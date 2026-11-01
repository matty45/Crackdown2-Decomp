"""Batch: the class-descriptor pointer `ms_p<Class>Class = &<Class>::StaticCreateClass()` (its dynamic initializer)
and RetClass (`return *ms_p<Class>Class;`), from rc_plan.json. usage: py -I rc_gen.py <repo root> <plan json> [--write]"""
import json, os, re, sys

root, ppath = sys.argv[1], sys.argv[2]
write = '--write' in sys.argv
os.chdir(root)
plan = [p for p in json.load(open(ppath)) if not p['src_has_ptr'] and p['init_open']]
decl = {}
for dp, _, fs in os.walk('include'):
    for f in fs:
        if f.endswith('.h'):
            pth = os.path.join(dp, f).replace('\\', '/')
            for m in re.finditer(r'^\s*class\s+(\w+)\s*(?::[^{;]*)?\{', open(pth, errors='replace').read(), re.M):
                decl.setdefault(m.group(1), []).append(pth)
print(len(plan), 'planned')
written = []
for p in plan:
    if len(decl.get(p['cls'], [])) != 1:
        print('skip (declarations):', p['cls'])
        continue
    hdr = decl[p['cls']][0]
    ptr = 'ms_p%sClass' % p['cls']
    h = open(hdr, encoding='utf-8', newline='').read()
    nl = '\r\n' if '\r\n' in h else '\n'
    m = re.search(r'class\s+%s\b[^{;]*\{' % re.escape(p['cls']), h)
    close = h.find('};', m.end())
    body = h[m.end():close]
    want_rc = bool(p['retclass']) and 'RetClass()' not in body
    pub = h.find('public:', m.end())
    if pub < 0 or pub > close:
        print('skip (no public section):', p['cls'])
        continue
    line_end = h.find('\n', pub) + 1
    indent = re.match(r'[ \t]*', h[h.rfind('\n', 0, pub) + 1:]).group(0) + '    '
    add_h = indent + 'static const Fun_Runtime::cClass *%s;' % ptr + nl
    if want_rc:
        add_h += indent + 'virtual const Fun_Runtime::cClass &RetClass() const;' + nl
    h = h[:line_end] + add_h + h[line_end:]
    s = open(p['file'], encoding='utf-8-sig', newline='').read()
    snl = '\r\n' if '\r\n' in s else '\n'
    bom = open(p['file'], 'rb').read(3) == b'\xef\xbb\xbf'
    q = p['cls']
    fn = ['const Fun_Runtime::cClass *%s::%s = &%s::StaticCreateClass();' % (q, ptr, q)]
    if want_rc:
        fn += ['', 'const Fun_Runtime::cClass &%s::RetClass() const' % q, '{', '    return *%s;' % ptr, '}']
    add = [''] + ((['namespace %s' % p['ns'], '{'] + ['    ' + l if l else l for l in fn] + ['}']) if p['ns'] else fn)
    nsq = (p['ns'] + '@@') if p['ns'] else '@'
    entry = dict(source=p['file'], header=hdr, init=p['init'], init_symbol='??__E?%s@%s@%s' % (ptr, q, nsq),
                 retclass=p['retclass'] if want_rc else None, rc_symbol='?RetClass@%s@%s' % (q, nsq))
    if write:
        open(hdr, 'w', encoding='utf-8', newline='').write(h)
        open(p['file'], 'w', encoding='utf-8-sig' if bom else 'utf-8', newline='').write(s.rstrip('\r\n') + snl + snl.join(add) + snl)
    written.append(entry)
if write:
    json.dump(written, open(os.path.join(os.path.dirname(ppath), 'rc_written.json'), 'w'), indent=1)
print('would write' if not write else 'wrote', len(written), '; with RetClass:', sum(bool(w['retclass']) for w in written))
