"""Synthetic regressions for the gates' soundness: no game executable or XDK is needed."""
import pathlib
import struct
import sys
import unittest

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parents[1] / 'tools'))
import coff
import facts
import relocs
import verify_src


def words(*ws):
    return struct.pack('>%dI' % len(ws), *ws)


class RelocatedFieldTests(unittest.TestCase):
    """A relocated word may differ only in the field its relocation patches."""
    # lis r11, g@ha ; lwz r3, g@l(r11) ; blr
    ours = words(0x3D600000, 0x806B0000, 0x4E800020)
    rel = coff.Relocations([(0, relocs.REFHI), (0, coff.PAIR), (4, relocs.REFLO), (4, coff.PAIR)])

    def test_linked_immediates_are_accepted(self):
        self.assertTrue(coff.compare(self.ours, words(0x3D608393, 0x806BC9A4, 0x4E800020), self.rel)[0])

    def test_destination_register_of_a_relocated_load_is_compared(self):
        self.assertFalse(coff.compare(self.ours, words(0x3D608393, 0x808BC9A4, 0x4E800020), self.rel)[0])

    def test_base_register_of_a_relocated_load_is_compared(self):
        self.assertFalse(coff.compare(self.ours, words(0x3D608393, 0x806AC9A4, 0x4E800020), self.rel)[0])

    def test_register_of_a_relocated_lis_is_compared(self):
        self.assertFalse(coff.compare(self.ours, words(0x3D408393, 0x806BC9A4, 0x4E800020), self.rel)[0])

    def test_call_and_jump_differ(self):
        call = coff.Relocations([(0, relocs.REL24)])
        self.assertTrue(coff.compare(words(0x48000001), words(0x48001231), call)[0])   # bl to another target
        self.assertFalse(coff.compare(words(0x48000001), words(0x48001230), call)[0])  # b: the link bit differs
        self.assertFalse(coff.compare(words(0x48000001), words(0x48001233), call)[0])  # bla: the absolute bit differs

    def test_facts_hash_keeps_registers(self):
        linked = words(0x3D608393, 0x806BC9A4, 0x4E800020)
        other = words(0x3D608393, 0x808BC9A4, 0x4E800020)
        moved = words(0x3D608394, 0x806B1234, 0x4E800020)
        self.assertEqual(facts.mask(linked, self.rel), facts.mask(moved, self.rel))
        self.assertNotEqual(facts.mask(linked, self.rel), facts.mask(other, self.rel))


class SymbolMatchTests(unittest.TestCase):
    def test_prefix_names_the_function(self):
        self.assertTrue(verify_src.symbol_matches('?RetClass@cX@AI@@', '?RetClass@cX@AI@@UBAABVcClass@Fun_Runtime@@XZ'))

    def test_prefix_does_not_name_a_thunk(self):
        for name in ('?RetClass@cX@AI@@WBA@BAABVcClass@Fun_Runtime@@XZ', '?RetClass@cX@AI@@GBA@BAABVcClass@Fun_Runtime@@XZ',
                     '?RetClass@cX@AI@@OBA@BAABVcClass@Fun_Runtime@@XZ'):
            with self.subTest(name=name):
                self.assertFalse(verify_src.symbol_matches('?RetClass@cX@AI@@', name))
        self.assertFalse(verify_src.symbol_matches('?f@C@@', '?f@C@@$4PPPPPPPM@A@AAXXZ'))  # a vtordisp thunk

    def test_template_arguments_after_the_prefix_are_not_a_thunk(self):
        # `$0CFI@` is the template value 600, not a vtordisp code; `H` is an int argument, not a private adjustor
        self.assertTrue(verify_src.symbol_matches('?Reset@?$cPool@URopeSegmentData@VFX@@',
                                                  '?Reset@?$cPool@URopeSegmentData@VFX@@$0CFI@@Fun_Runtime@@QAAXXZ'))
        self.assertTrue(verify_src.symbol_matches('?f@?$T@', '?f@?$T@H@@QAAXXZ'))

    def test_a_symbol_with_the_thunk_code_names_the_thunk(self):
        self.assertTrue(verify_src.symbol_matches('??_EcBloom@VFX@@WBI@', '??_EcBloom@VFX@@WBI@AAPAXI@Z'))

    def test_a_vcall_thunk_is_named_by_its_prefix(self):
        self.assertTrue(verify_src.symbol_matches('??_9cChaseBehaviour@AI@@', '??_9cChaseBehaviour@AI@@$BBA@AA'))

    def test_a_symbol_inside_another_name_does_not_name_it(self):
        self.assertFalse(verify_src.symbol_matches('?ms_pcXClass@cX@AI@@', '??__E?ms_pcXClass@cX@AI@@2PBVcClass@@B@@YAXXZ'))

    def test_c_names_are_exact(self):
        self.assertTrue(verify_src.symbol_matches('resume', 'resume'))
        self.assertFalse(verify_src.symbol_matches('resume', 'lua_resume'))


class ImageTests(unittest.TestCase):
    def test_another_image_is_refused(self):
        # a one-section PE that is not the extracted game image
        pe = 0x40
        exe = bytearray(0x200)
        struct.pack_into('<I', exe, 0x3C, pe)
        struct.pack_into('<H', exe, pe + 6, 1)
        struct.pack_into('<H', exe, pe + 20, 0xE0)
        struct.pack_into('<I', exe, pe + 24 + 28, 0x82000000)
        struct.pack_into('<I', exe, pe + 24 + 16, 0x3BF8C8)
        struct.pack_into('<8sIIII', exe, pe + 24 + 0xE0, b'.text', 0x10, 0x1000, 0x10, 0x180)
        with self.assertRaises(SystemExit):
            verify_src.pe_reader(bytes(exe))


if __name__ == '__main__':
    unittest.main()
