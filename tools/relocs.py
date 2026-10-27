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
  - functions of our own manifest: their name must resolve to their manifest address;
  - names that embed an address (Ext_82954E48, sub_82954E48, fn_82954E48) must resolve to that address;
  - local (per-object) symbols ('$...', '.rdata' section symbols) are only checked for content where possible.
"""
import collections, re, struct

ADDR32, REL24, REFHI, REFLO, PAIR = 0x02, 0x06, 0x10, 0x11, 0x12
EMBEDDED = re.compile(r'(?:Ext|sub|fn|loc|unk|off|dword)_([0-9A-Fa-f]{8})\b')


class Obj:
    """COFF object with the full symbol table (indices as stored) and per-section relocations."""

    def __init__(self, path):
        d = self.data = open(path, 'rb').read()
        mach, nsec, _, symptr, nsym, opt, _ = struct.unpack('<HHIIIHH', d[:20])
        self.sections = []
        for i in range(nsec):
            o = 20 + opt + i * 40
            name, vs, va, size, praw, preloc, plin, nrel, nlin, ch = struct.unpack('<8sIIIIIIHHI', d[o:o + 40])
            relocs = [struct.unpack_from('<IIH', d, preloc + r * 10) for r in range(nrel)]
            self.sections.append(dict(name=name.rstrip(b'\0').decode('latin-1'), data=d[praw:praw + size] if praw else b'',
                                      relocs=relocs, ch=ch))
        strtab = symptr + nsym * 18
        self.symbols, i = {}, 0
        while i < nsym:
            o = symptr + i * 18
            raw, val, sec, typ, cls, naux = struct.unpack_from('<8sIhHBB', d, o)
            name = (d[strtab + struct.unpack('<I', raw[4:])[0]:].split(b'\0', 1)[0] if raw[:4] == b'\0\0\0\0'
                    else raw.rstrip(b'\0')).decode('latin-1')
            self.symbols[i] = dict(name=name, value=val, sec=sec, type=typ, cls=cls)
            i += 1 + naux
        # names this object defines with internal linkage (STATIC storage class): every file has its own copy
        self.internal = {s['name'] for s in self.symbols.values() if s['cls'] == 3 and s['sec'] > 0}

    def functions(self):
        """{name: (section index, offset, size)} for function symbols defined in code sections"""
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

    def local_address_offset(self, fname, off, symbol, addend=0):
        """Resolve an ADDR32 to a label inside this function; reject other uses for now."""
        sec, start, size = self.functions()[fname]
        if off < 0 or off % 4 or off + 4 > size:
            raise ValueError('unaligned or out-of-range ADDR32 site')
        hit = [s for s in self.symbols.values() if s['name'] == symbol]
        if len(hit) != 1 or hit[0]['sec'] != sec:
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


def is_constant(name):
    return name.startswith('__real@')


def is_string(name):
    return name.startswith('??_C@')


def is_local(name):
    return name.startswith(('$', '.'))


def check_consistency(entries, read, aliases, known):
    """entries: [(file, function, symbol, address, kind, offset, obj)]; read(va, n) -> CD2 bytes;
    aliases: {address: set(names)} declared in config/symbol_aliases.txt; known: {symbol: address} from the manifest.
    Returns [problem strings]."""
    problems = []
    by_name = collections.defaultdict(set)
    by_addr = collections.defaultdict(set)
    where = collections.defaultdict(list)
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
            ours = obj.symbol_bytes(sym, 64)
            if ours is not None:
                n = ours.find(b'\0') + 1 if b'\0' in ours else len(ours)
                if read(addr, n) != ours[:n]:
                    problems.append('%s %s+%X: string %s differs from CD2 at %08X' % (f, fn, off, sym[:40], addr))
            continue
        local = is_local(sym) or sym in getattr(obj, 'internal', ())
        key = (f, sym) if local else sym
        by_name[key].add(addr)
        where[key].append('%s+%X' % (fn[:40], off))
        if not local:
            by_addr[addr].add(sym)
        m = EMBEDDED.search(sym)
        if m and int(m.group(1), 16) != addr:
            problems.append('%s %s+%X: %s names address %s but resolves to %08X' % (f, fn, off, sym, m.group(1), addr))
        if sym in known and known[sym] != addr:
            problems.append('%s %s+%X: %s is matched at %08X (manifest) but this reference resolves to %08X'
                            % (f, fn, off, sym, known[sym], addr))
    for key, addrs in by_name.items():
        if len(addrs) > 1:
            problems.append('%s resolves to several addresses: %s (references: %s)'
                            % (key if isinstance(key, str) else '%s in %s' % (key[1], key[0]),
                               ', '.join('%08X' % a for a in sorted(addrs)), ', '.join(where[key][:4])))
    for addr, names in by_addr.items():
        if len(names) > 1 and not names <= aliases.get(addr, set()):
            problems.append('%08X is referenced under several names: %s (declare in config/symbol_aliases.txt if the '
                            'linker really merged them)' % (addr, ', '.join(sorted(names))))
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
