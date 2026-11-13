"""Relocation-target verification: does matched code reference the same functions and data as Crackdown 2?

Byte comparison masks relocated fields, so a call to the wrong function or a load from the wrong global would still
"match". This module resolves every relocation of a matched function to the CD2 address it stands for and checks that
the references are consistent across the whole repository:
  - REL24 (b/bl):          target = CD2 instruction address + displacement
  - REFHI/REFLO (lis + addi/lwz/stw/lfs/...): CD2 high half (from the lis) + low half; minus our addend (PAIR record)
Rules (check_consistency):
  - one name, one address. Exceptions, checked by CONTENT instead: float/double constants (__real@...) and string
    literals (??_C@...), which may legitimately exist at several addresses;
  - one address, one name, unless config/symbol_aliases.txt declares the alias (e.g. identical vtables folded by the
    linker);
  - functions of our own manifest: their name must resolve to their manifest address (a name with internal linkage
    to the manifest address in the same file: every file has its own copy, see known_key);
  - names that embed an address (Ext_82954E48, sub_82954E48, fn_82954E48) must resolve to that address;
  - names with internal linkage (header statics, their initializers) are one name, one address per file, and within a
    file an address one of them resolves to has no other name. One exception, listed by name in LTCG_SHARED_COPIES
    and checked by CONTENT (identical_copies): g_GlobalConstants may resolve to the file's own copy and to 0x830ACBD8,
    the copy LTCG's inlined cClass::HasAncestor reads in every object, when both hold identical, not all-zero bytes;
  - local (per-object) symbols ('$...', '.rdata' section symbols) are only checked for content where possible.
Data (check_data, check_extents): the data a matched function references and our object defines (a vtable, an
initialized global, a constant table) must equal CD2's at the resolved address, byte for byte outside its relocations;
each address it holds (a vtable slot) resolves to CD2's word there and joins the checks above as a 'data pointer'; a
COMDAT's extent (a vtable's length) must not run over another referenced symbol.
"""
import bisect, collections, re, struct

ADDR32, REL24, REFHI, REFLO, PAIR = 0x02, 0x06, 0x10, 0x11, 0x12
CODE, UNINITIALIZED, COMDAT = 0x20, 0x80, 0x1000
WEAK_EXTERNAL = 105
EMBEDDED = re.compile(r'(?:Ext|sub|fn|loc|unk|off|dword)_([0-9A-Fa-f]{8})\b')


