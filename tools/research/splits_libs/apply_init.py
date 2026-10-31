"""Add initializer-region functions to game files in config/splits.txt as init/atexit entries (by area: initializers
end at the last existing init entry, at-exit destructors start at the first existing atexit entry).
usage: py -I apply_init.py <work dir>"""
import io, json, os, re, sys

W = sys.argv[1]
d = json.load(open(os.path.join(W, 'initnew.json')))
p = 'config/splits.txt'
t = io.open(p, encoding='utf-8', newline='').read()
nl = '\r\n' if '\r\n' in t else '\n'
lines = t.split(nl)
out, cur, added = [], None, 0
existing = set(re.findall(r'^\s+(?:init|atexit)\s+(0x[0-9A-Fa-f]+)', t, re.M))
existing = {int(x, 16) for x in existing}


def flush(f):
    global added
    if f in d['new']:
        for a in d['new'][f]:
            if a in existing:
                continue
            kind = 'init' if a <= d['init_max'] else 'atexit' if a >= d['atexit_min'] else None
            if kind:
                out.append('  %s 0x%08X   # 2026-10-31: initializer-region function whose code references only this '
                           'file\'s functions, or lies between two of its entries' % (kind, a))
                added += 1


for line in lines:
    if line and not line[0].isspace() and not line.startswith('#'):
        # a new file entry starts: the previous file's block ends before its trailing blank line(s)
        if cur:
            while out and out[-1] == '':
                out.pop()
            flush(cur)
            out.append('')
        cur = line.split('#')[0].strip()
    out.append(line)
if cur:
    while out and out[-1] == '':
        out.pop()
    flush(cur)
    out.append('')
io.open(p, 'w', encoding='utf-8', newline='').write(nl.join(out))
print('added', added, 'entries')
