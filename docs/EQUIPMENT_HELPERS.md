Eighteen equipment/display helpers are reconstructed as ordinary C in
`src/equipment_helpers.c`: 1,824 bytes match the reference ROM exactly. They
use normal agbcc with `-fprologue-bugfix`; canonical interfaces and observed
data aliases are in `include/equipment_helpers.h`. Address-based names remain
provisional because these routines alone do not establish a gameplay role.

| Range | Bytes | Observed behavior |
| --- | ---: | --- |
| 43560..435B0 | 80 | Update one byte at row*240+index*2+byteOffset of 03004C40. Subtraction wraps on byte storage; addition caps the unsigned sum at 99. |
| 435B0..4361C | 108 | Draw a 2x2 tile block. Value 255 selects entry+101C; values >=4 select entry+value*4+1000; smaller values select entry+value*4. Entry truncates to 16 bits. |
| 43814..4384C | 56 | Return 1 if record !=30 and all four other byte arguments <=119, otherwise 0. It does not test record <30. |
| 4384C..4387C | 48 | For input <=29, search nine stride8 records at 030017A0 for first byte >1 and third byte equal to input; return index or 255. |
| 4387C..438C4 | 72 | Copy one byte from stride8 table 083BEC10 indexed by work[7FE] to scratch 0300052E, store it to work[C29], and clear work[C2B]. |
| 43AE0..43B58 | 120 | Select buffer 02023C00 on odd frame counters or 02023200 on even frames, preload eight BG scroll registers, and configure DMA0 with source+16, destination 04000010 and control A6600004. |
| 43B58..43B7C | 36 | Wait for VBlank, clear DMA0's control upper halfword, and restore callback 03000B98 to DummyInterruptHandler. |
| 43B7C..43C08 | 140 | Load graphics and two tilemaps from four-pointer asset groups, then copy 64 palette words to hardware or 0202FA00 shadow according to the second argument. |
| 43C08..43C94 | 140 | Same sequence with five-pointer asset groups and different tilemap/palette slots. |
| 43C94..43CA8 | 20 | Compute signed value*100/255 from copied helper 424B8. |
| 43CA8..43CD4 | 44 | Clear all four canonical background scroll pairs. |
| 43CD4..43DF8 | 292 | Update transfer-work scroll group 39..40. |
| 43DF8..43E48 | 80 | Use blend fields 3C/3D/3E to update BLDALPHA, clear BLDY and set BLDCNT 1844; otherwise call existing blend setup with zero arguments. |
| 43E48..43E54 | 12 | Call the reconstructed scroll helper 43CD4. |
| 43E54..43E78 | 36 | Copy eight bytes from table 083C3CDC indexed by transfer-work byte 38 to offset 74. |
| 43E78..43F9C | 292 | Update transfer-work scroll group 74..7B. |
| 43F9C..43FEC | 80 | Same blend-register update as 43DF8, using fields 77/78/79. |
| 43FEC..44094 | 168 | Every third call advance a 128-position frame cursor, read width/frame table bytes, reset cursor on FF, and copy width*32 tile bytes to VRAM 06008020. |

The two scroll groups form a packed `EquipmentScrollControl` overlay in
canonical `State0TransferWork`. If selector is nonzero, add quarterSpeed to
the byte fraction. On a nonzero quotient by 4, store wholeStep, retain remainder
modulo 4, and apply every selected direction independently: bits 1/2 add/subtract
Y; bits 4/8 add/subtract X. Selector 1 addresses BG2 scroll and selector 2 BG3
scroll. Other nonzero selectors still advance the accumulator. Byte accumulator
and halfword scroll wrap are retained. The adjacent blend fields have separately
verified readers.

Compiler-sensitive ordinary source forms preserve the reference instructions.
Direct nested global fields produce the observed repeated address calculations;
a cached pointer view changes them. `/4` and `%4` preserve post-store byte
loads, whereas `&3` forwards the earlier sum. Asset loaders retain a local base
for the first call and global accesses afterward. Tile animation forms its
integer frame offset before adding the ROM table base. Direct volatile hardware
register stores match the DMA callback. No instruction patches or fixed-register
constraints are used.

Array bounds remain provisional where callers accept unchecked indices. The
still-copied 43960 builder writes 160 records of eight halfwords to a scanline
buffer, giving 2,560 bytes of observed coverage per selected buffer. Its C
candidate remains isolated until exact. Other gaps in 43560..44094 remain copied,
including inventory/part searches and the flag-gated byte-counter routine.

Staged delivery comparisons are reproducible with `tools/match.py` and JSON
files under `build/experiments/compiler_input`: equipment_helpers_ready,
equipment_helpers_next, equipment_helpers_copy, equipment_helpers_dma and
equipment_helpers_scroll. The scroll preview header was used only for isolated
verification; production uses the canonical shared header. Every integrated
section is also checked by the full-ROM build.

Two asset pointer tables are integrated as typed C data in `src/equipment_assets.c`: `gEquipmentAssets_083B2578[44]` occupies176 bytes at `3B2578..3B2628`, and `gEquipmentAssets_083B2628[55]` occupies220 bytes at `3B2628..3B2704`. They contain eleven groups of four and five pointers respectively. The four-pointer loader uses slots0/1/2/3 for graphics, palette, and two tilemaps; the five-pointer loader uses slots0/1/2/3/4 for two graphics sources, palette, and two tilemaps. Their 77 native compressed streams and 22 128-word palettes are reconstructed in src/equipment_graphics_data.c, with symbolic array references in both roots. The first rendered groups show battlefield terrain. All 99 payload sections and both roots match; commit 6904b7e also passed the fresh complete-ROM and 264-test checkpoint.

The separate bank at 083B2704 ends at the independently defined callback root
083B291C, giving 67 pairs of graphics and 16-word palettes. Its callers
0801BC5C and 0801BCA0 concatenate Le-decoded tile data into EWRAM according to
piece descriptors; 0801BCE4 copies one paired palette bank to hardware.
include/composite_graphics.h gives those callers the shared eight-byte record
layout. Native tile atlases show effect graphics. This bank is reconstructed
separately from the battlefield roots; no role is inferred from its old
provisional symbol name.
