"""Target facts: confirm matches without the game.

usage: py -I tools/facts.py record <path to extracted default.exe>     (writes config/target_facts.json)
       py -I tools/facts.py verify                                      (anyone with the XDK: no game file needed)
       py -I tools/facts.py --self-test                                 (plants errors; each must be caught)

Every gate normally reads Crackdown 2's code from your own extracted executable. To confirm the matches without the
game (another machine, a reviewer), whoever adds a match records (`cd2.py facts record`, with the game), for every
function in config/matched_functions.json, facts from which a match can be confirmed but no code recovered:
  plain   the word positions the compiler leaves to the linker (relocations), and a SHA-256 of CD2's bytes with those
          fields masked as the byte comparison masks them (only the opcode bits kept)
  targets the CD2 address each relocation resolves to; the bytes of the float constants referenced; a SHA-256 of the
          strings referenced (their text is not stored)
  ltcg    a SHA-256 of CD2's words with address immediates masked (tools/verify_ltcg.py), whether the code ends the
          function, and per file the float constants CD2 loads directly (values, needed to build the LTCG model)
  vtable  whether CD2 puts the function in a vtable (lowest slot, its table, number of tables): a match declared as a
          plain member function fails (R13), since its bytes match whether it is virtual or not
  data    per address of data the matched functions reach (relocs.data_reached: a vtable, an initialized global) and
          per extent our objects give it: a SHA-256 of CD2's bytes there with the relocated words cleared, and the
          words at those relocations (the addresses CD2's vtable slots and pointers hold)
`verify` compiles every file with the pinned compiler and reaches the same verdicts as tools/verify_src.py and
tools/verify_ltcg.py. A function whose relocations moved, or a new entry, needs `record` again (with the game).
"""
import concurrent.futures, hashlib, json, os, re, shutil, struct, sys, tempfile

TOOLS = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, TOOLS)
import buildcache  # noqa: E402
import coff  # noqa: E402
import cvtypes  # noqa: E402
import relocs  # noqa: E402
import verify_ltcg  # noqa: E402
from verify_src import (ROOT, XDK, BIN, EXPECTED_ENTRY, DATA_PLANTS, pe_reader, check_toolchain, plain_command,  # noqa: E402
                        file_flags, ltcg_built, plant_copy, symbol_matches, vtable_fact, vtable_slot_problem,
                        compile_z7, game_tables, game_data_check, data_coverage, coverage_figures, data_splits, work_dir)

FACTS = os.path.join(ROOT, 'config', 'target_facts.json')
MANIFEST = os.path.join(ROOT, 'config', 'matched_functions.json')


def sha(b):
    return hashlib.sha256(b).hexdigest()


def env():
    return dict(os.environ, PATH=BIN + ';' + os.environ['PATH'],
                INCLUDE=os.path.join(XDK, 'include', 'xbox') + ';' + os.path.join(ROOT, 'include'))


def compile_plain(src, d, path=None):
    """Compile the repository file src (or a modified copy at path, with src's directory on the include path), and
    beside it its /Z7 build, whose records give the sizes of its data (object_sizes)."""
    obj = os.path.join(d, os.path.basename(src) + '.obj')
    r = buildcache.compile(plain_command(src, obj, path), env())
    if r.returncode:
        raise SystemExit('%s: compile error\n%s' % (src, r.stdout + r.stderr))
    compile_z7(src, d, env(), path)
    return obj


def object_sizes(obj):
    """{symbol: size} of the data of a compile_plain object, from its /Z7 build ({} if it has none)"""
    z7 = obj[:-len('.obj')] + '.z7.obj'
    return cvtypes.data_sizes(z7) if os.path.exists(z7) else {}


def mask(code, rel):
    """Clear the field each relocation patches (coff.compare's rule: opcode and registers stay); mask ADDR32 data
    words whole, whose destinations are checked separately."""
    b = bytearray(code)
    fields = getattr(rel, 'fields', {})
    for off in rel:
        if off + 4 <= len(b):
            if off in getattr(rel, 'absolute', ()):
                b[off:off + 4] = b'\0\0\0\0'
            else:
                w = int.from_bytes(b[off:off + 4], 'big') & ~fields.get(off, coff.OPERANDS) & 0xFFFFFFFF
                b[off:off + 4] = w.to_bytes(4, 'big')
    return bytes(b)


def ltcg_hash(ws, start, absolute_offsets=()):
    return sha(struct.pack('>%dI' % len(ws), *verify_ltcg.masked(ws, start, absolute_offsets)))


# ---------------------------------------------------------------------------------------------------- record

FACTS_VERSION = 5  # 2: the vtable fact; 3: relocated words keep their registers in the plain hash; 4: data facts;
# 5: exact data sizes, the zero check, anchors, table lengths, whole strings


