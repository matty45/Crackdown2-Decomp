"""usage: cmpsym.py <t.pe> <t.map> <default.exe> <symbol-substring> <cd2 address> <size>"""
import os, struct, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ltcg_check import read_image, map_funcs, words, lenient_equal, pe_reader
pe_path, map_path, exe, sym, va, size = sys.argv[1:7]
va, size = int(va, 16), int(size)
rd = read_image(pe_path); fs = map_funcs(map_path)
a = [x for x, n in fs if sym in n][0]
nxt = [x for x, _ in fs if x > a]
lw = words(rd(a, (nxt[0] if nxt else a + size + 64) - a))
while lw and lw[-1] == 0: lw.pop()
tw = words(pe_reader(open(exe, 'rb').read())[0](va, size))
res = [lenient_equal(x, y) for x, y in zip(lw, tw)]
print('%s: ltcg %d words, cd2 %d words, %d equal (%d address-masked)' % (sym, len(lw), len(tw), sum(ok for ok, _ in res), sum(1 for ok, m in res if ok and m)))
for k, (x, y) in enumerate(zip(lw, tw)):
    if not lenient_equal(x, y)[0]: print('  +%03X ltcg %08X cd2 %08X' % (4 * k, x, y))
