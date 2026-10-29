# Record display assets

`src/record_asset_data.c` reconstructs 26,256 bytes in 499 GCC data
sections, using the existing `RecordAssetPair` and `RecordAssetSet` layouts.
All sections are staged through `tools/match.py`; flags use the normal GCC
data profile without overrides. No game function is newly claimed here.

| ROM range | Representation |
| --- | --- |
| 083CF5B0..083D1940 | 1,138 physical 8-byte asset pairs |
| 083D1940..083D1D78 | 45 stored 24-byte sprite/asset descriptors |
| 083D1D78..083D1E40 | 50 descriptor pointers |
| 496 scattered 32-byte blocks | 16-halfword palette payloads |

The pair bank references 1,095 distinct previously reconstructed LZ77 tile
streams, plus 43 fully NULL pairs. Each nonzero primary stream decodes with
`tools/lz77_codec.py` and consumes exactly its existing section length.
Those existing payloads receive no additional coverage credit.

Companion words preserve all original addresses as relocations: 496 point
to raw palette payloads and 599 point to existing tile streams. Native loader
08045E6C copies 32 **raw bytes** from a selected first command's companion
into palette RAM and its shadow, even when that address names compressed
tile data. The source does not reinterpret or repair that behavior.

Descriptors retain their eleven incompletely understood bytes at offsets
04..0E; their first word is not asserted to be a frame count. Known children,
palette, dimensions, grid and sprite flags use the existing struct fields.
The pointer directory contains all 45 ROM descriptors, one NULL, and four
mutable RAM descriptors at 03005290/B0/D0/F0. The existing character-view
alias `gUnknownBytes_083D1D78` remains valid at the directory base.

Run `python tools/check_record_assets.py` for native validation. It executes
08045E6C with RAM fixtures independently selecting all 1,138 physical pairs;
host models implement LZ77 and CpuSet, while native 08045D34 sprite setup
executes unchanged. Checks cover decompressed tile bytes, raw palette bytes,
destination guards, tile increments, sprite attributes, returned byte counts,
callee-saved registers and stack restoration. A further 135 cases execute
08045D34 on all 45 original descriptors with varied palette/tile inputs,
including field truncation. Directory targets and child index bounds are
checked. Report: `build/analysis/record-assets-cpu.json`.

Fixtures establish the consumer's behavior for each stored pair; they do not
establish gameplay reachability or full rendering behavior. The original
08045E6C remains assembly/raw: its fresh m2c draft does not match.
