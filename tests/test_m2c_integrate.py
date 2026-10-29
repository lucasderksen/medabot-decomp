"""Multiple result queues must publish each accepted function only once."""

import contextlib
import io
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import m2c_integrate as integrate


class IntegrationQueueTests(unittest.TestCase):
    def test_callback_typedefs_survive_draft_type_extraction(self):
        source = ('typedef void (*Callback)(void);\n'
                  'typedef s32 (*Command)(u8);\n'
                  'extern Callback const table[12];\n'
                  'void example(void) {Callback local[12];memcpy(local,table,sizeof(local));local[0]();}')
        declarations, body, other = integrate.split_draft(source, 'example')
        self.assertEqual(declarations, ['extern Callback const table[12];'])
        self.assertEqual(integrate.private_types(other), {
            'typedef Callback': 'typedef void (*Callback)(void);',
            'typedef Command': 'typedef s32 (*Command)(u8);'})
        self.assertIn('Callback local[12]', body)
        self.assertIsNone(integrate.private_types(other + ['u32 unexpected_data;']))

    def test_compact_nested_function_keeps_complete_body(self):
        source = 'extern u32 value;\nvoid sub_0803536C(u32 phase){switch(phase){case 1:value++;break;default:value=0;}}'
        declarations, body, other = integrate.split_draft(source, 'sub_0803536C')
        self.assertEqual(declarations, ['extern u32 value;'])
        self.assertEqual(other, [])
        self.assertEqual(body, 'void sub_0803536C(u32 phase) {\nswitch(phase){case 1:value++;break;default:value=0;}}')

    def test_integrated_entry_does_not_require_an_experiment_draft(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'src').mkdir()
            segments, symbols, manual = [root / name for name in ('segments.json', 'symbols.json', 'manual.json')]
            existing = [dict(name='sub_08000100', start='0x100', end='0x104', kind='c',
                             source='src/existing.c', input_section='.text.sub_08000100')]
            segments.write_text(json.dumps(existing))
            symbols.write_text('{}')
            manual.write_text(json.dumps([dict(name='sub_08000100', start='0x100', end='0x104', cflags=[])]))
            with patch.multiple(integrate, ROOT=root, SEGMENTS=segments, SYMBOLS=symbols,
                                SOLVED=root / 'absent_solved.json', MANUAL=manual, HARVEST=root / 'absent.json'), \
                    patch.object(sys, 'argv', ['m2c_integrate.py']), contextlib.redirect_stdout(io.StringIO()) as output:
                integrate.main()
            self.assertIn('already integrated', output.getvalue())
            self.assertEqual(json.loads(segments.read_text()), existing)
            self.assertEqual(list((root / 'src').iterdir()), [])

    def test_grouped_declarators_keep_all_names_and_ignore_parameter_commas(self):
        self.assertEqual(integrate.declared_names('extern u32 a[8], *b, c[8];'), ['a', 'b', 'c'])
        self.assertEqual(integrate.declared_names('extern void (*a)(u32, u32), (*b[])(u8, u16);'), ['a', 'b'])
        self.assertEqual(integrate.declared_names('extern void f(u8, u16);'), ['f'])
        self.assertEqual(integrate.declared_names('extern void f(void);extern void g(void);'), ['f', 'g'])

    def test_grouped_private_aliases_preserve_every_data_address_and_conflict(self):
        first = dict(name='sub_0806113C', declarations=['extern u32 a[8], b[8], c[8], d[8];'],
                     symbols={name: {'address': address, 'kind': 'data'} for name, address in
                              zip('abcd', ('0x0202F800', '0x0202F9E0', '0x0202F9C0', '0x0202F820'))})
        self.assertEqual(integrate.collect_symbols([{'functions': [first]}], set()), first['symbols'])
        second = dict(name='sub_0806280C', declarations=['extern u32 d[8];'],
                      symbols={'d': {'address': '0x0202FC00', 'kind': 'data'}})
        with self.assertRaisesRegex(ValueError, 'Conflicting match-spec aliases for d'):
            integrate.collect_symbols([{'functions': [first, second]}], set())

    def test_qualified_callback_pointer_tables_preserve_names_and_aliases(self):
        declaration = 'extern void (*const callbacks[])(void), (*volatile other)(u32, u32);'
        self.assertEqual(integrate.declared_names(declaration), ['callbacks', 'other'])
        aliases = {'callbacks': {'address': '0x083AF180', 'kind': 'data'},
                   'other': {'address': '0x03000440', 'kind': 'data'}}
        function = dict(name='sub_08033840', declarations=[declaration], symbols=aliases)
        self.assertEqual(integrate.collect_symbols([{'functions': [function]}], set()), aliases)

    def test_declared_private_aliases_preserve_data_addresses_and_thumb_kind(self):
        function = dict(name='sub_0806EEA8', declarations=[
            'extern u32 gGraphicsWork6EEA803001800;',
            'extern const u8 gUnknown_083AD553[];',
            'extern void sub_080700C8(void);',
        ], symbols={
            'gGraphicsWork6EEA803001800': {'address': '0x03001800', 'kind': 'data'},
            'gUnknown_083AD553': {'address': '0x083AD553', 'kind': 'data'},
            'sub_080700C8': {'address': '0x080700C9', 'kind': 'thumb_function'},
            'unusedPrivateAlias': {'address': '0x03000440', 'kind': 'data'},
        })
        result = integrate.collect_symbols([{'functions': [function]}], set())
        self.assertEqual(result['gGraphicsWork6EEA803001800'], function['symbols']['gGraphicsWork6EEA803001800'])
        self.assertEqual(result['gUnknown_083AD553']['address'], '0x083AD553')
        self.assertEqual(result['sub_080700C8']['kind'], 'thumb_function')
        self.assertNotIn('unusedPrivateAlias', result)
        self.assertEqual(integrate.collect_symbols([{'functions': [function]}], set(result)), {})

    def test_conflicting_private_aliases_fail_before_publication(self):
        first = dict(name='sub_08000100', declarations=['extern u32 privateWork;'],
                     symbols={'privateWork': {'address': '0x03001800', 'kind': 'data'}})
        second = dict(name='sub_08000200', declarations=first['declarations'],
                      symbols={'privateWork': {'address': '0x03000440', 'kind': 'data'}})
        with self.assertRaisesRegex(ValueError, 'Conflicting match-spec aliases'):
            integrate.collect_symbols([{'functions': [first, second]}], set())

    def test_private_alias_from_spec_reaches_production_symbol_table(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            drafts = root / 'build/m2c'
            (drafts / 'sub_08000100').mkdir(parents=True)
            (root / 'src').mkdir()
            (root / 'include').mkdir()
            segments, symbols, manual = [root / name for name in ('segments.json', 'symbols.json', 'manual.json')]
            segments.write_text('[]')
            symbols.write_text('{}')
            manual.write_text(json.dumps([dict(name='sub_08000100', start='0x100', end='0x104', cflags=[])]))
            alias = {'address': '0x03001800', 'kind': 'data'}
            (drafts / 'sub_08000100/spec.json').write_text(json.dumps({'symbols': {'privateWork': alias}}))
            (drafts / 'sub_08000100.c').write_text('extern u32 privateWork;\nvoid sub_08000100(void) {\n    privateWork = 0;\n}\n')
            with patch.multiple(integrate, ROOT=root, SEGMENTS=segments, SYMBOLS=symbols,
                                SOLVED=root / 'absent_solved.json', MANUAL=manual, HARVEST=root / 'absent.json'), \
                    patch.object(sys, 'argv', ['m2c_integrate.py']), contextlib.redirect_stdout(io.StringIO()):
                integrate.main()
            self.assertEqual(json.loads(symbols.read_text())['privateWork'], alias)
            self.assertEqual(len(json.loads(segments.read_text())), 1)

    def test_latest_exact_profile_wins_with_equivalent_address_spelling(self):
        old = dict(exact=True, start='08000100', end='08000104', cflags=[])
        newer = dict(exact=True, start='0x08000100', end='08000104', cflags=['-fprologue-bugfix'])
        unfinished = dict(exact=False, start='08000100')
        self.assertEqual(integrate.latest_exact_rows([old, newer, unfinished]), [newer])

    def test_permuter_and_manual_result_generate_one_definition_and_segment(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            drafts = root / 'build/m2c'
            drafts.mkdir(parents=True)
            (root / 'src').mkdir()
            (root / 'include').mkdir()
            segments = root / 'segments.json'
            symbols = root / 'symbols.json'
            solved = root / 'solved.json'
            manual = root / 'manual.json'
            segments.write_text('[]')
            symbols.write_text('{}')
            entry = dict(name='sub_08000100', start='0x100', end='0x104', cflags=[])
            solved.write_text(json.dumps([entry]))
            entry['cflags'] = ['-fprologue-bugfix']
            manual.write_text(json.dumps([entry]))
            (drafts / 'sub_08000100.c').write_text('void sub_08000100(void) {\n    return;\n}\n')
            with patch.multiple(integrate, ROOT=root, SEGMENTS=segments, SYMBOLS=symbols,
                                SOLVED=solved, MANUAL=manual, HARVEST=root / 'absent.json'), \
                    patch.object(sys, 'argv', ['m2c_integrate.py']), contextlib.redirect_stdout(io.StringIO()):
                integrate.main()
            published = json.loads(segments.read_text())
            self.assertEqual(len(published), 1)
            self.assertEqual(published[0]['cflags'], ['-fprologue-bugfix'])
            source = (root / published[0]['source']).read_text()
            self.assertEqual(source.count('void sub_08000100(void) {'), 1)


if __name__ == '__main__':
    unittest.main()
