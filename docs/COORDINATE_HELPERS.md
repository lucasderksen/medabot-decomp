# Coordinate and composite-object helpers

The assigned interval is `0x08042CA0..0x08043560`, comprising six routines and 2,240 bytes. The next entry at 43560 remains outside this assignment. Bounds follow observed caller targets, returns, literal pools and alignment.

| Entry | End | Bytes | Observed operation | Status |
| --- | --- | ---: | --- | --- |
| 08042CA0 | 08042D94 | 244 | Independently reduce the two sine-offset radii | Exact C |
| 08042D94 | 08042E58 | 196 | Decompress six selected OBJ graphic records | Exact C |
| 08042E58 | 0804305C | 516 | Initialize a four-object composite | Exact C |
| 0804305C | 08043240 | 484 | Update a four-object composite | Exact C |
| 08043240 | 080432A0 | 96 | Set four increments after hiding two objects | Exact C |
| 080432A0 | 08043560 | 704 | Animate positions and frame selectors | Exact C |

The first staged delivery has three routines and 536 exact bytes. It uses the normal agbcc game settings with `-fprologue-bugfix`; `build/experiments/initialization/coordinate_helpers/delivery_spec.json` and its strict results include every instruction, literal and padding byte.

The reduced-radius routine returns the same two-halfword `TileCoordinates` aggregate as `sub_08042BC0`. APCS passes its hidden return buffer in R0 and its six explicit arguments as angle, radius, x, y, y-radius reduction and x-radius reduction. Each reduction is clamped to the radius with unsigned comparisons. Products of signed sine-table entries and unsigned reduced radii scaled by 1/256 are converted to unsigned words; the result retains nine x bits and eight y bits. Its matching C establishes this interface without an extra structure-return compiler flag.

The graphics loader reads a six-column pointer table at `0x083B1A08`. Columns 0, 1/2, 3/4 and 5 select from its four input record indices respectively. Each payload is Le-decompressed to OBJ VRAM at `0x06010000 + graphicsSlot*1024`, with destination offsets 0, 128, 256, 384, 512 and 640. Expressing the six-column index as `(index<<2)+(index<<1)` preserves the reference's shifts and arithmetic order; multiplying by six produced different code.

The next independently defined table starts at 083B2578, bounding this root at
732 pointers: 122 rows of six. Every pointer has a distinct native Le stream.
Columns 0..4 decode to 128 bytes each; column 5 decodes to 384 bytes, exactly
filling the 1,024-byte slot. A 16x16, 4bpp tile preview confirms heads, two arm
views per side, and three leg frames. These streams and their symbolic root
are reconstructed in src/part_graphics_data.c with include/part_graphics.h.
The native 122-row storage bound does not add validation to the original loader.

The setter accesses the shared 64-byte `FrameObject` view at `0x03002C30`. It sets flag 0200 on the middle two records, executes the observed 16-iteration empty counting loop, and stores the supplied increment byte at offset 24 of all four consecutive records. That byte is currently addressed as `unknown23[1]` in the shared view. Its physical location is established; a gameplay interpretation and original field name are not.

The next staged delivery reconstructs the 516-byte initializer and 484-byte updater. Both address four consecutive `FrameObject` records with offsets `(0,-4)`, `(-8,+4)`, `(+8,+4)` and `(0,+4)`, and assign frame-group offsets 0500..0505, palette indices from the byte table at 083BEB94, selector zero and relative priorities. The flip argument controls flag 1000 and exchanges the middle frame/priority choices. The initializer clears all four 64-byte records through sub_08040CD0, explicitly resets each flags field, and sets scale 64/64 and angle zero on the middle records. The updater preserves existing flag bits before OR-ing C004 and the shifted flag-group argument. Both preserve the observed initial flags write followed by a flip-dependent flags write using ordinary nonvolatile C. Table bounds remain unproven.

All six routines now match their complete 2,240-byte assigned interval using ordinary C and `-fprologue-bugfix`. The complete staged source and strict spec are `build/experiments/initialization/coordinate_helpers/delivery_all.c` and `delivery_all_spec.json`. Earlier subgroup deliveries remain available as evidence.

The animator at 432A0 uses the fourth record as an anchor, advances progress bytes at offset 26 by increment bytes at 24, wraps at 64 and advances each command selector modulo four. Its two middle records follow different four-case quarter arcs through sub_08042BC0, with radius five, x displacement minus/plus five and y displacement minus three. The returned pair is read through a signed packed union view, reproducing the observed arithmetic upper-halfword shifts without changing the shared aggregate interface. Eight source calls account for eight distinct four-byte APCS return buffers. The fourth record's frame changes through the four-byte selector table at 083B2AEC; that same lookup chooses a one-pixel y adjustment for the other three records.

Two source forms are compiler sensitive: dividing the middle stored progress byte by two reproduces the actual post-store byte reloads, while an equivalent right shift forwards the prior store and produces different code. No volatile qualifiers are needed. Narrowing `0505 + selectorByte` to u16 before adding the shifted graphics group reproduces the first branch's arithmetic and register allocation. These are matching source models, not proof of the original spelling or intermediate declaration.

The canonical animator retains a third unused u32 formal parameter because exact callers explicitly load R2=0. Only R0 and R1 are consumed by the callee, which establishes used arguments but does not prove the original function had only two declared parameters. No table bounds beyond the four selector entries accessed by this routine are claimed.
