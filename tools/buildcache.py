"""A cache of compiled objects, so that a gate recompiles only the sources whose inputs changed.

Only the repository's own sources (under src/) are cached. An object is reused only when everything the compiler read
is unchanged:
  key   the pinned toolchain (config/toolchain.txt: every gate refuses any other compiler), the command line without
        its /Fo output path, the INCLUDE path and the compiler's own environment variables (CL, _CL_), the source's
        path and bytes, and the names of every header under include/ and src/ (and in the source's own folder): a
        header added or removed anywhere could be found first by some #include, so it invalidates every entry
  deps  the path and SHA-256 of every file the compiler opened (its /showIncludes list), checked again on each hit
The LTCG gate's link results (tools/verify_ltcg.py) and the source policy's results (`cd2.py lint`) are kept the same
way, each under its own key, through entry(), lookup() and store().
Entries live in build/cd2/cache (ignored by git), at most CD2_CACHE_MB megabytes (default 2048; the least recently
used go first, when a process that added entries exits). CD2_NO_CACHE=1 turns every cache off for this process and
the gates it starts: `cd2.py review` always runs without them, so a maintainer's judgement never depends on a cached
result.
"""
import atexit, hashlib, json, os, shutil, subprocess, threading

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CACHE = os.path.join(ROOT, 'build', 'cd2', 'cache')  # the self-test points it elsewhere
INCLUDE_NOTE = 'Note: including file:'
HEADERS = ('.h', '.hpp', '.inl', '.hh')
TOOL_ENV = ('CL', '_CL_', 'LINK', '_LINK_')  # options cl.exe and link.exe read from the environment
_memo, _lock, _names = {}, threading.Lock(), {}
stats = dict(hits=0, misses=0, ltcg_hits=0, ltcg_misses=0, lint_hits=0, lint_misses=0)


def count(what):
    with _lock:
        stats[what] += 1


def enabled():
    return os.environ.get('CD2_NO_CACHE') != '1'


def sha(b):
    return hashlib.sha256(b).hexdigest()


def file_sha(path):
    """SHA-256 of a file's bytes, remembered per process while its size and time stay the same"""
    st = os.stat(path)
    stamp = (st.st_mtime_ns, st.st_size)
    with _lock:
        hit = _memo.get(path)
    if hit and hit[0] == stamp:
        return hit[1]
    with open(path, 'rb') as fh:
        h = sha(fh.read())
    with _lock:
        _memo[path] = (stamp, h)
    return h


def header_names(directory):
    """SHA-256 of the sorted header file names below directory (once per process)"""
    with _lock:
        if directory in _names:
            return _names[directory]
    names = sorted(os.path.relpath(os.path.join(dp, f), directory) for dp, _, fs in os.walk(directory)
                   for f in fs if f.lower().endswith(HEADERS))
    h = sha('\n'.join(names).encode())
    with _lock:
        _names[directory] = h
    return h


def folder_names(directory):
    """SHA-256 of the names in one folder (not below it)"""
    try:
        return sha('\n'.join(sorted(os.listdir(directory))).encode())
    except OSError:
        return ''


def common(env, folder):
    """The key parts every cached result shares: the toolchain, the include path, the tools' options from the
    environment, and the header names a #include could find (folder: the source's own folder)"""
    return dict(toolchain=open(os.path.join(ROOT, 'config', 'toolchain.txt'), 'rb').read().decode('latin-1'),
                include=env.get('INCLUDE', ''), tool_env=[env.get(k) for k in TOOL_ENV],
                headers=[header_names(os.path.join(ROOT, 'include')), header_names(os.path.join(ROOT, 'src'))],
                folder=folder_names(folder))


def digest(parts):
    return sha(json.dumps(parts, sort_keys=True).encode())


def key(cmd, env):
    """The cache key of a compile command (its last argument is the source; one argument is /Fo<object>)"""
    src = cmd[-1]
    return digest(dict(common(env, os.path.dirname(os.path.abspath(src))), args=[a for a in cmd[1:-1] if not a.startswith('/Fo')],
                       source=os.path.abspath(src), source_sha=file_sha(src)))


def cacheable(path):
    """Whether results for this source may be cached: the cache is on, and the source is a repository file under src/
    (a self-test's copy or a generated file is never cached)"""
    return enabled() and os.path.abspath(path).startswith(os.path.join(ROOT, 'src') + os.sep)


def entry(kind, k):
    """The base path (without extension) of the entry of key k; kind: '' (objects), 'ltcg' or 'lint'"""
    return os.path.join(CACHE, kind, k[:2], k)


