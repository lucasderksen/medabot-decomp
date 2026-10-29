"""Actual Thumb CFGs guard opt-in stack constants without guessed call inputs."""
import contextlib
import io
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch
from types import SimpleNamespace

ROOT = Path(__file__).resolve().parents[1]
DRIVER = ROOT / 'tools/m2c_stack_join_driver.py'
UPSTREAM = ROOT / 'tools/downloads/m2c/m2c.py'
sys.path.insert(0, str(ROOT / 'tools'))
import m2c_candidate as candidate


@unittest.skipUnless(UPSTREAM.exists(), 'optional m2c download unavailable')
class StackJoinTests(unittest.TestCase):
    def draft(self, left, right, *, enabled=True, prototype=None, join='', head='', frame=4):
        with tempfile.TemporaryDirectory() as directory:
            directory = Path(directory)
            context = directory / 'context.c'
            context.write_text('typedef unsigned int u32; typedef unsigned char u8;\n'
                               'u32 entry(u32); void barrier(void);\n' +
                               (prototype or 'u32 consume(u32, u32, u32, u32, u32);') + '\n')
            assembly = directory / 'entry.s'
            assembly.write_text('.syntax unified\n.thumb\n.text\n.align 2\n.globl entry\n.thumb_func\nentry:\n'
                                f' push {{r4, lr}}\n sub sp, #{frame}\n' + head +
                                ' cmp r0, #0\n beq .Lright\n' + left + '\n b .Ljoin\n.Lright:\n' + right +
                                '\n.Ljoin:\n' + join +
                                ' movs r0, #1\n movs r1, #2\n movs r2, #3\n movs r3, #4\n bl consume\n' +
                                f' add sp, #{frame}\n pop {{r4}}\n pop {{r1}}\n bx r1\n')
            report = directory / 'report.json'
            command = [sys.executable, str(DRIVER if enabled else UPSTREAM)]
            if enabled:
                command += ['--stack-join-report', str(report)]
            command += ['--target', 'gba', '--valid-syntax', '--context', str(context), str(assembly)]
            result = subprocess.run(command, capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stderr + result.stdout)
            self.assertNotIn('Error occurred', result.stderr)
            return result.stdout, json.loads(report.read_text()) if enabled else []

    def test_identical_branch_words_are_recovered(self):
        store = ' movs r1, #13\n str r1, [sp]\n'
        baseline, _ = self.draft(store, store, enabled=False)
        fixed, records = self.draft(store, store)
        self.assertIn('Unable to find stack arg 0x0', baseline)
        self.assertNotIn('M2C_ERROR', fixed)
        self.assertIn('consume(1U, 2U, 3U, 4U, 0xDU)', fixed)
        self.assertEqual([(r['offset'], r['value']) for r in records], [(0, 13)])
        self.assertNotIn('extra?', fixed)

    def test_conflicting_and_missing_predecessors_stay_unresolved(self):
        for right in [' movs r1, #14\n str r1, [sp]\n', ' movs r1, #13\n']:
            with self.subTest(right=right):
                fixed, records = self.draft(' movs r1, #13\n str r1, [sp]\n', right)
                self.assertIn('Unable to find stack arg 0x0', fixed)
                self.assertEqual(records, [])

    def test_intervening_call_invalidates_values(self):
        store = ' movs r1, #13\n str r1, [sp]\n'
        fixed, records = self.draft(store + ' bl barrier\n', store)
        self.assertIn('Unable to find stack arg 0x0', fixed)
        self.assertEqual(records, [])

    def test_partial_and_indirect_writes_invalidate_values(self):
        store = ' movs r1, #13\n str r1, [sp]\n'
        for overwrite in [' mov r2, sp\n movs r1, #2\n strb r1, [r2, #1]\n',
                          ' movs r1, #2\n str r1, [r4]\n']:
            with self.subTest(overwrite=overwrite):
                fixed, records = self.draft(store + overwrite, store)
                self.assertIn('Unable to find stack arg 0x0', fixed)
                self.assertEqual(records, [])

    def test_current_block_store_takes_precedence(self):
        store = ' movs r1, #13\n str r1, [sp]\n'
        fixed, records = self.draft(store, store, join=' movs r1, #14\n str r1, [sp]\n')
        self.assertNotIn('M2C_ERROR', fixed)
        self.assertIn('consume(1U, 2U, 3U, 4U, 0xEU)', fixed)
        self.assertEqual(records, [])

    def test_known_four_argument_call_gets_no_extra_inherited_slot(self):
        store = ' movs r1, #13\n str r1, [sp]\n'
        fixed, records = self.draft(store, store, prototype='u32 consume(u32, u32, u32, u32);')
        self.assertIn('consume(1U, 2U, 3U, 4U)', fixed)
        self.assertNotIn('extra?', fixed)
        self.assertEqual(records, [])

    def test_unsupported_signatures_are_unchanged(self):
        store = ' movs r1, #13\n str r1, [sp]\n'
        for prototype in ['u32 consume();', 'u32 consume(u32, ...);',
                          'u32 consume(u32, u32, u32, u32, float);',
                          'u32 consume(u32, u32, u32, u32, long long);',
                          'struct Pair { u32 x, y; }; struct Pair consume(u32, u32, u32, u32, u32);']:
            with self.subTest(prototype=prototype):
                fixed, records = self.draft(store, store, prototype=prototype)
                baseline, _ = self.draft(store, store, enabled=False, prototype=prototype)
                self.assertEqual(fixed, baseline)
                self.assertEqual(records, [])

    def test_one_required_slot_does_not_import_another_slot(self):
        store = ' movs r1, #13\n str r1, [sp]\n movs r1, #14\n str r1, [sp, #4]\n'
        fixed, records = self.draft(store, store, frame=8)
        self.assertNotIn('M2C_ERROR', fixed)
        self.assertNotIn('extra?', fixed)
        self.assertEqual([(r['offset'], r['value']) for r in records], [(0, 13)])

    def test_loop_backedge_is_not_treated_as_a_proven_predecessor(self):
        store = ' movs r1, #13\n str r1, [sp]\n'
        loop = ' movs r4, #1\n.Lloop:\n subs r4, #1\n cmp r4, #0\n bne .Lloop\n'
        fixed, records = self.draft(store, store, join=loop)
        baseline, _ = self.draft(store, store, join=loop, enabled=False)
        self.assertEqual(fixed, baseline)
        self.assertEqual(records, [])

    def test_constant_written_before_branch_propagates_through_both_paths(self):
        fixed, records = self.draft(' movs r2, #8\n', ' movs r2, #9\n',
                                    head=' movs r1, #13\n str r1, [sp]\n')
        self.assertNotIn('M2C_ERROR', fixed)
        self.assertEqual([(r['offset'], r['value']) for r in records], [(0, 13)])

    def test_unknown_value_is_not_promoted_to_literal(self):
        store = ' str r0, [sp]\n'
        fixed, records = self.draft(store, store)
        self.assertIn('Unable to find stack arg 0x0', fixed)
        self.assertEqual(records, [])