def data_offsets(d):
    return sorted({off for off, _, _, _ in d['relocations']})


def data_fact(read, addr, d, obj):
    """What `verify` needs to check data d (relocs.Obj.data_symbol, defined in obj) at CD2 address addr without the
    game."""
    offsets = data_offsets(d)
    rec = dict(size=d['size'], relocations=offsets)
    try:
        theirs = read(addr, d['size'])
    except ValueError:
        rec['uninitialized'] = True  # CD2 has no initialized data there
        return rec
    if d['data'] is not None:
        rec['sha'] = sha(relocs.mask_words(theirs, offsets))
    rec['words'] = {str(off): '0x%08X' % struct.unpack_from('>I', theirs, off)[0] for off in offsets
                    if off + 4 <= len(theirs)}
    for off, t, target, addend in d['relocations']:  # what relocs.check_consistency reads where a pointer leads
        if str(off) not in rec['words']:
            continue
        a = (int(rec['words'][str(off)], 16) - addend) & 0xFFFFFFFF
        if relocs.is_constant(target):
            try:
                rec.setdefault('constants', {})[str(off)] = read(a, len(bytes.fromhex(target.split('@', 1)[1]))).hex()
            except ValueError:
                pass
        elif relocs.is_string(target):
            ours = relocs.string_bytes(obj, target)  # compared as relocs.check_consistency compares it: our length
            if ours is not None:
                try:
                    rec.setdefault('strings', {})[str(off)] = sha(read(a, len(ours)))
                except ValueError:
                    pass
    return rec


def zero_key(addr, d):
    return '0x%08X:%X' % (addr, d['size'])


def record_data(facts, read, reached):
    for f, sym, addr, obj, d in reached:
        if d['data'] is None and not d['relocations']:
            if d['exact']:  # uninitialized: whether CD2 has zeros there too (relocs.check_data's zero check)
                try:
                    p = relocs.zero_problem(f, sym, addr, d['size'], read(addr, d['size']))
                    # 'zero', or the problem's figures: how many bytes CD2 initializes, the first one's offset
                    facts['zero'][zero_key(addr, d)] = 'zero' if p is None else re.search(
                        r'initializes (\d+) of .*\(first at \+([0-9A-F]+)\)', p).group(1, 2)
                except ValueError:
                    facts['zero'][zero_key(addr, d)] = 'bss'
            continue
        recs = facts['data'].setdefault('0x%08X' % addr, [])
        if not any(r['size'] == d['size'] and r['relocations'] == data_offsets(d) for r in recs):
            recs.append(data_fact(read, addr, d, obj))


class Oracle:
    """The answers the game gives the data checks besides the data's own bytes (relocs.anchor_data's words,
    relocs.check_tables' table lengths and slot owners): recorded while `record` asks the game, replayed by `verify`.
    A question not recorded counts as no answer: anchoring then finds nothing and a table check is skipped, which
    `record` then fixes, as facts recorded from an older tree would have to be re-recorded anyway."""

    def __init__(self, facts, words_of=None, table_words=None, own_slot=None):
        self.facts, self.game = facts, (words_of, table_words, own_slot)
        for k in ('words', 'tables', 'owners'):
            facts.setdefault(k, {})

    # only answers other than the default (no words, no table, not owned) are kept
    def words_of(self, a):
        if self.game[0]:
            words = self.game[0](a)
            if words:
                self.facts['words']['0x%08X' % a] = ['0x%08X' % w for w in words]
        return [int(w, 16) for w in self.facts['words'].get('0x%08X' % a, ())]

    def table_words(self, a):
        if self.game[1]:
            n = self.game[1](a)
            if n is not None:
                self.facts['tables']['0x%08X' % a] = n
        return self.facts['tables'].get('0x%08X' % a)

    def own_slot(self, f, a):
        if self.game[2] and self.game[2](f, a):
            self.facts['owners']['0x%08X:%s' % (a, f)] = True
        return self.facts['owners'].get('0x%08X:%s' % (a, f), False)


