"""Repository integrity gate: every function in the right file, no duplicate code.

usage: py -I tools/check_integrity.py [--no-compile] [--self-test]

Checks config/matched_functions.json and the sources against config/splits.txt (maintainer-owned ground truth).
Needs no game files; --no-compile skips check 7, the only one that needs the XDK compiler (for machines without
it). All checks must pass:
  1. files      every file in the manifest has a splits.txt entry, and every file there exists (a file may be set
                up before any of its functions is matched)
  2. ranges     no two files' text ranges overlap; no listed address belongs to two files
  3. ownership  every claimed function lies in its file's text range or is listed for that file (hot/init/atexit);
                entries marked "folded" must be listed as folded for that file and lie outside its range
  4. claims     no address is claimed by two files, and no file claims an address another file lists as folded
  5. order      the files' text ranges, initializers and at-exit destructors appear in the same (link) order
  6. types      no class/struct/union is defined in more than one place (include/ except include/ref, and src/)
  7. functions  no non-inline function is defined by more than one source file (COMDAT selection NODUPLICATES)
  8. binaries   no binary file anywhere git would track (by extension or NUL bytes): the repository holds source and
                text only; tools are submodules built from source (tools/build_tools.ps1)

The same CD2 function declared under two names is caught by the relocation-target check (tools/verify_src.py).
"""
import collections, json, os, re, struct, subprocess, sys, tempfile

TOOLS = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, TOOLS)
from verify_src import FLAGS, XDK, BIN, ROOT, parallel_map

HOT = (0x821D0000, 0x823D0000)


BINARY_EXT = ('.exe', '.dll', '.lib', '.obj', '.o', '.a', '.so', '.pdb', '.ilk', '.exp', '.xdb', '.pe', '.xex', '.i64',
              '.idb', '.pyc', '.bin', '.zip', '.7z', '.rar', '.iso')


def binary_files(extra=()):
    """Binary files among those git would track (all files outside .git and build/ when git is unavailable)."""
    files = None
    try:
        r = subprocess.run(['git', '-C', ROOT, 'ls-files', '-co', '--exclude-standard'], capture_output=True, text=True)
        if r.returncode == 0:
            files = [os.path.join(ROOT, f) for f in r.stdout.splitlines()]
    except FileNotFoundError:
        pass
    if files is None:
        files = [os.path.join(dp, f) for dp, dn, fn in os.walk(ROOT) for f in fn
                 if not (os.sep + '.git' in dp or dp.startswith(os.path.join(ROOT, 'build'))
                         or os.sep + '__pycache__' in dp)]
    bad = []
    for p in list(files) + list(extra):
        if not os.path.isfile(p):  # e.g. submodule gitlinks
            continue
        if p.lower().endswith(BINARY_EXT):
            bad.append(rel(p))
            continue
        with open(p, 'rb') as fh:
            if b'\0' in fh.read(1 << 16):
                bad.append(rel(p))
    return bad


def rel(path):
    try:
        return os.path.relpath(path, ROOT)
    except ValueError:  # another drive (e.g. the self-test's temporary files)
        return path


def load_splits(path):
    files, cur = collections.OrderedDict(), None
    for n, line in enumerate(open(path), 1):
        body = line.split('#', 1)[0].rstrip()
        if not body.strip():
            continue
        if not line[0].isspace():
            cur = body.strip()
            files[cur] = dict(text=None, hot=[], init=[], atexit=[], folded=[], line=n)
            continue
        parts = body.split()
        kind = parts[0]
        vals = [int(v, 16) for v in parts[1:]]
        if kind == 'text':
            files[cur]['text'] = (vals[0], vals[1])
        elif kind in ('hot', 'init', 'atexit', 'folded'):
            files[cur][kind].append(vals[0])
        else:
            raise SystemExit('splits.txt line %d: unknown entry %r' % (n, kind))
    return files


