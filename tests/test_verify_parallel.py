"""Regression tests for verification scheduling; no game or XDK required.

Run: py -I -m unittest discover -s tests -p test_verify_parallel.py
"""
import argparse
import contextlib
import io
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import threading
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import cd2
import facts
import verify_ltcg
from verify_src import parallel_map, verification_jobs


class ParallelVerificationTests(unittest.TestCase):
    def test_workers_overlap_but_results_keep_input_order(self):
        barrier = threading.Barrier(2)
        second_finished = threading.Event()

        def work(n):
            barrier.wait(timeout=5)
            if n == 0:
                self.assertTrue(second_finished.wait(timeout=5))
            else:
                second_finished.set()
            return n

        self.assertEqual(list(parallel_map(work, [0, 1], jobs=2)), [0, 1])

    def test_serial_mode_and_worker_failures(self):
        caller = threading.get_ident()
        self.assertEqual(list(parallel_map(lambda _: threading.get_ident(), range(3), jobs=1)), [caller] * 3)

        def fail(_):
            raise RuntimeError('compiler failed')

        for jobs in (1, 2):
            with self.subTest(jobs=jobs), self.assertRaisesRegex(RuntimeError, 'compiler failed'):
                list(parallel_map(fail, [0], jobs=jobs))

    def test_worker_limit_and_override(self):
        with patch.dict(os.environ, {}, clear=True), patch('verify_src.os.cpu_count', return_value=32):
            self.assertEqual(verification_jobs(), 8)
        with patch.dict(os.environ, {}, clear=True), patch('verify_src.os.cpu_count', return_value=None):
            self.assertEqual(verification_jobs(), 1)
        with patch.dict(os.environ, {'CD2_VERIFY_JOBS': '2'}):
            self.assertEqual(verification_jobs(), 2)
            self.assertEqual(verification_jobs(3), 3)
        for value in (0, -1, 'invalid'):
            with self.subTest(value=value), self.assertRaises(ValueError):
                verification_jobs(value)

    def test_failed_gate_does_not_skip_later_gates(self):
        def run(command, **kwargs):
            self.assertEqual(kwargs['env']['CD2_VERIFY_JOBS'], '3')
            failed = command[2].endswith('verify_ltcg.py') and '--self-test' not in command
            return subprocess.CompletedProcess(command, int(failed), 'self-test example caught\n', '')

        with patch.dict(os.environ, {'CD2_VERIFY_JOBS': '1'}), \
                patch.object(cd2, 'toolchain_problems', return_value=[]), \
                patch.object(cd2, 'cmd_lint', return_value=dict(files=[], without_code=0)) as lint, \
                patch.object(cd2, 'policy_self_test', return_value=(True, [dict(ok=True)])), \
                patch.object(cd2.subprocess, 'run', side_effect=run) as child, \
                contextlib.redirect_stderr(io.StringIO()):
            result = cd2.cmd_verify(argparse.Namespace(exe=None, facts=False, jobs=3))
            self.assertEqual(os.environ['CD2_VERIFY_JOBS'], '1')
        self.assertFalse(result['ok'])
        self.assertEqual(result['jobs'], 3)
        self.assertEqual(len(result['gates']), 14)
        self.assertEqual(child.call_count, 11)
        self.assertEqual(lint.call_args.args[0].jobs, 3)
        self.assertEqual([g['gate'] for g in result['gates'] if not g['ok']],
                         ['LTCG build + LTCG relocation targets'])
        self.assertEqual(result['gates'][-1]['gate'], 'self-test: search transformations')
        self.assertIn('target facts (no game)', [g['gate'] for g in result['gates']])
        self.assertTrue(all(g['seconds'] >= 0 for g in result['gates']))

    def test_facts_reuses_objects_and_isolates_duplicate_basenames(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            sources = ['src/one/same.cpp', 'src/two/same.cpp']
            manifest = root / 'manifest.json'
            manifest.write_text(json.dumps(dict(files={src: [] for src in sources})))
            target = root / 'facts.json'
            target.write_text(json.dumps(dict(files={}, functions={})))
            work = root / 'work'
            work.mkdir()
            objects = {}

            def compile_plain(src, d, override):
                obj = str(Path(d) / 'same.obj')
                objects[src] = obj
                return obj

            def build_ltcg(srcpath, plain, consts, d, env, extra_flags):
                src = os.path.relpath(srcpath, facts.ROOT).replace('\\', '/')
                self.assertEqual(plain, objects[src])
                return None, [], 0

            with patch.object(facts, 'MANIFEST', str(manifest)), patch.object(facts, 'FACTS', str(target)), \
                    patch.object(facts.tempfile, 'mkdtemp', return_value=str(work)), \
                    patch.object(facts, 'compile_plain', side_effect=compile_plain) as compile_, \
                    patch.object(facts.coff, 'functions', return_value=[]), \
                    patch.object(facts.relocs, 'Obj'), \
                    patch.object(facts.relocs, 'check_consistency', return_value=[]), \
                    patch.object(facts.verify_ltcg, 'build_ltcg', side_effect=build_ltcg) as build, \
                    patch.object(facts.verify_ltcg, 'map_symbols', return_value=[]):
                self.assertEqual(facts.verify(out=lambda _: None), (True, []))
            self.assertEqual(compile_.call_count, 2)
            self.assertEqual(len(set(objects.values())), 2)
            self.assertEqual(len({call.args[3] for call in build.call_args_list}), 2)

    def test_ltcg_build_failure_cannot_pass_an_empty_total(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'config').mkdir()
            (root / 'config' / 'matched_functions.json').write_text(json.dumps(dict(files={'src/file.cpp': []})))
            exe = root / 'input.exe'
            exe.write_bytes(b'')
            with patch.object(verify_ltcg, 'ROOT', directory), \
                    patch.object(sys, 'argv', ['verify_ltcg.py', str(exe)]), \
                    patch.object(verify_ltcg, 'check_toolchain'), \
                    patch.object(verify_ltcg, 'pe_reader', return_value=(None, verify_ltcg.EXPECTED_ENTRY)), \
                    patch.object(verify_ltcg, 'check_file', return_value=None), \
                    patch.object(verify_ltcg.relocs, 'load_aliases', return_value={}), \
                    patch.object(verify_ltcg.relocs, 'check_consistency', return_value=[]), \
                    contextlib.redirect_stdout(io.StringIO()), self.assertRaises(SystemExit) as exited:
                verify_ltcg.main()
            self.assertEqual(exited.exception.code, 1)


if __name__ == '__main__':
    unittest.main()
