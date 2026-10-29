"""A new permutation seed/profile must not reuse another invocation's results."""

from pathlib import Path
import json
import runpy
import subprocess
import sys
import tempfile
from types import ModuleType, SimpleNamespace
import unittest
from unittest.mock import Mock, patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import permute


class SpawnedCompilerRoutingTests(unittest.TestCase):
    def modules(self):
        package = ModuleType('src')
        package.__path__ = []
        modules = {'src': package}
        for name in ('compiler', 'preprocess', 'main'):
            module = ModuleType('src.' + name)
            module.subprocess = subprocess
            setattr(package, name, module)
            modules['src.' + name] = module
        return modules

    def test_spawned_worker_routes_shell_compiler_and_cpp(self):
        modules = self.modules()
        # spawn inherits the rewritten argv, without --run-permuter.
        with patch.dict(sys.modules, modules), \
                patch.object(sys, 'argv', ['permuter.py', 'private-run', '-j', '4']), \
                patch.object(sys, 'path', list(sys.path)), \
                patch('common.tool', return_value='test-cross-gcc'), \
                patch.object(subprocess, 'check_call') as compile_call, \
                patch.object(subprocess, 'check_output', return_value='') as cpp_call:
            runpy.run_path(str(Path(permute.__file__)), run_name='__mp_main__')
            modules['src.compiler'].subprocess.check_call(
                ['private-run/compile.sh', 'input.c', '-o', 'output.o'], cwd='private-run')
            modules['src.preprocess'].subprocess.check_output(['cpp', '-P', 'input.c'])
        compile_call.assert_called_once_with(
            [sys.executable, str(Path(permute.__file__)), '--compile', 'input.c', '-o', 'output.o'],
            cwd='private-run')
        cpp_call.assert_called_once_with(['test-cross-gcc', '-E', '-x', 'c', '-P', 'input.c'])

    def test_compile_invocation_does_not_install_worker_imports(self):
        modules = self.modules()
        with patch.dict(sys.modules, modules), \
                patch.object(sys, 'argv', ['permute.py', '--compile', 'input.c', '-o', 'output.o']), \
                patch.object(sys, 'path', list(sys.path)):
            runpy.run_path(str(Path(permute.__file__)), run_name='compile_import_probe')
        self.assertIs(modules['src.compiler'].subprocess, subprocess)
        self.assertIs(modules['src.preprocess'].subprocess, subprocess)


class InlineHelperTests(unittest.TestCase):
    def test_inline_body_survives_stripping_with_nested_blocks(self):
        helper = 'static inline unsigned Wrap(unsigned x)\n{ if (x) { return x & 511; } return 0; }'
        original = helper + '\nvoid unused(void) {}\nvoid target(void) { Wrap(1); }'
        stripped = 'static inline unsigned Wrap(unsigned x);\nvoid unused(void);\nvoid target(void) { Wrap(1); }'
        actual = permute.restore_inline_helpers(original, stripped, 'target')
        self.assertIn(helper, actual)
        self.assertIn('void unused(void);', actual)
        self.assertNotIn('void unused(void) {}', actual)

    def test_inline_target_is_already_preserved(self):
        source = 'static inline void target(void) {}'
        self.assertEqual(permute.restore_inline_helpers(source, source, 'target'), source)

    def test_missing_inline_declaration_fails_instead_of_changing_seed(self):
        with self.assertRaisesRegex(ValueError, 'Inline helper declaration missing'):
            permute.restore_inline_helpers('inline int helper(void) { return 1; }', '', 'target')


class RegisterPinTests(unittest.TestCase):
    def test_pins_are_stripped_for_pycparser_and_restored_in_variants(self):
        source = ('extern int gView asm("gTable");\n'
                  'void target(int r) { register unsigned short r0 asm("r0") = r | 1; register int rest; rest = r0; }')
        with tempfile.TemporaryDirectory() as temporary:
            path = Path(temporary) / 'base.c'
            path.write_text(source, encoding='utf-8')
            pins = permute.strip_register_pins(path)
            stripped = path.read_text(encoding='utf-8')
        self.assertEqual(pins, {'r0': 'r0'})
        self.assertIn('register unsigned short r0 = r | 1;', stripped)
        self.assertIn('asm("gTable")', stripped)  # labels are strip_asm_labels' job
        variant = stripped.replace('rest = r0;', 'rest = r0 + 0;')
        restored = permute.apply_pins(variant, pins)
        self.assertIn('register unsigned short r0 asm("r0") = r | 1;', restored)
        self.assertIn('register int rest;', restored)
        self.assertEqual(permute.apply_pins(stripped, pins).replace('rest = r0;', ''), source.replace('rest = r0;', ''))


