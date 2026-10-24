"""compile one .cpp with the CD2 compiler and diff a function against CD2 bytes.
usage: check.py file.cpp <cd2_ea_hex> <symbol-substring> [extra cl flags...]"""
import os, subprocess, sys, json, struct
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
import coff
XDK = r'<XDK>'
BIN = os.environ.get('CLBIN', XDK + r'\bin\win32')
src, ea, sym = sys.argv[1], int(sys.argv[2], 16), sys.argv[3]
flags = sys.argv[4:] or ['/Ox']
obj = os.path.splitext(src)[0] + '.obj'
env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'], INCLUDE=XDK + r'\include\xbox')
r = subprocess.run([BIN + r'\cl.exe', '/nologo', '/c', '/Gy', '/GF', '/GR-', '/D_XBOX', '/DNDEBUG', '/Fo' + obj] + flags + [src],
                   env=env, capture_output=True, text=True)
if r.returncode:
    print(r.stdout, r.stderr); sys.exit(1)
target = bytes.fromhex(open(os.path.join(os.path.dirname(src), 'target_%08x.hex' % ea)).read().strip())
for name, code, rel in coff.functions(obj):
    if sym in name:
        exact, ratio = coff.compare(code, target, rel)
        print('%s  ours=%dB target=%dB  exact=%s  ratio=%.2f' % (name, len(code), len(target), exact, ratio))
        if not exact:
            for w in range(max(len(code), len(target)) // 4):
                a, b = code[w*4:w*4+4], target[w*4:w*4+4]
                mark = '' if a == b else (' reloc' if w*4 in rel and a and b and a[0] >> 2 == b[0] >> 2 else ' <<<')
                print('  +%03x %s %s%s' % (w*4, a.hex() or '--------', b.hex() or '--------', mark))

