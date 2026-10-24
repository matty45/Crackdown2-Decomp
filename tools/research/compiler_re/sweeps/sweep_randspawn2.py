"""Second sweep: Rand(max) and operator[] forms, with size = unsigned pointer difference and caller `size() > 0`."""
import itertools, os, subprocess, sys
ROOT = r'<repo>'
sys.path.insert(0, os.path.join(ROOT, 'tools')); sys.path.insert(0, os.path.join(ROOT, 'tools', 'research', 'scripts'))
import coff
from verify_src import FLAGS, XDK, BIN, pe_reader
exe, WORK = sys.argv[1], sys.argv[2]
read, _ = pe_reader(open(exe, 'rb').read())
target = read(0x8284EC80, 220)
HDR = os.path.join(ROOT, 'include', 'GameManagement', 'cGameModeArena.h')
RG = os.path.join(ROOT, 'include', 'fun_runtime', 'randgen.h')
SRC = os.path.join(ROOT, 'src', 'GameManagement', 'cGameModeArena.cpp')
h_size_old = '        int size() const { return ((int)m_pLast - (int)m_pFirst) >> 2; }\n'
h_size_new = '        unsigned int size() const { return (unsigned int)(m_pLast - m_pFirst); }\n'
h_idx_old = '        T &operator[](unsigned int i) const { return m_pFirst[i]; }\n'
c_old = ('        int n = list.size();\n        if (n != 0)\n            return (T *)list[s_RandGen.Rand(n)];\n        return 0;\n')
c_new = '        if (list.size() > 0)\n            return (T *)list[s_RandGen.Rand(list.size())];\n        return 0;\n'
r_old = '        unsigned int Rand(unsigned int max) { return Rand() % max; }\n'
RANDS = {
    'mod_of_rand': r_old,
    'inline_body': '        unsigned int Rand(unsigned int max)\n        {\n            m_nSeed = 0;\n            m_nNext = m_nNext * 1103515245 + 12345;\n            return ((m_nNext >> 16) & 0x7FFF) % max;\n        }\n',
    'local_r': '        unsigned int Rand(unsigned int max) { unsigned int r = Rand(); return r % max; }\n',
}
IDX = {
    'uint_idx': h_idx_old,
    'int_idx': '        T &operator[](int i) const { return m_pFirst[i]; }\n',
    'ptr_add': '        T &operator[](unsigned int i) const { return *(m_pFirst + i); }\n',
    'nonconst_ref': '        const T &operator[](unsigned int i) const { return m_pFirst[i]; }\n',
}
env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'], INCLUDE=os.path.join(XDK, 'include', 'xbox') + ';' + os.path.join(ROOT, 'include'))
ht, rt, ct = open(HDR).read(), open(RG).read(), open(SRC).read()
assert h_size_old in ht and h_idx_old in ht and r_old in rt and c_old in ct
for (rk, rv), (ik, iv) in itertools.product(RANDS.items(), IDX.items()):
    k = '%s+%s' % (rk, ik)
    d = os.path.join(WORK, k.replace('+', '_'))
    for sub in ('GameManagement', 'fun_runtime'):
        os.makedirs(os.path.join(d, sub), exist_ok=True)
    open(os.path.join(d, 'GameManagement', 'cGameModeArena.h'), 'w').write(ht.replace(h_size_old, h_size_new).replace(h_idx_old, iv))
    open(os.path.join(d, 'fun_runtime', 'randgen.h'), 'w').write(rt.replace(r_old, rv))
    cpp = os.path.join(d, 'a.cpp'); open(cpp, 'w').write(ct.replace(c_old, c_new))
    obj = os.path.join(d, 'a.obj')
    r = subprocess.run([os.path.join(BIN, 'cl.exe')] + FLAGS + ['/I' + d, '/Fo' + obj, cpp], env=env, capture_output=True, text=True)
    if r.returncode:
        print('%-28s compile error %s' % (k, (r.stdout + r.stderr).strip().splitlines()[-1][:90])); continue
    res = []
    for sym, va in (('GetRandSpawnPointInList@VcNetGamePlayerSpawnPoint', 0x8284EC80), ('GetRandSpawnPointInList@VcNetGamePickupSpawnPoint', 0x8284ED60)):
        name, code, rel = [x for x in coff.functions(obj) if sym in x[0]][0]
        exact, ratio = coff.compare(code, read(va, 220), rel)
        res.append('EXACT' if exact else '%5.1f%%' % (100 * ratio))
    print('%-28s %s' % (k, '  '.join(res)))
