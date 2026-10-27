"""Verify every source file in src/ against the original game code.

usage: py -I tools/verify_src.py <path to extracted default.exe>

Reads config/matched_functions.json, compiles each listed source file with the Crackdown 2 compiler and flags, and
compares each listed function with the original, read at run time from your own extracted executable (nothing from the
game is stored in this repository). The executable must come from the title-update XEX, default_patched.xex (SHA1
EC7B163617CD725F50B0CCA665AAF943F9BC6D8A); never the unpatched base default.xex. Extract it with
`build/tools/bin/jeff.exe xex extract default_patched.xex` (jeff is built from source by tools/build_tools.ps1). The XDK
location defaults to the extracted XDK 9328; override with XDK_DIR.

Linker-filled fields (call targets, addresses of globals and strings) are masked in the byte comparison, and then
checked separately (tools/relocs.py): every relocation of an exact function must resolve to the CD2 address its
symbol stands for, consistently across the whole repository (one name, one address; one address, one name unless
declared in config/symbol_aliases.txt; constants and strings by content). A function that calls the wrong function
or reads the wrong global fails here even though its bytes match.
"""
import concurrent.futures, json, os, struct, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
import coff  # noqa: E402
import relocs  # noqa: E402



def local_config():
    """Machine-specific settings in local.json at the repository root (ignored by git): xdk, ruffking_pdb, burn_pdb.
    `tools/cd2.py config --xdk <dir>` writes it; environment variables override it."""
    try:
        return json.load(open(os.path.join(ROOT, 'local.json')))
    except (OSError, ValueError):
        return {}


# the extracted XDK 9328 (its bin\win32 holds the pinned compiler): XDK_DIR, else local.json's "xdk"
XDK = os.environ.get('XDK_DIR') or local_config().get('xdk') or ''
BIN = os.path.join(XDK, 'bin', 'win32')
FLAGS = ['/nologo', '/c', '/Ox', '/Ob1', '/Gy', '/GF', '/GR-', '/GS-', '/fp:fast', '/D_XBOX', '/DNDEBUG', '/W3']
EXPECTED_ENTRY = 0x823BF8C8  # title-update build
# sections a matched function may be in: ordinary code, and the compiler's own sections for a file's dynamic
# initializers (.text$yc) and at-exit destructors (.text$yd). Code anywhere else did not come from ordinary source.
CODE_SECTIONS = ('.text', '.text$yc', '.text$yd')


# a compiler failure that is about the file system, not the source: another process (a virus scanner, the indexer)
# briefly holding a file the compiler must open or write
TRANSIENT = ('C1083', 'C1085', 'Permission denied', 'being used by another process', 'Access is denied')


def run_compiler(cmd, **kw):
    """subprocess.run of the compiler (capture_output, text), retried once after a transient file-system failure."""
    import time
    r = subprocess.run(cmd, capture_output=True, text=True, **kw)
    if r.returncode and any(t in r.stdout + r.stderr for t in TRANSIENT):
        time.sleep(1)
        r = subprocess.run(cmd, capture_output=True, text=True, **kw)
    return r


def verification_jobs(value=None):
    """Bound compiler concurrency; one worker also provides a serial diagnostic mode."""
    if value is None:
        value = os.environ.get('CD2_VERIFY_JOBS', min(8, os.cpu_count() or 1))
    jobs = int(value)
    if jobs < 1:
        raise ValueError('verification worker count must be positive')
    return jobs


def parallel_map(function, items, jobs=None):
    """Run independent files concurrently, yielding results and exceptions in input order.

    Callers must give each file its own output paths. Cross-file checks and reporting remain on the calling thread.
    Nothing is cached across runs: changed sources and headers are always compiled again.
    """
    jobs = verification_jobs(jobs)
    if jobs == 1:
        yield from map(function, items)
    else:
        with concurrent.futures.ThreadPoolExecutor(max_workers=jobs) as pool:
            yield from pool.map(function, items)


def toolchain_problems():
    """Files under BIN whose SHA1 differs from config/toolchain.txt (empty when the toolchain is the pinned one)."""
    import hashlib
    if not XDK:
        return ['the XDK location is not set: run `py -I tools/cd2.py config --xdk <XDK dir>` '
                '(or set XDK_DIR to the extracted XDK 9328, the directory that holds bin\\win32)']
    problems = []
    for line in open(os.path.join(ROOT, 'config', 'toolchain.txt')):
        body = line.split('#', 1)[0].split()
        if len(body) != 2:
            continue
        want, name = body[0].upper(), body[1]
        path = os.path.join(BIN, name)
        if not os.path.exists(path):
            problems.append('%s is missing' % path)
        elif hashlib.sha1(open(path, 'rb').read()).hexdigest().upper() != want:
            problems.append('%s is not the pinned build (SHA1 %s expected)' % (path, want))
    return problems


