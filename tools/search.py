"""Automatic source search: try source transformations on one function and keep those that bring it closer to CD2.

Used by `tools/cd2.py search <file.cpp> <address>`. The function must already be structurally right (the search does
not write code, it only reshapes it). Every candidate is compiled with the game flags and scored by the number of
words that match CD2 (relocated fields masked, as in `check`); a transformation that breaks the code simply fails
to compile and is dropped. Greedy: each round tries every single transformation of the current best and keeps the
best improvement, until the function is exact, nothing improves, or the budget is spent.

Transformations (the shapes docs/matching-notes.md found to matter):
  swap        the operands of a commutative operator (+ * & | ^ == !=)
  flip        a comparison (a < b becomes b > a)
  arms        the arms of an if/else, negating the condition
  order       two adjacent simple statements (declaration and evaluation order)
  zero-test   `if (p)` versus `if (p != 0)`, `if (!p)` versus `if (p == 0)`
  zero-cmp    a comparison with zero in another form: `n > 0`, `n != 0`, `0 < n`, `n`
  inline      a local replaced by its initializer at every use (CD2 recomputing a value means the source did)
  increment   `i++;` versus `++i;`
Nothing is written unless --apply is given; the result shows the transformations and the changed lines.
"""
import concurrent.futures, difflib, os, re, shutil, subprocess, sys

TOOLS = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, TOOLS)
import coff  # noqa: E402
from verify_src import ROOT, XDK, BIN, FLAGS  # noqa: E402

TOKEN = re.compile(r'''
    (?P<ws>\s+) | (?P<comment>//[^\n]*|/\*.*?\*/) | (?P<str>"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*') |
    (?P<num>(?:0[xX][0-9a-fA-F]+|\d+\.?\d*(?:[eE][+-]?\d+)?|\.\d+(?:[eE][+-]?\d+)?)[uUlLfF]*) |
    (?P<id>[A-Za-z_]\w*) |
    (?P<op>->\*|\.\.\.|<<=|>>=|->|\+\+|--|<<|>>|<=|>=|==|!=|&&|\|\||\+=|-=|\*=|/=|%=|&=|\|=|\^=|::|[-+*/%&|^!~<>=?:;,.(){}\[\]])
''', re.S | re.X)
PREC = {'*': 5, '/': 5, '%': 5, '+': 6, '-': 6, '<<': 7, '>>': 7, '<': 9, '<=': 9, '>': 9, '>=': 9, '==': 10, '!=': 10,
        '&': 11, '^': 12, '|': 13, '&&': 14, '||': 15}
ASSIGN = {'=', '+=', '-=', '*=', '/=', '%=', '&=', '|=', '^=', '<<=', '>>='}
STOPS = {';', '{', '}', ',', '?', ':', 'return', 'case', 'else', 'do'} | ASSIGN
STATEMENT_START = {';', '{', '}', ')', 'else'}  # tokens after which a statement starts
KEYWORDS = {'return', 'case', 'sizeof', 'new', 'delete', 'throw', 'else', 'do', 'if', 'while', 'for', 'switch', 'goto'}
TYPES = {'int', 'float', 'double', 'char', 'bool', 'short', 'long', 'unsigned', 'signed', 'void', 'const', 'volatile'}
COMMUTATIVE = {'+', '*', '&', '|', '^', '==', '!='}
FLIP = {'<': '>', '>': '<', '<=': '>=', '>=': '<='}


def lex(text):
    out = []
    for m in TOKEN.finditer(text):
        kind = m.lastgroup
        if kind not in ('ws', 'comment'):
            out.append((kind, m.group(), m.start(), m.end()))
    return out


# ---------------------------------------------------------------------------------------------------- locating

def demangle_name(symbol):
    """(name, scope or None) from a mangled symbol prefix: ?Name@Scope@..., ??0Class@ (constructor), ??1Class@
    (destructor), ??$Name@<template arguments>@Scope@... (function template)."""
    m = re.match(r'\?\?([01])(\w+)@', symbol)
    if m:
        return ('~' if m.group(1) == '1' else '') + m.group(2), m.group(2)
    m = re.match(r'\?\?\$(\w+)@', symbol)
    if m:
        scopes = re.findall(r'@@@(\w+)@', symbol)
        return m.group(1), scopes[0] if scopes else None
    m = re.match(r'\?(\w+)@(\w+)?@', symbol)
    if m:
        return m.group(1), m.group(2)
    raise ValueError('cannot read a function name from %r (operators and compiler-generated functions are not searched)' % symbol)


