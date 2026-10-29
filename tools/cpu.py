"""Bounded isolated ARM/Thumb routine execution for reverse-engineering checks.

Memory maps resemble GBA RAM/ROM addresses. This is CPU execution with ordinary
memory, not a GBA system emulator: BIOS, DMA, timers, interrupts, audio and video
devices are not implemented. Only self-contained routines are suitable.
"""

import sys
from common import ROOT

sys.path.insert(0, str(ROOT / "tools" / "python"))
try:
    import unicorn
    from unicorn import arm_const
except ImportError:
    unicorn = None
    arm_const = None


class RoutineCpu:
    RETURN_ADDRESS = 0x0203FFF0

    def __init__(self, rom):
        if unicorn is None:
            raise ValueError("Unicorn is optional; install it with python tools/bootstrap.py --emulation.")
        self.engine = unicorn.Uc(unicorn.UC_ARCH_ARM, unicorn.UC_MODE_THUMB)
        self.engine.ctl_set_cpu_model(arm_const.UC_CPU_ARM_TI925T)
        self.engine.mem_map(0x08000000, (len(rom) + 0xFFF) & ~0xFFF)
        self.engine.mem_write(0x08000000, rom)
        self.engine.mem_protect(0x08000000, (len(rom) + 0xFFF) & ~0xFFF, unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC)
        for address, size in ((0x02000000, 0x40000), (0x03000000, 0x8000), (0x06000000, 0x18000)):
            self.engine.mem_map(address, size)

    def write(self, address, data):
        self.engine.mem_write(address, data)

    def read(self, address, size):
        return bytes(self.engine.mem_read(address, size))

    def call(self, address, arguments=(), thumb=True, instruction_limit=2000000, timeout_us=2000000):
        if len(arguments) > 4:
            raise ValueError("This helper currently accepts only four register arguments.")
        if timeout_us < 0 or (timeout_us == 0 and instruction_limit <= 0):
            raise ValueError("CPU execution needs a time or instruction bound")
        registers = [getattr(arm_const, f"UC_ARM_REG_R{i}") for i in range(13)]
        for i, register in enumerate(registers):
            self.engine.reg_write(register, 0xAB000000 | i)
        for register, value in zip(registers[:4], arguments):
            self.engine.reg_write(register, value)
        self.engine.reg_write(arm_const.UC_ARM_REG_SP, 0x03007F00)
        self.engine.reg_write(arm_const.UC_ARM_REG_LR, self.RETURN_ADDRESS | 1)
        self.engine.emu_start(address | (1 if thumb else 0), self.RETURN_ADDRESS, timeout=timeout_us, count=instruction_limit)
        if self.engine.reg_read(arm_const.UC_ARM_REG_PC) != self.RETURN_ADDRESS:
            raise ValueError("Routine did not return within the instruction/time limit.")
        return tuple(self.engine.reg_read(register) for register in registers)
