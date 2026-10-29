# Map object spawn storage

`src/map_object_spawns.c` reconstructs the complete `0847E40C..08483534`
prefix (20,776 bytes) and 22 script palettes (704 bytes): **21,480 new data
bytes**, in 29 objects. Shared bounds and the native eight-byte layout are in
`include/map_object_spawns.h`.

| ROM range | Storage |
| --- | --- |
| `0847E40C..0847E643` | Special map 83's 21-column, 27-row direction grid |
| `0847E643..0847E644` | One zero alignment byte |
| `0847E644..0847E704` | 192 scene-selection bytes |
| `0847E704..0847E76C` | 26 palette pointers |
| `0847E76C..0847E7D4` | 26 tile-stream pointers |
| `0847E7D4..08483234` | 2,188 object records and 192 full eight-byte terminals |
| `08483234..08483534` | 192 ascending map-object pointers |

Each object has X/Y bytes, a halfword attribute, appearance/order bytes and a
halfword visibility mask. `080513C8` scans each list by order 0..31 and tests
the visibility bit selected by work `7FF`. Attribute bits 12..15 select the
object type; bits 0..11 identify it. Appearance FF suppresses actor creation;
other values provide a high-nibble group and low-nibble frame. A terminal has
X == FF and seven zero bytes. The largest stored list has 66 objects; no
visibility state exposes more than 64 of them. Two stored objects have a zero
visibility mask and are retained.

`src/unreferenced_map_spawns.c` reconstructs two further lists at
`083D62F4..083D6374` and `083D6374..083D63D4`, plus an empty terminal at
`083D63D4..083D63DC` (232 bytes). The first two terminals have additional FF
values and nonzero order and mask fields rather than the main bank's zeros;
all stored fields are preserved. No normal reader for these lists is known. The
`--unreferenced-lists` option of `tools/check_map_object_spawns.py` redirects
map 0's pointer in emulated memory and runs 81 native loader fixtures covering
the lists and terminal behavior, with the same helper stubs as below. This
checks compatibility with the loader, not that the game normally selects them.

Rebuild mode 1 preserves existing frame selections when an ID matches a saved
descriptor. Mode 2 skips unmatched or inactive saved descriptors, but still
advances the output slot: skipped objects leave holes. The typed bank preserves
all source records, including those that do not create visible actors.

The special direction grid agrees with map 83's stored 42-by-54 tile dimensions
at half resolution. `08051C64` remaps direction bits for cell codes 1..4 and
otherwise returns its narrowed input. When work C30 is not FF, `080483F8` indexes
the scene table with the map byte at 7FE; otherwise it directly returns work C31.
Native map indices 192..255 continue
into adjacent ROM storage after the 192 stored selector bytes.

The graphic directories are independent. Slot 17 uses palette `08762858` with
tile stream `08765300`; it does not use the palette immediately before that
stream. The 26 tile slots reference 23 distinct existing BIOS LZ77 streams,
each decoding to 512 bytes. All consumed compressed sizes match their existing
source sections; this adds no compressed-payload credit. Every palette is an
exact sixteen-halfword bank, retaining all stored bits.

`tools/check_map_object_spawns.py` executes original `080513C8` with its real
clear/copy helpers and compares complete work, frame and attribute buffers,
saved registers, SP and frame-selection call arguments against an independent
ROM-backed model. It covers all
192 maps, all visibility bits used by each map, 0/15/31 controls, and modes
0/1/2. Event flags and actor/graphics-related operations are explicit
stubs; no rendering claim is made. It also checks every special-grid cell
with sixteen direction combinations plus FF, and the primary/fallback selector
paths including adjacent-ROM indices. The completed run passes 4,551 rebuild
cases, 9,639 direction cases and 1,024 selector cases, including 3,437 mode-2
holes. Report: `build/more/map_object_spawns_cpu.json`.

All 29 data sections and 16 functions across the three affected production
source files match under unchanged compiler profiles, including the 9,896-byte
script interpreter `0805424C`. The spawn-selection routine itself remains
unmatched C; the new data and native checks add no game-C/function credit.
Reproduction: `build/more/map_object_spawns*_spec.json`, `spawn_*_spec.json`,
`map_object_spawns_audit.json`; full gate `checkpoint_map_object_spawns.log`.