def check_recorded_data(f, sym, addr, obj, d, facts, contents, used=None):
    """relocs.check_data from the recorded facts. contents ({(address, length): bytes}, the consistency checker's view
    of CD2) receives the constants and strings the data's pointers lead to; used (a set) receives the record consulted
    (record_key), for stale_facts. Returns (entries, problems)."""
    used = set() if used is None else used
    if d['data'] is None and not d['relocations']:
        if not d['exact']:
            return [], []  # its size is unknown: only what follows (relocs.check_extents) can be checked
        zero = facts.get('zero', {}).get(zero_key(addr, d))
        used.add(('zero', zero_key(addr, d)))
        if zero is None:
            return [], ['%s %s at %08X: no recorded data facts for its %X bytes (run `py -I tools/cd2.py facts record`)'
                        % (f, sym, addr, d['size'])]
        if zero in ('zero', 'bss'):
            return [], []
        return [], ['%s %s at %08X: zero-initialized, but CD2 initializes %s of its %d byte(s) (first at +%s)'
                    % (f, sym, addr, zero[0], d['size'], zero[1])]
    recs = facts.get('data', {}).get('0x%08X' % addr)
    rec = next((r for r in recs or () if r['size'] == d['size'] and r['relocations'] == data_offsets(d)), None)
    used.add(record_key('0x%08X' % addr, dict(size=d['size'], relocations=data_offsets(d))))
    if rec is None:
        return [], ['%s %s at %08X: no recorded data facts for its %X bytes (run `py -I tools/cd2.py facts record`)'
                    % (f, sym, addr, d['size'])]
    if rec.get('uninitialized'):
        return [], ['%s %s at %08X: initialized data, but CD2 has no initialized data there' % (f, sym, addr)]
    problems = []
    if d['data'] is not None and sha(relocs.mask_words(d['data'], rec['relocations'])) != rec.get('sha'):
        problems.append('%s %s at %08X: its %X bytes outside its relocations differ from CD2 (from recorded facts)'
                        % (f, sym, addr, d['size']))
    elif d['data'] is not None and not rec['relocations']:
        contents[(addr, d['size'])] = d['data']  # CD2's bytes there, confirmed (relocs.identical_copies reads them)
    words = {int(k): int(v, 16) for k, v in rec['words'].items()}
    for off, t, target, addend in d['relocations']:
        if off not in words:
            continue
        a = (words[off] - addend) & 0xFFFFFFFF
        if relocs.is_constant(target) and str(off) in rec.get('constants', {}):
            want = bytes.fromhex(rec['constants'][str(off)])
            contents[(a, len(want))] = want
        elif relocs.is_string(target):
            ours = relocs.string_bytes(obj, target)
            if ours is not None:
                contents[(a, len(ours))] = ours if rec.get('strings', {}).get(str(off)) == sha(ours) else b'\0' * len(ours)
    entries, pr = relocs.data_pointers(f, sym, d, words, obj)
    return entries, problems + pr


def facts_data_check(facts, contents, used=None):
    """relocs.check_all_data's check from the recorded facts"""
    return lambda f, sym, addr, obj, d: check_recorded_data(f, sym, addr, obj, d, facts, contents, used)


def record_key(addr, rec):
    return ('data', addr, rec['size'], tuple(rec['relocations']))


def stale_facts(facts, used):
    """The coverage guard: recorded data facts no datum consulted (record_key; zero facts as ('zero', key)). Each
    stood for a datum the gates located when the facts were recorded and no longer locate (a header change that
    stops a vtable from anchoring, a reference removed): the coverage dropped without a word, so it is a problem until
    the facts are recorded again, whose diff then shows what was lost."""
    recorded = {record_key(a, r) for a, recs in facts.get('data', {}).items() for r in recs}
    recorded |= {('zero', k) for k in facts.get('zero', {})}
    stale = sorted(recorded - used, key=lambda k: k[1])
    if not stale:
        return []
    return ['%d recorded data fact(s) stand for data the gates no longer locate (first: %s): the data coverage dropped; '
            'record the facts again (`py -I tools/cd2.py facts record`) and check what the diff of '
            'config/target_facts.json drops' % (len(stale), stale[0][1])]


