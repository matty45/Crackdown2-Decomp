import os, subprocess, sys
ROOT = r'<repo>'
sys.path.insert(0, os.path.join(ROOT, 'tools')); sys.path.insert(0, os.path.join(ROOT, 'tools', 'research', 'scripts'))
import coff
from verify_src import FLAGS, XDK, BIN, pe_reader
exe, WORK = sys.argv[1], sys.argv[2]
read, _ = pe_reader(open(exe, 'rb').read())
SRC = os.path.join(ROOT, 'src', 'GameManagement', 'cGameModeArena.cpp')
OLD = '        if (list.size() > 0)\n            return (T *)list[s_RandGen.Rand(list.size())];\n        return 0;\n'
V = {
    'current': OLD,
    'idx_uint': '        if (list.size() > 0)\n        {\n            unsigned int i = s_RandGen.Rand(list.size());\n            return (T *)list[i];\n        }\n        return 0;\n',
    'idx_int': '        if (list.size() > 0)\n        {\n            int i = s_RandGen.Rand(list.size());\n            return (T *)list[i];\n        }\n        return 0;\n',
    'mod_callsite': '        if (list.size() > 0)\n            return (T *)list[s_RandGen.Rand() % list.size()];\n        return 0;\n',
    'result_local': '        T *pResult = 0;\n        if (list.size() > 0)\n            pResult = (T *)list[s_RandGen.Rand(list.size())];\n        return pResult;\n',
    'ternary': '        return list.size() > 0 ? (T *)list[s_RandGen.Rand(list.size())] : 0;\n',
    'p_local': '        if (list.size() > 0)\n        {\n            T *p = (T *)list[s_RandGen.Rand(list.size())];\n            return p;\n        }\n        return 0;\n',
    'cast_static': '        if (list.size() > 0)\n            return static_cast<T *>(list[s_RandGen.Rand(list.size())]);\n        return 0;\n',
}
env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'], INCLUDE=os.path.join(XDK, 'include', 'xbox') + ';' + os.path.join(ROOT, 'include'))
ct = open(SRC).read(); assert OLD in ct
os.makedirs(WORK, exist_ok=True)
for k, v in V.items():
    cpp = os.path.join(WORK, k + '.cpp'); open(cpp, 'w').write(ct.replace(OLD, v)); obj = cpp[:-4] + '.obj'
    r = subprocess.run([os.path.join(BIN, 'cl.exe')] + FLAGS + ['/I' + os.path.dirname(SRC), '/Fo' + obj, cpp], env=env, capture_output=True, text=True)
    if r.returncode:
        print('%-14s compile error %s' % (k, (r.stdout + r.stderr).strip().splitlines()[-1][:100])); continue
    res = []
    for sym, va in (('GetRandSpawnPointInList@VcNetGamePlayerSpawnPoint', 0x8284EC80), ('GetRandSpawnPointInList@VcNetGamePickupSpawnPoint', 0x8284ED60)):
        name, code, rel = [x for x in coff.functions(obj) if sym in x[0]][0]
        exact, ratio = coff.compare(code, read(va, 220), rel)
        res.append('EXACT' if exact else '%5.1f%%' % (100 * ratio))
    print('%-14s %s' % (k, '  '.join(res)))
