"""Batch: StaticCreateClass with a constant class ID (the 152- and 156-byte shapes), for classes declared once in
include/. The ID, name and size are read from CD2's arguments to the cClass constructor (0x8264A890).
usage: py -I scc_gen.py <repo root> <scc json> [--write]   (with --write: written.json beside scc json)"""
import json, os, re, struct, sys

root, spath = sys.argv[1], sys.argv[2]
write = '--write' in sys.argv
os.chdir(root)
sys.path.insert(0, 'tools')
import cd2  # noqa: E402

CCLASS = 0x8264A890
rows = [r for r in json.load(open(spath)) if r['status'] == 'open' and r['size'] == 164 and r['counter']
        and r['string'] and r['file']]
decl = {}
for dp, _, fs in os.walk('include'):
    for f in fs:
        if f.endswith('.h'):
            p = os.path.join(dp, f).replace('\\', '/')
            for m in re.finditer(r'^(\s*)class\s+(\w+)\s*(?::[^{;]*)?\{', open(p, errors='replace').read(), re.M):
                decl.setdefault(m.group(2), []).append(p)


def args(a, size):
    """r4 (ID) and r6 (size) as set before the cClass constructor call."""
    ws = struct.unpack('>%dI' % (size // 4), cd2.read(a, size))
    regs = {}
    for i, w in enumerate(ws):
        op, rd, ra, imm = w >> 26, (w >> 21) & 31, (w >> 16) & 31, w & 0xFFFF
        if op == 14 and ra == 0:
            regs[rd] = imm - 0x10000 if imm & 0x8000 else imm
        elif op == 15 and ra == 0:
            regs[rd] = imm << 16
        elif op == 24 and rd in regs:  # ori rA, rS, imm (rS = rd field)
            regs[ra] = regs[rd] | imm
        elif op == 18 and w & 1:
            d = w & 0x03FFFFFC
            if (a + 4 * i + (d - 0x04000000 if d & 0x02000000 else d)) & 0xFFFFFFFF == CCLASS:
                return regs.get(4), regs.get(6)
    return None, None


plan, skipped = [], []
for r in rows:
    name = r['string']
    if len(decl.get(name, [])) != 1:
        skipped.append((name, 'declared %d times' % len(decl.get(name, []))))
        continue
    cid, csize = args(int(r['address'], 16), r['size'])
    if csize is None:
        skipped.append((name, 'arguments not read'))
        continue
    hdr = decl[name][0]
    ht = open(hdr, encoding='utf-8-sig', errors='replace').read()
    ns = re.findall(r'^namespace\s+(\w+)', ht, re.M)
    ns = ns[0] if len(ns) == 1 else None if not ns else '?'
    if ns == '?':
        skipped.append((name, 'several namespaces in its header'))
        continue
    src = open(r['file'], encoding='utf-8-sig', errors='replace').read()
    if 'StaticCreateClass' in src:
        skipped.append((name, 'source already has StaticCreateClass'))
        continue
    plan.append(dict(r, cls=name, ns=ns, header=hdr, cid=0, csize=csize,
                     symbol='?StaticCreateClass@%s@%s' % (name, ns + '@@' if ns else '@')))
print('%d candidates, %d planned; skipped: %s' % (len(rows), len(plan), sorted(set(s for _, s in skipped))))
print([(p['cls'], hex(p['cid']), hex(p['csize'])) for p in plan[:8]])
if not write:
    sys.exit(0)
written = []
for p in plan:
    # the declaration, in the class body after its first `public:`
    h = open(p['header'], encoding='utf-8', newline='').read()
    nl = '\r\n' if '\r\n' in h else '\n'
    m = re.search(r'class\s+%s\b[^{;]*\{' % re.escape(p['cls']), h)
    pub = h.find('public:', m.end())
    close = h.find('};', m.end())
    if 'StaticCreateClass' not in h[m.end():close]:
        if pub < 0 or pub > close:
            print('no public section, skipped:', p['cls'])
            continue
        line_end = h.find('\n', pub) + 1
        indent = re.match(r'[ \t]*', h[h.rfind('\n', 0, pub) + 1:]).group(0) + '    '
        h = h[:line_end] + indent + 'static Fun_Runtime::cClass &StaticCreateClass();' + nl + h[line_end:]
        if 'fun_runtime/class.h' not in h and 'gom/non_game_base.h' not in h:
            h = h.replace('#define', '#include "fun_runtime/class.h"' + nl + '#define', 1) if False else h
        open(p['header'], 'w', encoding='utf-8', newline='').write(h)
    s = open(p['file'], encoding='utf-8-sig', newline='').read()
    nl = '\r\n' if '\r\n' in s else '\n'
    bom = open(p['file'], 'rb').read(3) == b'\xef\xbb\xbf'
    var = p['cls'] + 'Class'
    fn = ['Fun_Runtime::cClass &%s::StaticCreateClass()' % p['cls'], '{',
          '    static Fun_Runtime::cClass *%s = new Fun_Runtime::cClass(g_nBehaviourClassID++, "%s", 0x%X);' % (var, p['cls'], p['csize']),
          '    return *%s;' % var, '}']
    add = []
    if '"cd2/memory.h"' not in s:
        add += ['', '#include "cd2/memory.h"']
    if 'AI/BehaviourClassID.h' not in s:
        add += ['#include "AI/BehaviourClassID.h"']
    add += [''] + ((['namespace %s' % p['ns'], '{'] + ['    ' + l for l in fn] + ['}']) if p['ns'] else fn)
    open(p['file'], 'w', encoding='utf-8-sig' if bom else 'utf-8', newline='').write(s.rstrip('\r\n') + nl + nl.join(add) + nl)
    written.append(dict(source=p['file'], header=p['header'], address=p['address'], symbol=p['symbol']))
json.dump(written, open(os.path.join(os.path.dirname(spath), 'written_counter.json'), 'w'), indent=1)
print('wrote', len(written))
