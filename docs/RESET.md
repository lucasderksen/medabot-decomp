# Software game reset

These functions reproduce the Metabee Europe revision 0 ROM intervals below
with ordinary C and the project-default `agbcc` flags. The reset routine returns
to its caller in the existing main loop; it does not invoke the BIOS `SoftReset`
service or branch to the cartridge entrypoint.

| Function | Interval, exclusive end | Bytes | Source |
| --- | --- | ---: | --- |
| `ResetGame` | `080008C0..08000964` | 164 | `src/reset.c` |
| `sub_08000964` | `08000964..0800099C` | 56 | `src/reset.c` |
| `Dma1AudioHandler` | `0800099C..080009A8` | 12 | `src/audio.c` |
| `Dma2AudioHandler` | `080009A8..080009B4` | 12 | `src/audio.c` |
| `Nullsub_080009B4` | `080009B4..080009B8` | 4 | `src/reset.c` |
| `Nullsub_080009B8` | `080009B8..080009BC` | 4 | `src/reset.c` |

Independent verification uses
`build/experiments/initialization/verify_irq_audio.py audio reset`.

| Function | Matching SHA-256 |
| --- | --- |
| `ResetGame` | `f518b664f97e0d4416e415f68a568e50bef6c20bb14cf505d2a8f495b688da9a` |
| `sub_08000964` | `e0fd5ef0c79b94c4b5475eee048b82632e6c25b5d223f4c9aa62ac7db37bb389` |
| `Dma1AudioHandler` | `ecf88e57e8964741b190ee8b249ad6adc4606756ddbeffeb4174cb329673aa4b` |
| `Dma2AudioHandler` | `77fab10bc83e560eb40c398a5c4b1b27bbeb689554c171186ef323c9d07956bd` |
| Either empty function | `6c1871acd4bd9950e81b2850fac7ddd44f28500d6bba63991c2599234ddbe61c` |

## Reset-button check

`sub_08000964` examines only the low byte of the held and newly pressed key
halfwords. It requires all four bits `000F` (A, B, Select, and Start) to be held,
and requires newly pressed Start bit `0008`. Extra held buttons do not prevent
the reset. Pressing A, B, or Select last while Start remains held does not satisfy
the newly pressed Start test.

When the check succeeds, it calls `ResetGame`, calls `ReadKeys`, and returns one.
Otherwise it returns zero. The explicit `u8` casts in the reconstruction preserve
the original byte-load instructions; testing the full `u16` variables produces
different loads with this compiler. The function is called by `GameMain` at
`080003B0`. Its eight-byte literal pool at `0800098C..08000994` is reached only by
PC-relative loads; control branches around it. Zero padding occurs at
`0800098A` and `0800099A`.

## Reset sequence

`ResetGame` first tests the signed byte at `03005030`. Its exact gameplay meaning
remains unknown. If it is nonzero, the routine stores `FFFF` in both halfwords
of `gMainSerialWork.unknown04`, the outgoing four-byte payload at `03005014`.
It then performs exactly eight iterations of `sub_080022DC(payload)` followed by
`VBlankIntrWait`. It clears the byte at `03005030` and calls `sub_080021A4`.
The matching source uses an unsigned first-halfword and signed second-halfword
view to preserve the original constant encodings (`FFFF` and signed `-1`);
both stores write the same sixteen one bits. These view types do not establish
the original payload field declarations.

The four-byte all-ones payload is consistent with the main loop's observed
received-payload reset marker. Its communication intent is an inference from
that check and this sending sequence; the serial API names remain address-based.

The routine then performs these operations regardless of the initial byte:

1. Wait for VBlank.
2. Write `00FF` to `BLDCNT` (`04000050`) and `0010` to `BLDY` (`04000054`),
   selecting maximum brightness decrease for all first-target layers.
3. Write zero to `SOUNDCNT_X` (`04000084`), disabling the sound hardware, then
   write zero to `IME` (`04000208`).
4. Call `ResetMemory`, then `InitInterrupts`, then serial initializer
   `sub_080020C8`.
5. Set `gMainState` at `0300178C` to three, clear words at `03002B8C` and
   `0300137C`, and disable DMA0 with a zero halfword store to `040000BA`.
6. Return to the calling reset-button check.

`ResetMemory` clears keypad state as part of its RAM fills, so the subsequent
`ReadKeys` reconstructs it from hardware. `GameMain` separately performs two
VBlank waits around `InitAudio` after the reset-button check returns one. This
division of work should be preserved rather than moving audio initialization
into `ResetGame`.

The routine's 44-byte literal pool occupies `08000938..08000964`, following a
zero alignment halfword at `08000936`. The active stack remains above the IWRAM
range that `ResetMemory` clears, as documented in `INITIALIZATION.md`.

## DMA audio and empty functions

The default fourteen-entry interrupt table at `0807E860` has Thumb pointers
`0800099D` and `080009A9` in slots five and six. The ARM dispatcher selects
those slots for DMA1 and DMA2, respectively. Thus the corresponding wrappers
are named `Dma1AudioHandler` and `Dma2AudioHandler`. They call `08074090` and
`080740D4`, then return. The underlying engine routines operate on distinct
regions of the context referenced at `03007014`, at offsets `690` and `6D8`,
with a shared guard halfword at `730`. Their full audio behavior is not yet
decompiled.

Neither wrapper writes `IF` itself; the dispatcher's acknowledgement precedes
the handler call. Each wrapper includes a final zero alignment halfword.
The functions at `080009B4` and `080009B8` are separately named empty functions,
each compiling to `bx lr` followed by a zero alignment halfword. Their purposes
are unknown.

Blend-register addresses were checked against
[libgba's video definitions](https://github.com/devkitPro/libgba/blob/master/include/gba_video.h),
and blend masks against
[libtonc's memory definitions](https://github.com/devkitPro/libtonc/blob/master/include/tonc_memdef.h).