class Obj:
    """COFF object with the full symbol table (indices as stored) and per-section relocations. sizes: {symbol: size}
    of its data (tools/cvtypes.py, from a /Z7 build of the same source), which gives data_symbol exact extents."""

    def __init__(self, path, sizes=None):
        self.sizes = sizes or {}
        d = self.data = open(path, 'rb').read()
        mach, nsec, _, symptr, nsym, opt, _ = struct.unpack('<HHIIIHH', d[:20])
        self.sections = []
        for i in range(nsec):
            o = 20 + opt + i * 40
            name, vs, va, size, praw, preloc, plin, nrel, nlin, ch = struct.unpack('<8sIIIIIIHHI', d[o:o + 40])
            relocs = [struct.unpack_from('<IIH', d, preloc + r * 10) for r in range(nrel)]
            self.sections.append(dict(name=name.rstrip(b'\0').decode('latin-1'), data=d[praw:praw + size] if praw else b'',
                                      relocs=relocs, ch=ch, size=size))
        strtab = symptr + nsym * 18
        self.symbols, i, weak = {}, 0, {}
        while i < nsym:
            o = symptr + i * 18
            raw, val, sec, typ, cls, naux = struct.unpack_from('<8sIhHBB', d, o)
            name = (d[strtab + struct.unpack('<I', raw[4:])[0]:].split(b'\0', 1)[0] if raw[:4] == b'\0\0\0\0'
                    else raw.rstrip(b'\0')).decode('latin-1')
            self.symbols[i] = dict(name=name, value=val, sec=sec, type=typ, cls=cls)
            if cls == WEAK_EXTERNAL and naux:
                weak[i] = struct.unpack_from('<I', d, o + 18)[0]  # its auxiliary record's TagIndex: the default
            i += 1 + naux
        # a weak external stands for its default unless another object defines the name: MSVC makes a class's vector
        # deleting destructor (??_E) a weak alias of its scalar one (??_G) when nothing needs the vector form, so a
        # vtable slot or an adjustor thunk naming ??_E reaches ??_G. CD2's own words decide if a strong one existed.
        for i, tag in weak.items():
            if tag in self.symbols:
                self.symbols[i]['weak'] = self.symbols[i]['name']
                self.symbols[i]['name'] = self.symbols[tag]['name']
        # names this object defines with internal linkage (STATIC storage class): every file has its own copy
        self.internal = {s['name'] for s in self.symbols.values() if s['cls'] == 3 and s['sec'] > 0}

    def functions(self):
        """{name: (section index, offset, size)} for function symbols defined in code sections (worked out once: every
        relocation lookup asks for it)"""
        if getattr(self, '_functions', None) is None:
            self._functions = self._find_functions()
        return self._functions

    def _find_functions(self):
        out, by_sec = {}, collections.defaultdict(list)
        for s in self.symbols.values():
            if s['sec'] > 0 and s['cls'] in (2, 3) and self.sections[s['sec'] - 1]['ch'] & 0x20 \
                    and not s['name'].startswith(('.', '$')):
                by_sec[s['sec']].append(s)
        for sec, lst in by_sec.items():
            lst.sort(key=lambda s: s['value'])
            data = self.sections[sec - 1]['data']
            for j, s in enumerate(lst):
                end = lst[j + 1]['value'] if j + 1 < len(lst) else len(data)
                out[s['name']] = (sec, s['value'], end - s['value'])
        return out

    def relocations(self, fname):
        """[(offset in function, type, symbol name, addend)] for one function"""
        sec, start, size = self.functions()[fname]
        out, rel = [], self.sections[sec - 1]['relocs']
        for k, (off, si, t) in enumerate(rel):
            if t == PAIR or not start <= off < start + size:
                continue
            addend = 0
            if k + 1 < len(rel) and rel[k + 1][2] == PAIR:
                addend = rel[k + 1][1]
                addend = addend - (1 << 32) if addend & 0x80000000 else addend
            out.append((off - start, t, self.symbols[si]['name'], addend))
        return out

    def symbol_bytes(self, name, n):
        """first n bytes of a data symbol defined in this object (for content checks), or None"""
        for s in self.symbols.values():
            if s['name'] == name and s['sec'] > 0:
                data = self.sections[s['sec'] - 1]['data']
                return data[s['value']:s['value'] + n]
        return None

    def data_names(self, with_pointers=False):
        """The names of the data this object defines (not code, section symbols or labels); with_pointers: only those
        in a section with relocations"""
        return [s['name'] for s in self.symbols.values() if s['sec'] > 0 and not s['name'].startswith(('.', '$'))
                and not self.sections[s['sec'] - 1]['ch'] & CODE
                and (not with_pointers or self.sections[s['sec'] - 1]['relocs'])]

    def data_symbol(self, name):
        """The data of a symbol this object defines outside code: dict(data (None if uninitialized), size, comdat,
        exact, relocations [(offset, type, target symbol, addend)]), or None for code, undefined, section and repeated
        names. Its extent is its size from `sizes`, else it runs to the next symbol of its section or the section's
        end; `exact` says whether that is its size (a COMDAT holds one symbol). An ADDR32's addend is the word it
        patches."""
        if not hasattr(self, '_defined'):
            self._defined, self._data, self._starts = collections.defaultdict(list), {}, collections.defaultdict(set)
            for s in self.symbols.values():
                if s['sec'] > 0:
                    self._defined[s['name']].append(s)
                    if not s['name'].startswith('.'):
                        self._starts[s['sec']].add(s['value'])
            self._starts = {k: sorted(v) for k, v in self._starts.items()}
        if name not in self._data:
            self._data[name] = self._data_symbol(name)
        return self._data[name]

    def _data_symbol(self, name):
        hits = self._defined.get(name, [])
        if len(hits) != 1 or name.startswith('.'):
            return None
        s = hits[0]
        sec = self.sections[s['sec'] - 1]
        if sec['ch'] & CODE:
            return None
        start, sizes = s['value'], getattr(self, 'sizes', {})
        if name in sizes:
            end, exact = start + sizes[name], True
        else:
            starts = self._starts.get(s['sec'], [])
            k = bisect.bisect_right(starts, start)
            end, exact = (starts[k] if k < len(starts) else sec['size']), bool(sec['ch'] & COMDAT)
        data = sec['data'][start:end] if sec['data'] and not sec['ch'] & UNINITIALIZED else None
        rels = []
        for k, (off, si, t) in enumerate(sec['relocs']):
            if t == PAIR or not start <= off < end:
                continue
            if t == ADDR32 and data is not None and off + 4 <= end:
                addend = struct.unpack_from('>i', data, off - start)[0]
            else:
                addend = 0
            rels.append((off - start, t, self.symbols[si]['name'], addend))
        return dict(data=data, size=end - start, comdat=bool(sec['ch'] & COMDAT), exact=exact, relocations=rels)

    def local_address_offset(self, fname, off, symbol, addend=0):
        """Resolve an ADDR32 to a label inside this function; reject other uses for now."""
        sec, start, size = self.functions()[fname]
        if off < 0 or off % 4 or off + 4 > size:
            raise ValueError('unaligned or out-of-range ADDR32 site')
        # the symbol the relocation itself names (by index): label names such as $LN5 repeat in every function of an
        # object that has a jump table, so a lookup by name could pick another function's label
        hit = [self.symbols.get(si) for o, si, t in self.sections[sec - 1]['relocs'] if o == start + off and t == ADDR32]
        if len(hit) != 1 or hit[0] is None or hit[0]['name'] != symbol or hit[0]['sec'] != sec:
            raise ValueError('ADDR32 must reference a label in the same function section')
        data = self.sections[sec - 1]['data']
        embedded_addend = struct.unpack_from('>i', data, start + off)[0]
        dest = hit[0]['value'] + embedded_addend + addend - start
        if dest % 4 or not 0 <= dest < size:
            raise ValueError('ADDR32 destination is not an aligned label inside the function')
        return dest


