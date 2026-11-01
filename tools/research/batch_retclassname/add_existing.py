"""Batch: RetClassName for classes that are already declared (once, with a base) in files that already have code: add
the declaration to the class and the definition to the source. usage: py -I add_existing.py <root> <bases json> [--write]
Writes the claimed items to items.json beside the bases json."""
import json, os, re, subprocess, sys

root, bpath = sys.argv[1], sys.argv[2]
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
for r in json.load(open(bpath)):
    cls = r['cls']
    d = decl.get(cls, [])
    if len(d) != 1 or not d[0][1]:
        continue
    hdr = d[0][0]
    src = r['file']
    s = open(src, encoding='utf-8-sig', newline='').read()
    if '%s::RetClassName' % cls in s:
        continue
    h = open(hdr, encoding='utf-8', newline='').read()
    hm = re.search(r'class\s+%s\b[^{;]*\{' % re.escape(cls), h)
    close = h.find('};', hm.end())
    pub = h.find('public:', hm.end())
    if pub < 0 or pub > close:
        continue
    ns = r['ns']
    hdr_ns = re.findall(r'^namespace\s+(\w+)', h, re.M)
    if (ns and ns not in hdr_ns) or (not ns and hdr_ns):
        continue  # the header's namespace and the file comment's disagree
    nsq = (ns + '@@') if ns else '@'
    items.append(dict(source=src, header=hdr, address=r['address'], symbol='?RetClassName@%s@%s' % (cls, nsq)))
    if not write:
        continue
    nl = '\r\n' if '\r\n' in h else '\n'
    if 'RetClassName' not in h[hm.end():close]:
        le = h.find('\n', pub) + 1
        indent = re.match(r'[ \t]*', h[h.rfind('\n', 0, pub) + 1:]).group(0) + '    '
        h = h[:le] + indent + 'virtual const char *RetClassName() const;' + nl + h[le:]
        open(hdr, 'w', encoding='utf-8', newline='').write(h)
    snl = '\r\n' if '\r\n' in s else '\n'
    bom = open(src, 'rb').read(3) == b'\xef\xbb\xbf'
    fn = ['const char *%s::RetClassName() const' % cls, '{', '    return "%s";' % cls, '}']
    add = [''] + ((['namespace %s' % ns, '{'] + ['    ' + l for l in fn] + ['}']) if ns else fn)
    open(src, 'w', encoding='utf-8-sig' if bom else 'utf-8', newline='').write(s.rstrip('\r\n') + snl + snl.join(add) + snl)
    subprocess.run([sys.executable, '-I', 'tools/cd2.py', 'claim', r['address'], items[-1]['symbol']], capture_output=True)
json.dump(items, open(os.path.join(os.path.dirname(bpath), 'items.json'), 'w'), indent=1)
print(len(items), 'written and claimed' if write else 'planned')
