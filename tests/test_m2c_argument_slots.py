"""Check ARM parameter positions against emitted Thumb instructions."""
from pathlib import Path
import contextlib
import io
import subprocess
import sys
import tempfile
import unittest
from types import SimpleNamespace
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))


@unittest.skipUnless((ROOT / 'tools/downloads/m2c/m2c.py').exists(), 'optional m2c unavailable')
class ArgumentSlotTests(unittest.TestCase):
    def draft(self, instructions, fixed, context=None):
        with tempfile.TemporaryDirectory() as directory:
            directory = Path(directory)
            assembly = directory / 'entry.s'
            assembly.write_text('.syntax unified\n.thumb\n.text\n.align 2\n.globl entry\n'
                                '.thumb_func\nentry:\n' + instructions + '\n bx lr\n')
            driver = ROOT / ('tools/m2c_argument_slots_driver.py' if fixed else
                             'tools/downloads/m2c/m2c.py')
            command = [sys.executable, str(driver), '--target', 'gba', '--valid-syntax']
            if context:
                path = directory / 'context.c'
                path.write_text(context)
                command += ['--context', str(path)]
            result = subprocess.run(command + [str(assembly)], capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stderr)
            self.assertNotIn('M2C_ERROR', result.stdout)
            return result.stdout, result.stderr

    def test_missing_middle_register_keeps_r2_at_parameter_three(self):
        source, report = self.draft(' adds r0, r0, r2', True)
        self.assertIn('s32 entry(s32 arg0, u32 _unused_arg1, s32 arg2)', source)
        self.assertIn('return arg0 + arg2;', source)
        self.assertIn('"observed_slots": [0, 2]', report)

    def test_missing_leading_registers_are_retained(self):
        source, _ = self.draft(' mov r0, r2', True)
        self.assertIn('entry(u32 _unused_arg0, u32 _unused_arg1, s32 arg2)', source)

    def test_stack_word_offset_is_not_compacted_into_a_register(self):
        source, report = self.draft(' ldr r0, [sp, #4]', True)
        self.assertIn('_unused_arg4, s32 arg5)', source)
        self.assertIn('"observed_slots": [5]', report)

    def test_dense_and_known_signatures_are_unchanged(self):
        cases = [(' adds r0, r0, r1', None),
                 (' adds r0, r0, r2', 'int entry(int first, unsigned int unused, int third);')]
        for instructions, context in cases:
            with self.subTest(context=context):
                fixed, report = self.draft(instructions, True, context)
                original, _ = self.draft(instructions, False, context)
                self.assertEqual(fixed, original)
                self.assertEqual(report, '')

    def test_large_apparent_stack_argument_is_left_for_review(self):
        fixed, report = self.draft(' ldr r0, [sp, #64]', True)
        original, _ = self.draft(' ldr r0, [sp, #64]', False)
        self.assertEqual(fixed, original)
        self.assertEqual(report, '')

    def render_info(self, wide=False):
        import m2c_argument_slots_driver as driver
        driver.install_argument_slot_rendering()()
        from m2c import translate
        from m2c.types import Type, FunctionSignature
        from m2c.instruction import Register
        signature = FunctionSignature()
        stack = SimpleNamespace(arguments=[], param_names={}, replace_first_arg=None,
                                function=SimpleNamespace(name='entry'))
        for index in (0, 2):
            stack.arguments.append(translate.PassedInArg(
                loc=translate.ArgLoc(None, index, Register(f'r{index}')), stack_info=stack,
                type=Type.u64() if wide and index == 0 else Type.s32()))
        info = SimpleNamespace(stack_info=stack, symbol=SimpleNamespace(type=Type.function(signature)),
                               return_type=Type.s32())
        return info, signature

    def test_render_failure_restores_analysis_arguments_and_names(self):
        import m2c_argument_slots_driver as driver
        info, signature = self.render_info()
        from m2c import if_statements
        original = list(info.stack_info.arguments)

        def fail_render(current, options):
            self.assertEqual(len(current.stack_info.arguments), 3)
            raise RuntimeError('format failed')

        with patch.object(if_statements, 'get_function_text', side_effect=fail_render):
            undo = driver.install_argument_slot_rendering()
            try:
                with self.assertRaisesRegex(RuntimeError, 'format failed'), contextlib.redirect_stderr(io.StringIO()):
                    if_statements.get_function_text(info, None)
            finally:
                undo()
        self.assertEqual(info.stack_info.arguments, original)
        self.assertTrue(all(a is b for a, b in zip(info.stack_info.arguments, original)))
        self.assertEqual(info.stack_info.param_names, {})
        self.assertEqual(signature.params, [])

    def test_multiword_parameter_is_left_for_review(self):
        import m2c_argument_slots_driver as driver
        info, _ = self.render_info(wide=True)
        from m2c import if_statements
        original = list(info.stack_info.arguments)
        with patch.object(if_statements, 'get_function_text', return_value='unchanged') as formatter:
            undo = driver.install_argument_slot_rendering()
            try:
                self.assertEqual(if_statements.get_function_text(info, None), 'unchanged')
                formatter.assert_called_once_with(info, None)
                self.assertEqual(info.stack_info.arguments, original)
            finally:
                undo()

    @unittest.skipUnless((ROOT / 'tools/downloads/agbcc/agbcc.exe').exists(), 'optional agbcc unavailable')
    def test_real_compiler_preserves_the_observed_add_register(self):
        from compiler_agbcc import compile_source
        from common import tool
        original, _ = self.draft(' adds r0, r0, r2', False)
        fixed, _ = self.draft(' adds r0, r0, r2', True)
        with tempfile.TemporaryDirectory() as directory:
            directory = Path(directory)
            binaries = []
            for index, source in enumerate((original, fixed)):
                path = directory / f'candidate{index}.c'
                path.write_text('#include "global.h"\n' + source)
                obj = path.with_suffix('.o')
                with contextlib.redirect_stdout(io.StringIO()):
                    compile_source(path, obj, ['-fprologue-bugfix'])
                binary = path.with_suffix('.bin')
                subprocess.run([tool('objcopy'), '-O', 'binary', '-j', '.text.entry', obj, binary],
                               check=True, capture_output=True)
                binaries.append(binary.read_bytes())
            self.assertEqual(binaries[0], bytes.fromhex('40187047'))  # ADD R0,R0,R1; BX LR
            self.assertEqual(binaries[1], bytes.fromhex('80187047'))  # ADD R0,R0,R2; BX LR


if __name__ == '__main__':
    unittest.main()
