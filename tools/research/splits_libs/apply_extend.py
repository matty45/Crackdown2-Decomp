import io, json, os, re, sys

W = sys.argv[1]
ext = json.load(open(os.path.join(W, 'extend.json')))
p = 'config/splits.txt'
t = io.open(p, encoding='utf-8', newline='').read()
nl = '\r\n' if '\r\n' in t else '\n'
lines = t.split(nl)
cur, done = None, 0
for i, line in enumerate(lines):
    if line and not line[0].isspace() and not line.startswith('#'):
        cur = line.split('#')[0].strip()
        continue
    m = re.match(r'^(\s+)text\s+(0x[0-9A-Fa-f]+)\s+(0x[0-9A-Fa-f]+)(.*)$', line)
    if m and cur in ext:
        s, e, before, after = ext[cur]
        comment = m.group(4)
        note = 'extended 2026-10-31 by %d function(s) before and %d after: used only by this file (calls, addresses, ' \
               'vtables it installs)' % (before, after)
        comment = (comment.rstrip() + '; ' + note) if comment.strip() else '   # ' + note
        lines[i] = '%stext %s %s%s' % (m.group(1), s, e, comment)
        done += 1
io.open(p, 'w', encoding='utf-8', newline='').write(nl.join(lines))
print('updated', done, 'ranges')
