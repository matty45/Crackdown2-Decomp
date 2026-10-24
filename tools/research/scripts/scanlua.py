import os, sys, re
root = sys.argv[1]
pat = re.compile(rb'\x1bLua[\x50\x51]|\bfunction\s+\w+\s*\([^)]{0,40}\)\s*\n|\.lua\b')
for dp, dn, fn in os.walk(root):
    for f in fn:
        p = os.path.join(dp, f)
        try:
            if os.path.getsize(p) > 200 * 1024 * 1024:
                continue
            d = open(p, 'rb').read()
        except OSError:
            continue
        hits = pat.findall(d)
        if hits:
            kinds = {}
            for h in hits:
                k = 'bytecode' if h.startswith(b'\x1bLua') else ('.lua name' if h == b'.lua' else 'source')
                kinds[k] = kinds.get(k, 0) + 1
            names = sorted(set(m.group(0).decode('latin-1') for m in re.finditer(rb'[\w/\\.-]{2,60}\.lua\b', d)))[:8]
            print(os.path.relpath(p, root), kinds, names)
