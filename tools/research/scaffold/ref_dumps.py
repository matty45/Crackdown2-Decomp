"""Reference type dumps for the classes of the automatically set-up files, one class at a time (maintainers only).

For every class in plan.json, `resymc dump -a -x` (the type only, as tools/headers/ref_dump.ps1 -NoDeps) from the
RuffKing PDB, or from Burn's when RuffKing lacks it, into include/ref/<pdb>/<Namespace_Class>.h. One resymc process at a
time, each loading one type: never `dump-all`, which loads every type of the PDB at once and can exhaust the memory.
Classes found in neither PDB are listed at the end. Existing dumps are kept.

usage: py -I tools/research/scaffold/ref_dumps.py <work dir> [--limit N]    (PDB paths from local.json, as ref_dump.ps1)
"""
import json, os, re, subprocess, sys, time

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', '..'))
RESYM = os.path.join(ROOT, 'build', 'tools', 'bin', 'resymc.exe')
LIMIT = 2 << 30  # a resymc process using more memory than this is stopped (one type needs well under 100 MB)


def working_set(handle):
    """The process's working set in bytes (Windows), or 0 when it cannot be read."""
    import ctypes
    from ctypes import wintypes

    class PMC(ctypes.Structure):
        _fields_ = [('cb', wintypes.DWORD), ('PageFaultCount', wintypes.DWORD)] + [
            (n, ctypes.c_size_t) for n in ('PeakWorkingSetSize', 'WorkingSetSize', 'QuotaPeakPagedPoolUsage',
                                           'QuotaPagedPoolUsage', 'QuotaPeakNonPagedPoolUsage',
                                           'QuotaNonPagedPoolUsage', 'PagefileUsage', 'PeakPagefileUsage')]
    c = PMC()
    c.cb = ctypes.sizeof(PMC)
    ok = ctypes.windll.psapi.GetProcessMemoryInfo(wintypes.HANDLE(int(handle)), ctypes.byref(c), c.cb)
    return max(c.WorkingSetSize, c.PagefileUsage) if ok else 0


def run_guarded(cmd):
    """Run cmd, stopping it if its memory exceeds LIMIT. Returns (exit code or 'too large', peak bytes)."""
    import time
    p = subprocess.Popen(cmd, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    peak = 0
    while p.poll() is None:
        peak = max(peak, working_set(p._handle))
        if peak > LIMIT:
            p.kill()
            p.wait()
            return 'too large', peak
        time.sleep(0.05)
    return p.returncode, peak


def main():
    S = sys.argv[1]
    limit = int(sys.argv[sys.argv.index('--limit') + 1]) if '--limit' in sys.argv else None
    local = json.load(open(os.path.join(ROOT, 'local.json')))
    pdbs = [('ruffking', os.environ.get('CD2_RUFFKING_PDB') or local.get('ruffking_pdb')),
            ('burn', os.environ.get('CD2_BURN_PDB') or local.get('burn_pdb'))]
    if not os.path.exists(RESYM):
        raise SystemExit('resymc.exe not built: powershell -File tools\\build_tools.ps1 resym')
    todo = []
    for p in json.load(open(os.path.join(S, 'plan.json'))):
        for c in p['classes']:
            ns = p['namespaces'][0] if len(p['namespaces']) == 1 else None
            todo.append((c, ns))
    todo = todo[:limit] if limit else todo
    missing, made, kept, big = [], 0, 0, []
    peak_all = 0
    t0 = time.time()
    for k, (cls, ns) in enumerate(todo, 1):
        names = ([ns + '::' + cls] if ns else []) + [cls]
        done = False
        for pdb_name, pdb in pdbs:
            for name in names:
                out = os.path.join(ROOT, 'include', 'ref', pdb_name, re.sub(r'[<>,* ]', '_', name.replace('::', '_')) + '.h')
                if os.path.exists(out):
                    kept += 1
                    done = True
                    break
                os.makedirs(os.path.dirname(out), exist_ok=True)
                code, peak = run_guarded([RESYM, 'dump', '-a', '-x', pdb, name, out])
                peak_all = max(peak_all, peak)
                if code == 'too large':
                    big.append(name)
                if code == 0 and os.path.exists(out) and os.path.getsize(out) > 0:
                    made += 1
                    done = True
                    break
                if os.path.exists(out) and os.path.getsize(out) == 0:
                    os.remove(out)
            if done:
                break
        if not done:
            missing.append(cls)
        print('%3d/%d %-40s %s  (%.0f s, peak so far %d MB)' % (
            k, len(todo), cls, 'ok' if done else 'not found', time.time() - t0, peak_all >> 20), flush=True)
    print('\n%d dumps made, %d already present, %d classes in neither PDB: %s' % (made, kept, len(missing),
                                                                             ', '.join(missing)))
    if big:
        print('stopped for using over %d MB: %s' % (LIMIT >> 20, ', '.join(big)))


if __name__ == '__main__':
    main()
