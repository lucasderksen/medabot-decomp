# Display helper reconstruction

The reference interval `0x0803EED8..0x0803F684` contains fourteen Thumb functions,
including their literal pools and zero alignment bytes. Address-based names
preserve the caller interfaces already used by the reconstructed state callbacks.
The descriptions below are inferred from instruction behavior, rather than
recovered original symbols.

| Start | End | Bytes | Observed behavior |
|---|---|---:|---|
| 0803EED8 | 0803EF20 | 72 | State transition guard involving callback-work byte 0x89 and serial-work bytes 0x1D/0x1E |
| 0803EF20 | 0803EF8C | 108 | Reset serial/memory/interrupt state, restore state 3, and initialize audio |
| 0803EF8C | 0803EFD8 | 76 | Fill a rectangle with a halfword entry, using 32 entries per row |
| 0803EFD8 | 0803F15C | 388 | Fill a rectangle across four 32x32 tilemap screen blocks |
| 0803F15C | 0803F1C8 | 108 | Copy consecutive source rows with a shared tilemap entry offset |
| 0803F1C8 | 0803F3A8 | 480 | Copy rows across four tilemap screen blocks |
| 0803F3A8 | 0803F3E0 | 56 | Load two compressed graphics assets and one sixteen-color palette |
| 0803F3E0 | 0803F41C | 60 | Enable BG0 and load a compressed map at row 13 |
| 0803F41C | 0803F480 | 100 | Load a bank/frame graphics asset and its palette |
| 0803F480 | 0803F51C | 156 | Set up BG0, load graphics, and copy an 8x8 tilemap |
| 0803F51C | 0803F624 | 264 | Advance a nine-frame tilemap sequence, with optional reverse indexing |
| 0803F624 | 0803F63C | 24 | Fill bytes, truncating the input value to eight bits |
| 0803F63C | 0803F65C | 32 | Copy bytes forward |
| 0803F65C | 0803F684 | 40 | Swap pairs of bytes forward |

## Verified source

Thirteen functions have matching C, totaling 1,484 bytes. The only outstanding
function is the 480-byte wide row copy at `0x0803F1C8`. These definitions use
agbcc with `-fprologue-bugfix`: the historical compiler's compatibility option
removes unnecessary LR preservation from the state guard and byte fill, without
changing the other eleven matching routines. The isolated integration specification is
`build/experiments/initialization/display/spec.json`; strict comparison results
are in that directory's `strict/results.json`. Unmatched candidates remain in
`build/experiments/initialization/display/candidate.c` and are excluded from the
production source. The parent build has confirmed that integration still produces
the reference ROM's complete 8 MiB SHA256.

## Memory and loading behavior

The simple rectangle fill computes its destination as
`0x06000000 + (((control >> 8) & 31) << 11) + x*2 + y*64`.
Only the low sixteen bits of the supplied entry are written. Width and height
are unsigned loop limits; this helper does not validate screen boundaries.

The wide fill selects one of four starting screen blocks from `x < 32` and
`y < 32`. A left-block row jumps forward `0x7C0` bytes immediately after writing
the last column before x=32. A top-block rectangle adds `0x800` bytes to its row
base after reaching y=32. The bottom-right base includes `0x1800`; the bottom-left
base includes `0x1000`. These additions preserve a 64x64 tilemap arranged as four
consecutive 32x32 screen blocks. The source uses shared destination/output pointers
and boundary counters across its branches; independently scoped pointers changed
register allocation despite having the same high-level behavior.

The state guard reads callback-work byte `0x03000440 + 0x89` and the aligned word
at serial-work offset `0x1C`. Its `0x00FFFF00` mask covers the `appeared` and
`disappeared` bytes recovered by the serial worker at offsets `0x1D` and `0x1E`.
When the callback-work byte is one and either serial event byte is nonzero, it
sets main state 0, subordinate state 10, and the word at `0x0300137C` to 16.
The local structure view preserves the original aligned word load without
claiming that the original source used this structure declaration.