class StackJoinOptionTests(unittest.TestCase):
    def test_bulk_generation_is_rejected_before_rom_read(self):
        for mode in ('--harvest', '--evaluate', '--near-misses'):
            arguments = ['m2c_candidate.py', '--recover-stack-constants', mode]
            if mode != '--near-misses':
                arguments.append('1')
            with self.subTest(mode=mode), patch.object(sys, 'argv', arguments), \
                    patch.object(candidate, 'find_rom') as read, contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as raised:
                    candidate.main()
                self.assertEqual(raised.exception.code, 2)
                read.assert_not_called()

    def test_opt_in_driver_composes_with_arrays_and_strides_and_default_is_unchanged(self):
        with tempfile.TemporaryDirectory() as directory:
            with patch.object(candidate, 'OUTPUT', Path(directory)), \
                    patch.object(candidate, 'decode', return_value=({}, {}, {}, set())), \
                    patch.object(candidate, 'render', return_value='assembly'), \
                    patch.object(candidate.subprocess, 'run', return_value=subprocess.CompletedProcess([], 0, 'draft', '')) as run:
                candidate.generate(b'', None, candidate.BASE, candidate.BASE + 4, 'entry')
                self.assertEqual(run.call_args.args[0][1], str(UPSTREAM))
                for arrays in (False, True):
                    for strides in (False, True):
                        candidate.generate(b'', None, candidate.BASE, candidate.BASE + 4, 'entry',
                                           recover_stack_constants=True, declare_stack_arrays=arrays,
                                           fix_pointer_strides=strides)
                        command = run.call_args.args[0]
                        self.assertEqual(command[1], str(DRIVER))
                        self.assertEqual('--declare-stack-arrays' in command, arrays)
                        self.assertEqual('--stack-array-report' in command, arrays)
                        self.assertEqual('--fix-pointer-strides' in command, strides)
                        self.assertIn(str(Path(directory) / 'entry.stack_joins.json'), command)


