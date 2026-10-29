# Navigation and numeric display data

This batch reconstructs 11,596 bytes in twelve GCC data sections, with normal
data flags and no overrides. No new game function is claimed. Production
specifications are under `build/more/` with stems `navigation`,
`numeric_display`, `menu_navigation`, and `scene_graphics_loads`.

`src/unreferenced_rom_pointers.c` reconstructs 160 pointers at
`083D67AC..083D6A2C` (640 bytes), immediately before the existing sine table.
Their addresses increase strictly from `083D63DC` through `083D67A8`, and all
point to decoded banked-command boundaries in the preceding storage. No runtime
consumer is known; see `docs/BANKED_SCRIPTS.md` for the target-data evidence.

* `083D6118..083D62E4`: four selection values, a 16x10 tilemap, two banks of
  three halfword RAM pointers, 21 byte RAM pointers, and seven nested roots.
  Three nested roots are NULL; the others point inside the byte-pointer bank.
  Sub-list lengths are not inferred from those roots.
* `080AC71C`: sixteen hexadecimal glyph selectors.
* `080ACCF4..080AE8F4`: 224 physical 8x8 4bpp tile slots, represented as pixel
  rows. The old byte-view alias remains valid. The consumer accepts a byte
  index without a bounds check; indices beyond the physical bank are not
  asserted to be glyphs or clamped.
* `080AE8F4..080AEB74`: 320 signed sine samples, comprising a 256-phase cycle
  and a repeated 64-phase extension used for cosine lookup.
* `080AEB74..080AF774`: 192 graphics-load descriptors, 62 initialized and
  130 zero records. Source pointers relocate to already reconstructed LZ77
  streams. Every initialized stream decodes within its VRAM destination range;
  existing payloads receive no additional credit. The shared struct is in
  `include/scene_graphics_loads.h`; consumer 08049440 remains exactly 280 bytes.
* `080AF774..080AF864`: two navigation banks, each three modes by ten physical
  selections by four directions (left, right, up, down). Stored destination
  value 10 is preserved; the source does not assert that it is a valid next
  table index.

`python tools/check_navigation_data.py` executes original ROM routines in
1,944 direct-slot cases, 64 nested-root cases and 360 menu cases. It checks
underflow, overflow, acceleration, competing key priority, stored destination
values and callee preservation. Refresh helpers 080582B8/08059960 and sound
08074DE0 are explicit no-ops. Reports go to `build/analysis/`.

`python tools/check_numeric_display_data.py` checks 224 native tile transfers
with a host DMA3 copy model and sprite initialization 08048864 stubbed; 768
native affine calculations cover all 256 phases with three scale pairs;
12 tilemap cases check both destination strides, palette insertion and tile
offsets, including writes into surrounding guard memory. Fixed-point multiply
truncates toward zero; it is not a plain arithmetic shift for negative values.
Native affine and tilemap arithmetic execute without helper stubs.

`python tools/check_scene_animation.py` still agrees on 36,864 animation steps
across all 128 roots, preserving 17,335 adjacent-ROM prefetches. Its BIOS and
sound calls are recorded stubs. These isolated checks do not claim full game
rendering, reachability of every physical slot, or safety of reserved roots.

## Selector ASCII labels

`src/selector_ascii_labels.c` reconstructs the 64 ASCII labels and their
stored zero padding at `080AC604..080AC71C` (280 bytes). Existing absolute
address aliases remain available to the selector routine `08058C0C`.
`tools/check_selector_ascii_labels.py` runs 512 original selector fixtures,
reaching every label and checking each passed text length and preserved ABI.
The text renderer and other callees are stubbed; no rendered output is checked.

## Main-two selection and blend data

`src/main2_small_data.c` reconstructs twenty blend words at `080AF868`, nine
tile masks at `080AF8B8`, three sound choices at `080AF8CA` and a sixteen-color
name-entry palette at `080AF988` (133 bytes). Existing address aliases remain.
The original blend routine accepts value 160 and reads a word at `080AF8B8`,
overlapping the first two mask halfwords. `src/continued_blend_table.c` forms
that ROM address as an integer before reading, retaining the exact instructions
without indexing past the twenty-word array.

`tools/check_blend_steps.py` checks 165 original inputs and the adjacent read;
`tools/check_main2_tile_masks.py` checks 108 tile-mask cases with guarded VRAM.
`tools/check_main2_sound_choices.py` covers the three audio choices with helpers
stubbed, and `tools/check_name_entry_palette.py` covers the palette transfer in
eight native fixtures with DMA/BIOS modeled and other helpers stubbed.

## Main-two coordinates and palettes

`src/main2_coordinates_palettes.c` reconstructs four tile-coordinate pairs at
`080AFB80` and sixteen-color palettes at `080AFBC4` and `080AFC60` (72 bytes).
Existing fixed-address aliases remain. `tools/check_main2_coordinates.py`
checks 20 original tile-update cases against guarded VRAM without helper stubs.
`tools/check_main2_pair_palettes.py` checks 16 original loader fixtures and
covers both banks; DMA and CpuFastSet are modeled, other helpers stubbed.

## Copied masks and menu byte lookup

`src/serial_menu_lookup.c` reconstructs the four copied mask bytes at
`080AF864` and sixteen lookup bytes at `080AFB88`. `0805BB0C` copies the
first four bytes to its local stack; their later purpose is not established.
`08060D28` reads the byte lookup through an unchecked numeric ROM address,
so bytes beyond its physical span remain accessible as in the original.
`tools/check_serial_masks.py` and `tools/check_menu_byte_lookup.py` exercise
the original routines without helper stubs, including adjacent-ROM lookup.
