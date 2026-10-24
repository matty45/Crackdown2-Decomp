import sys, os, glob
S = sys.argv[1]
sys.path.insert(0, S)
import coff
def funcs(d):
    out = {}
    for o in glob.glob(d + r'\*.obj'):
        for n, c, r in coff.functions(o):
            out[n] = c
    return out
a = funcs(S + r'\build\atg_8153'); b = funcs(S + r'\build\atg_8327')
common = set(a) & set(b)
diff = [n for n in common if a[n] != b[n]]
print('ATG C++ functions compiled by both: %d, byte-different: %d' % (len(common), len(diff)), diff[:10])