@unittest.skipUnless(UPSTREAM.exists(), 'optional m2c download unavailable')
class StackJoinHookTests(unittest.TestCase):
    def test_hooks_restore_all_upstream_methods(self):
        sys.path.insert(0, str(ROOT / 'tools/downloads/m2c'))
        from m2c import translate
        import m2c_stack_join_driver as driver
        names = ('translate_all_blocks', 'translate_block', 'evaluate_instruction')
        methods = ('store_memory', 'make_function_call', 'push_subroutine_arg')
        originals = [getattr(translate, name) for name in names]
        original_methods = [getattr(translate.NodeState, name) for name in methods]
        undo, records = driver.install_constant_stack_joins()
        try:
            self.assertEqual(records, [])
            for name, original in zip(names, originals):
                self.assertIsNot(getattr(translate, name), original)
        finally:
            undo()
        for name, original in zip(names, originals):
            self.assertIs(getattr(translate, name), original)
        for name, original in zip(methods, original_methods):
            self.assertIs(getattr(translate.NodeState, name), original)

    def test_sp_write_and_elided_store_invalidate_and_new_translation_resets(self):
        sys.path.insert(0, str(ROOT / 'tools/downloads/m2c'))
        from m2c import translate as t
        from m2c.types import Type
        import m2c_stack_join_driver as driver
        parent = SimpleNamespace(parents=[], name=lambda: 'parent')
        child = SimpleNamespace(parents=[parent], name=lambda: 'child')
        join = SimpleNamespace(parents=[child], name=lambda: 'join')
        arch = SimpleNamespace(arch=t.Target.ArchEnum.ARM, home_space_size=0,
                               function_abi=lambda *args, **kwargs: SimpleNamespace(
                                   arg_slots=[SimpleNamespace(loc=SimpleNamespace(reg=None, offset=0))]))
        sig = SimpleNamespace(params_known=True, is_variadic=False, return_type=Type.u32(),
                              params=[SimpleNamespace(type=Type.u32()) for _ in range(5)])
        target = SimpleNamespace(type=SimpleNamespace(get_function_pointer_signature=lambda: sig),
                                 format=lambda formatter: 'consume')
        instruction = SimpleNamespace(mnemonic='str', outputs=[], clobbers=[], is_store=True)
        state = SimpleNamespace(node=parent, subroutine_args={},
                                stack_info=SimpleNamespace(global_info=SimpleNamespace(arch=arch),
                                                           function=SimpleNamespace(name='entry')),
                                regs=SimpleNamespace(current_instr_ref=lambda: SimpleNamespace(instruction=instruction)))
        def body(current_state, options):
            if current_state.node is parent:
                t.NodeState.store_memory(current_state, SimpleNamespace(
                    dest=t.SubroutineArg(0, Type.u32()), source=t.Literal(13)), t.Register('r1'))
            elif current_state.node is child:
                t.evaluate_instruction(SimpleNamespace(instruction=options), current_state)
            else:
                t.NodeState.make_function_call(current_state, target, [])
        with patch.object(t, 'translate_all_blocks'), patch.object(t, 'translate_block', side_effect=body), \
                patch.object(t, 'evaluate_instruction'), patch.object(t.NodeState, 'store_memory'), \
                patch.object(t.NodeState, 'make_function_call'), patch.object(t, 'as_function_ptr', side_effect=lambda target: target):
            undo, records = driver.install_constant_stack_joins()
            try:
                for invalidator in [SimpleNamespace(mnemonic='add', outputs=[t.Register('sp')], clobbers=[], is_store=False),
                                    SimpleNamespace(mnemonic='str', outputs=[], clobbers=[], is_store=True)]:
                    state.node = parent
                    t.translate_block(state, None)
                    state.node = child
                    t.translate_block(state, invalidator)
                    state.node = join
                    t.translate_block(state, None)
                    self.assertEqual(state.subroutine_args, {})
                    self.assertEqual(records, [])
                state.node = parent
                t.translate_block(state, None)
                t.translate_all_blocks()  # A new function/type-resolution pass.
                state.node = SimpleNamespace(parents=[parent], name=lambda: 'new join')
                t.translate_block(state, None)
                self.assertEqual(state.subroutine_args, {})
                self.assertEqual(records, [])
            finally:
                undo()


if __name__ == '__main__':
    unittest.main()
