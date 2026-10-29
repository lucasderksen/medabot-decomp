"""Guard byte-offset analysis while correcting opt-in typed-pointer rendering."""
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
import m2c_stride_driver as driver


@unittest.skipUnless((ROOT / 'tools/downloads/m2c/m2c.py').exists(), 'optional m2c download unavailable')
class PointerStrideRenderingTests(unittest.TestCase):
    def run_draft(self, prototype, instructions, fixed):
        with tempfile.TemporaryDirectory() as directory:
            directory = Path(directory)
            context = directory / 'context.c'
            context.write_text('typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;\n'
                               'struct Frame { u16 value; u8 pad[62]; };\n'
                               'struct Pair { u16 first, second; };\n' + prototype + ';\n')
            assembly = directory / 'entry.s'
            assembly.write_text('.syntax unified\n.thumb\n.text\n.align 2\n.globl entry\n.thumb_func\nentry:\n'
                                + instructions + '\n bx lr\n')
            script = ROOT / ('tools/m2c_stride_driver.py' if fixed else 'tools/downloads/m2c/m2c.py')
            result = subprocess.run([sys.executable, str(script), '--target', 'gba', '--valid-syntax',
                                     '--context', str(context), str(assembly)], capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stderr)
            self.assertNotIn('M2C_ERROR', result.stdout)
            return result.stdout

    def loop(self, stride):
        return (' movs r2, #0\n.Lloop:\n ldrh r3, [r0]\n adds r3, #1\n strh r3, [r0]\n'
                f' adds r0, #{stride}\n adds r2, #1\n cmp r2, r1\n blo .Lloop')

    def test_halfword_loop_steps_one_element_and_keeps_scalar_increment(self):
        original = self.run_draft('void entry(u16 *cursor, u32 count)', self.loop(2), False)
        fixed = self.run_draft('void entry(u16 *cursor, u32 count)', self.loop(2), True)
        self.assertIn('var_r0 += 2;', original)
        self.assertEqual(fixed, original.replace('var_r0 += 2;', 'var_r0 += 1;'))

    def test_whole_frame_loop_steps_one_frame_and_keeps_field_access(self):
        original = self.run_draft('void entry(struct Frame *cursor, u32 count)', self.loop(64), False)
        fixed = self.run_draft('void entry(struct Frame *cursor, u32 count)', self.loop(64), True)
        self.assertIn('var_r0 += 0x40;', original)
        self.assertEqual(fixed, original.replace('var_r0 += 0x40;', 'var_r0 += 1;'))
        self.assertIn('var_r0->value += 1;', fixed)

    def test_byte_integer_and_nondivisible_pointer_additions_are_unchanged(self):
        for type_name, stride in [('u8 *', 2), ('u32', 2), ('struct Frame *', 2)]:
            with self.subTest(type_name=type_name):
                instructions = self.loop(stride) if '*' in type_name else ' adds r0, #2'
                prototype = f'void entry({type_name} cursor, u32 count)' if '*' in type_name else 'u32 entry(u32 cursor)'
                self.assertEqual(self.run_draft(prototype, instructions, True),
                                 self.run_draft(prototype, instructions, False))

    def test_existing_struct_field_address_is_not_scaled_again(self):
        instructions = ' adds r0, #2\n ldrh r0, [r0]'
        original = self.run_draft('u16 entry(struct Pair *cursor)', instructions, False)
        self.assertIn('cursor->second', original)
        self.assertEqual(self.run_draft('u16 entry(struct Pair *cursor)', instructions, True), original)

    def test_variable_byte_offset_does_not_scale_a_halfword_pointer(self):
        instructions = ' adds r0, r0, r1\n ldrh r0, [r0]'
        prototype = 'u16 entry(u16 *cursor, u32 byteOffset)'
        original = self.run_draft(prototype, instructions, False)
        fixed = self.run_draft(prototype, instructions, True)
        self.assertIn('*(cursor + byteOffset)', original)
        self.assertIn('*(u16 *) ((u32) cursor + (u32) byteOffset)', fixed)

    def test_commuted_variable_byte_offset_uses_word_address_arithmetic(self):
        instructions = ' adds r0, r1, r0\n ldrh r0, [r0]'
        fixed = self.run_draft('u16 entry(u16 *cursor, u32 byteOffset)', instructions, True)
        self.assertIn('*(u16 *) ((u32) byteOffset + (u32) cursor)', fixed)

    def test_variable_byte_subtraction_does_not_scale_a_halfword_pointer(self):
        instructions = ' subs r0, r0, r1\n ldrh r0, [r0]'
        fixed = self.run_draft('u16 entry(u16 *cursor, u32 byteOffset)', instructions, True)
        self.assertIn('*(u16 *) ((u32) cursor - (u32) byteOffset)', fixed)

    def test_variable_frame_offset_preserves_bytes_and_the_result_type(self):
        instructions = ' adds r0, r0, r1'
        fixed = self.run_draft('struct Frame *entry(struct Frame *cursor, u32 byteOffset)', instructions, True)
        self.assertIn('(struct Frame *) ((u32) cursor + (u32) byteOffset)', fixed)

    def test_variable_inplace_offset_uses_a_full_assignment(self):
        instructions = (' movs r3, #0\n.Lloop:\n ldrh r4, [r0]\n adds r4, #1\n'
                        ' strh r4, [r0]\n adds r0, r0, r1\n adds r3, #1\n cmp r3, r2\n blo .Lloop')
        fixed = self.run_draft('void entry(u16 *cursor, u32 byteOffset, u32 count)', instructions, True)
        self.assertIn('var_r0 = (u16 *) ((u32) var_r0 + (u32) byteOffset);', fixed)
        self.assertNotIn('var_r0 += byteOffset;', fixed)

    def test_variable_byte_and_integer_additions_stay_unchanged(self):
        for prototype, instructions in [
                ('u8 entry(u8 *cursor, u32 byteOffset)', ' adds r0, r0, r1\n ldrb r0, [r0]'),
                ('u32 entry(u32 first, u32 second)', ' adds r0, r0, r1')]:
            with self.subTest(prototype=prototype):
                self.assertEqual(self.run_draft(prototype, instructions, True),
                                 self.run_draft(prototype, instructions, False))

    def test_recognized_variable_array_index_is_not_scaled_again(self):
        instructions = ' lsls r1, r1, #1\n adds r0, r0, r1\n ldrh r0, [r0]'
        prototype = 'u16 entry(u16 *cursor, u32 index)'
        original = self.run_draft(prototype, instructions, False)
        self.assertIn('cursor[index]', original)
        self.assertEqual(self.run_draft(prototype, instructions, True), original)

    def unknown_table(self, mnemonic):
        return (' ldr r1, .Ltable\n adds r0, r0, r1\n ' + mnemonic +
                ' r0, [r0]\n bx lr\n.align 2\n.Ltable:\n.word gUnknownTable')

    def test_unknown_global_byte_index_survives_real_agbcc_compilation(self):
        import contextlib
        import io
        from compiler_agbcc import BINARY, compile_source
        if not BINARY.is_file():
            self.skipTest('optional agbcc download unavailable')
        original = self.run_draft('u8 entry(u32 index)', self.unknown_table('ldrb'), False)
        fixed = self.run_draft('u8 entry(u32 index)', self.unknown_table('ldrb'), True)
        self.assertIn('*(u8 *) ((u32) index + (u32) &gUnknownTable)', fixed)
        # The original C scales index by sizeof(M2C_UNK)==4. Prove the actual
        # compiler sees that erroneous scale, while the repaired draft adds
        # byte offsets directly. No cartridge or copied ROM fixture is needed.
        with tempfile.TemporaryDirectory() as directory:
            directory = Path(directory)
            assembly = []
            for name, body in [('original', original), ('fixed', fixed)]:
                source = directory / (name + '.c')
                source.write_text('#include "global.h"\ntypedef s32 M2C_UNK;\n' + body)
                obj = directory / (name + '.o')
                with contextlib.redirect_stdout(io.StringIO()):
                    compile_source(source, obj, ['-fprologue-bugfix'])
                assembly.append(obj.with_suffix('.s').read_text())
            scale = r'\blsl\s+[^\n]*#2(?:\s|$)'
            self.assertRegex(assembly[0], scale)
            self.assertNotRegex(assembly[1], scale)
            self.assertRegex(assembly[1], r'\bldrb\s')

    def test_unknown_halfword_and_word_results_do_not_invent_a_pointee_size(self):
        for result, instruction in [('u16', 'ldrh'), ('u32', 'ldr')]:
            with self.subTest(result=result):
                prototype = result + ' entry(u32 index)'
                self.assertEqual(self.run_draft(prototype, self.unknown_table(instruction), True),
                                 self.run_draft(prototype, self.unknown_table(instruction), False))

    def test_dynamic_rendering_keeps_the_original_ast_and_waits_for_pointer_type(self):
        sys.path.insert(0, str(ROOT / 'tools/downloads/m2c'))
        from m2c import evaluate, translate
        from m2c.types import Type
        source = translate.Literal(0x03001800, type=Type.any_reg())
        offset = translate.LocalVar(4, Type.u32(), None)
        expr = translate.BinaryOp(source, '+', offset, Type.ptr(Type.u16()))
        with patch.object(evaluate, 'handle_add_real', return_value=expr):
            undo = driver.install_pointer_stride_rendering()
            try:
                result = evaluate.handle_add_real(source, offset, None)
                self.assertIs(result.normalize_for_formatting(), expr)
                self.assertTrue(source.type.unify(Type.ptr(Type.u16())))
                rendered = result.normalize_for_formatting()
                self.assertIsInstance(rendered, translate.Cast)
                self.assertIs(result, expr)
                self.assertIs(expr.left, source)
                self.assertIs(expr.right, offset)
                self.assertIs(rendered.expr.left.expr, source)
                self.assertIs(rendered.expr.right.expr, offset)
            finally:
                undo()

    def test_load_multiple_writeback_steps_one_word(self):
        instructions = (' movs r2, #0\n movs r3, #0\n.Lloop:\n ldm r0!, {r4}\n'
                        ' adds r3, r3, r4\n adds r2, #1\n cmp r2, r1\n blo .Lloop\n mov r0, r3')
        original = self.run_draft('u32 entry(u32 *cursor, u32 count)', instructions, False)
        fixed = self.run_draft('u32 entry(u32 *cursor, u32 count)', instructions, True)
        self.assertIn('var_r0 += 4;', original)
        self.assertEqual(fixed, original.replace('var_r0 += 4;', 'var_r0 += 1;'))

    def test_store_multiple_writeback_steps_one_word(self):
        instructions = (' movs r2, #0\n movs r3, #1\n.Lloop:\n stm r0!, {r3}\n'
                        ' adds r2, #1\n cmp r2, r1\n blo .Lloop')
        original = self.run_draft('void entry(u32 *cursor, u32 count)', instructions, False)
        fixed = self.run_draft('void entry(u32 *cursor, u32 count)', instructions, True)
        self.assertIn('var_r0 += 4;', original)
        self.assertEqual(fixed, original.replace('var_r0 += 4;', 'var_r0 += 1;'))

    def test_explicit_subtraction_steps_one_halfword(self):
        instructions = ' subs r0, #2\n ldrh r0, [r0]'
        original = self.run_draft('u16 entry(u16 *cursor)', instructions, False)
        fixed = self.run_draft('u16 entry(u16 *cursor)', instructions, True)
        self.assertIn('cursor - 2', original)
        self.assertEqual(fixed, original.replace('cursor - 2', 'cursor - 1'))

    def test_rendering_does_not_mutate_byte_offset_ast_and_handles_negative_add(self):
        sys.path.insert(0, str(ROOT / 'tools/downloads/m2c'))
        from m2c import evaluate, translate
        from m2c.types import Type
        source = translate.Literal(0x03001800, type=Type.ptr(Type.u16()))
        for value in (2, -2):
            with self.subTest(value=value):
                immediate = translate.Literal(value)
                expr = translate.BinaryOp(source, '+', immediate, source.type)
                with patch.object(evaluate, 'add_imm', return_value=expr):
                    undo = driver.install_pointer_stride_rendering()
                    try:
                        result = evaluate.add_imm(None, source, immediate, None)
                        rendered = result.normalize_for_formatting()
                        self.assertIs(result, expr)
                        self.assertEqual(result.right.value, value)
                        self.assertEqual(rendered.right.value, 1)
                        self.assertEqual(rendered.op, '+' if value > 0 else '-')
                        self.assertIs(rendered.left, source)
                    finally:
                        undo()

    def test_raw_immediate_waits_for_late_pointer_inference(self):
        sys.path.insert(0, str(ROOT / 'tools/downloads/m2c'))
        from m2c import evaluate, translate
        from m2c.types import Type
        source = translate.Literal(0x03001800, type=Type.any_reg())
        immediate = translate.Literal(2)
        expr = translate.BinaryOp(source, '+', immediate, source.type)
        with patch.object(evaluate, 'add_imm', return_value=expr):
            undo = driver.install_pointer_stride_rendering()
            try:
                result = evaluate.add_imm(None, source, immediate, None)
                self.assertEqual(result.normalize_for_formatting().right.value, 2)
                self.assertTrue(source.type.unify(Type.ptr(Type.u16())))
                self.assertEqual(result.normalize_for_formatting().right.value, 1)
                self.assertEqual(result.right.value, 2)
            finally:
                undo()


class PointerStrideOptionTests(unittest.TestCase):
    def test_generate_uses_upstream_by_default_and_driver_only_when_opted_in(self):
        import m2c_candidate as candidate
        with tempfile.TemporaryDirectory() as directory:
            with patch.object(candidate, 'OUTPUT', Path(directory)), \
                    patch.object(candidate, 'decode', return_value=({}, {}, {}, set())), \
                    patch.object(candidate, 'render', return_value='assembly'), \
                    patch.object(candidate.subprocess, 'run', return_value=subprocess.CompletedProcess([], 0, 'draft', '')) as run:
                for enabled in (False, True):
                    candidate.generate(b'', None, candidate.BASE, candidate.BASE+4, 'entry', fix_pointer_strides=enabled)
                    expected = ROOT / ('tools/m2c_stride_driver.py' if enabled else 'tools/downloads/m2c/m2c.py')
                    self.assertEqual(run.call_args.args[0][1], str(expected))


if __name__ == '__main__':
    unittest.main()
