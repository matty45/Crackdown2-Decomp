"""The gates' speed-ups must not change a verdict: the manifest index answers as the loop over every symbol did, the
remembered tables are read again once they change, and a cache keeps a result only under a key that covers what it
came from. No game executable or XDK is needed."""
import os
import pathlib
import sys
import tempfile
import time
import unittest
from unittest import mock

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parents[1] / 'tools'))
import buildcache
import verify_src


class ManifestIndexTests(unittest.TestCase):
    manifest = {'files': {
        'a.cpp': [dict(address='0x82000000', symbol='?RetClass@cX@AI@@'), dict(address='0x82000010', symbol='resume'),
                  dict(address='0x82000020', symbol='?f@C@@', matching=False)],
        'b.cpp': [dict(address='0x82000030', symbol='?RetClass@cX@'),
                  dict(address='0x82000040', symbol='??_EcBloom@VFX@@WBI@'),
                  dict(address='0x82000050', symbol='?Reset@?$cPool@URopeSegmentData@VFX@@')]}}
    names = ['?RetClass@cX@AI@@UBAABVcClass@Fun_Runtime@@XZ', '?RetClass@cX@AI@@WBA@BAABVcClass@Fun_Runtime@@XZ',
             'resume', 'lua_resume', 'resume_error', '?f@C@@QAAXXZ', '??_EcBloom@VFX@@WBI@AAPAXI@Z',
             '?Reset@?$cPool@URopeSegmentData@VFX@@@VFX@@QAAXXZ', '?Other@@YAXXZ', '']

    def every_symbol(self, name):
        return [(f, e['address']) for f, es in self.manifest['files'].items() for e in es
                if e.get('matching', True) and verify_src.symbol_matches(e['symbol'], name)]

    def test_same_answers_as_every_symbol(self):
        index = verify_src.ManifestIndex(self.manifest)
        for name in self.names:
            with self.subTest(name=name):
                self.assertEqual([(f, e['address']) for f, e in index.naming(name)], self.every_symbol(name))

    def test_hits_come_in_manifest_order(self):
        # b.cpp's symbol is the shorter prefix, found first; a.cpp's entry still comes first, as in the manifest
        index = verify_src.ManifestIndex(self.manifest)
        self.assertEqual([f for f, _ in index.naming(self.names[0])], ['a.cpp', 'b.cpp'])

    def test_one_index_per_manifest(self):
        self.assertIs(verify_src.manifest_index(self.manifest), verify_src.manifest_index(self.manifest))
        self.assertIsNot(verify_src.manifest_index(self.manifest), verify_src.manifest_index(dict(self.manifest)))


class RememberedTableTests(unittest.TestCase):
    def test_a_changed_table_is_read_again(self):
        with tempfile.TemporaryDirectory() as d:
            path = os.path.join(d, 'file_flags.txt')
            open(path, 'w').write('src/a.cpp /Ob2\n')
            self.assertEqual(verify_src.load_file_flags(path), [('src/a.cpp', ['/Ob2'])])
            open(path, 'w').write('src/a.cpp /Ob2\nsrc/b.cpp /O1\n')
            self.assertEqual(verify_src.load_file_flags(path), [('src/a.cpp', ['/Ob2']), ('src/b.cpp', ['/O1'])])


class CacheKeyTests(unittest.TestCase):
    source = os.path.join(buildcache.ROOT, 'tools', 'buildcache.py')  # any file that exists

    def test_the_compilers_environment_is_part_of_the_key(self):
        cmd, env = ['cl.exe', '/c', '/Fox.obj', self.source], dict(INCLUDE='include')
        for var in ('CL', '_CL_'):
            with self.subTest(var=var):
                self.assertNotEqual(buildcache.key(cmd, env), buildcache.key(cmd, dict(env, **{var: '/Od'})))

    def test_the_output_path_is_not(self):
        env = dict(INCLUDE='include')
        self.assertEqual(buildcache.key(['cl.exe', '/c', '/Fox.obj', self.source], env),
                         buildcache.key(['cl.exe', '/c', '/Foy.obj', self.source], env))

    def test_only_repository_sources_are_cached(self):
        self.assertTrue(buildcache.cacheable(os.path.join(buildcache.ROOT, 'src', 'x.cpp')))
        self.assertFalse(buildcache.cacheable(os.path.join(tempfile.gettempdir(), 'x.cpp')))
        with mock.patch.dict(os.environ, {'CD2_NO_CACHE': '1'}):
            self.assertFalse(buildcache.cacheable(os.path.join(buildcache.ROOT, 'src', 'x.cpp')))


class PruneTests(unittest.TestCase):
    def test_least_recently_used_go_first(self):
        with tempfile.TemporaryDirectory() as d, mock.patch.object(buildcache, 'CACHE', d):
            now = time.time()

            def put(path, size, age):
                os.makedirs(os.path.dirname(path), exist_ok=True)
                open(path, 'wb').write(b'x' * size)
                os.utime(path, (now - age, now - age))
            for k, age in (('aa1', 300), ('bb2', 200), ('cc3', 100)):  # an object and its record each
                put(buildcache.entry('', k) + '.obj', 990, age)
                put(buildcache.entry('', k) + '.json', 10, age)
            put(buildcache.entry('lint', 'dd4') + '.json', 10, 50)  # a record alone
            put(buildcache.entry('', 'ee5') + '.123.456.obj', 500, 1000)  # left by a killed store: no record
            buildcache.prune(limit=2100)
            left = sorted(f for _, _, fs in os.walk(d) for f in fs)
            self.assertEqual(left, ['bb2.json', 'bb2.obj', 'cc3.json', 'cc3.obj', 'dd4.json'])


if __name__ == '__main__':
    unittest.main()