def _sx16(v):
    return v - 0x10000 if v & 0x8000 else v


def resolve(obj, fname, cd2_code, cd2_va):
    """Resolve every relocation of compiled function fname against CD2's bytes at cd2_va.
    Returns (resolutions [(symbol, address, kind, offset)], problems [str])."""
    rels = obj.relocations(fname)
    words = struct.unpack('>%dI' % (len(cd2_code) // 4), cd2_code[:len(cd2_code) // 4 * 4])
    out, problems = [], []
    his = collections.defaultdict(list)  # symbol -> [(offset, register, ha)]
    for off, t, sym, add in sorted(rels):
        if off // 4 >= len(words):
            problems.append('%s+%X: relocation beyond the CD2 function' % (fname, off))
            continue
        w = words[off // 4]
        if t == ADDR32:
            try:
                dest = obj.local_address_offset(fname, off, sym, add)
            except ValueError as e:
                problems.append('%s+%X: %s' % (fname, off, e))
                continue
            expected = (cd2_va + dest) & 0xFFFFFFFF
            if w != expected:
                problems.append('%s+%X: ADDR32 %s targets %08X but CD2 targets %08X'
                                % (fname, off, sym, expected, w))
            out.append((sym, w, 'local address', off))
        elif t == REL24:
            if w >> 26 != 18:
                problems.append('%s+%X: REL24 on a non-branch CD2 instruction %08X' % (fname, off, w))
                continue
            disp = w & 0x03FFFFFC
            disp = disp - 0x04000000 if disp & 0x02000000 else disp
            tgt = disp if w & 2 else cd2_va + off + disp
            out.append((sym, (tgt - add) & 0xFFFFFFFF, 'call' if w & 1 else 'branch', off))
        elif t == REFHI:
            his[sym].append((off, (w >> 21) & 31, w & 0xFFFF))
        elif t == REFLO:
            base = (w >> 16) & 31
            cands = [h for h in his[sym] if h[0] < off and h[1] == base] or [h for h in his[sym] if h[0] < off] or his[sym]
            if not cands:
                problems.append('%s+%X: REFLO for %s without a matching REFHI' % (fname, off, sym))
                continue
            ha = cands[-1][2]
            addr = ((ha << 16) + _sx16(w & 0xFFFF)) & 0xFFFFFFFF
            out.append((sym, (addr - add) & 0xFFFFFFFF, 'data', off))
        else:
            problems.append('%s+%X: unhandled relocation type %02X for %s' % (fname, off, t, sym))
    # a REFHI whose symbol never gets a REFLO cannot be checked; report it
    for sym, lst in his.items():
        if not any(r[0] == sym for r in out):
            problems.append('%s: REFHI for %s has no REFLO to complete the address' % (fname, sym))
    return out, problems


def mask_words(b, offsets):
    """b with the word at each offset cleared: the relocated words of data, compared as pointers instead"""
    b = bytearray(b)
    for off in offsets:
        b[off:off + 4] = bytes(len(b[off:off + 4]))
    return bytes(b)


def data_pointers(src, sym, d, words, obj):
    """The addresses data d (Obj.data_symbol of sym) holds, each resolved through CD2's word at its place (words:
    {offset: word}), as check_consistency entries [(file, data symbol, target, address, 'data pointer', offset, obj)].
    Returns (entries, problems)."""
    entries, problems = [], []
    for off, t, target, addend in d['relocations']:
        if t != ADDR32:
            problems.append('%s %s+%X: unhandled data relocation type %02X for %s' % (src, sym, off, t, target))
        elif off not in words:
            problems.append('%s %s+%X: pointer to %s runs past the data' % (src, sym, off, target))
        else:
            entries.append((src, sym, target, (words[off] - addend) & 0xFFFFFFFF, 'data pointer', off, obj))
    return entries, problems


def content_problem(src, sym, addr, ours, theirs):
    """None if the masked bytes agree, else the problem (where and how many bytes, never CD2's values)"""
    if ours == theirs:
        return None
    diff = [i for i in range(max(len(ours), len(theirs))) if ours[i:i + 1] != theirs[i:i + 1]]
    return '%s %s at %08X: %d of %d byte(s) outside its relocations differ from CD2 (first at +%X)' % (
        src, sym, addr, len(diff), len(ours), diff[0])


def check_data(src, sym, addr, d, read, obj):
    """The data d (Obj.data_symbol) of sym, resolved to CD2 address addr: its bytes outside relocations must equal
    CD2's, and each address it holds resolves through CD2's word there. Returns (entries for check_consistency,
    problems)."""
    offsets = sorted({off for off, _, _, _ in d['relocations']})
    if d['data'] is None and not offsets:
        if not d['exact']:
            return [], []  # its size is unknown: only what follows (check_extents) can be checked
        try:
            p = zero_problem(src, sym, addr, d['size'], read(addr, d['size']))
        except ValueError:
            return [], []  # CD2 has no initialized data there either
        return [], [p] if p else []
    problems = []
    try:
        theirs = read(addr, d['size'])
    except ValueError:
        return [], ['%s %s at %08X: initialized data, but CD2 has no initialized data there' % (src, sym, addr)]
    if d['data'] is not None:
        p = content_problem(src, sym, addr, mask_words(d['data'], offsets), mask_words(theirs, offsets))
        if p:
            problems.append(p)
    words = {off: struct.unpack_from('>I', theirs, off)[0] for off in offsets if off + 4 <= len(theirs)}
    entries, pr = data_pointers(src, sym, d, words, obj)
    return entries, problems + pr


def zero_problem(src, sym, addr, size, theirs):
    """Uninitialized data (zero at load) where CD2 holds initialized bytes: None if CD2's are zero too"""
    nonzero = [i for i, x in enumerate(theirs) if x]
    if not nonzero:
        return None
    return '%s %s at %08X: zero-initialized, but CD2 initializes %d of its %d byte(s) (first at +%X)' % (
        src, sym, addr, len(nonzero), size, nonzero[0])


def string_bytes(obj, name):
    """The bytes of string literal `name` as obj defines it: its whole COMDAT (a wide string's NULs included), else
    up to its first NUL within 64 bytes; None if obj does not define it"""
    d = obj.data_symbol(name) if hasattr(obj, 'data_symbol') else None
    if d is not None and d['data']:
        return d['data']
    ours = obj.symbol_bytes(name, 64)
    if ours is None:
        return None
    return ours[:ours.find(b'\0') + 1] if b'\0' in ours else ours


def data_key(f, sym, obj):
    """The identity of a datum: a name with internal linkage is each file's own"""
    return (f if is_local(sym) or sym in getattr(obj, 'internal', ()) else '', sym)


def data_reached(entries):
    """The data the resolved references reach (of matched functions, or the pointers found in data), once per copy:
    [(file, symbol, address, obj, data (Obj.data_symbol))]. Strings and float constants are compared by
    check_consistency; a COMDAT several files emit is checked once per distinct copy (identical copies are the same
    data)."""
    out, seen = [], set()
    for f, fn, sym, addr, kind, off, obj in entries:
        if kind in ('call', 'branch', 'local address') or is_constant(sym) or is_string(sym):
            continue
        d = obj.data_symbol(sym) if hasattr(obj, 'data_symbol') else None
        if d is None:
            continue
        key = data_key(f, sym, obj) + (addr, d['size'], d['data'], tuple(d['relocations']))
        if key not in seen:
            seen.add(key)
            out.append((f, sym, addr, obj, d))
    return out


def scope(name):
    """The class (or namespace) a decorated name belongs to: 'cBody@PHYSICS' for ??_7cBody@PHYSICS@@6B@,
    ?Init@cBody@PHYSICS@@UAA... and ??_GcBody@PHYSICS@@UAAPAXI@Z; None for other names"""
    if name.startswith(('??_7', '??_G', '??_E')):
        rest = name[4:]
    elif name.startswith(('??0', '??1')):
        rest = name[3:]
    elif name.startswith('?') and not name.startswith('??'):
        rest = name[1:].split('@', 1)[1] if '@' in name[1:] else ''
    else:
        return None
    return rest.split('@@', 1)[0] or None


def anchor_data(file_objs, known, words_of, located, table_words=None):
    """Vtables no matched function references, located through the matched functions they point at (a class with
    only RetClassName matched): the CD2 words holding a matched function's address (words_of(address), from the
    game's tables), each minus the slot's offset, vote for the table's address. Only the class's own functions vote: an
    inherited one sits in every derived class's table too, and would vote a base's table onto a derived one's (or
    one CD2 never installs onto its derived class's). The address must be the one candidate, or win by more votes;
    a tie goes to the one candidate whose CD2 table (table_words) is as long as ours. file_objs: [(file, obj)];
    known: {name: manifest address}; located: data_key()s of the data already reached. Returns [(file, symbol,
    address, obj, data)]."""
    out = []
    for f, obj in file_objs:
        for name in obj.data_names(with_pointers=True):
            own = scope(name) if name.startswith('??_7') else None
            if own is None or data_key(f, name, obj) in located:
                continue
            d = obj.data_symbol(name)
            if d is None:
                continue
            votes = collections.Counter()
            for off, t, target, addend in d['relocations']:
                if t == ADDR32 and not addend and target in known and scope(target) == own:
                    for w in words_of(known[target]):
                        votes[(w - off) & 0xFFFFFFFF] += 1
            if not votes:
                continue
            top = max(votes.values())
            best = [a for a, n in votes.items() if n == top]
            if len(best) > 1 and table_words:
                best = [a for a in best if table_words(a) == d['size'] // 4]
            if len(best) == 1:
                out.append((f, name, best[0], obj, d))
    return out


def check_extents(reached, entries):
    """A datum whose size is known (a COMDAT such as a vtable, or one sized by tools/cvtypes.py) must end before the
    next symbol the references reach: a longer vtable declares a virtual CD2's class does not have, a larger global
    covers another. reached: data_reached()."""
    named = collections.defaultdict(set)  # address -> the names referenced there
    for f, fn, sym, addr, kind, off, obj in entries:
        if kind not in ('call', 'branch', 'local address') and not is_local(sym):
            named[addr].add(sym)
    for f, sym, addr, obj, d in reached:
        named[addr].add(sym)
    starts = sorted(named)
    problems, seen = [], set()
    for f, sym, addr, obj, d in reached:
        if not d['exact'] or (sym, addr, d['size']) in seen:
            continue
        seen.add((sym, addr, d['size']))
        k = bisect.bisect_right(starts, addr)
        if k < len(starts) and starts[k] < addr + d['size'] and named[starts[k]] - {sym}:
            problems.append('%s %s at %08X: its %X bytes run over %s at %08X (+%X)' % (
                f, sym, addr, d['size'], ', '.join(sorted(named[starts[k]] - {sym}))[:80], starts[k], starts[k] - addr))
    return problems


def check_tables(reached, table_words, own_slot):
    """A table of code pointers (a vtable) must not have fewer slots than CD2's at its address: table_words(address)
    is the number of words in CD2's run of code pointers there, up to the next address code builds (None where CD2 has
    no such table). That count is a lower bound only (code builds addresses inside some tables), so a longer table of
    ours is left to check_extents, which needs the next table located. Fewer counts only with evidence that the words
    after ours are still this table, since a table no code installs may follow: own_slot(file, word address) says the
    function CD2's word there points at belongs to the file (config/splits.txt), the next datum located must not start
    there, and the object must define no other table of the class that is not located (it could be the one that
    follows)."""
    starts = {addr for f, sym, addr, obj, d in reached}
    located = {data_key(f, sym, obj) for f, sym, addr, obj, d in reached}
    problems, seen = [], set()
    for f, sym, addr, obj, d in reached:
        if not d['exact'] or not d['relocations'] or d['size'] % 4 or (sym, addr) in seen:
            continue
        seen.add((sym, addr))
        n, theirs = d['size'] // 4, table_words(addr)
        if theirs is None or n >= theirs:
            continue
        cls = sym.split('@@6B', 1)[0] + '@@6B' if sym.startswith('??_7') else None
        if addr + 4 * n in starts or not own_slot(f, addr + 4 * n) or (cls and any(
                o.startswith(cls) and o != sym and data_key(f, o, obj) not in located for o in obj.data_names())):
            continue
        problems.append('%s %s at %08X: %d slots, but CD2\'s table there runs on (%d words before the next address '
                        'code builds) and its word after ours points at a function of this file: CD2\'s class has '
                        'virtuals ours lacks' % (f, sym, addr, n, theirs))
    return problems


DATA_RANGES = ('data', 'bss', 'rdata')


def check_ownership(reached, splits):
    """Every located datum a file defines belongs to that file in CD2 (config/splits.txt: its data, bss and rdata
    ranges): it lies wholly inside one of the file's ranges, and inside no other file's, unless the file lists its
    address as folded (one copy the linker shares between files, such as an identical constant table). COMDAT data
    (vtables, strings) is the linker's to place, and a file without data ranges yet is checked only for lying in
    another's. splits: check_integrity.load_splits()."""
    ranges = sorted((a, b, f) for f, s in splits.items() for kind in DATA_RANGES for a, b in s.get(kind, ()))
    starts = [a for a, b, f in ranges]
    problems, seen = [], set()
    for f, sym, addr, obj, d in reached:
        if d['comdat'] or (f, sym, addr) in seen or addr in splits.get(f, {}).get('folded', ()):
            continue
        seen.add((f, sym, addr))
        end = addr + (d['size'] if d['exact'] else 1)
        k = bisect.bisect_right(starts, addr) - 1
        holder = ranges[k] if k >= 0 and ranges[k][0] <= addr < ranges[k][1] else None
        if holder and holder[2] != f:
            problems.append('%s %s at %08X lies in %s\'s data range [%08X, %08X) in config/splits.txt: the wrong file '
                            'defines it, or the linker shares one copy between files (list it as folded)'
                            % (f, sym, addr, holder[2], holder[0], holder[1]))
        elif any(splits.get(f, {}).get(kind) for kind in DATA_RANGES) and (holder is None or end > holder[1]):
            problems.append('%s %s at %08X: %s the file\'s data ranges in config/splits.txt'
                            % (f, sym, addr, 'outside' if holder is None else 'runs past the end of'))
    return problems


def check_all_data(entries, check, anchors=None, tables=None, extents=True):
    """Every datum the references reach, the data their pointers lead to in turn, and (anchors) the data located
    through the matched functions it points at, each checked by check(file, symbol, address, obj, data) -> (pointer
    entries, problems): check_data against CD2, or the recorded facts. entries (the resolved references of matched
    functions) receives the pointers, for check_consistency. anchors: (file_objs, known, words_of) for anchor_data;
    tables: (table_words, own_slot) for check_tables; extents: run check_extents (a caller that gathers several calls'
    data runs it once over all). Returns (reached, problems)."""
    reached, problems, seen = [], [], set()

    def new(items):
        out = []
        for item in items:
            f, sym, addr, obj, d = item
            key = data_key(f, sym, obj) + (addr, d['size'], d['data'], tuple(d['relocations']))
            if key not in seen:
                seen.add(key)
                out.append(item)
        return out
    todo = new(data_reached(entries))
    while todo:
        reached += todo
        found = []
        for f, sym, addr, obj, d in todo:
            e, pr = check(f, sym, addr, obj, d)
            entries += e
            problems += pr
            found += e
        todo = new(data_reached(found))  # data the pointers in data lead to
        if not todo and anchors:
            todo = new(anchor_data(*anchors, located={k[:2] for k in seen}, table_words=tables[0] if tables else None))
            anchors = None
    if extents:
        problems += check_extents(reached, entries)
    if tables:
        problems += check_tables(reached, *tables)
    return reached, problems


def is_constant(name):
    return name.startswith('__real@')


def is_string(name):
    return name.startswith('??_C@')


def is_local(name):
    return name.startswith(('$', '.'))


def known_key(src, name, obj):
    """The key of a matched function in check_consistency's `known` map: the name, or (file, name) when the name has
    internal linkage in obj, since every file that defines it (a header static's at-exit destructor) has its own copy
    at its own address."""
    return (src, name) if name in getattr(obj, 'internal', ()) else name


# The one known case of identical_copies, by name: {internal data name: the CD2 copy LTCG's inlined code reads}.
# Fun_Runtime::g_GlobalConstants (fun_runtime/class.h) is a static in a header, so every object has its own copy; LTCG
# inlined cClass::HasAncestor from the one COMDAT the linker kept, so every IsA reads that object's copy at 0x830ACBD8,
# while each file's own code (its header constants' initializers) reads its own copy. Add a name only with that
# evidence: anything not listed here keeps the rule one name, one address per file.
LTCG_SHARED_COPIES = {'g_GlobalConstants': 0x830ACBD8, '?g_GlobalConstants@Fun_Runtime@@3UtGlobalConstants@1@A': 0x830ACBD8}


def identical_copies(obj, sym, addrs, read):
    """Whether the several CD2 addresses one file's internal name resolves to are the file's own copy of a datum
    LTCG_SHARED_COPIES lists plus the copy LTCG's inlined code reads: exactly two addresses, one of them the listed
    one, holding identical bytes, not all zero, over the datum's exact size. Any other name, a third address, another
    shared address or a copy that differs is still a problem."""
    shared = LTCG_SHARED_COPIES.get(sym)
    if shared is None or len(addrs) != 2 or shared not in addrs:
        return False
    if is_local(sym) or sym not in getattr(obj, 'internal', ()) or not hasattr(obj, 'data_symbol'):
        return False
    d = obj.data_symbol(sym)
    if not d or not d['exact'] or d['size'] < 8:
        return False
    try:
        copies = {bytes(read(a, d['size'])) for a in addrs}
    except (ValueError, KeyError):
        return False
    return len(copies) == 1 and any(next(iter(copies)))


def check_consistency(entries, read, aliases, known):
    """entries: [(file, function, symbol, address, kind, offset, obj)]; read(va, n) -> CD2 bytes;
    aliases: {address: set(names)} declared in config/symbol_aliases.txt; known: {known_key(): address} from the
    manifest. Returns [problem strings]."""
    problems = []
    by_name = collections.defaultdict(set)
    by_addr = collections.defaultdict(set)
    by_file_addr = collections.defaultdict(set)  # (file, address) -> names, to check the internal names of a file
    where = collections.defaultdict(list)
    objs = {}  # an internal name's key -> the object defining it, for identical_copies
    for f, fn, sym, addr, kind, off, obj in entries:
        if kind == 'local address':
            continue  # validated against this function's label offset by resolve/facts.verify
        if is_constant(sym):
            hexval = sym.split('@', 1)[1]
            want = bytes.fromhex(hexval)
            got = read(addr, len(want))
            if got != want:
                problems.append('%s %s+%X: constant %s but CD2 holds %s at %08X' % (f, fn, off, sym, got.hex(), addr))
            continue
        if is_string(sym):
            ours = string_bytes(obj, sym)
            if ours is not None and read(addr, len(ours)) != ours:
                problems.append('%s %s+%X: string %s differs from CD2 at %08X' % (f, fn, off, sym[:40], addr))
            continue
        local = is_local(sym) or sym in getattr(obj, 'internal', ())
        key = (f, sym) if local else sym
        if local:
            objs.setdefault(key, obj)
        by_name[key].add(addr)
        where[key].append((addr, '%s+%X' % (fn[:40], off)))
        if not local:
            by_addr[addr].add(sym)
        if not is_local(sym):
            by_file_addr[(f, addr)].add(sym)
        m = EMBEDDED.search(sym)
        if m and int(m.group(1), 16) != addr:
            problems.append('%s %s+%X: %s names address %s but resolves to %08X' % (f, fn, off, sym, m.group(1), addr))
        if key in known and known[key] != addr:
            problems.append('%s %s+%X: %s is matched at %08X (manifest) but this reference resolves to %08X'
                            % (f, fn, off, sym, known[key], addr))
    def site(key, addr):  # the first reference that resolves key to addr
        return next((s for a, s in where[key] if a == addr), 'manifest')
    for key, addrs in by_name.items():
        if len(addrs) > 1 and not (isinstance(key, tuple) and identical_copies(objs[key], key[1], addrs, read)):
            problems.append('%s resolves to several addresses: %s'
                            % (key if isinstance(key, str) else '%s in %s' % (key[1], key[0]),
                               ', '.join('%08X (%s)' % (a, site(key, a)) for a in sorted(addrs)[:8])))
    matched = collections.defaultdict(set)  # address -> the external names of the manifest's functions there
    for key, addr in known.items():
        if isinstance(key, str):
            matched[addr].add(key)
    for addr, names in by_addr.items():
        names = names | matched.get(addr, set())
        if len(names) > 1 and not names <= aliases.get(addr, set()):
            undeclared = sorted(names - aliases.get(addr, set()))
            problems.append('%08X is referenced under several names: %s%s (declare in config/symbol_aliases.txt if the '
                            'linker really merged them)' % (
                                addr, ', '.join('%s (%s)' % (n, site(n, addr)) for n in undeclared[:12]),
                                ' and %d more' % (len(undeclared) - 12) if len(undeclared) > 12 else ''))
    # an internal name is not in by_addr (other files have their own copy), so check it against the file's other names
    internal = {sym for f, fn, sym, addr, kind, off, obj in entries if sym in getattr(obj, 'internal', ())}
    for (f, addr), names in by_file_addr.items():
        if len(names) > 1 and names & internal and not names <= aliases.get(addr, set()):
            problems.append('%s: %08X is referenced under several names: %s' % (f, addr, ', '.join(sorted(names))))
    return problems


def load_aliases(path):
    """config/symbol_aliases.txt: '<address> <name> <name> ... # reason' per line"""
    out = {}
    try:
        for line in open(path):
            body = line.split('#', 1)[0].split()
            if len(body) >= 3:
                out[int(body[0], 16)] = set(body[1:])
    except FileNotFoundError:
        pass
    return out
