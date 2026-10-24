"""Mismatch classifier: turn an instruction diff (CD2 against ours) into findings with concrete hints.

Used by `tools/cd2.py diff` and `check --explain`. Input: objdiff's one-shot JSON for one function pair (rows aligned
index by index; an inserted or deleted instruction leaves an empty row on the other side). Output: findings, most
fundamental first, each with the CD2 addresses involved, a hint and the docs/matching-notes.md entry that explains it.

The categories come from what the project has learned so far (docs/matching-notes.md). Each is a mechanical test on
the parsed instructions; none needs knowledge of the source. Run `py -I tools/mismatch.py --self-test` to check each
category against synthetic rows.
"""
import collections, re, sys

NOTES = 'docs/matching-notes.md'

# commutative instructions: positions of the operands that may be swapped
COMMUTATIVE = {'add': (1, 2), 'add.': (1, 2), 'addc': (1, 2), 'adde': (1, 2), 'mullw': (1, 2), 'mulhw': (1, 2),
               'mulhwu': (1, 2), 'and': (1, 2), 'and.': (1, 2), 'or': (1, 2), 'or.': (1, 2), 'xor': (1, 2),
               'nand': (1, 2), 'nor': (1, 2), 'eqv': (1, 2), 'fadd': (1, 2), 'fadds': (1, 2), 'fmul': (1, 2),
               'fmuls': (1, 2), 'fmadd': (1, 2), 'fmadds': (1, 2), 'fmsub': (1, 2), 'fmsubs': (1, 2),
               'fnmadd': (1, 2), 'fnmadds': (1, 2), 'fnmsub': (1, 2), 'fnmsubs': (1, 2)}
LOADS_STORES = re.compile(r'^(l|st)(b|h|w|d|f[sd]|fs|fd|ha|hz|bz|wz)\w*$')
INVERSE_BRANCH = {'beq': 'bne', 'bne': 'beq', 'blt': 'bge', 'bge': 'blt', 'bgt': 'ble', 'ble': 'bgt'}


def parse(row, symbols, start):
    """objdiff instruction row -> dict(mn, args, text, call, reloc) or None for an empty row.
    args: ('reg', name) | ('imm', int) | ('mem', disp, base) | ('memreloc', target, base) | ('reloc', target)
          | ('branch', offset from the function start)"""
    ins = row.get('instruction')
    if not ins:
        return None
    parts = ins['parts']
    mn = parts[0]['opcode']['mnemonic'] if parts and 'opcode' in parts[0] else '?'
    reloc = None
    if 'relocation' in ins and ins['relocation'].get('target_symbol') is not None:
        idx = ins['relocation']['target_symbol']
        reloc = symbols[idx]['name'] if idx < len(symbols) else '?'
    args = []
    k = 1
    while k < len(parts):
        p = parts[k]
        a = p.get('arg')
        if a is None:
            k += 1
            continue
        nxt = parts[k + 1] if k + 1 < len(parts) else {}
        if nxt.get('basic') == '(' and k + 2 < len(parts) and 'arg' in parts[k + 2]:
            base = parts[k + 2]['arg'].get('opaque')
            if 'reloc' in a:
                args.append(('memreloc', reloc, base))
            else:
                args.append(('mem', int(a.get('signed', a.get('unsigned', '0')), 0), base))
            k += 4
            continue
        if 'opaque' in a:
            v = a['opaque']
            args.append(('reg', v) if re.match(r'^(r|f|v|cr)\d+$', v) else ('imm', _num(v)))
        elif 'signed' in a or 'unsigned' in a:
            args.append(('imm', int(a.get('signed', a.get('unsigned')), 0)))
        elif 'reloc' in a:
            args.append(('reloc', reloc))
        elif 'branch_dest' in a:
            args.append(('branch', int(a['branch_dest']) - start))
        k += 1
    return dict(mn=mn, args=args, text=ins.get('formatted', '').strip(), reloc=reloc,
                call=mn == 'bl' or (mn == 'b' and reloc is not None))


def _num(v):
    try:
        return int(v, 0)
    except ValueError:
        return v