def lookup(base):
    """The record of an entry (its .json) when every file it depends on is unchanged, else None. A hit marks the entry
    as recently used."""
    try:
        with open(base + '.json') as fh:
            rec = json.load(fh)
        if all(os.path.exists(p) and file_sha(p) == h for p, h in rec['deps']):
            os.utime(base + '.json')  # least recently used goes first
            return rec
    except (OSError, ValueError, KeyError, TypeError):
        pass
    return None


def restore(base, outputs):
    """Copy an entry's files out of the cache (outputs: {extension: destination}); False if one is gone"""
    try:
        for ext, path in outputs.items():
            shutil.copyfile(base + ext, path)
        return True
    except OSError:
        return False


def deps_of(paths):
    """[[path, SHA-256]] of the files a result depends on"""
    return [[p, file_sha(p)] for p in sorted(set(paths))]


def store(base, files, rec):
    """Store an entry: files ({extension: path of the file to keep}) and rec (a dict with 'deps', written as the .json).
    The files are moved into place before the record, so that a record always has its files."""
    try:
        os.makedirs(os.path.dirname(base), exist_ok=True)
        tmp = '%s.%d.%d' % (base, os.getpid(), threading.get_ident())
        for ext, path in files.items():
            shutil.copyfile(path, tmp + ext)
        with open(tmp + '.json', 'w') as fh:
            json.dump(rec, fh)
        for ext in files:
            os.replace(tmp + ext, base + ext)
        os.replace(tmp + '.json', base + '.json')
        _added()
    except OSError:
        pass


class Result:
    def __init__(self, returncode, stdout, stderr):
        self.returncode, self.stdout, self.stderr = returncode, stdout, stderr


def compile(cmd, env, run=None):
    """Run compile command cmd (cl.exe argv: /Fo<object>, the source last) through the cache. run(cmd, env=env) runs
    the compiler (default: subprocess.run with captured text output). Returns an object with returncode, stdout and
    stderr; on a hit the cached object is copied to the /Fo path and the output is empty."""
    run = run or (lambda c, env: subprocess.run(c, env=env, capture_output=True, text=True))
    if not cacheable(cmd[-1]):
        return run(cmd, env=env)
    out = next(a[3:] for a in cmd if a.startswith('/Fo'))
    base = entry('', key(cmd, env))
    if lookup(base) is not None and restore(base, {'.obj': out}):
        count('hits')
        return Result(0, '', '')
    count('misses')
    r = run(cmd + ['/showIncludes'], env=env)
    included, stdout = split_includes(r.stdout)
    if r.returncode == 0 and os.path.exists(out):
        store(base, {'.obj': out}, dict(deps=deps_of(included), source=cmd[-1]))
    return Result(r.returncode, stdout, r.stderr)


def split_includes(stdout):
    """(the files a /showIncludes compile opened, its output without those notes)"""
    lines = (stdout or '').splitlines(True)
    return ([l.split(INCLUDE_NOTE, 1)[1].strip() for l in lines if INCLUDE_NOTE in l],
            ''.join(l for l in lines if INCLUDE_NOTE not in l))


_pruning = []


def _added():
    """An entry was added: keep the cache in its budget when this process exits (once per process)"""
    with _lock:
        if not _pruning:
            _pruning.append(True)
            atexit.register(prune)


def prune(limit=None):
    """Keep the cache under CD2_CACHE_MB, dropping the least recently used entries: a record's time is its use (each
    hit touches it); files without a record (a store a killed process left behind) go by their own time. Sizes and
    times come from the directory listings (os.scandir, which on Windows needs no call per file)."""
    limit = limit if limit is not None else int(os.environ.get('CD2_CACHE_MB', 2048)) << 20
    groups, total = {}, 0  # base path -> [time, size, files]

    def walk(d):
        nonlocal total
        try:
            listing = os.scandir(d)
        except OSError:
            return
        with listing:
            for e in listing:
                try:
                    if e.is_dir(follow_symlinks=False):
                        walk(e.path)
                        continue
                    st = e.stat(follow_symlinks=False)
                except OSError:
                    continue
                base, ext = os.path.splitext(e.path)
                g = groups.setdefault(base, [None, 0, [], 0.0])
                g[1] += st.st_size
                g[2].append(e.path)
                g[3] = max(g[3], st.st_mtime)
                if ext == '.json':
                    g[0] = st.st_mtime
                total += st.st_size
    walk(CACHE)
    if total <= limit:
        return
    for when, size, files, newest in sorted(groups.values(), key=lambda g: g[0] if g[0] is not None else g[3]):
        if total <= limit:
            break
        for f in sorted(files, key=lambda f: not f.endswith('.json')):  # the record first: never a record without files
            try:
                os.remove(f)
            except OSError:
                pass
        total -= size
