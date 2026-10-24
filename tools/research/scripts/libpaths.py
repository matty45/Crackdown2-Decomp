import json, sys, collections, re
for f in ('ruff_pdb.json', 'burn_pdb.json'):
    p = json.load(open(sys.argv[1] + '\\' + f))
    paths = collections.OrderedDict()
    for m in p['mods']:
        o = m['obj'].lower(); n = m['name'].lower()
        for key in ('hk', 'gfx', 'ak', 'rwai', 'morpheme', 'kaim', 'kynapse', 'lua', 'zlib', 'bink'):
            if o.endswith('.lib') and o.split('\\')[-1].startswith(key):
                paths.setdefault(key, set()).add((o.rsplit('\\', 1)[0][-90:], n.rsplit('\\', 1)[0][-90:]))
    print('==', f)
    for k, v in paths.items():
        for x in sorted(v)[:2]:
            print('  %-8s lib-dir=%s | obj-dir=%s' % (k, x[0], x[1]))