def find_body(text, symbol):
    """(start, end) offsets of the body of the function defined in text, between its braces (exclusive)."""
    name, scope = demangle_name(symbol)
    toks = lex(text)
    cands = []
    for i, (k, v, s, e) in enumerate(toks):
        nm = v
        j = i
        if v == '~' and i + 1 < len(toks):
            nm, j = '~' + toks[i + 1][1], i + 1
        if nm != name or j + 1 >= len(toks) or toks[j + 1][1] != '(':
            continue
        qual = toks[i - 2][1] if i >= 2 and toks[i - 1][1] == '::' else None
        depth, p = 0, j + 1
        while p < len(toks):
            depth += toks[p][1] == '('
            depth -= toks[p][1] == ')'
            if depth == 0:
                break
            p += 1
        p += 1
        while p < len(toks) and toks[p][1] in ('const',):
            p += 1
        if p < len(toks) and toks[p][1] == ':':  # constructor initializer list
            while p < len(toks) and toks[p][1] != '{':
                p += 1
        if p < len(toks) and toks[p][1] == '{':
            depth, q = 0, p
            while q < len(toks):
                depth += toks[q][1] == '{'
                depth -= toks[q][1] == '}'
                if depth == 0:
                    break
                q += 1
            cands.append((qual, toks[p][3], toks[q][2]))
    best = [c for c in cands if c[0] == scope] or cands
    if not best:
        raise ValueError('no definition of %s in the source' % name)
    return best[0][1], best[0][2]


# ---------------------------------------------------------------------------------------------------- transformations

def _binary(toks, i):
    if i == 0:
        return False
    k, v = toks[i - 1][0], toks[i - 1][1]
    if v in (')', ']') or k in ('num', 'str'):
        return True
    return k == 'id' and v not in KEYWORDS and v not in TYPES


def _left(toks, i, prec):
    j, depth = i - 1, 0
    while j >= 0:
        v = toks[j][1]
        if v in (')', ']'):
            depth += 1
        elif v in ('(', '['):
            if depth == 0:
                break
            depth -= 1
        elif depth == 0 and (v in STOPS or (v in PREC and _binary(toks, j) and PREC[v] > prec)):
            break
        j -= 1
    return j + 1


def _right(toks, i, prec):
    j, depth = i + 1, 0
    while j < len(toks):
        v = toks[j][1]
        if v in ('(', '['):
            depth += 1
        elif v in (')', ']'):
            if depth == 0:
                break
            depth -= 1
        elif depth == 0 and (v in STOPS or (v in PREC and _binary(toks, j) and PREC[v] >= prec)):
            break
        j += 1
    return j - 1


def _block_end(toks, i):
    """Index of the last token of the statement starting at toks[i] (a block or a simple statement)."""
    if toks[i][1] == '{':
        depth = 0
        for j in range(i, len(toks)):
            depth += toks[j][1] == '{'
            depth -= toks[j][1] == '}'
            if depth == 0:
                return j
    depth = 0
    for j in range(i, len(toks)):
        v = toks[j][1]
        if v in ('(', '[', '{'):
            depth += 1
        elif v in (')', ']', '}'):
            depth -= 1
        elif v == ';' and depth == 0:
            return j
    return None


