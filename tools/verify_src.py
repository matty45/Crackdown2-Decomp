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
import atexit, hashlib, json, os, re, shutil, struct, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
import buildcache  # noqa: E402
import coff  # noqa: E402
import cvtypes  # noqa: E402
import relocs  # noqa: E402

# every tool's working folders: build/cd2/tmp/<pid>_<prefix>... (build/ is ignored by git)
WORK_TMP = os.path.join(ROOT, 'build', 'cd2', 'tmp')
_pruned = []


def pid_alive(pid):
    """Whether process pid still runs (on Windows through the kernel's process table; elsewhere with signal 0). A
    process of another user that cannot be opened counts as running."""
    if os.name != 'nt':
        try:
            os.kill(pid, 0)
        except ProcessLookupError:
            return False
        except PermissionError:
            return True
        return True
    import ctypes
    k32 = ctypes.windll.kernel32
    h = k32.OpenProcess(0x1000, False, pid)  # PROCESS_QUERY_LIMITED_INFORMATION
    if not h:
        return k32.GetLastError() == 5  # ERROR_ACCESS_DENIED: it exists
    try:
        code = ctypes.c_ulong()
        return bool(k32.GetExitCodeProcess(h, ctypes.byref(code))) and code.value == 259  # STILL_ACTIVE
    finally:
        k32.CloseHandle(h)


def prune_work_dirs():
    """Remove the working folders of processes that no longer run (killed ones never reach their atexit), and any
    older than a week (a process id the system has since given to another process)."""
    import time
    for name in os.listdir(WORK_TMP):
        path = os.path.join(WORK_TMP, name)
        pid = int(name.split('_', 1)[0]) if name.split('_', 1)[0].isdigit() else None
        if pid is None or pid == os.getpid():
            continue  # not a working folder (they are named <pid>_...), or this process's own
        try:
            stale = not pid_alive(pid) or time.time() - os.path.getmtime(path) > 7 * 86400
        except OSError:
            continue
        if stale:
            shutil.rmtree(path, ignore_errors=True)


def work_dir(prefix):
    """A working folder private to this process, removed when it exits; folders left by processes that were killed
    are removed by the next tool that makes one (prune_work_dirs). Every tool makes its folders here, never in the
    system's temporary folder, where nothing would ever remove a killed process's folders."""
    os.makedirs(WORK_TMP, exist_ok=True)
    if not _pruned:
        _pruned.append(True)
        prune_work_dirs()
    d = tempfile.mkdtemp(prefix='%d_%s' % (os.getpid(), prefix), dir=WORK_TMP)
    atexit.register(shutil.rmtree, d, ignore_errors=True)
    return d


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

# Compiler settings that differ from FLAGS for some objects (a library built with other settings, such as Lua with
# automatic inlining): maintainer-owned, one line per source file or directory (a path ending in /), each with its
# evidence. Only these options may appear; anything else is an error, so that no flag can change what a check proves.
FILE_FLAGS = os.path.join(ROOT, 'config', 'file_flags.txt')
# (a /D value is a name or number, or a quoted header name next to the file, for a library's configuration header such
# as Lua's LUA_USER_H; /O1 and /fp:precise are a library's optimization level and floating-point model, and /TP compiles
# a library's .c files as C++, as libjpeg's; /Oi enables the compiler's intrinsic implementations)
FILE_OPTION = re.compile(r'^(?:/Ob[012]|/O[12]|/Oi|/TP|/fp:(?:precise|fast|strict)|/D[A-Za-z_]\w*(?:=(?:[\w.]+|"\w+\.h"))?|plain)$')


def load_file_flags(path=None):
    """[(repository path or directory ending in /, [options])] from config/file_flags.txt. Raises ValueError on an
    option outside FILE_OPTION or a line without options."""
    path = path or FILE_FLAGS
    out = []
    if not os.path.exists(path):
        return out
    for n, line in enumerate(open(path), 1):
        body = line.split('#', 1)[0].split()
        if not body:
            continue
        if len(body) < 2:
            raise ValueError('%s line %d: a path without options' % (os.path.basename(path), n))
        bad = [o for o in body[1:] if not FILE_OPTION.match(o)]
        if bad:
            raise ValueError('%s line %d: option(s) not allowed: %s (allowed: /Ob0-2, /O1, /O2, /Oi, /TP, /fp:precise|fast|strict, /D<name>[=<value> or ="<header>.h"], plain)'
                             % (os.path.basename(path), n, ' '.join(bad)))
        out.append((body[0].replace('\\', '/'), body[1:]))
    return out


def _repo_path(src):
    p = os.path.abspath(os.path.join(ROOT, src))
    try:
        r = os.path.relpath(p, ROOT)
    except ValueError:  # another drive
        return None
    return None if r.startswith('..') else r.replace('\\', '/')


