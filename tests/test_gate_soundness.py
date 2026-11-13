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


class JumpTableLabelTests(unittest.TestCase):
    """A jump-table entry (ADDR32) resolves through the symbol its relocation names, not through the label's name:
    every function of an object with a switch has its own $LN labels, with the same names."""

    def obj(self, target_symbol):
        o = object.__new__(relocs.Obj)
        table = words(0, 0x48000000, 0x4E800020)  # one jump-table word, then code
        o.sections = [dict(ch=0x20, data=table, relocs=[(0, target_symbol, relocs.ADDR32)]),
                      dict(ch=0x20, data=words(0x60000000, 0x60000000, 0x4E800020), relocs=[])]
        o.symbols = {0: dict(name='f', value=0, sec=1, type=0x20, cls=2), 1: dict(name='g', value=0, sec=2, type=0x20, cls=2),
                     2: dict(name='$LN5', value=8, sec=1, type=0, cls=6), 3: dict(name='$LN5', value=4, sec=2, type=0, cls=6)}
        return o

    def test_the_label_of_the_function_itself(self):
        self.assertEqual(self.obj(2).local_address_offset('f', 0, '$LN5'), 8)

    def test_another_functions_label_of_the_same_name_is_refused(self):
        with self.assertRaises(ValueError):
            self.obj(3).local_address_offset('f', 0, '$LN5')


class IdenticalCopiesTests(unittest.TestCase):
    """One file's internal datum may resolve to two CD2 addresses only when relocs.LTCG_SHARED_COPIES lists its name,
    one address is the listed shared copy, and both hold identical, not all-zero copies of its exact size (LTCG's
    inlined HasAncestor reads one object's g_GlobalConstants in every object)."""
    name = '?g_GlobalConstants@Fun_Runtime@@3UtGlobalConstants@1@A'
    shared = relocs.LTCG_SHARED_COPIES[name]
    memory = {shared: words(0, 1, 2, 100), 0x2000: words(0, 1, 2, 100), 0x3000: words(0, 1, 2, 101),
              0x4000: words(0, 1, 2, 100)}

    class Obj:
        def __init__(self, internal, size, exact=True, name=None):
            self.internal, self.size, self.exact, self.name = internal, size, exact, name

        def symbol_bytes(self, name, n):
            return None

        def data_symbol(self, name):
            if name != self.name:
                return None
            return dict(data=None, size=self.size, exact=self.exact, comdat=False, relocations=[])

    def problems(self, *addrs, name=None, size=16, exact=True, internal=True, data=True, memory=None):
        name = name or self.name
        obj = self.Obj({name} if internal else set(), size, exact, name if data else None)
        entries = [('f.cpp', 'f%d' % k, name, a, 'data', 0, obj) for k, a in enumerate(addrs)]
        mem = memory or self.memory
        return relocs.check_consistency(entries, lambda va, n: mem[va][:n], {}, {})

    def test_own_copy_and_the_shared_copy_are_one_datum(self):
        self.assertFalse(self.problems(self.shared, 0x2000))

    def test_a_copy_that_differs_is_caught(self):
        self.assertTrue(self.problems(self.shared, 0x3000))

    def test_identical_copies_without_the_shared_one_are_caught(self):
        self.assertTrue(self.problems(0x2000, 0x4000))

    def test_a_third_copy_is_caught(self):
        self.assertTrue(self.problems(self.shared, 0x2000, 0x4000))

    def test_an_unlisted_name_is_caught(self):
        self.assertTrue(self.problems(self.shared, 0x2000, name='?fOther@@3UtGlobalConstants@Fun_Runtime@@A'))

    def test_zero_copies_are_caught(self):
        self.assertTrue(self.problems(self.shared, 0x2000, memory={self.shared: bytes(16), 0x2000: bytes(16)}))

    def test_a_size_that_is_not_exact_is_caught(self):
        self.assertTrue(self.problems(self.shared, 0x2000, exact=False))

    def test_an_external_name_is_caught(self):
        self.assertTrue(self.problems(self.shared, 0x2000, internal=False))

    def test_a_function_is_caught(self):
        self.assertTrue(self.problems(self.shared, 0x2000, data=False))


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
