"""Source-shape sweep: compile named variants of repo files and compare chosen functions with Crackdown 2.

usage: py -I tools/sweep.py <path to extracted default.exe> <spec.py> [workdir]

The spec is a Python file defining:
    SOURCE   = 'src/VFX/cAmbientVFXSpawner.cpp'            # the file to compile (repo-relative)
    TARGETS  = [('?IsVFXFinished@cAmbientVFXSpawner@', 0x827F9748, 164), ...]   # symbol substring, address, size
    VARIANTS = {'name': [('include/VFX/cAmbientVFXSpawner.h', 'old text', 'new text'), ...], ...}

Each variant applies its replacements to copies of the named files (headers go into an override include directory that
is searched first, the source is copied), compiles with the game flags (plain, not LTCG), and prints, per target,
EXACT or the share of matching words (relocated fields masked). A variant named 'baseline' with no replacements is
always run first. Replacements must match exactly once, otherwise the variant is reported as a spec error.

Typical use: find which source shape gives an instruction CD2 has, e.g. the operand order of a commutative op,
an extract instead of a mask, or where a value is recomputed. Examples are in tools/research/compiler_re/sweeps/.
"""
import os, runpy, shutil, subprocess, sys, tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import coff
from verify_src import pe_reader, FLAGS, XDK, BIN, ROOT, EXPECTED_ENTRY, check_toolchain


def main():
    check_toolchain()
    if len(sys.argv) < 3:
        print(__doc__)
        sys.exit(2)
    read, entry = pe_reader(open(sys.argv[1], 'rb').read())
    if entry != EXPECTED_ENTRY:
        sys.exit('This executable has entry %08X, not the title-update build (%08X). Use the patched XEX only.' % (entry, EXPECTED_ENTRY))
    spec = runpy.run_path(sys.argv[2])
    source, targets = spec['SOURCE'], spec['TARGETS']
    variants = [('baseline', [])] + [(k, v) for k, v in spec['VARIANTS'].items() if k != 'baseline']
    work = sys.argv[3] if len(sys.argv) > 3 else tempfile.mkdtemp(prefix='cd2sweep_')
    env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'],
               INCLUDE=os.path.join(XDK, 'include', 'xbox') + ';' + os.path.join(ROOT, 'include'))
    srcpath = os.path.join(ROOT, source)
    width = max(len(k) for k, _ in variants)
    print('%-*s  %s' % (width, 'variant', '  '.join(t[0][:28] for t in targets)))
    for name, reps in variants:
        d = os.path.join(work, name)
        shutil.rmtree(d, ignore_errors=True)
        os.makedirs(d)
        texts, err = {}, None
        for path, old, new in reps:
            t = texts.get(path)
            if t is None:
                t = open(os.path.join(ROOT, path)).read()
            n = t.count(old)
            if n != 1:
                err = '%s: replacement text found %d times' % (path, n)
                break
            texts[path] = t.replace(old, new)
        if err:
            print('%-*s  spec error: %s' % (width, name, err))
            continue
        cpp = srcpath
        for path, t in texts.items():
            norm = path.replace('\\', '/')
            if norm == source.replace('\\', '/'):
                cpp = os.path.join(d, os.path.basename(path))
                open(cpp, 'w').write(t)
            elif norm.startswith('include/'):
                out = os.path.join(d, 'include', *norm[len('include/'):].split('/'))
                os.makedirs(os.path.dirname(out), exist_ok=True)
                open(out, 'w').write(t)
            else:
                print('%-*s  spec error: only the source and files under include/ can be varied' % (width, name))
                break
        obj = os.path.join(d, 'v.obj')
        r = subprocess.run([os.path.join(BIN, 'cl.exe')] + FLAGS + ['/I' + os.path.join(d, 'include'),
                           '/I' + os.path.dirname(srcpath), '/Fo' + obj, cpp], env=env, capture_output=True, text=True)
        if r.returncode:
            lines = [l for l in (r.stdout + r.stderr).splitlines() if 'error' in l]
            print('%-*s  compile error: %s' % (width, name, (lines[0] if lines else '?').strip()[:110]))
            continue
        funcs = list(coff.functions(obj))
        cells = []
        for sym, va, size in targets:
            found = [(n, c, rel) for n, c, rel in funcs if sym in n]
            if not found:
                cells.append('%-28s' % 'not found')
                continue
            exact, ratio = coff.compare(found[0][1], read(va, size), found[0][2])
            cells.append('%-28s' % ('EXACT' if exact else '%.1f%%' % (100 * ratio)))
        print('%-*s  %s' % (width, name, '  '.join(cells)))


if __name__ == '__main__':
    main()
