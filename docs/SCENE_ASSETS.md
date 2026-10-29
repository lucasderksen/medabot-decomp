# Paired scene tile and palette directories

`src/scene_asset_data.c` reconstructs both 336-slot directories:
`gFreshPointers_083F7E80` at `083F7E80..083F83C0` and
`gPaletteSourcePointers_083F83C0` at `083F83C0..083F8900`. The latter ends at
the independently recovered map-dimension table. Both directories contain 147
distinct non-null asset pointers and 189 null slots, with identical null masks.
Each non-null tile pointer is exactly 32 bytes after its paired palette pointer.

The tile entries use relocations to the already sourced BIOS LZ77 streams at
`085D7018..085FB35C`. All 147 streams independently decode to `0x900` bytes;
their bounded consumed lengths agree with their existing source sections.
These compressed streams receive no additional coverage credit in this batch.

The 147 preceding palette banks and the separate override at `085FB684` are
stored as sixteen native halfwords each. All bits are preserved, including
bit 15 and `FFFF` values present in the original banks. Consumers `080486B0`,
`08048708`, `0804877C` and `08051E38` request eight-word (32-byte) DMA transfers.
`08069A08` also uses a sixteen-halfword transfer for one bank. The override is
the final transfer requested by `08048708`, now expressed with its data symbol
instead of an integer address. Its five-function source file remains exact
with agbcc `-fprologue-bugfix -fno-rerun-loop-opt`.

`include/scene_asset_data.h` provides the common directory bounds and palette
types. Null slots retain the native slot-1 fallback. The selector-return value
`FF` terminates the sequential palette loaders before a slot lookup; the
fixed twelve-load helpers retain their own native null fallback behavior.

`python tools/check_scene_assets.py` executes the original four loader routines
for every stored slot: **1,344 cases**, **5,038 DMA requests** and **4,032 BIOS
decompression requests**. Selector helpers supply the tested slot and the
sequential-list terminator. MMIO writes are recorded in ordinary mapped memory;
DMA and decompression are not emulated, so this verifies transfer requests and
fallback behavior rather than rendered graphics. Independent byte comparisons
verify the actual directory/palette contents. CPU report and decoded-stream
hashes are in `build/more/scene_asset_cpu.json` and `scene_asset_audit.json`.

All 150 scratch and production data sections match with the normal GCC profile,
as do all five functions in `palette_transfer_helpers.c`. This adds **7,424 data
bytes**: 2,688 directory bytes and 4,736 palette bytes. There is no new game-C or
function credit. Full-ROM/test gate: `build/more/checkpoint_scene_assets.log`.
