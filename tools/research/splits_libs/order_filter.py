"""Keep only new init/atexit entries that respect link order: files sorted by text start; a file's new entry in an area
(init or atexit) must lie between the previous file's and the next file's existing entries in that area (nearest files
that have one). usage: py -I order_filter.py <work dir>   (rewrites initnew.json)"""
import sys, json, os, bisect
sys.path.insert(0, 'tools')
import cd2
from check_integrity import load_splits

W = sys.argv[1]
d = json.load(open(os.path.join(W, 'initnew.json')))
sp = load_splits(os.path.join(W, 'splits.before_init.txt'))
order = sorted((e['text'][0], f) for f, e in sp.items() if e['text'])
files = [f for _, f in order]
kept, dropped = {}, 0
for f, addrs in d['new'].items():
    if f not in sp or not sp[f]['text']:
        dropped += len(addrs)
        continue
    i = files.index(f)
    for a in addrs:
        kind = 'init' if a <= d['init_max'] else 'atexit'
        prev = [max(sp[g][kind]) for g in files[:i] if sp[g][kind]]
        nxt = [min(sp[g][kind]) for g in files[i + 1:] if sp[g][kind]]
        lo = prev[-1] if prev else 0
        hi = nxt[0] if nxt else 0xFFFFFFFF
        own = sp[f][kind]
        if lo < a < hi and (not own or True):
            kept.setdefault(f, []).append(a)
        else:
            dropped += 1
print('kept %d, dropped %d out-of-order entries' % (sum(len(v) for v in kept.values()), dropped))
d['new'] = kept
json.dump(d, open(os.path.join(W, 'initnew.json'), 'w'))