def file_options(src, table=None):
    """The options config/file_flags.txt gives src (repository-relative or absolute): those of every directory entry
    that contains it, then its own entry. A file outside the repository (a self-test copy) has none."""
    r = _repo_path(src)
    if r is None:
        return []
    out = []
    for p, opts in (load_file_flags() if table is None else table):
        if r == p or (p.endswith('/') and r.startswith(p)):
            out += opts
    return out


def file_flags(src, table=None):
    """The compiler flags src adds to FLAGS (later flags win, so /Ob2 replaces FLAGS' /Ob1)."""
    return [o for o in file_options(src, table) if o != 'plain']


def flags_for(src, table=None):
    return FLAGS + file_flags(src, table)


def compiled_as_c(src, table=None):
    """Whether src is compiled as C (a .c file without /TP in config/file_flags.txt): its symbols are exact C names."""
    return src.lower().endswith('.c') and '/TP' not in file_options(src, table)


def ltcg_built(src, table=None):
    """Whether CD2 built src's object with /GL. Not for C: CD2's Rich header lists objects of the 15.00.8153 C compiler
    but none of its LTCG C compiler. Not for a file marked plain in config/file_flags.txt. A plain object gets no LTCG
    gate, and its bodies are never shown to another file's LTCG model."""
    return not src.lower().endswith('.c') and 'plain' not in file_options(src, table)


# Middleware whose original source the repository holds (config/middleware.txt): maintainer-owned, one line per library
# directory under src/middleware/, naming the [match] rules that library's original source breaks, with the reason. A
# finding of a waived rule in a file of that directory does not block a match there; nothing else is waived, and no
# file outside src/middleware/ (game code) can be. R13 (vtables) and R18 (assembly) can never be waived.
MIDDLEWARE = os.path.join(ROOT, 'config', 'middleware.txt')
MIDDLEWARE_ROOT = 'src/middleware/'
WAIVABLE = ('R1', 'R2', 'R4', 'R17')


def load_middleware(path=None):
    """[(library directory ending in /, [waived rules])] from config/middleware.txt. Raises ValueError on a directory
    that is not one level below src/middleware/, a rule outside WAIVABLE, or a line without its reason."""
    path = path or MIDDLEWARE
    out = []
    if not os.path.exists(path):
        return out
    for n, line in enumerate(open(path), 1):
        body, _, why = line.partition('#')
        body = body.split()
        if not body:
            continue
        where = '%s line %d' % (os.path.basename(path), n)
        d = body[0].replace('\\', '/')
        if not (d.startswith(MIDDLEWARE_ROOT) and d.endswith('/') and d.count('/') == MIDDLEWARE_ROOT.count('/') + 1):
            raise ValueError('%s: %s is not a library directory src/middleware/<library>/' % (where, body[0]))
        bad = [r for r in body[1:] if r not in WAIVABLE]
        if bad:
            raise ValueError('%s: rule(s) that cannot be waived: %s (allowed: %s)' % (where, ' '.join(bad),
                                                                                    ' '.join(WAIVABLE)))
        if not why.strip():
            raise ValueError('%s: a waiver without its reason (# why the original source breaks the rule)' % where)
        out.append((d, body[1:]))
    return out


def waived(src, rule, table=None):
    """Whether config/middleware.txt waives rule for src (a repository-relative path)."""
    r = _repo_path(src)
    if r is None:
        return False
    return any(r.startswith(d) and rule in rules for d, rules in (load_middleware() if table is None else table))


# the first character of a this-adjusting thunk's code after the function's scope: adjustors (private G/H, protected
# O/P, public W/X) and vtordisp thunks ($). The same characters also start template arguments (`H` int, `$0` a
# value), so a name is such a thunk only if dbghelp says so. A vcall thunk (`??_9`, "`vcall'") is not one: it is a
# thunk in its own right, not a copy of a named function.
THUNK_START = frozenset('GHOPWX$')
_thunks = {}


def is_thunk(name):
    """Whether name is an adjustor or vtordisp thunk of a function (dbghelp: "`adjustor{...}'", "`vtordisp{...}'")."""
    if name not in _thunks:
        try:
            u = undecorate(name)
            _thunks[name] = u.startswith('[thunk]:') and ('`adjustor{' in u or '`vtordisp' in u)
        except RuntimeError:
            _thunks[name] = False
    return _thunks[name]


def symbol_matches(symbol, name):
    """A manifest symbol names a compiled function: a mangled C++ name by its prefix (usually stopping before the
    argument list), a C name exactly (`resume` must not also name `resume_error` or `lua_resume`). A prefix that ends
    at `@@` (`?RetClass@cX@AI@@`) does not name the this-adjusting thunks of that function (`?RetClass@cX@AI@@WBA@...`),
    which a class with several vtables also compiles: a thunk is named only by a symbol that includes its code
    (`??_EcBloom@VFX@@WBI@`)."""
    if not symbol.startswith('?'):
        return symbol == name
    if not name.startswith(symbol):
        return False
    return not (symbol.endswith('@@') and name[len(symbol):len(symbol) + 1] in THUNK_START and is_thunk(name))


