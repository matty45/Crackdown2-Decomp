"""IDA (RuffKing database): reference material for a class: every function of the class plus all functions of
the RuffKing object file(s) that define it, with pseudocode and disassembly (trace markers stripped), and its vtables.

Run inside the RuffKing IDB after setting CLASS, OUT, and RUFF_PDB_JSON (output of tools/research/scripts/pdbinfo.py).
"""
import bisect, json, os
import ida_bytes, ida_funcs, ida_hexrays, ida_name, idautils, idc

MARKERS = ('mr        r13, r13', 'mr        r14, r14')


def build(CLASS, OUT, RUFF_PDB_JSON):
    pdb = json.load(open(RUFF_PDB_JSON))
    mods = pdb['mods']
    code = sorted((c for c in pdb['contribs'] if c[3] & 0x20 and c[0] == 3), key=lambda c: c[1])
    starts = [c[1] for c in code]

    def mod(ea):
        off = ea - 0x822D0000
        i = bisect.bisect_right(starts, off) - 1
        return code[i][4] if i >= 0 and code[i][1] <= off < code[i][1] + code[i][2] else None
    cls_funcs, vts = [], []
    for ea, n in idautils.Names():
        f = ida_funcs.get_func(ea)
        if f and f.start_ea == ea and ('@%s@' % CLASS in n or n.startswith(('??0%s@' % CLASS, '??1%s@' % CLASS, '??_G%s@' % CLASS))
                                       or ('%sRegistrar' % CLASS) in n):
            cls_funcs.append(ea)
        if n.startswith('??_7%s@' % CLASS):
            vt, p = [], ea
            while len(vt) < 64:
                v = ida_bytes.get_dword(p)
                fv = ida_funcs.get_func(v)
                if not (fv and fv.start_ea == v):
                    break
                vt.append(v)
                p += 4
            vts.append(n + '\n' + '\n'.join('  slot %2d: %s' % (i, ida_name.demangle_name(ida_name.get_name(v), 0) or ida_name.get_name(v))
                                            for i, v in enumerate(vt)))
    # primary object(s): the one(s) defining most of the class's functions; others only contribute the class's own functions
    counts = {}
    for ea in cls_funcs:
        m = mod(ea)
        if m is not None:
            counts[m] = counts.get(m, 0) + 1
    objs = {m for m, c in counts.items() if c == max(counts.values())} if counts else set()
    obj_funcs = [ea for ea in idautils.Functions() if mod(ea) in objs]
    allf = sorted(set(cls_funcs) | set(obj_funcs))
    os.makedirs(OUT, exist_ok=True)
    parts = ['// RuffKing (Ryse prototype, Nov 2010): %s in a later build of the same codebase, with symbols.\n'
             '// Object file(s): %s\n// The code may differ from CD2. Trace markers mr r13,r13 / mr r14,r14 are stripped.\n'
             '// Tiny functions may carry wrong (identical-code-folded) names.\n'
             % (CLASS, ', '.join(mods[m]['name'].split('\\')[-1] for m in objs))]
    for ea in allf:
        nm = ida_name.get_name(ea)
        try:
            pc = str(ida_hexrays.decompile(ea))
        except Exception as e:
            pc = '// decompile failed: %s' % e
        dis = '\n'.join('    %08X  %s' % (a, idc.GetDisasm(a)) for a in idautils.FuncItems(ea) if not idc.GetDisasm(a).startswith(MARKERS))
        parts.append('\n// ===== %08X %s\n// %s\n%s\n/* disassembly:\n%s\n*/\n' % (ea, nm, ida_name.demangle_name(nm, 0) or nm, pc, dis))
    open(os.path.join(OUT, 'ruffking_%s.c' % CLASS), 'w').write(''.join(parts))
    open(os.path.join(OUT, 'ruffking_vtables.txt'), 'w').write('\n\n'.join(vts) + '\n')
    return len(allf), len(vts), [mods[m]['name'].split('\\')[-1] for m in objs]
