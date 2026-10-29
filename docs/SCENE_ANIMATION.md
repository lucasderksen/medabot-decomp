# Scene animation storage and numeric tables

`src/scene_animation_data.c` reconstructs `083F704C..083F7D80`: 2,868 bytes of
native halfword commands and the following 128-entry pointer directory.
`08049440` selects the directory with object byte `24`, multiplies command byte
`22` by eight, and unconditionally fetches four halfwords before dispatch.
The halfwords are opcode, argument, duration and frame.

Stored records are variable-width despite that fixed runtime stride. `FFFE`
stores only an opcode and loop index; `FFFF` stores only its opcode. Fifty-eight
directory entries address short zero storage. The source uses a contiguous
halfword bank and pointers to its actual words, preserving those abbreviated
records and shared adjacent reads. It does not pad terminals into eight-byte
objects. In particular, the last zero root at `083F7B7C` prefetches duration and
frame words from the following pointer directory; zero storage is not a promise
of inert playback for arbitrary directory indices.

The reader now forms the eight-byte command address on the ROM bus before
fetching scalar halfwords. It remains **280 bytes exact** with agbcc
`-fprologue-bugfix`. Commands retain their stored values: `FFFD` advances and
recursively plays a sound command, `FFFE` resets the timer and recursively
enters the selected command index, `FFFF` stops, `FFFA` adds object byte `2F`
to the frame, and `FFFC` conditionally requests a graphics load before ordinary
duration/frame handling. Other opcodes use ordinary duration/frame handling.

`python tools/check_scene_animation.py` executes the original Thumb routine and
compares object fields, command prefetch addresses, sound/copy arguments,
R4..R11 and SP against a ROM-backed model. Across all 128 roots it checks 256
steps from timer/group zero and another 32 from timer/group 255: **36,864 steps**,
including **17,335 prefetches beyond individual root extents**. Sound and BIOS
decompression are recorded and stubbed; no rendered graphics or audio claim is
made. The CPU report is `build/more/scene_animation_cpu.json`.

`src/scene_numeric_data.c` adds four 256-element tables: signed halfword sine
and cosine at `083D6A2C` and `083D6C2C`, and native floats at `083D6F2C` and
`083D732C`. Integer cosine is exactly the quarter-phase integer sine table.
The float cosine/sine banks differ at 24 quarter-phase comparisons, so both
are stored independently using exact hexadecimal float literals. Together
these tables cover 3,072 bytes; no host trigonometric approximation is emitted.
Bounds and types are in `include/scene_numeric_data.h`; existing address aliases
for the integer sine bank retain their original addresses.

All six production data sections and the reader match in isolation. The batch
adds **6,452 data bytes**, with no additional function or game-C credit. Scratch
and production specs/audits use `build/more/scene_animation*` and
`build/more/scene_numeric*`; the full-ROM/test gate is
`build/more/checkpoint_scene_animation.log`.

The adjacent signed-byte wave at `083D6E2C..083D6F2C` stores two identical
128-step cycles with amplitude 100. All 256 stored values match truncation
toward zero of `100 * sin(2*pi*i/128)` for their phase; the source retains
the exact bytes rather than calculating them. No direct pointer or consumer is
identified, so the number of logical tables and their use are unknown.

The sparse block at `083D772C..083F704C` is typed as
`gSparseSceneRecords_083D772C[144][449]` halfwords in
`src/sparse_scene_records.c` (29 October 2026, data rule in AGENTS.md): the
144 records of 898 bytes differ only in halfwords 1 (`6 * i`) and 13
(`6 * i + 2`). They still have no established reader or format. A full byte-offset scan
of the reference ROM found no occurrences outside the block of the 22-byte
fragments at record-zero offsets 4 and 28, or the 18-byte fragments at offsets
6 and 30. This rules out exact copies of those fragments, not indirect access
or differently encoded records. To reproduce, search the complete ROM for each
slice `rom[0x3D772C + offset:0x3D772C + offset + length]`, excluding hits in
`0x3D772C..0x3F704C`.

The two varying halfwords in record `i` are `6*i` and `6*i+2`. As a
graphics hypothesis, those offsets correspond to six 32-byte tiles per
record: 144 groups span `0x6C00` bytes, the same space that `080482CC` fills
by decompressing twelve `0x900`-byte scene sheets. Decoding directory slots
0, 2, 10 and 37 and viewing each sheet as twelve consecutive six-tile groups
produces recognizable poses. This is evidence of a graphics relationship,
not proof of the sparse record format or a runtime reference to it.
