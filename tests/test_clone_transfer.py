"""Clone drafts retain private layouts without importing unrelated code/data."""

from pathlib import Path
import sys
from types import SimpleNamespace
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from clone_transfer import describe, file_scope_types, substitute
from m2c_integrate import private_types


class PrivateTypeTests(unittest.TestCase):
    def test_nested_layout_and_typedef_survive(self):
        layout = 'struct View { u8 padding[4]; union { u16 value; u8 bytes[2]; } field; };'
        alias = 'typedef struct View View;'
        self.assertEqual(file_scope_types(layout + '\n' + alias), [layout, alias])

    def test_skips_data_functions_and_block_local_types(self):
        text = '''struct Kept { u8 value; };
struct Data { u8 value; } object;
void other(void) {
typedef u8 Local;
struct Hidden { u8 value; };
}
static const u8 table[] = { 1, 2 };
'''
        self.assertEqual(file_scope_types(text), ['struct Kept { u8 value; };'])

    def test_comments_and_strings_do_not_change_scope(self):
        text = '''/* { ; } */
struct View {
    u8 byte; /* } ; */
};
void other(void) { const char *s = "}"; char c = '}'; }
enum Mode { A, B };
'''
        types = file_scope_types(text)
        self.assertEqual(len(types), 2)
        self.assertTrue(types[0].startswith('struct View'))
        self.assertEqual(types[1], 'enum Mode { A, B };')

    def test_integrator_rejects_non_type_output(self):
        self.assertIsNone(private_types(['static u8 data[4];']))
        self.assertEqual(private_types([]), {})

    def test_integrator_tracks_layout_conflicts_by_tag(self):
        a = 'struct View { u8 padding[4]; u16 value; };'
        b = 'struct View { u8 padding[8]; u16 value; };'
        self.assertEqual(private_types([a]), {'struct View': a})
        self.assertEqual(private_types([b]), {'struct View': b})
        self.assertIsNone(private_types([a, b]))

    def test_integrator_keeps_tag_and_typedef_namespaces_distinct(self):
        layout = 'struct View { u8 value; };'
        alias = 'typedef struct View View;'
        self.assertEqual(private_types([layout, alias]), {'struct View': layout, 'typedef View': alias})


class ConstantTransferTests(unittest.TestCase):
    def test_shifted_constants_transfer_as_source_values(self):
        def code(immediate, shift):
            return {0: SimpleNamespace(mnemonic='movs', op_str=f'r0, #{immediate}'),
                    2: SimpleNamespace(mnemonic='lsls', op_str=f'r0, r0, #{shift}')}
        twin = describe(b'', code(248, 5), 0, None, fold_constants=True)
        target = describe(b'', code(128, 6), 0, None, fold_constants=True)
        self.assertEqual(substitute('frame = 0x1F00;', twin, target, None), 'frame = 0x2000;')

    def test_numeric_replacements_do_not_cascade(self):
        twin = [('imm', (1,)), ('imm', (2,))]
        target = [('imm', (2,)), ('imm', (3,))]
        self.assertEqual(substitute('a = 1; b = 2;', twin, target, None), 'a = 2; b = 3;')

    def test_layout_can_imply_changed_offsets_without_literal_spellings(self):
        twin = [('imm', (8,)), ('imm', (12,))]
        target = [('imm', (16,)), ('imm', (20,))]
        source = 'struct View { u8 padding[8]; u32 value; u8 flag; };\nview->flag = 1;'
        expected = source.replace('padding[8]', 'padding[0x10]')
        self.assertEqual(substitute(source, twin, target, None), expected)

    def test_different_register_shift_is_not_folded(self):
        code = {0: SimpleNamespace(mnemonic='movs', op_str='r0, #248'),
                2: SimpleNamespace(mnemonic='lsls', op_str='r1, r1, #5')}
        self.assertEqual(describe(b'', code, 0, None, fold_constants=True), [('imm', (248,)), ('imm', (5,))])


if __name__ == '__main__':
    unittest.main()