def transformations(body):
    """[(description, new body text)] of every single transformation of a function body."""
    toks = lex(body)
    out = []

    def sub(s, e, new):
        return body[:s] + new + body[e:]

    def where(i):
        return 'line %d' % (body.count('\n', 0, toks[i][2]) + 1)
    for i, (k, v, s, e) in enumerate(toks):
        if v in COMMUTATIVE and _binary(toks, i):
            a, b = _left(toks, i, PREC[v]), _right(toks, i, PREC[v])
            if a < i <= b:
                lt, rt = body[toks[a][2]:toks[i - 1][3]], body[toks[i + 1][2]:toks[b][3]]
                out.append(('swap %s: %s %s %s (%s)' % (v, lt, v, rt, where(i)),
                            sub(toks[a][2], toks[b][3], '%s %s %s' % (rt, v, lt))))
        if v in FLIP and _binary(toks, i):
            a, b = _left(toks, i, PREC[v]), _right(toks, i, PREC[v])
            if a < i <= b:
                lt, rt = body[toks[a][2]:toks[i - 1][3]], body[toks[i + 1][2]:toks[b][3]]
                out.append(('flip %s: %s %s %s (%s)' % (v, lt, v, rt, where(i)),
                            sub(toks[a][2], toks[b][3], '%s %s %s' % (rt, FLIP[v], lt))))
        if v == 'if' and i + 1 < len(toks) and toks[i + 1][1] == '(':
            depth, c = 0, i + 1
            while c < len(toks):
                depth += toks[c][1] == '('
                depth -= toks[c][1] == ')'
                if depth == 0:
                    break
                c += 1
            cond = body[toks[i + 1][3]:toks[c][2]]
            if c + 1 >= len(toks):
                continue
            s1e = _block_end(toks, c + 1)
            if s1e is not None and s1e + 1 < len(toks) and toks[s1e + 1][1] == 'else' and toks[s1e + 2][1] != 'if':
                s2e = _block_end(toks, s1e + 2)
                if s2e is not None:
                    a1 = body[toks[c + 1][2]:toks[s1e][3]]
                    a2 = body[toks[s1e + 2][2]:toks[s2e][3]]
                    out.append(('arms of if (%s) (%s)' % (cond.strip(), where(i)),
                                sub(toks[i][2], toks[s2e][3], 'if (!(%s)) %s else %s' % (cond, a2, a1))))
            inner = toks[i + 2:c]
            if len(inner) == 1 or (len(inner) == 3 and inner[1][1] in ('.', '->')):
                out.append(('zero-test: if (%s != 0) (%s)' % (cond, where(i)), sub(toks[i + 1][3], toks[c][2], '%s != 0' % cond)))
            if len(inner) >= 2 and inner[0][1] == '!' and len(inner) <= 4:
                rest = body[inner[1][2]:inner[-1][3]]
                out.append(('zero-test: if (%s == 0) (%s)' % (rest, where(i)), sub(toks[i + 1][3], toks[c][2], '%s == 0' % rest)))
            if len(inner) >= 3 and inner[-1][1] == '0' and inner[-2][1] in ('!=', '=='):
                rest = body[inner[0][2]:inner[-3][3]]
                new = rest if inner[-2][1] == '!=' else '!%s' % rest
                out.append(('zero-test: if (%s) (%s)' % (new, where(i)), sub(toks[i + 1][3], toks[c][2], new)))
        if v in ('++', '--') and i + 2 < len(toks) and toks[i + 1][0] == 'id' and toks[i + 2][1] == ';' and \
                (i == 0 or toks[i - 1][1] in STATEMENT_START):
            out.append(('increment: %s%s (%s)' % (toks[i + 1][1], v, where(i)), sub(s, toks[i + 1][3], toks[i + 1][1] + v)))
        if k == 'id' and i + 2 < len(toks) and toks[i + 1][1] in ('++', '--') and toks[i + 2][1] == ';' and \
                (i == 0 or toks[i - 1][1] in STATEMENT_START):
            out.append(('increment: %s%s (%s)' % (toks[i + 1][1], v, where(i)), sub(s, toks[i + 1][3], toks[i + 1][1] + v)))
    # comparisons with zero in other forms
    for i, (k, v, s, e) in enumerate(toks):
        if v in ('>', '!=', '>=') and _binary(toks, i) and i + 1 < len(toks) and toks[i + 1][1] in ('0', '1'):
            if v == '>=' and toks[i + 1][1] != '1' or v != '>=' and toks[i + 1][1] != '0':
                continue
            a = _left(toks, i, PREC[v])
            b = i + 1
            ex = body[toks[a][2]:toks[i - 1][3]]
            for new in ('%s > 0' % ex, '%s != 0' % ex, '0 < %s' % ex, '(%s)' % ex):
                if new != body[toks[a][2]:toks[b][3]]:
                    out.append(('zero-cmp: %s (%s)' % (new, where(i)), sub(toks[a][2], toks[b][3], new)))
    # a local replaced by its initializer at every later use
    for i in range(len(toks) - 3):
        if toks[i][0] == 'id' and toks[i + 1][1] == '=' and (i == 0 or toks[i - 1][0] == 'id' or toks[i - 1][1] in ('*', '&')) \
                and i >= 1 and (toks[i - 1][1] in TYPES or toks[i - 1][0] == 'id' or toks[i - 1][1] in ('*', '&')):
            name = toks[i][1]
            stmt_start = i - 1
            while stmt_start > 0 and toks[stmt_start - 1][1] not in (';', '{', '}'):
                stmt_start -= 1
            if toks[stmt_start][1] in KEYWORDS:
                continue
            end = _block_end(toks, i + 2)
            if end is None:
                continue
            init = body[toks[i + 2][2]:toks[end - 1][3]]
            uses = [j for j in range(end + 1, len(toks)) if toks[j][0] == 'id' and toks[j][1] == name
                    and toks[j - 1][1] not in ('.', '->', '::')]
            if not uses or any(toks[j + 1][1] in ASSIGN | {'++', '--'} for j in uses if j + 1 < len(toks)):
                continue
            new = body[:toks[stmt_start][2]]
            pos = toks[end][3]
            for j in uses:
                new += body[pos:toks[j][2]] + '(%s)' % init
                pos = toks[j][3]
            new += body[pos:]
            out.append(('inline: %s = %s at %d use(s) (%s)' % (name, init.strip()[:40], len(uses), where(i)), new))
    # adjacent simple statements in the same block
    starts = [0] + [j + 1 for j, t in enumerate(toks) if t[1] in (';', '{', '}')]
    simple = []
    for st in starts:
        if st >= len(toks) or toks[st][1] in ('}', '{') or toks[st][1] in KEYWORDS:
            continue
        en = _block_end(toks, st)
        if en is None or any(t[1] in ('{', '}') for t in toks[st:en + 1]):
            continue
        simple.append((st, en))
    for (s1, e1), (s2, e2) in zip(simple, simple[1:]):
        if s2 == e1 + 1:
            first, second = body[toks[s1][2]:toks[e1][3]], body[toks[s2][2]:toks[e2][3]]
            gap = body[toks[e1][3]:toks[s2][2]]
            out.append(('order: swap "%s" and "%s" (%s)' % (first.strip()[:40], second.strip()[:40], where(s1)),
                        sub(toks[s1][2], toks[e2][3], second + gap + first)))
    seen, uniq = set(), []
    for d, t in out:
        if t != body and t not in seen:
            seen.add(t)
            uniq.append((d, t))
    return uniq


