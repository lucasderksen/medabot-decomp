# Initial reverse engineering notes

These observations come from the local `A8BP` revision 0 dump identified in
`config/rom.json`. ROM offsets are GBA addresses minus `0x08000000`. Naming a
function describes observed behavior and does not recover its original name.

## Confirmed entry and interrupt code

- The header's ARM branch enters `0x080000C0`.
- Startup selects IRQ mode (`CPSR = 0x12`) and sets SP to `0x03007FA0`;
  system mode (`0x1F`) uses SP `0x03007F00`.
- Startup installs the ARM interrupt dispatcher at `0x08000104` in the BIOS
  callback slot `0x03007FFC`, then calls Thumb code at `0x0800025C`.
- The routine at `0x08000458` copies 0x800 bytes beginning with the dispatcher
  (ROM `0x08000104..0x08000904`) into IWRAM at `0x03001C10..0x03002410`
  and replaces the BIOS callback with that address. It copies fourteen handler
  pointers from ROM `0x0807E860` to IWRAM `0x03000BA0`.
- The dispatcher prioritizes the combined Timer3/Serial bits, then VBlank, VCount,
  HBlank, DMA0-3, keypad, and Timer2. A Game Pak interrupt writes the low byte of
  `0x2000` (zero) to `SOUNDCNT_X` at `0x04000084`, then loops.
- It acknowledges the selected IF bits, restricts IE with mask `0x26C0`, changes
  CPU mode while calling the selected handler, and restores IE/IME/SPSR.
- `0x08000824` acknowledges IF bit 1 (`0x0002`), identifying it as an HBlank
  handler. `0x08000840` is a dummy handler that returns immediately.

The dispatcher and surrounding ARM code assemble identically from
`asm/startup.s`; the Thumb main loop and initialization now compile identically
from ordinary C in `src/main.c` and `src/initialization.c`. Their earlier
assembly transcriptions remain as research references. VBlank/HBlank processing
now matches ordinary C in `src/interrupts.c`, and the fourteen-entry table is
typed C data in `src/interrupt_table.c`. The VBlank helper uploads scroll/OAM
state, invokes callbacks, and runs audio frame work. The guard and serial timeout
bookkeeping preserve the original memory widths and access order. See
[INTERRUPTS.md](INTERRUPTS.md) for verified field offsets.
Do not infer handler roles solely from the order of the ROM table;
the dispatcher uses its own priority order.

## Main loop

The Thumb routine at `0x0800025C` sets `WAITCNT = 0x4014`, calls memory and
interrupt initialization, enables sound, and enters the loop at `0x080002AC`.
The loop waits for VBlank, reads keys, performs serial/game work, and dispatches
through a function table at `0x083ABF98`, indexed by a word at `0x0300178C`.
It also calls routines at `0x08001520` and `0x080022DC` each iteration.
The complete 508-byte function now matches from ordinary C. The six-entry callback
table is typed C data in `src/main_callbacks.c`. The following table begins at
`0x083ABFB0` and has a separate reference at `0x08001760`, confirming the main
table boundary. Callback gameplay roles remain under investigation. Detailed
field widths and compiler-sensitive ordering are in [MAIN.md](MAIN.md).

The callbacks in main slots 0, 1, and 3 are themselves 32-byte dispatchers at
`08002534`, `0804763C`, and `08068440`. They now match ordinary C in
`src/callback_dispatch.c`. All three index a secondary table using the shared
word at `03002B8C`, named `gMainSubstate` descriptively. Their tables begin at
`083AC2C8`, `083D2104`, and `084856E8`, respectively. Table lengths and gameplay
roles remain under investigation. The state-zero table now has a verified
256-byte source interval ending at the independently referenced `083AC3C8`
table. It is typed C data with 64 pointers, including the dummy callbacks.
The state-one/state-three tables are still copied ROM intervals.

## Keypad reader

`ReadKeys` occupies `0x08000844` through `0x080008BF` (exclusive end
`0x080008C0`), including literal pools and padding. It reads `KEYINPUT` at
`0x04000130`, inverts the ten GBA button bits using XOR `0x03FF`, and calculates:

| RAM address | Width | Observed role |
| --- | --- | --- |
| `03002B64` | u16 | Held keys |
| `03001790` | u16 | Previous held keys |
| `0300058C` | u16 | Newly pressed keys: held & ~previous |
| `03001C00` | u16 | Released keys: previous & ~held |
| `03001798` | u16 | Key repeat events |
| `03002418` | u8 | Shared key repeat countdown |

