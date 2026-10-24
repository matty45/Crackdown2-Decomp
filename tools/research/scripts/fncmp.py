import re, json, sys, collections, bisect
S = sys.argv[1]
asm = open(S + r'\jeffwork2\out\asm\auto_02_821D0000_text.s').read()
jeff = {}
for m in re.finditer(r'# \.text:0x[0-9A-F]+ \| 0x([0-9A-F]{8}) \| size: 0x([0-9A-F]+)\n\.fn (\S+),', asm):
    jeff[int(m.group(1), 16)] = int(m.group(2), 16)
ida = {r['ea']: r['size'] for r in (json.loads(l) for l in open(S + r'\cd2_funcs.jsonl'))}
pdata = json.load(open(S + r'\cd2_pdata.json'))
pd = {int(k): v for k, v in pdata.items()}
J, I, P = set(jeff), set(ida), set(pd)
print('jeff=%d ida=%d pdata=%d' % (len(J), len(I), len(P)))
print('ida & jeff=%d  jeff-only=%d  ida-only=%d' % (len(I & J), len(J - I), len(I - J)))
print('pdata covered: by ida %d, by jeff %d' % (len(P & I), len(P & J)))
# jeff-only starts: inside an IDA function (split) or in a gap?
istarts = sorted(I)
def ida_owner(ea):
    i = bisect.bisect_right(istarts, ea) - 1
    if i >= 0 and istarts[i] <= ea < istarts[i] + ida[istarts[i]]:
        return istarts[i]
cat = collections.Counter(); sz = collections.Counter()
for ea in J - I:
    o = ida_owner(ea)
    k = 'inside IDA func' if o else 'in IDA gap'
    cat[k] += 1; sz[k] += jeff[ea]
print('jeff-only:', dict(cat), 'bytes:', dict(sz))
small = collections.Counter(min(jeff[ea], 64) // 8 * 8 for ea in J - I)
print('jeff-only size histogram (<=64 bucketed):', sorted(small.items()))
cat2 = collections.Counter()
for ea in I - J:
    cat2['ida-only size<=8' if ida[ea] <= 8 else 'ida-only larger'] += 1
print(dict(cat2))
# size agreement where both
agree = sum(1 for ea in I & J if ida[ea] == jeff[ea])
print('same start & same size: %d of %d' % (agree, len(I & J)))
