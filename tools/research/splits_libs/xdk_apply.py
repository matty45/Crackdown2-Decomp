"""Fold the XDK 9328 library identities (xdk_libmatch.py) into config/library_splits.txt.

A CD2 function is taken from the XDK when its identity is unambiguous: every library function it matches lies in one
object (release, instrumented, LTCG and debug variants of a library count as one), and each of those library
functions matches no other CD2 function. Rules, in order: game files (config/splits.txt) win; an XDK identity of at
least 100 bytes replaces a different existing object (smaller ones are generic shapes, such as destructors); one of at
least 32 bytes fills an unassigned function outside the game span (game objects hold inline copies); unassigned
functions between two XDK identities of one object join it (the linker lays out objects contiguously). Everything else
keeps its RuffKing-derived assignment.
usage: py -I tools/research/splits_libs/xdk_apply.py <xdk_ident json> [--write]"""
import bisect, collections, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
os.chdir(ROOT)
import cd2  # noqa: E402

write = '--write' in sys.argv
ident = json.load(open(sys.argv[1]))
syms = cd2.jeff_symbols()
order = sorted(syms)
pos = {a: i for i, a in enumerate(order)}
libfiles = {f.lower() for f in os.listdir(os.path.join(cd2.XDK, 'lib', 'xbox'))}


def norm(lib):
    b = lib.lower()[:-4]
    for suf in ('ltcgi', 'ltcg', 'i', 'd'):
        if b.endswith(suf) and (b[:-len(suf)] + '.lib') in libfiles:
            return b[:-len(suf)]
    return b


HOT = (0x821D0000, 0x823D0000)
INIT = 0x82F00000
# existing assignment, per function
cur, labels, existing, kind = None, {}, {}, {}
header = []
for line in open('config/library_splits.txt', encoding='utf-8'):
    if line.startswith('#') and not existing and cur is None:
        header.append(line.rstrip('\n'))
        continue
    s = line.split('#')[0].strip()
    m = re.match(r'^(\S+\.lib)\((.+)\)$', s) or re.match(r'^(\S+\.obj)$', s)
    if m:
        cur = s
        if m.lastindex == 2:
            labels.setdefault((norm(m.group(1)), m.group(2).lower()), s)
        continue
    m = re.match(r'^text\s+0x([0-9A-Fa-f]+)\s+0x([0-9A-Fa-f]+)', s)
    if m and cur:
        a0, a1 = int(m.group(1), 16), int(m.group(2), 16)
        for a in order[bisect.bisect_left(order, a0):bisect.bisect_left(order, a1)]:
            existing[a] = (cur, 'rk')
            kind[a] = 'text'
        continue
    m = re.match(r'^(hot|init)\s+0x([0-9A-Fa-f]+)', s)
    if m and cur:
        existing[int(m.group(2), 16)] = (cur, 'rk')
        kind[int(m.group(2), 16)] = m.group(1)
splits = cd2.load_splits(cd2.SPLITS)
lib_name = collections.Counter()
for (n, o), lab in labels.items():
    lib_name[(n, lab.split('(')[0])] += 1
preferred = {}
for (n, f), c in sorted(lib_name.items(), key=lambda x: -x[1]):
    preferred.setdefault(n, f)

# unambiguous XDK identities
hits = collections.defaultdict(set)
for a, cands in ident.items():
    for l, o, nm, _ in cands:
        hits[(norm(l), o.lower(), nm)].add(a)
xdk, xdk_name = {}, {}
for a, cands in ident.items():
    objs = {(norm(l), o.lower()) for l, o, _, _ in cands}
    if len(objs) != 1 or not all(len(hits[(norm(l), o.lower(), nm)]) == 1 for l, o, nm, _ in cands):
        continue
    n, o = next(iter(objs))
    member = [c[1] for c in cands if norm(c[0]) == n][0]
    lab = labels.get((n, o)) or '%s(%s)' % (preferred.get(n) or [c[0] for c in cands if norm(c[0]) == n][0], member)
    xdk[int(a, 16)] = lab
    xdk_name[int(a, 16)] = cands[0][2]

assign = dict(existing)
how = collections.Counter()
for a, lab in xdk.items():
    if cd2.owner(a, splits):
        how['skipped: in a game file'] += 1
        continue
    n = syms[a][1]
    ex = assign.get(a)
    if ex and ex[0] == lab:
        assign[a] = (lab, 'xdk')
        how['confirmed'] += 1
    elif ex and n >= 100:
        assign[a] = (lab, 'xdk')
        how['corrected'] += 1
    elif not ex and n >= 32 and not 0x823D0000 <= a < 0x82913700:
        assign[a] = (lab, 'xdk')
        how['new'] += 1
    else:
        how['kept (too small to decide)'] += 1