A new press immediately creates a repeat event and loads countdown 16. If keys
are held, the countdown is decremented during the same call; when it is already
zero, all held keys become repeat events and the timer reloads to 3. The timer is
shared across buttons. It stops changing when no keys are held. This precise
ordering is preserved by the matching ordinary C in `src/input.c`.

## Small C helpers

`ExtractHighNibble` at `0x080502B0` is six bytes of Thumb code:
`lsl r0,24; lsr r0,28; bx lr`. It extracts bits 4-7 of the low byte and discards
all higher bits. Direct BL callers include `0x080502D2`, `0x08050444`,
`0x0805045E`, `0x08059D1C`, and `0x08059D36`. Its original C parameter type is
unknown; the reconstructed `u32` interface explicitly preserves truncation.
Its full source interval now includes the original two zero padding bytes through
`0x080502B8`.

`ExtractLowTwoBits` at `0x080502B8` masks a byte with 3. The `u8` argument/return
interface and ordinary expression `value & 3` reproduce its fourteen instruction
bytes and two padding bytes with agbcc. Both helpers live in `src/bitfields.c`.

`SetUnknownState8` at `0x08040B50` writes byte 8 to `0x03000444`, the fourth
offset of an unidentified object beginning at `0x03000440`, then returns. Its
12-byte interval includes a four-byte address literal. Seven Thumb pointers
near `0x083B2968` reference it. Its gameplay role is still unknown. It now matches
using the same standard historical-compiler settings as the main loop and keypad;
the initial modern GCC register/scheduling workarounds have been removed.

Three adjacent index routines at `080502C8..08050358` now match ordinary C in
`src/packed_fields.c`. Their observed arithmetic is:

| Function | Returned low byte |
| --- | --- |
| `080502C8` | `high_nibble(value) * 12 + low_two_bits(value) * 3` |
| `08050300` | `records[index].byte2B * 4 + value` |
| `08050320` | `records[mapper(index) + 79].byte2B * 12 + value * 3` |

The record base is `03002C30`, and addressing proves a 64-byte stride with the
accessed byte at offset `2B`. The frame helpers establish 128 records and share
the partial `FrameObject` declaration in `include/frame.h`. Gameplay meanings
remain under investigation. The mapper at `0804DBF0` now matches in
`src/continued_command_helpers.c`: a byte slot load minus one returns a full
signed word, including -1. Its canonical declaration and all earlier callers
pass the complete-ROM comparison. Explicit byte casts
after both helper calls preserve the original truncation order in the first
routine. See [FRAME.md](FRAME.md) for the verified renderer fields and helpers.

## BIOS and save library

At `0x0807CCC0` there is a group of conventional Thumb BIOS wrappers:
`CpuFastSet`, `CpuSet`, `Div`, `DivArm`, `Mod`, `LZ77UnCompVram`,
`LZ77UnCompWram`, `ObjAffineSet`, `Sqrt`, and `VBlankIntrWait`. Their SWI
numbers and exact instructions are recorded in `asm/bios.s`. Interworking
trampolines at `0x0807CCF0..0x0807CD2C` now assemble exactly from
`asm/trampolines.s`, with the conventional `_call_via_*` runtime names.

The ROM contains the SDK marker `EEPROM_V122` at `0x083ABE14`. The complete
ten-function library at `0x0807C8B0..0x0807CCC0` now matches reconstructed C,
using agbcc `-O1 -fprologue-bugfix`. Its 4/64-kilobit configurations, timeout
parameters, and 88 compiler-generated pointer constant bytes also match.
Boot passes 64 to the selector, choosing the 8 KiB / 1,024-doubleword
configuration. The game's save layout still needs investigation. Detailed
protocol and timer observations are in [EEPROM.md](EEPROM.md).

The routine at `0x08000218` disables IME, swaps pointers at `0x03005198` and
`0x0300519C`, returns the previous byte at `0x03005175`, clears that byte, and
reenables IME. Its descriptive name is `SwapSerialBuffers`. The complete serial
block now matches C; the 0xD8-byte context, packet fields, IRQ code-copy behavior,
and buffer ownership are documented in [SERIAL.md](SERIAL.md).

## Graphics and callbacks

