"""cd2: the contributor tool for the Crackdown 2 decompilation. One entry point for any person or agent.

usage: py -I tools/cd2.py <command> [arguments] [--json]

  config --xdk <dir> [--ruffking-pdb P] [--burn-pdb P] [--bench-dir D]
                                 one time: where the extracted XDK 9328 is (written to local.json, ignored by git);
                                 the PDB options are for maintainers' tools/headers/ref_dump.ps1 only; --bench-dir
                                 moves the benchmark workspaces (default %LOCALAPPDATA%\\cd2-bench; never in the repo)
  setup <default_patched.xex>    one time: verify the XEX, extract the exe, split it into one target object per source
                                 file (jeff), all under build/cd2 (ignored by git)
  doctor                         check the environment: pinned compiler, extracted exe, split, built tools
  status                         per source file: functions in its range, matched, LTCG-only, in progress, open
  tasks [file] [--tier N]        open functions of the scaffolded files, easiest first
  show <address>                 a task brief: file, size, difficulty, status, neighbours, hints, CD2's assembly
  claim <address> <symbol>       start a task: map the function to the symbol you write for it (local, untracked)
  unclaim <address>              drop a claim
  check <file.cpp> [--ltcg] [--explain]
                                 the edit loop: source policy, compile, compare every function of the file mapped by
                                 config/matched_functions.json or a claim, verify relocation targets; logs the attempt;
                                 --explain adds the mismatch classifier's findings for each function not yet exact
  diff <file.cpp> <address>      instruction diff of one function against CD2 (objdiff), differing regions only, with
                                 the mismatch classifier's findings and hints (tools/mismatch.py)
  search <file.cpp> <address> [--apply] [--rounds N] [--budget N] [--jobs N]
                                 try source transformations (operand order, if/else arms, statement order, ...) and
                                 keep those that bring the function closer to CD2 (tools/search.py)
  search-test [--limit N]        break solved functions with one transformation each; the search must restore them
  bench list|suite|prepare|check|score|run|report|selftest [address] [--model M] [--agent A] [--tier N] [--limit N]
        [--resume]
                                 the benchmark: re-solve solved functions in isolated workspaces (tools/bench.py).
                                 `bench run --model NAME --agent A` runs an agent over the suite; A is
                                 chat:<model> (any model behind an OpenAI-compatible API, tools/bench_chat.py),
                                 claude:<model> or kilo:<provider/model> (those CLIs, sandboxed), or the command of
                                 any other agent. IDE agents: `bench prepare --model NAME` (the whole suite), work
                                 through the workspaces, then `bench score --model NAME`. An agent that exits with an
                                 error without working is an agent error, not scored; 3 in a row stop the run, and
                                 --resume re-runs only the tasks without a genuine result
  lint [file.cpp ...]            the source policy on the preprocessed source (default: every file in src/)
  verify [--facts]               every gate; exit status 0 only if all pass. --facts needs no game file: the facts
                                 recorded in config/target_facts.json stand in for it
  facts record                   record those facts from your copy of the game (after adding matches to the manifest)
  review <branch> [--record-facts]
                                 maintainers, before merging a contribution: verify it with this checkout's tools and
                                 config (only its changes to src/, include/, the manifest and the notes are applied),
                                 list its changes anywhere else, then restore the checkout

--json prints one JSON object instead of text, for agents and scripts.

Nothing a contributor writes decides what counts as matched: check and verify compare by symbol against your own
extracted copy of the game, with the pinned compiler (config/toolchain.txt) and the maintainers' symbol table
(config/matched_functions.json). docs/contributor-harness.md explains the workflow and the rules.
"""
import argparse, collections, datetime, hashlib, json, os, re, shutil, struct, subprocess, sys, tempfile

TOOLS = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, TOOLS)
import coff  # noqa: E402
import relocs  # noqa: E402
import mismatch  # noqa: E402
import search as srch  # noqa: E402
import bench  # noqa: E402
import verify_ltcg  # noqa: E402
from verify_src import (ROOT, XDK, BIN, FLAGS, EXPECTED_ENTRY, CODE_SECTIONS, pe_reader, toolchain_problems,  # noqa: E402
                        local_config, run_compiler)
from check_integrity import load_splits  # noqa: E402

XEX_SHA1 = 'EC7B163617CD725F50B0CCA665AAF943F9BC6D8A'
WORK = os.path.join(ROOT, 'build', 'cd2')
EXE = os.path.join(WORK, 'orig', 'default_patched.exe')
JEFF = os.path.join(ROOT, 'build', 'tools', 'bin', 'jeff.exe')
OBJDIFF = os.path.join(ROOT, 'build', 'tools', 'bin', 'objdiff-cli.exe')
MANIFEST = os.path.join(ROOT, 'config', 'matched_functions.json')
SPLITS = os.path.join(ROOT, 'config', 'splits.txt')
ALIASES = os.path.join(ROOT, 'config', 'symbol_aliases.txt')
CLAIMS = os.path.join(WORK, 'claims.json')
ATTEMPTS = os.path.join(WORK, 'attempts.jsonl')
JEFF_SECTIONS = [('.rdata', 'rodata'), ('.pdata', 'rodata'), ('.text', 'code'), ('PSFD00', 'code'), ('.data', 'data'),
                 ('.tls', 'data'), ('.XBMOVIE', 'data'), ('.edata', 'rodata'), ('.idata', 'data'), ('.XBLD', 'data'),
                 ('.reloc', 'data')]


class Fail(Exception):
    pass


_proc = None


def scratch(*parts):
    """A scratch path private to this process (build/cd2/tmp/<pid>/...), removed when it exits: several cd2.py
    processes (a benchmark, an agent's check, a verify) may run at once and must never share a working file. Folders
    left by processes that were killed are removed after a day."""
    global _proc
    if _proc is None:
        import atexit, time
        base = os.path.join(WORK, 'tmp')
        os.makedirs(base, exist_ok=True)
        for d in os.listdir(base):
            p = os.path.join(base, d)
            try:
                if time.time() - os.path.getmtime(p) > 86400:
                    shutil.rmtree(p, ignore_errors=True)
            except OSError:
                pass
        _proc = tempfile.mkdtemp(prefix='%d_' % os.getpid(), dir=base)
        atexit.register(shutil.rmtree, _proc, True)
    p = os.path.join(_proc, *parts)
    os.makedirs(os.path.dirname(p), exist_ok=True)
    return p


def scratch_dir(*parts):
    """A directory private to this process (see scratch)."""
    d = scratch(*parts)
    os.makedirs(d, exist_ok=True)
    return d


def env():
    return dict(os.environ, PATH=BIN + ';' + os.environ['PATH'],
                INCLUDE=os.path.join(XDK, 'include', 'xbox') + ';' + os.path.join(ROOT, 'include'))


def rel(path):
    """A path relative to the repository, or absolute when it is outside (e.g. a benchmark workspace)."""
    p = os.path.abspath(path)
    try:
        inside = os.path.commonpath([os.path.normcase(p), os.path.normcase(ROOT)]) == os.path.normcase(ROOT)
    except ValueError:  # another drive
        inside = False
    return (os.path.relpath(p, ROOT) if inside else p).replace('\\', '/')


def need_toolchain():
    problems = toolchain_problems()
    if problems:
        raise Fail('wrong toolchain (set XDK_DIR to the extracted XDK 9328):\n  ' + '\n  '.join(problems))


def need_setup():
    if not os.path.exists(os.path.join(WORK, 'symbols.txt')) or not os.path.exists(os.path.join(WORK, 'split', 'obj')):
        raise Fail('not set up: run  py -I tools/cd2.py setup <path to default_patched.xex>')


# ---------------------------------------------------------------------------------------------------- game data

_reader = None


def read(va, n):
    global _reader
    if _reader is None:
        if not os.path.exists(EXE):
            raise Fail('no extracted exe: run  py -I tools/cd2.py setup <path to default_patched.xex>')
        r, entry = pe_reader(open(EXE, 'rb').read())
        if entry != EXPECTED_ENTRY:
            raise Fail('%s is not the title-update build' % EXE)
        _reader = r
    return _reader(va, n)


def jeff_symbols():
    """{address: (name, size)} of the functions jeff found (build/cd2/symbols.txt)."""
    out = {}
    pat = re.compile(r'^(\S+) = \.text:0x([0-9A-Fa-f]+); // type:function size:0x([0-9A-Fa-f]+)')
    for line in open(os.path.join(WORK, 'symbols.txt')):
        m = pat.match(line)
        if m:
            out[int(m.group(2), 16)] = (m.group(1), int(m.group(3), 16))
    return out


def manifest():
    return json.load(open(MANIFEST))


def claims():
    return json.load(open(CLAIMS)) if os.path.exists(CLAIMS) else {}


def file_functions(splits, syms):
    """{file: [address, ...]} of every function a file owns: its text range, plus hot, init and atexit functions."""
    import bisect
    starts = sorted(syms)
    out = {}
    for f, e in splits.items():
        addrs = set(e['hot'] + e['init'] + e['atexit'])
        if e['text']:
            addrs.update(starts[bisect.bisect_left(starts, e['text'][0]):bisect.bisect_left(starts, e['text'][1])])
        out[f] = sorted(addrs)
    return out


def owner(addr, splits):
    for f, e in splits.items():
        if (e['text'] and e['text'][0] <= addr < e['text'][1]) or addr in e['hot'] + e['init'] + e['atexit']:
            return f
    return None


