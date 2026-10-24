"""Compile a candidate .cpp with the Crackdown 2 compiler settings and diff one function against the CD2 target.

usage: py -I check.py <packet_dir> <file.cpp> <symbol-substring>

Compiler/flags are fixed (do not try to change them): XDK 9328 cl 15.00.8153, /Ox /Gy /GF /GR- /GS- /fp:fast.
Relocated fields (call targets, global/string addresses) are masked: only their opcode must match.
Every run is appended to <packet_dir>/attempts.log.
"""
import os, re, subprocess, sys, time, struct
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE))
import coff

XDK = r'<XDK>'
BIN = XDK + r'\bin\win32'
DUMPBIN_DIR = XDK + r'\TechPreview\Mar09Compiler\bin\win32'
FLAGS = ['/Ox', '/Gy', '/GF', '/GR-', '/GS-', '/fp:fast', '/D_XBOX', '/DNDEBUG', '/W3']


def target_lines(packet):
    out = []
    for l in open(os.path.join(packet, 'cd2_disasm.txt')):
        parts = l.rstrip('\n').split(None, 2)
        if len(parts) == 3:
            out.append(parts[2])
    return out


def our_lines(obj, sym):
    env = dict(os.environ, PATH=DUMPBIN_DIR + ';' + BIN + ';' + os.environ['PATH'])
    r = subprocess.run([DUMPBIN_DIR + r'\dumpbin.exe', '/disasm', obj], env=env, capture_output=True, text=True)
    lines, inside = [], False
    for l in r.stdout.splitlines():
        if re.match(r'^\S.*\):$', l) or re.match(r'^\?\S+', l):
            inside = sym in l
            continue
        m = re.match(r'\s+[0-9A-F]{8}: [0-9A-F]{8} (.*)$', l)
        if inside and m:
            lines.append(re.sub(r'\s+', ' ', m.group(1)).strip())
    return lines


def main():
    packet, src, sym = sys.argv[1], sys.argv[2], sys.argv[3]
    obj = os.path.splitext(src)[0] + '.obj'
    env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'], INCLUDE=XDK + r'\include\xbox')
    r = subprocess.run([BIN + r'\cl.exe', '/nologo', '/c', '/Fo' + obj] + FLAGS + [src], env=env, capture_output=True, text=True)
    log = open(os.path.join(packet, 'attempts.log'), 'a')
    if r.returncode:
        print('COMPILE ERROR\n' + r.stdout + r.stderr)
        log.write('%s\t%s\tcompile_error\n' % (time.strftime('%H:%M:%S'), os.path.basename(src)))
        return
    target = bytes.fromhex(open(os.path.join(packet, 'target.hex')).read().strip())
    found = [(n, c, rel) for n, c, rel in coff.functions(obj) if sym in n]
    if not found:
        names = [n for n, c, rel in coff.functions(obj)]
        print('No function containing %r in object. Functions present: %s' % (sym, names))
        log.write('%s\t%s\tno_symbol\n' % (time.strftime('%H:%M:%S'), os.path.basename(src)))
        return
    name, code, rel = found[0]
    exact, ratio = coff.compare(code, target, rel)
    log.write('%s\t%s\t%s\t%.3f\n' % (time.strftime('%H:%M:%S'), os.path.basename(src), 'EXACT' if exact else 'diff', ratio))
    print('%s\n  ours=%d bytes  target=%d bytes  %s  (%.1f%% of instruction words match)' % (
        name, len(code), len(target), 'EXACT MATCH' if exact else 'NOT MATCHING', 100 * ratio))
    if exact:
        return
    ol = our_lines(obj, name)
    tl = target_lines(packet)
    n = max(len(code), len(target)) // 4
    print('\n  %-5s %-8s %-38s | %-8s %s' % ('off', 'ours', 'ours disasm', 'target', 'target disasm'))
    for w in range(n):
        a, b = code[w * 4:w * 4 + 4], target[w * 4:w * 4 + 4]
        same = a == b or (w * 4 in rel and a and b and a[0] >> 2 == b[0] >> 2)
        print('%s %03x  %-8s %-38s | %-8s %s' % (' ' if same else '>', w * 4, a.hex() or '--------',
              (ol[w] if w < len(ol) else '')[:38], b.hex() or '--------', tl[w] if w < len(tl) else ''))


if __name__ == '__main__':
    main()