Thirteen matching graphics functions cover custom Le loading, row copying,
affine transforms, scanline DMA, random/interpolation arithmetic and palette
snapshots/uploads. The sine and random tables are typed data. Three remaining
tilemap/palette loops and the larger frame renderer are still being matched.
See [GRAPHICS.md](GRAPHICS.md) for addresses, memory widths and supported
compiler-loop settings, and [FRAME.md](FRAME.md) for object and OAM handling.

An expanding contiguous callback block after `080025B4` now matches ordinary C.
It handles BG1 scroll, nested callback states, several-frame row transitions,
four-position selection, cursor setup and state changes. Shared-object fields
retain address/offset names until their wider roles are established.
The entry/link block now matches through `08004AF8`, including two larger
display initializers and three-record transfer preparation. Thirteen helpers at
`0803EED8..0803F684` also match, with one wide row-copy interval still copied;
their behavior is documented in [DISPLAY_HELPERS.md](DISPLAY_HELPERS.md).
The complete 28-function effect-work interval now matches, including its text
compositors, bytecode interpreter and delay/input helpers; seven adjacent
callback tables are typed data. Record and inventory callbacks now extend
through the next inventory dispatcher and its callbacks at `080093F8`.
All twenty-six shared inventory-view helpers through `0800A000` also match.
Copied gaps include the script selector at `08008CA0`, the
transfer loop, two earlier text loops, the `08006F34` return-value experiment,
and transfer-object setup/duplicate/blinking helpers. Two part-text and inventory
callback tables are typed C data. Frame/object helpers also cover animation
commands, decimal output and inventory access. See [EFFECT_WORK.md](EFFECT_WORK.md),
[FRAME_OBJECTS.md](FRAME_OBJECTS.md), [OBJECT_HELPERS.md](OBJECT_HELPERS.md),
[TILE_TEXT.md](TILE_TEXT.md) and [COORDINATE_HELPERS.md](COORDINATE_HELPERS.md).
[EQUIPMENT_HELPERS.md](EQUIPMENT_HELPERS.md) and
[UTILITY_HELPERS.md](UTILITY_HELPERS.md) describe the following asset, scroll,
motion and display-setup routines. [RECORD_HELPERS.md](RECORD_HELPERS.md) records
the following mode, memory-transfer and OAM helpers.
[STATE0.md](STATE0.md) records observed transitions and simultaneous-button
ordering. Recovered compiler/runtime sources and their provenance are in
[RUNTIME.md](RUNTIME.md).

## Next research tasks

1. Continue using the compatible historical compiler established by independent
   keypad, main-loop, and initialization C matches. Record any functions that
   require another compiler family or library-specific settings.
2. Finish the custom Le decoder, graphics loops and frame renderer as matching C.
   Preserve alignment, overlapping references and original hardware access order.
3. Trace the callback table at `0x083ABF98` and the state at `0x0300178C` to
   separate title, overworld, menu, and battle dispatch.
4. Extend callback decompilation and verify secondary-table boundaries before
   replacing the copied tables with typed data.
5. Establish code/data boundaries and then extract tables, text encodings,
   compressed graphics, maps, audio, and save structures into documented assets.

Use `tools/analyze.py disasm` for mixed ARM/Thumb inspection and `xrefs` for
candidate BL/pointer references. Its default Thumb scan bound `0x0807CCC0` is a
research convenience; it is not a verified contiguous code region.

## Validation scope

The complete linked ROM has the same SHA-256 as the cartridge dump. All production
C, typed data, and handwritten assembly intervals participate in that comparison.
The rebuilt game boots in the pinned mGBA core and reaches the intro, title,
New Game/options menu and opening story through repeatable button scripts.
The observed paths associate main states 3, 2 and 1 with those respective
contexts; state-zero screen names remain provisional. These traces do not cover
all gameplay or original hardware. See [EMULATION.md](EMULATION.md).
Isolated CPU checks now
execute the original custom compression routines against synthetic streams and
all 1,508 bounded scan candidates, agreeing with the host decoder for byte and
halfword destinations, including odd VRAM addresses. Decodability does not prove
that each scan candidate is used by the game. See [COMPRESSION.md](COMPRESSION.md).
Infrastructure
tests exercise corrupt-ROM rejection, manifest overlap/bounds checks, full ROM
coverage, and detection of changed output bytes. A matching ROM does not imply
that the copied game logic has been understood or decompiled.
