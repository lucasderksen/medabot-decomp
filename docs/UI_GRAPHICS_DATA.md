# Medal icons and menu/background palettes

`src/ui_graphics_data.c` reconstructs 13,920 bytes in 24 modern-GCC data
objects. It adds no game-C functions.

`084C29D8..084C38D8` stores 30 medal icons, each four 8-by-8, 4bpp tiles
(128 bytes). Native tile-map setup uses the tiles as top left, top right,
bottom left and bottom right. `084C38D8..084C39D8` contains two identical
fallback icons. `08017D50` selects an icon from a setup record with a 256-byte
stride, then copies 32 words to `06007800`. Other consumers use the same
128-byte selection stride or copy the whole 4,096-byte bank. Source `P8` rows
specify eight pixel indices explicitly, packing the leftmost pixel into the
least significant nibble of a word. Existing byte-view symbols remain at their
original addresses.

Thirteen physical palette banks cover `084F3A80..084F50E0` (5,728 bytes).
They contain 16-color RGB555 slots with all stored bits retained. Banks have
13 or 14 physical slots; a copy of 0x60 words uses 12 slots and a copy of
0x70 words uses 14. Stored lengths are distinguished from individual copy
lengths: the extra slots in a 13-slot bank are retained, without claiming that
each consumer copies all of them. The preceding byte at `084F3A7F` remains raw.

Nine background palette banks cover `087F1D40..087F2D40` (4,096 bytes).
Their addresses occupy slots 2, 3, 4, 5, 6, 8, 9, 10 and 11 of the existing
twelve-entry directory at `08486E24`; the other three assets are outside this
batch. `0806E2A0` copies 224 halfwords (14 palette slots) through DMA3.
`087F2600` has a 512-byte physical span: its last two palette slots are zero
and are not copied by this consumer. The two bytes before `087F1D40` remain
raw. No inferred padding was added to compressed streams.

All 24 production sections match. `tools/check_ui_graphics.py` executes the
original `08017D50` for 192 setup/selection cases, covering all 32 stored icon
slots, and `0806E2A0` for all twelve background indices. The latter expands
each packed 30-by-20 tile map to 32-by-20 and selects its palette. It checks
the resulting VRAM map, decoded tiles, exact 448-byte palette copy, surrounding
palette bytes, work fields, preserved registers and stack.

The checker explicitly models BIOS copy/LZ77 and immediate DMA3 transfers.
Display helpers `08068460` and `0803FAA0` are no-ops. These are bounded CPU/data
checks, not hardware timing or rendering checks.

```text
python tools/check_ui_graphics.py --output build/more/ui_graphics_cpu.json
python tools/match.py build/more/ui_graphics_production_spec.json --output-dir build/more/ui_graphics_production
```

## Background and sound register directories

`src/scene_and_sound_roots.c` reconstructs three twelve-entry directories
for background graphics, maps and palettes at `08486DC4..08486E54`. Each
pointer names an existing reconstructed asset. Existing absolute aliases keep
their addresses. `tools/check_ui_graphics.py` executes the original background
selection and map expansion for all twelve selections; BIOS LZ77 and DMA are
modeled and two display helpers are no-ops.

The following six pointers at `08486E54..08486E6C` identify the two sound
FIFOs, timers and DMA control registers. `tools/check_sound_register_roots.py`
runs twelve original routine fixtures through both channels; MMIO is ordinary
memory in this check and the timer-case helper is stubbed. No audio or hardware
timing behavior is claimed.