def mapped(file, man=None, cl=None):
    """The functions of a file with a symbol: manifest entries, then local claims. [{address, size, symbol, ...}]"""
    man = man or manifest()
    out = [dict(f, source='manifest') for f in man['files'].get(file, [])]
    known = {int(f['address'], 16) for f in out}
    for a, c in sorted((cl if cl is not None else claims()).items()):
        if c['file'] == file and int(a, 16) not in known:
            out.append(dict(address=a, size=c['size'], symbol=c['symbol'], matching=False, source='claim'))
    return out


# ---------------------------------------------------------------------------------------------------- difficulty

def _sx(v, bits):
    return v - (1 << bits) if v & (1 << (bits - 1)) else v


def features(code):
    ws = struct.unpack('>%dI' % (len(code) // 4), code[:len(code) // 4 * 4])
    back = 0
    for i, w in enumerate(ws):
        op = w >> 26
        if op == 16 and not w & 2 and _sx(w & 0xFFFC, 16) < 0:
            back += 1
        elif op == 18 and not w & 3 and _sx(w & 0x3FFFFFC, 26) < 0:
            back += 1
    return dict(instructions=len(ws),
                calls=sum(1 for w in ws if w >> 26 == 18 and w & 1),
                float_ops=sum(1 for w in ws if w >> 26 in (48, 49, 50, 51, 52, 53, 54, 55, 59, 63)),
                vmx=sum(1 for w in ws if w >> 26 in (4, 5, 6)),
                # a jump table loads its target with an indexed load (lwzx) right before mtctr/bctr; a bctr alone may
                # be a virtual tail call
                jump_table=any(w == 0x4E800420 and any(x >> 26 == 31 and (x >> 1) & 0x3FF == 23 for x in ws[max(0, i - 4):i])
                               for i, w in enumerate(ws)),
                loops=back)


def anchored_float_loads(code):
    """lfs/lfd at a displacement from a register set to an address in .rdata (lis + addi): how LTCG loads the float
    constants it gathered. A plain build loads each constant from its own address instead (lis + lfs)."""
    ws = struct.unpack('>%dI' % (len(code) // 4), code[:len(code) // 4 * 4])
    high, anchors, n = {}, set(), 0
    for w in ws:
        op, rd, ra, lo = w >> 26, (w >> 21) & 31, (w >> 16) & 31, _sx(w & 0xFFFF, 16)
        if op in (48, 50) and ra in anchors:  # lfs/lfd f, d(anchor)
            n += 1
        elif op == 15 and ra == 0:  # lis rD, hi
            high[rd] = (w & 0xFFFF) << 16
            anchors.discard(rd)
        elif op == 14:  # addi rD, rA, lo (li when rA is 0): an address when rA holds a high half
            if ra and ra in high and verify_ltcg.RDATA[0] <= (high[ra] + lo) & 0xFFFFFFFF < verify_ltcg.RDATA[1]:
                anchors.add(rd)
            else:
                anchors.discard(rd)
            if rd != ra:
                high.pop(rd, None)
        elif op in (32, 33, 34, 35, 40, 41, 42, 43):  # integer loads overwrite rD
            anchors.discard(rd)
            high.pop(rd, None)
        elif op == 31 and (w >> 1) & 0x3FF == 444:  # or rA, rS, rB (mr): overwrites rA
            anchors.discard(ra)
            high.pop(ra, None)
    return n


def tier(ft):
    """1 = small and straight (anyone), 2 = medium, 3 = large or a jump table, 4 = very large or VMX (experts)."""
    n = ft['instructions']
    t = 1 if n <= 24 else 2 if n <= 80 else 3 if n <= 250 else 4
    if ft['jump_table']:
        t = max(t, 3)
    if ft['vmx']:
        t = 4
    return t


# ---------------------------------------------------------------------------------------------------- source policy

POLICY_ERRORS = [
    (re.compile(r'\b_{0,2}asm\b'), 'inline assembly'),
    (re.compile(r'\b__emit\b'), '__emit (raw machine code)'),
    (re.compile(r'__declspec\s*\(\s*(naked|allocate)\b'), '__declspec(naked/allocate)'),
    (re.compile(r'\b__pragma\b'), '__pragma'),
]
PRAGMA_ALLOWED = ('pack', 'warning', 'once')


def policy(src, extra_roots=(), roots=None, include=None):
    """(errors, warnings) of the source policy for one file. Checked on the preprocessed source, so macros cannot hide
    anything; only lines that come from this repository count, and every included file must come from the repository
    or the XDK. extra_roots: more directories that count as the repository (for the self-test). roots and include
    replace the repository's src/ and include/ (a benchmark workspace counts only itself)."""
    errors, warnings = [], []
    path = os.path.join(ROOT, src)
    for n, line in enumerate(open(path, errors='replace'), 1):
        if re.match(r'\s*#\s*line\b', line):
            errors.append('%s:%d: #line directive (would disguise where code comes from)' % (src, n))
    # this compiler has no /Fi: /P writes <name>.i to the current directory, a fresh one per call (no file is reused, so
    # nothing still held by another process from an earlier call gets in the way)
    pp = tempfile.mkdtemp(prefix='pp_', dir=scratch_dir('pp'))
    e = env()
    if include is not None:
        e['INCLUDE'] = ';'.join([os.path.join(XDK, 'include', 'xbox')] + list(include))
    try:
        r = run_compiler([os.path.join(BIN, 'cl.exe')] + FLAGS + ['/P', '/I' + os.path.dirname(path), path], env=e, cwd=pp)
        if r.returncode:
            return ['%s: preprocessor error\n%s' % (src, (r.stdout + r.stderr)[-2000:])], warnings
        preprocessed = open(os.path.join(pp, os.path.splitext(os.path.basename(src))[0] + '.i'), errors='replace').readlines()
    finally:
        shutil.rmtree(pp, ignore_errors=True)
    if roots is None:
        roots = [os.path.join(ROOT, 'src'), os.path.join(ROOT, 'include')]
    roots = [os.path.normcase(os.path.abspath(r)) for r in list(roots) + list(extra_roots)]
    ref = os.path.normcase(os.path.join(ROOT, 'include', 'ref'))
    xdk = os.path.normcase(XDK)
    origin, lineno, ours = path, 0, True
    seen_outside = set()
    for line in preprocessed:
        m = re.match(r'#line (\d+) "(.*)"', line)
        if m:
            lineno, origin = int(m.group(1)) - 1, os.path.normcase(os.path.abspath(m.group(2).replace('\\\\', '\\')))
            ours = any(origin.startswith(p) for p in roots) and not origin.startswith(ref)
            if not ours and not origin.startswith(xdk) and origin not in seen_outside:
                seen_outside.add(origin)
                errors.append('%s: includes %s, which is neither in the repository nor in the XDK' % (src, origin))
            continue
        lineno += 1
        if not ours:
            continue
        where = '%s:%d' % (rel(origin), lineno)
        text = line.split('//', 1)[0]
        for pat, what in POLICY_ERRORS:
            if pat.search(text):
                errors.append('%s: %s' % (where, what))
        pm = re.match(r'\s*#\s*pragma\s+(\w+)', text)
        if pm and pm.group(1) not in PRAGMA_ALLOWED:
            errors.append('%s: #pragma %s (allowed: %s)' % (where, pm.group(1), ', '.join(PRAGMA_ALLOWED)))
        if re.search(r'\bgoto\b', text):
            warnings.append('%s: goto (needs review: rarely what the original source did)' % where)
    return errors, warnings


# ---------------------------------------------------------------------------------------------------- compile/compare

def compile_file(src):
    obj = scratch('obj', os.path.basename(src) + '.obj')
    os.makedirs(os.path.dirname(obj), exist_ok=True)
    r = subprocess.run([os.path.join(BIN, 'cl.exe')] + FLAGS + ['/Fo' + obj, os.path.join(ROOT, src)],
                       env=env(), capture_output=True, text=True)
    if r.returncode:
        raise Fail('%s: compile error\n%s' % (src, (r.stdout + r.stderr)[-3000:]))
    return obj


def compare_file(src, funcs, ltcg=False):
    """Compare each mapped function of src with CD2. Returns (results, problems)."""
    obj = compile_file(src)
    compiled = list(coff.functions(obj))
    robj = relocs.Obj(obj)
    results, entries, problems = [], [], []
    man = manifest()
    known = {}
    lt = None
    if ltcg:
        consts = verify_ltcg.direct_constants(read, funcs)
        d = scratch_dir('ltcg', os.path.basename(src))
        try:
            lt = verify_ltcg.build_ltcg(os.path.join(ROOT, src), obj, consts, d, env(),
                                        deps=verify_ltcg.dependencies(src, obj, d, env(), man))
        except RuntimeError as e:
            raise Fail('%s: %s' % (src, str(e)[-3000:]))
    for f in funcs:
        va, size = int(f['address'], 16), f['size']
        target = read(va, size)
        res = dict(address='0x%08X' % va, size=size, symbol=f['symbol'], source=f.get('source', 'manifest'),
                   tracked=f.get('matching', True) and f.get('source') == 'manifest', ltcg_only=bool(f.get('ltcg')))
        found = [(n, c, r) for n, c, r in compiled if f['symbol'] in n]
        if not found:
            res.update(status='missing', plain=0.0)
            results.append(res)
            continue
        name, code, rl = found[0]
        res['name'] = name
        exact, ratio = coff.compare(code, target, rl)
        res['plain'] = round(100 * ratio, 1)
        res['plain_exact'] = exact
        if lt:
            c = verify_ltcg.compare_ltcg(lt[0], lt[1], f['symbol'], target, va, getattr(rl, 'absolute', ()))
            res['ltcg_exact'] = bool(c and c[0])
            res['ltcg'] = '%d/%d words' % (c[1], c[2]) if c else 'not in image'
        if exact:
            sec = robj.functions()[name][0]
            if robj.sections[sec - 1]['name'] not in CODE_SECTIONS:
                problems.append('%s is in section %s, not an ordinary code section' % (name, robj.sections[sec - 1]['name']))
            rs, probs = relocs.resolve(robj, name, target, va)
            entries += [(src, name, s, a, k, o, robj) for s, a, k, o in rs]
            problems += probs
            known[name] = va
        if exact:
            res['status'] = 'EXACT'
        elif res.get('ltcg_exact'):
            res['status'] = 'LTCG EXACT'
        elif res['ltcg_only'] and not ltcg:
            res['status'] = 'needs --ltcg'
        else:
            res['status'] = '%.1f%%' % res['plain']
        results.append(res)
    for g in man['files'].values():  # names other files' matched functions stand for
        for e in g:
            if e.get('matching', True):
                for n, _, _ in compiled:
                    if e['symbol'] in n:
                        known.setdefault(n, int(e['address'], 16))
    problems += relocs.check_consistency(entries, read, relocs.load_aliases(ALIASES), known)
    for res in results:  # problem texts name the function by its first 40 characters
        if res['status'] == 'EXACT' and any(res['name'][:40] in p for p in problems):
            res['status'] = 'WRONG TARGET'
    return results, problems


def log_attempt(command, src, results):
    os.makedirs(WORK, exist_ok=True)
    with open(ATTEMPTS, 'a') as fh:
        fh.write(json.dumps(dict(time=datetime.datetime.now().isoformat(timespec='seconds'), command=command, file=src,
                                 results={r['address']: r['status'] for r in results})) + '\n')


# ---------------------------------------------------------------------------------------------------- commands

def labels_inside_code(obj_path):
    """Turn every non-function symbol in a code section of a target object into a label (storage class LABEL).
    objdiff infers a COFF function's size from the next function or data symbol, so a jump table or an internal label
    that jeff writes as data would cut the function short in diffs. These objects are only diffed, never linked, so
    the labels need not be visible to other objects."""
    d = bytearray(open(obj_path, 'rb').read())
    nsec, symptr, nsym, opt = struct.unpack_from('<H', d, 2)[0], *struct.unpack_from('<II', d, 8), struct.unpack_from('<H', d, 16)[0]
    code = {i + 1 for i in range(nsec) if struct.unpack_from('<I', d, 20 + opt + 40 * i + 36)[0] & 0x20}
    n, i = 0, 0
    while i < nsym:
        o = symptr + 18 * i
        sec, typ, cls, naux = struct.unpack_from('<hHBB', d, o + 12)
        if sec in code and cls in (2, 3) and naux == 0 and typ & 0x30 != 0x20:
            struct.pack_into('<HB', d, o + 14, 0, 6)
            n += 1
        i += 1 + naux
    open(obj_path, 'wb').write(bytes(d))
    return n


def cmd_setup(a):
    need_toolchain()
    if not os.path.exists(JEFF):
        raise Fail('jeff is not built: powershell -File tools\\build_tools.ps1 jeff')
    if hashlib.sha1(open(a.xex, 'rb').read()).hexdigest().upper() != XEX_SHA1:
        raise Fail('%s is not the title-update default_patched.xex (SHA1 %s); refusing' % (a.xex, XEX_SHA1))
    orig = os.path.join(WORK, 'orig')
    os.makedirs(orig, exist_ok=True)
    xex = os.path.join(orig, 'default_patched.xex')
    if not os.path.exists(xex):
        shutil.copy(a.xex, xex)
    if not os.path.exists(EXE):
        subprocess.run([JEFF, 'xex', 'extract', xex], cwd=orig, check=True, capture_output=True)
        made = [f for f in os.listdir(orig) if f.endswith('.exe') and f != os.path.basename(EXE)]
        os.replace(os.path.join(orig, made[0]), EXE)
    read(EXPECTED_ENTRY, 4)
    header = ['Sections:'] + ['\t%-11s type:%s align:65536' % s for s in JEFF_SECTIONS] + ['']

    def split(name, units, symbols_in):
        d = os.path.join(WORK, name)
        if os.path.exists(d):
            shutil.rmtree(d)
        open(os.path.join(WORK, name + '_splits.txt'), 'w').write('\n'.join(header + units))
        open(os.path.join(WORK, name + '.yml'), 'w').write('object: orig/default_patched.xex\nsplits: %s_splits.txt\n'
                                                          'symbols: %s\n' % (name, symbols_in))
        print('jeff: %s split...' % name, flush=True)
        r = subprocess.run([JEFF, 'xex', 'split', name + '.yml', name], cwd=WORK, capture_output=True, text=True)
        open(os.path.join(WORK, name + '.log'), 'w').write(r.stdout + r.stderr)
        if r.returncode:
            raise Fail('jeff %s split failed; see %s' % (name, os.path.join(WORK, name + '.log')))
    # pass 1: jeff's analysis gives every function's size (symbols.txt is read and written back)
    open(os.path.join(WORK, 'symbols.txt'), 'w').write('')
    split('analysis', [], 'symbols.txt')
    shutil.rmtree(os.path.join(WORK, 'analysis'), ignore_errors=True)
    syms = jeff_symbols()
    # pass 2: one unit per source file (its text range) and one per extra function (hot, init, atexit), see unit_of
    units = []
    for f, e in load_splits(SPLITS).items():
        if e['text']:
            units += ['%s:' % f, '\t.text       start:0x%08X end:0x%08X' % e['text'], '']
        for addr in e['hot'] + e['init'] + e['atexit']:
            if addr not in syms:
                raise Fail('%s: no function at %08X in jeff\'s analysis' % (f, addr))
            units += ['%s_%08X.cpp:' % (f[:-4], addr), '\t.text       start:0x%08X end:0x%08X' % (addr, addr + syms[addr][1]), '']
    split('split', units, 'symbols.txt')
    for dp, _, fs in os.walk(os.path.join(WORK, 'split', 'obj', 'src')):
        for f in fs:
            if f.endswith('.obj'):
                labels_inside_code(os.path.join(dp, f))
    return dict(ok=True, workdir=rel(WORK), functions=len(syms))


def cmd_config(a):
    """Machine-specific settings in local.json (ignored by git): the XDK, and optionally the reference PDBs."""
    path = os.path.join(ROOT, 'local.json')
    cfg = local_config()
    for key, val in (('xdk', a.xdk), ('ruffking_pdb', a.ruffking_pdb), ('burn_pdb', a.burn_pdb)):
        if val:
            if not os.path.exists(val):
                raise Fail('%s does not exist' % val)
            cfg[key] = os.path.abspath(val)
    if a.xdk and not os.path.exists(os.path.join(a.xdk, 'bin', 'win32', 'cl.exe')):
        raise Fail('%s has no bin\\win32\\cl.exe: give the extracted XDK 9328 directory' % a.xdk)
    if a.bench_dir:  # need not exist yet; must be outside the repository (the agents would sit next to the solutions)
        bench.BENCH = os.path.abspath(a.bench_dir)
        if bench.location_problem():
            raise Fail(bench.location_problem())
        cfg['bench_dir'] = bench.BENCH
    if a.xdk or a.ruffking_pdb or a.burn_pdb or a.bench_dir:
        json.dump(cfg, open(path, 'w'), indent=1)
    return dict(ok=True, file=rel(path), settings=cfg)


def cmd_doctor(a):
    checks = []

    def add(name, ok, detail):
        checks.append(dict(check=name, ok=bool(ok), detail=detail))
    add('python', sys.version_info >= (3, 8), sys.version.split()[0])
    tp = toolchain_problems() if os.path.isdir(BIN) else ['XDK not configured: cd2.py config --xdk <extracted XDK 9328 directory>' if not XDK else 'XDK not found at %s' % XDK]
    add('toolchain', not tp, 'pinned (config/toolchain.txt)' if not tp else '; '.join(tp))
    add('jeff', os.path.exists(JEFF), rel(JEFF) if os.path.exists(JEFF) else 'not built: tools/build_tools.ps1 jeff')
    add('objdiff-cli', os.path.exists(OBJDIFF), rel(OBJDIFF) if os.path.exists(OBJDIFF) else 'not built: tools/build_tools.ps1 objdiff')
    ok_exe = os.path.exists(EXE) and pe_reader(open(EXE, 'rb').read())[1] == EXPECTED_ENTRY
    add('game', ok_exe, rel(EXE) if ok_exe else 'run: cd2.py setup <default_patched.xex>')
    ok_split = os.path.exists(os.path.join(WORK, 'split', 'obj'))
    add('split', ok_split, 'target objects in build/cd2/split' if ok_split else 'run: cd2.py setup <default_patched.xex>')
    return dict(ok=all(c['ok'] for c in checks), checks=checks)


def cmd_status(a):
    need_setup()
    splits, syms, man, cl = load_splits(SPLITS), jeff_symbols(), manifest(), claims()
    rows = []
    for f, addrs in file_functions(splits, syms).items():
        entries = {int(e['address'], 16): e for e in man['files'].get(f, [])}
        exact = sum(1 for e in entries.values() if e.get('matching', True) and not e.get('ltcg'))
        ltcg = sum(1 for e in entries.values() if e.get('matching', True) and e.get('ltcg'))
        wip = sum(1 for e in entries.values() if not e.get('matching', True))
        in_range = [x for x in addrs if x not in entries]
        claimed = sum(1 for x in in_range if '0x%08X' % x in cl)
        rows.append(dict(file=f, functions=len(set(addrs) | set(entries)), exact=exact, ltcg_only=ltcg, in_progress=wip,
                         claimed=claimed, open=len(in_range) - claimed))
    tot = {k: sum(r[k] for r in rows) for k in ('functions', 'exact', 'ltcg_only', 'in_progress', 'claimed', 'open')}
    return dict(ok=True, files=rows, total=tot,
                note='matched counts are as recorded in config/matched_functions.json; `verify` recomputes them')


def open_tasks(file_filter=None):
    splits, syms, man, cl = load_splits(SPLITS), jeff_symbols(), manifest(), claims()
    out = []
    for f, addrs in file_functions(splits, syms).items():
        if file_filter and file_filter not in f:
            continue
        entries = {int(e['address'], 16): e for e in man['files'].get(f, [])}
        for addr in addrs:
            e = entries.get(addr)
            if e and e.get('matching', True):
                continue
            size = e['size'] if e else syms[addr][1]
            ft = features(read(addr, size))
            c = cl.get('0x%08X' % addr)
            out.append(dict(address='0x%08X' % addr, size=size, file=f, tier=tier(ft), features=ft,
                            status='in progress' if e else 'claimed' if c else 'open',
                            symbol=(e or c or {}).get('symbol')))
    out.sort(key=lambda t: (t['tier'], t['size'], t['address']))
    return out


def cmd_tasks(a):
    need_setup()
    tasks = open_tasks(a.file)
    if a.tier:
        tasks = [t for t in tasks if t['tier'] == a.tier]
    return dict(ok=True, tasks=tasks)


def target_asm(unit, addr):
    """jeff's assembly of one function, from the unit's .s file."""
    path = os.path.join(WORK, 'split', 'asm', unit[:-4] + '.s')
    if not os.path.exists(path):
        return None
    lines, inside = [], False
    name = 'fn_%08X' % addr
    for line in open(path, errors='replace'):
        if re.match(r'\.fn %s\b' % name, line):
            inside = True
        if inside:
            lines.append(line.rstrip('\n'))
            if re.match(r'\.endfn %s\b' % name, line):
                break
    return '\n'.join(lines) if lines else None


def unit_of(addr, file, splits):
    e = splits[file]
    # one dot only: jeff names a unit's assembly file by cutting the name at its first dot
    return file if e['text'] and e['text'][0] <= addr < e['text'][1] else '%s_%08X.cpp' % (file[:-4], addr)


def cmd_show(a):
    need_setup()
    addr = int(a.address, 16)
    splits, syms = load_splits(SPLITS), jeff_symbols()
    start = max((x for x in syms if x <= addr), default=None)
    if start is None or addr >= start + syms[start][1]:
        raise Fail('no function at %08X' % addr)
    f = owner(start, splits)
    entry = next((e for e in manifest()['files'].get(f, []) if int(e['address'], 16) == start), None) if f else None
    c = claims().get('0x%08X' % start)
    size = entry['size'] if entry else syms[start][1]
    ft = features(read(start, size))
    status = ('exact' if entry and entry.get('matching', True) else 'in progress' if entry
              else 'claimed' if c else 'open' if f else 'not in a scaffolded file')
    hints = []
    if anchored_float_loads(read(start, size)):
        hints.append('float constants through one base register (addi rX, anchor; lfs f, d(rX)): the LTCG way, which a '
                     'plain build cannot produce; check with --ltcg')
    elif ft['float_ops']:
        hints.append('float code: most functions match in a plain build; if diff reports CD2 loading constants the '
                     'LTCG way, check with --ltcg')
    if ft['jump_table']:
        hints.append('switch with a jump table: case bodies are laid out in source order')
    if ft['vmx']:
        hints.append('VMX128 vector code: tier 4, needs the intrinsics in ppcintrinsics.h/vectorintrinsics.h')
    neighbours = []
    if f:
        addrs = file_functions(splits, syms)[f]
        i = addrs.index(start)
        man = {int(e['address'], 16): e for e in manifest()['files'].get(f, [])}
        for x in addrs[max(0, i - 2):i] + addrs[i + 1:i + 3]:
            e = man.get(x)
            neighbours.append(dict(address='0x%08X' % x, symbol=e['symbol'] if e else None,
                                   status='exact' if e and e.get('matching', True) else 'in progress' if e else 'open'))
    return dict(ok=True, address='0x%08X' % start, size=size, file=f, unit=unit_of(start, f, splits) if f else None,
                status=status, symbol=(entry or c or {}).get('symbol'), tier=tier(ft), features=ft, hints=hints,
                neighbours=neighbours, notes='docs/matching-notes.md',
                assembly=target_asm(unit_of(start, f, splits), start) if f else None)


def cmd_claim(a):
    need_setup()
    addr = int(a.address, 16)
    splits, syms = load_splits(SPLITS), jeff_symbols()
    f = owner(addr, splits)
    if addr not in syms or not f:
        raise Fail('%08X is not the start of a function in a scaffolded file (see `tasks`)' % addr)
    if any(int(e['address'], 16) == addr for e in manifest()['files'].get(f, [])):
        raise Fail('%08X is already in config/matched_functions.json' % addr)
    if not a.symbol.startswith('?') and not a.symbol.startswith('_'):
        raise Fail('the symbol must be (a prefix of) the MANGLED name, e.g. ?Update@cFoo@NS@@')
    cl = claims()
    cl['0x%08X' % addr] = dict(file=f, size=syms[addr][1], symbol=a.symbol,
                               time=datetime.datetime.now().isoformat(timespec='seconds'))
    os.makedirs(WORK, exist_ok=True)
    write_claims(cl)
    return dict(ok=True, claimed='0x%08X' % addr, file=f, symbol=a.symbol)


def cmd_unclaim(a):
    cl = claims()
    key = '0x%08X' % int(a.address, 16)
    if key not in cl:
        raise Fail('%s is not claimed' % key)
    del cl[key]
    write_claims(cl)
    return dict(ok=True, released=key)


def cmd_check(a):
    need_toolchain()
    src = rel(a.file)
    if src not in load_splits(SPLITS):
        raise Fail('%s is not a scaffolded source file (config/splits.txt)' % src)
    errors, warnings = policy(src)
    if errors:
        return dict(ok=False, file=src, policy_errors=errors, policy_warnings=warnings, functions=[])
    funcs = mapped(src)
    results, problems = compare_file(src, funcs, ltcg=a.ltcg)
    if a.explain:
        explain(src, results)
    log_attempt('check --ltcg' if a.ltcg else 'check', src, results)
    tracked = [r for r in results if r['tracked']]
    ok = not problems and all(r['status'] == 'EXACT' or (r['ltcg_only'] and r['status'] in ('LTCG EXACT', 'needs --ltcg'))
                              for r in tracked)
    return dict(ok=ok, file=src, functions=results, relocation_problems=problems, policy_errors=[], policy_warnings=warnings,
                summary='%d of %d functions exact' % (sum(r['status'] in ('EXACT', 'LTCG EXACT') for r in results),
                                                     len(results)))


def objdiff_unit(src, obj, unit, mappings):
    """objdiff's one-shot diff of one target unit against our object. mappings: {CD2 address: our full symbol}.
    Returns the parsed JSON (every symbol of the unit)."""
    target = os.path.join(WORK, 'split', 'obj', unit[:-4] + '.obj')
    d = scratch_dir('objdiff')
    # objdiff takes Unix-style paths relative to the project directory
    cfg = dict(min_version='2.0.0', units=[dict(name='u', target_path=os.path.relpath(target, d).replace('\\', '/'),
                                                base_path=os.path.relpath(obj, d).replace('\\', '/'),
                                                symbol_mappings={'fn_%08X' % a: n for a, n in mappings.items()})])
    json.dump(cfg, open(os.path.join(d, 'objdiff.json'), 'w'), indent=1)
    out = os.path.join(d, 'diff.json')
    if os.path.exists(out):
        os.remove(out)
    first = 'fn_%08X' % min(mappings)
    r = subprocess.run([OBJDIFF, 'diff', '-p', d, '-u', 'u', '-c', 'functionRelocDiffs=none', '-o', out, '--format', 'json',
                        first], capture_output=True, text=True)
    if r.returncode or not os.path.exists(out):
        raise Fail('objdiff failed:\n%s' % (r.stdout + r.stderr)[-2000:])
    return json.load(open(out))


def compiled_names(obj, funcs):
    """{CD2 address: our full symbol} for the mapped functions that the object defines."""
    names = [n for n, _, _ in coff.functions(obj)]
    out = {}
    for f in funcs:
        hit = [n for n in names if f['symbol'] in n]
        if hit:
            out[int(f['address'], 16)] = hit[0]
    return out


def cmd_diff(a):
    need_setup()
    need_toolchain()
    src = rel(a.file)
    splits = load_splits(SPLITS)
    if src not in splits:
        raise Fail('%s is not a scaffolded source file' % src)
    addr = int(a.address, 16)
    funcs = mapped(src)
    if not any(int(x['address'], 16) == addr for x in funcs):
        raise Fail('%08X has no symbol yet: claim it first (cd2.py claim %08X <mangled symbol prefix>)' % (addr, addr))
    obj = compile_file(src)
    names = compiled_names(obj, funcs)
    if addr not in names:
        raise Fail('no compiled function matches the symbol mapped to %08X' % addr)
    unit = unit_of(addr, src, splits)
    same_unit = {x: n for x, n in names.items() if unit_of(x, src, splits) == unit}
    data = objdiff_unit(src, obj, unit, same_unit)
    return dict(ok=True, file=src, address='0x%08X' % addr, symbol=names[addr], diff=render_diff(data, addr, a.context))


def explain(src, results):
    """Attach the classifier's findings to every function of `results` that is not exact (one objdiff run per unit)."""
    need_setup()
    splits = load_splits(SPLITS)
    obj = scratch('obj', os.path.basename(src) + '.obj')
    names = {int(r['address'], 16): r['name'] for r in results if r.get('name')}
    todo = [r for r in results if r.get('name') and r['status'] not in ('EXACT', 'LTCG EXACT')]
    by_unit = collections.defaultdict(list)
    for r in todo:
        by_unit[unit_of(int(r['address'], 16), src, splits)].append(r)
    for unit, rs in by_unit.items():
        same_unit = {x: n for x, n in names.items() if unit_of(x, src, splits) == unit}
        data = objdiff_unit(src, obj, unit, same_unit)
        for r in rs:
            rows = mismatch.pairs(data, int(r['address'], 16))
            r['findings'] = mismatch.classify(rows) if rows else []


def cmd_search(a):
    need_toolchain()
    src = rel(a.file)
    if src not in load_splits(SPLITS):
        raise Fail('%s is not a scaffolded source file' % src)
    addr = int(a.address, 16)
    f = next((x for x in mapped(src) if int(x['address'], 16) == addr), None)
    if not f:
        raise Fail('%08X has no symbol yet: claim it first' % addr)
    errors, _ = policy(src)
    if errors:
        raise Fail('fix the source policy first:\n  ' + '\n  '.join(errors))
    try:
        res = srch.search(src, f['symbol'], read(addr, f['size']), scratch_dir('search'), rounds=a.rounds,
                          budget=a.budget, jobs=a.jobs, log=lambda m: print(m, file=sys.stderr, flush=True))
    except ValueError as e:
        raise Fail(str(e))
    applied = bool(a.apply and res['steps'])
    if applied:
        open(os.path.join(ROOT, src), 'w', newline='').write(res['text'])
    log_attempt('search', src, [dict(address='0x%08X' % addr, status='EXACT' if res['best']['exact'] else
                                     '%d/%d words' % (res['best']['words'], res['best']['of']))])
    return dict(ok=True, file=src, address='0x%08X' % addr, symbol=f['symbol'], baseline=res['baseline'],
                best=res['best'], steps=res['steps'], compiles=res['compiles'], applied=applied, diff=res['diff'])


def cmd_facts(a):
    need_toolchain()
    import facts
    f = facts.record(read)
    return dict(ok=True, functions=len(f['functions']), file=rel(facts.FACTS))


# what a contribution may change; everything else (tools, config, tests, ...) is the maintainers' and needs their review
CONTRIBUTION = ('src', 'include', 'config/matched_functions.json', 'docs/matching-notes.md')


def git(*args):
    r = subprocess.run(['git', '-C', ROOT] + list(args), capture_output=True, text=True)
    if r.returncode:
        raise Fail('git %s: %s' % (' '.join(args[:3]), (r.stderr or r.stdout).strip()))
    return r.stdout


def write_claims(cl):
    tmp = scratch('claims.json')
    json.dump(cl, open(tmp, 'w'), indent=1)
    os.replace(tmp, CLAIMS)


def cmd_review(a):
    """Verify a contribution (a branch, tag or commit) with THIS checkout's tools and config, as a maintainer before
    merging: only the contribution's own changes to src/, include/, the manifest and the notes are applied, so it cannot
    change the gates that judge it. Its changes anywhere else are listed for review by hand. Needs a clean checkout,
    and restores it afterwards."""
    need_setup()
    need_toolchain()
    if git('status', '--porcelain', '--untracked-files=all').strip():
        raise Fail('the checkout has uncommitted changes: commit or stash them first')
    try:
        commit = git('rev-parse', '--verify', a.ref + '^{commit}').strip()
    except Fail:
        raise Fail('%s is not a branch, tag or commit here (fetch it first, e.g. git fetch origin pull/123/head:pr-123)'
                    % a.ref)
    base = git('merge-base', 'HEAD', commit).strip()

    def inside(p):
        return any(p == c or p.startswith(c + '/') for c in CONTRIBUTION)
    changes = [l.split('\t', 1) for l in git('diff', '--no-renames', '--name-status', base, commit).splitlines() if l]
    outside = [p for _, p in changes if not inside(p)]
    applied = [(s, p) for s, p in changes if inside(p)]
    in_head = set(git('ls-tree', '-r', '--name-only', 'HEAD', '--', *CONTRIBUTION).splitlines())
    try:
        for s, p in applied:
            if s == 'D' and os.path.exists(os.path.join(ROOT, p)):
                os.remove(os.path.join(ROOT, p))
        added = [p for s, p in applied if s != 'D']
        for i in range(0, len(added), 100):
            git('checkout', commit, '--', *added[i:i + 100])
        if a.record_facts:  # facts come from the game; recording them first lets the facts gate judge the new entries
            cmd_facts(a)
        res = cmd_verify(argparse.Namespace(exe=None, facts=False))
    finally:
        touched = [p for _, p in applied]
        back = [p for p in touched if p in in_head]
        for i in range(0, len(back), 100):
            git('checkout', 'HEAD', '--', *back[i:i + 100])
        for p in touched:
            if p not in in_head:
                git('rm', '-q', '--cached', '--ignore-unmatch', '--', p)
                if os.path.exists(os.path.join(ROOT, p)):
                    os.remove(os.path.join(ROOT, p))
    left = [l for l in git('status', '--porcelain', '--untracked-files=all').splitlines()
            if not (a.record_facts and l.endswith('config/target_facts.json'))]
    return dict(ok=res['ok'] and not outside and not left, ref=a.ref, commit=commit, base=base,
                applied=['%s %s' % sp for sp in applied], outside=outside, gates=res['gates'], restored=not left,
                left_over=left, facts_recorded=bool(a.record_facts))


def cmd_search_test(a):
    need_toolchain()
    r, t = srch.recovery_test(manifest(), read, limit=a.limit, log=lambda m: print(m, file=sys.stderr, flush=True))
    return dict(ok=r == t and t > 0, recovered=r, tried=t)


def bench_tasks(man):
    rows = []
    for f, e in bench.candidates(man):
        ft = features(read(int(e['address'], 16), e['size']))
        rows.append(dict(address=e['address'], size=e['size'], file=f, symbol=e['symbol'], tier=tier(ft)))
    rows.sort(key=lambda r: (r['tier'], r['address']))
    return rows


def bench_prepare(man, address, model):
    addr = int(address, 16)
    hit = next(((f, e) for f, e in bench.candidates(man) if int(e['address'], 16) == addr), None)
    if not hit:
        raise Fail('%08X is not a benchmark task (see `bench list`)' % addr)
    return bench.prepare(hit[0], hit[1], cmd_show(argparse.Namespace(address=address)), model)


def bench_suite_tasks(a):
    suite = bench.load_suite()
    if not suite:
        raise Fail('no benchmark suite: a maintainer runs `cd2.py bench suite --make`')
    tasks = suite['tasks']
    if a.tier:
        tasks = [t for t in tasks if t['tier'] == a.tier]
    return tasks[:a.limit] if a.limit else tasks


def bench_policy(src, workspace):
    """The source policy for a benchmark workspace: only the workspace and the XDK are allowed origins."""
    return policy(src, roots=[workspace], include=[os.path.join(workspace, 'include')])[0]


def bench_agent(agent):
    """`chat:<model>` is the built-in agent for any model behind an OpenAI-compatible API (tools/bench_chat.py);
    `claude:<model>` and `kilo:<provider/model>` run those CLIs sandboxed (tools/bench_claude.py, tools/bench_kilo.py);
    anything else is the command of any agent."""
    m = re.match(r'^(chat|claude|kilo):(\S+)$', agent or '')
    if m:
        script = dict(chat='bench_chat.py', claude='bench_claude.py', kilo='bench_kilo.py')[m.group(1)]
        return '"%s" -I "%s" %s' % (sys.executable, os.path.join(TOOLS, script), m.group(2))
    return agent


def selftest_expected(r):
    """Whether one self-test run ended as its agent must: the oracle and the chat agent EXACT, the cheats rejected by the
    source policy (emit, include) or not exact (forged result), the do-nothing agent not exact, the agent that fails
    without working flagged as an agent error."""
    m = r['kind']
    if m in ('oracle', 'chat'):
        return r['exact']
    if m in ('cheat-emit', 'cheat-include'):
        return r['status'] == 'rejected by the source policy'
    if m == 'error':
        return r['status'] == 'agent error' and not r['exact']
    return not r['exact']


def cmd_bench(a):
    need_toolchain()
    man = manifest()
    model = a.model or 'unnamed'
    if a.action in ('prepare', 'run', 'selftest') and bench.location_problem():
        raise Fail(bench.location_problem())
    if a.action == 'list':
        rows = bench_tasks(man)
        return dict(ok=True, tasks=[r for r in rows if not a.tier or r['tier'] == a.tier])
    if a.action == 'suite':
        if a.make:
            return dict(ok=True, tasks=bench.make_suite(bench_tasks(man))['tasks'])
        return dict(ok=True, tasks=bench_suite_tasks(a))
    if a.action == 'report':
        rows, table = bench.report(a.model)
        return dict(ok=True, results=rows, by_model_and_tier=table)
    if a.action in ('run', 'selftest'):
        need_setup()
        tasks = bench_suite_tasks(a)
        selftest = '"%s" -I "%s" ' % (sys.executable, os.path.join(TOOLS, 'bench.py'))
        if a.action == 'run':
            if not a.agent:
                raise Fail('bench run needs --agent "<command>" (TASK.md on stdin; {task} and {workspace} are '
                           'replaced) or --agent claude:<model>')
            runs = [(bench_agent(a.agent), model)]
        else:
            # only the oracle may reach EXACT: doing nothing, emitting CD2's words, compiling the repository's own
            # file and forging the result must all fail
            # model names private to this process, so that two self-tests (two verify runs) never share a workspace
            own = 'selftest%d-' % os.getpid()
            runs = [(selftest + 'oracle', own + 'oracle'), ('echo nothing', own + 'null')] + [
                (selftest + c, own + c) for c in ('cheat-emit', 'cheat-include', 'cheat-result')] + [
                (bench_agent('chat:mock-model') + ' --rounds 3', own + 'chat'),
                ('"%s" -I -c "import sys; sys.exit(3)"' % sys.executable, own + 'error')]  # fails without working
        aliases = relocs.load_aliases(ALIASES)
        out, stopped = [], None
        for agent, m in runs:
            saved, server = dict(os.environ), None
            kind = m.split('-', 1)[1] if a.action == 'selftest' else None
            if kind == 'chat':  # the built-in chat agent against a local stand-in model: no API, no key
                server, url = bench.mock_chat_server()
                for k in ('CD2_LLM_API_KEY', 'CD2_LLM_OPTIONS'):
                    os.environ.pop(k, None)
                os.environ['CD2_LLM_BASE_URL'] = url
            todo = tasks
            if kind and (kind.startswith('cheat') or kind == 'error'):  # one task per tier shows these
                todo = [t for i, t in enumerate(tasks) if t['tier'] not in [x['tier'] for x in tasks[:i]]]
            failures_in_a_row = 0
            try:
                for t in todo:
                    addr = int(t['address'], 16)
                    if a.action == 'run' and a.resume and not bench.needs_run(addr, m):
                        print('%-22s %s tier %d  kept (already has a result)' % (m, t['address'], t['tier']),
                              file=sys.stderr, flush=True)
                        continue
                    bench_prepare(man, t['address'], m)
                    code, secs = bench.run_agent(addr, m, agent, a.timeout)
                    rec = json.load(open(bench.result_path(addr, m)))
                    if bench.agent_failed(rec, os.path.join(bench.workspace(addr, m), rec['file'])):
                        res = bench.mark_agent_error(addr, m)  # the agent never worked on it: not scored
                        failures_in_a_row += 1
                        print('%-22s %s agent error (exit %s, nothing done):\n    %s' % (
                            m, t['address'], code, res['detail'][-300:].replace('\n', '\n    ')), file=sys.stderr, flush=True)
                    else:
                        res = bench.check(addr, m, read, {}, aliases, count=False, policy=bench_policy)
                        res = dict(res, **{k: v for k, v in bench.mark_scored(addr, m).items() if k == 'agent_error'})
                        failures_in_a_row = 0
                    out.append(dict(model=m, kind=kind, address=t['address'], tier=t['tier'], status=res['status'],
                                    exact=res['exact'], attempts=res['attempts'], agent_exit=code, seconds=secs,
                                    same_as_repository=res.get('same_as_repository'), detail=res.get('detail', '')))
                    if a.action == 'selftest' and not selftest_expected(out[-1]):  # keep the evidence of a failure
                        log = os.path.join(bench.workspace(int(t['address'], 16), m), 'agent.log')
                        out[-1]['agent_log_tail'] = open(log, errors='replace').read()[-1500:] if os.path.exists(log) else ''
                    print('%-22s %s tier %d  %-14s %3d attempt(s) %6.1f s' % (
                        m, t['address'], t['tier'], res['status'], res['attempts'], secs), file=sys.stderr, flush=True)
                    if a.action == 'run' and failures_in_a_row >= 3:
                        stopped = ('stopped: the agent failed %d tasks in a row without doing anything (a usage limit, a '
                                   'missing key, a crash; its output is above and in agent.log). Fix it, then continue '
                                   'with the same command plus --resume.' % failures_in_a_row)
                        break
            finally:
                if server:
                    server.shutdown()
                    os.environ.clear()
                    os.environ.update(saved)
        if a.action == 'selftest':
            def runs_of(kind):
                return [r for r in out if r['kind'] == kind]
            checks = dict(
                oracle_all_exact=all(r['exact'] for r in runs_of('oracle')),
                chat_agent_all_exact=all(r['exact'] for r in runs_of('chat')),
                null_none_exact=not any(r['exact'] for r in runs_of('null')),
                emit_rejected=all(r['status'] == 'rejected by the source policy' for r in runs_of('cheat-emit')),
                include_rejected=all(r['status'] == 'rejected by the source policy' for r in runs_of('cheat-include')),
                forged_result_ignored=not any(r['exact'] for r in runs_of('cheat-result')),
                agent_error_flagged=all(r['status'] == 'agent error' for r in runs_of('error')))
            for m in {r['model'] for r in out}:
                shutil.rmtree(os.path.join(bench.BENCH, bench.model_dir(m)), ignore_errors=True)
            return dict(ok=all(checks.values()), runs=out, unexpected=[r for r in out if not selftest_expected(r)],
                        **checks)
        return dict(ok=not stopped, runs=out, summary=bench.report(model)[1], stopped=stopped)
    if a.action == 'score':  # the final verdict of every prepared task (after working through them in an IDE agent)
        need_setup()
        rdir = os.path.dirname(bench.result_path(0, model))
        if not os.path.isdir(rdir):
            raise Fail('nothing prepared for model %s: run bench prepare --model %s first' % (model, model))
        aliases = relocs.load_aliases(ALIASES)
        out = []
        for f in sorted(os.listdir(rdir)):
            if f.endswith('.json'):
                res = bench.check(int(f[:-5], 16), model, read, {}, aliases, count=False, policy=bench_policy)
                out.append(dict(model=model, address=res['address'], tier=res['tier'], status=res['status'],
                                exact=res['exact'], attempts=res['attempts'], same_as_repository=res.get('same_as_repository')))
                print('%-22s %s tier %d  %-14s %3d attempt(s)' % (model, res['address'], res['tier'], res['status'],
                                                                 res['attempts']), file=sys.stderr, flush=True)
        return dict(ok=True, runs=out, summary=bench.report(model)[1])
    if a.action == 'prepare' and not a.address:  # the whole suite (or --tier/--limit), e.g. for an IDE agent
        need_setup()
        ds = [bench_prepare(man, t['address'], model) for t in bench_suite_tasks(a)]
        return dict(ok=True, workspaces=[rel(d) for d in ds], model=model)
    if not a.address:
        raise Fail('bench %s needs an address' % a.action)
    addr = int(a.address, 16)
    if a.action == 'prepare':
        need_setup()
        d = bench_prepare(man, a.address, model)
        return dict(ok=True, workspace=rel(d), task=rel(os.path.join(d, 'TASK.md')))
    if a.action == 'check':
        if not os.path.exists(bench.result_path(addr, model)):
            raise Fail('no workspace for %08X and model %s: run bench prepare first' % (addr, model))
        res = bench.check(addr, model, read, {}, relocs.load_aliases(ALIASES), policy=bench_policy)
        return dict(res, ok=bool(res['exact']))
    raise Fail('unknown bench action %s' % a.action)


def policy_self_test():
    """Plant one violation of each kind in a scratch file and require the policy to catch it; a clean file must pass."""
    d = scratch_dir('policy_selftest')
    shutil.rmtree(d, ignore_errors=True)
    os.makedirs(d)
    outside = tempfile.mkdtemp(prefix='cd2_outside_')
    open(os.path.join(outside, 'outside.h'), 'w').write('int g_outside;\n')
    cases = [
        ('clean file', 'int f(int a) { return a + 1; }\n', False),
        ('inline assembly', 'void f() { __asm { nop } }\n', True),
        ('assembly hidden in a macro', '#define QUIET __asm\nvoid f() { QUIET { nop } }\n', True),
        ('__emit', 'void f() { __emit 0x60000000; }\n', True),
        ('__declspec(naked)', '__declspec(naked) void f() {}\n', True),
        ('#pragma optimize', '#pragma optimize("", off)\nint f(int a) { return a; }\n', True),
        ('#line disguise', '#line 1 "C:/xdk/include/xbox/xtl.h"\nint f(int a) { return a; }\n', True),
        ('include from outside', '#include "%s"\n' % os.path.join(outside, 'outside.h').replace('\\', '/'), True),
    ]
    ok = True
    out = []
    for k, (what, text, bad) in enumerate(cases):
        src = os.path.join(d, 'case%d.cpp' % k)
        open(src, 'w').write(text)
        errors, _ = policy(rel(src), extra_roots=[d])
        good = bool(errors) == bad
        ok &= good
        out.append(dict(case=what, expected='rejected' if bad else 'accepted', result='rejected' if errors else 'accepted',
                        ok=good))
    shutil.rmtree(outside, ignore_errors=True)
    return ok, out


def cmd_lint(a):
    if a.self_test:
        ok, cases = policy_self_test()
        return dict(ok=ok, self_test=cases)
    files = [rel(p) for p in a.files] or sorted(rel(os.path.join(dp, f)) for dp, _, fs in os.walk(os.path.join(ROOT, 'src'))
                                                  for f in fs if f.endswith('.cpp'))
    res, empty = [], 0
    for src in files:
        if not has_code(os.path.join(ROOT, src)):  # set up, nothing written yet: nothing to check
            empty += 1
            continue
        e, w = policy(src)
        res.append(dict(file=src, errors=e, warnings=w))
    return dict(ok=not any(r['errors'] for r in res), files=res, without_code=empty)


def has_code(path):
    """False for a file of nothing but comments and whitespace (a set-up source file nobody has written in yet)."""
    text = re.sub(r'//[^\n]*|/\*.*?\*/', '', open(path, encoding='utf-8', errors='replace').read(), flags=re.S)
    return bool(text.strip())


def cmd_verify(a):
    """Every gate, then the gates' own self-tests (each plants errors and must catch all of them)."""
    exe = a.exe or EXE
    py = [sys.executable, '-I']
    ps = ['powershell', '-NoProfile', '-ExecutionPolicy', 'Bypass', '-File']
    # (name, command, pattern of the summary lines to report)
    facts_gate = ('target facts (no game)', py + [os.path.join(TOOLS, 'facts.py'), 'verify'],
                  r'matched functions are exact|relocation targets|LTCG')
    if a.facts:  # no game file: the recorded facts stand in for it (tools/facts.py)
        game = [facts_gate, ('self-test: target facts', py + [os.path.join(TOOLS, 'facts.py'), '--self-test'], r'self-test')]
    else:
        game = [('plain build + relocation targets', py + [os.path.join(TOOLS, 'verify_src.py'), exe],
                 r'matched functions are exact|relocation targets'),
                ('LTCG build + LTCG relocation targets', py + [os.path.join(TOOLS, 'verify_ltcg.py'), exe],
                 r'exact under LTCG|LTCG relocation targets'),
                ('self-test: relocation check', py + [os.path.join(TOOLS, 'verify_src.py'), exe, '--self-test'], r'self-test'),
                ('self-test: LTCG relocation check', py + [os.path.join(TOOLS, 'verify_ltcg.py'), exe, '--self-test'], r'self-test'),
                ('self-test: benchmark harness', py + [os.path.join(TOOLS, 'cd2.py'), 'bench', 'selftest'], r'benchmark self-test'),
                facts_gate]  # the recorded facts must agree with the game, or `verify --facts` would disagree
    gates = [('toolchain', None, None),
             ('source policy', None, None)] + game[:2] + [
             ('integrity', py + [os.path.join(TOOLS, 'check_integrity.py')], r'integrity'),
             ('headers', ps + [os.path.join(TOOLS, 'headers', 'check_headers.ps1')], r'headers')] + game[2:] + [
             ('self-test: integrity', py + [os.path.join(TOOLS, 'check_integrity.py'), '--self-test'], r'self-test'),
             ('self-test: source policy', None, None),
             ('self-test: mismatch classifier', py + [os.path.join(TOOLS, 'mismatch.py'), '--self-test'], r'self-test'),
             ('self-test: search transformations', py + [os.path.join(TOOLS, 'search.py'), '--self-test'], r'self-test'),
             ('self-test: jump table relocations', py + ['-m', 'unittest', 'discover', '-s',
                os.path.join(ROOT, 'tests'), '-p', 'test_jump_table_relocations.py'], r'Ran |^OK$|FAILED|ERROR')]
    out = []
    for name, cmd, pattern in gates:
        if name == 'toolchain':
            tp = toolchain_problems()
            out.append(dict(gate=name, ok=not tp, detail='; '.join(tp) or 'pinned'))
            continue
        if name == 'source policy':
            lint = cmd_lint(argparse.Namespace(files=[], self_test=False))
            bad = [e for f in lint['files'] for e in f['errors']]
            out.append(dict(gate=name, ok=not bad, detail='; '.join(bad[:5]) or '%d files clean (%d set up, nothing written yet)' % (
                len(lint['files']), lint['without_code'])))
            continue
        if name == 'self-test: source policy':
            ok, cases = policy_self_test()
            out.append(dict(gate=name, ok=ok, detail='%d of %d cases as expected' % (sum(c['ok'] for c in cases), len(cases))))
            continue
        print('%s...' % name, file=sys.stderr, flush=True)
        r = subprocess.run(cmd, capture_output=True, text=True)
        lines = [l.strip() for l in (r.stdout + r.stderr).splitlines() if l.strip()]
        summary = [l for l in lines if re.search(pattern, l)]
        if 'self-test' in name and 'benchmark' not in name and 'jump table' not in name:
            caught = sum(1 for l in summary if re.search(r'\b(caught|accepted|ok)\b', l))
            summary = ['%d of %d cases as expected' % (caught, len(summary))]
        out.append(dict(gate=name, ok=r.returncode == 0, detail=' | '.join(summary[-3:] or lines[-2:])))
    return dict(ok=all(g['ok'] for g in out), gates=out)


# ---------------------------------------------------------------------------------------------------- diff rendering

def render_diff(data, addr, context):
    """The diff of CD2's fn_<addr> against ours (tools/mismatch.py pairs objdiff's aligned rows), the classifier's
    findings, and the differing rows with `context` rows around each."""
    rows = mismatch.pairs(data, addr)
    if rows is None:
        raise Fail('objdiff paired no function of ours with fn_%08X' % addr)
    left = next(s for s in data['left']['symbols'] if s['name'] == 'fn_%08X' % addr)
    kinds = collections.Counter(k for _, _, k, _ in rows if k != 'none')
    keep = set()
    for i, (_, _, k, _) in enumerate(rows):
        if k != 'none':
            keep.update(range(i - context, i + context + 1))
    shown, last = [], -1
    for i, (l, r, k, a) in enumerate(rows):
        if i in keep:
            if last >= 0 and i != last + 1:
                shown.append(dict(gap=True))
            shown.append(dict(index=i, kind=k, cd2_address='0x%08X' % a if a is not None else None,
                              cd2=l['text'] if l else '', ours=r['text'] if r else ''))
            last = i
    return dict(match_percent=round(float(left.get('match_percent', 0)), 1),
                cd2_instructions=sum(1 for l, _, _, _ in rows if l), our_instructions=sum(1 for _, r, _, _ in rows if r),
                differences=dict(kinds), findings=mismatch.classify(rows), rows=shown)


# ---------------------------------------------------------------------------------------------------- text output

def show_text(cmd, res):
    if 'error' in res:
        print('error: ' + res['error'])
        return
    if cmd == 'doctor':
        for c in res['checks']:
            print('%-12s %-4s %s' % (c['check'], 'ok' if c['ok'] else 'FAIL', c['detail']))
    elif cmd == 'status':
        print('%-46s %5s %5s %5s %5s %5s %5s' % ('file', 'funcs', 'exact', 'ltcg', 'wip', 'claim', 'open'))
        for r in res['files'] + [dict(res['total'], file='total')]:
            print('%-46s %5d %5d %5d %5d %5d %5d' % (r['file'], r['functions'], r['exact'], r['ltcg_only'],
                                                     r['in_progress'], r['claimed'], r['open']))
        print(res['note'])
    elif cmd == 'tasks':
        for t in res['tasks']:
            ft = t['features']
            print('%s %5d bytes  tier %d  %-11s %-44s %s' % (t['address'], t['size'], t['tier'], t['status'], t['file'],
                  'calls %d, float %d, loops %d%s%s' % (ft['calls'], ft['float_ops'], ft['loops'],
                                                       ', jump table' if ft['jump_table'] else '',
                                                       ', VMX' if ft['vmx'] else '')))
        print('%d tasks' % len(res['tasks']))
    elif cmd == 'show':
        for k in ('address', 'size', 'file', 'unit', 'status', 'symbol', 'tier'):
            print('%-10s %s' % (k, res[k]))
        print('%-10s %s' % ('features', ', '.join('%s %s' % kv for kv in res['features'].items())))
        for h in res['hints']:
            print('hint       ' + h)
        for n in res['neighbours']:
            print('neighbour  %s %-12s %s' % (n['address'], n['status'], n['symbol'] or ''))
        print('notes      ' + res['notes'])
        print('\n' + (res['assembly'] or '(no assembly: run setup)'))
    elif cmd == 'check':
        for e in res.get('policy_errors', []):
            print('POLICY ' + e)
        for f in res['functions']:
            print('%s %5d bytes  %-12s %s%s' % (f['address'], f['size'], f['status'], f.get('name', f['symbol'])[:90],
                  '' if f['tracked'] else '   [%s]' % ('claim' if f['source'] == 'claim' else 'work in progress')))
            for fd in f.get('findings', []):
                print('             finding: %s%s' % (fd['title'], '  at ' + ', '.join(fd['rows'][:4]) if fd['rows'] else ''))
        for p in res.get('relocation_problems', []):
            print('PROBLEM ' + p)
        for w in res.get('policy_warnings', []):
            print('warning ' + w)
        if 'summary' in res:
            print(res['summary'])
    elif cmd == 'lint' and 'self_test' in res:
        for c in res['self_test']:
            print('self-test %-28s expected %-9s got %-9s %s' % (c['case'], c['expected'], c['result'], 'ok' if c['ok'] else 'FAILED'))
    elif cmd == 'lint':
        for f in res['files']:
            for e in f['errors']:
                print('ERROR ' + e)
            for w in f['warnings']:
                print('warning ' + w)
        print('%d files, %s%s' % (len(res['files']), 'policy OK' if res['ok'] else 'POLICY VIOLATIONS',
                                  ' (%d without code yet, skipped)' % res['without_code'] if res.get('without_code') else ''))
    elif cmd == 'search':
        print('%s %s: %d of %d words match before, %d of %d after (%d compiles)%s' % (
            res['address'], res['symbol'], res['baseline']['words'], res['baseline']['of'], res['best']['words'],
            res['best']['of'], res['compiles'], ', EXACT' if res['best']['exact'] else ''))
        for st in res['steps']:
            print('  kept: ' + st['transformation'])
        if res['diff']:
            print(res['diff'])
        print('applied to the source' if res['applied'] else
              ('not applied (run again with --apply to write it)' if res['steps'] else 'no improvement found'))
    elif cmd == 'facts':
        print('recorded facts for %d functions in %s' % (res['functions'], res['file']))
    elif cmd == 'search_test':
        print('search recovery test: %d of %d broken functions restored' % (res['recovered'], res['tried']))
    elif cmd == 'bench':
        if 'oracle_all_exact' in res:
            names = [('oracle_all_exact', 'oracle EXACT on every task'),
                     ('chat_agent_all_exact', 'chat agent (mock model) EXACT on every task'),
                     ('null_none_exact', 'do-nothing agent exact on none'),
                     ('emit_rejected', '__emit of CD2\'s words rejected'),
                     ('include_rejected', '#include of the repository\'s file rejected'),
                     ('forged_result_ignored', 'forged result ignored'),
                     ('agent_error_flagged', 'an agent that fails without working is flagged, not scored')]
            for k, what in names:
                print('  %-4s %s' % ('ok' if res.get(k) else 'FAIL', what))
            for r in res.get('unexpected', []):
                print('  unexpected: %s %s: %s (agent exit %s)%s%s' % (
                    r['model'], r['address'], r['status'], r['agent_exit'],
                    ('\n    detail: ' + r['detail'][:300]) if r.get('detail') else '',
                    ('\n    agent log: ' + r['agent_log_tail'][-600:].replace('\n', '\n               '))
                    if r.get('agent_log_tail') else ''))
            print('benchmark self-test: %s' % ('all %d checks hold' % len(names) if res['ok'] else 'FAILED'))
        elif 'runs' in res:
            for k, v in sorted(res['summary'].items()):
                print('%-30s %3d of %3d exact, %d attempts, %.0f s%s%s%s' % (
                    k, v['exact'], v['tasks'], v['attempts'], v['seconds'],
                    ', %d identical to the repository' % v['same_as_repository'] if v.get('same_as_repository') else '',
                    ', %d agent error(s), not scored' % v['agent_errors'] if v.get('agent_errors') else '',
                    ', %d not run' % v['not_run'] if v.get('not_run') else ''))
            if res.get('stopped'):
                print(res['stopped'])
        elif 'tasks' in res:
            for t in res['tasks']:
                print('%s %5d bytes  tier %d  %-44s %s' % (t['address'], t['size'], t['tier'], t['file'], t['symbol'][:60]))
            print('%d benchmark tasks' % len(res['tasks']))
        elif 'by_model_and_tier' in res:
            for k, v in sorted(res['by_model_and_tier'].items()):
                print('%-30s %3d of %3d exact, %d attempts, %.0f s%s%s%s' % (
                    k, v['exact'], v['tasks'], v['attempts'], v['seconds'],
                    ', %d identical to the repository' % v['same_as_repository'] if v.get('same_as_repository') else '',
                    ', %d agent error(s), not scored' % v['agent_errors'] if v.get('agent_errors') else '',
                    ', %d not run' % v['not_run'] if v.get('not_run') else ''))
            if not res['by_model_and_tier']:
                print('no results yet')
        elif 'workspace' in res:
            print('workspace %s; give the agent %s' % (res['workspace'], res['task']))
        elif 'workspaces' in res:
            for w in res['workspaces']:
                print(w)
            print('%d workspaces prepared for %s: in each, have the agent do TASK.md; then `bench score --model %s`'
                  % (len(res['workspaces']), res['model'], res['model']))
        else:
            print('%s: %s (attempt %d)%s' % (res['address'], res['status'], res['attempts'],
                                            ('\n' + res['detail']) if res.get('detail') else ''))
    elif cmd == 'config':
        print('settings in %s:' % res['file'])
        for k, v in sorted(res['settings'].items()):
            print('  %-13s %s' % (k, v))
        if not res['settings'].get('xdk'):
            print('  (no xdk: cd2.py config --xdk <extracted XDK 9328 directory>)')
    elif cmd == 'setup':
        print('set up in %s: %d functions analysed, one target object per source file' % (res['workdir'], res['functions']))
    elif cmd == 'claim':
        print('claimed %s (%s) as %s' % (res['claimed'], res['file'], res['symbol']))
    elif cmd == 'unclaim':
        print('released %s' % res['released'])
    elif cmd == 'diff':
        d = res['diff']
        print('%s %s: objdiff match %.1f%%, %d CD2 / %d our instructions; %s' % (
            res['address'], res['symbol'], d['match_percent'], d['cd2_instructions'], d['our_instructions'],
            ', '.join('%d %s' % (n, k.replace('_', ' ')) for k, n in sorted(d['differences'].items())) or 'no differences'))
        for f in d['findings']:
            print('FINDING %s%s' % (f['title'], ('  at ' + ', '.join(f['rows'][:6]) + (' ...' if len(f['rows']) > 6 else ''))
                                    if f['rows'] else ''))
            print('        %s' % f['hint'])
            print('        (%s)' % f['notes'])
        print()
        print('%-10s %-34s %-34s %s' % ('CD2 addr', 'CD2', 'ours', ''))
        for r in d['rows']:
            if r.get('gap'):
                print('   ...')
                continue
            print('%-10s %-34s %-34s %s' % (r['cd2_address'] or '', r['cd2'][:34], r['ours'][:34],
                                          '' if r['kind'] == 'none' else '<- ' + r['kind'].replace('_', ' ')))
    elif cmd == 'verify':
        for g in res['gates']:
            print('%-34s %-4s %s' % (g['gate'], 'PASS' if g['ok'] else 'FAIL', g['detail'][:150]))
        print('VERIFY: %s' % ('PASS' if res['ok'] else 'FAIL'))
    elif cmd == 'review':
        print('%s (%s), branched from %s; applied %d change(s) to src/, include/, the manifest and the notes'
              % (res['ref'], res['commit'][:10], res['base'][:10], len(res['applied'])))
        for g in res['gates']:
            print('  %-34s %-4s %s' % (g['gate'], 'PASS' if g['ok'] else 'FAIL', g['detail'][:140]))
        if res['outside']:
            print('changes outside what a contribution may change (not judged by the gates; review them by hand):')
            for p in res['outside']:
                print('  ' + p)
        if res['facts_recorded']:
            print('target facts recorded in config/target_facts.json: commit them with the merge')
        if not res['restored']:
            print('WARNING: the checkout was not restored cleanly: %s' % '; '.join(res['left_over'][:10]))
        print('REVIEW: %s' % ('PASS' if res['ok'] else 'FAIL'))
    else:
        print(json.dumps(res, indent=1))


def main():
    p = argparse.ArgumentParser(prog='cd2', description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument('--json', action='store_true', help='print one JSON object')
    sub = p.add_subparsers(dest='cmd', required=True)
    s = sub.add_parser('setup'); s.add_argument('xex')
    s = sub.add_parser('config'); s.add_argument('--xdk'); s.add_argument('--ruffking-pdb'); s.add_argument('--burn-pdb')
    s.add_argument('--bench-dir')
    sub.add_parser('doctor')
    sub.add_parser('status')
    s = sub.add_parser('tasks'); s.add_argument('file', nargs='?'); s.add_argument('--tier', type=int)
    s = sub.add_parser('show'); s.add_argument('address')
    s = sub.add_parser('claim'); s.add_argument('address'); s.add_argument('symbol')
    s = sub.add_parser('unclaim'); s.add_argument('address')
    s = sub.add_parser('check'); s.add_argument('file'); s.add_argument('--ltcg', action='store_true')
    s.add_argument('--explain', action='store_true')
    s = sub.add_parser('diff'); s.add_argument('file'); s.add_argument('address'); s.add_argument('--context', type=int, default=2)
    s = sub.add_parser('search'); s.add_argument('file'); s.add_argument('address')
    s.add_argument('--rounds', type=int, default=6); s.add_argument('--budget', type=int, default=400)
    s.add_argument('--jobs', type=int); s.add_argument('--apply', action='store_true')
    s = sub.add_parser('search-test'); s.add_argument('--limit', type=int, default=25)
    s = sub.add_parser('bench')
    s.add_argument('action', choices=['list', 'suite', 'prepare', 'check', 'score', 'run', 'report', 'selftest'])
    s.add_argument('address', nargs='?'); s.add_argument('--tier', type=int); s.add_argument('--model')
    s.add_argument('--agent'); s.add_argument('--limit', type=int); s.add_argument('--timeout', type=int, default=1800)
    s.add_argument('--make', action='store_true'); s.add_argument('--resume', action='store_true')
    s = sub.add_parser('lint'); s.add_argument('files', nargs='*'); s.add_argument('--self-test', action='store_true')
    s = sub.add_parser('verify'); s.add_argument('--exe'); s.add_argument('--facts', action='store_true')
    s = sub.add_parser('review'); s.add_argument('ref'); s.add_argument('--record-facts', action='store_true')
    s = sub.add_parser('facts'); s.add_argument('action', choices=['record'])
    a = p.parse_args(sys.argv[1:] if '--json' not in sys.argv else [x for x in sys.argv[1:] if x != '--json'])
    a.json = '--json' in sys.argv
    cmd = a.cmd.replace('-', '_')
    try:
        res = globals()['cmd_' + cmd](a)
    except Fail as e:
        res = dict(ok=False, error=str(e))
    if a.json:
        print(json.dumps(res, indent=1))
    else:
        show_text(cmd, res)
    sys.exit(0 if res.get('ok') else 1)


if __name__ == '__main__':
    main()
