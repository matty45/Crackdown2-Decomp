import sys
sys.argv = [sys.argv[0], sys.argv[1], sys.argv[2], sys.argv[3]]
lo, hi = int(sys.argv[2], 16), int(sys.argv[3], 16)
exec(open(sys.argv[0].replace('constform.py', 'pgo_scan.py')).read().split('stats = collections')[0])
POOL = 0x820F8C80
for s, e, pl in funcs:
    if not (lo <= s < hi): continue
    lis, anc = {}, {}
    direct, pooled = [], []
    for a in range(s, e, 4):
        w = word(a); op = w >> 26; rt = (w >> 21) & 31; ra = (w >> 16) & 31; imm = w & 0xFFFF
        sx = imm - 0x10000 if imm & 0x8000 else imm
        if op == 15 and ra == 0: lis[rt] = imm << 16; anc.pop(rt, None); continue
        if op == 14 and ra in lis and ra != 0:
            t = (lis[ra] + sx) & 0xFFFFFFFF
            if t == POOL: anc[rt] = t
            continue
        if op in (48, 50):
            if ra in lis: direct.append((lis[ra] + sx) & 0xFFFFFFFF)
            elif ra in anc: pooled.append(POOL + sx)
    if direct or pooled:
        v = lambda t: '%g' % struct.unpack('>f', struct.pack('>I', word(t)))[0]
        print('%08X %4d insns  direct: %-40s pool: %s' % (s, (e - s) // 4, ' '.join('%s@%X' % (v(t), t) for t in direct), ' '.join('%s@+%X' % (v(t), t - POOL) for t in pooled)))
