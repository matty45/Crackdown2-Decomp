"""Check every matched function (repo src manifest + examples) under alternative flag sets.
usage: flagcheck_all.py <default.exe> "<flagset1>" "<flagset2>" ..."""
import json, os, struct, subprocess, sys, tempfile
ROOT = r'<repo>'
sys.path.insert(0, os.path.join(ROOT, 'tools', 'research', 'scripts'))
import coff
XDK = r'<XDK>'
BIN = XDK + r'\bin\win32'
exe = open(sys.argv[1], 'rb').read()
pe = struct.unpack('<I', exe[0x3C:0x40])[0]; nsec = struct.unpack('<H', exe[pe + 6:pe + 8])[0]
optsz = struct.unpack('<H', exe[pe + 20:pe + 22])[0]; base = struct.unpack('<I', exe[pe + 24 + 28:pe + 24 + 32])[0]
secs = [struct.unpack('<IIII', exe[pe + 24 + optsz + i * 40 + 8: pe + 24 + optsz + i * 40 + 24]) for i in range(nsec)]
def read(va, n):
    for vs, sva, rs, ra in secs:
        if base + sva <= va < base + sva + rs:
            o = ra + va - base - sva; return exe[o:o + n]
items = []
m = json.load(open(os.path.join(ROOT, 'config', 'matched_functions.json')))
for src, fs in m['files'].items():
    for f in fs:
        items.append((os.path.join(ROOT, src), int(f['address'], 16), f['size'], f['symbol']))
ex = os.path.join(ROOT, 'examples', 'matching')
for src, va, size, sym in [('AI_cTrainingMission_StartMission.cpp', 0x82480DA0, 88, 'StartMission@cTrainingMission'),
                           ('UI_HUD_RaceHUD_OnEnter.cpp', 0x821E6878, 80, 'OnEnter@RaceHUD'),
                           ('CHARACTER_cActionManager_DeactivateMainIF.cpp', 0x82302E10, 152, 'DeactivateMainIF'),
                           ('Equip_cCloakingDevice_ClassGetter.cpp', 0x822F33C8, 156, 'GetCloakingDevice'),
                           ('ClosestOfTwo.cpp', 0x82401C88, 128, '?Closest@@'), ('ClosestOfTwo_alt.cpp', 0x82401C88, 128, '?PickClosest@@'),
                           ('Classify.cpp', 0x821D0CE0, 124, 'Classify@Owner'), ('Classify_alt.cpp', 0x821D0CE0, 124, 'Check@cBase')]:
    items.append((os.path.join(ex, src), va, size, sym))
env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'], INCLUDE=XDK + r'\include\xbox;' + os.path.join(ROOT, 'include'))
tmp = tempfile.mkdtemp()
for fl in sys.argv[2:]:
    ok = 0; bad = []
    cache = {}
    for src, va, size, sym in items:
        if src not in cache:
            obj = os.path.join(tmp, os.path.basename(src) + '.obj')
            r = subprocess.run([BIN + r'\cl.exe', '/nologo', '/c', '/Gy', '/GF', '/GR-', '/GS-', '/fp:fast', '/D_XBOX', '/DNDEBUG']
                               + fl.split() + ['/Fo' + obj, src], env=env, capture_output=True, text=True)
            cache[src] = list(coff.functions(obj)) if r.returncode == 0 else None
        funcs = cache[src]
        cand = [(n, c, rel) for n, c, rel in (funcs or []) if sym in n]
        e = bool(cand) and coff.compare(cand[0][1], read(va, size), cand[0][2])[0]
        ok += e
        if not e: bad.append('%s@%08X' % (os.path.basename(src), va))
    print('%-14s %d/%d exact  %s' % (fl, ok, len(items), ('failing: ' + ', '.join(bad)) if bad else ''))
