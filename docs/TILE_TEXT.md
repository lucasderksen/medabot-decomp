# Text and tile helpers

The assigned interval is `0x08042678..0x08042CA0`. Nine routine boundaries are supported by returns, caller targets, executable control flow, and intervening literal pools or zero alignment. The next entry at `0x08042CA0` is outside this assignment.

| Entry | End | Bytes | Observed operation | Status |
| --- | --- | ---: | --- | --- |
| 08042678 | 08042698 | 32 | Fill a byte string with 43, append FE | Exact C |
| 08042698 | 080426F0 | 88 | Write sequential tilemap entries | Exact C |
| 080426F0 | 08042838 | 328 | Render a number or marker in two columns | Exact C |
| 08042838 | 08042950 | 280 | Six-digit source, one-row tile output | Exact C |
| 08042950 | 08042A90 | 320 | Six-digit source, two-row tile output | Exact C |
| 08042A90 | 08042B58 | 200 | Two compact numbers with a separator | Exact C |
| 08042B58 | 08042B80 | 40 | Copy one 16-byte record slot | Exact C |
| 08042B80 | 08042BC0 | 64 | Map input values 0 through 7 to zero/one | Candidate |
| 08042BC0 | 08042CA0 | 224 | Sine-table coordinate offsets and packing | Exact C |

The current delivery contains 1,512 bytes of ordinary C in eight routines, compiled with the normal agbcc game settings plus `-fprologue-bugfix`. The isolated spec is `build/experiments/initialization/tile_text/delivery_spec.json`; the strict comparison includes padding and requires both size and all bytes to match. Names remain address-based because original SDK or game names are unknown.

The sequential tile helper derives a 2 KiB screen-block offset from bits 8 through 12 of the supplied BG control value. Its destination is `0x06000000 + screenOffset + x*2 + y*64`. Each row advances 32 halfwords; entries increment across row boundaries and wrap as unsigned halfwords. This routine does not implement a wider screen's quadrant transitions.

The two-column renderer narrows its first three inputs to bytes and its starting tile to a halfword. Values 0 through 99 render decimal digits with a blank leading column for values below ten. Values 100 through 254 instead render fixed entries `base+20` and `base+22`, each as a one-by-two tile column. Value FF renders `base+24` in both columns. These are observed marker patterns; their visual meaning has not been established. Quotients are explicitly narrowed to bytes before the next remainder calculation, reproducing the reference's shifts without reading back the digit array.

The two six-digit renderers divide the original value by 100000, then divide the remainder by 10000. Their following subtraction uses the original value divided by 10000, rather than that remainder. This unusual arithmetic is retained exactly and has not been corrected or generalized into a standard decimal formatter. The selected number of columns is narrowed to a byte. Rendering starts at byte index `(u8)(6-columns)` and does nothing if that index exceeds five; leading zero digits are blank until the first nonzero digit, but the final digit is always drawn.

The taller renderer writes the upper entry `base + digit*2` and the lower entry `(s16)base + (digit*2+1)` one tile row below. The destination uses a volatile halfword view, and an explicit discarded read at `*destination++` reproduces the reference's halfword read after writing each tile pair. Its zero/nonzero branches retain their own pointer advancement. This is a compatible model of the observed VRAM accesses, not proof of the original qualifier or a hardware requirement. Deriving the lower destination as `destination[32]` allows this compiler to generate the separate incrementing lower-row pointer seen in the ROM.

The coordinate helper reads signed halfword tables at `0x083D6C2C` and `0x083D6A2C`, scales the unsigned radius by the floating-point value 1/256, and converts both products to unsigned words. The conversion target `0x0807CDC4` is `__fixunssfsi`: it compares against 2^31, uses the signed converter for the lower range, and subtracts 2^31 before conversion for the upper range. Final coordinate packing keeps nine low bits of x and eight low bits of y at bit 16. The ordinary C return value is `struct TileCoordinates { u16 x; u16 y; }`. This aggregate uses an APCS hidden return-buffer argument: observed R0 points to the caller's stack result, while the four explicit arguments occupy R1, R2, R3 and one stack word. Call sites at `0x08043364`, `0x08043386`, `0x080433AC` and `0x080433D0` load the returned word from successive four-byte stack buffers. A one-word scalar or one-word struct uses a different return convention and was rejected by byte comparison.

The paired-number routine builds two two-byte digit arrays from division by ten and subtraction using the full quotient. Each tens digit is omitted when zero; ones digits are always emitted, with the supplied separator entry between the numbers. Inputs are not clamped to two decimal digits.

The record-slot copy reads 16 bytes from `0x083B83FC + record*64 + slot*16` and writes them forward into the supplied destination. An ordinary integer address temporary adds the combined record/slot offset before conversion to a byte pointer; this preserves the reference's address-construction order. It is a compatible source representation, not evidence of the original table declaration. Table bounds have not yet been independently proven.
