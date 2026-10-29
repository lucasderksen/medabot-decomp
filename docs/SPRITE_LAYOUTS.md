# Sprite frame tables and object palettes

`src/sprite_layouts.c` reconstructs ROM `08075C50..0807C210` as
1,291 frame definitions and 141 pointer groups. These are data consumed by
the still-unmatched renderer at `08001520`, rather than executable code.
`include/sprite_layouts.h` records its four-byte header and eight-byte parts.

The renderer selects one of four root tables: `083ABFB0..083AC208` has
150 group pointers; `083AC208..083AC248`, `083AC248..083AC288` and
`083AC288..083AC2C8` each have sixteen. All four are reconstructed with
relocations to the actual group members, rather than integer ROM addresses.
They collectively reference 141 distinct groups.

At `080016E6`, the high byte of the frame/group selector indexes a root
with stride four; its low byte indexes the selected group with stride four.
The result points to a frame header. The renderer reads its first halfword
as the part count and starts the part cursor four bytes later. The second
header halfword is zero in every recovered record; its meaning remains
unknown, so it is named `reserved`.

Part halfwords are attributes, tile/palette, signed X and signed Y. Signed
coordinate loads occur at `08001956` and nearby instructions; the cursor
advances eight bytes at `08001C1A`. Observed counts are 1, 2, 3, 4, 5, 6,
7, 8, 12 and 14. Each definition therefore occupies `4 + 8 * count` bytes.
The union of those records and their contiguous pointer groups covers
exactly 26,048 bytes, without gaps or overlaps. The enclosing C aggregate
preserves their interleaving and lets group initializers refer to typed
frame headers. A compile-time assertion checks the complete aggregate size.

`src/object_palettes.c` reconstructs the following `0807C210..0807C8B0`
as 53 banks of sixteen RGB555 halfwords (1,696 bytes). Every color has bit
15 clear. The next address begins the EEPROM runtime. Known consumers:

| Source | Consumer and observed transfer |
| --- | --- |
| `0807C210` | `0806B820`: 240 halfwords to object palette RAM |
| `0807C3D0` | `08069E1C`: one sixteen-color bank |
| `0807C3F0`, `0807C450` | `08069E78`: eight words from each |
| `0807C410`, `0807C430` | `08069F44`, `08069EDC`: eight words each |
| `0807C470` | Literal reference at `08069B30` |
| `0807C490` | `0806D7A0`: 96 halfwords to palette RAM, then fourteen to saved work |
| `0807C570`, `0807C610` | Pointer entries at `08485A78`, `08485A7C`; `0806F114` transfers eighty halfwords |
| `0807C730`, `0807C7B0`, `0807C830`, `0807C870` | `08070D74`: 64, 64, 16 and 16 halfwords respectively |
| `0807C890` | Literal reference at `08070D48` |

The four banks `0807C6B0..0807C730` have the same sixteen-color layout,
but no direct aligned pointer was found. Their specific consumer remains
unknown. Existing address aliases for palette interiors remain in use by
accepted functions; this data recovery does not change those instructions.

Both sources use the project's strict modern GCC profile with no extra
flags. `tools/match.py` verifies 26,048 frame/group bytes, 792 root-table
bytes and 1,696 palette bytes exactly. Reproduction specs and boundary
audits are under `build/to70/`; production placement is recorded in
`config/segments.json`. The complete ROM build is the integration gate.

The provisional code-region metric includes the 27,744 bytes below
`0807C8B0`; these are **typed-data progress**, not newly matched functions.
The 792 root-table bytes lie outside that measured region.