def record(read, references=None):
    """references: cd2.py game_references() (computed from the game when not given). The builds go through the caches
    (tools/buildcache.py) unless CD2_NO_CACHE=1, as `cd2.py review` sets."""
    if references is None:
        import cd2
        references = cd2.game_references()
    man = json.load(open(MANIFEST))
    facts = dict(version=FACTS_VERSION, note='generated by tools/facts.py record; do not edit', files={}, functions={},
                 data={}, zero={})
    tmp = work_dir('facts_')

    def build(src):
        d = os.path.join(tmp, re.sub(r'\W', '_', os.path.splitext(src)[0]))
        os.makedirs(d, exist_ok=True)
        obj = compile_plain(src, d)
        return obj, object_sizes(obj)
    with concurrent.futures.ThreadPoolExecutor(max_workers=verify_ltcg.WORKERS) as pool:
        builds = dict(zip(man['files'], pool.map(build, man['files'])))
    file_objs, entries, known = [], [], {}  # as the plain gate gathers them, for the data checks below
    for src, funcs in man['files'].items():
        obj, sizes = builds[src]
        compiled = list(coff.functions(obj))
        robj = relocs.Obj(obj, sizes)
        file_objs.append((src, robj))
        consts = verify_ltcg.direct_constants(read, funcs)
        facts['files'][src] = dict(direct_constants=[[op, struct.pack('>d', v).hex()] for op, v in consts])
        for f in funcs:
            va, size = int(f['address'], 16), f['size']
            target = read(va, size)
            tw = verify_ltcg.words(target)
            e = dict(size=size)
            vt = vtable_fact(f['address'], f['symbol'], references)
            if vt:
                e['vtable'] = vt
            if ltcg_built(src):
                e['ltcg'] = dict(sha=ltcg_hash(tw, va), ends=verify_ltcg.ends_function(tw))
            if f.get('ltcg') and f.get('matching', True) and ltcg_built(src):
                # exact only under LTCG: what its references are in CD2 (positions, addresses, constant bytes, and
                # a hash of the C string at each data address, as the string checks need)
                refs = verify_ltcg.references(tw, va)
                floats, strings = {}, {}
                for i, kind, addr, op in refs:
                    if op in verify_ltcg.FLOAT_LOADS:
                        floats['0x%08X:%d' % (addr, verify_ltcg.FLOAT_LOADS[op])] = read(addr, verify_ltcg.FLOAT_LOADS[op]).hex()
                    elif kind == 'address':
                        cs = verify_ltcg.cstring(read, addr)
                        if cs:
                            strings['0x%08X' % addr] = sha(cs)
                e['ltcg'].update(refs=[[i, kind, '0x%08X' % addr, op] for i, kind, addr, op in refs], floats=floats,
                                 strings=strings)
            found = [(n, c, rl) for n, c, rl in compiled if symbol_matches(f['symbol'], n)]
            if found:
                name, code, rl = found[0]
                if f.get('matching', True):
                    known[relocs.known_key(src, name, robj)] = va
                absolute = sorted(getattr(rl, 'absolute', ()))
                if absolute and 'ltcg' in e:
                    e['ltcg'].update(absolute_relocations=absolute, sha=ltcg_hash(tw, va, absolute))
                if coff.compare(code, target, rl)[0]:
                    res, _ = relocs.resolve(robj, name, target, va)
                    if f.get('matching', True) and not f.get('ltcg'):  # as the plain gate checks them
                        entries += [(src, name, s, a, k, o, robj) for s, a, k, o in res]
                    consts_b, strings = {}, {}
                    for sym, addr, kind, off in res:
                        if relocs.is_constant(sym):
                            n = len(bytes.fromhex(sym.split('@', 1)[1]))
                            consts_b['0x%08X' % addr] = read(addr, n).hex()
                        elif relocs.is_string(sym):
                            ours = relocs.string_bytes(robj, sym)
                            if ours is not None:
                                strings['0x%08X:%d' % (addr, len(ours))] = sha(read(addr, len(ours)))
                    e['plain'] = dict(relocations=sorted(rl), sha=sha(mask(target, rl)),
                                      targets=sorted([off, kind, '0x%08X' % addr] for _, addr, kind, off in res),
                                      constants=consts_b, strings=strings)
                    if absolute:
                        e['plain']['absolute_relocations'] = absolute
            facts['functions'][f['address']] = e
    # the data, as the plain gate checks it; the oracle keeps what the game answers besides the data's own bytes
    words_of, (table_words, own_slot) = game_tables(read)
    oracle = Oracle(facts, words_of, table_words, own_slot)
    reached, _ = relocs.check_all_data(entries, game_data_check(read), tables=(oracle.table_words, oracle.own_slot),
                                       anchors=(file_objs, {k: v for k, v in known.items() if isinstance(k, str)},
                                                oracle.words_of))
    record_data(facts, read, reached)
    facts['coverage'] = coverage_figures(reached, file_objs, sum(1 for e in entries if e[4] == 'data pointer'), entries,
                                         data_splits())
    # the data the functions exact only under LTCG reach: naming it takes their LTCG build, as tools/verify_ltcg.py
    lfiles = [src for src, funcs in man['files'].items()
              if ltcg_built(src) and any(f.get('ltcg') and f.get('matching', True) for f in funcs)]

    def ltcg_reached(src):
        res = verify_ltcg.check_file(src, man['files'][src], read, env(),
                                     os.path.join(tmp, 'ltcg_' + re.sub(r'\W', '_', os.path.splitext(src)[0])),
                                     out=lambda m: None)
        return res['reached'] if res else []
    ltcg_all = []
    with concurrent.futures.ThreadPoolExecutor(max_workers=verify_ltcg.WORKERS) as pool:
        for reached in pool.map(ltcg_reached, lfiles):
            record_data(facts, read, reached)
            ltcg_all += reached
    relocs.check_tables(ltcg_all, oracle.table_words, oracle.own_slot)  # the answers verify's LTCG part replays
    json.dump(facts, open(FACTS, 'w', newline='\n'), indent=1, sort_keys=True)
    return facts