class PermuterArtifactTests(unittest.TestCase):
    def test_repeated_setup_preserves_legacy_outputs_but_isolates_scores(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            name = 'sub_080121F0'
            draft = root / 'build/m2c' / name
            draft.mkdir(parents=True)
            (draft / 'candidate.c').write_text('void sub_080121F0(void) {}')
            output = root / 'build/permuter'
            legacy = output / name / 'output-0-1'
            legacy.mkdir(parents=True)
            (legacy / 'source.c').write_text('older exact source')
            with patch.multiple(permute, ROOT=root, OUTPUT=output), \
                    patch.object(permute, 'tool', return_value='unused-tool'), \
                    patch.object(permute.subprocess, 'run'), \
                    patch.object(permute, 'prepare_reference'):
                first = permute.setup(name, ['-fprologue-bugfix'])
                (first / 'output-2-1').mkdir()
                (draft / 'candidate.c').write_text('void sub_080121F0(void) { return; }')
                second = permute.setup(name, ['-fprologue-bugfix', '-fno-regmove'])
            self.assertNotEqual(first, second)
            self.assertEqual(first.parent, output / name)
            self.assertEqual(second.parent, first.parent)
            self.assertEqual(permute.best_score(first), 2)
            self.assertIsNone(permute.best_score(second))
            self.assertEqual((first / 'cflags.txt').read_text().strip(), '-fprologue-bugfix')
            self.assertEqual((second / 'cflags.txt').read_text().strip(), '-fprologue-bugfix -fno-regmove')
            self.assertEqual((legacy / 'source.c').read_text(), 'older exact source')


class ReferenceNormalizationTests(unittest.TestCase):
    def test_high_register_sp_add_spelling(self):
        text = '\tadd\tr0, sp, r0\n\tadd\tr12, sp, r12\n'
        actual, rewrites = permute.normalize_reference(text, '.text.example', {}, set())
        self.assertEqual(actual, '\tadd\tr0, sp\n\tadd\tr12, sp\n')
        self.assertEqual(rewrites, {})

    def test_other_sp_add_forms_are_untouched(self):
        text = '\tadd\tr0, sp, #4\n\tadd\tr0, sp, r1\n\tadds\tr0, sp, r0\n'
        actual, _ = permute.normalize_reference(text, '.text.example', {}, set())
        self.assertEqual(actual, text)

    def test_unique_alias_and_local_section(self):
        text = '.text\n.word canonical\n.word canonical+4\n'
        actual, rewrites = permute.normalize_reference(
            text, '.text.m2c_example',
            {'canonical': '0x03001800', 'private': '0x03001800'}, {'private'})
        self.assertEqual(actual, '.section .text.m2c_example,"ax",%progbits\n'
                                 '.word private\n.word canonical+4\n')
        self.assertEqual(rewrites, {'canonical': 'private'})

    def test_ambiguous_aliases_are_held(self):
        text = '.word canonical\n'
        actual, rewrites = permute.normalize_reference(
            text, '.text.example',
            dict(canonical='0x03001800', first='0x03001800', second='0x03001800'),
            {'first', 'second'})
        self.assertEqual(actual, text)
        self.assertEqual(rewrites, {})

    def test_thumb_state_and_odd_data_bits_are_retained(self):
        symbols = {'function': {'address': '0x08000101', 'kind': 'thumb_function'},
                   'even': '0x08000100', 'odd_data': '0x080AFCB7',
                   'private_data': '0x080AFCB7'}
        actual, rewrites = permute.normalize_reference(
            '.word function\n.word odd_data\n', '.text.example', symbols,
            {'even', 'private_data'})
        self.assertEqual(actual, '.word function\n.word private_data\n')
        self.assertEqual(rewrites, {'odd_data': 'private_data'})

    def test_existing_and_unknown_names_are_preserved(self):
        text = '.word original\n.word unknown\n'
        actual, rewrites = permute.normalize_reference(
            text, '.text.example', {'original': '0x03001800'}, {'original', 'unknown'})
        self.assertEqual(actual, text)
        self.assertEqual(rewrites, {})

    def test_reconstruction_byte_gate_rejects_changed_target(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            name = 'sub_08000100'
            draft = root / 'draft'
            draft.mkdir()
            seed = draft / 'candidate.c'
            seed.write_text('void sub_08000100(void) {}')
            (draft / 'spec.json').write_text(json.dumps({'segments': [{
                'name': name, 'start': '0x100', 'end': '0x104',
                'input_section': '.text.m2c_' + name}]}))
            assembly = root / 'build/m2c'
            assembly.mkdir(parents=True)
            (assembly / (name + '.s')).write_text('.text\n.word 0\n')
            output = root / 'output'
            output.mkdir()
            (output / 'target_check.bin').write_bytes(b'\0\0\0\0')
            session = Mock()
            session.symbols.return_value = {}
            session.symbol_object.return_value = output / 'symbols.o'
            session.reference.return_value = b'\0' * 0x100 + b'\x01\0\0\0'
            with patch.object(permute, 'ROOT', root), \
                    patch.object(permute, 'tool', return_value='unused-tool'), \
                    patch.object(permute.subprocess, 'run', return_value=SimpleNamespace(stdout='')), \
                    patch('compiler_agbcc.compile_source'), \
                    patch('match.MatchSession', return_value=session):
                with self.assertRaisesRegex(ValueError, 'changed ROM bytes'):
                    permute.prepare_reference(name, seed, [], output)
            self.assertFalse((output / 'normalization.json').exists())


if __name__ == '__main__':
    unittest.main()
