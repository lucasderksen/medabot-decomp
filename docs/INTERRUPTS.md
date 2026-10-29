# Audio setup and display interrupts

This block is reconstructed from the supplied Metabee Europe revision 0 ROM.
Names are descriptive or address-based until stronger identification is available.
All functions below match their complete original intervals with the pinned
`agbcc` GCC `2.9-arm-000512` compiler and default project flags
`-O2 -mthumb-interwork -ffunction-sections`. These are ordinary C functions,
without inline assembly, fixed-register constraints, or machine-code arrays.

| Function | Interval, exclusive end | Bytes | Source |
| --- | --- | ---: | --- |
| `InitAudio` | `0800058C..080005D0` | 68 | `src/audio.c` |
| `VBlankHandler` | `080005D0..0800065C` | 140 | `src/interrupts.c` |
| `RunVBlankWork` | `0800065C..08000824` | 456 | `src/interrupts.c` |
| `HBlankHandler` | `08000824..08000840` | 28 | `src/interrupts.c` |
| `DummyInterruptHandler` | `08000840..08000844` | 4 | `src/interrupts.c` |

`build/experiments/initialization/verify_irq_audio.py` independently compiles,
links, and compares each interval. Matching slice SHA-256 values:

| Function | SHA-256 |
| --- | --- |
| `InitAudio` | `8a53f1e26f66e23f55cdb71a71bd9330552cba1cba3168490fa4d70a57e618fd` |
| `VBlankHandler` | `eb97f9490e2bd75f697635b204bc101ea754286c63afaf8b8cd132b9fc2c3e38` |
| `RunVBlankWork` | `dc822cca77188aca86f27e283260d9bf355c7715a020f08403745dd78046570e` |
| `HBlankHandler` | `d021e9d82075e3d092c11051630d569129363301c343ac32dc777d884620e7e1` |
| `DummyInterruptHandler` | `6c1871acd4bd9950e81b2850fac7ddd44f28500d6bba63991c2599234ddbe61c` |

## Audio initialization

`GameMain` passes context address `03002430` to `InitAudio`; its first call
forwards that context to `080723AC`. It then passes five ROM data addresses to
five engine routines, in order:

| Callee | Argument |
| --- | --- |
| `08074A78` | `080B012C` |
| `08074D3C` | `080B0860` |
| `08074FE8` | `080B18FC` |
| `08073C5C` | `080B16E4` |
| `08073C70` | `080B188C` |

Finally, it calls `08074B88` with zero. The engine interfaces and data formats
have not been identified, so the source preserves address-based callee and data
names. The arguments are pointers to copied ROM data; the data itself has not
been extracted or counted as decompiled code.

The 20-byte literal pool starts at `080005BC`. The halfword at `080005BA` is
zero alignment padding.

## VBlank wrapper

`VBlankHandler` tests bit zero of the volatile halfword at `03002B90`. A nested
entry with that bit set returns immediately. Otherwise it sets the bit, calls
`RunVBlankWork`, then clears the bit through the original `FFFE` halfword mask.
It next calls the serial routine `sub_080023D8` if bit `80` is present in
`gMainSerialWork.polledBits`.

It disables `IME`, increments the signed byte at `03002410`, and checks the
**updated signed value** against five. `GameMain` resets that byte after each
VBlank wait, so it records consecutive VBlanks not yet consumed by the main
loop. When it exceeds five and `gSerialState.sendReady` at `03005174` is nonzero,
it writes `FF` to `gMainSerialWork.disappeared` at `0300502E` and ORs the Serial
bit `0080` into the BIOS interrupt-check halfword at `03007FF8`. It then ORs
VBlank bit `0001` into that same halfword and reenables `IME`.

The BIOS check write is software bookkeeping for interrupt waits; setting its
Serial bit does not directly request a hardware serial interrupt. The counter's
increment and signed-byte truncation are preserved, including its byte wrap.
The wrapper's seven-word literal pool occupies `08000640..0800065C`.

## VBlank display and callback work

`RunVBlankWork` performs the following operations in order.

If bit zero of `gBgScrollFlags` at `03000434` is clear, it writes all eight
background scroll halfwords at `04000010..0400001E`. Each background's X/Y
offset pair is added to the common pair at `03002C2C`. Offsets for BG0 through
BG3 come from `03005000`, `03004C30`, `0300057C`, and `03001C04`, respectively.
The halfword stores preserve truncation of the sums.

The word `gRenderMode` at `03000430` selects the object-copy behavior:

- Mode zero optionally copies the full `03001380` OAM shadow to hardware OAM
  when the byte at `0300056E` (`gUnknown_03000440 + 12E`) is nonzero.
- Mode two calls `08047204`, then calls `08045A14` with addresses at offsets
  `B84` and `F8C` in the structure pointed to by `gRenderWork` (`03002414`).
  It copies 88 affine halfwords from that structure's objects 0–87 into shadow
  objects 0–87, and copies the 40 affine halfwords from shadow objects 88–127
  back into structure objects 0–39. If byte `03000571` (offset `131`) is zero,
  it copies those 40 complete structure objects to hardware OAM objects 88–127.
  It clears structure bytes `1094` and `1095`. When the byte at `0300056E` is
  nonzero, it also copies shadow objects 0–87 to hardware OAM.
- Any other nonzero mode is reset to zero; this branch performs no OAM copy.

The OAM copies use `CpuFastSet` in copy mode. Its sizes are word counts:

| Copy | Count | Bytes | Destination |
| --- | ---: | ---: | --- |
| Full shadow | `100` | `400` | `07000000..07000400` |
| First 88 shadow objects | `B0` | `2C0` | `07000000..070002C0` |
| Forty structure objects | `50` | `140` | `070002C0..07000400` |

The helper clears the byte at `0300056E` for every render mode, then calls the
callbacks at `03000B98` and `030017F0`. It resets the **first** callback to
`DummyInterruptHandler`; the second remains installed. Thus the first slot
has one-shot behavior in this helper and the second is persistent.

It writes `0001` to the BIOS check halfword at `03007FF8` (an assignment, not
an OR), acknowledges VBlank through `IF` at `04000202`, then calls engine
routines `08074070` and `08073274`. The audio calls follow the acknowledgement.
Their exact interfaces remain unidentified.

`RenderWork` names only the layout needed by these accesses: an OAM-shaped
array at `B84`, an unidentified region at `F8C`, and the two bytes at `1094` and
`1095`. It does not claim the whole structure is understood. Replacing these
field accesses with byte-pointer arithmetic produces different code with agbcc.

The helper contains a 72-byte internal literal pool at `08000760..080007AC`;
execution branches around it. A second 28-byte pool occupies
`08000808..08000824`. Zero halfword padding precedes both pools at `0800075E`
and `08000806`. All pools and branches participate in the exact byte comparison.

## HBlank and empty handler

`HBlankHandler` invokes the callback at `03002C20`, then acknowledges HBlank
through an `IF = 0002` halfword store. It does not update the BIOS interrupt
check word. Its two-word literal pool occupies `08000838..08000840`.

`DummyInterruptHandler` is an empty C function whose body compiles to `bx lr`,
followed by the original zero alignment halfword. Callback calls compile to
the historical `_call_via_r0` interworking routine at `0807CCF0`; the existing
ROM trampoline performs `bx r0` and supports both ARM and Thumb destinations.

The observed register meanings and IRQ masks are checked against
[libgba's video definitions](https://github.com/devkitPro/libgba/blob/master/include/gba_video.h)
and [interrupt definitions](https://github.com/devkitPro/libgba/blob/master/include/gba_interrupt.h).
The hardware definitions are reference checks, not copied implementation code.
