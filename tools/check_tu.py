"""Agent harness: compile one source file and compare it with every target function of a packet.

usage: py -I tools/check_tu.py <packet_dir> <file.cpp> [--diff Fnn] [--ltcg] [--include DIR ...]

- Targets are <packet_dir>/targets/<Fnn>_<ADDR>/ (target.hex, cd2_disasm.txt), built by tools/packets/build_cd2.py.
- Map targets to your functions in work/map.txt next to the source (one `Fnn symbol-substring` per line). Mapped
  targets are verified by symbol; unmapped ones are paired by similarity, which can falsely report EXACT for
  same-shape functions, so only trust results without "(similarity pairing)".
- --diff Fnn prints the differing regions of one target (ours | CD2).
- --ltcg also builds the file with link-time code generation, as CD2's game code was, and reports the mapped targets
  under it (see tools/verify_ltcg.py). Use it for functions whose CD2 code loads float constants through one base
  register (addi rX, anchor; lfs f, d(rX)), which a plain build can never produce. Needs the CD2_EXE environment variable
  (path to the extracted default.exe) to read the constants CD2 loads directly.
- Flags are those of tools/verify_src.py (/Ox /Ob1 /Gy /GF /GR- /GS- /fp:fast ...). Relocated fields are masked.
- Every run is appended to <packet_dir>/attempts.log.
"""
import glob, os, re, subprocess, sys, time

TOOLS = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, TOOLS)
import coff
from verify_src import FLAGS, XDK, BIN, ROOT, pe_reader, check_toolchain

DUMPBIN_DIR = os.path.join(XDK, 'TechPreview', 'Mar09Compiler', 'bin', 'win32')


def lines_of(path):
    out = []
    for l in open(path):
        parts = l.rstrip('\n').split(None, 2)
        if len(parts) == 3:
            out.append(parts[2])
    return out


def our_lines(obj, sym):
    env = dict(os.environ, PATH=DUMPBIN_DIR + ';' + BIN + ';' + os.environ['PATH'])
    r = subprocess.run([os.path.join(DUMPBIN_DIR, 'dumpbin.exe'), '/disasm', obj], env=env, capture_output=True, text=True)
    out, inside = [], False
    for l in r.stdout.splitlines():
        if re.match(r'^\S.*\):$', l) or re.match(r'^\?\S+', l):
            inside = sym in l
            continue
        m = re.match(r'\s+[0-9A-F]{8}: [0-9A-F]{8} (.*)$', l)
        if inside and m:
            out.append(re.sub(r'\s+', ' ', m.group(1)).strip())
    return out


def diff_words(code, target, rel):
    n = max(len(code), len(target)) // 4
    return n, [w for w in range(n) if not (code[w*4:w*4+4] == target[w*4:w*4+4] or
               (w * 4 in rel and code[w*4:w*4+4] and target[w*4:w*4+4] and code[w*4] >> 2 == target[w*4] >> 2))]


