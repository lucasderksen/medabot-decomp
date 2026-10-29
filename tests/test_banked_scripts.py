import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from banked_scripts import OPERANDS, decode, script_address


class BankedScriptTests(unittest.TestCase):
    def test_nested_commands_remain_separate(self):
        data = bytes([0x80, 0x81, 1, 2, 3, 255, 255, 255, 255, 255, 0x82, 6])
        commands = decode(data)
        self.assertEqual([x.opcode for x in commands], [0x80, 0x81, 0x82, 6])
        self.assertEqual(b"".join(x.encode() for x in commands), data)

    def test_dispatch_extent_and_shared_command_bytes(self):
        data = bytes([0x2F, 4, 14, 13, 2, 1, 8, 0, 242])
        commands = decode(data)
        self.assertEqual(commands[0].operands, bytes([4, 14, 13, 2]))
        # Native selector 3 branches into the last two dispatch bytes: 0D 02.
        self.assertEqual(decode(data, 3, 5)[0].opcode, 0x0D)

    def test_dispatch_forward_target_shortens_table(self):
        commands = decode(bytes([0x2F, 27, 3, 17, 6]))
        self.assertEqual(len(commands[0].operands), 3)
        self.assertEqual(commands[1].opcode, 6)

    def test_rejects_unknown_truncated_and_oversize(self):
        for data in (b"\x89", b"\x01\x00\x01", b"\x2f\x08", bytes(65537)):
            with self.assertRaises(ValueError):
                decode(data)
        with self.assertRaises(ValueError):
            decode(b"\x00", 1, 0)

    def test_cursor_and_offset_narrowing(self):
        self.assertEqual(script_address(0x4000, 2), 0x0876DEC0)
        self.assertEqual(script_address(0x5AD0, 1), 0x0876B990)
        self.assertEqual(script_address(0, 0, 65536), 0x08771EC0)
        self.assertEqual(len(OPERANDS), 0x89)


if __name__ == "__main__":
    unittest.main()
