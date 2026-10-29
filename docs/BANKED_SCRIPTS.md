# Banked event storage

`src/unreferenced_banked_scripts.c` reconstructs 973 bytes at
`083D63DC..083D67A9` as 453 commands using the existing handler-derived operand
widths. All 160 pointers in the adjacent `083D67AC` directory select command
boundaries, and all eight targets of its one switch select boundaries. Three
bytes after the commands remain raw. No runtime reader for this directory is
known, and the three `30` jump operands are preserved without claiming their
runtime destinations. `tools/check_unreferenced_banked_scripts.py` verifies
the storage decode and boundaries; it does not execute the commands. The
command storage and symbolic root pointers both match under standard GCC data
flags.

`src/banked_script_data.c` reconstructs the event storage based at `08765EC0`.
The existing 2,288-entry offset/bank directories remain in
`src/banked_command_directory.c`. Their 2,139 distinct roots all coincide with
decoded command boundaries. Ninety-nine indices share the empty zero root at
`0876B990`; the other roots occupy banks 2 through 7 (`0876DEC0..08785EC0`).

The new sections contain 124,208 bytes: 94,589 script bytes, four header bytes,
16,380 reserved header bytes, 9,520 bytes at the shared empty root, and 3,715
trailing zero bytes across the six banks. Reserved storage and padding do not
represent additional game code or functions. Commands retain numeric names
where their complete meaning is unknown. The 32,230 emitted command records
include native end commands between shared roots; the decoder does not assume
that every directory root owns a separate terminated object.

## Reader and command structure

The native reader `0804D83C` obtains two window offsets from the header, finds
the selected script's offset and bank in the existing directories, and reads
`root + ((offset - 0x4000) & 0xFFFF) + (bank << 14) + position`. Its cursor is
an unsigned halfword and wraps after `FFFF`. The recovered 144-byte function
uses ROM bus arithmetic across the separate source objects and remains exact
with agbcc `-fprologue-bugfix`.

`tools/banked_scripts.py` records the operand widths of the 137 defined commands
from the matched handlers at `0804B73C..0804D83C`. Values `89..FF` have null
callback entries, rather than commands of unspecified length. `80` resets the
command work and immediately dispatches the next opcode; `81` appends an
eight-byte row and immediately dispatches the next opcode. A chain of these
commands is represented linearly, preserving recursive native dispatch.

Command `2F` (`0804C444`) uses the selected script's three-bit packed RAM state
to choose a byte displacement. It first adds that selector to the cursor,
reads one displacement, then sets the cursor to the position immediately after
the opcode plus the displacement. Stored table extents are inferred from the
earliest forward targets and checked against all decoded boundaries. This is a
storage inference, not a claim that the runtime clamps the selector to the
recovered table size. There are 542 tables and 1,502 stored entries.

One table deliberately overlaps a command: `0877A023` stores `04 0E 0D 02`.
Selector 3 branches to `0877A026`, where `0D 02` sets object 47's facing fields
to 2. Every other stored `2F` target is a regular decoded command boundary.
The source retains all four displacement bytes and identifies this alternate
entry instead of changing the table or inserting padding.

## Reproduction and verification

`python tools/reconstruct_banked_scripts.py` writes scratch source, a header,
an eight-section match spec and an audit under `build/more/`. It validates the
ROM, verifies all roots, checks complete storage re-encoding and dispatch
targets, and leaves production files unchanged. Compare with:

```
python tools/match.py build/more/banked_script_spec.json --output-dir build/more/banked_script_match
python tools/check_banked_scripts.py --all-commands --output build/more/banked_cpu.json
```

Both scratch and production sections match with the normal GCC data profile.
All four affected setup/reader functions also remain exact. Original Thumb
execution passes 9,152 directory reads (every index at positions 0, 1, 255 and
65535), operand-read checks for all 32,230 emitted commands, all 1,502 dispatch
entries, and the overlapping facing command's argument and object-field stores.

The CPU check executes the native reader, command handlers, argument helper
and indirect-call veneer. Calls outside that set return zero; `080532D4`
supplies the selected packed-state value. It checks read locations and dispatch
targets, not graphics, audio, interactive waits or complete scene behavior.
Five parser tests cover recursive command storage, inferred table bounds,
overlap, malformed input and halfword narrowing. The full-ROM checkpoint gate
is `build/more/checkpoint_banked_scripts.log`.
