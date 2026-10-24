import json, sys, collections, bisect, re
S = sys.argv[1]
REFS = {'ruff': 0x822d0000, 'burn': 0x82470000}
load = lambda n: [json.loads(l) for l in open(S + '\\' + n + '_funcs.jsonl')]
cd2 = sorted(load('cd2'), key=lambda r: r['ea'])

GROUPS = [('Havok', r'^hk'), ('Wwise', r'^ak'), ('Scaleform', r'^(libgfx|gfcore|libgrenderer|libas[23])'),
          ('Kynapse', r'^rwai'), ('morpheme', r'^morpheme'), ('CRT', r'^(libc|libcp|libcmt)'),
          ('XDK', r'^(x|d3d|tracerc|vincexe|nui|st\.lib)'), ('jpeg/zlib/misc', r'^(libjpeg|zlib|transport|tickettracker|cameralib|msmodal)')]
def group(lib):
    for g, p in GROUPS:
        if re.match(p, lib):
            return g
    return 'other-lib:' + lib

def labeller(name, base):
    pdb = json.load(open(S + '\\%s_pdb.json' % name))
    mods = pdb['mods']
    code = [c for c in pdb['contribs'] if c[3] & 0x20]
    tsec = collections.Counter(c[0] for c in code).most_common(1)[0][0]
    code = sorted((c for c in code if c[0] == tsec), key=lambda c: c[1])
    starts = [c[1] for c in code]
    def lab(ea):
        off = ea - base
        i = bisect.bisect_right(starts, off) - 1
        if i < 0 or not (code[i][1] <= off < code[i][1] + code[i][2]):
            return None
        m = mods[code[i][4]]
        o = m['obj'].lower()
        if o.endswith('.lib'):
            return group(o.split('\\')[-1])
        if '* linker *' in m['name'].lower():
            return None
        return 'GAME'
    return lab

labels = {}
ia = collections.Counter(r['hl'] for r in cd2)
sa = collections.Counter(tuple(r['strs']) for r in cd2 if r['strs'])
for name, base in REFS.items():
    ref = load(name); lab = labeller(name, base)
    ib = collections.Counter(r['hl'] for r in ref); byh = {r['hl']: r for r in ref}
    sb = collections.defaultdict(list)
    for r in ref:
        if r['strs']:
            sb[tuple(r['strs'])].append(r)
    for r in cd2:
        if r['ea'] in labels:
            continue
        o = None
        if r['n'] >= 6 and ia[r['hl']] == 1 and ib.get(r['hl']) == 1:
            o = byh[r['hl']]
        elif r['strs'] and sa[tuple(r['strs'])] == 1 and len(sb.get(tuple(r['strs']), [])) == 1:
            o = sb[tuple(r['strs'])][0]
        if o:
            l = lab(o['ea'])
            if l:
                labels[r['ea']] = l
direct = len(labels)
# gap fill between agreeing labelled neighbours
eas = [r['ea'] for r in cd2]
lab_idx = [i for i, e in enumerate(eas) if e in labels]
filled = dict(labels)
for a, b in zip(lab_idx, lab_idx[1:]):
    la, lb = labels[eas[a]], labels[eas[b]]
    if la == lb:
        for i in range(a + 1, b):
            filled[eas[i]] = la
size = {r['ea']: r['size'] for r in cd2}
tot = sum(size.values())
by = collections.Counter()
for e in eas:
    by[filled.get(e, 'UNKNOWN')] += size[e]
print('CD2 funcs: %d, directly labelled %d, after gap fill %d' % (len(eas), direct, len(filled)))
for k, v in by.most_common():
    print('  %-22s %6.2f MB  %5.1f%%' % (k, v / 1e6, 100.0 * v / tot))
json.dump({str(k): v for k, v in filled.items()}, open(S + r'\cd2_labels.json', 'w'))
