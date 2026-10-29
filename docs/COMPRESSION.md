# Custom Le compression

The routine at `080009BC..08000A0C` is reconstructed as matching ordinary C in
`src/compression.c`. Its descriptive name is `LeDecompress`. It checks the two
signature bytes `4C 65` (ASCII `Le`) and returns zero for a different signature.
The original function does not validate bounds or stream integrity.

It dispatches destinations in the inclusive address range
`04000001..07FFFFFF` to `08000B14`, which writes halfwords while preserving
the other byte of each destination halfword. Other addresses use the byte-write
routine at `08000A0C`. This explains why graphics callers use the same interface
for EWRAM and VRAM destinations. The exact boundary at `04000000` is excluded
by the original unsigned range check and is preserved in the matching C.

The byte routine at `08000A0C..08000B14` is matching ordinary C in
`src/le_decompress_bytes.c` (264 bytes, agbcc `-fprologue-bugfix`). It retains
forward overlapping copies and the original unchecked count subtraction.
The halfword routine at `08000B14..08000E04` remains an experimental candidate.

## Stream format

| Offset | Size | Meaning |
| --- | ---: | --- |
| 0 | 2 | ASCII `Le` |
| 2 | 3 | Decoded byte length, little-endian |
| 5 | 1 | Skipped by both decoders; zero in inspected assets |
| 6 | variable | Command flag bytes and payloads |

Each flag byte holds four two-bit commands, consumed from least significant bits
to most significant bits. The decoder stops as soon as the declared byte length
has been produced, even if the last flag byte has unused commands.

| Command | Payload | Operation |
| --- | --- | --- |
| `0` | Little-endian 16-bit value | Copy `(value >> 12) + 3` bytes from distance `(value & 0xFFF) + 5` |
| `1` | One byte | Copy `(value >> 2) + 2` bytes from distance `(value & 3) + 1` |
| `2` | One literal byte | Append one byte |
| `3` | Three literal bytes | Append three bytes |

Backreferences copy forward one byte at a time; the source can overlap the output
being generated. For example, distance one repeats the last output byte.
The original loops subtract command lengths from an unsigned remaining count.
Valid assets end exactly at the declared length; malformed overshooting streams
can underflow that count and access unrelated memory.

`tools/le_codec.py` provides a bounded offline decoder for research. It rejects
truncation, references before the output buffer, declared-length overruns, and
oversized output. Those checks belong to the host tool and do not change the
original game code. Synthetic tests exercise all four commands, overlapping
copies, multiple flag groups, header handling, and rejection paths.

## Verified code references

The graphics-loading function at `080027DC` passes these ROM data addresses to
the dispatcher. All six streams decode successfully. Output purpose remains
provisional until tile/palette layout and game screens are correlated.

| ROM address | Destination | Compressed bytes consumed | Decoded bytes |
| --- | --- | ---: | ---: |
| `084C1E24` | `06001800` | 487 | 768 |
| `084C200C` | `06001B00` | 321 | 768 |
| `084C2150` | `06001E00` | 406 | 768 |
| `084C22E8` | `06002100` | 326 | 768 |
| `084871A4` | `06002400` | 266 | 480 |
| `084C8034` | `06017400` | 1759 | 2496 |

The first four adjacent streams have padding to a four-byte boundary:
487 becomes 488, 321 becomes 324, and 406 becomes 408 before the next known
stream starts. The intervening bytes are respectively `00`, `30 31 32`, and
`30 31`; padding is outside the consumed compressed stream and must be preserved
for an exact reconstruction.

```powershell
python tools/le_codec.py --start 0x084C1E24 --output data/extracted/le/4c1e24.bin
```

Decoded ROM assets are ignored by Git. Their extraction is research progress and
does not count as reconstructed source in `tools/analyze.py progress`. The build
still obtains these data intervals from the supplied reference ROM.

## CPU validation

