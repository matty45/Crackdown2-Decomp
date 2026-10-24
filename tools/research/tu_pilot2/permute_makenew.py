"""Mini permuter for cFactionConfigData's constructor chain: try source variants, score MakeNew (F07) under /Ob1."""
import itertools, os, subprocess, sys, glob
S = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(S))
import coff
XDK = r'<XDK>'
BIN = XDK + r'\bin\win32'
V = os.path.join(os.environ['TEMP'], 'cfcd')
base_h = open(os.path.join(V, 'v2.h')).read()
cpp = open(os.path.join(V, 'v2.cpp')).read().replace('#include "v2.h"', '#include "perm.h"')
open(os.path.join(V, 'perm.cpp'), 'w').write(cpp)
tgt = {k: bytes.fromhex(open(glob.glob(os.path.join(S, 'cFactionConfigData', 'targets', k + '_*', 'target.hex'))[0]).read().strip())
       for k in ('F07', 'F13', 'F15')}
LIST = {
    'init-npc': 'cConfigList() : m_pNext(this), m_pPrev(this), m_nCount(0) {}',
    'init-c+body-np': 'cConfigList() : m_nCount(0) { m_pNext = this; m_pPrev = this; }',
    'body-cnp': 'cConfigList() { m_nCount = 0; m_pNext = this; m_pPrev = this; }',
    'body-chain': 'cConfigList() { m_pNext = m_pPrev = this; m_nCount = 0; }',
}
ORIG_LIST = 'cConfigList() : m_nCount(0) { m_pNext = this; m_pPrev = this; }'
B2 = {
    'flag-in-base': None,
    'flag-in-b2': True,
}
CTOR = {
    'init': '__forceinline cFactionConfigData(const RWS::CAttributePacket &) : m_pTargetingProfile(0) {}',
    'body': '__forceinline cFactionConfigData(const RWS::CAttributePacket &) { m_pTargetingProfile = 0; }',
}
ORIG_CTOR = 'cFactionConfigData(const RWS::CAttributePacket &) : m_pTargetingProfile(0) {}'
results = []
env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'],
           INCLUDE=';'.join([XDK + r'\include\xbox', r'<repo>\include', V]))
for (lk, lsrc), (bk, b2), (ck, csrc), force in itertools.product(LIST.items(), B2.items(), CTOR.items(), (True, False)):
    h = base_h.replace(ORIG_LIST, lsrc)
    c = csrc if force else csrc.replace('__forceinline ', '')
    h = h.replace(ORIG_CTOR, c)
    if b2:
        h = h.replace('class cConfigB2 { public: virtual void Notify() {} protected: bool m_bFlag; };',
                      'class cConfigB2 { public: cConfigB2() : m_bFlag(false) {} virtual void Notify() {} protected: bool m_bFlag; };')
        h = h.replace('cConfigBase() { m_bFlag = false; }', 'cConfigBase() {}')
    open(os.path.join(V, 'perm.h'), 'w').write(h)
    obj = os.path.join(V, 'perm.obj')
    r = subprocess.run([BIN + r'\cl.exe', '/nologo', '/c', '/Ox', '/Ob1', '/Gy', '/GF', '/GR-', '/GS-', '/fp:fast', '/D_XBOX',
                        '/DNDEBUG', '/Fo' + obj, os.path.join(V, 'perm.cpp')], env=env, capture_output=True, text=True)
    if r.returncode:
        results.append((0, lk, bk, ck, force, 'compile error')); continue
    funcs = list(coff.functions(obj))
    def score(k, sym):
        cand = [(n, cc, rel) for n, cc, rel in funcs if sym in n and 'cFactionConfigData' in n]
        return max((coff.compare(cc, tgt[k], rel) for n, cc, rel in cand), default=(False, 0.0))
    f7, f13, f15 = score('F07', '?MakeNew@'), score('F13', '??_G'), score('F15', '?HandleAttributes@')
    results.append((f7[1], lk, bk, ck, force, 'F07=%s F13=%s F15=%s' % ('EXACT' if f7[0] else '%.0f%%' % (100 * f7[1]),
                    'EXACT' if f13[0] else 'no', 'EXACT' if f15[0] else 'no')))
results.sort(key=lambda r: -r[0])
for r in results[:12]:
    print('%-16s %-13s ctor=%-5s force=%-5s %s' % r[1:])