_undname = None


def undecorate(name):
    """The C++ declaration a mangled name stands for (`public: virtual void __cdecl NS::cFoo::Bar(int)`), by Windows'
    own dbghelp.dll (the XDK ships no undname.exe; the project runs on Windows only)."""
    global _undname
    import ctypes, threading
    if _undname is None:
        f = ctypes.windll.dbghelp.UnDecorateSymbolName
        f.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_uint32, ctypes.c_uint32]
        _undname = (f, threading.Lock())  # dbghelp is not thread-safe
    f, lock = _undname
    buf = ctypes.create_string_buffer(4096)
    with lock:
        n = f(name.encode('latin-1'), buf, len(buf), 0)
    if not n:
        raise RuntimeError('dbghelp cannot undecorate %s' % name)
    return buf.value.decode('latin-1')


def plain_member(name):
    """Whether a compiled function is a member function that is neither virtual nor static: the kind of function CD2
    cannot have put in a vtable."""
    return bool(name.startswith('?') and
                re.match(r'(?:public|protected|private): (?!virtual |static )', undecorate(name)))


def vtable_slot_problem(name, fact):
    """A matched function CD2 puts in a vtable (fact: the recorded `vtable` fact, or None) declared as a plain member
    function: its bytes match, but the class's vtable lacks the slot, or the function belongs to another class. None
    when there is nothing to report."""
    if not fact or not plain_member(name):
        return None
    return ('R13 (vtables from evidence): CD2 puts this function in a vtable (slot %d of the table at %s, %d table(s) '
            'in all), but it is declared as a plain member function: declare it virtual in that slot of the class that '
            'owns the table (AGENTS.md)' % (fact['slot'], fact['table'], fact['tables']))


def vtable_fact(address, symbol, references):
    """The `vtable` fact of a matched function, from the game's references (cd2.py game_references()): its lowest
    slot, that slot's table and how many tables hold it, or None when no vtable holds it. None as well for C
    functions, dynamic initializers and at-exit functions, which are never virtual (the tables that point at them, such
    as the CRT's initializer list, are not vtables), and for an address CD2 registers as a script method under the
    symbol's own name: a non-virtual method whose code was folded with a virtual's (cTimeOfDay::RetPeriod)."""
    if not symbol.startswith('?') or symbol.startswith('??__'):
        return None
    address = '0x%08X' % int(address, 16)
    tables = references['vtables'].get(address)
    if not tables:
        return None
    m = re.match(r'\?([A-Za-z_]\w*)@', symbol)
    if m and any(n == m.group(1) for _, n in references['names'].get(address, [])):
        return None
    table, slot, _ = min(tables, key=lambda t: t[1])
    return dict(table=table, slot=slot, tables=len(tables))


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


# the image `cd2.py setup` extracts from default_patched.xex: SHA1 of every section's name, address and file bytes
# (what the tools read; the PE headers are left out), so that a damaged or different extraction is refused instead of
# compared against
IMAGE_SHA1 = '0C3091FF5BE77B8FC78D6474229193B598F6CC36'


def compile_z7(src, out_dir, env, path=None):
    """A /Z7 build of src (or a modified copy at path) in out_dir, beside the gate's own (whose flags stay as pinned;
    /Z7 adds debug records only), for the sizes of its data (tools/cvtypes.py). Returns its path; exits on a compile
    error, as the gate's own build of the same source would have failed too."""
    obj = os.path.join(out_dir, os.path.basename(src) + '.z7.obj')
    r = buildcache.compile([os.path.join(BIN, 'cl.exe')] + flags_for(src) + ['/Z7', '/I' + os.path.dirname(os.path.join(ROOT, src)),
                            '/Fo' + obj, path or os.path.join(ROOT, src)], env, run=run_compiler)
    if r.returncode:
        raise SystemExit('%s: compile error in the /Z7 build\n%s' % (src, r.stdout + r.stderr))
    return obj


def compile_sizes(src, out_dir, env, path=None):
    """{symbol: size} of the data src defines (compile_z7, tools/cvtypes.py)"""
    return cvtypes.data_sizes(compile_z7(src, out_dir, env, path))


def table_lookups(references):
    """(words_of, table_words) from the game's references (cd2.py game_references()): the CD2 words holding a
    function's address, and the number of words in CD2's table at an address (None if no table starts there)."""
    words = {int(a, 16): [int(t, 16) + 4 * slot for t, slot, _ in lst] for a, lst in references['vtables'].items()}
    tables = {int(t, 16): n for t, n in references.get('tables', {}).items()}
    return (lambda a: words.get(a, ())), tables.get


