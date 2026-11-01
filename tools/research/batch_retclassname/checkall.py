"""Run `cd2.py check` on every written source file (in parallel) and report each claimed function's status.
usage: py -I checkall.py <repo root> <written json> <out json>"""
import concurrent.futures, json, os, subprocess, sys

root, wpath, out = sys.argv[1], sys.argv[2], sys.argv[3]
os.chdir(root)
w = json.load(open(wpath))


def one(x):
    r = subprocess.run([sys.executable, '-I', 'tools/cd2.py', 'check', x['source'], '--json'], capture_output=True,
                       text=True)
    try:
        d = json.loads(r.stdout)
    except ValueError:
        return dict(x, status='check failed', detail=(r.stdout + r.stderr)[-600:])
    if d.get('error'):
        return dict(x, status='error', detail=str(d.get('error'))[-600:])
    f = [f for f in d.get('functions', []) if f['address'] == x['address']]
    if not f:
        return dict(x, status='not compared', detail=str(d)[-300:])
    return dict(x, status=f[0].get('status'), rules=f[0].get('rules'), size=f[0].get('size'))


with concurrent.futures.ThreadPoolExecutor(4) as pool:
    res = list(pool.map(one, w))
json.dump(res, open(out, 'w'), indent=1)
import collections  # noqa: E402
print(collections.Counter(r['status'] for r in res))
for r in res:
    if r['status'] != 'EXACT':
        print(r['address'], r['source'], r['status'], (r.get('detail') or '')[:300])
