"""Compile a candidate .cpp with the Crackdown 2 compiler settings and diff one function against the CD2 target.

usage: py -I check.py <packet_dir> <file.cpp> <symbol-substring> [--full]

Compact output: a one-line summary, then only the differing regions (2 lines of context, at most 60 lines).
--full prints the complete side-by-side listing (expensive for large functions; avoid).
Compiler/flags are fixed: XDK 9328 cl 15.00.8153, /Ox /Gy /GF /GR- /GS- /fp:fast.
Relocated fields (call targets, global/string addresses) are masked: only their opcode must match.
Every run is appended to <packet_dir>/attempts.log.
"""
import os, re, subprocess, sys, time
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE))
import coff

XDK = r'<XDK>'
BIN = XDK + r'\bin\win32'
DUMPBIN_DIR = XDK + r'\TechPreview\Mar09Compiler\bin\win32'
FLAGS = ['/Ox', '/Gy', '/GF', '/GR-', '/GS-', '/fp:fast', '/D_XBOX', '/DNDEBUG', '/W3']
CONTEXT, MAX_LINES = 2, 60


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
    args = [a for a in sys.argv[1:] if a != '--full']
    full = '--full' in sys.argv
    packet, src, sym = args[0], args[1], args[2]
    obj = os.path.splitext(src)[0] + '.obj'
    env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'], INCLUDE=XDK + r'\include\xbox')
    r = subprocess.run([BIN + r'\cl.exe', '/nologo', '/c', '/Fo' + obj] + FLAGS + [src], env=env, capture_output=True, text=True)
    log = open(os.path.join(packet, 'attempts.log'), 'a')
    if r.returncode:
        errs = [l for l in (r.stdout + r.stderr).splitlines() if 'error' in l.lower()][:15]
        print('COMPILE ERROR\n' + '\n'.join(errs))
        log.write('%s\t%s\tcompile_error\n' % (time.strftime('%H:%M:%S'), os.path.basename(src)))
        return
    target = bytes.fromhex(open(os.path.join(packet, 'target.hex')).read().strip())
    found = [(n, c, rel) for n, c, rel in coff.functions(obj) if sym in n]
    if not found:
        print('No function containing %r. Functions present: %s' % (sym, [n for n, c, rel in coff.functions(obj)]))
        log.write('%s\t%s\tno_symbol\n' % (time.strftime('%H:%M:%S'), os.path.basename(src)))
        return
    name, code, rel = found[0]
    exact, ratio = coff.compare(code, target, rel)
    log.write('%s\t%s\t%s\t%.3f\n' % (time.strftime('%H:%M:%S'), os.path.basename(src), 'EXACT' if exact else 'diff', ratio))
    n = max(len(code), len(target)) // 4
    diff = [w for w in range(n) if not (code[w*4:w*4+4] == target[w*4:w*4+4] or
            (w * 4 in rel and code[w*4:w*4+4] and target[w*4:w*4+4] and code[w*4] >> 2 == target[w*4] >> 2))]
    print('%s: ours=%d bytes target=%d bytes  %s  (%.1f%% words match, %d differ, first diff at +0x%x)' % (
        name, len(code), len(target), 'EXACT MATCH' if exact else 'NOT MATCHING', 100 * ratio, len(diff),
        diff[0] * 4 if diff else 0))
    if exact:
        return
    ol, tl = our_lines(obj, name), target_lines(packet)
    show = set(range(n)) if full else {x for w in diff for x in range(w - CONTEXT, w + CONTEXT + 1) if 0 <= x < n}
    printed, last = 0, -2
    for w in sorted(show):
        if not full and printed >= MAX_LINES:
            print('... (%d more differing words not shown; fix the first region, then re-run)' % sum(1 for d in diff if d > w))
            break
        if w != last + 1:
            print('  ----')
        a, b = code[w*4:w*4+4], target[w*4:w*4+4]
        print('%s %03x  %-36s | %s' % ('>' if w in diff else ' ', w * 4,
              (ol[w] if w < len(ol) else '--')[:36], tl[w] if w < len(tl) else '--'))
        printed += 1
        last = w


if __name__ == '__main__':
    main()