def check_toolchain():
    """Exit unless the XDK compiler and linker are the pinned builds (config/toolchain.txt)."""
    problems = toolchain_problems()
    if problems:
        sys.exit('Wrong toolchain; results would not be comparable (set XDK_DIR to the extracted XDK 9328):\n  '
                 + '\n  '.join(problems))


def pe_reader(exe):
    pe = struct.unpack('<I', exe[0x3C:0x40])[0]
    nsec = struct.unpack('<H', exe[pe + 6:pe + 8])[0]
    optsz = struct.unpack('<H', exe[pe + 20:pe + 22])[0]
    base = struct.unpack('<I', exe[pe + 24 + 28:pe + 24 + 32])[0]
    entry = base + struct.unpack('<I', exe[pe + 24 + 16:pe + 24 + 20])[0]
    secs = []
    for i in range(nsec):
        o = pe + 24 + optsz + i * 40
        vs, va, rs, ra = struct.unpack('<IIII', exe[o + 8:o + 24])
        secs.append((base + va, rs, ra))

    def read(va, size):
        for sva, rs, ra in secs:
            if sva <= va < sva + rs:
                return exe[ra + va - sva: ra + va - sva + size]
        raise ValueError('address %08X not in any section' % va)
    return read, entry


def self_test(read, env):
    """Prove the relocation check catches what the byte comparison cannot. Returns True if every case is caught."""
    ok = True
    tmp = tempfile.mkdtemp(prefix='cd2verify_selftest_')
    # 1. end to end: a tail call to the wrong function with the same signature
    src = os.path.join(ROOT, 'src', 'VFX', 'cAmbientVFXSpawner.cpp')
    text = open(src).read()
    old = ('    void cAmbientVFXSpawner::OnBecomeRelevantToPlayer()\n    {\n        if (!RetAmbientVFXPrototype()->m_bRandSpawn)\n'
           '            return;\n        CalcRandInitSpawnTime();\n    }\n')
    if text.count(old) != 1:
        print('self-test: cannot find OnBecomeRelevantToPlayer in %s (update the self-test)' % src)
        return False
    bad = os.path.join(tmp, 'wrong_callee.cpp')
    open(bad, 'w').write(text.replace(old, old.replace('CalcRandInitSpawnTime();', 'CalcRandRespawnTime();')))
    obj = os.path.join(tmp, 'wrong_callee.obj')
    subprocess.run([os.path.join(BIN, 'cl.exe')] + FLAGS + ['/I' + os.path.dirname(src), '/Fo' + obj, bad],
                   env=env, capture_output=True, text=True, check=True)
    va, size = 0x827F9498, 24
    name = [n for n, c, rel in coff.functions(obj) if '?OnBecomeRelevantToPlayer@cAmbientVFXSpawner@' in n][0]
    code, rel = [(c, rel) for n, c, rel in coff.functions(obj) if n == name][0]
    bytes_exact = coff.compare(code, read(va, size), rel)[0]
    robj = relocs.Obj(obj)
    res, _ = relocs.resolve(robj, name, read(va, size), va)
    known = {n: a for n, a in ((x, 0x827F94C0) for x in robj.functions() if '?CalcRandInitSpawnTime@' in x)}
    known.update({x: 0x827F9598 for x in robj.functions() if '?CalcRandRespawnTime@' in x})
    probs = relocs.check_consistency([('selftest', name, s, a, k, o, robj) for s, a, k, o in res], read, {}, known)
    caught = bool(probs)
    print('self-test wrong callee (bytes %s): %s' % ('still match' if bytes_exact else 'differ', 'caught' if caught else 'NOT CAUGHT'))
    ok &= caught and bytes_exact
    # 2. synthetic cases
    class _O:
        def symbol_bytes(self, name, n):
            return None
    o = _O()
    cases = [
        ('one address under two names', [('a', 'f', '?Foo@@YAXXZ', 0x82000000, 'call', 0, o), ('b', 'g', '?Bar@@YAXXZ', 0x82000000, 'call', 0, o)]),
        ('one name at two addresses', [('a', 'f', '?Foo@@YAXXZ', 0x82000000, 'call', 0, o), ('b', 'g', '?Foo@@YAXXZ', 0x82000010, 'call', 0, o)]),
        ('Ext_ name with the wrong address', [('a', 'f', 'Ext_82000010', 0x82000000, 'call', 0, o)]),
        ('constant with the wrong value', [('a', 'f', '__real@3f800000', 0x827F9748, 'data', 0, o)]),
    ]
    for what, entries in cases:
        caught = bool(relocs.check_consistency(entries, read, {}, {}))
        ok &= caught
        print('self-test %-32s %s' % (what, 'caught' if caught else 'NOT CAUGHT'))
    # 3. not an error: a name with internal linkage (each file's own copy, like Ret_OK) at a different address per file
    class _S(_O):
        internal = {'?Ret_OK@@3VRetVal@Fun_Runtime@@B'}
    s = _S()
    entries = [('a', 'f', '?Ret_OK@@3VRetVal@Fun_Runtime@@B', 0x82000000, 'data', 0, s),
               ('b', 'g', '?Ret_OK@@3VRetVal@Fun_Runtime@@B', 0x82000010, 'data', 0, s)]
    accepted = not relocs.check_consistency(entries, read, {}, {})
    ok &= accepted
    print('self-test %-32s %s' % ('per-file static at two addresses', 'accepted' if accepted else 'WRONGLY REJECTED'))
    return ok


