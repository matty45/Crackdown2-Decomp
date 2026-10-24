import collections, struct, sys
sys.argv = [sys.argv[0], sys.argv[1]]
exec(open(sys.argv[0].replace('constref.py', 'pgo_scan.py')).read().split('stats = collections')[0])
targets = {0x820F7680: '0.0f', 0x8208E84C: '1.0f'}
def region(a):
    return 'hot' if 0x821D0000 <= a < 0x823D0000 else 'game' if a < 0x82900000 else 'libs' if a < 0x82F00000 else 'init'
hits = collections.defaultdict(collections.Counter)
POOL = 0x820F8C80
pool_vals = collections.Counter()
for s, e, pl in funcs:
    lis = {}
    for a in range(s, e, 4):
        w = word(a); op = w >> 26; rt = (w >> 21) & 31; ra = (w >> 16) & 31; imm = w & 0xFFFF
        sx = imm - 0x10000 if imm & 0x8000 else imm
        if op == 15 and ra == 0: lis[rt] = imm << 16; continue
        if op in (48, 50) and ra in lis:
            t = (lis[ra] + sx) & 0xFFFFFFFF
            if t in targets: hits[targets[t]][region(s)] += 1
for k, v in hits.items(): print('%s direct loads by region: %s' % (k, dict(v)))
# where does the pool keep 0.0 and 1.0?
pool = [word(POOL + 4 * i) for i in range(0x2000)]
for val, name in ((0x00000000, '0.0f'), (0x3F800000, '1.0f')):
    offs = [4 * i for i, w in enumerate(pool) if w == val][:5]
    print('%s in pool at offsets %s' % (name, ', '.join('+%X' % o for o in offs)))
print('word at 0x820F7680..: ' + ' '.join('%08X' % word(0x820F7680 + 4 * i) for i in range(8)))
print('word at 0x8208E840..: ' + ' '.join('%08X' % word(0x8208E840 + 4 * i) for i in range(8)))
