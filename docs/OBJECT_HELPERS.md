# Object and work-state helpers

The assigned interval is ROM `0x080415BC..0x08042678`. Address names and RAM
roles remain provisional. Twenty-nine routines, totaling 2248 bytes, currently match
ordinary C in `src/object_helpers.c`.

| Range (end exclusive) | Function | Bytes |
| --- | --- | ---: |
| 415BC..415E8 | sub_080415BC | 44 |
| 415E8..41624 | sub_080415E8 | 60 |
| 41624..41674 | sub_08041624 | 80 |
| 41674..4169C | sub_08041674 | 40 |
| 4169C..4172C | sub_0804169C | 144 |
| 4172C..4177C | sub_0804172C | 80 |
| 4177C..41818 | sub_0804177C | 156 |
| 41818..418C0 | sub_08041818 | 168 |
| 418C0..41920 | sub_080418C0 | 96 |
| 41920..419CC | sub_08041920 | 172 |
| 419CC..41A28 | sub_080419CC | 92 |
| 41BA4..41BF4 | sub_08041BA4 | 80 |
| 41BF4..41C14 | sub_08041BF4 | 32 |
| 41C14..41C5C | sub_08041C14 | 72 |
| 41C5C..41CA4 | sub_08041C5C | 72 |
| 41CA4..41CD4 | sub_08041CA4 | 48 |
| 41CD4..41D04 | sub_08041CD4 | 48 |
| 41D04..41D28 | sub_08041D04 | 36 |
| 41D28..41D3C | sub_08041D28 | 20 |
| 41D3C..41D70 | sub_08041D3C | 52 |
| 41FE4..42028 | sub_08041FE4 | 68 |
| 420C4..42114 | sub_080420C4 | 80 |
| 42114..4213C | sub_08042114 | 40 |
| 4213C..42170 | sub_0804213C | 52 |
| 42170..421A0 | sub_08042170 | 48 |
| 421A0..421B4 | sub_080421A0 | 20 |
| 42218..42238 | sub_08042218 | 32 |
| 4253C..425DC | sub_0804253C | 160 |
| 425DC..42678 | sub_080425DC | 156 |

`sub_080415BC` clears both halfwords in each of the four background-scroll
pairs, using the canonical `bg_scroll.h` view. The next two routines clear
eight bytes at `0x03000468`, then store byte arguments at offsets 2, 4 and 5.
The three-argument version puts 0x7F at offset 3; the four-argument version
puts its fourth argument there. This area overlaps offsets 0x28..0x2F of
the shared work base `0x03000440`. Its eight-byte alias records the clear
extent, without asserting a separate original object.

`sub_08041674` dispatches through pointers at `0x083B2994`, indexed by work
byte 0x29, and returns work byte 0x28 after the call. The two dispatchers at
41CA4 and 41CD4 clear work byte 4, call a pointer indexed by work byte 0x1B
from tables 083B29CC and 083B29E4, and return whether byte 4 exceeds seven.
The table declarations are incomplete arrays until their bounds are checked.
`sub_08041BF4` stores `(work[0x2A] << 4) + 1` into byte 0x28 and increments
byte 0x29, retaining byte truncation.

4169C decompresses three assets into VRAM at 06002600, 060026E0 and
06017E00. It loads tilemaps at grid positions (0,21) and (2,22), reading BG0
control separately for each call, then copies eight words into palette RAM
050003C0 and advances work byte 0x29. The asset aliases preserve their ROM
addresses; the artwork has not been identified here. 4172C clears two 8 by 6
tilemap rectangles, at work-byte coordinates 0x2C/0x2D and at (0,21), then
advances the same state byte.

The three tile-row routines use the same selected VRAM position:
`06002800 + work[0x2D]*64 + work[0x2C]*2`. Each row operation writes eight
halfwords and advances by a 64-byte row stride. 4177C clears two rows, copies
one row from 06002D40 and one from 06002E80, then clears two more rows. 41818
clears one row, copies two rows from 06002D40 and two from 06002E40, then
clears the last row. 418C0 copies six rows from 06002D40. Each routine advances
work byte 0x29. The pointer steps are explicit ordinary C: row offset first,
column pointer next, then their sum; source-row setup precedes the reset of
the destination cursor. This preserves the observed allocation and setup
order without volatile or assembly constraints.

41920 initializes the frame object selected by work byte 0x2B: flags D204,
frame/group 0307, palette 14, table selector zero, both scales one, and
priority FF. Screen coordinates derive from work bytes 0x2C, 0x2D and 0x2A.
It sets work byte 0x84 to one and advances 0x29. 419CC adds eight to both
scales with byte wraparound. Once scale X exceeds 63, it sets both to 64 and
advances 0x29. It clears work byte 0x84 on every call.

41BA4 selects a frame object with work byte 0x2B and subtracts eight from
each byte-sized scale, retaining wraparound and the observed repeated index
reads. If scale X becomes zero, it clears the object and advances work byte
0x29. It does not separately test scale Y.