def main():
    args = [a for a in sys.argv[1:] if a != '--self-test']
    if len(args) != 1:
        print(__doc__)
        sys.exit(2)
    check_toolchain()
    exe = open(args[0], 'rb').read()
    read, entry = pe_reader(exe)
    if entry != EXPECTED_ENTRY:
        sys.exit('This executable has entry %08X, not the title-update build (%08X). Use the patched XEX only.' % (entry, EXPECTED_ENTRY))
    if '--self-test' in sys.argv:
        env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'],
                   INCLUDE=os.path.join(XDK, 'include', 'xbox') + ';' + os.path.join(ROOT, 'include'))
        sys.exit(0 if self_test(read, env) else 1)
    manifest = json.load(open(os.path.join(ROOT, 'config', 'matched_functions.json')))
    env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'],
               INCLUDE=os.path.join(XDK, 'include', 'xbox') + ';' + os.path.join(ROOT, 'include'))
    tmp = tempfile.mkdtemp(prefix='cd2verify_')
    total = ok = pending = 0
    entries, problems, known, nfuncs = [], [], {}, 0
    def compile_source(item):
        n, (src, funcs) = item
        obj = os.path.join(tmp, '%d_%s.obj' % (n, os.path.basename(src)))
        r = subprocess.run([os.path.join(BIN, 'cl.exe')] + FLAGS + ['/Fo' + obj, os.path.join(ROOT, src)],
                           env=env, capture_output=True, text=True)
        return src, funcs, obj, r

    for src, funcs, obj, r in parallel_map(compile_source, enumerate(manifest['files'].items())):
        if r.returncode:
            print('%s: COMPILE ERROR\n%s' % (src, r.stdout + r.stderr))
            total += len(funcs)
            continue
        compiled = list(coff.functions(obj))
        robj = relocs.Obj(obj)
        print(src)
        for f in funcs:
            va, size = int(f['address'], 16), f['size']
            named = [n for n, c, rel in compiled if f['symbol'] in n]
            if named and f.get('matching', True):
                known[named[0]] = va
            if f.get('ltcg'):  # exact only under LTCG: checked by tools/verify_ltcg.py
                print('  %08X  %4d bytes  %-8s %s' % (va, size, 'LTCG', f['symbol'] + '   [checked by verify_ltcg.py]'))
                continue
            tracked = f.get('matching', True)  # matching: false = work in progress, reported but not required
            if tracked:
                total += 1
            found = [(n, c, rel) for n, c, rel in compiled if f['symbol'] in n]
            if not found:
                print('  %08X  %4d bytes  symbol not found: %s' % (va, size, f['symbol']))
                continue
            name, code, rel = found[0]
            exact, ratio = coff.compare(code, read(va, size), rel)
            if tracked:
                ok += exact
            else:
                pending += 1
            if tracked and exact:
                sec = robj.functions()[name][0]
                if robj.sections[sec - 1]['name'] not in CODE_SECTIONS:
                    problems.append('%s: %s is in section %s, not an ordinary code section' % (src, name, robj.sections[sec - 1]['name']))
                res, probs = relocs.resolve(robj, name, read(va, size), va)
                entries += [(src, name, sym, addr, kind, off, robj) for sym, addr, kind, off in res]
                problems += ['%s: %s' % (src, p) for p in probs]
                nfuncs += 1
            status = 'EXACT' if exact else '%.1f%%' % (100 * ratio)
            print('  %08X  %4d bytes  %-8s %s%s' % (va, size, status, name, '' if tracked else '   [work in progress]'))
    aliases = relocs.load_aliases(os.path.join(ROOT, 'config', 'symbol_aliases.txt'))
    problems += relocs.check_consistency(entries, read, aliases, known)
    print('\n%d of %d matched functions are exact; %d work-in-progress function(s) tracked' % (ok, total, pending))
    print('relocation targets: %d references in %d exact functions checked; %s'
          % (len(entries), nfuncs, 'all consistent' if not problems else '%d PROBLEM(S):' % len(problems)))
    for p in problems:
        print('  ' + p)
    sys.exit(0 if ok == total and not problems else 1)


if __name__ == '__main__':
    main()

