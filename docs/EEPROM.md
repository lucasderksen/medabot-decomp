# EEPROM library

The ten functions at `0807C8B0..0807CCC0` are reconstructed as ordinary C in
`src/eeprom.c`, with types and declarations in `include/eeprom.h`. Every byte
of this 1,040-byte interval matches the supplied Metabee Europe revision 0 ROM,
including literal pools and zero alignment. The functions are inferred library
roles; the ROM does not provide a symbol table establishing their original SDK
names. `Unknown_0807C8B0` retains its existing ABI name for integration.

| Function | Interval, exclusive end | Bytes |
| --- | --- | ---: |
| `Unknown_0807C8B0` | `0807C8B0..0807C8F4` | 68 |
| `EepromTimerIntr` | `0807C8F4..0807C918` | 36 |
| `SetEepromTimerIntr` | `0807C918..0807C950` | 56 |
| `StartEepromTimer` | `0807C950..0807C9D8` | 136 |
| `StopEepromTimer` | `0807C9D8..0807CA1C` | 68 |
| `EepromDma3Transmit` | `0807CA1C..0807CA9C` | 128 |
| `ReadEepromDword` | `0807CA9C..0807CB4C` | 176 |
| `ProgramEepromDword` | `0807CB4C..0807CC28` | 220 |
| `VerifyEepromDword` | `0807CC28..0807CC80` | 88 |
| `ProgramEepromDwordEx` | `0807CC80..0807CCC0` | 64 |

## Compiler and matching evidence

Use the project historical compiler, `agbcc 2.9-arm-000512`, with additional
flags `-O1 -fprologue-bugfix`. The final `-O1` overrides the project's default
`-O2`. `StartEepromTimer` and `EepromDma3Transmit` distinguish these optimization
levels: the reconstructed expressions match at `-O1`, while `-O2` changes
register allocation, loop structure, and literal placement. The leaf-function
flag removes the extra LR save/restore in the branched selector, timer handler,
and timer-installation routine.

The following independent specifications apply strict section-size assertions
and compare each linked interval with `baserom.gba`:

```powershell
python tools/match.py build/experiments/initialization/eeprom_spec.json --output-dir build/experiments/initialization/eeprom_strict
python tools/match.py build/experiments/initialization/eeprom_data_spec.json --output-dir build/experiments/initialization/eeprom_data_strict
```

The first verifies all ten functions and the compiler-generated pointer pool.
The second verifies all four declared data records. All fifteen intervals pass.
Per-interval reference and emitted SHA-256 values are recorded in each output
directory's `results.json`. The earlier diagnostic verifier,
`build/experiments/initialization/verify_eeprom.py -O1 -fprologue-bugfix`, preserves
an independent linker and disassembly for inspection.

These checks establish an exact ROM reconstruction, including the observed
hardware access order. They do not substitute for an emulator or cartridge test
of EEPROM reads, writes, or timeout behavior.

## Device configuration and version data

`src/eeprom_data.c` supplies the following typed data. The `EEPROM_V122` marker
identifies the library version present in this ROM; it does not alone establish
all original symbol names.

| Record | Interval, exclusive end | Meaning |
| --- | --- | --- |
| `gEepromLibraryVersion` | `083ABE14..083ABE20` | `EEPROM_V122` and terminating zero |
| `gEepromConfig4K` | `083ABE20..083ABE2C` | 512 bytes, 64 eight-byte blocks, WAITCNT bits `0300`, six address bits |
| `gEepromConfig64K` | `083ABE2C..083ABE38` | 8,192 bytes, 1,024 eight-byte blocks, WAITCNT bits `0300`, fourteen address bits |
| `gEepromTimeoutParams` | `083ABE38..083ABE40` | `000A`, `FFBD`, `00C2`, then zero alignment |

The twelve-byte configuration layout is `u32 sizeBytes`, `u16 blockCount`,
`u16 waitcnt`, `u8 addressBits`, and three zero padding bytes. The 8-KiB device
uses fourteen transmitted address bits despite needing only ten bits to index
its 1,024 doublewords. The block-range check prevents out-of-range requests.

The selector accepts device sizes in kilobits: four selects the 512-byte record,
64 selects the 8-KiB record, and any other value selects the smaller record and
returns one. Valid sizes return zero. `InitInterrupts` calls it with `0040` at
`08000498`, so this game initializes the 8-KiB configuration.

There is also an 88-byte pool at `083ABE40..083ABE98`. It is the `.rodata`
section generated naturally by `agbcc -O1` from the function bodies: twenty-two
four-byte addresses, including repeated addresses of shared RAM variables and
configuration records. It matches the ROM exactly after relocation. No manual
pointer table is necessary. Integrate this interval from `src/eeprom.c` with
`input_section: ".rodata"` and `category: "data"`; omitting it leaves unexpected
allocated data in the strict whole-ROM build. The reconstructed marker,
configuration records, timer parameters, and this pool cover 132 data bytes.

## Shared state and Timer 2 installation