def type_definitions(extra_roots=()):
    defs = collections.defaultdict(set)
    roots = [os.path.join(ROOT, 'include'), os.path.join(ROOT, 'src')] + list(extra_roots)
    for root in roots:
        for dp, dn, fn in os.walk(root):
            if os.path.join(ROOT, 'include', 'ref') in dp:
                continue
            for f in fn:
                if not f.endswith(('.h', '.cpp')):
                    continue
                path = os.path.join(dp, f)
                text = open(path, encoding='utf-8', errors='replace').read()
                text = re.sub(r'//[^\n]*|/\*.*?\*/', '', text, flags=re.S)
                text = re.sub(r'"(?:\\.|[^"\\])*"', '""', text)
                stack, depth = [], 0
                pat = (r'\bnamespace\s+(\w+)\s*\{|\b(class|struct|union)\s+(?:__declspec\([^)]*\)\s*)?(\w+)\s*'
                       r'(?::[^{;()]*)?\{|\{|\}')
                for tok in re.finditer(pat, text):
                    if tok.group(1):
                        stack.append((tok.group(1), depth))
                        depth += 1
                    elif tok.group(3):
                        q = '::'.join([s[0] for s in stack] + [tok.group(3)])
                        defs[q].add(rel(path))
                        stack.append((tok.group(3), depth))
                        depth += 1
                    elif tok.group(0) == '{':
                        depth += 1
                    else:
                        depth -= 1
                        while stack and stack[-1][1] >= depth:
                            stack.pop()
    return defs


def coff_function_defs(obj):
    """[(name, comdat_selection)] for external function definitions in a COFF object (selection 0 = not COMDAT)"""
    d = open(obj, 'rb').read()
    mach, nsec, _, symptr, nsym, opt, _ = struct.unpack('<HHIIIHH', d[:20])
    chars = [struct.unpack_from('<I', d, 20 + opt + 40 * i + 36)[0] for i in range(nsec)]
    strtab = symptr + nsym * 18
    sel, funcs, i = {}, [], 0
    while i < nsym:
        o = symptr + i * 18
        raw, val, sec, typ, cls, naux = struct.unpack_from('<8sIhHBB', d, o)
        name = (d[strtab + struct.unpack('<I', raw[4:])[0]:].split(b'\0', 1)[0] if raw[:4] == b'\0\0\0\0'
                else raw.rstrip(b'\0')).decode('latin-1')
        if cls == 3 and naux and val == 0 and sec > 0 and chars[sec - 1] & 0x1000:
            sel[sec] = d[o + 18 + 14]
        if cls == 2 and sec > 0 and typ & 0x20:
            funcs.append((name, sec))
        i += 1 + naux
    return [(n, sel.get(s, 0)) for n, s in funcs]