The row-copy helper at `0x0803F15C` first stores the low halfword of `entryOffset`
in `gTilemapEntryOffset`. It copies source halfwords consecutively, adding the
current shared offset to each entry, while destination rows are separated by
32 entries. Source-pointer initialization occurs after destination construction;
moving it earlier changes its parameter-load position in the emitted code.

`sub_0803EF20` clears byte `0x03005030`, resets serial activity, waits for VBlank,
disables sound and interrupts, and calls the matching memory and IRQ initializers.
It then initializes serial state, sets main state 3 and clears the subordinate
state/countdown words. It stops DMA0 and performs another VBlank wait before
initializing audio at `0x03002430`, followed by a final VBlank wait.

The asset loader indexes the pointer table at `0x083AFE88` by `bank*9 + frame`.
The palette pointer table at `0x083B1748` is indexed by bank alone. Each palette
copy uses CpuFastSet count 8, meaning eight words (sixteen RGB555 colors).
The saved-palette branch writes to `0x0202FA00 + paletteSlot*32`; the immediate
branch writes to `0x05000000 + paletteSlot*32`.

`sub_0803F480` enables BG0 with DISPCNT bit 8, writes BG0CNT `0x0500`, decompresses
graphics to `0x06000F80`, and copies its palette to slot 13 at `0x050001A0`.
It selects the final frame of an independently supplied tilemap bank from
`0x083B4C60[mapBank*9 + 8]` and copies an 8x8 map with entry offset zero.

`sub_0803F3A8` decompresses `0x08486E6C` to VRAM `0x06000020` and `0x084C39D8`
to `0x06001780`, then loads sixteen colors from `0x08488520` into palette slot 15.
The sixteen-color palette is reconstructed in `src/interface_palette_banks.c`;
these calls do not establish the full compressed asset boundaries.

## Typed asset pointer tables

Subsequent independent inspection establishes the graphics-pointer table at
`0x083AFE88..0x083B1748` as 1,584 entries: 176 banks of nine pointers. Every entry
points to an asset beginning with the game's `Le` signature. The independently
loaded palette-table base at `0x083B1748` terminates that graphics table.

The palette-pointer table occupies `0x083B1748..0x083B1A08`, exactly 176 pointers,
matching the graphics bank count. It contains 97 distinct pointer values in the
range `0x084BF044..0x084BFC44`; unused/shared bank entries include repeated default
palettes. These payloads have no `Le` prefix. The next table at `0x083B1A08` has
its own code references, including the literal at `0x08042E3C` and several
references around `0x0805B1B0`. Its compressed-asset pointers are a separate run.
The matching counts, payload distinction, and independently referenced table
bases support both boundaries.

`src/display_assets_data.c` defines these two arrays with their existing symbol
names and compatible pointer types. Their asset payloads remain copied ROM data.
Modern GCC emits `.rodata.gUnknownPointers_083AFE88` (6,336 bytes) and
`.rodata.gUnknownPointers_083B1748` (704 bytes). Both pass strict size and byte
comparison using `build/experiments/initialization/display/data_spec.json`.
These 7,040 bytes are typed data, rather than decompiled game instructions.

## Nine-frame sequence

`sub_0803F51C` initializes graphics/palette data only when callback-work byte
`0x0E` is zero. Each call draws an 8x8 map from the table at `0x083B4C60` and
increments that byte. Forward indexing is `mapBank*9 + frame`; reverse indexing
is `mapBank*9 - (frame - 8)`. It returns one when the incremented byte equals
nine, and zero otherwise. The helper does not reset the frame itself.

The original also writes the low bytes of its first two arguments to a local
two-byte stack record that it does not subsequently read. An ordinary byte array
written through an incremented pointer preserves these stores with agbcc.
Direct aggregate-field assignments were optimized away; volatile aggregates
introduced additional reads absent from the ROM. The record's original purpose
is unknown. Explicit table-address and index temporaries retain the reverse
branch's `frame -= 8; index -= frame` instruction sequence.

The three final helpers fill, copy, or exchange individual bytes in increasing
address order. The copy helper has forward-copy behavior even if its memory
ranges overlap; it is not a memmove implementation. Their zero-byte counts
perform no accesses, and the fill value is reduced to its low byte.
