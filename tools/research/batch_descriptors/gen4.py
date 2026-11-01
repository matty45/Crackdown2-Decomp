"""Batch: StaticCreateClass and the descriptor pointer for classes declared nowhere yet. Each class gets a stand-in
header with only those static members (bases not modelled), and its source file the two definitions. The class ID,
name and size come from CD2's arguments to the cClass constructor.
usage: py -I gen4.py <repo root> <scc json> [--write]"""
import json, os, re, struct, sys

root, spath = sys.argv[1], sys.argv[2]
write = '--write' in sys.argv
os.chdir(root)
sys.path.insert(0, 'tools')
import cd2  # noqa: E402

CCLASS = 0x8264A890
COUNTER = 0x832B6A4C
decl = set()
for dp, _, fs in os.walk('include'):
    for f in fs:
        if f.endswith('.h'):
            for m in re.finditer(r'^\s*(?:class|struct)\s+(\w+)\b', open(os.path.join(dp, f), errors='replace').read(), re.M):
                decl.add(m.group(1))
claims = cd2.claims()
man = {int(e['address'], 16) for es in cd2.manifest()['files'].values() for e in es}


def args(a, size):
    ws = struct.unpack('>%dI' % (size // 4), cd2.read(a, size))
    regs, hi, counter = {}, {}, False
    for i, w in enumerate(ws):
        op, rd, ra, imm = w >> 26, (w >> 21) & 31, (w >> 16) & 31, w & 0xFFFF
        if op == 15 and ra == 0:
            regs[rd] = imm << 16
            hi[rd] = imm << 16
        elif op == 14 and ra == 0:
            regs[rd] = imm - 0x10000 if imm & 0x8000 else imm
        elif op == 24 and rd in regs:
            regs[ra] = regs[rd] | imm
        elif op == 32 and ra in hi and rd == 4:
            lo = imm - 0x10000 if imm & 0x8000 else imm
            counter = (hi[ra] + lo) & 0xFFFFFFFF == COUNTER
        elif op == 18 and w & 1:
            d = w & 0x03FFFFFC
            if (a + 4 * i + (d - 0x04000000 if d & 0x02000000 else d)) & 0xFFFFFFFF == CCLASS:
                return ('counter' if counter else regs.get(4)), regs.get(6)
    return None, None


rows = [r for r in json.load(open(spath)) if r['status'] == 'open' and r['string'] and r['file']
        and int(r['address'], 16) not in man and r['string'] not in decl]
plan = []
for r in rows:
    head = open(r['file'], errors='replace').read(1500)
    m = re.search(r'Class: (\w+)(?: \(namespace: (\w+)\))?', head)
    if not m or m.group(1) != r['string']:
        continue
    cid, size = args(int(r['address'], 16), r['size'])
    if cid is None or size is None:
        continue
    plan.append(dict(r, cls=m.group(1), ns=m.group(2), cid=cid, csize=size))
print(len(rows), 'undeclared classes;', len(plan), 'planned;', sum(p['cid'] == 'counter' for p in plan), 'with the counter')
if not write:
    sys.exit(0)
items = []
for p in plan:
    cls, ns = p['cls'], p['ns']
    rel = '%s/%s.h' % (ns, cls) if ns else '%s.h' % cls
    hp = os.path.join('include', rel)
    if os.path.exists(hp):
        continue
    guard = re.sub(r'\W', '_', rel).upper()
    ptr = 'ms_p%sClass' % cls
    q = (ns + '::' if ns else '') + cls
    idtxt = 'g_nBehaviourClassID++' if p['cid'] == 'counter' else '0x%X' % p['cid']
    lines = ['// %s (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.' % q,
             '// StaticCreateClass (%s) builds cClass(%s, "%s", 0x%X); 0x%X is the size its registrar gives.'
             % (p['address'], 'the next behaviour class ID' if p['cid'] == 'counter' else '0x%X' % p['cid'], cls,
                p['csize'], p['csize']),
             '#ifndef %s' % guard, '#define %s' % guard, '', '#include "fun_runtime/class.h"', '']
    body = ['class %s' % cls, '{', 'public:', '    static const Fun_Runtime::cClass *%s;' % ptr,
            '    static Fun_Runtime::cClass &StaticCreateClass();', '};']
    lines += (['namespace %s' % ns, '{'] + ['    ' + l for l in body] + ['}']) if ns else body
    lines += ['', '#endif // %s' % guard, '']
    os.makedirs(os.path.dirname(hp), exist_ok=True)
    open(hp, 'w', encoding='utf-8', newline='').write('\n'.join(lines))
    src = p['file']
    s = open(src, encoding='utf-8-sig', newline='').read()
    nl = '\r\n' if '\r\n' in s else '\n'
    bom = open(src, 'rb').read(3) == b'\xef\xbb\xbf'
    fn = ['const Fun_Runtime::cClass *%s::%s = &%s::StaticCreateClass();' % (cls, ptr, cls), '',
          'Fun_Runtime::cClass &%s::StaticCreateClass()' % cls, '{',
          '    static Fun_Runtime::cClass *%sClass = new Fun_Runtime::cClass(%s, "%s", 0x%X);' % (cls, idtxt, cls, p['csize']),
          '    return *%sClass;' % cls, '}']
    add = ['', '#include "%s"' % rel, '#include "cd2/memory.h"']
    if p['cid'] == 'counter':
        add.append('#include "AI/BehaviourClassID.h"')
    add += [''] + ((['namespace %s' % ns, '{'] + ['    ' + l if l else l for l in fn] + ['}']) if ns else fn)
    open(src, 'w', encoding='utf-8-sig' if bom else 'utf-8', newline='').write(s.rstrip('\r\n') + nl + nl.join(add) + nl)
    nsq = (ns + '@@') if ns else '@'
    items.append(dict(source=src, header=hp, address=p['address'], symbol='?StaticCreateClass@%s@%s' % (cls, nsq),
                      ptr_symbol='??__E?%s@%s@%s' % (ptr, cls, nsq)))
json.dump(items, open(os.path.join(os.path.dirname(spath), 'gen4_written.json'), 'w'), indent=1)
print('wrote', len(items))
