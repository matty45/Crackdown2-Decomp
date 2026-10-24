"""Look for PGO hot/cold splitting in CD2: branches (b / bc, no link) that leave their .pdata function.
  into_start  : target is the first instruction of another function (tail call, or entry to a split-off fragment)
  into_middle : target is inside another function, not its start (never produced without code splitting)
  nowhere     : target is outside every .pdata function
Also: functions never called with bl and entered only by b/bc from other functions ("fragment-like").
usage: py -I pgo_scan.py <default.exe>
"""
import bisect, collections, struct, sys

d = open(sys.argv[1], 'rb').read()
pe = struct.unpack_from('<I', d, 0x3C)[0]
nsec = struct.unpack_from('<H', d, pe + 6)[0]
opt = struct.unpack_from('<H', d, pe + 20)[0]
base = struct.unpack_from('<I', d, pe + 24 + 28)[0]
secs = {}
for i in range(nsec):
    name, vs, va, rs, rp = struct.unpack_from('<8sIIII', d, pe + 24 + opt + 40 * i)
    secs[name.rstrip(b'\0').decode()] = (base + va, vs, rp, rs)
print('sections: ' + ', '.join('%s %08X+%X' % (n, v[0], v[1]) for n, v in secs.items()))


def word(va):
    for sva, vs, rp, rs in secs.values():
        if sva <= va < sva + min(vs, rs) - 3:
            return struct.unpack_from('>I', d, rp + va - sva)[0]
    return 0


pva, pvs, prp, prs = secs['.pdata']
funcs = []
for k in range(min(pvs, prs) // 8):
    start, packed = struct.unpack_from('>II', d, prp + 8 * k)
    n = (packed >> 8) & 0x3FFFFF
    if start and n:
        funcs.append((start, start + 4 * n, packed & 0xFF))
funcs.sort()
starts = [f[0] for f in funcs]


def find(a):
    i = bisect.bisect_right(starts, a) - 1
    if i >= 0 and funcs[i][0] <= a < funcs[i][1]:
        return i
    return None


def region(a):
    if 0x821D0000 <= a < 0x823D0000:
        return 'hot 821D-823D'
    if a < 0x82900000:
        return 'game 823D-8290'
    if a < 0x82F00000:
        return 'libs 8290-82F0'
    return 'init 82F0+'


stats = collections.defaultdict(collections.Counter)
called = set()
entered_by_branch = collections.defaultdict(set)
examples = collections.defaultdict(list)
for fi, (s, e, pl) in enumerate(funcs):
    for a in range(s, e, 4):
        w = word(a)
        op = w >> 26
        if op == 18:
            disp = w & 0x03FFFFFC
            if disp & 0x02000000:
                disp -= 0x04000000
            tgt = (disp if w & 2 else a + disp) & 0xFFFFFFFF
            link = w & 1
        elif op == 16:
            disp = w & 0xFFFC
            if disp & 0x8000:
                disp -= 0x10000
            tgt = (disp if w & 2 else a + disp) & 0xFFFFFFFF
            link = w & 1
        else:
            continue
        ti = find(tgt)
        if link:
            if ti is not None and funcs[ti][0] == tgt:
                called.add(ti)
            continue
        if ti == fi:
            continue
        kind = 'nowhere' if ti is None else ('into_start' if funcs[ti][0] == tgt else 'into_middle')
        kind += '_bc' if op == 16 else '_b'
        stats[region(a)][kind] += 1
        if ti is not None:
            entered_by_branch[ti].add(fi)
        if kind.startswith('into_middle') and len(examples[region(a)]) < 6:
            examples[region(a)].append('%08X -> %08X (inside %08X-%08X)' % (a, tgt, funcs[ti][0], funcs[ti][1]))
print('%d .pdata functions' % len(funcs))
kinds = ['into_start_b', 'into_start_bc', 'into_middle_b', 'into_middle_bc', 'nowhere_b', 'nowhere_bc']
print('%-16s' % 'region' + ''.join('%15s' % k for k in kinds))
for r in sorted(stats):
    print('%-16s' % r + ''.join('%15d' % stats[r][k] for k in kinds))
for r in sorted(examples):
    print('examples, %s:' % r)
    for x in examples[r]:
        print('   ' + x)
frag = [i for i in entered_by_branch if i not in called]
by = collections.Counter(region(funcs[i][0]) for i in frag)
print('functions never bl-called but entered by b/bc from other functions: %d  %s' % (len(frag), dict(by)))
print('  of which prolog length 0: %d' % sum(1 for i in frag if funcs[i][2] == 0))

# --- group into_middle branches by target function
mid = collections.defaultdict(lambda: [0, set()])
for fi, (s, e, pl) in enumerate(funcs):
    for a in range(s, e, 4):
        w = word(a)
        op = w >> 26
        if op not in (16, 18) or w & 1:
            continue
        if op == 18:
            disp = w & 0x03FFFFFC
            if disp & 0x02000000: disp -= 0x04000000
        else:
            disp = w & 0xFFFC
            if disp & 0x8000: disp -= 0x10000
        tgt = (disp if w & 2 else a + disp) & 0xFFFFFFFF
        ti = find(tgt)
        if ti is None or ti == fi or funcs[ti][0] == tgt:
            continue
        mid[ti][0] += 1
        mid[ti][1].add(fi)
print('\ninto_middle targets: %d distinct functions' % len(mid))
for ti, (n, src) in sorted(mid.items(), key=lambda kv: -kv[1][0])[:12]:
    s, e, pl = funcs[ti]
    print('  %08X-%08X (%3d insns, prolog %d): %6d branches from %5d functions; first words %s'
          % (s, e, (e - s) // 4, pl, n, len(src), ' '.join('%08X' % word(s + 4 * k) for k in range(3))))
rest = {ti: v for ti, v in mid.items() if len(v[1]) < 20}
print('targets entered mid-function from fewer than 20 functions: %d (total %d branches)' % (len(rest), sum(v[0] for v in rest.values())))
for ti, (n, src) in list(rest.items())[:10]:
    s, e, pl = funcs[ti]
    print('  %08X-%08X  %d branches from %s' % (s, e, n, ', '.join('%08X' % funcs[x][0] for x in list(src)[:4])))