def pairs(diff_json, addr):
    """[(cd2, ours, kind, cd2_address)] for CD2's function fn_<addr> and ours, from objdiff's one-shot JSON."""
    left = next((s for s in diff_json['left']['symbols'] if s['name'] == 'fn_%08X' % addr), None)
    if left is None or 'target_symbol' not in left:
        return None
    right = diff_json['right']['symbols'][left['target_symbol']]
    lrows, rrows = left.get('instructions', []), right.get('instructions', [])
    lstart = next((int(r['instruction']['address']) for r in lrows if 'instruction' in r and 'address' in r['instruction']), 0)
    rstart = next((int(r['instruction'].get('address', 0)) for r in rrows if 'instruction' in r), 0)
    out = []
    for i in range(max(len(lrows), len(rrows))):
        l = lrows[i] if i < len(lrows) else {}
        r = rrows[i] if i < len(rrows) else {}
        kind = (l.get('diff_kind') or r.get('diff_kind') or 'DIFF_NONE')[5:].lower()
        pl = parse(l, diff_json['left']['symbols'], lstart)
        pr = parse(r, diff_json['right']['symbols'], rstart)
        a = addr + int(l['instruction']['address']) - lstart if pl and 'address' in l['instruction'] else None
        out.append((pl, pr, kind, a))
    return out


# ---------------------------------------------------------------------------------------------------- the tests

def _regclass(name):
    return re.match(r'^[a-z]+', name).group(0)


def register_renaming(rows):
    """True when every aligned row has the same mnemonic and non-register operands, and the register operands differ
    by one consistent renaming (per register class)."""
    fwd, back = {}, {}
    any_diff = False
    for l, r, kind, _ in rows:
        if l is None or r is None or l['mn'] != r['mn'] or len(l['args']) != len(r['args']):
            return False
        for x, y in zip(l['args'], r['args']):
            if x[0] != y[0]:
                return False
            regs = []
            if x[0] == 'reg':
                regs = [(x[1], y[1])]
            elif x[0] in ('mem', 'memreloc'):
                if x[0] == 'mem' and x[1] != y[1]:
                    return False
                regs = [(x[2], y[2])]
            elif x[0] in ('imm', 'branch') and x[1] != y[1]:
                return False
            for a, b in regs:
                if _regclass(a) != _regclass(b) or fwd.get(a, b) != b or back.get(b, a) != a:
                    return False
                fwd[a], back[b] = b, a
                any_diff |= a != b
    return any_diff


