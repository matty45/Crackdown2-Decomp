import idautils, ida_funcs, ida_name, ida_ua, ida_bytes, ida_idp, idc, hashlib, json, ida_xref, ida_nalt

def norm_insn(ea):
    insn = ida_ua.insn_t()
    if not ida_ua.decode_insn(insn, ea):
        return None, None
    mn = insn.get_canon_mnem()
    strict = [mn]
    for op in insn.ops:
        if op.type == ida_ua.o_void:
            break
        if op.type == ida_ua.o_reg:
            strict.append('r%d' % op.reg)
        elif op.type == ida_ua.o_imm:
            v = op.value & 0xFFFFFFFF
            strict.append('#%x' % v if v < 0x1000 or v > 0xFFFFF000 else '#A')
        elif op.type == ida_ua.o_displ:
            strict.append('d%x(r%d)' % (op.addr & 0xFFFFFFFF, op.reg) if (op.addr & 0xFFFFFFFF) < 0x1000 else 'dA(r%d)' % op.reg)
        elif op.type in (ida_ua.o_near, ida_ua.o_far, ida_ua.o_mem):
            strict.append('@')
        else:
            strict.append('o%d' % op.type)
    return mn, ' '.join(strict)

MARKER_REGS = ()  # e.g. (13, 14): drop `or rX,rX,rX` trace markers from internal builds

def is_marker(ea):
    w = ida_bytes.get_dword(ea)
    if (w >> 26) == 31 and ((w >> 1) & 0x3FF) == 444:
        rs = (w >> 21) & 31
        return rs == (w >> 16) & 31 == (w >> 11) & 31 and rs in MARKER_REGS
    return False

def run(out_path):
    with open(out_path, 'w') as fo:
        for fea in idautils.Functions():
            f = ida_funcs.get_func(fea)
            mns = []; st = []; callees = set(); strs = set()
            for ea in idautils.FuncItems(fea):
                if MARKER_REGS and is_marker(ea):
                    continue
                mn, s = norm_insn(ea)
                if mn is None:
                    continue
                mns.append(mn); st.append(s)
                for x in idautils.XrefsFrom(ea, 0):
                    if x.type in (ida_xref.fl_CN, ida_xref.fl_CF):
                        callees.add(x.to)
                    elif x.type in (ida_xref.dr_O, ida_xref.dr_R):
                        t = ida_nalt.get_str_type(x.to)
                        if t is not None and t != 0xFFFFFFFF and ida_bytes.is_strlit(ida_bytes.get_flags(x.to)):
                            b = ida_bytes.get_strlit_contents(x.to, -1, t)
                            if b:
                                strs.add(b.decode('latin-1')[:200])
            rec = dict(ea=fea, size=f.end_ea - fea, n=len(mns), name=ida_name.get_name(fea),
                       hl=hashlib.md5(' '.join(mns).encode()).hexdigest()[:16],
                       hs=hashlib.md5('\n'.join(st).encode()).hexdigest()[:16],
                       calls=sorted(callees), strs=sorted(strs))
            fo.write(json.dumps(rec) + '\n')
