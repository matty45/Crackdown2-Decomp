"""Sweep: functions a source file already defines but nobody claimed. For each file, compile it; for each compiled
function not in the manifest or the claims, compare it with the file's open functions of the same size; propose it
when exactly one matches byte for byte (masked relocations). Proposals still go through claim + check.
usage: py -I sweep.py <repo root> <tasks json> <out json>"""
import collections, concurrent.futures, json, os, re, sys

root, tpath, out = sys.argv[1], sys.argv[2], sys.argv[3]
os.chdir(root)
sys.path.insert(0, 'tools')
import cd2, coff  # noqa: E402

open_by_file = collections.defaultdict(list)
for t in json.load(open(tpath))['tasks']:
    if t['status'] == 'open' and t['size'] >= 12:
        open_by_file[t['file']].append((int(t['address'], 16), t['size']))
man = cd2.manifest()['files']
known = {e['symbol'] for es in man.values() for e in es} | {c['symbol'] for c in cd2.claims().values()}


def prefix(name):
    i = name.find('@@')
    return name[:i + 2] if name.startswith('?') and i > 0 else name


def one(src):
    if not open_by_file.get(src):
        return []
    try:
        obj = cd2.compile_file(src)
    except Exception:
        return []
    props = []
    for name, code, rl in coff.functions(obj):
        p = prefix(name)
        if any(k in name for k in known) or len(code) < 12:
            continue
        hits = [a for a, n in open_by_file[src] if n == len(code) and coff.compare(code, cd2.read(a, n), rl)[0]]
        if len(hits) == 1:
            props.append(dict(source=src, address='0x%08X' % hits[0], symbol=p, name=name))
    return props


files = sorted(f for f in open_by_file if cd2.has_code(f))
with concurrent.futures.ThreadPoolExecutor(4) as pool:
    res = [x for r in pool.map(one, files) for x in r]
seen = collections.Counter(x['address'] for x in res)
res = [x for x in res if seen[x['address']] == 1]
symseen = collections.Counter((x['source'], x['symbol']) for x in res)
res = [x for x in res if symseen[(x['source'], x['symbol'])] == 1]
json.dump(res, open(out, 'w'), indent=1)
print(len(files), 'files compiled;', len(res), 'proposals')
print(collections.Counter(re.sub(r'@.*', '', x['symbol']) for x in res).most_common(12))
