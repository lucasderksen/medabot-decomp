# Map metadata storage

`src/map_metadata.c` reconstructs the complete `08404634..08413FF0` interval
as fourteen objects: **63,932 bytes**, including two explicit alignment bytes.
The data is consumed by the already matched map, animation, dialogue and
selector helpers. Bounds and observed field layouts are in `map_metadata.h`.

| ROM range | Native storage |
| --- | --- |
| `08404634..0840947F` | 153 packed tile-animation records, 131 bytes each |
| `0840947F..08409480` | One zero alignment byte |
| `08409480..08409880` | 256 animation pointers; the final 64 slots are null |
| `08409880..0840F880` | 6,144 four-byte cell-direction records, 32 stored slots per map |
| `0840F880..0840FB80` | 192 direction-record pointers |
| `0840FB80..08411ADF` | 202 encoded messages, 8,031 bytes |
| `08411ADF..08411AE0` | One zero alignment byte |
| `08411AE0..08411E08` | 202 message pointers |
| `08411E08..08412E60` | 499 eight-byte exits plus 192 one-byte FF sentinels |
| `08412E60..08413160` | 192 exit-list pointers |
| `08413160..08413460` | 192 palette-selector pointers |
| `08413460..08413EE0` | 192 fourteen-byte palette-selector rows |
| `08413EE0..08413F20` | Sixteen indirect-selector pointers |
| `08413F20..08413FF0` | Sixteen thirteen-byte indirect-selector rows |

## Native layouts and boundary behavior

Each tile-animation record stores tile units, frame count, total tiles and 128
sequence bytes. Active records satisfy `totalTiles == tileUnits * frameCount`;
all sequence values before the FF terminator address a stored frame. Eighty-five
disabled records retain `FF FF 00` and an all-FF sequence. The directory's first
192 entries select the first 152 records, sharing the native disabled entries;
the last record remains stored without a directory reference.

`08048174` reads the tile-unit byte and gates playback on RAM enable and the
total-tiles byte. A nonzero timer decrements; otherwise an FF sequence byte
resets the byte cursor, requests `units * 32` DMA bytes to `06009020`, advances
the cursor and sets the timer to 2. The source now forms ROM and DMA-source
addresses as integers before converting back to pointers. This preserves the
unchecked native cursor, including reads into adjacent records at indices
128 and 255, while keeping all 156 function bytes exact.

`08052624` searches cells one step ahead of the player. A zero directions byte
terminates the search; the returned value selects `gContinuedScripts_08411AE0`.
Object 47's direction byte and `gLaterBuffer_03003810[0]` are the same address,
so the CPU model preserves that alias. **Map 81 has 32 nonterminating stored
records**. A failed search reads map 82's first zero record. The source uses
one contiguous 6,144-record bank and retains that cross-map read.

Exit records store X/Y, destination map, packed flags, two unknown bytes and
destination X/Y. `08052E88` uses the low flags bits as direction and the last
two coordinates when changing maps. `08052C68` returns the high flags nibble
for the last matching exit. The directory and existing reader now use const
byte pointers; no source records are padded past their one-byte sentinel.

The palette selector reader `08048684` passes stored values to `08048210`.
Codes D0..DF select the sixteen indirect rows using controlled RAM indices.
The selector source now computes ROM addresses before reads beyond a stored
thirteen-byte row, preserving the native unchecked RAM-byte index. The entire
120-byte function remains exact. Numeric names remain where semantics are
unestablished; neither table extent is a claim that native code clamps an index.

## Verification

All fourteen scratch/production data sections match with the normal GCC data
profile. All eleven functions in `fresh_helpers.c` remain exact with agbcc
`-fprologue-bugfix`; the second affected harvest file also matches with its
existing profile. `08052E88` remains 220 bytes after correcting its read-only
exit pointer declaration. This batch adds no functions or game-C bytes.

`python tools/check_map_metadata.py` executes original Thumb and passes:

- 5,208 cell queries, explicitly observing map 81's read of map 82's marker;
- 689 exit queries, including absent coordinates and packed interaction values;
- 2,712 tile-animation cases, including disabled playback, timers and adjacent
  ROM reads at indices 128/255;
- 10,816 direct/indirect selector cases, including indices 13 and 255.

Queries and selector code execute without stubs. Animation DMA writes are
recorded in ordinary MMIO memory; no transfer/rendering claim is made. The
existing dialogue CPU checker separately passes sixteen synthetic and all 202
native messages with its documented BIOS/drawing/sound stubs. Reports, scratch
generators and match specs are under `build/more/map_metadata*`,
`survey_map_metadata.py`, `reconstruct_map_metadata.py`, and
`map_fresh_helpers*`. Full-ROM/test gate: `checkpoint_map_metadata.log`.
