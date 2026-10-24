import json, sys, collections, re
p = json.load(open(sys.argv[1]))
mods, contribs = p['mods'], p['contribs']
# code bytes per module (section 1..n with CNT_CODE 0x20)
code = collections.Counter()
for sec, off, size, ch, mi in contribs:
    if ch & 0x20:
        code[mi] += size
def lib_of(m):
    o = m['obj']
    return o.split('\\')[-1].lower() if o.lower().endswith('.lib') else '(game obj)'
groups = collections.defaultdict(lambda: [0, 0, collections.Counter()])
for m in mods:
    g = groups[lib_of(m)]
    g[0] += 1; g[1] += code[m['i']]; g[2][m.get('compile', {}).get('be')] += 1
tot = sum(code.values())
print('total code bytes in contributions: %.2f MB' % (tot / 1e6))
for k, (n, b, c) in sorted(groups.items(), key=lambda x: -x[1][1])[:45]:
    print('%-34s mods=%4d code=%6.2fMB %5.1f%%  compilers=%s' % (k[:34], n, b / 1e6, 100 * b / tot, dict(c.most_common(2))))
# game obj source roots
roots = collections.Counter()
for m in mods:
    if lib_of(m) == '(game obj)':
        nm = m['name'].lower()
        roots['\\'.join(nm.split('\\')[:4])] += code[m['i']]
print('game obj roots:', [(k, round(v / 1e6, 2)) for k, v in roots.most_common(15)])
