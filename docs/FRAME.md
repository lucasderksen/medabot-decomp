# Frame helper reconstruction

The assigned block is ROM `0x08001520..0x080020C8`. Established function
boundaries are `1520..1CAC`, `1CAC..1EA8`, `1EA8..1FF8`, `1FF8..2060`, and
`2060..20C8`. The first routine traverses 128 objects with a 64-byte stride at
`0x03002C30`; full reconstruction is in progress. Names remain descriptive or
address-based rather than recovered original symbols.

Four helpers are matching ordinary C in `src/frame.c`, using default pinned
agbcc settings. Together they cover **1,052 bytes** at `1CAC..20C8`, including
original alignment and literal bytes:

| Routine | Interval | Bytes |
| --- | --- | ---: |
| `sub_08001CAC` | `1CAC..1EA8` | 508 |
| `sub_08001EA8` | `1EA8..1FF8` | 336 |
| `sub_08001FF8` | `1FF8..2060` | 104 |
| `sub_08002060` | `2060..20C8` | 104 |

Isolated verification records are `frame-affine/results.json`,
`frame-scale/results.json`, and `frame-small/results.json` under
`build/experiments/compiler_input`.

The affine helpers write four halfwords into the `affine` field of four
successive OAM shadow entries, beginning at `affineIndex*4`. The scale helper
uses diagonal values of `+/-16384/scaleX` and `+/-16384/scaleY`, with zero
off-diagonal values. Flag bits `0x1000` and `0x2000` select the respective
signs. When the signed word at `0x03005048` differs from -1, it replaces both
denominators and the numerator magnitude becomes 4194304.

The trig helper reads cosine and sine samples with the same ten-bit index as
the coordinate helper. In the -1 override state, zero X/Y scales are replaced
with one. It computes cosine/X, sine/Y, negative sine/X, and cosine/Y, with
the two flag bits changing signs and store order. Other override states use
samples multiplied by 256 and the override as a common denominator. Calls
use the BIOS `DivArm` wrapper at `0x0807CCCC`, whose argument order is
denominator first, numerator second. This differs from the ordinary C division
calls in the scale helper, which use `__divsi3` at `0x0807CD2C`.

The coordinate helper reads a halfword at object offset `18`, masks its index
to ten bits, and reads signed samples from `gSineTable` at `0x08075250`.
The cosine sample is taken 256 entries after the sine sample. It updates two
signed words using `(x*cosine - y*sine)/16384` and
`(x*sine + y*cosine)/16384`, with C signed division truncating toward zero.
It snapshots both original coordinates before either store. The products and
sums use the original 32-bit arithmetic; inputs large enough to overflow are
not given an invented mathematical interpretation.

The order helper operates on four-byte entries. Byte `00` is an object index;
byte `01` is the compared priority; the remaining halfword has no established
role. It repeatedly shrinks the comparison gap to `floor(gap*5/8)`, clamps a
zero gap to one, and swaps when the earlier priority is lower. It continues
until a gap-one pass has no swaps. Only the first halfword moves; each entry's
trailing halfword stays at its original array position. Equal-priority swaps
are skipped at the comparison itself, but no stable-sort property is claimed.

An ordinary C union represents the four-byte entry and its first-halfword
view. Label-based loops and integer-address arithmetic preserve the original
branch layout and operand order. There is no inline assembly, fixed-register
declaration, or emitted-byte patch.

Isolated execution of the original routines through `tools/cpu.py` checked
64 deterministic order cases with counts from zero to 128, verifying descending
priorities, preservation of index/priority pairs, and unchanged trailing
halfwords. Another 128 coordinate cases agreed with signed division of the
actual ROM table samples. Run the optional check with
`python tools/check_frame_helpers.py`; it requires the optional Unicorn
dependency installed through `python tools/bootstrap.py --emulation`.
This is bounded CPU execution, not a full GBA hardware simulation.

`include/frame.h` contains the provisional 64-byte `FrameObject` layout.
The byte at offset `2B` is independently used by packed-index helpers; its
gameplay role is not established. The header will be extended as the larger
frame and affine routines establish more field offsets.