# contiguity between XDK identities of one object
xs = sorted(a for a, v in assign.items() if v[1] == 'xdk')
for a, b in zip(xs, xs[1:]):
    if assign[a][0] != assign[b][0]:
        continue
    mid = order[pos[a] + 1:pos[b]]
    if mid and all(m not in assign and not cd2.owner(m, splits) for m in mid):
        for m in mid:
            assign[m] = (assign[a][0], 'xdk-contiguity')
            how['contiguity'] += 1
print(dict(how), '; functions assigned now:', len(assign), '(before: %d)' % len(existing))
if '--report' in sys.argv:
    for a in sorted(a for a in assign if a in existing and assign[a][1] == 'xdk' and existing[a][0] != assign[a][0]):
        print('corrected 0x%08X %5d  %s -> %s' % (a, syms[a][1], existing[a][0], assign[a][0]))
    new = [a for a in assign if a not in existing]
    print('new by region:', dict(collections.Counter(
        'order list' if HOT[0] <= a < HOT[1] else 'game span' if 0x823D0000 <= a < 0x82913700 else 'init' if a >= INIT
        else 'library span' for a in new)))
    print('new in the game span:', [('0x%08X' % a, assign[a][0]) for a in sorted(new) if 0x823D0000 <= a < 0x82913700][:12])
if not write:
    sys.exit(0)

blocks, singles = [], collections.defaultdict(list)
for a in order:
    if a not in assign:
        continue
    lab, h = assign[a]
    by_name = ('hot' if HOT[0] <= a < HOT[1] else 'init' if xdk_name.get(a, '').startswith(('??__E', '??__F'))
               else 'text')
    k = by_name if h.startswith('xdk') and a in xdk_name else (kind.get(a) or by_name)
    if k != 'text':
        singles[lab].append((a, h, k))
        continue
    if blocks and blocks[-1][0] == lab and pos[a] == pos[blocks[-1][2]] + 1:
        blocks[-1][2] = a
        blocks[-1][3][h] += 1
    else:
        blocks.append([lab, a, a, collections.Counter({h: 1})])
per = collections.defaultdict(list)
for b in blocks:
    per[b[0]].append(b)
for lab in singles:
    per.setdefault(lab, [])
i = header.index('#   init <addr>             one of its functions in the initializer region (from 0x82F00000)')
evidence = [
    '#',
    '# XDK libraries (2026-11-01, tools/research/splits_libs/xdk_libmatch.py, xdk_apply.py): CD2 was built with XDK',
    '# 9328, whose own library objects are compared with CD2 directly. A function is taken from them when its masked',
    '# code equals a library function exactly (coff.compare, the library\'s relocations masked), every match lies in one',
    '# object, and each of those library functions matches no other CD2 function. Such an identity of at least 100',
    '# bytes replaces a RuffKing-derived object (RuffKing was built with an older XDK, whose objects are cut',
    '# differently), one of at least 32 bytes fills an unassigned function outside the game span (0x823D0000-0x82913700,',
    '# where game objects hold inline copies), and unassigned functions between two of one object join it.',
    '# Counts per block: RuffKing-derived (rk) / XDK identity (xdk) / XDK contiguity.']
lines = header[:] + evidence + ['']
key = lambda x: min([b[1] for b in x[1]] + [a for a, _, _ in singles.get(x[0], [])])
n_fun = 0
for lab, bs in sorted(per.items(), key=key):
    lines.append(lab)
    for a, h, k in sorted(singles.get(lab, [])):
        lines.append('  %s 0x%08X   # %s' % (k, a, 'XDK identity' if h.startswith('xdk') else 'RuffKing-derived'))
        n_fun += 1
    for b in bs:
        end = b[2] + syms[b[2]][1]
        n = sum(b[3].values())
        n_fun += n
        lines.append('  text 0x%08X 0x%08X   # %d functions: %d rk / %d xdk / %d contiguity%s' % (
            b[1], end, n, b[3]['rk'], b[3]['xdk'], b[3]['xdk-contiguity'], '; several blocks: review' if len(bs) > 1 else ''))
    lines.append('')
open('config/library_splits.txt', 'w', newline='\n').write('\n'.join(lines))
print('%d objects, %d blocks, %d functions written' % (len(per), len(blocks), n_fun))
