"""A cache of compiled objects, so that a gate recompiles only the sources whose inputs changed.

Only the repository's own sources (under src/) are cached. An object is reused only when everything the compiler read
is unchanged:
  key   the pinned toolchain (config/toolchain.txt: every gate refuses any other compiler), the command line without
        its /Fo output path, the INCLUDE path, the source's path and bytes, and the names of every header under
        include/ and src/ (and in the source's own folder): a header added or removed anywhere could be found first
        by some #include, so it invalidates every entry
  deps  the path and SHA-256 of every file the compiler opened (its /showIncludes list), checked again on each hit
Objects live in build/cd2/cache (ignored by git), at most CD2_CACHE_MB megabytes (default 2048; the least recently
used go first). CD2_NO_CACHE=1 turns the cache off for this process and the gates it starts: `cd2.py review` and
`cd2.py facts record` always run without it, so a judgement or a recorded fact never depends on a cached object.
"""
import hashlib, json, os, shutil, subprocess, threading, time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CACHE = os.path.join(ROOT, 'build', 'cd2', 'cache')  # the self-test points it elsewhere
INCLUDE_NOTE = 'Note: including file:'
HEADERS = ('.h', '.hpp', '.inl', '.hh')
_memo, _lock, _names = {}, threading.Lock(), {}
stats = dict(hits=0, misses=0)


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


def key(cmd, env):
    """The cache key of a compile command (its last argument is the source; one argument is /Fo<object>)"""
    src = cmd[-1]
    parts = dict(toolchain=open(os.path.join(ROOT, 'config', 'toolchain.txt'), 'rb').read().decode('latin-1'),
                 args=[a for a in cmd[1:-1] if not a.startswith('/Fo')], include=env.get('INCLUDE', ''),
                 source=os.path.abspath(src), source_sha=file_sha(src),
                 headers=[header_names(os.path.join(ROOT, 'include')), header_names(os.path.join(ROOT, 'src'))],
                 folder=folder_names(os.path.dirname(os.path.abspath(src))))
    return sha(json.dumps(parts, sort_keys=True).encode())


class Result:
    def __init__(self, returncode, stdout, stderr):
        self.returncode, self.stdout, self.stderr = returncode, stdout, stderr


def compile(cmd, env, run=None):
    """Run compile command cmd (cl.exe argv: /Fo<object>, the source last) through the cache. run(cmd, env=env) runs
    the compiler (default: subprocess.run with captured text output). Returns an object with returncode, stdout and
    stderr; on a hit the cached object is copied to the /Fo path and the output is empty."""
    run = run or (lambda c, env: subprocess.run(c, env=env, capture_output=True, text=True))
    if not enabled() or not os.path.abspath(cmd[-1]).startswith(os.path.join(ROOT, 'src') + os.sep):
        return run(cmd, env=env)  # only the repository's sources: a self-test's copy or a generated file runs uncached
    out = next(a[3:] for a in cmd if a.startswith('/Fo'))
    k = key(cmd, env)
    entry = os.path.join(CACHE, k[:2], k)
    try:
        with open(entry + '.json') as fh:
            deps = json.load(fh)['deps']
        if all(os.path.exists(p) and file_sha(p) == h for p, h in deps):
            shutil.copyfile(entry + '.obj', out)
            os.utime(entry + '.json')  # least recently used goes first
            with _lock:
                stats['hits'] += 1
            return Result(0, '', '')
    except (OSError, ValueError, KeyError):
        pass
    with _lock:
        stats['misses'] += 1
    r = run(cmd + ['/showIncludes'], env=env)
    lines = (r.stdout or '').splitlines(True)
    included = [l.split(INCLUDE_NOTE, 1)[1].strip() for l in lines if INCLUDE_NOTE in l]
    stdout = ''.join(l for l in lines if INCLUDE_NOTE not in l)
    if r.returncode == 0 and os.path.exists(out):
        try:
            deps = [[p, file_sha(p)] for p in sorted(set(included))]
            os.makedirs(os.path.dirname(entry), exist_ok=True)
            tmp = '%s.%d.%d' % (entry, os.getpid(), threading.get_ident())
            shutil.copyfile(out, tmp + '.obj')
            with open(tmp + '.json', 'w') as fh:
                json.dump(dict(deps=deps, source=cmd[-1]), fh)
            os.replace(tmp + '.obj', entry + '.obj')  # the object first: a .json always has its object
            os.replace(tmp + '.json', entry + '.json')
            prune()
        except OSError:
            pass
    return Result(r.returncode, stdout, r.stderr)


_last_prune = []


def prune(limit=None):
    """Keep the cache under CD2_CACHE_MB, dropping the least recently used entries (checked once a minute)"""
    now = time.time()
    with _lock:
        if _last_prune and now - _last_prune[0] < 60:
            return
        _last_prune[:] = [now]
    limit = limit if limit is not None else int(os.environ.get('CD2_CACHE_MB', 2048)) << 20
    entries, total = [], 0
    for dp, _, fs in os.walk(CACHE):
        for f in fs:
            if f.endswith('.json'):
                base = os.path.join(dp, f[:-5])
                try:
                    size = os.path.getsize(base + '.obj') + os.path.getsize(base + '.json')
                    entries.append((os.path.getmtime(base + '.json'), size, base))
                    total += size
                except OSError:
                    pass
    for _, size, base in sorted(entries):
        if total <= limit:
            break
        for ext in ('.json', '.obj'):
            try:
                os.remove(base + ext)
            except OSError:
                pass
        total -= size