41C14 and 41C5C write an object's screen X or Y. The operation is bits 2..3
of a byte argument: 1 writes the supplied halfword plus one, 3 writes it
minus one, and 0 or 2 writes it unchanged. They do not read the prior
coordinate. Halfword storage preserves wraparound. The final routine copies
an unsigned-byte count from the first pointer argument to the second,
advancing both pointers; zero count performs no accesses.

The record helpers reuse `InventoryRecord` from `state0_inventory.h`: 30
records of 64 bytes at `0x03000BE0`. 41D28 assigns the index 0..29 to each
record's first byte. 41D3C scans in order for bit 0x80 in byte 0 and a matching
identifier in byte 1, returning the first index plus one or zero if absent.
41FE4 finds the same first matching record, clears its 64 bytes, then restores
the prior first byte's low five bits. None of these scans asserts uniqueness.

420C4 tests four unsigned-byte thresholds in descending argument order.
It returns the highest numbered nonzero threshold that the value meets, or
zero. A zero threshold is ignored; the arguments need not be sorted.

42114 reads two bytes at `0x03004C40 + row*240 + index*2`, first byte most
significant. 4213C adds an unsigned-byte amount to the first byte there and
caps the result at 99; 42170 subtracts an unsigned-byte amount and clamps the
result to zero. The second byte is untouched by those updaters. The flat byte
alias preserves the observed address arithmetic without assuming table bounds.
421A0 writes indices 0..8 to byte 7 of the nine eight-byte records at
`0x030017A0`, using the canonical `State0Record8` view. 42218 scans those nine
records and returns one only when every first byte is nonzero.

4253C writes a byte mode at work offset 90, a supplied halfword increment at
92, and zero at 94. Modes 1/2 select blend-control effect 40, 3/4 select 80,
and 5/6 select C0. Odd modes initialize both blend coefficients and brightness
to 16; even modes initialize them to zero. Other modes select effect zero and
zero values. It masks coefficients to five bits, writes BLDALPHA and BLDY,
then writes the supplied control halfword ORed with the effect to BLDCNT.
The jump table is generated directly from the ordinary C switch.

425DC adds the halfword at work offset 92 into the halfword at 94, wrapping at
16 bits. For configured modes 1, 3 or 5, each coefficient becomes the low
halfword of `16 - (counter >> 4)`; modes 2, 4 or 6 use `counter >> 4`.
It masks these values to five bits, writes BLDALPHA and BLDY, and returns
whether the updated counter exceeds 255. It does not clamp the counter or
coefficient. The observed copied callers configure modes 5 or 6.

The step routine requires a configured mode 1..6. Its original default path
uses coefficient registers without assigning them; the C leaves those locals
uninitialized rather than inventing a zero result. This is undefined behavior
for invalid modes, recorded as a precondition rather than an inferred feature.
No volatile work view was needed: a separate initial `base`, explicit
`mode = base[0x90] - 1`, and then `work = base` reproduce the exact load and
register-copy order. Repeated counter reads across the switch remain ordinary
C accesses in the historical compiler.

The normal [historical compiler](COMPILER.md) uses `-fprologue-bugfix` for this
source. Without this supported upstream option, the two coordinate switches
save LR unnecessarily and emit 80 instead of 72 bytes. All eight other
routines are exact with the same flag. The later batch also remains exact with
that option. There are no instruction patches,
inline assembly, or fixed registers.

The isolated evidence is `build/experiments/compiler_input/object_helpers_candidate_fixed/results.json`.
Its spec initially points to the staged source; the production check uses
`object_helpers_production.json` in the same experiment directory:

```powershell
python tools/match.py build/experiments/compiler_input/object_helpers_production.json --output-dir build/experiments/compiler_input/object_helpers_production
```

Unverified portions remain in experiments and are excluded from production.


Staged additions; production source remains unchanged until root integrates.

Normal agbcc, `-fprologue-bugfix`, sections `.text.sub_0804206C`
at 0x4206C..0x420C4 (88 bytes) and `.text.sub_08042278` at
0x42278..0x422B8 (64 bytes). Reproduce:

`python tools/match.py build/experiments/compiler_input/object_helpers_next.json --output-dir build/experiments/compiler_input/object_helpers_next`

Proposed canonical declarations: `s32 sub_0804206C(void);`
and `u32 sub_08042278(u8 input);`, plus `void sub_0804242C(u8 count);`
for the copied descending sort. `ObjectSortEntry` has four halfwords at
offsets 0/2/4/6, with the first two compared by the sort. The summary clears
512 bytes at 0x02023000, fills the first halfword of 30 entries from
`InventoryRecord.byte5`, sorts descending, and computes signed
`(first - fourth) / 2 + fourth` with truncation toward zero. The independently
loaded halfword alias `gObjectFourthKey` overlaps entry 3 at 0x02023018;
the separate literal is present in the original instructions.

The lookup scans exactly 64 two-byte records at 0x03002BA0. It masks its
input to six bits, requires the first byte's bit 7, compares its lower seven
bits, and returns the second byte of the first match or zero. This does not
yet establish a gameplay interpretation or a larger table extent.
