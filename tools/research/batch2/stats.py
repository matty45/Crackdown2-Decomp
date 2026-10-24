import glob, json, os, sys
S = sys.argv[1]
packets = {'cChaseBehaviour': S + r'\batch2\cChaseBehaviour_r2\cChaseBehaviour',
           'cFlocket': S + r'\batch2\cFlocket\cFlocket',
           'cHelicopterController': S + r'\batch2\cHelicopterController\cHelicopterController'}
tot = {}
for cls, p in packets.items():
    res = json.load(open(os.path.join(p, 'results.json')))
    sizes = {os.path.basename(d).split('_')[0]: len(open(os.path.join(d, 'target.hex')).read().strip()) // 2
             for d in glob.glob(os.path.join(p, 'targets', 'F*_*'))}
    rows = {}
    for f in res['functions']:
        if f.get('belongs') is not True:
            continue
        kind = f.get('kind', '?')
        b = sizes.get(f['id'], 0)
        r = rows.setdefault(kind, [0, 0, 0, 0])
        r[0] += 1; r[1] += b
        if f.get('exact'):
            r[2] += 1; r[3] += b
    print(cls)
    for kind, (n, b, ne, be) in sorted(rows.items()):
        print('   %-18s %2d/%2d functions exact, %5d/%5d bytes (%.0f%%)' % (kind, ne, n, be, b, 100.0 * be / max(b, 1)))
        t = tot.setdefault(kind, [0, 0, 0, 0])
        for i, v in enumerate((n, b, ne, be)):
            t[i] += v
print('BATCH 2 TOTAL')
for kind, (n, b, ne, be) in sorted(tot.items()):
    print('   %-18s %2d/%2d functions exact, %5d/%5d bytes (%.0f%%)' % (kind, ne, n, be, b, 100.0 * be / max(b, 1)))
n = sum(v[0] for v in tot.values()); b = sum(v[1] for v in tot.values()); ne = sum(v[2] for v in tot.values()); be = sum(v[3] for v in tot.values())
print('   %-18s %2d/%2d functions exact, %5d/%5d bytes (%.0f%%)' % ('all', ne, n, be, b, 100.0 * be / b))