def classify(rows):
    """Findings for a list of rows from pairs(). Each: dict(category, title, rows=[CD2 addresses], hint, notes)."""
    found = collections.OrderedDict()

    def add(cat, title, addr, hint, notes):
        f = found.setdefault(cat, dict(category=cat, title=title, rows=[], hint=hint, notes='%s: %s' % (NOTES, notes)))
        if addr is not None and addr not in f['rows']:
            f['rows'].append(addr)
    diff = [x for x in rows if x[2] != 'none']
    if not diff:
        return []
    only_cd2 = [l for l, r, k, a in rows if l is not None and r is None]
    only_ours = [r for l, r, k, a in rows if l is None and r is not None]

    # --- structural: frame, saved registers, inlining, constants ---------------------------------------------------
    def frame(ins_list):
        for i in ins_list:
            if i and i['mn'] == 'stwu' and i['args'] and i['args'][0] == ('reg', 'r1') and i['args'][1][0] == 'mem':
                return -i['args'][1][1]
        return None

    def saved(ins_list):
        for i in ins_list:
            if i and i['call'] and i['reloc'] and re.match(r'__savegprlr_\d+|__savefpr_\d+', i['reloc']):
                return i['reloc']
        return None
    lall = [l for l, r, k, a in rows if l]
    rall = [r for l, r, k, a in rows if r]
    if frame(lall) != frame(rall):
        add('frame', 'stack frame size differs (CD2 %s, ours %s bytes)' % (frame(lall), frame(rall)), None,
            'The frame holds the locals and temporaries: a local or a returned struct of a different size, or one more '
            'or fewer local, changes it. Look for a helper whose return type has the wrong size.',
            'Codegen idioms, "Return types shape the caller"; "Stack slots"')
    if saved(lall) != saved(rall):
        add('saved-registers', 'different registers saved (CD2 %s, ours %s)' % (saved(lall), saved(rall)), None,
            'A different number of values live across calls. Constants used after a call get hoisted into saved '
            'registers; a value kept in a local versus re-read from memory changes the count too.',
            'Codegen idioms, "Constants used after calls get hoisted"')
    lcalls = collections.Counter(i['reloc'] for i in lall if i['call'] and not re.match(r'__(save|rest)', i['reloc'] or ''))
    rcalls = collections.Counter(i['reloc'] for i in rall if i['call'] and not re.match(r'__(save|rest)', i['reloc'] or ''))
    if sum(rcalls.values()) > sum(lcalls.values()):
        for l, r, k, a in rows:
            if l is None and r is not None and r['call']:
                add('inline-missing', 'a call where CD2 has the code inline', a,
                    'CD2 inlines this callee. Under /Ob1 only functions declared inline (or defined in the class body) are '
                    'inlined: make it inline in the header, or __forceinline for chained in-class constructors.',
                    'Codegen idioms, "Template helpers need inline under /Ob1"; cNPCTintProfile findings')
    if sum(lcalls.values()) > sum(rcalls.values()):
        for l, r, k, a in rows:
            if r is None and l is not None and l['call']:
                add('inline-extra', 'CD2 calls out of line where ours is inline', a,
                    'CD2 calls this function: in the original it is not inline (or too big to inline). Declare it out of '
                    'line instead of defining it in the header.',
                    'cNPCTintProfile findings (accessors inline or not)')
    # LTCG gathers float constants and loads them through one base register (addi r30, anchor; lfs f0, 0x84(r30));
    # a plain build loads each from its own __real@ constant. A plain-style load of CD2's (lis + lfs lbl_...) is no
    # sign of LTCG: it compiles to the same bytes. Field reads through the address of a global count on both sides.
    rreal = [r for r in rall if r['mn'] in ('lfs', 'lfd') and (r['reloc'] or '').startswith('__real@')]
    if rreal and len(_anchored_float_loads(lall)) > len(_anchored_float_loads(rall)):
        add('ltcg-constants', 'float constants: CD2 loads them the LTCG way', None,
            'CD2 was built with link-time code generation: it loads float constants through one base register '
            '(`addi rX, anchor`, then `lfs f, disp(rX)`), where a plain build loads each from its own constant. Check '
            'with `cd2.py check <file> --ltcg`; if it is exact there, mark the function "ltcg": true.',
            'Traps, "Game code is LTCG"; "LTCG limit"')

    # --- row by row -------------------------------------------------------------------------------------------------
    for l, r, kind, a in rows:
        if kind == 'none' or l is None or r is None:
            continue
        if l['mn'] != r['mn']:
            pair = {l['mn'], r['mn']}
            if any(m.startswith('extrwi') for m in pair) and any(m.startswith(('rlwinm', 'clrlwi', 'andi')) for m in pair):
                add('extract-vs-mask', 'single bit: extract versus mask', a,
                    '`extrwi` comes from converting the bit into a bool (or unsigned char) local first; testing it in '
                    'place (`x & 0x1000`, a bitfield) gives `rlwinm`. Switch between the two forms.',
                    'Traps, "Extract versus mask for single bits"')
            elif pair in ({'cmpw', 'cmplw'}, {'cmpwi', 'cmplwi'}):
                add('signedness', 'signed versus unsigned compare (CD2 %s, ours %s)' % (l['mn'], r['mn']), a,
                    'The compare follows the expression type exactly: int versus unsigned (a return type, a field type, '
                    'or a cast such as `(int)rwSwap32(x)`).', 'Codegen idioms, "Signed versus unsigned compares"; '
                    '"Return types shape the caller"')
            elif {INVERSE_BRANCH.get(l['mn']), l['mn']} == pair:
                add('branch-inverted', 'branch condition inverted (CD2 %s, ours %s)' % (l['mn'], r['mn']), a,
                    'Branch layout follows source order: swap the if/else arms (and negate the condition), or move an '
                    'early return.', 'Codegen idioms, "Branch layout follows source order"')
            elif LOADS_STORES.match(l['mn']) and LOADS_STORES.match(r['mn']) and l['mn'][0] == r['mn'][0]:
                add('width', 'load/store width or sign differs (CD2 %s, ours %s)' % (l['mn'], r['mn']), a,
                    'The field or variable has another type in CD2: bool/char versus int, short versus unsigned short '
                    '(lha/lhz), float versus double (lfs/lfd).', 'Codegen idioms, "A short member passed to an int parameter"')
            else:
                add('different-instruction', 'different instructions', a,
                    'The expression differs here. Compare the surrounding instructions with the source.', 'Codegen idioms')
            continue
        # same mnemonic, different operands
        if len(l['args']) == len(r['args']):
            for x, y in zip(l['args'], r['args']):
                if x[0] == 'mem' and y[0] == 'mem' and x[1] != y[1] and l['mn'] != 'stwu':  # stwu: the frame
                    if x[2] == 'r1' and y[2] == 'r1':
                        add('stack-slot', 'stack slot differs (CD2 0x%X, ours 0x%X)' % (x[1], y[1]), a,
                            'Locals are placed by size, smaller nearer the stack pointer, ties by first appearance; the '
                            'compiler may share a slot between locals whose lifetimes do not overlap. Reorder or rescope '
                            'locals.', 'Codegen idioms, "Stack slots"')
                    else:
                        add('field-offset', 'field offset differs (CD2 0x%X(%s), ours 0x%X(%s))' % (x[1], x[2], y[1], y[2]), a,
                            'A structure layout in the headers does not match CD2 here: a field is at another offset, '
                            'or the access goes through another member. Fix the header (and its CD2_OFFSET checks), '
                            'not the function.', 'include/README.md, "Verify against CD2 before trusting a layout"')
                elif x[0] == 'imm' and y[0] == 'imm' and x[1] != y[1]:
                    if l['mn'] == 'addi' and len(l['args']) == 3 and l['args'][1] == r['args'][1] == ('reg', 'r1'):
                        add('stack-slot', 'stack slot differs (CD2 0x%X, ours 0x%X)' % (x[1], y[1]), a,
                            'The address of a stack local (addi rX, r1, N): see the stack-slot finding.',
                            'Codegen idioms, "Stack slots"')
                    else:
                        add('immediate', 'constant differs (CD2 %s, ours %s)' % (_fmt(x[1]), _fmt(y[1])), a,
                            'A literal, enum value, array size or shift amount differs.', 'Codegen idioms')
            pos = COMMUTATIVE.get(l['mn'])
            if pos and len(l['args']) > max(pos):
                i, j = pos
                if l['args'][i] == r['args'][j] and l['args'][j] == r['args'][i] and l['args'][i] != l['args'][j]:
                    add('operands-swapped', 'operands of %s swapped' % l['mn'], a,
                        'Operand order follows where the values were defined, not their order in the expression: '
                        'swapping `a * b` rarely helps; computing one operand in its own statement (a local) does.',
                        'Traps, "Operand order of commutative float ops"; Codegen idioms, "Evaluation order around calls"')
    if not any(f in found for f in ('different-instruction', 'width', 'branch-inverted')) and register_renaming(rows):
        found.pop('operands-swapped', None)
        add('registers-only', 'same instructions, registers numbered differently', None,
            'Only the register allocation differs. It follows the order in which values are defined and how long they '
            'live: the declaration order of locals, a value computed into its own local first, the evaluation order '
            'around calls. Try `cd2.py search`.', 'Codegen idioms, "Evaluation order around calls"; Traps, "Operand order"')
    elif not any(k in found for k in ('registers-only',)):
        regs = sum(1 for l, r, k, a in rows if k == 'arg_mismatch' and l and r and l['mn'] == r['mn']
                   and all(x == y or (x[0] == y[0] == 'reg') or (x[0] == y[0] and x[0] in ('mem', 'memreloc') and x[1] == y[1])
                           for x, y in zip(l['args'], r['args'])))
        if regs:
            for l, r, k, a in rows:
                if k == 'arg_mismatch' and l and r and l['mn'] == r['mn'] and all(
                        x == y or (x[0] == y[0] == 'reg') or (x[0] == y[0] and x[0] in ('mem', 'memreloc') and x[1] == y[1])
                        for x, y in zip(l['args'], r['args'])):
                    add('registers', 'registers differ', a,
                        'Same instruction with other registers: a consequence of a different value order or lifetime '
                        'nearby. Fix the other findings first; what remains is register allocation.',
                        'Codegen idioms, "Evaluation order around calls"')
    if only_cd2 or only_ours:
        n1, n2 = len(only_cd2), len(only_ours)
        add('structure', '%d instruction(s) only in CD2, %d only in ours' % (n1, n2), None,
            'The code shape differs: an expression computed differently, recomputed versus reused (CD2 recomputing a '
            'value means the source called or read it twice), a missing or extra temporary.',
            'Traps, "Recomputed values come from repeated calls"')
        for l, r, k, a in rows:
            if l is not None and r is None:
                found['structure']['rows'].append(a)
    order = ['frame', 'saved-registers', 'inline-missing', 'inline-extra', 'ltcg-constants', 'field-offset', 'width',
             'signedness', 'extract-vs-mask', 'branch-inverted', 'structure', 'different-instruction', 'immediate',
             'stack-slot', 'operands-swapped', 'registers-only', 'registers']
    out = sorted(found.values(), key=lambda f: order.index(f['category']) if f['category'] in order else 99)
    for f in out:
        f['rows'] = ['0x%08X' % x for x in f['rows'] if x is not None]
    return out