def game_tables(read):
    """(words_of, (table_words, own_slot)) for relocs.check_all_data, from the game: own_slot(file, word address) says
    the function CD2's word there points at lies in the file's text range (config/splits.txt)."""
    import cd2  # the game's tables and the split ranges
    words_of, table_words = table_lookups(cd2.game_references())
    splits = cd2.load_splits(cd2.SPLITS)

    def own_slot(f, a):
        try:
            return cd2.owner(struct.unpack('>I', read(a, 4))[0], splits) == f
        except (ValueError, struct.error):
            return False
    return words_of, (table_words, own_slot)


def coverage_figures(reached, file_objs, npointers, entries=(), splits=None):
    """How much of the data the files define is located in CD2 and checked (the rest no matched function, pointer or
    anchor reaches yet), and how many files have data ranges in splits.txt: dict(located, defined, pointers[, ranged,
    files])"""
    defined = {relocs.data_key(f, n, o) for f, o in file_objs for n in o.data_names()}
    located = {relocs.data_key(f, sym, o) for f, sym, addr, o, d in reached}
    located |= {relocs.data_key(f, sym, o) for f, fn, sym, addr, kind, off, o in entries
                if relocs.is_string(sym) or relocs.is_constant(sym)}
    out = dict(located=len(located & defined), defined=len(defined), pointers=npointers)
    if splits is not None:
        out.update(ranged=sum(1 for s in splits.values() if any(s[k] for k in relocs.DATA_RANGES)), files=len(splits))
    return out


def data_coverage(reached, file_objs, npointers, entries=(), splits=None):
    """The data line of a gate's summary (coverage_figures)"""
    c = coverage_figures(reached, file_objs, npointers, entries, splits)
    line = 'data: %(located)d of the %(defined)d data symbols the files define located in CD2 and checked (%(pointers)d ' \
           'pointers in them)' % c
    if splits is not None:
        line += '; %(ranged)d of %(files)d files have data ranges' % c
    return line


def data_splits():
    """config/splits.txt as tools/check_integrity.py reads it, for relocs.check_ownership"""
    from check_integrity import load_splits  # it imports this module
    return load_splits(os.path.join(ROOT, 'config', 'splits.txt'))


def game_data_check(read):
    """relocs.check_all_data's check against CD2's bytes"""
    return lambda f, sym, addr, obj, d: relocs.check_data(f, sym, addr, d, read, obj)


def pe_reader(exe):
    """(read(va, n), entry point) of the extracted game image. Exits unless it is the image setup extracts."""
    pe = struct.unpack('<I', exe[0x3C:0x40])[0]
    nsec = struct.unpack('<H', exe[pe + 6:pe + 8])[0]
    optsz = struct.unpack('<H', exe[pe + 20:pe + 22])[0]
    base = struct.unpack('<I', exe[pe + 24 + 28:pe + 24 + 32])[0]
    entry = base + struct.unpack('<I', exe[pe + 24 + 16:pe + 24 + 20])[0]
    secs = []
    digest = hashlib.sha1()
    for i in range(nsec):
        o = pe + 24 + optsz + i * 40
        vs, va, rs, ra = struct.unpack('<IIII', exe[o + 8:o + 24])
        secs.append((base + va, rs, ra))
        digest.update(exe[o:o + 8] + struct.pack('<II', base + va, rs) + exe[ra:ra + rs])
    if digest.hexdigest().upper() != IMAGE_SHA1:
        raise SystemExit('The extracted game image is not the one `py -I tools/cd2.py setup` extracts from '
                         'default_patched.xex (section digest %s, expected %s): delete build/cd2/orig and run setup '
                         'again with the patched XEX.' % (digest.hexdigest().upper(), IMAGE_SHA1))

    def read(va, size):
        for sva, rs, ra in secs:
            if sva <= va < sva + rs:
                return exe[ra + va - sva: ra + va - sva + size]
        raise ValueError('address %08X not in any section' % va)
    return read, entry


