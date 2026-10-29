import struct
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from scene_programs import command_at, decode_bank, validate_roots


class SceneProgramTests(unittest.TestCase):
    def test_scheduled_call_has_optional_tail(self):
        short = struct.pack('<5i', 36, 2, 1, 48, 0x08000014)
        extended = struct.pack('<7i', 36, 2, 0x101, 48, 0x08000014, 1, 0)
        self.assertEqual(command_at(short, 0).end, 20)
        command = command_at(extended, 0)
        self.assertEqual(command.end, 28)
        self.assertEqual(command.target, 0x08000014)
        with self.assertRaises(ValueError):
            command_at(extended[:-4], 0)

    def test_negative_operands_and_terminal_are_stored(self):
        commands = decode_bank(struct.pack('<5i', 8, 9, 0, -123, 4), 0, 20)
        self.assertEqual(commands[0].words, (8, 9, 0, -123))
        self.assertEqual(commands[1].opcode, 4)

    def test_root_cannot_point_into_operand(self):
        commands = decode_bank(struct.pack('<5i', 6, 0, 0, 1, 4), 0, 20)
        validate_roots(commands, [0x08000000, 0x08000010])
        with self.assertRaises(ValueError):
            validate_roots(commands, [0x08000004])

    def test_call_target_cannot_point_into_operand(self):
        commands = decode_bank(struct.pack('<4i', 34, 2, 0x08000004, 35), 0, 16)
        with self.assertRaises(ValueError):
            validate_roots(commands, [0x08000000])

    def test_bounds_and_unknown_opcode(self):
        for data, offset, end in [(bytes(8), 1, 8), (bytes(8), 0, 12),
                                  (struct.pack('<i', 1), 0, 4),
                                  (struct.pack('<i', 0x7F), 0, 4)]:
            with self.subTest(data=data, offset=offset, end=end), self.assertRaises(ValueError):
                command_at(data, offset, end)

    def test_motion_setup_keeps_all_sixteen_payload_words(self):
        words = (18, 7, *range(16), 35)
        commands = decode_bank(struct.pack('<19i', *words), 0, 76)
        self.assertEqual(len(commands[0].words), 18)
        self.assertEqual(commands[0].words[-1], 15)
        self.assertEqual(commands[1].opcode, 35)


if __name__ == '__main__':
    unittest.main()