# ---------------------------------------------------------------------------------------------------- verify

def plain_file(src, funcs, obj, sizes, facts):
    """verify's plain check of one file, from its build (obj and the sizes of its data): dict(lines (its output), ok,
    total, pending, nfuncs, entries (the references of its exact functions), problems, known, contents (the constants
    and strings they reach, as recorded), robj). It depends on nothing but the file's build and the recorded facts."""
    compiled = list(coff.functions(obj))
    robj = relocs.Obj(obj, sizes)
    r = dict(lines=[src], ok=0, total=0, pending=0, nfuncs=0, entries=[], problems=[], known={}, contents={}, robj=robj)
    out, entries, problems, known, contents = r['lines'].append, r['entries'], r['problems'], r['known'], r['contents']
    for f in funcs:
        va, size, tracked = int(f['address'], 16), f['size'], f.get('matching', True)
        fe = facts['functions'].get(f['address'])
        found = [(n, c, rl) for n, c, rl in compiled if symbol_matches(f['symbol'], n)]
        if found and tracked:
            known[relocs.known_key(src, found[0][0], robj)] = va
            vp = vtable_slot_problem(found[0][0], (fe or {}).get('vtable'))
            if vp:
                problems.append('%s %s: %s' % (src, found[0][0], vp))
        if f.get('ltcg') and not ltcg_built(src):  # a plain object has no LTCG build to be exact in
            r['total'] += bool(tracked)
            out('  %08X  INVALID      %s   [marked "ltcg" in a plain object]' % (va, f['symbol']))
            continue
        if f.get('ltcg'):
            continue  # exact only under LTCG: verify's LTCG part
        r['total'] += bool(tracked)
        r['pending'] += not tracked
        if not found:
            out('  %08X  symbol not found: %s' % (va, f['symbol']))
            continue
        name, code, rl = found[0]
        if fe is None or fe['size'] != size:
            out('  %08X  NO FACTS     %s' % (va, name))
            if tracked:
                problems.append('%s: no recorded facts for %08X (run `py -I tools/cd2.py facts record`)' % (src, va))
            continue
        p = fe.get('plain')
        exact = bool(p) and sorted(rl) == p['relocations'] and \
            sorted(getattr(rl, 'absolute', ())) == p.get('absolute_relocations', []) and \
            len(code) == size and sha(mask(code, rl)) == p['sha']
        if exact and tracked:
            stored = {off: int(a, 16) for off, kind, a in p['targets']}
            for off, t, sym, add in robj.relocations(name):
                if t == relocs.REFHI:
                    continue
                if off not in stored:
                    problems.append('%s %s+%X: relocation not in the recorded facts' % (src, name, off))
                    continue
                kind = 'call' if t == relocs.REL24 else 'data'
                if t == relocs.ADDR32:
                    kind = 'local address'
                    try:
                        expected = (va + robj.local_address_offset(name, off, sym, add)) & 0xFFFFFFFF
                        if stored[off] != expected:
                            problems.append('%s %s+%X: ADDR32 destination differs from the recorded target'
                                            % (src, name, off))
                    except ValueError as e:
                        problems.append('%s %s+%X: %s' % (src, name, off, e))
                entries.append((src, name, sym, stored[off], kind, off, robj))
                if relocs.is_constant(sym):
                    want = bytes.fromhex(sym.split('@', 1)[1])
                    rec = p['constants'].get('0x%08X' % stored[off])
                    if rec is not None:
                        contents[(stored[off], len(want))] = bytes.fromhex(rec)
                elif relocs.is_string(sym):
                    ours = relocs.string_bytes(robj, sym)
                    if ours is not None:
                        rec = p['strings'].get('0x%08X:%d' % (stored[off], len(ours)))
                        contents[(stored[off], len(ours))] = ours if rec == sha(ours) else b'\0' * len(ours)
            r['nfuncs'] += 1
        r['ok'] += exact and tracked
        out('  %08X  %4d bytes  %-8s %s%s' % (va, size, 'EXACT' if exact else 'differs', name,
                                                '' if tracked else '   [work in progress]'))
    return r