def _anchored_float_loads(ins_list):
    """lfs/lfd at a displacement from a register that an addi set to a symbol's address."""
    regs, out = set(), []
    for i in ins_list:
        dest = i['args'][0][1] if i['args'] and i['args'][0][0] == 'reg' else None
        if i['mn'] in ('lfs', 'lfd'):
            if any(x[0] == 'mem' and x[2] in regs for x in i['args']):
                out.append(i)
        elif i['mn'] == 'addi' and i['reloc'] and dest:
            regs.add(dest)
        elif dest and not i['mn'].startswith(('st', 'cmp', 'fcmp', 'b', 'mt')):
            regs.discard(dest)  # the register now holds something else
    return out


def _addr_in_name(name):
    m = re.search(r'(?:lbl|fn|off|dword|flt|dbl)_([0-9A-F]{8})', name or '')
    return int(m.group(1), 16) if m else 0


def _fmt(v):
    return '0x%X' % v if isinstance(v, int) else str(v)


# ---------------------------------------------------------------------------------------------------- self-test

def _ins(mn, *args, reloc=None):
    return dict(mn=mn, args=list(args), text=mn, reloc=reloc, call=mn == 'bl')


def self_test():
    R, I, M = (lambda n: ('reg', n)), (lambda v: ('imm', v)), (lambda d, b: ('mem', d, b))
    cases = [
        ('registers-only', [(_ins('lwz', R('r11'), M(4, 'r3')), _ins('lwz', R('r10'), M(4, 'r3')), 'arg_mismatch', 0x10),
                            (_ins('add', R('r3'), R('r11'), R('r4')), _ins('add', R('r3'), R('r10'), R('r4')), 'arg_mismatch', 0x14)]),
        ('operands-swapped', [(_ins('fmuls', R('f1'), R('f2'), R('f3')), _ins('fmuls', R('f1'), R('f3'), R('f2')), 'arg_mismatch', 0x10),
                              (_ins('lwz', R('r3'), M(0, 'r4')), _ins('lwz', R('r4'), M(0, 'r4')), 'arg_mismatch', 0x14)]),
        ('stack-slot', [(_ins('stw', R('r3'), M(0x50, 'r1')), _ins('stw', R('r3'), M(0x54, 'r1')), 'arg_mismatch', 0x10)]),
        ('field-offset', [(_ins('lwz', R('r3'), M(0x58, 'r31')), _ins('lwz', R('r3'), M(0x54, 'r31')), 'arg_mismatch', 0x10)]),
        ('extract-vs-mask', [(_ins('extrwi', R('r3'), R('r4'), I(1), I(19)), _ins('rlwinm', R('r3'), R('r4'), I(0), I(19), I(19)), 'op_mismatch', 0x10)]),
        ('signedness', [(_ins('cmpwi', R('cr6'), R('r3'), I(0)), _ins('cmplwi', R('cr6'), R('r3'), I(0)), 'op_mismatch', 0x10)]),
        ('branch-inverted', [(_ins('beq', R('cr6'), ('branch', 0x20)), _ins('bne', R('cr6'), ('branch', 0x20)), 'op_mismatch', 0x10)]),
        ('width', [(_ins('lbz', R('r3'), M(4, 'r31')), _ins('lwz', R('r3'), M(4, 'r31')), 'op_mismatch', 0x10)]),
        ('inline-missing', [(None, _ins('bl', reloc='?Get@cFoo@@QAAHXZ'), 'insert', None)]),
        ('inline-extra', [(_ins('bl', reloc='fn_82000000'), None, 'delete', 0x10)]),
        ('frame', [(_ins('stwu', R('r1'), M(-0x80, 'r1')), _ins('stwu', R('r1'), M(-0x90, 'r1')), 'arg_mismatch', 0x10)]),
        ('ltcg-constants', [(_ins('lis', R('r11'), ('reloc', 'lbl_820F8C80'), reloc='lbl_820F8C80'),
                             _ins('lis', R('r11'), ('reloc', '__real@3f800000'), reloc='__real@3f800000'), 'arg_mismatch', 0x10),
                            (_ins('addi', R('r30'), R('r11'), ('reloc', 'lbl_820F8C80'), reloc='lbl_820F8C80'), None, 'delete', 0x14),
                            (_ins('lfs', R('f0'), M(0x84, 'r30'), reloc='lbl_820F8C80'),
                             _ins('lfs', R('f0'), ('memreloc', '__real@3f800000', 'r11'), reloc='__real@3f800000'), 'arg_mismatch', 0x18)]),
        ('structure', [(_ins('mr', R('r3'), R('r4')), None, 'delete', 0x10)]),
    ]
    ok = True
    for want, rows in cases:
        got = [f['category'] for f in classify(rows)]
        good = want in got
        ok &= good
        print('self-test %-18s %s%s' % (want, 'ok' if good else 'MISSED', '' if good else '  (got %s)' % got))
    same = classify([(_ins('blr'), _ins('blr'), 'none', 0x10)])
    ok &= not same
    print('self-test %-18s %s' % ('identical code', 'ok (no findings)' if not same else 'FALSE FINDINGS %s' % same))
    # a plain-style constant load (same shape, other symbol names) next to an unrelated difference: no LTCG finding
    plain = [f['category'] for f in classify([
        (_ins('lis', R('r11'), ('reloc', 'lbl_820EA99C'), reloc='lbl_820EA99C'),
         _ins('lis', R('r11'), ('reloc', '__real@40a00000'), reloc='__real@40a00000'), 'none', 0x10),
        (_ins('lfs', R('f0'), ('memreloc', 'lbl_820EA99C', 'r11'), reloc='lbl_820EA99C'),
         _ins('lfs', R('f0'), ('memreloc', '__real@40a00000', 'r11'), reloc='__real@40a00000'), 'none', 0x14),
        (_ins('li', R('r4'), I(6)), _ins('li', R('r4'), I(7)), 'arg_mismatch', 0x18)])]
    good = 'ltcg-constants' not in plain and 'immediate' in plain
    ok &= good
    print('self-test %-18s %s' % ('plain constants', 'ok (no LTCG finding)' if good else 'WRONG %s' % plain))
    # a float field read through a global's address, on both sides, next to a constant and a difference: no finding
    glob = [f['category'] for f in classify([
        (_ins('addi', R('r4'), R('r7'), ('reloc', 'lbl_838FF698'), reloc='lbl_838FF698'),
         _ins('addi', R('r5'), R('r8'), ('reloc', '?g_Thing@@3UThing@@A'), reloc='?g_Thing@@3UThing@@A'), 'arg_mismatch', 0x10),
        (_ins('lfs', R('f13'), M(0x44, 'r4'), reloc='lbl_838FF698'),
         _ins('lfs', R('f13'), M(0x44, 'r5'), reloc='?g_Thing@@3UThing@@A'), 'arg_mismatch', 0x14),
        (_ins('lfs', R('f0'), ('memreloc', 'lbl_820EA99C', 'r11'), reloc='lbl_820EA99C'),
         _ins('lfs', R('f0'), ('memreloc', '__real@40a00000', 'r11'), reloc='__real@40a00000'), 'none', 0x18),
        (_ins('li', R('r4'), I(6)), _ins('li', R('r4'), I(7)), 'arg_mismatch', 0x1C)])]
    good = 'ltcg-constants' not in glob
    ok &= good
    print('self-test %-18s %s' % ('global field read', 'ok (no LTCG finding)' if good else 'WRONG %s' % glob))
    return ok


if __name__ == '__main__':
    if '--self-test' in sys.argv:
        sys.exit(0 if self_test() else 1)
    print(__doc__)
