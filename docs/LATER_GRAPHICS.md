# Later graphics helpers

The resumed initialization worker examined `080490E0..08049A6C` (2,444 bytes).
The orchestrator integrated sixteen exact C functions, totaling 756 bytes, into
`src/later_graphics.c`. The complete 8 MiB rebuild remains byte-identical to the
supplied reference. All sixteen use normal agbcc game settings plus
`-fprologue-bugfix`; every isolated delivery checks size, instruction bytes,
literal pools and zero alignment.

| Function interval | Bytes | Status | Established behavior |
| --- | ---: | --- | --- |
| 490E0..49110 | 48 | Integrated | Write a 2x2 tile-entry block, map stride 32 |
| 49110..49140 | 48 | Integrated | Write one selected subposition of that block |
| 49140..49198 | 88 | Integrated | Clamp height; copy rows with tile offset and palette OR |
| 49198..491B8 | 32 | Integrated | DMA3 copy eight halfwords into a BG palette bank |
| 491B8..49210 | 88 | Unresolved, 4 bytes differ | Fill a tilemap rectangle |
| 49210..492A8 | 152 | Unresolved, 42 bytes differ | Copy tile indices and preserve flip bits |
| 492A8..49318 | 112 | Unresolved, 6 bytes differ | Copy a rectangle between maps with equal stride |
| 49318..49344 | 44 | Integrated | Reset two settings halfwords and 32 matrix records |
| 49344..49374 | 48 | Integrated | Clear a four-byte slot and a 64-byte object |
| 49374..49420 | 172 | Integrated | Compute four matrix coefficients from angle/scales |
| 49420..49440 | 32 | Integrated | Set object byte24; clear bytes23 and22 |
| 49440..49558 | 280 | Unresolved, 8 bytes differ | Interpret eight-byte commands; recursive jumps and optional decompression |
| 49558..496EC | 404 | Unresolved, emits 392 | Input adjustment of matrix/object/settings values; returns zero |
| 496EC..496F0 | 4 | Integrated | Empty routine and zero alignment |
| 496F0..49714 | 36 | Integrated | DMA3 copy eight halfwords into an OBJ palette bank |
| 49714..49728 | 20 | Integrated | Clear bytes |
| 49728..49740 | 24 | Integrated | Fill bytes |
| 49740..49768 | 40 | Integrated | Count differing bytes, signed length |
| 49768..49780 | 24 | Integrated | Sum bytes, signed length |
| 49780..497C0 | 64 | Integrated | Update a mapped state byte, then return BIOS Mod narrowed to u8 |
| 497C0..497E0 | 32 | Integrated | Copy bytes |
| 497E0..49A6C | 652 | Not reconstructed | Nine-slot display-effect setup with floating-point steps |

`08049000` cuts the preceding `08048E24..080490E0` function. The following
function starts at `08049A6C` and extends beyond `08049C00`; this assignment
stops before it. Prologue/return, caller and literal-pool evidence establish
the listed boundaries. Command jump-table words belong to their function.

The canonical header retains word-sized argument slots and narrows values in
local variables where required. In particular, `49110` retains seven slots:
the final two are supplied by callers but unread. Its u32 formals and separate
u16 locals reproduce all 48 bytes. `492A8` has ten slots, including unread
slots 6/7 before offset 8/mode 9; a nine-slot candidate incorrectly read the stack.

The DMA control `80000008` selects eight **halfwords** (16 bytes), while each
palette index advances a 32-byte bank. The trailing volatile control-register
read is retained. Matrix records have a 16-byte stride; reset establishes 32
records at `03006D40`. The coefficient routine uses canonical sine alias
`gAffineSineTable_080AE8F4`, and the copied multiply helper `48B70` currently has
the provisional shared ABI `s32(s32,s32)`. ROM table bounds and gameplay names
remain unproven.

Reproducible source lessons from the exact matches:

- A separate signed for-index reproduces the compare loops at 49740/49768;
  decrementing the signed size directly had correct sizes but wrong comparisons.
- Initializing zero/scale locals before the matrix pointer restores 49318's
  initialization scheduling.
- Separate array-base and selected-object pointers restore 49420's address load
  between index shifts. This also agrees with the independently matching 48864.
- Mutating 497C0's incoming source/destination formals preserves the reference
  allocation; separate cursor locals did not.
- Explicit phase/address calculation for the cosine load retains 49374's
  add 64, shift and table-base addition. Each reciprocal result is narrowed s16
  before calling 48B70. These are matching access models, not proof of original
  declarations or local variable names.

The experiment directory is
`build/experiments/initialization/resume_graphics/`. Deliveries 1..7 retain strict
specs/results; `unresolved_evidence.json` contains every differing byte, hashes,
closest source snapshots and specs. Nonmatching definitions remain outside
production. `CHECKPOINT.md` also preserves the bounded twelve-hypothesis palette
investigation.
