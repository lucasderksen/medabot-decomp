# Main-loop reconstruction

`GameMain` at ROM `0x0800025C..0x08000458` is matching ordinary C in
`src/main.c`, compiled with the same pinned agbcc settings as the keypad
routine. All **508 bytes**, including the three literal islands and alignment
padding, match the local reference dump in an isolated link. The record is
`build/experiments/compiler_input/main-match.log`; linked disassembly is
`main.disasm` beside it. `GameMain` is a descriptive name, not a recovered
original symbol.

## Observed behavior

The entry configures `WAITCNT` to `0x4014`, calls memory and interrupt
initialization, writes `0x60` to `DISPCNT`, and selects callback index 3. It
clears two unknown word fields, calls `sub_080020C8`, initializes the sound
subsystem through the provisionally named `InitAudio`, and clears several
unknown byte/halfword fields.

The routine then loops forever. Each iteration waits for VBlank, clears a byte
at `0x03002410`, reads keys, and increments the word at `0x03001780`. A nonzero
byte at `0x03000588` enables incrementing the word at `0x03002B88`, provided its
current unsigned value is at most `0x014996FE`. The latter condition permits
the counter to reach `0x014996FF` and then stops incrementing it.

The loop snapshots the byte at `0x03005172`, clears two per-frame flag bytes,
and passes the receive-payload area beginning at `0x03005018` to `sub_080021F4`.
It stores the returned word at `0x03005010`, then checks its lowest four bits.
For each set bit, it resets the corresponding missing-poll count. If the bit
was absent from the snapshot, it sets that bit in `0x03005172` and ORs `0xFF`
into the appeared flag. For each clear bit, it increments the missing count
unless its signed-byte interpretation already exceeds 10. On that condition,
it marks disappearance if the remembered bit was set, clears the remembered
bit, and resets the count. These are connection-like observations; the exact
meaning of each bit remains under investigation.

If `sub_08000964` returns nonzero, the loop waits for VBlank, calls `InitAudio`
with `0x03002430` still in its argument position, and waits again. If it returns
zero and the signed byte at `0x03005030` is nonzero, it chooses one of two pairs
of halfwords using the byte at `0x03000B90`. A zero selector chooses pair 1;
a nonzero selector chooses pair 0. If both selected halfwords are `0xFFFF`,
the routine selects callback state 0 and writes 10 and 16 to the two unknown
word fields previously cleared at startup.

Finally, it invokes `gMainCallbacks[gMainState]`, calls `sub_08001520`, calls
`sub_080022DC` with `0x03005014`, and begins the next frame. The callback table
has six entries at `0x083ABF98..0x083ABFB0`; the table and its boundary are
reconstructed separately in `src/main_callbacks.c`.

## Verified memory layout

The main-loop view of the object at `0x03005010` is:

| Offset | Width | Observation |
| --- | --- | --- |
| `00` | u32 | Result of `sub_080021F4`; lowest four bits inspected |
| `04` | 4 bytes | Address passed to `sub_080022DC`; type not established |
| `08` | eight u16 | Four received payload pairs; main checks the first two for `0xFFFF` |
| `18` | u8 | Unaccessed by this routine |
| `19` | four u8 | Missing-poll counters; comparison explicitly casts to s8 |
| `1D` | u8 | Appeared flag, cleared each frame and ORed with `0xFF` |
| `1E` | u8 | Disappeared flag, cleared each frame and ORed with `0xFF` |

The canonical `MainSerialWork` and `SerialContext` structs are in
`include/serial.h`. Serial receive code establishes that the payload area has
four four-byte slots, although main only checks the first two. The main-loop
remembered-bit byte is `gSerialState.rememberedBits` at `0x03005172`.
The larger context layout and its remaining provisional names are documented
in `docs/SERIAL.md`.

## Compiler and linkage details

The matching source uses signed `s32` for the snapshot and loop index, matching
the original arithmetic right-shift and signed loop branch. Missing-poll
counters remain `u8` storage with an explicit `s8` comparison, reproducing the
original byte loads and sign extension. The result of `sub_08000964` is kept
as an integer; its other meanings are unknown.

`gMainSerialWork` must be a linker-resolved symbol at `0x03005010`. Defining
the object as a constant-address macro allowed the compiler to substitute
separate `0x03005018` and `0x0300501A` literals, which changed the original
addressing. A symbolic struct base reproduces the base-plus-offset operations
directly. No per-file register-allocation or scheduling flags are required.

Copied Thumb callees need Thumb function metadata, rather than untyped
absolute linker-script symbols. The agbcc indirect-call helper is
`_call_via_r0` at `0x0807CCF0`; it is the existing register trampoline also
described by the provisional `CallViaR0` name in assembly.

Function prototypes for still-copied callees express the arguments and return
values used here, rather than claiming original source interfaces. In
particular, the meaning of the initial `0x03002430` argument to `InitAudio`
requires further callee tracing. Matching the caller proves its register value
and instruction sequence, not the argument's semantic type.

Proposed manifest change: use `src/main.c`, compiler `agbcc`, input section
`.text.GameMain`, with the same `0x00025C..0x000458` interval. Add RAM symbol
`gMainSerialWork = 0x03005010` and the typed Thumb helper `_call_via_r0` if it
has not yet been extracted into source.