def run(manifest, splits, extra_type_roots=(), extra_sources=(), skip_compile=False, extra_files=()):
    """Return an ordered dict check -> list of failure messages."""
    failures = collections.OrderedDict((k, []) for k in ('files', 'ranges', 'ownership', 'claims', 'order', 'types',
                                                          'functions', 'binaries'))
    for b in binary_files(extra_files):
        failures['binaries'].append('%s is a binary file; the repository holds source and text only' % b)

    # 1. files (a file in splits.txt without manifest entries is set up but has no matched function yet)
    for f in set(manifest) - set(splits):
        failures['files'].append('%s is in the manifest but has no entry in splits.txt' % f)
    for f in splits:
        if not os.path.exists(os.path.join(ROOT, f)):
            failures['files'].append('%s does not exist' % f)
        if splits[f]['text'] is None:
            failures['files'].append('%s has no text range' % f)

    # 2. ranges
    rng = sorted((s['text'][0], s['text'][1], f) for f, s in splits.items() if s['text'])
    for (a0, a1, fa), (b0, b1, fb) in zip(rng, rng[1:]):
        if b0 < a1:
            failures['ranges'].append('%s [%08X, %08X) overlaps %s [%08X, %08X)' % (fa, a0, a1, fb, b0, b1))
    listed = collections.defaultdict(list)
    for f, s in splits.items():
        for kind in ('hot', 'init', 'atexit', 'folded'):
            for a in s[kind]:
                listed[a].append((f, kind))
                if kind == 'hot' and not HOT[0] <= a < HOT[1]:
                    failures['ranges'].append('%s: hot %08X is outside the order-list region' % (f, a))
    for a, who in listed.items():
        owners = {f for f, k in who if k != 'folded'}
        if len(owners) > 1:
            failures['ranges'].append('%08X is listed for several files: %s' % (a, who))
        for f0, s0, f in rng:
            if f0 <= a < s0 and any(k != 'folded' and wf != f for wf, k in who):
                failures['ranges'].append('%08X is listed for %s but lies in %s\'s range' % (a, who, f))

    # 3. ownership, 4. claims
    claims = collections.defaultdict(list)
    for f, entries in manifest.items():
        s = splits.get(f)
        if not s or not s['text']:
            continue
        lo, hi = s['text']
        for e in entries:
            a = int(e['address'], 16)
            tag = '%s %08X %s' % (f, a, e['symbol'])
            if e.get('folded'):
                if a not in s['folded']:
                    failures['ownership'].append('%s is marked folded but splits.txt does not list it as folded for this file' % tag)
                if lo <= a < hi:
                    failures['ownership'].append('%s is marked folded but lies inside the file\'s own range' % tag)
                continue
            claims[a].append(f)
            if not (lo <= a < hi or a in s['hot'] or a in s['init'] or a in s['atexit']):
                where = [g for g0, g1, g in rng if g0 <= a < g1]
                failures['ownership'].append('%s lies outside the file\'s range [%08X, %08X)%s: wrong file?'
                                             % (tag, lo, hi, (' and inside %s' % where[0]) if where else ''))
    for a, fs in claims.items():
        if len(fs) > 1:
            failures['claims'].append('%08X is claimed by %s' % (a, ', '.join(fs)))
    for a, who in listed.items():
        for f, k in who:
            if k == 'folded' and a in claims:
                failures['claims'].append('%08X is claimed by %s but listed as folded for %s' % (a, claims[a], f))

    # 5. order
    by_text = [f for _, _, f in rng]
    for kind in ('init', 'atexit'):
        have = [(min(splits[f][kind]), f) for f in by_text if splits[f][kind]]
        order = [f for _, f in sorted(have)]
        expected = [f for f in by_text if splits[f][kind]]
        if order != expected:
            failures['order'].append('%s order %s differs from text order %s' % (kind, order, expected))

    # 6. types
    for q, where in sorted(type_definitions(extra_type_roots).items()):
        if len(where) > 1:
            failures['types'].append('%s is defined in %s' % (q, ', '.join(sorted(where))))

    # 7. functions
    if not skip_compile:
        env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'],
                   INCLUDE=os.path.join(XDK, 'include', 'xbox') + ';' + os.path.join(ROOT, 'include'))
        tmp = tempfile.mkdtemp(prefix='cd2integrity_')
        owners = collections.defaultdict(list)
        sources = [os.path.join(ROOT, f) for f in manifest] + list(extra_sources)
        def compile_source(item):
            n, path = item
            obj = os.path.join(tmp, '%d_%s.obj' % (n, os.path.basename(path)))
            r = subprocess.run([os.path.join(BIN, 'cl.exe')] + FLAGS + ['/I' + os.path.dirname(path), '/Fo' + obj, path],
                               env=env, capture_output=True, text=True)
            return path, obj, r

        for path, obj, r in parallel_map(compile_source, enumerate(sources)):
            if r.returncode:
                failures['functions'].append('%s does not compile' % path)
                continue
            for name, selection in coff_function_defs(obj):
                if selection in (0, 1):  # not COMDAT, or COMDAT "no duplicates": a real (non-inline) definition
                    owners[name].append(rel(path))
        for name, fs in sorted(owners.items()):
            if len(fs) > 1:
                failures['functions'].append('%s is defined (non-inline) in %s' % (name, ', '.join(fs)))
    return failures


