# Initialization routines

These observations and source matches use the supplied Metabee Europe revision 0
ROM with SHA-256
`4c64595190db3b4f50062d90a446fcab590f4e31c01830384558deca0691a26d`.
Function names describe observed behavior rather than recovered original names.

## Exact assembly coverage

`asm/initialization.s` reproduces the complete interval
`0x08000458..0x0800058C`, including alignment and literal pools. An independent
link using `build/experiments/initialization/verify_asm.py` compares all 308 bytes.
The reference slice and assembled output both have SHA-256
`db08590f55e741924d33941e815c5ed7a1addc62c09650440b675d56b79112c1`.

| Routine | Code and alignment | Literal pool | Exclusive end |
| --- | --- | --- | --- |
| `InitInterrupts` | `08000458..080004A8` | `080004A8..080004E0` | `080004E0` |
| `ResetMemory` | `080004E0..0800052C` | `0800052C..08000540` | `08000540` |
| `ResetSpritesAndVram` | `08000540..08000580` | `08000580..0800058C` | `0800058C` |

The halfwords at `080004A6` and `0800052A` are zero padding. The assembly spells
them out rather than accepting an assembler-selected NOP.

## Matching C

All three functions in `src/initialization.c` now compile to matching code and
literal pools with pret's `agbcc` compiler, GCC `2.9-arm-000512`, using
`-O2 -mthumb-interwork -ffunction-sections`. The compiler source commit is
`da598c1d918402c42c0c0d7128ba14567f3175e9`. No inline assembly, machine-code
arrays, or fixed-register constraints are used. The handwritten assembly remains
as the earlier verified reconstruction.

`build/experiments/initialization/verify_c.py` links each function at its original
address and compares its complete interval. Reference and compiled slices match:

| Section | Bytes | SHA-256 |
| --- | ---: | --- |
| `.text.InitInterrupts` | 136 | `f5c1712c04cd3e45199fcf44689cfebe63380e20b0a5458b47cf579ae581d7bb` |
| `.text.ResetMemory` | 96 | `2c6f89ecbd7b1640ba5586ebc738c4dbe8aea126f18fee431e3ed5a31857baaf` |
| `.text.ResetSpritesAndVram` | 76 | `23ea1528bb4ad39128e26b1fdfd168dc246d941f5e7d749f03a98f8dbc47d13c` |

The compiler emits explicit zero alignment for the internal literal pools. The
project compiler helper also supplies explicit zero alignment at section ends,
preventing modern GNU `as` from choosing a Thumb NOP for padding.

The sprite loop compares the next address as a **signed** 32-bit integer, matching
the original `bge` instruction. Its C condition calculates
`(s32)gOamShadow + i * 8` after decrementing the index. When the last entry has
been reset, the comparison uses the integer address eight bytes below the array;
it does not construct or dereference an out-of-bounds pointer. The array accesses
are only for indices 127 through zero. A simple index bound or an unsigned pointer
comparison compiles differently with this compiler.

## Interrupt setup

`GameMain` calls `ResetMemory` at `0800026E` and `InitInterrupts` at `08000272`.
The latter performs these operations in order:

1. `CpuSet` copies fourteen 32-bit handler pointers from `0807E860` to
   `03000BA0`, using control word `0400000E`.
2. `CpuSet` copies **512 words (0x800 bytes)** from
   `08000104..08000904` into `03001C10..03002410`, using control word
   `04000200`. The copy extends beyond the dispatcher body at
   `08000104..08000218`; its trailing bytes contain other startup and Thumb
   code. Only the dispatcher's entry is installed as a BIOS callback.
3. The ARM entry address `03001C10` is stored in the BIOS interrupt callback
   slot `03007FFC`; its low bit is clear.
4. Three callback slots at `03000B98`, `030017F0`, and `03002C20` receive the
   Thumb pointer `08000841` to `DummyInterruptHandler`. Their individual roles
   remain unidentified.
5. It writes `2601` to `IE` (`04000200`), enabling VBlank, DMA1, DMA2, and
   Game Pak interrupts. It writes `0008` to `DISPSTAT` (`04000004`) to enable
   the VBlank request, then writes `0001` to `IME` (`04000208`).
6. It calls `0807C8B0` with argument `0040`, followed by `0805DEB0`.

The final two calls have EEPROM-library evidence. The first truncates its input
to `u16`, accepts values `4` and `64`, and selects one of the adjacent ROM
structures at `083ABE20` and `083ABE2C` through the RAM pointer at `03007018`.
For `64`, it returns zero and selects `083ABE2C`. Other values select the first
structure and return one. These structures immediately follow the
`EEPROM_V122` marker at `083ABE14`. The second passes `2` and `03000BCC` to
`0807C918`, returning its result as a `u16`. Their exact library identifiers
are not yet established, so their assembly names remain provisional.

GBA interrupt bits should not be inferred from handler-table positions. In the
ARM dispatcher, mask `00C0` covers Timer3 and Serial, and mask `0020` covers
Timer2. They do not denote Timer2/3 and Timer1, respectively.

## Memory reset

`ResetMemory` disables `IME`, then uses stack-local fill values for BIOS
`CpuFastSet` calls. Bit 24 denotes fill; the count is in 32-bit words.
All counts here are multiples of eight words.

| Destination range (exclusive end) | Control | Bytes | Fill value |
| --- | --- | ---: | --- |
| EWRAM `02000000..02040000` | `01010000` | `40000` | `00000000` |
| IWRAM `03000000..03007D00` | `01001F40` | `7D00` | `00000000` |
| Palette RAM `05000000..05000400` | `01000100` | `400` | `00000000` |

The top `0x300` bytes of IWRAM remain intact. This preserves the stack locations
set by startup (`03007F00` system stack and `03007FA0` IRQ stack), and includes
the BIOS callback slot. Between the IWRAM and palette fills, the routine calls
`ResetSpritesAndVram`. Finally, it writes `7FFF` to the first palette halfword,
making palette entry zero white in RGB5. It leaves `IME` disabled for the
subsequent interrupt setup.

## OAM and VRAM reset

`ResetSpritesAndVram` fills OAM `07000000..07000400` with the word `000000A0`.
Each eight-byte hardware object entry therefore has `attr0 = 00A0`,
`attr1 = 0000`, `attr2 = 00A0`, and its affine halfword zero. The Y coordinate
160 lies below the visible 160-line screen for these normal 8-pixel objects.
This is a specific fill pattern; it is not an all-zero OAM clear.

It then iterates backwards through 128 shadow entries at `03001380`, storing
only `00A0` to each `attr0` halfword. The actual destination sequence is
`03001778`, `03001770`, ..., `03001380`. Other shadow fields are not modified
by this routine; `ResetMemory` has already cleared the entire shadow when it is
called during startup. A direct call must retain those other fields.

Finally, it fills the complete VRAM range `06000000..06018000` (0x18000 bytes)
with zero using `CpuFastSet` control `01006000`.

## Hardware references

The bit and register definitions were checked against the maintained
[libgba base definitions](https://github.com/devkitPro/libgba/blob/master/include/gba_base.h),
[interrupt definitions](https://github.com/devkitPro/libgba/blob/master/include/gba_interrupt.h),
and [video definitions](https://github.com/devkitPro/libgba/blob/master/include/gba_video.h).
The reconstruction uses project-local definitions; it does not copy libgba
implementation code. EEPROM conclusions above are observations and an inference
from the local marker and nearby behavior.