The optional `tests/test_rom_compression_cpu.py` executes the original ROM's
Thumb dispatcher and both decoders using Unicorn 2.1.4. All six referenced assets
and synthetic command streams produce exactly the host decoder's bytes in EWRAM,
even VRAM addresses, and odd VRAM addresses. Neighboring bytes and callee-saved
registers are preserved, and the returned decoded size matches the header.

This check uses ordinary mapped memory and an isolated ARM/Thumb CPU model. It
does not emulate GBA devices, graphics timing, DMA, interrupts, or BIOS services.
It confirms the stream algorithm and halfword preservation logic; it is not a
full-game emulator playtest. Unicorn's API is documented in its
[official tutorial](https://www.unicorn-engine.org/docs/tutorial.html).

```powershell
python tools/bootstrap.py --emulation
python -m unittest discover -s tests -p test_rom_compression_cpu.py -v
```

CPU tests skip cleanly when the optional dependency or matching local ROM is
absent. The build itself does not need Unicorn.

## Part and battlefield asset source

The six-column part root at 083B1A08 contains 122 rows, ending at the independent
equipment root 083B2578. Its 732 unique streams consume 73,143 compressed bytes;
the symbolic root adds 2,928 bytes. Each row decodes to five 128-byte images and
one 384-byte sequence. Native command traces live in data/part_graphics and are
compiled by src/part_graphics_data.c using include/le_stream.h. Padding between
streams remains separate from the consumed bytecode.

The existing four- and five-column equipment roots select another 77 streams
and 22 palettes, totaling 215,174 bytes. The palettes contain 128 RGB555 words,
matching each caller's 64-word CpuFastSet. Each pair of tilemaps has a 16-byte
GraphicsRows header followed by 64x32 or 32x32 halfword cells. The original
horizontal/vertical flip and palette-bank bits render the first groups as
desert battlefield layers. All other header words and unused final command
flags remain unchanged. The five-column table's extra compressed stream is
retained without assigning an unproven role.

These assets are ordinary native-command source in data/equipment_graphics,
with typed C palettes and symbolic roots. Offline previews and bounded audits
are in build/resume; reconstructed source is credited only after its fresh
full-ROM checkpoint passes. Commit 6904b7e passed that gate and all 264 tests.

The next independently bounded bank, 083B2704..083B291C, contains 67 native
Le streams and 67 paired RGB555 palettes. With its shared eight-byte root
records it occupies 274,275 bytes. Its callers concatenate decoded tiles into
EWRAM and copy 32-byte palettes separately. Atlas previews show slash, impact
and explosion effects. Source lives in data/composite_graphics and
src/composite_graphics_data.c; include/composite_graphics.h is the common
record declaration for the root and both caller files.

Two other object banks have independent bounds at 083AFA0C..083AFACC and
083AFADC..083AFAEC. Their 26 native streams and 24 unique sixteen-color
palettes use 29,185 bytes including both symbolic roots. Callers decompress
to OBJ VRAM or EWRAM and transfer eight palette words. The source keeps the
flat alternating pointer layout used by those callers, in
src/object_assets_data.c and data/object_assets.

The other 324 inventoried streams occupy 282,371 bytes, reconstructed as
native command traces in data/le_streams and src/native_le_streams.c. Each has
an aligned explicit ROM reference, a bounded decode with the recorded output
hash, and the existing original-Thumb CPU validation. Names identify their
serialization address; higher-level resource roles remain in their callers.
Consumed ends exclude padding, and all intervals are disjoint from previous
source. All 324 production sections match in isolation; the fresh complete-ROM
checkpoint is the final acceptance gate. Together these source groups cover
all 1,508 nonempty streams in the validated inventory.

Commit abaffb2 passed the fresh full-ROM comparison and all 264 tests
(22.465s). The complete validated inventory now has 1,088,183 compressed bytes
represented in source.

## BIOS LZ77 research

The game also calls BIOS LZ77 entry points, including graphics at 085FB6E4 and
085FBC00. tools/lz77_codec.py is a bounded host decoder for 0x10 streams:
24-bit little-endian output length, eight high-to-low flag bits, literals or
big-endian packed distance/count pairs, and overlapping forward copies.
Its format was cross-checked against the primary
[mGBA BIOS implementation](https://github.com/mgba-emu/mgba/blob/master/src/gba/bios.c).
Seven synthetic tests cover flags, overlapping and distant copies, consumed
extent, offsets, size limits, truncation and invalid references. This is host
format validation; the new inventory has not been executed through a BIOS.

Semantic review after 5e0e12b excludes the 18-byte candidate at 0809B230:
it is outside the compressed resource region, and its table consumer has not
been proved to call BIOS decompression. Its interval returns to the ROM
remainder. The remaining source has 2,221 streams / 2,219,944 bytes. A valid
decode plus a pointer is useful evidence for research, but does not establish
a resource's consumer or role.

The final palette at 087F4444 is independently established by the 16-halfword
DMA in 0806E7EC to palette RAM 05000020. Its ignored RGB555 high bits remain
exact. The 48,028 bytes from 087F4464 to the ROM end are all zero; ordinary C
zero initialization represents this cartridge fill separately from graphics.

## Cartridge inventory

A bounded scan found **1,508 nonempty decodable candidates**, from ROM offset
`486E6C` through `787144`. All candidates begin at a four-byte boundary and have
zero in header byte 5. The largest declared output is 36,864 bytes; the outputs
have 1,287 distinct SHA-256 hashes. Decodability and duplication alone do not
establish callers, boundaries outside the consumed stream, or gameplay roles.

All 1,508 candidates were compared against the original Thumb dispatcher in both
EWRAM and at an odd VRAM address. The host output, returned size, neighboring
bytes, and callee-saved registers agreed for every candidate. The persistent
tool below reproduces that inventory check; the smaller unit tests remain the
usual check after parser changes.

```powershell
python tools/le_codec.py --scan --max-output 0x20000 --output build/analysis/le-inventory.json
python tools/check_le.py --inventory build/analysis/le-inventory.json
```

Use `--limit 6` for a quick tool smoke check. Inventory and CPU reports are local
ignored research outputs under `build/analysis/`.


## Reconstructed character portraits

The 176-by-nine frame root at 083AFE88 references 282 distinct Le streams.
All decode to 2,048 bytes: 64 row-major 8-by-8 tiles with four-bit palette
indices. The 176-entry palette root at 083B1748 references 97 sixteen-color
banks. The 8-by-8 tilemap consumers at 0803F480/0803F51C and the 32-byte palette
transfers establish the 64-by-64, 4bpp portrait layout. A twelve-frame rendered
contact sheet confirms the character portraits and expression variants.

The production source represents each original compression choice with
LE_FLAGS, LE_FAR, LE_NEAR, LE_BYTE and LE_TRIPLE initializers from
include/le_stream.h. data/portrait_frames stores these readable native command
traces; src/portrait_assets.c defines the streams and their raw RGB555 palettes.
Unused final flag bits and palette bit 15 are retained. Consumed stream ends
exclude alignment bytes, which remain separate intervals. Source roots use the
actual array symbols. PNG previews stay ignored and are not counted as source.

Staging proof covers all 379 sections / 226,427 bytes plus both existing root
sections / 7,040 bytes. Reproduction and boundary/hash audit are in
build/resume/reconstruct_portraits.py and display_frame_asset_audit.json.
Commit `7e60aa0` passed the fresh complete-ROM comparison and all 262 tests
(71.837s), then pushed this batch.


The formerly ambiguous0809B230 hit is now identified independently as the
35th nonempty resource's timing list:16,12,0. The root at083D2018 is59 duration
pointers, separate from the59 angle/coordinate roots at083D1E40/083D1F2C.
08044A5E..08044A82 counts bytes to zero;08047428 compares the selected byte
against elapsed time and uses the difference as an interpolation divisor.
The actual timing list occupies3 bytes, not the18-byte format-compatible LZ77
candidate. It remains excluded from compression credit and is reconstructed
with the other pose durations. This is direct consumer evidence, beyond the
original signature/pointer-based exclusion.
