# Early graphics helpers

This block occupies ROM `0x08000E04..0x08001520` in the supplied European
Metabee revision 0 image. Names describe observed operations, not recovered
original SDK or game symbols. The functions are reconstructed C; their lookup
tables are typed representations of ROM data.

## Boundaries and verification

| Function | ROM start | Exclusive end | Bytes | C status |
| --- | --- | --- | ---: | --- |
| `LoadLeTilemap` | `08000E04` | `08000E40` | 60 | Exact |
| `LoadLeTileRows` | `08000E40` | `08000E70` | 48 | Exact |
| `LoadLeData` | `08000E70` | `08000E94` | 36 | Exact |
| `CopyTilemap` | `08000E94` | `08000F1C` | 136 | Candidate only |
| `CopyTileRows` | `08000F1C` | `08000F78` | 92 | Exact |
| `CopyLargeTilemap` | `08000F78` | `080010B4` | 316 | Exact |
| `SetBg3Affine` | `080010B4` | `08001188` | 212 | Exact |
| `PrepareBg2ScanlineAffine` | `08001188` | `08001278` | 240 | Exact |
| `StartBg2ScanlineDma` | `08001278` | `080012E4` | 108 | Exact |
| `StopBg2ScanlineDma` | `080012E4` | `080012F0` | 12 | Exact |
| `NextRandom` | `080012F0` | `0800134C` | 92 | Exact |
| `Lerp4096` | `0800134C` | `08001380` | 52 | Exact |
| `SnapshotPalettes` | `08001380` | `080013A8` | 40 | Exact |
| `BlendPalettes` | `080013A8` | `08001454` | 172 | Candidate only |
| `ApplyBlendedPalettes` | `08001454` | `0800147C` | 40 | Exact |
| `BlendPalette16` | `0800147C` | `08001520` | 164 | Candidate only |

The thirteen exact definitions currently account for 1,348 of the block's 1,820
bytes. `src/graphics.c` contains only verified definitions. The full working
candidate is `build/experiments/initialization/graphics_candidate.c`; nonmatching
candidates are excluded from the production build.

Code matches use the normal `agbcc` compiler, default `-O2`, with the per-source
flag `-fno-rerun-loop-opt`. The other twelve functions also match without that
flag; the wide tilemap routine requires it to retain the original loop layout.
Strict isolated verification is reproducible with:

```powershell
python tools/match.py build/experiments/initialization/graphics_spec.json --output-dir build/experiments/initialization/graphics_strict
python tools/match.py build/experiments/initialization/graphics_data_spec.json --output-dir build/experiments/initialization/graphics_data_strict
```

These checks include section sizes, literal pools, and zero alignment. They
establish equality to the reference ROM; they do not establish runtime behavior
on a GBA or identify the intended appearance of any particular game screen.

## Decompression and row copying

The three `LoadLe*` wrappers decompress into shared EWRAM scratch at
`0x02030000` using the game's `LeDecompress` routine. The same scratch region
also holds affine scanline data, so these operations depend on caller ordering.

`LoadLeTilemap` stores its fifth argument in `gTilemapEntryOffset` at
`0x03000580` before decompression and copying. The offset remains set afterward.
Tilemap copying adds it to the entire 16-bit entry, without separating the tile
number from flip or palette bits.

`LoadLeData` uses the decompressor's returned byte count, divides it by two,
masks it to 21 bits, and invokes BIOS `CpuSet` in halfword-copy mode. An odd
remaining byte is therefore omitted.

Both row-copy helpers read a 16-byte header, with dimensions at offsets 0 and
4 and currently unidentified words at offsets 8 and 12. `GraphicsRows` records
this observed layout. The meaning of the width differs between callers:
`CopyTilemap` treats it as a count of halfword entries; `CopyTileRows` treats it
as a byte count. A shared structural layout does not prove that the underlying
asset formats have identical dimension units.

For `CopyTileRows`, the exact address calculation is:

```text
rowShift = ((control & 0xC000) >> 14) + 3
destination = 0x06000000 + x
            + (((control >> 8) & 31) << 11)
            + (y << rowShift)
row address = destination + ((row << rowShift) * 2)
copy count = (width >> 1) & 0x1FFFFF halfwords
```

The source advances by `width` bytes after each BIOS call. The first `y` offset
and subsequent row stride intentionally retain the different factors present
in the original instructions.

The tilemap helpers describe the observed narrow and wide screen block layouts.
The narrow helper remains a candidate. Bit 14 of `control` selects the wide
helper. Its first quadrant
limits width and height to 32 using signed comparisons; subsequent quadrants
start at column or row 32 and use the asset dimensions as loop bounds. No
additional dimension validation has been inferred or introduced.

## Affine registers and scanline DMA

`SetBg3Affine` masks the angle to 10 bits and obtains sine/cosine samples from
`gSineTable`. It makes four separate BIOS division calls, in this order:

```text
pa = (cosine << 2) / scale
pb = (sine << 2) / scale
pc = ((-sine) << 2) / scale
pd = (cosine << 2) / scale
```

It then writes BG3's matrix as four halfwords at `0x04000030..0x04000036`.
Reference values are `-centerX*pa-centerY*pb-x` and
`-centerX*pc-centerY*pd-y`. Each is written as a low halfword and a masked
12-bit upper halfword to `0x04000038..0x0400003E`.