def main():
    check_toolchain()
    args = sys.argv[1:]
    want_diff, ltcg, incs = None, False, [os.path.join(ROOT, 'include')]
    if '--diff' in args:
        i = args.index('--diff'); want_diff = args[i + 1]; del args[i:i + 2]
    if '--ltcg' in args:
        args.remove('--ltcg'); ltcg = True
    while '--include' in args:
        i = args.index('--include'); incs.append(args[i + 1]); del args[i:i + 2]
    if len(args) != 2:
        print(__doc__)
        sys.exit(2)
    tu, src = args[0], os.path.abspath(args[1])
    obj = os.path.splitext(src)[0] + '.obj'
    env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'], INCLUDE=';'.join([os.path.join(XDK, 'include', 'xbox')] + incs))
    r = subprocess.run([os.path.join(BIN, 'cl.exe')] + FLAGS + ['/I' + os.path.dirname(src), '/Fo' + obj, src],
                       env=env, capture_output=True, text=True)
    log = open(os.path.join(tu, 'attempts.log'), 'a')
    if r.returncode:
        errs = [l for l in (r.stdout + r.stderr).splitlines() if 'error' in l.lower()][:15]
        print('COMPILE ERROR\n' + '\n'.join(errs))
        log.write('%s\t%s\tcompile_error\n' % (time.strftime('%H:%M:%S'), os.path.basename(src)))
        return
    funcs = list(coff.functions(obj))
    targets = []
    for d in sorted(glob.glob(os.path.join(tu, 'targets', 'F*_*'))):
        k, addr = os.path.basename(d).split('_')
        targets.append((k, addr, bytes.fromhex(open(os.path.join(d, 'target.hex')).read().strip()), d))
    mapping = {}
    mp = os.path.join(os.path.dirname(src), 'map.txt')
    if os.path.exists(mp):
        for l in open(mp):
            p = l.split()
            if len(p) >= 2 and not l.startswith('#'):
                mapping[p[0]] = p[1]
    scores = []
    for ti, (k, addr, tgt, d) in enumerate(targets):
        for fi, (name, code, rel) in enumerate(funcs):
            exact, ratio = coff.compare(code, tgt, rel)
            scores.append((exact, ratio, ti, fi))
    scores.sort(reverse=True)
    pair, used_t, used_f = {}, set(), set()
    unresolved = set()
    for ti, (k, addr, tgt, d) in enumerate(targets):
        if k in mapping:
            hits = [fi for fi, (name, code, rel) in enumerate(funcs) if mapping[k] in name]
            if hits:
                fi = hits[0]; ex, ra = coff.compare(funcs[fi][1], tgt, funcs[fi][2])
                pair[ti] = (fi, ex, ra); used_t.add(ti); used_f.add(fi)
            else:
                unresolved.add(k)
    if unresolved:
        print('WARNING: map.txt entries that match no compiled symbol (use a substring of the MANGLED name): %s'
              % ', '.join('%s "%s"' % (k, mapping[k]) for k in sorted(unresolved)))
    for k in unresolved:
        del mapping[k]
    for exact, ratio, ti, fi in scores:
        if ti in used_t or fi in used_f or ratio < 0.2:
            continue
        pair[ti] = (fi, exact, ratio); used_t.add(ti); used_f.add(fi)
    lt_status = {}
    if ltcg:
        exe = os.environ.get('CD2_EXE')
        if not exe or not os.path.exists(exe):
            print('--ltcg needs the CD2_EXE environment variable (path to the extracted default.exe)')
        else:
            import verify_ltcg as vl
            read, _ = pe_reader(open(exe, 'rb').read())
            mapped = [(k, int(addr, 16), tgt) for k, addr, tgt, d in targets if k in mapping]
            consts = vl.direct_constants(read, [dict(address=a, size=len(t)) for k, a, t in mapped])
            try:
                ltcg_read, fs, nglobs = vl.build_ltcg(src, obj, consts, os.path.join(os.path.dirname(src), 'ltcg'), env)
                for k, a, t in mapped:
                    res = vl.compare_ltcg(ltcg_read, fs, mapping[k], t, a)
                    lt_status[k] = 'not in image' if res is None else ('EXACT' if res[0] else '%d/%d words' % (res[1], res[2]))
            except RuntimeError as e:
                print('LTCG build failed: %s' % str(e)[:500])
    # relocation targets of exact, mapped functions (tools/relocs.py): calls and references must hit CD2's addresses
    reloc_bad = {}
    exe = os.environ.get('CD2_EXE')
    if exe and os.path.exists(exe):
        import relocs
        read, _ = pe_reader(open(exe, 'rb').read())
        robj = relocs.Obj(obj)
        known = {funcs[fi][0]: int(targets[ti][1], 16) for ti, (fi, ex, ra) in pair.items() if targets[ti][0] in mapping}
        entries, local = [], {}
        for ti, (fi, ex, ra) in pair.items():
            k, addr, tgt, d = targets[ti]
            if not ex or k not in mapping:
                continue
            res, probs = relocs.resolve(robj, funcs[fi][0], tgt, int(addr, 16))
            entries += [(k, funcs[fi][0], s, a, kind, off, robj) for s, a, kind, off in res]
            if probs:
                local[k] = probs
        for p in relocs.check_consistency(entries, read, relocs.load_aliases(os.path.join(ROOT, 'config', 'symbol_aliases.txt')), known):
            k = p.split(' ', 1)[0]
            reloc_bad.setdefault(k if k in mapping else '*', []).append(p)
        for k, probs in local.items():
            reloc_bad.setdefault(k, []).extend(probs)
    total = sum(len(t[2]) for t in targets)
    good = {ti for ti, (fi, ex, ra) in pair.items() if ex and targets[ti][0] not in reloc_bad}
    matched = sum(len(targets[ti][2]) for ti in good)
    print('TU %s: %d/%d target functions exact, %d/%d bytes exact%s' % (
        os.path.basename(tu), len(good), len(targets), matched, total,
        ' (%d more match byte-wise but reference the wrong targets)' % len(reloc_bad) if reloc_bad else ''))
    rec = []
    for ti, (k, addr, tgt, d) in enumerate(targets):
        lt = ('  ltcg %-12s' % lt_status[k]) if k in lt_status else ''
        if ti in pair:
            fi, ex, ra = pair[ti]
            status = ('EXACT' if k not in reloc_bad else 'WRONGTGT') if ex else '%5.1f%%' % (100 * ra)
            print('  %s %s %4dB  %-7s%s <- %s%s' % (k, addr, len(tgt), status, lt, funcs[fi][0][:80],
                                                 '' if k in mapping else '  (similarity pairing)'))
            rec.append('%s=%s' % (k, 'X' if ex else '%.2f' % ra))
        else:
            print('  %s %s %4dB  (no compiled function resembles it)%s' % (k, addr, len(tgt), lt))
            rec.append('%s=-' % k)
    if reloc_bad:
        print('RELOCATION TARGETS: the bytes match but these references do not point where CD2 points (WRONGTGT):')
        for k in sorted(reloc_bad):
            for p in reloc_bad[k]:
                print('  ' + p)
    log.write('%s\t%s\t%s%s\n' % (time.strftime('%H:%M:%S'), os.path.basename(src), ' '.join(rec), ' ltcg' if ltcg else ''))
    if want_diff:
        for ti, (k, addr, tgt, d) in enumerate(targets):
            if k != want_diff:
                continue
            if ti not in pair:
                print('\n%s: nothing to diff (no paired function)' % k); return
            fi, ex, ra = pair[ti]
            name, code, rel = funcs[fi]
            if ex:
                print('\n%s is an exact match' % k); return
            n, diff = diff_words(code, tgt, rel)
            ol, tl = our_lines(obj, name), lines_of(os.path.join(d, 'cd2_disasm.txt'))
            show = sorted({x for w in diff for x in range(w - 2, w + 3) if 0 <= x < n})
            print('\n%s diff (%d differing words, first at +0x%x):' % (k, len(diff), diff[0] * 4 if diff else 0))
            last, printed = -2, 0
            for w in show:
                if printed >= 60:
                    print('  ... more differences not shown; fix the first region and re-run'); break
                if w != last + 1:
                    print('  ----')
                print('%s %03x  %-36s | %s' % ('>' if w in diff else ' ', w * 4, (ol[w] if w < len(ol) else '--')[:36], tl[w] if w < len(tl) else '--'))
                last, printed = w, printed + 1


if __name__ == '__main__':
    main()