# ---------------------------------------------------------------------------------------------------- search

def score(src_path, text, symbol, target, workdir, env):
    """Compile a variant of the source file; (matching words, total words, exact) of the function, or None."""
    os.makedirs(workdir, exist_ok=True)
    path = os.path.join(workdir, os.path.basename(src_path))
    open(path, 'w', newline='').write(text)
    obj = os.path.join(workdir, 'v.obj')
    if os.path.exists(obj):
        os.remove(obj)
    r = subprocess.run([os.path.join(BIN, 'cl.exe')] + FLAGS + ['/I' + os.path.dirname(src_path), '/Fo' + obj, path],
                       env=env, capture_output=True, text=True)
    if r.returncode:
        return None
    for n, code, rel in coff.functions(obj):
        if symbol in n:
            exact, ratio = coff.compare(code, target, rel)
            total = max(len(code), len(target)) // 4
            return round(ratio * total), total, exact
    return None


def search(src, symbol, target, workdir, rounds=6, budget=400, jobs=None, log=print, start_text=None):
    """Greedy search from the file's current text (or start_text). Returns dict(baseline, best, steps, compiles, diff,
    text)."""
    env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'],
               INCLUDE=os.path.join(XDK, 'include', 'xbox') + ';' + os.path.join(ROOT, 'include'))
    src_path = os.path.join(ROOT, src)
    original = start_text if start_text is not None else open(src_path, newline='').read()
    shutil.rmtree(workdir, ignore_errors=True)
    base = score(src_path, original, symbol, target, os.path.join(workdir, 'base'), env)
    if base is None:
        raise ValueError('the file does not compile, or %s is not in it' % symbol)
    jobs = jobs or max(2, (os.cpu_count() or 4) - 1)
    text, best, steps, compiles = original, base, [], 1
    log('baseline: %d of %d words match' % (best[0], best[1]))
    for rnd in range(rounds):
        if best[2] or compiles >= budget:
            break
        start, end = find_body(text, symbol)
        body = text[start:end]
        cands = transformations(body)[:max(0, budget - compiles)]
        if not cands:
            break
        with concurrent.futures.ThreadPoolExecutor(jobs) as pool:
            futs = {pool.submit(score, src_path, text[:start] + t + text[end:], symbol, target,
                                os.path.join(workdir, 'r%d_%d' % (rnd, k)), env): (d, t) for k, (d, t) in enumerate(cands)}
            results = [(f.result(), futs[f]) for f in concurrent.futures.as_completed(futs)]
        compiles += len(cands)
        ok = [(s, d, t) for s, (d, t) in results if s is not None]
        log('round %d: %d candidates, %d compiled' % (rnd + 1, len(cands), len(ok)))
        if not ok:
            break
        s, d, t = max(ok, key=lambda x: (x[0][2], x[0][0], -len(x[2])))
        if (s[2], s[0]) <= (best[2], best[0]):
            break
        text = text[:start] + t + text[end:]
        best = s
        steps.append(dict(transformation=d, words=s[0], of=s[1], exact=s[2]))
        log('  kept: %s -> %d of %d words%s' % (d, s[0], s[1], ' EXACT' if s[2] else ''))
    diff = ''.join(difflib.unified_diff(original.splitlines(True), text.splitlines(True), src, src + ' (searched)', n=1))
    return dict(baseline=dict(words=base[0], of=base[1], exact=base[2]), best=dict(words=best[0], of=best[1], exact=best[2]),
                steps=steps, compiles=compiles, diff=diff, text=text)


