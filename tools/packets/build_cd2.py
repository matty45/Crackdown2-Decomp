r"""IDA (CD2 database): build a whole-file pilot packet for an RWS attribute-handler class.

Run inside the CD2 IDB (e.g. via ida-pro-mcp execute_python) after setting:
    CLASS = 'cRopes'; OUT = r'...\packets\cRopes'; REGISTRARS = r'...\cd2_registrars.json'
Writes OUT/targets/Fnn_ADDR/{target.hex,cd2_disasm.txt,cd2_pseudocode.c} and OUT/cd2_vtable.txt.

Candidates: functions around MakeNew (BEFORE before, AFTER after), the registrar initializer and at-exit destructor,
and vtable entries that the link order list moved into the hot region (0x821D0000-0x823D0000).
Note: target bytes are game-derived; packets stay outside the repository.
"""
import json, os
import ida_bytes, ida_funcs, ida_hexrays, ida_segment, idautils, idc

HOT_LO, HOT_HI = 0x821D0000, 0x823D0000
BLR, BCTR = 0x4E800020, 0x4E800420
EPILOGUE = (0x38210060, 0x8181FFF8, 0x7D8803A6, BLR)  # addi r1,r1,96 / lwz r12,-8(r1) / mtlr r12 / blr


def true_end(fn):
    """IDA ends some functions early: after `bl atexit` (it treats atexit as no-return), the epilogue is dropped,
    and after a tail-call `b`, the compiler's unreachable trailing `blr` is dropped. Extend over those words only."""
    end = fn.end_ea
    last = ida_bytes.get_dword(end - 4)
    if last in (BLR, BCTR):
        return end
    if last >> 26 == 18 and last & 1:  # bl: a function cannot end in a call; take words up to the first blr
        for k in range(8):
            if ida_bytes.get_dword(end + 4 * k) == BLR:
                return end + 4 * (k + 1)
    elif last >> 26 == 18 and ida_bytes.get_dword(end) == BLR:  # b + lone blr
        return end + 4
    return end


def build(CLASS, OUT, REGISTRARS, BEFORE=10, AFTER=20):
    """The candidate window is centred on the class's RetClassName when one is found, else on MakeNew. For gameplay
    classes the registrar's MakeNew often creates a separate prototype object and lives away from the class's code
    (e.g. cChaseBehaviour); MakeNew and the registrar functions are always included."""
    reg = [r for r in json.load(open(REGISTRARS)) if r['name'] == CLASS][0]
    mk, sva = reg['makenew'], reg['str']
    # RetClassName: lis/addi r3,<class string>/blr. The class name can exist as several string copies; check them all.
    rd = ida_segment.get_segm_by_name('.rdata')
    data = ida_bytes.get_bytes(rd.start_ea, rd.end_ea - rd.start_ea)
    strs, i = {sva}, data.find(CLASS.encode() + b'\0')
    while i != -1:
        if i == 0 or data[i - 1] == 0:
            strs.add(rd.start_ea + i)
        i = data.find(CLASS.encode() + b'\0', i + 1)
    retname = None
    for s in sorted(strs):
        for x in idautils.XrefsTo(s):
            f = ida_funcs.get_func(x.frm)
            if f and f.end_ea - f.start_ea == 12 and ida_bytes.get_dword(f.start_ea + 8) == 0x4E800020:
                retname = f.start_ea
    # vtable: the .rdata slot holding RetClassName; walk back to the nearest slot referenced from code
    vt_start, slots = None, []
    if retname:
        i = data.find(retname.to_bytes(4, 'big'))
        if i != -1:
            p = rd.start_ea + i
            for k in range(64):
                if any(ida_bytes.is_code(ida_bytes.get_flags(x.frm)) for x in idautils.XrefsTo(p - 4 * k)):
                    vt_start = p - 4 * k
                    break
            if vt_start:
                slots = [ida_bytes.get_dword(vt_start + 4 * j) for j in range(48)]
    # candidate functions
    addrs = []
    centre = retname if retname and not HOT_LO <= retname < HOT_HI else mk
    f = ida_funcs.get_func(centre)
    p = f.start_ea
    for _ in range(BEFORE):
        pf = ida_funcs.get_prev_func(p)
        if not pf:
            break
        p = pf.start_ea
        addrs.insert(0, p)
    addrs.append(centre)
    n = centre
    for _ in range(AFTER):
        nf = ida_funcs.get_next_func(n)
        if not nf:
            break
        n = nf.start_ea
        addrs.append(n)
    hot = [s for s in slots if HOT_LO <= s < HOT_HI and ida_funcs.get_func(s) and ida_funcs.get_func(s).start_ea == s]
    for a in hot + [mk, reg['init'], reg['atexit']]:
        if a and a not in addrs:
            addrs.append(a)
    os.makedirs(os.path.join(OUT, 'targets'), exist_ok=True)
    info = []
    for i, a in enumerate(addrs):
        fn = ida_funcs.get_func(a)
        k = 'F%02d' % (i + 1)
        d = os.path.join(OUT, 'targets', '%s_%08X' % (k, a))
        os.makedirs(d, exist_ok=True)
        end = true_end(fn)
        open(os.path.join(d, 'target.hex'), 'w').write(ida_bytes.get_bytes(fn.start_ea, end - fn.start_ea).hex())
        open(os.path.join(d, 'cd2_disasm.txt'), 'w').write(
            '\n'.join('%08X  %08X  %s' % (x, ida_bytes.get_dword(x), idc.GetDisasm(x))
                      for x in list(idautils.FuncItems(a)) + list(range(fn.end_ea, end, 4))) + '\n')
        try:
            pc = str(ida_hexrays.decompile(a))
        except Exception as e:
            pc = '// decompilation failed: %s' % e
        open(os.path.join(d, 'cd2_pseudocode.c'), 'w').write(pc)
        role = ('MakeNew' if a == mk else 'RetClassName' if a == retname else 'registrar init' if a == reg['init']
                else 'registrar atexit' if a == reg['atexit'] else 'vtable entry in hot region' if a in hot else '')
        info.append('%s %08X %4d insns %s' % (k, a, (end - fn.start_ea) // 4, role))
    with open(os.path.join(OUT, 'cd2_vtable.txt'), 'w') as fo:
        fo.write('CD2 data at 0x%08X: vtable of %s (RetClassName 0x%08X). Later slots may belong to secondary vtables.\n'
                 % (vt_start or 0, CLASS, retname or 0))
        for j, v in enumerate(slots):
            fo.write('  slot %2d: %08X %s\n' % (j, v, idc.get_name(v)))
    with open(os.path.join(OUT, 'candidates.txt'), 'w') as fo:
        fo.write('Class %s: CD2 object size 0x%X, MakeNew 0x%08X, window centred on %s 0x%08X\n'
                 % (CLASS, reg['size'] or 0, mk, 'RetClassName' if centre == retname else 'MakeNew', centre)
                 + '\n'.join(info) + '\n')
    return info
