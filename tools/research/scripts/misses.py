import json, os, sys, glob
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import coff
S = os.path.dirname(os.path.abspath(__file__))
target = {k: bytes.fromhex(v['bytes']) for k, v in json.load(open(S + r'\cd2_lua_bytes.json')).items()}
outdir = S + '\\build\\' + sys.argv[1]
for obj in glob.glob(outdir + r'\*.obj'):
    for name, code, rel in coff.functions(obj):
        k = name.lstrip('.').lstrip('_')
        if k in target:
            e, r = coff.compare(code, target[k], rel)
            if not e:
                t = target[k]
                diff = [w for w in range(min(len(code), len(t)) // 4) if code[w*4:w*4+4] != t[w*4:w*4+4] and not (w*4 in rel and code[w*4] >> 2 == t[w*4] >> 2)]
                print('%-20s obj=%4dB cd2=%4dB ratio=%.2f first-diff-words=%s' % (k, len(code), len(t), r, diff[:6]))
                for w in diff[:3]:
                    print('     +%03x  obj=%s  cd2=%s' % (w*4, code[w*4:w*4+4].hex(), t[w*4:w*4+4].hex()))
