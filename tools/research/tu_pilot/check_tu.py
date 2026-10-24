"""TU-level harness: compile one source file and compare every target function of the TU.

usage: py -I check_tu.py <tu_dir> <file.cpp> [--diff Fn] [--include DIR ...]

- Targets are <tu_dir>/targets/<Fn>_<ADDR>/ (target.hex, cd2_disasm.txt).
- Each target is paired with the compiled function that matches it best (each compiled function used at most once).
- Prints a status table; with --diff Fn also prints the compact diff for that target (differing regions only).
- Compiler/flags fixed: XDK 9328 cl 15.00.8153, /Ox /Gy /GF /GR- /GS- /fp:fast. The repo's include/ and the XDK
  headers are on the include path. Relocated fields are masked.
- Every run is appended to <tu_dir>/attempts.log.
"""
import os, re, subprocess, sys, time, glob
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE))
import coff

XDK = r'<XDK>'
BIN = XDK + r'\bin\win32'
DUMPBIN_DIR = XDK + r'\TechPreview\Mar09Compiler\bin\win32'
REPO_INCLUDE = r'<repo>\include'
FLAGS = ['/Ox', '/Gy', '/GF', '/GR-', '/GS-', '/fp:fast', '/D_XBOX', '/DNDEBUG', '/W3']


def lines_of(path):
    out = []
    for l in open(path):
        parts = l.rstrip('\n').split(None, 2)
        if len(parts) == 3:
            out.append(parts[2])
    return out


def our_lines(obj, sym):
    env = dict(os.environ, PATH=DUMPBIN_DIR + ';' + BIN + ';' + os.environ['PATH'])
    r = subprocess.run([DUMPBIN_DIR + r'\dumpbin.exe', '/disasm', obj], env=env, capture_output=True, text=True)
    out, inside = [], False
    for l in r.stdout.splitlines():
        if re.match(r'^\S.*\):$', l) or re.match(r'^\?\S+', l):
            inside = sym in l
            continue
        m = re.match(r'\s+[0-9A-F]{8}: [0-9A-F]{8} (.*)$', l)
        if inside and m:
            out.append(re.sub(r'\s+', ' ', m.group(1)).strip())
    return out


def diff_words(code, target, rel):
    n = max(len(code), len(target)) // 4
    return n, [w for w in range(n) if not (code[w*4:w*4+4] == target[w*4:w*4+4] or
               (w * 4 in rel and code[w*4:w*4+4] and target[w*4:w*4+4] and code[w*4] >> 2 == target[w*4] >> 2))]


def main():
    args = sys.argv[1:]
    want_diff = None
    incs = [REPO_INCLUDE]
    if '--diff' in args:
        i = args.index('--diff'); want_diff = args[i + 1]; del args[i:i + 2]
    while '--include' in args:
        i = args.index('--include'); incs.append(args[i + 1]); del args[i:i + 2]
    tu, src = args[0], args[1]
    obj = os.path.splitext(src)[0] + '.obj'
    env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'], INCLUDE=';'.join([XDK + r'\include\xbox'] + incs))
    r = subprocess.run([BIN + r'\cl.exe', '/nologo', '/c', '/Fo' + obj] + FLAGS + [src], env=env, capture_output=True, text=True)
    log = open(os.path.join(tu, 'attempts.log'), 'a')
    if r.returncode:
        errs = [l for l in (r.stdout + r.stderr).splitlines() if 'error' in l.lower()][:15]
        print('COMPILE ERROR\n' + '\n'.join(errs))
        log.write('%s\t%s\tcompile_error\n' % (time.strftime('%H:%M:%S'), os.path.basename(src)))
        return
    funcs = list(coff.functions(obj))
    targets = []
    for d in sorted(glob.glob(os.path.join(tu, 'targets', 'F*_*'))):
        k, addr = os.path.basename(d).split('_')
        targets.append((k, addr, bytes.fromhex(open(os.path.join(d, 'target.hex')).read().strip()), d))
    # score all pairs, assign greedily by best ratio
    scores = []
    for ti, (k, addr, tgt, d) in enumerate(targets):
        for fi, (name, code, rel) in enumerate(funcs):
            exact, ratio = coff.compare(code, tgt, rel)
            scores.append((exact, ratio, ti, fi))
    scores.sort(reverse=True)
    pair, used_t, used_f = {}, set(), set()
    for exact, ratio, ti, fi in scores:
        if ti in used_t or fi in used_f or ratio < 0.2:
            continue
        pair[ti] = (fi, exact, ratio); used_t.add(ti); used_f.add(fi)
    total = sum(len(t[2]) for t in targets)
    matched = sum(len(targets[ti][2]) for ti, (fi, ex, ra) in pair.items() if ex)
    print('TU %s: %d/%d target functions exact, %d/%d bytes exact' % (
        os.path.basename(tu), sum(1 for v in pair.values() if v[1]), len(targets), matched, total))
    rec = []
    for ti, (k, addr, tgt, d) in enumerate(targets):
        if ti in pair:
            fi, ex, ra = pair[ti]
            status = 'EXACT' if ex else '%5.1f%%' % (100 * ra)
            print('  %s %s %4dB  %-7s <- %s' % (k, addr, len(tgt), status, funcs[fi][0][:80]))
            rec.append('%s=%s' % (k, 'X' if ex else '%.2f' % ra))
        else:
            print('  %s %s %4dB  (no compiled function resembles it)' % (k, addr, len(tgt)))
            rec.append('%s=-' % k)
    log.write('%s\t%s\t%s\n' % (time.strftime('%H:%M:%S'), os.path.basename(src), ' '.join(rec)))
    if want_diff:
        for ti, (k, addr, tgt, d) in enumerate(targets):
            if k != want_diff:
                continue
            if ti not in pair:
                print('\n%s: nothing to diff (no paired function)' % k); return
            fi, ex, ra = pair[ti]
            name, code, rel = funcs[fi]
            if ex:
                print('\n%s is an exact match' % k); return
            n, diff = diff_words(code, tgt, rel)
            ol, tl = our_lines(obj, name), lines_of(os.path.join(d, 'cd2_disasm.txt'))
            show = sorted({x for w in diff for x in range(w - 2, w + 3) if 0 <= x < n})
            print('\n%s diff (%d differing words, first at +0x%x):' % (k, len(diff), diff[0] * 4 if diff else 0))
            last, printed = -2, 0
            for w in show:
                if printed >= 60:
                    print('  ... more differences not shown; fix the first region and re-run'); break
                if w != last + 1:
                    print('  ----')
                print('%s %03x  %-36s | %s' % ('>' if w in diff else ' ', w * 4, (ol[w] if w < len(ol) else '--')[:36], tl[w] if w < len(tl) else '--'))
                last, printed = w, printed + 1


if __name__ == '__main__':
    main()