def self_test(read, env):
    """Prove the relocation check catches what the byte comparison cannot. Returns True if every case is caught."""
    ok = True
    tmp = work_dir('verify_selftest_')
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
    # 1b. end to end: a relocated instruction whose register differs (CD2's lwz r3 made lwz r4: RetClass would return
    # garbage). The relocation patches only the 16-bit immediate, so the comparison must still see the register.
    src = os.path.join(ROOT, 'src', 'Audio', 'cVOAScheduler.cpp')
    obj = os.path.join(tmp, 'register.obj')
    subprocess.run([os.path.join(BIN, 'cl.exe')] + flags_for('src/Audio/cVOAScheduler.cpp') + ['/Fo' + obj, src],
                   env=env, capture_output=True, text=True, check=True)
    va, size = 0x82836DF0, 12
    hit = [(c, rel) for n, c, rel in coff.functions(obj) if n.startswith('?RetClass@cVOAScheduler@Audio@@')]
    target = bytearray(read(va, size))
    if len(hit) != 1 or target[4] >> 2 != 32 or (struct.unpack_from('>I', target, 4)[0] >> 21) & 31 != 3:
        print('self-test: cVOAScheduler::RetClass is not `lis; lwz r3; blr` at %08X (update the self-test)' % va)
        return False
    code, rel = hit[0]
    exact = coff.compare(code, bytes(target), rel)[0]
    struct.pack_into('>I', target, 4, struct.unpack_from('>I', target, 4)[0] & ~(31 << 21) | (4 << 21))
    caught = exact and not coff.compare(code, bytes(target), rel)[0]
    print('self-test %-32s %s' % ('register in a relocated word', 'caught' if caught else 'NOT CAUGHT'))
    ok &= caught
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
    # 4. a matched function with internal linkage (a header static's at-exit destructor): each file's reference must
    # reach that file's own manifest entry (relocs.known_key), and within a file two internal names cannot share an address
    fn = '??__FgRandGen@CHARACTER@@YAXXZ'

    class _F(_O):
        internal = {fn, '?fSlopeDotLimit@CHARACTER@@3MB', '?fStepDotLimit@CHARACTER@@3MB'}
    s = _F()
    known = {relocs.known_key('a', fn, s): 0x83000000, relocs.known_key('b', fn, s): 0x83000010}
    own = [('a', 'f', fn, 0x83000000, 'address', 0, s), ('b', 'g', fn, 0x83000010, 'address', 0, s)]
    accepted = not relocs.check_consistency(own, read, {}, known)
    ok &= accepted
    print('self-test %-32s %s' % ('per-file function, own copies', 'accepted' if accepted else 'WRONGLY REJECTED'))
    for what, entries in (
            ('per-file function, other copy', [('a', 'f', fn, 0x83000010, 'address', 0, s)]),
            ('two statics at one address', [('a', 'f', '?fSlopeDotLimit@CHARACTER@@3MB', 0x83800000, 'store', 0, s),
                                            ('a', 'g', '?fStepDotLimit@CHARACTER@@3MB', 0x83800000, 'store', 0, s)])):
        caught = bool(relocs.check_consistency(entries, read, {}, known))
        ok &= caught
        print('self-test %-32s %s' % (what, 'caught' if caught else 'NOT CAUGHT'))
    data_ok = data_self_test(read, env, tmp)
    owner_ok = ownership_self_test(read, env, tmp)
    return cache_self_test(env, tmp) and owner_ok and data_ok and ok


def ownership_self_test(read, env, tmp):
    """Data ownership (relocs.check_ownership) against ranges proposed from a file's own located data (cd2.py
    datasplits): those ranges hold it; the same ranges moved past the data, or given to another file, must not."""
    import cd2
    src = 'src/AI/cChaseBehaviour.cpp'
    _, _, reached = file_checks(src, None, read, env, os.path.join(tmp, 'owner'), splits={})
    ranges, folded = cd2.propose_data_ranges(reached)

    def splits_with(owner, rs):
        entry = dict((k, [(s, e) for kind, s, e, _, _, _ in rs if kind == k]) for k in relocs.DATA_RANGES)
        entry['folded'] = folded.get(src, [])
        return {owner: entry, src: dict(entry) if owner == src else dict((k, []) for k in relocs.DATA_RANGES)}
    moved = [(k, s + 0x1000, e + 0x1000, n, x, y) for k, s, e, n, x, y in ranges.get(src, [])]
    results = [("the file's own data ranges", not relocs.check_ownership(reached, splits_with(src, ranges.get(src, []))),
                'accepted'),
               ('data ranges moved past the data', bool(relocs.check_ownership(reached, splits_with(src, moved))), 'caught'),
               ("its data in another file's range", bool(relocs.check_ownership(
                   reached, splits_with('src/SelfTest/Other.cpp', ranges.get(src, [])))), 'caught')]
    ok = bool(ranges.get(src))
    if not ok:
        print('self-test %-32s cannot plant it: %s has no located data (update the self-test)' % ('data ownership', src))
    for what, good, word in results:
        ok &= good
        print('self-test %-32s %s' % (what, word if good else 'WRONGLY REJECTED' if word == 'accepted' else 'NOT CAUGHT'))
    return ok


