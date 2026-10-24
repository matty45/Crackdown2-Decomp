"""Verify the agent's cFactionConfigData.cpp by explicit symbol -> target mapping (no similarity pairing)."""
import os, subprocess, sys, glob
S = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(S))
import coff
XDK = r'<XDK>'
BIN = XDK + r'\bin\win32'
TU = os.path.join(S, 'cFactionConfigData')
src = sys.argv[1] if len(sys.argv) > 1 else os.path.join(TU, 'work', 'cFactionConfigData.cpp')
obj = os.path.join(TU, 'work', '_verify.obj')
env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'],
           INCLUDE=';'.join([XDK + r'\include\xbox', r'<repo>\include', os.path.join(TU, 'work')]))
r = subprocess.run([BIN + r'\cl.exe', '/nologo', '/c', '/Ox', '/Gy', '/GF', '/GR-', '/GS-', '/fp:fast', '/D_XBOX', '/DNDEBUG',
                    '/Fo' + obj, src], env=env, capture_output=True, text=True)
if r.returncode:
    sys.exit(r.stdout + r.stderr)
funcs = list(coff.functions(obj))

expect = {'F07': '?MakeNew@', 'F08': '?RetClassName@', 'F13': '??_G', 'F14': '??1cFactionConfigData', 'F15': '?HandleAttributes@',
          'F18': '??__E', 'F19': '??__F'}
print('\nby symbol:')
for k, sym in expect.items():
    d = glob.glob(os.path.join(TU, 'targets', k + '_*'))[0]
    tgt = bytes.fromhex(open(os.path.join(d, 'target.hex')).read().strip())
    cand = [(n, c, rel) for n, c, rel in funcs if sym in n and ('cFactionConfigData' in n or k in ('F18', 'F19'))]
    if not cand:
        print('  %s %s %4dB  no compiled symbol containing %r' % (k, os.path.basename(d)[4:], len(tgt), sym)); continue
    best = max((coff.compare(c, tgt, rel) + (n,) for n, c, rel in cand), key=lambda t: (t[0], t[1]))
    print('  %s %s %4dB  %-8s %s' % (k, os.path.basename(d)[4:], len(tgt), 'EXACT' if best[0] else '%.1f%%' % (100 * best[1]), best[2][:70]))

