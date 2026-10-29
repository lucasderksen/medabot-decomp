"""Tests for the m2c input decoder and the instruction-level diff."""

from pathlib import Path
import json
import struct
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools" / "python"))
try:
    import capstone
except ImportError:
    capstone = None
from m2c_candidate import BASE, Symbols, decode, generate, literal_text, resolve_register_stack_adjustments


class SymbolTests(unittest.TestCase):
    def setUp(self):
        self.symbols = Symbols("\n".join([
            "0300056f A gOddByte",
            "08485900 00000040 R gByteTable",
            "08485a91 0000000d R gOddStream",
            "0801234c 00000020 T callback",
            "08012351 00000003 R callbackData",
            "0802345d A sub_0802345C",
        ]))

    def test_data_symbols_keep_odd_addresses_and_offsets(self):
        self.assertEqual(self.symbols.exact(0x0300056F), "gOddByte")
        self.assertIsNone(self.symbols.exact(0x0300056E))
        self.assertEqual(self.symbols.containing(0x08485A91), "gOddStream")
        for address, expected in [(0x0300056F, "gOddByte"),
                                  (0x08485A91, "gOddStream"),
                                  (0x08485903, "gByteTable+0x3")]:
            with self.subTest(address=hex(address)):
                self.assertEqual(literal_text(address, self.symbols, BASE, BASE+4, {}), expected)

    def test_known_thumb_functions_still_normalize_the_tag(self):
        self.assertEqual(self.symbols.exact(0x0801234D), "callback")
        self.assertEqual(self.symbols.exact(0x0802345C), "sub_0802345C")
        self.assertEqual(literal_text(0x0801234D, self.symbols, BASE, BASE+4, {}), "callback+1")
        self.assertEqual(literal_text(0x0801234F, self.symbols, BASE, BASE+4, {}), "callback+0x2")
        self.assertEqual(literal_text(0x08012351, self.symbols, BASE, BASE+4, {}), "callbackData")
        self.assertEqual(literal_text(0x0802345D, self.symbols, BASE, BASE+4, {}), "sub_0802345C+1")

    def test_unknown_odd_pool_addresses_remain_opaque_data(self):
        self.assertEqual(literal_text(0x080AFCB7, self.symbols, BASE, BASE+4, {}), "D_080AFCB7")
        self.assertEqual(literal_text(0x03000003, self.symbols, BASE, BASE+4, {}), "D_03000003")

# Synthetic ROM image at the cartridge base. Halfwords are Thumb encodings.
def thumb(*halfwords):
    return b"".join(struct.pack("<H", value) for value in halfwords)


