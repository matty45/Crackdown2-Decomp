import json, os, subprocess, sys, glob, itertools
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import coff

S = os.path.dirname(os.path.abspath(__file__))
XDK = r'<XDK>'
COMPILERS = {'8153': XDK + r'\bin\win32', '8327': XDK + r'\TechPreview\Mar09Compiler\bin\win32'}
LUA = S + r'\dl\lua-5.0.2'
SRCS = glob.glob(LUA + r'\src\*.c') + glob.glob(LUA + r'\src\lib\*.c')
target = json.load(open(S + r'\cd2_lua_bytes.json'))
target = {k: bytes.fromhex(v['bytes']) for k, v in target.items()}

OPTS = sys.argv[1:] or ['/Ox', '/O2', '/O1', '/Ox /Os', '/O2 /Ob2', '/Ox /Oi /Ot /Ob2']

def build(comp, opt, outdir):
    os.makedirs(outdir, exist_ok=True)
    env = dict(os.environ)
    env['PATH'] = COMPILERS[comp] + ';' + XDK + r'\bin\win32;' + env['PATH']
    env['INCLUDE'] = XDK + r'\include\xbox'
    args = [COMPILERS[comp] + r'\cl.exe', '/nologo', '/c', '/W0', '/D_XBOX', '/DNDEBUG', '/Gy', '/GF',
            '/I' + LUA + r'\include', '/I' + LUA + r'\src', '/Fo' + outdir + '\\'] + opt.split() + SRCS
    r = subprocess.run(args, env=env, capture_output=True, text=True)
    if r.returncode:
        print(r.stdout[-2000:], r.stderr[-2000:])

def score(outdir):
    res = {}
    for obj in glob.glob(outdir + r'\*.obj'):
        for name, code, rel in coff.functions(obj):
            key = name.lstrip('.').lstrip('_')
            if key in target:
                res[key] = coff.compare(code, target[key], rel)
    return res

summary = []
for comp, opt in itertools.product(COMPILERS, OPTS):
    out = S + r'\build\%s_%s' % (comp, opt.replace('/', '').replace(' ', ''))
    build(comp, opt, out)
    res = score(out)
    exact = sum(1 for e, r in res.values() if e)
    avg = sum(r for e, r in res.values()) / max(1, len(res))
    summary.append((comp, opt, len(res), exact, avg))
    print('%s %-22s found=%2d exact=%2d avg=%.3f' % (comp, opt, len(res), exact, avg), flush=True)
json.dump(summary, open(S + r'\fingerprint_summary.json', 'w'))