def cache_self_test(env, tmp):
    """The build cache (tools/buildcache.py) reuses an object only while nothing the compiler read has changed, and a
    reused object is the one a fresh build gives, but for what no gate reads: the COFF time stamp, and the .debug$S
    record naming the object file (a reused object keeps its first build's name)."""
    saved = buildcache.CACHE, os.environ.pop('CD2_NO_CACHE', None)
    buildcache.CACHE = os.path.join(tmp, 'cache')
    src = 'src/AI/cChaseBehaviour.cpp'

    def build(n):  # objects of equally long names, so that the sections lie at the same offsets
        obj = os.path.join(tmp, 'cache_%d.obj' % n)
        r = buildcache.compile([os.path.join(BIN, 'cl.exe')] + flags_for(src) + ['/Fo' + obj, os.path.join(ROOT, src)], env)
        with open(obj, 'rb') as fh:
            b = bytearray(fh.read())
        b[4:8] = bytes(4)
        nsec, opt = struct.unpack_from('<HH', b, 2)[0], struct.unpack_from('<H', b, 16)[0]
        for i in range(nsec):
            o = 20 + opt + 40 * i
            if b[o:o + 8].rstrip(b'\0') == b'.debug$S':
                size, raw = struct.unpack_from('<II', b, o + 16)
                b[raw:raw + size] = bytes(size)
        return r.returncode, bytes(b)
    try:
        before = dict(buildcache.stats)
        _, first = build(1)
        _, second = build(2)
        reused = buildcache.stats['hits'] == before['hits'] + 1 and buildcache.stats['misses'] == before['misses'] + 1
        os.environ['CD2_NO_CACHE'] = '1'
        _, fresh = build(3)
        del os.environ['CD2_NO_CACHE']
        same = first == second == fresh
        # a header the compiler read now hashes differently: the entry must not be reused
        real = buildcache.file_sha
        buildcache.file_sha = lambda p: 'changed' if p.lower().endswith('aiconstants.h') else real(p)
        try:
            build(4)
        finally:
            buildcache.file_sha = real
        missed = buildcache.stats['misses'] == before['misses'] + 2
    finally:
        buildcache.CACHE = saved[0]
        if saved[1] is not None:
            os.environ['CD2_NO_CACHE'] = saved[1]
    for what, good, word in (('cache reuses an unchanged build', reused, 'accepted'),
                             ('cached object equals a fresh one', same, 'accepted'),
                             ('cache misses a changed header', missed, 'caught')):
        print('self-test %-32s %s' % (what, word if good else 'WRONGLY REJECTED' if word == 'accepted' else 'NOT CAUGHT'))
    return reused and same and missed


# Data plants: a shadowing copy of a header beside a copy of the source (its quoted #include finds the copy first)
# changes only data that one of the file's matched functions reaches; that function's bytes stay exact. Each is
# (what, source, header (under include/, or beside the source), old, new, the matched function that must stay exact,
# and optionally an edit of the source copy (old, new)).
DATA_PLANTS = [
    # a header constant the matched fPOINT_LOCK_RADIUS_SQ initializer loads: only its initialized value changes
    ('a changed initial value', 'src/AI/cChaseBehaviour.cpp', 'AI/aiconstants.h',
     'static const float fPOINT_LOCK_RADIUS = fCHARACTER_HALF_HEIGHT;',
     'static const float fPOINT_LOCK_RADIUS = fCHARACTER_HALF_HEIGHT * 2.0f;', '??__EfPOINT_LOCK_RADIUS_SQ@'),
    # the same constant left zero-initialized: CD2 initializes it, the initializer still loads it the same way
    ('zero where CD2 initializes', 'src/AI/cChaseBehaviour.cpp', 'AI/aiconstants.h',
     'static const float fPOINT_LOCK_RADIUS = fCHARACTER_HALF_HEIGHT;', 'static float fPOINT_LOCK_RADIUS;',
     '??__EfPOINT_LOCK_RADIUS_SQ@'),
    # two virtuals of the spawner base swapped: the factory still stores the same table, whose slots now name the
    # matched CanSpawn and OnVFXFinished overrides at each other's places
    ('two virtual slots swapped', 'src/VFX/cLinkedVFXSpawner.cpp', 'VFX/cAmbientVFXSpawner.h',
     '        virtual bool CanSpawn() const { return m_bRelevantToPlayer != 0; }\n'
     '        virtual void OnVFXFinished() { ReleaseVFX(); }\n',
     '        virtual void OnVFXFinished() { ReleaseVFX(); }\n'
     '        virtual bool CanSpawn() const { return m_bRelevantToPlayer != 0; }\n', '?MakeNew@cLinkedVFXSpawner@'),
    # the updraft zone's last two virtuals dropped (RetClassName's body too): the factory stores a table two slots
    # shorter than CD2's, whose next word is this file's RetClassName
    ('a table missing its last slots', 'src/CHARACTER/cWingSuitUpdraftZone.cpp', 'CHARACTER/cWingSuitUpdraftZone.h',
     '        virtual const char *RetClassName() const;\n        virtual void Destruct();\n', '',
     '?MakeNew@cWingSuitUpdraftZone@',
     ('    const char *cWingSuitUpdraftZone::RetClassName() const\n    {\n        return "cWingSuitUpdraftZone";\n'
      '    }\n\n', '')),
    # a virtual inserted in the base before RetClass and IsA: the table no matched function stores is located only
    # through its own matched virtuals, and two of three now place it a slot early, where RetClassName's is wrong
    ('an anchored table shifted', 'src/cNetGameAIVehicleSpawnPoint.cpp', 'unknown/cNetGameAISpawnPoint.h',
     '        virtual const Fun_Runtime::cClass &RetClass() const;\n',
     '        virtual void VerifyDataPlant();\n        virtual const Fun_Runtime::cClass &RetClass() const;\n',
     '?RetClassName@cNetGameAIVehicleSpawnPoint@'),
    # a libjpeg message changed after its 64th byte, reached through the message table jpeg_std_error installs
    ('a long string changed late', 'src/middleware/libjpeg/jerror.c', 'src/middleware/libjpeg/jerror.h',
     '"Adobe APP14 marker: version %d, flags 0x%04x 0x%04x, transform %d"',
     '"Adobe APP14 marker: version %d, flags 0x%04x 0x%04x, transform %u"', '?jpeg_std_error@@'),
]