`PrepareBg2ScanlineAffine` has seven arguments; the incoming third register
argument is overwritten without being read. It prepares 160 records, each
containing four matrix halfwords and four reference-coordinate halfwords.
Even frame parity selects buffer `0x02030000`; odd parity selects
`0x02030A00`. Each buffer occupies `0xA00` bytes.

The denominator begins at 1 and increases by the first argument once per row.
For each row the routine calls `DivArm` twice with cosine/sine shifted left by
7. It negates the unscaled sine result for `pc`, triples the sine result for
`pb`, and triples the cosine result for `pd`. The reference values include
`pb*row` and `pd*row`. Signed arithmetic and the separate division calls are
preserved. The routine does not add a denominator-zero check.

After preparing the records, it assigns `StartBg2ScanlineDma` to the one-shot
VBlank callback at `0x03000B98`. That callback selects the other parity buffer,
loads record 0 into BG2 registers `0x04000020..0x0400002E`, disables DMA0, and
then programs:

| DMA0 field | Value |
| --- | --- |
| Source | Selected buffer plus `0x10` |
| Destination | `0x04000020` |
| Count/control | `0xA2600008` |

This transfers eight halfwords per HBlank, repeats, increments the source,
reloads the destination, and enables DMA. Initialization writes all eight BG2
halfwords before disabling/programming DMA0, matching the ROM's order.
`StopBg2ScanlineDma` only clears the high DMA0 control halfword.

The EWRAM record fields are declared `u16` to reproduce observed halfword loads.
Their storage type does not mean that the matrix coefficients are mathematically
unsigned. Hardware stores use a primitive `volatile u16 *`: this historical
compiler emits extra read-before-write operations for some volatile aggregate
field stores, which are absent from the reference.

## Lookup tables and compiler-sensitive expressions

`src/graphics_data.c` contains two modern-GCC data sections:

| Symbol | Input section | ROM interval | Bytes |
| --- | --- | --- | ---: |
| `gSineTable[1280]` | `.data.gSineTable` | `08075250..08075C50` | 2,560 |
| `gRandomTable[16]` | `.data.gRandomTable` | `0807E898..0807E8D8` | 64 |

Both arrays have exact independent data matches. The sine table contains 1,024
signed samples with amplitude 16,384, followed by an exact duplicate of samples
0..255. Values at indices 0, 256, 512, and 768 are respectively 0, 16,384, 0,
and -16,384. The duplicated quarter supports accesses at `angle+256` without
another mask. At `0x08075C50`, the data changes to structured words beginning
`1, 0x03A00000, 0x00050000, 1`, supporting the array's exclusive boundary.

The C declarations are nonconst, while their fixed link addresses lie in ROM.
For the sine table this is compiler-sensitive: a const declaration allows the
compiler to retain sample values across BIOS calls, whereas the original code
reloads them. That observation is not proof of the original declaration or a
claim that the physical table can be written.

Explicit integer byte offsets in both affine helpers preserve original pointer
arithmetic and literal ordering. Declaring the cosine pointer before the sine
pointer in the scanline helper reproduces its stack slots at offsets 8 and 12.
The row-copy helper likewise initializes the screen offset before the VRAM
`x` address to retain the original commuted ADD encoding.

The wide tilemap helper uses explicit byte offsets, with the destination address
as the first ADD operand. Disabling the second loop-optimization pass preserves
per-row dimension loads in the first quadrant and prevents a destination-offset
constant from occupying the global-offset pointer's register in the fourth.
The resulting function includes the original literal pool inside the first
quadrant loop and a second pool at its end. All dimension accesses remain
ordinary C accesses; no volatile qualifier or compiler barrier is required.

## Random values, interpolation, and palettes

`NextRandom` increments the counter at `0x03005034`, uses its low four bits to
select a table word, and XORs that word with the state at `0x0300503C`. It stores
the result at `0x03005038`, then updates the state by adding the inverted result
to the old state's signed upper halfword plus `0x55555555`. An explicit
intermediate sum preserves the original ADD operands.

A zero bound returns the full generated word. Otherwise it multiplies the
generated word's signed upper halfword, converted to `u32`, by the `u16` bound
and returns a logical right shift by 16. This unusual signed-halfword behavior
is retained rather than replaced by a generic random-range formula.

`Lerp4096` returns `b*weight/4096 + a*(4096-weight)/4096`. The two signed
divisions round toward zero independently; combining them into one division
would change both behavior and code generation.

`SnapshotPalettes` copies OBJ palette RAM at `0x05000200` to `0x0202F800`, then
BG palette RAM at `0x05000000` to `0x0202FA00`. Each transfer uses `CpuFastSet`
with 128 words, exactly 512 bytes. `ApplyBlendedPalettes` copies the corresponding
output buffers at `0x0202FC00` and `0x0202FE00` back in the same OBJ/BG order.

The two unmatched blend candidates reproduce RGB555 component blending toward
an input color, with weight clamped to 32. The full-palette routine processes
512 colors and schedules `ApplyBlendedPalettes` through the one-shot callback;
the smaller helper processes 16 colors supplied by its caller. They remain
experimental until their emitted instructions and padding match.
