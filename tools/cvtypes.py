"""The size of every global and static an object defines, from the CodeView records of a /Z7 build of it.

A COFF symbol table gives a data symbol's place but not its size: without it, a datum's extent can only run to the
next symbol of its section, which includes alignment padding and says nothing once the linker has placed the data
differently. The compiler's own debug records give the size: each S_GDATA32/S_LDATA32 record of .debug$S names a type
index and, through its SECREL relocation, the symbol it describes; .debug$T holds the types (CodeView 8, signature 4).

usage: data_sizes(path of a /Z7 object) -> {symbol name: size in bytes}
"""
import struct

import relocs

S_LDATA32, S_GDATA32 = 0x110C, 0x110D
SECREL = 0x0B
LF_MODIFIER, LF_POINTER = 0x1001, 0x1002
LF_ARRAY, LF_CLASS, LF_STRUCTURE, LF_UNION, LF_ENUM = 0x1503, 0x1504, 0x1505, 0x1506, 0x1507
FWDREF = 0x80
NUMERIC = {0x8000: ('<b', 1), 0x8001: ('<h', 2), 0x8002: ('<H', 2), 0x8003: ('<i', 4), 0x8004: ('<I', 4),
           0x8009: ('<q', 8), 0x800A: ('<Q', 8)}


def numeric(b, o):
    """A numeric leaf at o: (value, offset after it)"""
    v = struct.unpack_from('<H', b, o)[0]
    if v < 0x8000:
        return v, o + 2
    fmt, n = NUMERIC[v]
    return struct.unpack_from(fmt, b, o + 2)[0], o + 2 + n


def cstr(b, o):
    e = b.index(b'\0', o)
    return b[o:e].decode('latin-1'), e + 1


def primitive_size(t):
    """Size of a CodeView primitive type index (below 0x1000); None if unknown"""
    if t & 0x700:  # a pointer mode: 32-bit pointer
        return 4
    k = t & 0xFF
    if k in (0x10, 0x20, 0x30, 0x68, 0x69, 0x70):  # char, uchar, bool, int8, uint8, rchar
        return 1
    if k in (0x11, 0x21, 0x31, 0x71, 0x72, 0x73, 0x7A):  # short, ushort, bool16, wchar, int16, uint16, char16
        return 2
    if k in (0x12, 0x22, 0x32, 0x74, 0x75, 0x40, 0x08, 0x7B):  # long, ulong, bool32, int32, uint32, float, HRESULT
        return 4
    if k in (0x13, 0x23, 0x33, 0x76, 0x77, 0x41):  # quad, uquad, bool64, int64, uint64, double
        return 8
    if k == 0x42:
        return 10
    return None


class Types:
    def __init__(self, data):
        self.records, self.by_name = {}, {}
        o, index = 4, 0x1000  # after the signature
        while o + 4 <= len(data):
            n, leaf = struct.unpack_from('<HH', data, o)
            self.records[index] = (leaf, data[o + 4:o + 2 + n])
            index += 1
            o += 2 + n
        for i, (leaf, b) in self.records.items():  # complete definitions, for forward references
            if leaf in (LF_CLASS, LF_STRUCTURE, LF_UNION):
                prop = struct.unpack_from('<H', b, 2)[0]
                if not prop & FWDREF:
                    self.by_name.setdefault(self.name(leaf, b), i)

    @staticmethod
    def name(leaf, b):
        if leaf in (LF_CLASS, LF_STRUCTURE):
            _, o = numeric(b, 16)
        else:
            _, o = numeric(b, 8)
        return cstr(b, o)[0]

    def size(self, t, depth=0):
        if t < 0x1000:
            return primitive_size(t)
        if t not in self.records or depth > 32:
            return None
        leaf, b = self.records[t]
        if leaf == LF_MODIFIER:
            return self.size(struct.unpack_from('<I', b, 0)[0], depth + 1)
        if leaf == LF_POINTER:
            attr = struct.unpack_from('<I', b, 4)[0]
            return (attr >> 13) & 0x3F or 4
        if leaf == LF_ARRAY:
            return numeric(b, 8)[0]
        if leaf in (LF_CLASS, LF_STRUCTURE, LF_UNION):
            prop = struct.unpack_from('<H', b, 2)[0]
            if prop & FWDREF:
                full = self.by_name.get(self.name(leaf, b))
                return self.size(full, depth + 1) if full is not None else None
            return numeric(b, 16 if leaf != LF_UNION else 8)[0]
        if leaf == LF_ENUM:
            return self.size(struct.unpack_from('<I', b, 4)[0], depth + 1)
        return None


def data_sizes(path):
    """{symbol name: size} of the data a /Z7 object defines (globals, statics, function-scope statics)"""
    obj = relocs.Obj(path)
    types = [s for s in obj.sections if s['name'] == '.debug$T']
    if len(types) != 1:
        return {}
    types = Types(types[0]['data'])
    # a symbol defined in a section, by (section, offset): a SECREL to a section symbol plus an offset names it too
    at = {}
    for s in obj.symbols.values():
        if s['sec'] > 0 and not s['name'].startswith('.'):
            at.setdefault((s['sec'], s['value']), s['name'])
    out = {}
    for sec in obj.sections:
        if sec['name'] != '.debug$S' or len(sec['data']) < 4:
            continue
        secrel = {off: si for off, si, t in sec['relocs'] if t == SECREL}
        b, o = sec['data'], 4
        while o + 8 <= len(b):
            kind, n = struct.unpack_from('<II', b, o)
            body = o + 8
            if kind == 0xF1:  # symbols
                r = body
                while r + 4 <= body + n:
                    reclen, rectype = struct.unpack_from('<HH', b, r)
                    if rectype in (S_LDATA32, S_GDATA32) and r + 14 <= len(b):
                        typ, value = struct.unpack_from('<II', b, r + 4)
                        si = secrel.get(r + 8)
                        sym = obj.symbols.get(si) if si is not None else None
                        if sym is not None:
                            name = (at.get((sym['sec'], sym['value'] + value)) if sym['name'].startswith('.')
                                    else sym['name'])
                            size = types.size(typ)
                            if name and size:
                                out[name] = size
                    r += 2 + reclen
            o = body + (n + 3) // 4 * 4
    return out