def plant_copy(d, src, hdr, old, new, src_edit=None):
    """A copy of src beside a copy of hdr (under include/, or a repository path beside the source) with old replaced
    by new, and src_edit (old, new) applied to the copy of src; returns the copy's path, or None if an old text is
    not there exactly once (the self-test needs updating)."""
    def edit(text, old, new):
        nl = '\r\n' if '\r\n' in text else '\n'  # a checkout may have either line ending
        old, new = old.replace('\n', nl), new.replace('\n', nl)
        return text.replace(old, new) if text.count(old) == 1 else None
    beside = hdr.startswith('src/')
    hpath = os.path.join(ROOT, hdr) if beside else os.path.join(ROOT, 'include', hdr)
    text = edit(open(hpath, newline='').read(), old, new)
    stext = open(os.path.join(ROOT, src), newline='').read()
    if src_edit:
        stext = edit(stext, *src_edit)
    if text is None or stext is None:
        return None
    target = os.path.join(d, os.path.basename(hdr) if beside else hdr)
    os.makedirs(os.path.dirname(target), exist_ok=True)
    open(target, 'w', newline='').write(text)
    path = os.path.join(d, os.path.basename(src))
    open(path, 'w', newline='').write(stext)
    return path


def file_checks(src, path, read, env, d, splits=None):
    """The plain gate's checks on one file's matched functions alone, compiled from path (a modified copy) or the
    repository: (names of its exact functions, problems, the data located). splits: data ranges to check ownership against (default
    config/splits.txt)."""
    manifest = json.load(open(os.path.join(ROOT, 'config', 'matched_functions.json')))
    os.makedirs(d, exist_ok=True)
    obj = os.path.join(d, os.path.basename(src) + '.obj')
    r = buildcache.compile([os.path.join(BIN, 'cl.exe')] + flags_for(src) + ['/I' + os.path.dirname(os.path.join(ROOT, src)),
                            '/Fo' + obj, path or os.path.join(ROOT, src)], env)
    if r.returncode:
        return set(), ['compile error'], []
    compiled = list(coff.functions(obj))
    robj = relocs.Obj(obj, compile_sizes(src, d, env, path))
    entries, known, exact = [], {}, set()
    for f in manifest['files'][src]:
        found = [(n, c, rel) for n, c, rel in compiled if symbol_matches(f['symbol'], n)]
        if f.get('ltcg') or not f.get('matching', True) or not found:
            continue
        name, code, rel = found[0]
        va, size = int(f['address'], 16), f['size']
        if coff.compare(code, read(va, size), rel)[0]:
            exact.add(name)
            known[relocs.known_key(src, name, robj)] = va
            res, _ = relocs.resolve(robj, name, read(va, size), va)
            entries += [(src, name, sym, addr, kind, off, robj) for sym, addr, kind, off in res]
    words_of, tables = game_tables(read)
    reached, problems = relocs.check_all_data(entries, game_data_check(read), tables=tables,
                                              anchors=([(src, robj)], {k: v for k, v in known.items() if isinstance(k, str)},
                                                       words_of))
    problems += relocs.check_ownership(reached, splits if splits is not None else data_splits())
    problems += relocs.check_consistency(entries, read, relocs.load_aliases(os.path.join(ROOT, 'config', 'symbol_aliases.txt')), known)
    return exact, problems, reached


