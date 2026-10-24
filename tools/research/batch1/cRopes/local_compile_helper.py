"""Local helper (NOT a harness run): compile the cpp, print status of all mapped targets, and the harness-style masked
diff for the requested ones.  usage: py -I d.py [F10 F11 ...]"""
import os, sys, subprocess, glob
W = os.path.dirname(os.path.abspath(__file__))
TU = os.path.dirname(W)
BATCH = os.path.dirname(TU)
sys.path.insert(0, BATCH)
import check_tu as c
coff = c.coff

src = os.path.join(W, 'cRopes.cpp')
obj = os.path.join(W, 'cRopes_local.obj')
env = dict(os.environ, PATH=c.BIN + ';' + os.environ['PATH'], INCLUDE=';'.join([c.XDK + r'\include\xbox', c.REPO_INCLUDE]))
r = subprocess.run([c.BIN + r'\cl.exe', '/nologo', '/c', '/Fo' + obj] + c.FLAGS + [src], env=env, capture_output=True, text=True)
if r.returncode:
    print('\n'.join([l for l in (r.stdout + r.stderr).splitlines() if 'error' in l.lower()][:20])); sys.exit(1)
mapping = {}
for l in open(os.path.join(W, 'map.txt')):
    p = l.split()
    if len(p) >= 2: mapping[p[0]] = p[1]
funcs = list(coff.functions(obj))
want = sys.argv[1:]
for k in sorted(mapping):
    d = glob.glob(os.path.join(TU, 'targets', k + '_*'))[0]
    tgt = bytes.fromhex(open(os.path.join(d, 'target.hex')).read().strip())
    hits = [f for f in funcs if mapping[k] in f[0]]
    if not hits:
        print(k, 'NOT EMITTED', mapping[k]); continue
    name, code, rel = hits[0]
    ex, ra = coff.compare(code, tgt, rel)
    print(k, 'EXACT' if ex else '%.1f%% (%d vs %d bytes)' % (100 * ra, len(code), len(tgt)), name[:50])
    if k in want and not ex:
        n, diff = c.diff_words(code, tgt, rel)
        ol, tl = c.our_lines(obj, name), c.lines_of(os.path.join(d, 'cd2_disasm.txt'))
        show = sorted({x for w in diff for x in range(w - 2, w + 3) if 0 <= x < n})
        print('  diff (%d differing words, first at +0x%x):' % (len(diff), diff[0] * 4 if diff else 0))
        last, printed = -2, 0
        for w in show:
            if printed >= 90:
                print('  ... more'); break
            if w != last + 1: print('  ----')
            print('%s %03x  %-36s | %s' % ('>' if w in diff else ' ', w * 4, (ol[w] if w < len(ol) else '--')[:36], tl[w] if w < len(tl) else '--'))
            last, printed = w, printed + 1