def recovery_test(manifest, read, limit=8, log=print):
    """End to end: break solved functions with one transformation each and require the search to restore an exact
    match. Returns (recovered, tried)."""
    env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'],
               INCLUDE=os.path.join(XDK, 'include', 'xbox') + ';' + os.path.join(ROOT, 'include'))
    tried = recovered = 0
    work = os.path.join(ROOT, 'build', 'cd2', 'search_test')
    for src, entries in manifest['files'].items():
        text = open(os.path.join(ROOT, src), newline='').read()
        for e in entries:
            if tried >= limit:
                return recovered, tried
            if not e.get('matching', True) or e.get('ltcg') or e.get('folded'):
                continue
            try:
                start, end = find_body(text, e['symbol'])
            except ValueError:
                continue
            va = int(e['address'], 16)
            target = read(va, e['size'])
            for d, body in transformations(text[start:end]):
                if d.startswith('inline'):
                    continue  # one-way: without the local's type the search cannot undo it
                broken = text[:start] + body + text[end:]
                sc = score(os.path.join(ROOT, src), broken, e['symbol'], target, os.path.join(work, 'probe'), env)
                if sc is None or sc[2]:
                    continue  # does not compile, or still exact: not a useful perturbation
                tried += 1
                res = search(src, e['symbol'], target, os.path.join(work, 'run'), rounds=3, budget=150, log=lambda m: None,
                             start_text=broken)
                ok = res['best']['exact']
                recovered += ok
                log('%s %-50s broken by "%s": %s' % (e['address'], e['symbol'][:50], d[:60],
                                                       'recovered' if ok else 'NOT recovered (%d/%d)' % (res['best']['words'], res['best']['of'])))
                break
    return recovered, tried


def self_test():
    """The transformations on a small body: each kind must appear and every result must still lex."""
    body = '''
        int a = x * y + z;
        int n = g();
        if (n > 0) { a = n; }
        if (p) { a = 1; } else { a = 2; }
        if (!q) a++;
        b = c < d;
        e = f;
'''
    kinds = {d.split(':')[0].split(' ')[0] for d, _ in transformations(body)}
    want = {'swap', 'flip', 'arms', 'zero-test', 'increment', 'order', 'zero-cmp', 'inline'}
    for k in sorted(want):
        print('self-test %-10s %s' % (k, 'ok' if k in kinds else 'MISSING'))
    probe = 'void T::F(int a) const { return; }\nint G(int b) { return b; }\n'
    s, e = find_body(probe, '?F@T@@QBAXH@Z')
    located = probe[s:e].strip() == 'return;'
    print('self-test %-10s %s' % ('locate', 'ok' if located else 'WRONG'))
    return want <= kinds and located


if __name__ == '__main__':
    if '--self-test' in sys.argv:
        sys.exit(0 if self_test() else 1)
    print(__doc__)
