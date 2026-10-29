# GNU compiler runtime

Five runtime functions have exact assembly matches to `libgcc/lib1thumb.asm`
from [pret/agbcc](https://github.com/pret/agbcc/blob/da598c1d918402c42c0c0d7128ba14567f3175e9/libgcc/lib1thumb.asm),
pinned commit `da598c1d918402c42c0c0d7128ba14567f3175e9`.
The upstream file's SHA-256 is
`8c1f8305f4fcf59f18d3140e32a77988ea76026d442e6bbcfe3c1c0b821362f4`.
Richard Earnshaw authored the division algorithms.

| ROM interval | Symbol | Bytes including alignment |
| --- | --- | ---: |
| `0807CD2C..0807CDC0` | `__divsi3` | 148 |
| `0807CDC0..0807CDC4` | `__div0` | 4 |
| `0807CDF8..0807CEC8` | `__modsi3` | 208 |
| `0807CEC8..0807CF40` | `__udivsi3` | 120 |
| `0807CF40..0807D000` | `__umodsi3` | 192 |

Sources are in `asm/libgcc/`. They were preprocessed with the upstream
`L_divsi3`, `L_dvmd_tls`, `L_modsi3`, `L_udivsi3`, and `L_umodsi3` selectors.
The only assembly changes are explicit ELF sections and final `.align 2, 0`,
which mirrors upstream's Makefile convention. Instruction streams are unchanged.
Every routine passed an isolated fixed-address comparison, followed by a full
8 MiB matching rebuild.

The assembly retains upstream's copyright, GPL terms and linking exceptions;
the accompanying GPL version 2 text is in `asm/libgcc/COPYING`. These terms apply
to the imported runtime sources. They do not establish a license for cartridge
data or for the project as a whole.

Both divide-by-zero and modulo-by-zero call `__div0`, whose default implementation
returns immediately. The callers then return zero. The signed division helper
is used by the reconstructed frame affine helpers. The overflow case
`INT_MIN / -1` follows the original 32-bit machine result rather than portable C
division semantics.

These functions are original upstream assembly, so progress counts them as
assembly rather than C decompilation.

## Floating-point and 64-bit C

The same pinned source's `old_agbcc` variant reproduces **44 runtime C function
intervals, 6,104 bytes**, from `libgcc/fp-bit-base.c` and `libgcc/libgcc2.c`.
The runtime uses `-O2` without `-mthumb-interwork`, as in upstream's libgcc
Makefile. The adapter adds `-ffunction-sections` for the fixed-address build and
explicit zero-fill section alignment. These settings preserve every instruction,
literal, and relocation in the original intervals.

| ROM interval | Source wrapper | Content |
| --- | --- | --- |
| `0807CDC4..0807CDF8` | `src/libgcc/fixunssfsi.c` | Float to unsigned 32-bit integer |
| `0807D000..0807DD9C` | `src/libgcc/double.c` | Twenty double-precision runtime functions |
| `0807DD9C..0807E6E8` | `src/libgcc/single.c` | Twenty single-precision runtime functions |
| `0807E6E8..0807E71C` | `src/libgcc/lshrdi3.c` | Logical 64-bit right shift |
| `0807E71C..0807E78C` | `src/libgcc/muldi3.c` | 64-bit multiplication |
| `0807E78C..0807E7A4` | `src/libgcc/negdi2.c` | 64-bit negation |

The imported implementation and needed historical headers are retained in
`src/libgcc/`, with their copyright and license text. The wrappers select the
same upstream conditional definitions. The single-precision wrapper defines
`FLOAT` and `FLOAT_BIT_ORDER_MISMATCH`; the double-precision wrapper defines
`FLOAT_BIT_ORDER_MISMATCH` and `FLOAT_WORD_ORDER_MISMATCH`. The original library
uses ARM's historical mixed-word double layout; these definitions are required
for matching and should not be replaced by host-native float representations.

One storage-binding adaptation replaces the function-local static `thenan` with
an external object. The original literal relocations establish its fixed RAM
addresses: double state at `03000408` (20 bytes) and single state at `03000420`
(16 bytes). Startup's IWRAM reset zeroes both. Their external declarations emit
the same code while avoiding a second allocation outside the original RAM
layout. No arithmetic or instruction-selection changes were made.

The installed old compiler's SHA-256 is
`ce74ca77f41d1f5b30733a67547c17b3c2a4367a5fa1b1ab919f9a3aae8139f6` in this
Windows host build. `tools/compiler_libgcc.py bootstrap` rebuilds it from the
pinned, unmodified compiler sources and records host/compiler provenance in
`tools/downloads/agbcc/old-provenance.json`.

All 44 functions passed isolated comparisons as C, then the complete cartridge
passed byte-for-byte equality. Progress distinguishes these imported runtime C
bytes from reconstructed game C. Matching the library establishes its source
family and settings; it does not identify the exact compiler executable used by
the original game studio.

## Newlib memory functions

`memcpy` at `0807E7A4..0807E804` (96 bytes) and `memset` at
`0807E804..0807E858` (84 bytes) match the pinned repository's
`libc/string/memcpy.c` and `libc/string/memset.c`. Their original unrolled
implementations are preserved in `src/libc/`, compiled with old_agbcc `-O2
-fno-builtin` and the same section/alignment convention.

The imported files use `libc_compat.h` in place of the original broad header
dependencies. It provides only their historical `size_t` (`unsigned long`) and
ANSI declaration macros, with the same expansions as Newlib's headers. The
function bodies are unchanged. The pinned source's `COPYING.NEWLIB` accompanies
the imports. Both functions passed isolated C comparisons and the full build.

These 180 bytes bring imported compiler/library C to 6,284 bytes in 46 function
intervals. Eight zero bytes at `0807E858..0807E860` remain explicitly copied
padding until their role is established.