def verify(override=None, ltcg=True, out=print, shared=None):
    """Plain build, relocation targets and (with ltcg) the LTCG build, from the recorded facts. override: {src: path of
    a modified copy} (for the self-test). shared: a dict that keeps the builds and plain checks of the files override
    leaves alone from one call to the next (the self-test's calls differ in one file each). Returns (passed,
    problems)."""
    override = override or {}
    shared = {} if shared is None else shared
    man = json.load(open(MANIFEST))
    if not os.path.exists(FACTS):
        raise SystemExit('no %s: run `py -I tools/cd2.py facts record`' % FACTS)
    facts = json.load(open(FACTS))
    if facts.get('version', 1) < FACTS_VERSION:
        raise SystemExit('%s predates the current facts format (version %d): run `py -I tools/cd2.py facts record`'
                         % (FACTS, FACTS_VERSION))
    tmp = work_dir('facts_')
    ok = total = pending = ltcg_ok = ltcg_total = 0
    entries, problems, known, nfuncs = [], [], {}, 0
    contents = {}  # (address, length) -> bytes confirmed against the recorded facts, for the consistency checker

    def read(addr, n):
        if (addr, n) in contents:
            return contents[(addr, n)]
        raise KeyError('no recorded fact for %d bytes at %08X' % (n, addr))
    # every file compiles at once, each into its own directory; the checks below read the results in manifest order
    pool = concurrent.futures.ThreadPoolExecutor(max_workers=verify_ltcg.WORKERS)

    def own_dir(src, kind):
        d = os.path.join(tmp, kind + '_' + re.sub(r'\W', '_', os.path.splitext(src)[0]))
        os.makedirs(d, exist_ok=True)
        return d
    def build(src):
        if src not in override and ('build', src) in shared:
            return shared[('build', src)]
        d = own_dir(src, 'plain')
        obj = compile_plain(src, d, override.get(src))
        res = obj, object_sizes(obj)
        if src not in override:
            shared[('build', src)] = res
        return res
    objs = dict(zip(man['files'], pool.map(build, man['files'])))
    file_objs = []
    for src, funcs in man['files'].items():
        part = shared.get(('plain', src)) if src not in override else None
        if part is None:
            part = plain_file(src, funcs, *objs[src], facts)
            if src not in override:
                shared[('plain', src)] = part
        file_objs.append((src, part['robj']))
        for line in part['lines']:
            out(line)
        ok, total, pending, nfuncs = ok + part['ok'], total + part['total'], pending + part['pending'], nfuncs + part['nfuncs']
        entries += part['entries']
        problems += part['problems']
        known.update(part['known'])
        contents.update(part['contents'])
    # the data, as tools/verify_src.py checks it, from the recorded data facts and the game's recorded answers
    oracle = Oracle(facts)
    nrefs = len(entries)
    used = set()  # the data facts consulted (stale_facts)
    reached, pr = relocs.check_all_data(entries, facts_data_check(facts, contents, used),
                                        tables=(oracle.table_words, oracle.own_slot),
                                        anchors=(file_objs, {k: v for k, v in known.items() if isinstance(k, str)},
                                                 oracle.words_of))
    problems += pr
    splits = data_splits()
    problems += relocs.check_ownership(reached, splits)
    try:
        problems += relocs.check_consistency(entries, read, relocs.load_aliases(os.path.join(ROOT, 'config', 'symbol_aliases.txt')), known)
    except KeyError as e:
        problems.append(str(e))
    out('\n%d of %d matched functions are exact (from recorded facts); %d work-in-progress function(s) tracked' % (ok, total, pending))
    out('relocation targets: %d references in %d exact functions checked; %s'
        % (nrefs, nfuncs, 'all consistent' if not problems else '%d PROBLEM(S):' % len(problems)))
    out(data_coverage(reached, file_objs, len(entries) - nrefs, entries, splits))
    for pr in problems:
        out('  ' + pr)
    if not ltcg:
        return ok == total and not problems, problems
    # LTCG, as tools/verify_ltcg.py, including the reference check of the functions exact only under LTCG
    ref_entries, ref_problems, nref, ltcg_reached = [], [], 0, []
    ltcg_contents = {}  # what the data's pointers lead to, from the recorded data facts (check_recorded_data)

    def no_read(addr, n):
        if (addr, n) in ltcg_contents:
            return ltcg_contents[(addr, n)]
        raise KeyError('no recorded fact for %d bytes at %08X' % (n, addr))
    def build(src):
        d, plain = own_dir(src, 'ltcg'), objs[src][0]
        consts = [(op, struct.unpack('>d', bytes.fromhex(h))[0]) for op, h in facts['files'].get(src, {}).get('direct_constants', [])]
        lread, fs, _ = verify_ltcg.build_ltcg(override.get(src) or os.path.join(ROOT, src), plain, consts, d, env(),
                                              extra_flags=['/I' + os.path.dirname(os.path.join(ROOT, src))] + file_flags(src),
                                              deps=verify_ltcg.dependencies(src, plain, d, env(), man, override))
        return lread, fs, verify_ltcg.StaticNames(d, plain)
    lfiles = [src for src in man['files'] if ltcg_built(src)]  # a plain object has no LTCG build
    builds = dict(zip(lfiles, pool.map(build, lfiles)))
    for src in lfiles:
        funcs = man['files'][src]
        lread, fs, names = builds[src]
        syms = names.symbols
        file_entries = []
        for f in funcs:
            if not f.get('matching', True):
                continue
            ltcg_total += 1
            fe = facts['functions'].get(f['address'])
            lt = [a for a, n in fs if symbol_matches(f['symbol'], n)]
            if not fe or not lt:
                continue
            a = lt[0]
            nxt = [x for x, _ in fs if x > a]
            lw = verify_ltcg.words(lread(a, (nxt[0] if nxt else a + f['size'] + 64) - a))
            while lw and lw[-1] == 0:
                lw.pop()
            n = f['size'] // 4
            if len(lw) > n and fe['ltcg']['ends']:
                lw = lw[:n]
            exact = len(lw) == n and ltcg_hash(lw, a, fe['ltcg'].get('absolute_relocations', ())) == fe['ltcg']['sha']
            ltcg_ok += exact
            if exact and f.get('ltcg'):
                rec = fe['ltcg']
                cd2_refs = [(i, k, int(x, 16), op) for i, k, x, op in rec.get('refs', [])]
                floats = {k: bytes.fromhex(h) for k, h in rec.get('floats', {}).items()}
                e, pr = verify_ltcg.check_references(
                    verify_ltcg.references(lw, a), cd2_refs, syms, lread, no_read, src, f['symbol'],
                    cd2_bytes=lambda addr, k: floats.get('0x%08X:%d' % (addr, k)),
                    cd2_string=lambda addr, rec=rec, lread=lread: None, obj=names)
                # strings: compare the hash of our C string with the recorded one (the text is not stored)
                pr = [x for x in pr if 'string' not in x]
                for i, kind, addr, op in verify_ltcg.references(lw, a):
                    k = verify_ltcg.bisect.bisect_right([s_[0] for s_ in syms], addr) - 1
                    if k >= 0 and syms[k][1].startswith('??_C@'):
                        cd2_addr = dict(((j, kk), x) for j, kk, x, _ in cd2_refs).get((i, kind))
                        ours_s = verify_ltcg.cstring(lread, addr)
                        if cd2_addr is None or sha(ours_s or b'') != rec.get('strings', {}).get('0x%08X' % cd2_addr):
                            pr.append('%s %s+%X: string %s differs from CD2' % (src, f['symbol'], 4 * i, syms[k][1][:40]))
                ref_entries += e
                file_entries += e
                ref_problems += pr
                nref += 1
        # the data they reach, as tools/verify_ltcg.py checks it, from the recorded data facts
        data_entries = verify_ltcg.plain_names(file_entries, relocs.Obj(*objs[src]))
        n = len(data_entries)
        rf, pr = relocs.check_all_data(data_entries, facts_data_check(facts, ltcg_contents, used), extents=False)
        ref_entries += data_entries[n:]
        ref_problems += pr
        ltcg_reached += rf
    out('LTCG: %d of %d matched functions exact under LTCG (from recorded facts)' % (ltcg_ok, ltcg_total))
    ref_problems += relocs.check_extents(ltcg_reached, ref_entries)
    ref_problems += relocs.check_tables(ltcg_reached, oracle.table_words, oracle.own_slot)
    ref_problems += relocs.check_ownership(ltcg_reached, splits)
    ref_problems += stale_facts(facts, used)  # needs both parts: the LTCG-only functions' data was recorded too
    try:
        ref_problems += relocs.check_consistency(ref_entries, no_read, relocs.load_aliases(os.path.join(ROOT, 'config', 'symbol_aliases.txt')), known)
    except KeyError as e:
        ref_problems.append(str(e))
    out('LTCG relocation targets: %d references in %d LTCG-only functions checked, %d data symbols they reach; %s' % (
        len(ref_entries), nref, len(ltcg_reached), 'all consistent' if not ref_problems else '%d PROBLEM(S):' % len(ref_problems)))
    for pr in ref_problems:
        out('  ' + pr)
    problems = problems + ref_problems
    return ok == total and not problems and ltcg_ok == ltcg_total, problems


