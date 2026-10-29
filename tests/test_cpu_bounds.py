from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from cpu import RoutineCpu, unicorn


@unittest.skipIf(unicorn is None, "Optional Unicorn dependency is absent")
class CpuBoundsTests(unittest.TestCase):
    def test_instruction_only_bound_returns_and_preserves_registers(self):
        cpu = RoutineCpu(bytes(4096))
        cpu.write(0x02010000, b"\x70\x47")  # Thumb BX LR
        registers = cpu.call(0x02010000, (0x12345678,), instruction_limit=32, timeout_us=0)
        self.assertEqual(registers[0], 0x12345678)
        self.assertEqual(registers[4:12], tuple(0xAB000000 | i for i in range(4, 12)))

    def test_instruction_only_bound_stops_a_loop_and_rejects_unbounded_calls(self):
        cpu = RoutineCpu(bytes(4096))
        cpu.write(0x02010000, b"\xFE\xE7")  # Thumb B .
        with self.assertRaisesRegex(ValueError, "did not return"):
            cpu.call(0x02010000, instruction_limit=32, timeout_us=0)
        with self.assertRaisesRegex(ValueError, "needs a time or instruction bound"):
            cpu.call(0x02010000, instruction_limit=0, timeout_us=0)


if __name__ == "__main__":
    unittest.main()
