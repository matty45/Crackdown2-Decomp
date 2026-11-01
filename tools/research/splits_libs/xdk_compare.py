"""Compare the XDK library identities (xdk_libmatch.py) with config/library_splits.txt and config/splits.txt.
usage: py -I tools/research/splits_libs/xdk_compare.py <xdk_ident json> <out json>"""
import bisect, collections, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
os.chdir(ROOT)
import cd2  # noqa: E402

ident = json.load(open(sys.argv[1]))
syms = cd2.jeff_symbols()


def norm_lib(lib):
    """d3d9i.lib / d3d9ltcg.lib / d3d9.lib -> d3d9 (debug variants end in d: kept apart)."""
    b = lib.lower()[:-4]
    for suf in ('ltcgi', 'ltcg', 'i'):
        if b.endswith(suf) and b[:-len(suf)] in ('d3d9', 'd3dx9', 'xapilib', 'x3daudio', 'xact3', 'xmahal', 'xmcore'):
            return b[:-len(suf)]
    return b


# library_splits.txt: [start, end) -> (lib, object); hot/init single addresses
blocks, single = [], {}
cur = None
for line in open('config/library_splits.txt', encoding='utf-8'):
    s = line.split('#')[0].strip()
    m = re.match(r'^(\S+\.lib)\((.+)\)$', s)
    if m:
        cur = (m.group(1), m.group(2))
        continue
    m = re.match(r'^text\s+0x([0-9A-Fa-f]+)\s+0x([0-9A-Fa-f]+)', s)
    if m and cur:
        blocks.append((int(m.group(1), 16), int(m.group(2), 16), cur))
        continue
    m = re.match(r'^(hot|init)\s+0x([0-9A-Fa-f]+)', s)
    if m and cur:
        single[int(m.group(2), 16)] = cur
blocks.sort()
starts = [b[0] for b in blocks]
splits = cd2.load_splits(cd2.SPLITS)


def lib_owner(a):
    if a in single:
        return single[a]
    i = bisect.bisect_right(starts, a) - 1
    if i >= 0 and blocks[i][0] <= a < blocks[i][1]:
        return blocks[i][2]
    return None


res = collections.Counter()
rows = collections.defaultdict(list)
for a_s, cands in ident.items():
    a = int(a_s, 16)
    objs = {(norm_lib(l), o.lower()) for l, o, _, _ in cands}
    names = sorted({n for _, _, n, _ in cands})
    game = cd2.owner(a, splits)
    lo = lib_owner(a)
    if game:
        kind = 'inside a game file'
    elif lo is None:
        kind = 'new'
    elif (norm_lib(lo[0]), lo[1].lower()) in objs:
        kind = 'confirmed'
    elif any(o == lo[1].lower() for _, o in objs):
        kind = 'confirmed (other library variant)'
    else:
        kind = 'different object'
    res[kind] += 1
    rows[kind].append(dict(address=a_s, size=syms[a][1] if a in syms else None, xdk=sorted(objs), names=names[:3],
                           library_splits=('%s(%s)' % lo) if lo else None, game_file=game))
json.dump(rows, open(sys.argv[2], 'w'), indent=1)
print(dict(res))
for k in ('inside a game file', 'different object'):
    for r in rows[k][:8]:
        print('  %-18s %s %s xdk=%s splits=%s %s' % (k[:18], r['address'], r['size'], r['xdk'][:2], r['library_splits'],
                                                   r['game_file'] or ''))
print('new, by object:', collections.Counter(r['xdk'][0][1] for r in rows['new']).most_common(10))