| Symbol | Address | Type and role |
| --- | --- | --- |
| `gEepromTimerNumber` | `030003F4` | Byte selecting timer 0 through 3 |
| `gEepromCountdown` | `030003F6` | Halfword counting timer interrupts |
| `gEepromTimedOut` | `030003F8` | Byte set when the countdown reaches zero |
| `gEepromTimerRegs` | `030003FC` | Pointer to volatile timer data/control halfwords |
| `gEepromSavedIme` | `03000400` | Saved interrupt master-enable halfword |
| `gEepromConfig` | `03007018` | Pointer to selected configuration record |

`SetEepromTimerIntr` rejects timer numbers above three with result one. On
success, it records the timer number, computes `04000100 + 4 * timerNumber`,
stores the Thumb function pointer for `EepromTimerIntr` through its output
argument, and returns zero. Game wrapper `0805DEB0..0805DEC8` calls this routine
with timer number two and output pointer `03000BCC`. This is entry eleven of
the game's custom interrupt table at `03000BA0`; the ARM dispatcher selects
entry eleven for the Timer 2 IRQ mask `0020`. The default table ordering differs
from hardware interrupt-bit order and must be interpreted through the dispatcher.

`EepromTimerIntr` leaves a zero countdown alone. Otherwise it reloads the
halfword, subtracts one, writes it back, and tests the narrowed result before
setting the timeout byte. The matching RAM declarations are ordinary globals.
Adding `volatile` to the countdown changes the original `lsls #16` zero test
into a fresh halfword load. The matching compiler still emits the observed
loads of the timeout flag on every polling-loop iteration at `-O1`.

`StartEepromTimer` preserves this sequence:

1. Save `IME`, then disable interrupt dispatch with `IME = 0`.
2. Clear the selected timer's control halfword.
3. Acknowledge its pending IRQ through `IF`, then enable its bit in `IE`.
4. Clear the timeout byte and load the countdown from parameter zero.
5. Write parameter one to the timer reload halfword and parameter two to its
   control halfword, updating the shared register pointer to the control
   halfword and back to the reload halfword.
6. Set `IME = 1`.

The write parameters are ten interrupts, reload `FFBD`, and control `00C2`.
The control value enables the timer and its interrupt; the register addresses
and enable/IRQ bit meanings agree with
[libgba's timer definitions](https://github.com/devkitPro/libgba/blob/master/include/gba_timers.h).
`StopEepromTimer` disables IME, writes zero to both timer halfwords while making
the same intermediate shared-pointer updates, clears its bit in `IE`, and
restores the saved IME. Thus a write deliberately enables interrupts while
waiting, even if its caller originally had IME disabled, and restores the
original state after stopping the timer.

## DMA and serial command construction

`EepromDma3Transmit` saves and disables IME. It replaces WAITCNT bits `0700`
with the selected record's `waitcnt`, writes DMA3 source, destination, and
`80000000 | halfwordCount`, and polls DMA3's enable bit until the immediate
16-bit transfer completes. Source and destination increment. It then restores
IME. The altered WAITCNT bits are retained; the old WAITCNT is not restored.

Both command builders send one serial bit per halfword through `0D000000`.
They store complete shifted values in the command buffer; the port consumes
the low bit. A block argument identifies one eight-byte EEPROM doubleword,
whose host representation is four halfwords.

`ReadEepromDword` uses a 68-halfword stack buffer. It checks the block against
`blockCount`, serializes the address backward, adds command bits `1,1`, and
transmits `addressBits + 3` halfwords. No store initializes the final transmitted
halfword at `buffer[addressBits + 2]`; that behavior is preserved. It then reads
68 halfwords, skips the first four, and assembles four sixteen-bit values from
the remaining low bits. The first assembled value is stored at destination
index three, then subsequent values at indices two, one, and zero. A successful
read returns zero; an out-of-range block returns `80FF`.

`ProgramEepromDword` uses an 82-halfword stack buffer. It emits a zero stop bit,
serializes four source halfwords backward, serializes the address backward,
and writes command bits `1,0`. The transfer has `addressBits + 67` halfwords.
It starts the timer and polls the port's low bit for completion. If the timeout
byte becomes nonzero, it checks the port again before returning `C001`, so a
completion detected on this final read still succeeds. It always stops the
timer after polling. An out-of-range block returns `80FF` before starting DMA.

`VerifyEepromDword` range-checks the block, calls the read routine into a
four-halfword local buffer, and compares all four source halfwords in order.
It returns zero for equality or `8000` for the first mismatch. The original
discards the inner read's return value after performing its own range check.
`ProgramEepromDwordEx` tries program followed by verification up to three times,
stopping on the first success and otherwise returning the final failure code.

Confirmed game calls into these functions include reads at `0805E154` and
`0805E294`, and program-with-verification calls at `0805E280`, `0805E2C0`, and
`0806055A`. These establish integration with the game-specific save layer;
that layer's full data layout is still a separate reconstruction task.
