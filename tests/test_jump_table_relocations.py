"""Synthetic regressions: no game executable or XDK is needed."""
import copy
import json
import pathlib
import struct
import sys
import tempfile
import unittest
from unittest import mock

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parents[1] / 'tools'))
import coff
import facts
import relocs
import verify_ltcg


class JumpTableTests(unittest.TestCase):
    address = 0x81000000
    name = '?SyntheticSwitch@@YAXXZ'

    def make_object(self, label=28, addend=0, section=1):
        # The function starts at section offset 16; its local label is at +12.
        code = struct.pack('>5I', 0x60000000, addend, 0x60000000, 0x60000000, 0x4E800020)
        obj = relocs.Obj.__new__(relocs.Obj)
        obj.sections = [dict(data=b'\0' * 16 + code)]
        obj.symbols = {0: dict(name='$case', value=label, sec=section)}
        obj.internal = set()
        obj.functions = lambda: {self.name: (1, 16, len(code))}
        obj.relocations = lambda _: [(4, relocs.ADDR32, '$case', 0)]
        target = bytearray(code)
        struct.pack_into('>I', target, 4, self.address + 12)
        return obj, code, bytes(target)

    def test_absolute_data_is_not_an_opcode(self):
        _, code, target = self.make_object()
        relocation = coff.Relocations([(4, coff.ADDR32)])
        self.assertTrue(coff.compare(code, target, relocation)[0])
        self.assertFalse(coff.compare(code, target, {4})[0])
        wrong = bytearray(target)
        wrong[0] ^= 4
        self.assertFalse(coff.compare(code, wrong, relocation)[0])

    def test_coff_parser_preserves_absolute_relocation_type(self):
        code = struct.pack('>3I', 0x60000000, 0, 0x4E800020)
        header = struct.pack('<HHIIIHH', 0x1F2, 1, 0, 82, 2, 0, 0)
        section = struct.pack('<8sIIIIIIHHI', b'.text', 0, 0, 12, 60, 72, 0, 1, 0, 0x20)
        relocation = struct.pack('<IIH', 4, 1, coff.ADDR32)
        function = struct.pack('<8sIhHBB', b'fn', 0, 1, 0x20, 2, 0)
        label = struct.pack('<8sIhHBB', b'$case', 8, 1, 0, 6, 0)
        with tempfile.TemporaryDirectory() as directory:
            path = pathlib.Path(directory) / 'synthetic.obj'
            path.write_bytes(header + section + code + relocation + function + label + struct.pack('<I', 4))
            functions = list(coff.functions(str(path)))
        self.assertEqual(len(functions), 1)
        self.assertEqual(functions[0][:2], ('fn', code))
        self.assertEqual(functions[0][2].absolute, {4})

    def test_instruction_opcode_guard_remains(self):
        relocation = coff.Relocations([(0, relocs.REL24)])
        self.assertTrue(coff.compare(bytes.fromhex('48000001'), bytes.fromhex('48000101'), relocation)[0])
        self.assertFalse(coff.compare(bytes.fromhex('48000001'), bytes.fromhex('60000000'), relocation)[0])

    def test_pair_and_unaligned_sites_are_not_absolute_words(self):
        relocation = coff.Relocations([(0, coff.PAIR), (5, coff.ADDR32)])
        self.assertNotIn(0, relocation)
        self.assertEqual(relocation.absolute, set())

    def test_correct_label_is_accepted(self):
        obj, _, target = self.make_object()
        resolved, problems = relocs.resolve(obj, self.name, target, self.address)
        self.assertEqual(problems, [])
        self.assertEqual(resolved, [('$case', self.address + 12, 'local address', 4)])

    def test_retargeted_label_is_rejected_despite_matching_bytes(self):
        obj, code, target = self.make_object(label=32)
        self.assertTrue(coff.compare(code, target, coff.Relocations([(4, coff.ADDR32)]))[0])
        self.assertTrue(relocs.resolve(obj, self.name, target, self.address)[1])

    def test_changed_embedded_addend_is_rejected(self):
        obj, _, target = self.make_object(addend=4)
        self.assertTrue(relocs.resolve(obj, self.name, target, self.address)[1])

    def test_signed_embedded_addend_is_resolved(self):
        obj, _, target = self.make_object(label=32, addend=0xFFFFFFFC)
        self.assertEqual(relocs.resolve(obj, self.name, target, self.address)[1], [])

    def test_external_out_of_range_and_unaligned_labels_are_rejected(self):
        for label, section in [(28, 2), (36, 1), (29, 1)]:
            with self.subTest(label=label, section=section):
                obj, _, target = self.make_object(label=label, section=section)
                self.assertTrue(relocs.resolve(obj, self.name, target, self.address)[1])

    def test_undefined_label_is_rejected(self):
        obj, _, target = self.make_object()
        obj.symbols.clear()
        self.assertTrue(relocs.resolve(obj, self.name, target, self.address)[1])

    def test_ltcg_normalizes_only_explicit_table_sites_and_keeps_destination(self):
        first = [0x60000000, self.address + 12, 0x4E800020, 0x60000000]
        second_start = self.address + 0x1000
        second = [first[0], second_start + 12, first[2], first[3]]
        self.assertEqual(verify_ltcg.masked(first, self.address, {4}),
                         verify_ltcg.masked(second, second_start, {4}))
        second[1] += 4
        self.assertNotEqual(verify_ltcg.masked(first, self.address, {4}),
                            verify_ltcg.masked(second, second_start, {4}))
        self.assertEqual(verify_ltcg.masked(first, self.address)[1], first[1])

    def test_ltcg_comparison_rejects_retargeted_linked_table(self):
        _, code, target = self.make_object()
        start = self.address + 0x1000
        linked = bytearray(code)
        struct.pack_into('>I', linked, 4, start + 12)
        symbols = [(start, self.name), (start + len(linked), 'end')]
        read = lambda address, size: bytes(linked[address - start:address - start + size])
        self.assertTrue(verify_ltcg.compare_ltcg(read, symbols, self.name, target, self.address, {4})[0])
        struct.pack_into('>I', linked, 4, start + 16)
        self.assertFalse(verify_ltcg.compare_ltcg(read, symbols, self.name, target, self.address, {4})[0])

    def test_facts_reject_retargeting_and_changed_relocation_kind(self):
        obj, code, target = self.make_object()
        relocation = coff.Relocations([(4, coff.ADDR32)])
        self.assertEqual(facts.mask(code, relocation), facts.mask(target, relocation))
        with tempfile.TemporaryDirectory() as directory:
            manifest = pathlib.Path(directory) / 'manifest.json'
            recorded = pathlib.Path(directory) / 'facts.json'
            address = '0x%08X' % self.address
            manifest.write_text(json.dumps(dict(files={'synthetic.cpp': [dict(address=address,
                                size=len(code), symbol=self.name)]})))
            snapshot = dict(functions={address: dict(size=len(code), plain=dict(
                relocations=[4], absolute_relocations=[4], sha=facts.sha(facts.mask(target, relocation)),
                targets=[[4, 'local address', '0x%08X' % (self.address + 12)]], constants={}, strings={}))})
            recorded.write_text(json.dumps(snapshot))
            with mock.patch.object(facts, 'MANIFEST', str(manifest)), \
                    mock.patch.object(facts, 'FACTS', str(recorded)), \
                    mock.patch.object(facts, 'compile_plain', return_value='synthetic.obj'), \
                    mock.patch.object(coff, 'functions', return_value=[(self.name, code, relocation)]), \
                    mock.patch.object(relocs, 'Obj', return_value=obj):
                self.assertTrue(facts.verify(ltcg=False, out=lambda _: None)[0])
                obj.symbols[0]['value'] += 4
                self.assertFalse(facts.verify(ltcg=False, out=lambda _: None)[0])
                obj.symbols[0]['value'] -= 4
                changed = copy.deepcopy(snapshot)
                changed['functions'][address]['plain'].pop('absolute_relocations')
                recorded.write_text(json.dumps(changed))
                self.assertFalse(facts.verify(ltcg=False, out=lambda _: None)[0])


if __name__ == '__main__':
    unittest.main()