@unittest.skipIf(capstone is None, "Optional Capstone dependency is absent")
class DecodeTests(unittest.TestCase):
    def test_register_stack_allocation_resolves_signed_literal_without_changing_bytes(self):
        # push lr; ldr r4,[pc,#4]; add sp,r4; pop pc; literal -568.
        data = thumb(0xB500, 0x4C01, 0x44A5, 0xBD00) + struct.pack('<I', 0xFFFFFDC8)
        code, pools, _, targets = decode(data, BASE, BASE + len(data))
        fixed, records = resolve_register_stack_adjustments(data, code, pools, targets)
        self.assertEqual(fixed[BASE + 4].mnemonic, 'sub')
        self.assertEqual(fixed[BASE + 4].op_str, 'sp, #0x238')
        self.assertEqual(fixed[BASE + 4].size, 2)
        self.assertEqual(bytes(fixed[BASE + 4].bytes), data[4:6])
        self.assertEqual(code[BASE + 4].op_str, 'sp, r4')
        self.assertEqual(records[0]['delta'], -568)

    def test_register_stack_restore_resolves_move_and_shift(self):
        # movs r3,#8E; lsls r3,r3,#2; add sp,r3; bx lr.
        data = thumb(0x238E, 0x009B, 0x449D, 0x4770)
        code, pools, _, targets = decode(data, BASE, BASE + len(data))
        fixed, records = resolve_register_stack_adjustments(data, code, pools, targets)
        self.assertEqual(fixed[BASE + 4].op_str, 'sp, #0x238')
        self.assertEqual(records[0]['delta'], 568)

    def test_stack_constants_do_not_survive_writes_calls_or_branch_joins(self):
        cases = [thumb(0x2304, 0x6813, 0x449D, 0x4770),  # unknown LDR r3,[r2]
                 thumb(0x2304, 0xF000, 0xF800, 0x449D, 0x4770),  # BL kills constants
                 thumb(0x2304, 0xE000, 0, 0x449D, 0x4770),  # branch target resets
                 thumb(0x2303, 0x449D, 0x4770)]  # unaligned value stays unchanged
        for data in cases:
            with self.subTest(data=data.hex()):
                code, pools, _, targets = decode(data, BASE, BASE + len(data))
                fixed, records = resolve_register_stack_adjustments(data, code, pools, targets)
                self.assertEqual(records, [])
                self.assertEqual(fixed, code)
        # A computed PC write or supervisor call also ends the known block.
        decoder = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_THUMB)
        decoder.detail = True
        for boundary in (0x4697, 0xDF00):  # mov pc,r2; svc #0
            data = thumb(0x2304, boundary, 0x449D, 0x4770)
            code = {i.address: i for i in decoder.disasm(data, BASE)}
            fixed, records = resolve_register_stack_adjustments(data, code, set(), set())
            self.assertEqual(records, [])
            self.assertEqual(fixed, code)

    def test_stack_input_is_separate_and_default_reference_remains_unchanged(self):
        data = thumb(0x238E, 0x009B, 0x449D, 0x4770)
        result = subprocess.CompletedProcess([], 0, 'void example(void) {}\n', '')
        with tempfile.TemporaryDirectory() as directory, patch('m2c_candidate.OUTPUT', Path(directory)), \
                patch('m2c_candidate.subprocess.run', return_value=result) as run:
            generate(data, Symbols(''), BASE, BASE + len(data), name='example', fix_register_stack=True)
            reference = (Path(directory)/'example.s').read_text()
            self.assertIn('\tadd\tsp, r3', reference)
            self.assertIn('\tadd\tsp, #0x238', (Path(directory)/'example.m2c.s').read_text())
            self.assertEqual(run.call_args.args[0][-1], str(Path(directory)/'example.m2c.s'))
            self.assertEqual(json.loads((Path(directory)/'example.stack_adjustments.json').read_text())['adjustments'][0]['delta'], 568)
            generate(data, Symbols(''), BASE, BASE + len(data), name='example')
            self.assertEqual((Path(directory)/'example.s').read_text(), reference)
            self.assertEqual(run.call_args.args[0][-1], str(Path(directory)/'example.s'))

    def test_stack_resolution_composes_with_reviewed_long_branches(self):
        data = thumb(0x2304, 0x449D, 0xF000, 0xF802, 0x4770, 0, 0x4770)
        result = subprocess.CompletedProcess([], 0, 'void example(void) {}\n', '')
        with tempfile.TemporaryDirectory() as directory, patch('m2c_candidate.OUTPUT', Path(directory)), \
                patch('m2c_candidate.subprocess.run', return_value=result):
            generate(data, Symbols(''), BASE, BASE + len(data), name='example',
                     long_branch_targets=[BASE + 12], fix_register_stack=True)
            semantic = (Path(directory)/'example.m2c.s').read_text()
            self.assertIn('\tadd\tsp, #0x4', semantic)
            self.assertIn('\tb\t.L0800000C', semantic)
            branch = json.loads((Path(directory)/'example.branch_hints.json').read_text())
            stack = json.loads((Path(directory)/'example.stack_adjustments.json').read_text())
            self.assertEqual(len(branch['sites']), 1)
            self.assertEqual(len(stack['adjustments']), 1)

    def test_internal_bl_is_a_call_by_default(self):
        # BL +8; bx lr; padding; bx lr. Internal addresses alone prove nothing.
        data = thumb(0xF000, 0xF802, 0x4770, 0, 0x4770)
        code, _, _, targets = decode(data, BASE, BASE + len(data))
        self.assertEqual(sorted(code), [BASE, BASE + 4])
        self.assertEqual(code[BASE].mnemonic, 'bl')
        self.assertNotIn(BASE + 8, targets)

    def test_reviewed_bl_jump_preserves_four_bytes_and_skips_fallthrough(self):
        data = thumb(0xF000, 0xF802, 0x4770, 0, 0x4770)
        code, _, _, targets = decode(data, BASE, BASE + len(data), [BASE + 8])
        self.assertEqual(sorted(code), [BASE, BASE + 8])
        self.assertEqual(code[BASE].mnemonic, 'b')
        self.assertEqual(code[BASE].size, 4)
        self.assertEqual(bytes(code[BASE].bytes), data[:4])
        self.assertEqual(targets, {BASE + 8})

    def test_invalid_or_unused_long_branch_hints_are_rejected(self):
        data = thumb(0xF000, 0xF802, 0x4770, 0, 0x4770)
        for target in [BASE - 2, BASE + 10, BASE + 9, BASE + 6]:
            with self.subTest(target=hex(target)), self.assertRaises(ValueError):
                decode(data, BASE, BASE + len(data), [target])

    def test_long_branch_input_keeps_reference_and_other_calls_unchanged(self):
        # Ordinary BL at+0 stays a call; reviewed BL at+4 jumps over bx lr.
        data = thumb(0xF000, 0xF806, 0xF000, 0xF802, 0x4770, 0, 0x4770)
        symbols = Symbols('')
        result = subprocess.CompletedProcess([], 0, 'void example(void) {}\n', '')
        with tempfile.TemporaryDirectory() as directory, patch('m2c_candidate.OUTPUT', Path(directory)), \
                patch('m2c_candidate.subprocess.run', return_value=result) as run:
            _, _, _, reference, _ = generate(data, symbols, BASE, BASE + len(data), name='example',
                                             long_branch_targets=[BASE + 12])
            original = reference.read_text()
            generate(data, symbols, BASE, BASE + len(data), name='plain')
            self.assertEqual(original, (Path(directory)/'plain.s').read_text().replace('plain', 'example'))
            semantic = (Path(directory)/'example.m2c.s').read_text()
            self.assertIn('\tbl\tsub_08000010', semantic)
            self.assertIn('\tb\t.L0800000C', semantic)
            self.assertEqual(run.call_args_list[0].args[0][-1], str(Path(directory)/'example.m2c.s'))
            audit = json.loads((Path(directory)/'example.branch_hints.json').read_text())
            self.assertEqual(audit['sites'], [{'address': '0x08000004', 'target': '0x0800000C',
                                              'rom_bytes': data[4:8].hex()}])

    def test_long_branch_generation_requires_explicit_bounds(self):
        with self.assertRaisesRegex(ValueError, 'explicit'):
            generate(thumb(0x4770), Symbols(''), BASE, long_branch_targets=[BASE])

    def test_literal_pool_is_data_not_code(self):
        # push {lr}; ldr r0, [pc, #4]; pop {pc}; padding; .word 0x03001234
        data = thumb(0xB500, 0x4801, 0xBD00, 0x0000) + struct.pack("<I", 0x03001234)
        code, pools, tables, _ = decode(data, BASE, BASE + len(data))
        self.assertEqual(sorted(code), [BASE, BASE + 2, BASE + 4])
        self.assertEqual(pools, {BASE + 8})
        self.assertEqual(tables, {})

    def test_switch_table_targets_are_followed(self):
        # cmp r0, #1; bhi default; lsl r0, #2; ldr r1, [pc, #8]; add r0, r1;
        # ldr r0, [r0]; mov pc, r0; pool -> table at +0x14; table: case0, case1;
        # case0: bx lr; case1/default: bx lr
        table, case0, case1 = BASE + 0x14, BASE + 0x1C, BASE + 0x1E
        data = (thumb(0x2801, 0xD80C, 0x0080, 0x4902, 0x1840, 0x6800, 0x4687, 0x0000)
                + struct.pack("<III", table, case0, case1) + thumb(0x4770, 0x4770))
        code, pools, tables, targets = decode(data, BASE, BASE + len(data))
        self.assertEqual(tables, {table: [case0, case1]})
        self.assertIn(case0, code)
        self.assertIn(case1, code)
        self.assertNotIn(table, code)
        self.assertIn(case1, targets)



@unittest.skipIf(capstone is None, "Optional Capstone dependency is absent")
class AsmDiffTests(unittest.TestCase):
    def test_register_only_difference_is_marked(self):
        from asm_diff import diff
        # adds r0, r1, #0; bx lr  versus  adds r2, r1, #0; bx lr
        rows = diff(thumb(0x1C08, 0x4770), thumb(0x1C0A, 0x4770), BASE)
        self.assertEqual([mark for mark, _, _ in rows], ["r", " "])

    def test_shifted_pool_load_with_same_value_is_equal(self):
        from asm_diff import diff
        # ldr r0, [pc, #0] / [pc, #4] loading the same word, then bx lr
        expected = thumb(0x4800, 0x4770) + struct.pack("<I", 0x03001234) + struct.pack("<I", 0)
        actual = thumb(0x4801, 0x4770) + struct.pack("<I", 0) + struct.pack("<I", 0x03001234)
        rows = diff(expected, actual, BASE)
        self.assertEqual(rows[0][0], " ")
        self.assertIn("=0x03001234", rows[0][1][2])


if __name__ == "__main__":
    unittest.main()
