"""Replace placeholder descriptor definitions `ms_p<X>Class = 0;` with CD2's `= &<Class>::StaticCreateClass();` where
the class's StaticCreateClass is matched and its initializer is open; add RetClass where it is open and undefined.
usage: py -I rc_fix0.py <repo root> <plan json> [--write]"""
import json, os, re, sys

root, ppath = sys.argv[1], sys.argv[2]
write = '--write' in sys.argv
os.chdir(root)
plan = [p for p in json.load(open(ppath)) if p['src_has_ptr'] and p['init_open']]
out = []
for p in plan:
    s = open(p['file'], encoding='utf-8-sig', newline='').read()
    m = re.search(r'(\b%s::(ms_p\w*Class))\s*=\s*0\s*;' % re.escape(p['cls']), s)
    if not m:
        print('no placeholder definition:', p['cls'])
        continue
    ptr = m.group(2)
    s2 = s[:m.start()] + '%s = &%s::StaticCreateClass();' % (m.group(1), p['cls']) + s[m.end():]
    nsq = (p['ns'] + '@@') if p['ns'] else '@'
    items = [dict(source=p['file'], address=p['init'], symbol='??__E?%s@%s@%s' % (ptr, p['cls'], nsq))]
    if p['retclass'] and not re.search(r'\b%s::RetClass\(\)' % re.escape(p['cls']), s):
        print('RetClass open but undefined (not handled):', p['cls'])
    if write:
        bom = open(p['file'], 'rb').read(3) == b'\xef\xbb\xbf'
        open(p['file'], 'w', encoding='utf-8-sig' if bom else 'utf-8', newline='').write(s2)
    out += items
json.dump(out, open(os.path.join(os.path.dirname(ppath), 'fix0_items.json'), 'w'), indent=1)
print(len(plan), 'planned;', len(out), 'definitions', 'replaced' if write else 'to replace')
