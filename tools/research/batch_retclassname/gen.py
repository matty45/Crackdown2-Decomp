"""Batch: declare each candidate class (RuffKing base, slot-11 RetClassName) in its own header and define RetClassName
in its source file. usage: py -I gen.py <repo root> <bases json> [--write]
Writes nothing without --write; with it, prints the files written to backup.json for undoing."""
import json, os, re, sys

root, bases_path = sys.argv[1], sys.argv[2]
write = '--write' in sys.argv
os.chdir(root)
sys.path.insert(0, 'tools')
import cd2  # noqa: E402

rows = json.load(open(bases_path))
refs = cd2.game_references()
modelled = {}
for dp, _, fs in os.walk('include'):
    for f in fs:
        if f.endswith('.h'):
            p = os.path.join(dp, f).replace('\\', '/')
            t = open(p, errors='replace').read()
            for m in re.finditer(r'^\s*(?:class|struct)\s+(\w+)\s*(?::[^{;]*)?\{', t, re.M):
                modelled.setdefault(m.group(1), p[len('include/'):])
cand = {}
for r in rows:
    if r['declared'] or r['has_code'] or not r['rk_base']:
        continue
    cand[r['cls']] = r


def header_of(name):
    return '%s/%s.h' % (cand[name]['ns'], name) if cand[name]['ns'] else '%s.h' % name


resolved, order = {}, []


def resolve(name, seen=()):
    """The include path of name's header, generating the chain; None if the chain reaches nothing modelled."""
    if name in resolved:
        return resolved[name]
    if name in modelled and name not in cand:
        return modelled[name]
    if name not in cand or name in seen:
        return None
    base = cand[name]['rk_base'].split('::')[-1]
    bh = resolve(base, seen + (name,))
    resolved[name] = header_of(name) if bh else None
    if bh:
        cand[name]['base_header'] = bh
        order.append(name)
    return resolved[name]


for name in list(cand):
    resolve(name)
print('%d candidates; %d resolvable through modelled bases' % (len(cand), len(order)))

written = []
for name in order:
    r = cand[name]
    ns, base = r['ns'], r['rk_base']
    vt = [v for v in refs['vtables'].get(r['address'], []) if v[1] == 11]
    guard = re.sub(r'\W', '_', header_of(name)).upper()
    q = (ns + '::' if ns else '')
    lines = ['// %s%s (Crackdown 2): STAND-IN for the class name only. Base %s, as in RuffKing\'s header; RetClassName (%s)'
             % (q, name, base, r['address']),
             '// is slot 11 of the vtable at %s, as cNonGameBase\'s RetClassName.' % (vt[0][0] if vt else '?'),
             '#ifndef %s' % guard, '#define %s' % guard, '', '#include "%s"' % r['base_header'], '']
    body = ['class %s : public %s' % (name, base), '{', 'public:', '    virtual const char *RetClassName() const;', '};']
    if ns:
        lines += ['namespace %s' % ns, '{'] + ['    ' + l if l else l for l in body] + ['}']
    else:
        lines += body
    lines += ['', '#endif // %s' % guard, '']
    hpath = os.path.join('include', header_of(name))
    src = r['file']
    text = open(src, encoding='utf-8-sig', newline='').read()
    nl = '\r\n' if '\r\n' in text else '\n'
    fn = ['const char *%s::RetClassName() const' % name, '{', '    return "%s";' % name, '}']
    add = ['', '#include "%s"' % header_of(name), '']
    add += (['namespace %s' % ns, '{'] + ['    ' + l if l else l for l in fn] + ['}']) if ns else fn
    if write:
        if os.path.exists(hpath):
            print('exists, skipped:', hpath)
            continue
        os.makedirs(os.path.dirname(hpath), exist_ok=True)
        open(hpath, 'w', encoding='utf-8', newline='').write('\n'.join(lines))
        bom = open(src, 'rb').read(3) == b'\xef\xbb\xbf'
        out = text.rstrip('\r\n') + nl + nl.join(add) + nl
        open(src, 'w', encoding='utf-8-sig' if bom else 'utf-8', newline='').write(out)
        written.append(dict(header=hpath, source=src, address=r['address'],
                            symbol='?RetClassName@%s@%s' % (name, ns + '@@' if ns else '@')))
if write:
    json.dump(written, open(os.path.join(os.path.dirname(bases_path), 'written.json'), 'w'), indent=1)
    print('wrote', len(written), 'headers and source files')
else:
    for name in order[:6]:
        print(' ', name, cand[name]['ns'], '<-', cand[name]['rk_base'], cand[name]['base_header'])