def data_self_test(read, env, tmp):
    """Each data plant must add a problem to its file's own (the unmodified file's open problems do not count) while
    the function reaching the data stays byte-exact."""
    ok = True
    for k, (what, src, hdr, old, new, user, *src_edit) in enumerate(DATA_PLANTS):
        d = os.path.join(tmp, 'data_%d' % k)
        path = plant_copy(d, src, hdr, old, new, *src_edit)
        if path is None:
            print('self-test %-32s cannot plant it in %s (update the self-test)' % (what, hdr))
            ok = False
            continue
        _, before, _ = file_checks(src, None, read, env, os.path.join(d, 'clean'))
        exact, after, _ = file_checks(src, path, read, env, os.path.join(d, 'planted'))
        valid = any(n.startswith(user) for n in exact)
        caught = valid and bool(set(after) - set(before))
        ok &= caught
        print('self-test %-32s %s' % (what, 'caught' if caught else 'NOT CAUGHT' if valid else
                                      'NOT A VALID PLANT (%s no longer exact)' % user))
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
    env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'],
               INCLUDE=os.path.join(XDK, 'include', 'xbox') + ';' + os.path.join(ROOT, 'include'))
    g = plain_gate(read, env)
    problems, entries, reached = g['problems'], g['entries'], g['reached']
    splits = data_splits()
    problems += relocs.check_ownership(reached, splits)
    problems += relocs.check_consistency(entries, read, relocs.load_aliases(os.path.join(ROOT, 'config', 'symbol_aliases.txt')),
                                         g['known'])
    print('\n%d of %d matched functions are exact; %d work-in-progress function(s) tracked' % (g['ok'], g['total'], g['pending']))
    print('relocation targets: %d references in %d exact functions checked; %s'
          % (g['nrefs'], g['nfuncs'], 'all consistent' if not problems else '%d PROBLEM(S):' % len(problems)))
    print(data_coverage(reached, g['file_objs'], len(entries) - g['nrefs'], entries, splits))
    for p in problems:
        print('  ' + p)
    sys.exit(0 if g['ok'] == g['total'] and not problems else 1)


def plain_gate(read, env, out=print):
    """The plain gate's builds and checks up to the data: every file of the manifest compiled (with the sizes of its
    data), its functions compared, the references of the exact ones resolved, and the data they reach located and
    checked (relocs.check_all_data). out prints the per-function lines. Returns dict(ok, total, pending, nfuncs,
    nrefs, entries, problems, known, file_objs, reached); the caller adds the ownership and consistency checks."""
    manifest = json.load(open(os.path.join(ROOT, 'config', 'matched_functions.json')))
    tmp = work_dir('verify_')
    total = ok = pending = 0
    entries, problems, known, nfuncs, file_objs = [], [], {}, 0, []

    def build(src):
        """The gate's build of src and the sizes of its data, in a directory of its own"""
        d = os.path.join(tmp, re.sub(r'\W', '_', os.path.splitext(src)[0]))
        os.makedirs(d)
        obj = os.path.join(d, os.path.basename(src) + '.obj')
        r = buildcache.compile([os.path.join(BIN, 'cl.exe')] + flags_for(src) + ['/Fo' + obj, os.path.join(ROOT, src)], env)
        if r.returncode:
            return None, r.stdout + r.stderr
        return obj, compile_sizes(src, d, env)
    import concurrent.futures
    with concurrent.futures.ThreadPoolExecutor(max_workers=max(1, int(os.environ.get('CD2_WORKERS', 2)))) as pool:
        builds = dict(zip(manifest['files'], pool.map(build, manifest['files'])))
    for src, funcs in manifest['files'].items():
        obj, sizes = builds[src]
        if obj is None:
            out('%s: COMPILE ERROR\n%s' % (src, sizes))
            total += len(funcs)
            continue
        compiled = list(coff.functions(obj))
        robj = relocs.Obj(obj, sizes)
        file_objs.append((src, robj))
        out(src)
        for f in funcs:
            va, size = int(f['address'], 16), f['size']
            named = [n for n, c, rel in compiled if symbol_matches(f['symbol'], n)]
            if named and f.get('matching', True):
                known[relocs.known_key(src, named[0], robj)] = va
            if f.get('ltcg') and not ltcg_built(src):  # a plain object has no LTCG build to be exact in
                total += f.get('matching', True)
                out('  %08X  %4d bytes  %-8s %s' % (va, size, 'INVALID', f['symbol'] + '   [marked "ltcg" in a plain '
                                                    'object: see ltcg_built()]'))
                continue
            if f.get('ltcg'):  # exact only under LTCG: checked by tools/verify_ltcg.py
                out('  %08X  %4d bytes  %-8s %s' % (va, size, 'LTCG', f['symbol'] + '   [checked by verify_ltcg.py]'))
                continue
            tracked = f.get('matching', True)  # matching: false = work in progress, reported but not required
            if tracked:
                total += 1
            found = [(n, c, rel) for n, c, rel in compiled if symbol_matches(f['symbol'], n)]
            if not found:
                out('  %08X  %4d bytes  symbol not found: %s' % (va, size, f['symbol']))
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
            out('  %08X  %4d bytes  %-8s %s%s' % (va, size, status, name, '' if tracked else '   [work in progress]'))
    words_of, tables = game_tables(read)
    nrefs = len(entries)
    reached, probs = relocs.check_all_data(
        entries, game_data_check(read), tables=tables,
        anchors=(file_objs, {k: v for k, v in known.items() if isinstance(k, str)}, words_of))
    return dict(ok=ok, total=total, pending=pending, nfuncs=nfuncs, nrefs=nrefs, entries=entries,
                problems=problems + probs, known=known, file_objs=file_objs, reached=reached)


if __name__ == '__main__':
    main()

