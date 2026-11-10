"""The contributor tools hold no undefined global names and no unused imports (a stdlib stand-in for pyflakes, so
the gates need no extra package)."""
import ast, builtins, os, symtable, tempfile, unittest

TOOLS = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), 'tools')


def modules():
    return sorted(os.path.join(TOOLS, f) for f in os.listdir(TOOLS) if f.endswith('.py'))


def source(path):
    with open(path, encoding='utf-8') as fh:
        return fh.read()


def undefined_names(path):
    """Global names a module or its functions use that the module never binds."""
    top = symtable.symtable(source(path), path, 'exec')
    bound = set(dir(builtins)) | {'__file__', '__name__', '__doc__', '__builtins__'}
    for s in top.get_symbols():
        if s.is_assigned() or s.is_imported() or s.is_namespace():
            bound.add(s.get_name())
    out = []

    def walk(t):
        for s in t.get_symbols():
            if s.is_referenced() and s.is_global() and s.get_name() not in bound:
                out.append('%s uses %s' % (t.get_name(), s.get_name()))
        for c in t.get_children():
            walk(c)
    for s in top.get_symbols():
        if s.is_referenced() and s.get_name() not in bound:
            out.append('module uses %s' % s.get_name())
    for c in top.get_children():
        walk(c)
    return out


def unused_imports(path):
    """Names a module imports at its top level and never uses (a name in __all__ counts as used)."""
    tree = ast.parse(source(path), path)
    imported = {}
    for node in tree.body:
        if isinstance(node, (ast.Import, ast.ImportFrom)):
            for a in node.names:
                name = (a.asname or a.name).split('.')[0]
                imported[name] = node.lineno
    used = {n.id for n in ast.walk(tree) if isinstance(n, ast.Name)}
    used |= {n.value.id for n in ast.walk(tree) if isinstance(n, ast.Attribute) and isinstance(n.value, ast.Name)}
    for node in ast.walk(tree):
        if isinstance(node, ast.Assign) and any(isinstance(t, ast.Name) and t.id == '__all__' for t in node.targets):
            used |= {e.value for e in getattr(node.value, 'elts', []) if isinstance(e, ast.Constant)}
    return ['line %d imports %s' % (line, name) for name, line in sorted(imported.items(), key=lambda x: x[1])
            if name not in used]


class ToolsLint(unittest.TestCase):
    def test_no_undefined_names(self):
        found = ['%s: %s' % (os.path.basename(p), x) for p in modules() for x in undefined_names(p)]
        self.assertEqual(found, [])

    def test_no_unused_imports(self):
        found = ['%s: %s' % (os.path.basename(p), x) for p in modules() for x in unused_imports(p)]
        self.assertEqual(found, [])

    def test_the_checks_catch_their_cases(self):
        with tempfile.TemporaryDirectory(prefix='cd2lint_') as d:
            path = os.path.join(d, 'planted.py')
            with open(path, 'w', encoding='utf-8') as fh:
                fh.write('import os, json\n\ndef f():\n    return json.dumps(undefined_thing)\n')
            self.assertEqual(undefined_names(path), ['f uses undefined_thing'])
            self.assertEqual(unused_imports(path), ['line 1 imports os'])


if __name__ == '__main__':
    unittest.main()
