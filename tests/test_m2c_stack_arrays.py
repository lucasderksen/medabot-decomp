"""Reviewed stack arrays gain declarations without changing draft expressions."""
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch
from types import SimpleNamespace

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
import m2c_candidate as candidate


@unittest.skipUnless((ROOT / 'tools/downloads/m2c/m2c.py').exists(), 'optional m2c download unavailable')
class StackArrayDeclarationTests(unittest.TestCase):
    def run_draft(self, fields, instructions, enabled, frame=16):
        with tempfile.TemporaryDirectory() as directory:
            directory = Path(directory)
            context = directory / 'context.c'
            context.write_text('typedef unsigned char u8; typedef unsigned short u16; '
                               'typedef unsigned int u32;\nu32 entry(void);\nvoid consume(void *);\n'
                               + (f'struct _m2c_stack_entry {{ {fields} u32 saved; }};\n' if fields else ''))
            assembly = directory / 'entry.s'
            assembly.write_text('.syntax unified\n.thumb\n.text\n.align 2\n.globl entry\n.thumb_func\nentry:\n'
                                f' push {{lr}}\n sub sp, #{frame}\n' + instructions
                                + f'\n add sp, #{frame}\n pop {{r1}}\n bx r1\n')
            script = ROOT / ('tools/m2c_stack_arrays_driver.py' if enabled else 'tools/downloads/m2c/m2c.py')
            result = subprocess.run([sys.executable, str(script), '--target', 'gba', '--valid-syntax',
                                     '--context', str(context), str(assembly)], capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stderr)
            self.assertNotIn('M2C_ERROR', result.stdout)
            return result.stdout

    def test_multiple_known_arrays_are_declared_and_other_output_is_identical(self):
        fields = 'u8 first[8]; u16 second[4];'
        instructions = (' mov r0, sp\n bl consume\n add r0, sp, #8\n bl consume\n'
                        ' mov r1, sp\n ldrb r0, [r1, #1]')
        original = self.run_draft(fields, instructions, False)
        fixed = self.run_draft(fields, instructions, True)
        self.assertIn('u8 first[8];', fixed)
        self.assertIn('u16 second[4];', fixed)
        without_declarations = fixed.replace('    u8 first[8];\n', '').replace('    u16 second[4];\n', '')
        self.assertEqual([line for line in without_declarations.splitlines() if line.strip()],
                         [line for line in original.splitlines() if line.strip()])

    def test_first_access_to_nonzero_element_declares_root_once(self):
        fields = 'u32 prefix[2]; u16 values[4];'
        instructions = ' add r1, sp, #12\n ldrh r0, [r1]\n subs r1, #2\n ldrh r2, [r1]\n adds r0, r0, r2'
        original = self.run_draft(fields, instructions, False)
        fixed = self.run_draft(fields, instructions, True)
        self.assertEqual(fixed.count('u16 values[4];'), 1)
        self.assertNotIn('u32 prefix[2];', fixed)
        without_declaration = fixed.replace('    u16 values[4];\n', '')
        self.assertEqual([line for line in without_declaration.splitlines() if line.strip()],
                         [line for line in original.splitlines() if line.strip()])

    def test_known_scalar_stack_is_unchanged(self):
        instructions = ' mov r0, sp\n bl consume\n ldr r0, [sp]'
        self.assertEqual(self.run_draft('u32 value;', instructions, True, frame=4),
                         self.run_draft('u32 value;', instructions, False, frame=4))

    def test_inferred_stack_without_reviewed_layout_is_unchanged(self):
        instructions = ' mov r0, sp\n bl consume\n mov r1, sp\n ldrb r0, [r1, #1]'
        self.assertEqual(self.run_draft(None, instructions, True), self.run_draft(None, instructions, False))


class StackArrayOptionTests(unittest.TestCase):
    def test_bulk_generation_is_rejected_before_rom_read(self):
        import contextlib
        import io
        for mode in ('--harvest', '--evaluate', '--near-misses'):
            arguments = ['m2c_candidate.py', '--declare-stack-arrays', mode]
            if mode != '--near-misses':
                arguments.append('1')
            with self.subTest(mode=mode), patch.object(sys, 'argv', arguments), \
                    patch.object(candidate, 'find_rom') as read, contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as raised:
                    candidate.main()
                self.assertEqual(raised.exception.code, 2)
                read.assert_not_called()

    def test_array_option_routes_independently_of_pointer_stride_option(self):
        with tempfile.TemporaryDirectory() as directory:
            with patch.object(candidate, 'OUTPUT', Path(directory)), \
                    patch.object(candidate, 'decode', return_value=({}, {}, {}, set())), \
                    patch.object(candidate, 'render', return_value='assembly'), \
                    patch.object(candidate.subprocess, 'run', return_value=subprocess.CompletedProcess([], 0, 'draft', '')) as run:
                for strides in (False, True):
                    candidate.generate(b'', None, candidate.BASE, candidate.BASE+4, 'entry',
                                       fix_pointer_strides=strides, declare_stack_arrays=True)
                    command = run.call_args.args[0]
                    self.assertEqual(command[1], str(ROOT / 'tools/m2c_stack_arrays_driver.py'))
                    self.assertEqual('--fix-pointer-strides' in command, strides)
                    self.assertIn(str(Path(directory) / 'entry.stack_arrays.json'), command)


@unittest.skipUnless((ROOT / 'tools/downloads/m2c/m2c.py').exists(), 'optional m2c download unavailable')
class StackArrayBookkeepingTests(unittest.TestCase):
    def run_hook(self, known, size, location):
        sys.path.insert(0, str(ROOT / 'tools/downloads/m2c'))
        from m2c import translate
        from m2c.types import Type
        import m2c_stack_arrays_driver as driver
        array = Type.array(Type.u16(), size)
        field = SimpleNamespace(name='values', known=known, type=array, offset=0)
        stack = SimpleNamespace(fields=[field])
        target = SimpleNamespace(get_struct_declaration=lambda: stack)
        pointer = SimpleNamespace(get_pointer_target=lambda: target)
        locals_added = []
        info = SimpleNamespace(stack_pointer_type=pointer, add_local_var=locals_added.append)
        local = translate.LocalVar(location, type=Type.u16(), path=[0, 'values', location // 2])
        with patch.object(translate.StackInfo, 'get_stack_var', return_value=local) as original:
            undo, records = driver.install_known_stack_arrays()
            try:
                returned = translate.StackInfo.get_stack_var(info, location, store=False)
                self.assertIs(returned, local)
            finally:
                undo()
            self.assertIs(translate.StackInfo.get_stack_var, original)
        return locals_added, records

    def test_root_registration_preserves_expression_identity_and_can_be_undone(self):
        added, records = self.run_hook(True, 4, 4)
        self.assertEqual(len(added), 1)
        self.assertEqual(added[0].value, 0)
        self.assertEqual(added[0].path, [0, 'values'])
        self.assertEqual(records[0]['declaration'], 'u16 values[4]')

    def test_unknown_zero_length_and_out_of_bounds_fields_are_not_invented(self):
        for case in [(False, 4, 0), (True, 0, 0), (True, 4, 8)]:
            with self.subTest(case=case):
                self.assertEqual(self.run_hook(*case), ([], []))


if __name__ == '__main__':
    unittest.main()
