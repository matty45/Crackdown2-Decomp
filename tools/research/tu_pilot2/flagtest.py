"""Compile a cFactionConfigData variant with extra flags and compare the 7 functions by symbol.
usage: flagtest.py <src.cpp> [extra cl flags...]"""
import os, subprocess, sys, glob
S = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(S))
import coff
XDK = r'<XDK>'
BIN = XDK + r'\bin\win32'
TU = os.path.join(S, 'cFactionConfigData')
src, extra = sys.argv[1], sys.argv[2:]
obj = os.path.splitext(src)[0] + '_ft.obj'
env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'],
           INCLUDE=';'.join([XDK + r'\include\xbox', r'<repo>\include', os.path.dirname(src)]))
r = subprocess.run([BIN + r'\cl.exe', '/nologo', '/c', '/Ox', '/Gy', '/GF', '/GR-', '/GS-', '/fp:fast', '/D_XBOX', '/DNDEBUG'] + extra +
                   ['/Fo' + obj, src], env=env, capture_output=True, text=True)
if r.returncode:
    sys.exit(r.stdout + r.stderr)
funcs = list(coff.functions(obj))
expect = {'F07': '?MakeNew@', 'F08': '?RetClassName@', 'F13': '??_G', 'F14': '??1cFactionConfigData', 'F15': '?HandleAttributes@',
          'F18': '??__E', 'F19': '??__F'}
res = []
for k, sym in expect.items():
    tgt = bytes.fromhex(open(glob.glob(os.path.join(TU, 'targets', k + '_*', 'target.hex'))[0]).read().strip())
    cand = [(n, c, rel) for n, c, rel in funcs if sym in n and ('cFactionConfigData' in n or k in ('F18', 'F19'))]
    if not cand:
        res.append('%s=missing' % k); continue
    ex, ra = max(coff.compare(c, tgt, rel) for n, c, rel in cand)
    res.append('%s=%s' % (k, 'EXACT' if ex else '%.0f%%' % (100 * ra)))
print(' '.join(extra) or '(base flags)', '|', ' '.join(res))