def self_test():
    """Plant errors that the byte comparison cannot see and require facts-mode verification to catch each one."""
    tmp = work_dir('facts_selftest_')
    # a plant is caught when it adds a problem to the unmodified repository's (whose open problems, if any, do not
    # count); a plant exact only under LTCG must add one about its own file, as the baseline has no LTCG check
    shared = {}  # the builds and plain checks of the files a case leaves alone, kept from one case to the next
    passed, base = verify(ltcg=False, out=lambda m: None, shared=shared)
    base = set(base)

    def added(problems, src=None):
        return [p for p in problems if p not in base and (src is None or src in p)]
    cases = [
        ('a call to the wrong function', 'src/VFX/cAmbientVFXSpawner.cpp',
         '        CalcRandInitSpawnTime();\n    }\n', '        CalcRandRespawnTime();\n    }\n', 'OnBecomeRelevantToPlayer'),
        ('a different string', 'src/AI/cChaseBehaviour.cpp', '"cChaseBehaviour"', '"cChaseBehaviouR"', None),
        ('a different float constant', 'src/AI/cChaseBehaviour.cpp', '5.0f', '6.0f', None),
        # exact only under LTCG: caught by the LTCG reference check alone
        ('LTCG-only: a different constant', 'src/VFX/cAmbientVFXSpawner.cpp', '(unsigned int)(f * -1000.0f)',
         '(unsigned int)(f * -2000.0f)', 'void cAmbientVFXSpawner::CalcRandInitSpawnTime()'),
    ]
    ok = True
    for what, src, old, new, near in cases:
        text = open(os.path.join(ROOT, src), newline='').read()
        nl = '\r\n' if '\r\n' in text else '\n'  # a checkout may have either line ending
        old, new = old.replace('\n', nl), new.replace('\n', nl)
        at = text.index(near) if near else 0
        if text.find(old, at) < 0:
            print('self-test %-30s cannot plant it (update the self-test)' % what)
            ok = False
            continue
        i = text.index(old, at)
        path = os.path.join(tmp, os.path.basename(src))
        open(path, 'w', newline='').write(text[:i] + new + text[i + len(old):])
        lt = what.startswith('LTCG')
        _, problems = verify(override={src: path}, ltcg=lt, out=lambda m: None, shared=shared)
        caught = bool(added(problems, src if lt else None))
        ok &= caught
        print('self-test %-30s %s' % (what, 'caught' if caught else 'NOT CAUGHT'))
    # a vtable slot declared as a plain member function: the bytes match either way, so only the vtable fact catches
    # it. The copy of the source sits next to a changed copy of its header, which its quoted #include finds first.
    what = 'a virtual declared non-virtual'
    src, hdr = 'src/Vehicle/cVehicleController.cpp', 'VEHICLE_CONTROL/cHelicopterController.h'
    d = tempfile.mkdtemp(dir=tmp)
    text = open(os.path.join(ROOT, 'include', hdr), newline='').read()
    cls = text.find('class cVehicleController ')
    at = text.find('virtual void AssignVehicle(', cls) if cls >= 0 else -1  # its own declaration, not an override's
    if at < 0:
        print('self-test %-30s cannot plant it (update the self-test)' % what)
        ok = False
    else:
        os.makedirs(os.path.join(d, os.path.dirname(hdr)))
        open(os.path.join(d, hdr), 'w', newline='').write(text[:at] + text[at + len('virtual '):])
        path = os.path.join(d, os.path.basename(src))
        shutil.copy(os.path.join(ROOT, src), path)
        _, problems = verify(override={src: path}, ltcg=False, out=lambda m: None, shared=shared)
        caught = any('R13' in pr for pr in added(problems))
        ok &= caught
        print('self-test %-30s %s' % (what, 'caught' if caught else 'NOT CAUGHT'))
    # data the byte comparison cannot see (tools/verify_src.py DATA_PLANTS): a changed initial value, swapped slots
    for k, (what, src, hdr, old, new, user, *src_edit) in enumerate(DATA_PLANTS):
        path = plant_copy(os.path.join(tmp, 'data_%d' % k), src, hdr, old, new, *src_edit)
        if path is None:
            print('self-test %-30s cannot plant it in %s (update the self-test)' % (what, hdr))
            ok = False
            continue
        _, problems = verify(override={src: path}, ltcg=False, out=lambda m: None, shared=shared)
        caught = bool(added(problems))
        ok &= caught
        print('self-test %-30s %s' % (what, 'caught' if caught else 'NOT CAUGHT'))
    print('self-test %-30s %s' % ('the unmodified repository', 'accepted' if passed else 'WRONGLY REJECTED'))
    return ok and passed


def main():
    if len(sys.argv) >= 3 and sys.argv[1] == 'record':
        check_toolchain()
        r, entry = pe_reader(open(sys.argv[2], 'rb').read())
        if entry != EXPECTED_ENTRY:
            sys.exit('not the title-update build')
        f = record(r)
        print('recorded facts for %d functions in %s' % (len(f['functions']), os.path.relpath(FACTS, ROOT)))
    elif len(sys.argv) == 2 and sys.argv[1] == 'verify':
        check_toolchain()
        sys.exit(0 if verify()[0] else 1)
    elif len(sys.argv) == 2 and sys.argv[1] == '--self-test':
        check_toolchain()
        sys.exit(0 if self_test() else 1)
    else:
        print(__doc__)
        sys.exit(2)


if __name__ == '__main__':
    main()
