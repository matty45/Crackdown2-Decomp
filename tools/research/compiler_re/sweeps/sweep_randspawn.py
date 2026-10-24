"""Sweep size()/caller shapes for cGameModeArena::GetRandSpawnPointInList<T> (target 0x8284EC80, 220 bytes)."""
import itertools, os, subprocess, sys
ROOT = r'<repo>'
sys.path.insert(0, os.path.join(ROOT, 'tools'))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'research', 'scripts'))
import coff
from verify_src import FLAGS, XDK, BIN, pe_reader

exe, WORK = sys.argv[1], sys.argv[2]
read, _ = pe_reader(open(exe, 'rb').read())
target = read(0x8284EC80, 220)
HDR = os.path.join(ROOT, 'include', 'GameManagement', 'cGameModeArena.h')
SRC = os.path.join(ROOT, 'src', 'GameManagement', 'cGameModeArena.cpp')
H_OLD = '        int size() const { return ((int)m_pLast - (int)m_pFirst) >> 2; }\n'
C_OLD = ('        int n = list.size();\n'
         '        if (n != 0)\n'
         '            return (T *)list[s_RandGen.Rand(n)];\n'
         '        return 0;\n')
SIZES = {
    'bytes_int': '        int size() const { return ((int)m_pLast - (int)m_pFirst) >> 2; }\n',
    'ptrdiff_int': '        int size() const { return m_pLast - m_pFirst; }\n',
    'ptrdiff_uint': '        unsigned int size() const { return (unsigned int)(m_pLast - m_pFirst); }\n',
    'ptrdiff_if_first': '        unsigned int size() const { return m_pFirst == 0 ? 0 : (unsigned int)(m_pLast - m_pFirst); }\n',
}
CALLERS = {
    'local_n': C_OLD,
    'twice_ne0': '        if (list.size() != 0)\n            return (T *)list[s_RandGen.Rand(list.size())];\n        return 0;\n',
    'twice_bool': '        if (list.size())\n            return (T *)list[s_RandGen.Rand(list.size())];\n        return 0;\n',
    'twice_gt0': '        if (list.size() > 0)\n            return (T *)list[s_RandGen.Rand(list.size())];\n        return 0;\n',
    'eq0_first': '        if (list.size() == 0)\n            return 0;\n        return (T *)list[s_RandGen.Rand(list.size())];\n',
    'idx_local': '        if (list.size() != 0)\n        {\n            unsigned int i = s_RandGen.Rand(list.size());\n            return (T *)list[i];\n        }\n        return 0;\n',
}
env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'],
           INCLUDE=os.path.join(XDK, 'include', 'xbox') + ';' + os.path.join(ROOT, 'include'))
htext, ctext = open(HDR).read(), open(SRC).read()
assert H_OLD in htext and C_OLD in ctext, 'patterns not found'
for (sk, sv), (ck, cv) in itertools.product(SIZES.items(), CALLERS.items()):
    k = '%s+%s' % (sk, ck)
    d = os.path.join(WORK, k.replace('+', '_'))
    os.makedirs(os.path.join(d, 'GameManagement'), exist_ok=True)
    open(os.path.join(d, 'GameManagement', 'cGameModeArena.h'), 'w').write(htext.replace(H_OLD, sv))
    cpp = os.path.join(d, 'a.cpp')
    open(cpp, 'w').write(ctext.replace(C_OLD, cv))
    obj = os.path.join(d, 'a.obj')
    r = subprocess.run([os.path.join(BIN, 'cl.exe')] + FLAGS + ['/I' + d, '/Fo' + obj, cpp], env=env, capture_output=True, text=True)
    if r.returncode:
        print('%-34s compile error' % k)
        continue
    name, code, rel = [x for x in coff.functions(obj) if 'GetRandSpawnPointInList@VcNetGamePlayerSpawnPoint' in x[0]][0]
    exact, ratio = coff.compare(code, target, rel)
    print('%-34s %s %5.1f%%  %d bytes' % (k, 'EXACT' if exact else '     ', 100 * ratio, len(code)))