def self_test(no_compile=False):
    """Inject one violation of each kind into copies of the inputs; every check must catch its violation."""
    import copy
    manifest = json.load(open(os.path.join(ROOT, 'config', 'matched_functions.json')))['files']
    splits = load_splits(os.path.join(ROOT, 'config', 'splits.txt'))
    files = [f for f in splits if manifest.get(f) and splits[f]['init']]  # files with matches and initializers
    a_file, b_file = files[0], files[1]
    b_addr = '0x%08X' % splits[b_file]['text'][0]
    tmp = tempfile.mkdtemp(prefix='cd2integrity_selftest_')
    cases = []
    m = copy.deepcopy(manifest)
    m['src/SelfTest/NotInSplits.cpp'] = [{'address': b_addr, 'size': 4, 'symbol': 'SelfTest'}]
    cases.append(('files', 'a manifest file without a splits entry', m, splits, (), ()))
    m = copy.deepcopy(manifest)
    m[a_file].append({'address': b_addr, 'size': 4, 'symbol': 'SelfTest'})
    cases.append(('ownership', 'a function claimed by the wrong file', m, splits, (), ()))
    m = copy.deepcopy(manifest)
    m[a_file].append(dict(m[b_file][0]))
    cases.append(('claims', 'one address claimed by two files', m, splits, (), ()))
    m = copy.deepcopy(manifest)
    in_range = [e for e in m[a_file] if not e.get('folded') and splits[a_file]['text'][0] <= int(e['address'], 16) < splits[a_file]['text'][1]][0]
    in_range['folded'] = True
    cases.append(('ownership', 'an owned function disguised as folded', m, splits, (), ()))
    s = copy.deepcopy(splits)
    s[a_file]['init'], s[b_file]['init'] = s[b_file]['init'], s[a_file]['init']
    cases.append(('order', 'initializers assigned to the wrong files', manifest, s, (), ()))
    s = copy.deepcopy(splits)
    s[b_file]['text'] = (splits[a_file]['text'][0], splits[b_file]['text'][1])
    cases.append(('ranges', 'overlapping file ranges', manifest, s, (), ()))
    tdir = os.path.join(tmp, 'types')
    os.makedirs(tdir)
    open(os.path.join(tdir, 'dup.h'), 'w').write('namespace Fun_Runtime\n{\n    class Vec3 { float x; };\n}\n')
    cases.append(('types', 'a type defined twice', manifest, splits, (tdir,), ()))
    srcs = []
    for n in range(2):
        p = os.path.join(tmp, 'dup%d.cpp' % n)
        open(p, 'w').write('int SelfTestDuplicateFunction(int x) { return x + 1; }\n')
        srcs.append(p)
    cases.append(('functions', 'a non-inline function defined in two files', manifest, splits, (), srcs))
    disguised = os.path.join(tmp, 'notes.txt')  # binary content under a text name
    open(disguised, 'wb').write(b'MZ\x90\x00\x03\x00\x00\x00')
    cases.append(('binaries', 'a binary file disguised as .txt', manifest, splits, (), (disguised,)))
    ok = True
    for check, what, m, s, roots, extra in cases:
        if check == 'functions' and no_compile:
            print('self-test %-10s %-45s %s' % (check, what, 'skipped (needs the XDK)'))
            continue
        if check == 'binaries':
            f = run(m, s, skip_compile=True, extra_files=extra)
        else:
            f = run(m, s, roots, extra, skip_compile=(check != 'functions'))
        caught = bool(f[check])
        ok &= caught
        print('self-test %-10s %-45s %s' % (check, what, 'caught' if caught else 'NOT CAUGHT'))
    return ok


def main():
    if '--self-test' in sys.argv:
        sys.exit(0 if self_test('--no-compile' in sys.argv) else 1)
    manifest = json.load(open(os.path.join(ROOT, 'config', 'matched_functions.json')))['files']
    splits = load_splits(os.path.join(ROOT, 'config', 'splits.txt'))
    no_compile = '--no-compile' in sys.argv
    failures = run(manifest, splits, skip_compile=no_compile)
    bad = 0
    for k, msgs in failures.items():
        print('%-10s %s' % (k, 'SKIPPED (needs the XDK)' if no_compile and k == 'functions' else 'PASS' if not msgs else 'FAIL'))
        for m in msgs:
            print('    ' + m)
        bad += len(msgs)
    print('\n%d files, %d claimed functions: %s' % (len(manifest), sum(len(v) for v in manifest.values()),
                                                     'integrity OK' if not bad else '%d problem(s)' % bad))
    print('%d source files set up in splits.txt' % len(splits))
    sys.exit(1 if bad else 0)


if __name__ == '__main__':
    main()
