# Serial block reconstruction

All eight routines in ROM `0x080020C8..0x08002534` are matching ordinary C in
`src/serial.c`. Their combined **1,132 bytes** include original instruction
sequences, register choices, literal pools, and zero alignment padding. They
use pinned normal agbcc with `-O2 -mthumb-interwork -ffunction-sections -Werror
-fprologue-bugfix`; see `docs/COMPILER.md` for reproducible bootstrap and
preprocessing commands. Address-based function names and descriptive fields
remain provisional.

| Routine | ROM interval | Bytes | Observed operation |
| --- | --- | ---: | --- |
| `sub_080020C8` | `20C8..2190` | 200 | Initialize serial hardware, RAM code, context, and buffer pointers |
| `sub_08002190` | `2190..21A4` | 20 | Set request byte when master byte is nonzero |
| `sub_080021A4` | `21A4..21F4` | 80 | Reset serial/timer controls and clear request byte |
| `sub_080021F4` | `21F4..22DC` | 232 | Poll phase, consume packets, advance sequence, and pack status |
| `sub_080022DC` | `22DC..2328` | 76 | Prepare pending send packet and checksum |
| `sub_08002328` | `2328..23D8` | 176 | Validate completed receive packets, copy payloads, and clear them |
| `sub_080023D8` | `23D8..2438` | 96 | Rotate buffers and start a requested transfer |
| `sub_08002438` | `2438..2534` | 252 | Exchange one halfword for each of four receive slots |

Every routine uses its own `.text.sub_<address>` input section. The isolated
comparison command is:

```powershell
python build/experiments/compiler_input/compare_serial.py src/serial.c
```

It reports exact sizes and byte equality for all eight intervals. The permanent
`python tools/build.py` command verifies the whole ROM after integration.
The experiment files and tool binaries are ignored local artifacts.

## Context and packet layout

The canonical types are in `include/serial.h`. `gSerialState` begins at
`0x03005170`; initialization clears `0xD8` bytes using CpuSet. Packet storage
has a 12-byte stride, established independently by initialization pointer
offsets and the interrupt's four-slot receive loop.

| Context offset | Type | Observation |
| --- | --- | --- |
| `00` | u8 | Master byte: set to 8 by poll, tested against zero or 8 |
| `01` | u8 | Phase: poll handles states zero and one |
| `02` | u8 | Remembered slot bitmap; main and receive code update it |
| `03` | u8 | Valid packet bitmap from the current receive poll |
| `04` | u8 | Pending send ready flag |
| `05` | u8 | Four-halfword receive completion flag |
| `06` | u8 | Transfer request flag |
| `07` | u8 | Copy of bit 6 from the 32-bit register read at `0x04000128` |
| `08..0A` | bytes | Meaning not established here |
| `0B` | u8 | Sequence byte incremented on every poll |
| `0C..13` | bytes | Meaning not established here |
| `14` | s32 | Send halfword position; initialization uses 6, active transfer starts at 0 |
| `18` | s32 | Receive halfword position; marker handling resets to -1 |
| `1C,20` | pointers | Pending and active send packets |
| `24,28,2C` | pointers | Active, pending, and completed four-packet receive buffers |
| `30..47` | two packets | Send buffer storage |
| `48..D7` | three groups of four packets | Receive buffer storage |

A packet consists of sequence byte at `00`, link bitmap byte at `01`,
checksum halfword at `02`, four-byte payload at `04`, and four unassigned
storage bytes at `08`. This block transfers and sums only the first four
halfwords. Preparing a packet zeroes its checksum, copies one payload word,
sums those halfwords, and stores the low halfword of the one's complement.
Receive validation sums four halfwords and accepts when their low 16 bits are
`0xFFFF`. Each accepted payload is copied into its corresponding four-byte
output slot. The completed payload word is cleared for every slot, including
slots rejected by the checksum test. Packet header and trailing storage bytes
are left untouched by that clear.

`MainSerialWork.words` therefore has four pairs of halfwords at context offset
`08..17`, rather than only the two pairs read explicitly by main. Its missing
poll counters remain at `19..1C`, followed by appeared/disappeared bytes at
`1D` and `1E`. The byte at `18` remains unassigned.

## Poll status and transfer observations

Poll returns current valid bits in bits `0..7` and remembered bits in `8..15`.
When the master byte equals 8, it additionally ORs `0x80`. A nonzero copied
bit-6 field ORs `0x1000`. These observations describe the actual operations;
they do not establish an original gameplay meaning for every bit.

The final original instructions perform unsigned `LSL #26`, unsigned
`LSR #30`, and compare the result against 3. That result is always in `0..3`,
so the following branch that would OR `0x2000` is unreachable for every
32-bit input. The C preserves `((u32)serialControl << 26 >> 30) > 3` to
reproduce this instruction sequence. It is not described as a recovered error
condition. The compiler's retention of this dead test is part of the match.

The interrupt snapshots all eight bytes at `0x04000120` into a local aligned
union, then handles four halfwords. When the first slot equals `0xFEFE` and the
previous receive position exceeds 3, it rotates the receive buffers, optionally
activates the pending send packet, and sets `0x80` in the BIOS interrupt flag
halfword at `0x03007FF8`. Each subsequent interrupt sends the selected local
halfword and stores the four received halfwords with a 12-byte packet stride.
The completion byte is set at receive position 3. Master mode also controls
the timer-3 halfword at `0x0400010E` and bit `0x80` of serial control.

Initialization copies 64 bytes from ARM `SwapSerialBuffers` at `0x08000218`
to `0x03005250`; receive calls the RAM address through `_call_via_r0`.
It also copies **288 bytes** from the Thumb IRQ entry at `0x08002438` to
`0x03005050`. This copy is 36 bytes longer than the IRQ routine's own 252-byte
interval, so the copied extent includes the beginning of the next ROM routine.
The source preserves that original count rather than assuming a function-size
copy. The RAM IRQ buffer ends exactly where `gSerialState` begins.

## Compiler-sensitive source choices

The leaf prologue option is an upstream compiler setting, not a binary patch.
The register snapshot union gives the eight-byte object four-byte alignment;
an ordinary struct containing only four halfwords would have two-byte
alignment and causes this compiler to call memcpy instead of generating the
original two word loads.

An aligned 16-bit `send` bitfield models the observed single halfword store at
`0x0400012A`. With this compiler, the plain volatile halfword-pointer form
emits an additional register copy, while a volatile bitfield form emits an
additional read. The matching bitfield store is unqualified; snapshot and
control accesses remain volatile and retain the original read widths.
The generated store and its order match the reference exactly. The choice
does not establish the original header declaration or promise portable MMIO
behavior under a different compiler.

The receive routine retains an eight-byte local scratch array whose first
word is zeroed before the RAM helper call, as the original does; only the
second word is passed to CpuSet for payload clears. The purpose of that first
stack write is unknown. Ordinary block-local pointer lifetimes and direct
packet payload expressions reproduce the original loop register allocation;
no inline assembly, fixed-register declarations, or emitted-byte patches are
used.
