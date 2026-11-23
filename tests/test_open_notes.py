"""show's open-function notes: a docs/open-functions.md entry reaches every function it names, alone or inside a
range, with its continuation lines, and nothing else. No game executable or XDK is needed."""
import os
import pathlib
import sys
import tempfile
import unittest

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parents[1] / 'tools'))
import cd2  # noqa: E402

NOTES = """# Open functions: what was tried

Entries name addresses such as 0x82000010; this paragraph is not an entry.

## src/a.cpp

- `A::f` (0x82000010): the first line
  continues here, blocked on 0x82000100.
- Thunks 0x82000020..0x82000040 lie in another file's split range.
"""


class OpenNotesTests(unittest.TestCase):
    def setUp(self):
        fd, self.path = tempfile.mkstemp(suffix='.md')
        with os.fdopen(fd, 'w', encoding='utf-8') as f:
            f.write(NOTES)

    def tearDown(self):
        os.remove(self.path)

    def notes(self, addr):
        return cd2.open_notes(addr, self.path)

    def test_an_entry_reaches_every_address_it_names(self):
        whole = '`A::f` (0x82000010): the first line continues here, blocked on 0x82000100.'
        self.assertEqual(self.notes(0x82000010), [whole])
        self.assertEqual(self.notes(0x82000100), [whole])

    def test_a_range_covers_its_inside_and_ends(self):
        for a in (0x82000020, 0x82000030, 0x82000040):
            self.assertEqual(self.notes(a), ['Thunks 0x82000020..0x82000040 lie in another file\'s split range.'])

    def test_other_addresses_and_prose_get_nothing(self):
        self.assertEqual(self.notes(0x82000044), [])
        self.assertEqual(self.notes(0x82000000), [])

    def test_a_missing_file_has_no_notes(self):
        self.assertEqual(cd2.open_notes(0x82000010, self.path + '.missing'), [])


if __name__ == '__main__':
    unittest.main()
