"""Print the dumpbin disassembly of functions in a PPC COFF object whose name contains any given substring.
usage: py -I dis.py file.obj substring [substring...]"""
import os, re, subprocess, sys
XDK = r'<XDK>'
T = XDK + r'\TechPreview\Mar09Compiler\bin\win32'
env = dict(os.environ, PATH=T + ';' + XDK + r'\bin\win32;' + os.environ['PATH'])
out = subprocess.run([T + r'\dumpbin.exe', '/disasm', sys.argv[1]], env=env, capture_output=True, text=True).stdout
on = False
for l in out.splitlines():
    if re.match(r'^\S.*\):\s*$', l):
        on = any(s in l for s in sys.argv[2:])
        if on:
            print('== ' + l[:90])
        continue
    m = re.match(r'\s+([0-9A-F]{8}): [0-9A-F]{8} (.*)$', l)
    if on and m:
        print('  %s %s' % (m.group(1)[-3:], re.sub(r'\s+', ' ', m.group(2))))
