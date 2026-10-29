# Historical compiler investigation

The keypad routine provides concrete evidence for the GCC 2.9 ARM/Thumb
compiler family. Its ordinary C reconstruction in `src/input.c` produces every
instruction, register choice, literal-pool placement, and literal byte in ROM
`0x08000844..0x080008C0` using the normal
[pret/agbcc](https://github.com/pret/agbcc) compiler at commit
`da598c1d918402c42c0c0d7128ba14567f3175e9`. Upstream's `gcc/version.c`
reports `2.9-arm-000512`. This identifies a working compiler family and settings;
it does **not** establish the exact executable shipped to the original game's
developers. No compiler version string has yet been recovered from the ROM.

## Reproducible local tool

Run:

```powershell
python tools/compiler_agbcc.py bootstrap
```

The script fetches the pinned commit from the original upstream, builds only its
normal Thumb compiler, and saves `tools/downloads/agbcc/agbcc.exe` on Windows
(`agbcc` on other hosts). The source checkout and executable remain ignored
build dependencies. It records commit, compiler version, host compiler,
executable hash, and source-patch list in the ignored `provenance.json` beside
the executable. No upstream source changes are required.

The tested Windows host is MinGW GCC 15.2.0, GNU Make, and Git Bash. In this
workspace, GCC is `C:/ProgramData/mingw64/mingw64/bin/gcc.exe`. Git Bash changes
PATH ordering at startup; its own DLL directory can make the MinGW compiler's
`cc1` silently fail. The bootstrap puts the host GCC directory first **inside**
Git Bash before running Make. It uses `-j1`, as upstream does: a parallel make
can compile sources before the generated `genrtl.h` exists. These are host-build
workarounds and do not change the target compiler.

Optional `AGBCC_HOST_CC`, `AGBCC_MAKE`, and `AGBCC_BASH` environment variables
select host executables for that command. They do not change global settings.
The ARM-target compiler, C preprocessor, assembler, and linker remain the pinned
Arm GNU Toolchain already used by the project.

## Compilation settings

The adapter can be invoked directly:

```powershell
python tools/compiler_agbcc.py compile src/input.c build/experiments/compiler_input/input.o
```

It runs the equivalent of:

```text
arm-none-eabi-gcc -E -P -x c -std=gnu89 -nostdinc -undef -Iinclude src/input.c -o input.i
agbcc -O2 -mthumb-interwork -ffunction-sections -Werror input.i -o input.s
arm-none-eabi-as -mcpu=arm7tdmi input.s -o input.o
```

The C preprocessor reads the project's own headers. `-undef` removes modern
compiler feature macros, and `-nostdinc` prevents inclusion of modern runtime
headers incompatible with the older compiler. Ordinary C is passed to agbcc;
there is no inline assembly in the keypad source.

One assembler compatibility step is necessary. Modern GNU as pads executable
Thumb sections with `0x46C0` NOPs. The reference's final two bytes at
`0x080008BE` are zero. The adapter appends `.align 2, 0` to each executable
section, explicitly requesting historical zero-fill alignment. This is the
same convention used by the
[pret/pokeemerald Makefile](https://github.com/pret/pokeemerald/blob/master/Makefile)
for agbcc output; function sections need that alignment applied to every
executable section. GNU as `-no-pad-sections` was tested and does not remove
this ARM-specific padding. The adapter changes no generated instructions,
constants, or relocations, and does not patch object files or ROM bytes.

## Keypad verification

`ReadKeys` is 122 bytes of compiler-generated code and literal pools plus two
bytes of alignment padding. Linking `.text.ReadKeys` at `0x08000844` with the
existing RAM symbols reproduces all 124 bytes of the original interval. The
first straightforward source candidate matched all code and literal bytes;
only the assembler padding compatibility step was needed. The isolated
comparison is recorded locally in
`build/experiments/compiler_input/keypad-match.log`.

Proposed manifest entry:

```json
{
  "name": "input",
  "start": "0x000844",
  "end": "0x0008C0",
  "kind": "c",
  "compiler": "agbcc",
  "source": "src/input.c",
  "input_section": ".text.ReadKeys",
  "description": "Matching C: keypad edges and shared repeat countdown"
}
```

The two original tiny C matches used modern GCC and unusual per-file flags.
Their existence alone was weak evidence of compiler provenance. The keypad
match spans control flow, a mid-function literal island, several register
lifetimes, hardware reads, and global stores, making it a substantially stronger
compiler-family fingerprint. The subsequent 508-byte `GameMain` and 1,132-byte
serial block also match ordinary C with this compiler family; their detailed
records are in `docs/MAIN.md` and `docs/SERIAL.md`.

## Leaf-function prologue setting

The serial source uses the upstream-supported `-fprologue-bugfix` option.
Upstream `gcc/toplev.c` describes this option as correcting unnecessary LR
saves in leaf functions and notes that some GBA games need it for matching.
Without the option, the branched leaf functions at `0x08002190` and
`0x080023D8` emit additional LR save/restore instructions. With it, their
20-byte and 96-byte original intervals match exactly. The same option is used
for every segment built from `src/serial.c`, because the build compiles a source
file once. It does not alter the already matching nonleaf serial routines.

The supported upstream `old_agbcc` variant was initially built from the same
pinned commit in an ignored experiment, with no source modifications. It
identifies itself with the same version string and does not expose
`-fprologue-bugfix`. For the tested serial send-register expression, it produced
the same extra register copy as normal agbcc's ordinary halfword-pointer form;
it did not improve that game-code match.

The old variant is now installed reproducibly through
`tools/compiler_libgcc.py` for the recovered runtime C under `src/libgcc`.
Runtime sources use `-O2` without the game code's interworking option; the
default game compiler remains normal agbcc. Independent upstream runtime
matches and their required RAM-backed state declarations are documented in
[RUNTIME.md](RUNTIME.md). This is further compiler-family evidence, while
leaving the exact original vendor executable unidentified.

## Return-address temporary under interworking

The pinned normal compiler's `gcc/thumb.c`, function `thumb_exit` at lines
556..625, selects the register into which it pops a stacked return address
from the return RTL/declaration mode. With interworking enabled, a void
result uses argument register 0; a scalar result up to four bytes uses
argument register 1. A memory-returned structure can also use register 1.
Therefore `pop {r1}; bx r1` supports a different return mode from ordinary
void, but cannot identify signedness, an omitted return, or the meaning of
the result on its own. Callers and complete matching remain necessary.

The resumed `0804842C..08048684` dispatcher illustrates the limit: the void
candidate emits 540 of the reference's 600 bytes; a word-returning variant
without a return statement emits 564 bytes and reproduces the epilogue but
still fails. Both remain isolated.

## Explicit interfaces in frozen candidates

A local staging extractor searched for the first substring `void sub_` and
mistook an extern declaration for the first function definition. Its prefix
cut then dropped copied-callee prototypes from three frozen action deliveries.
Those calls happened to use word slots and reproduced the bytes through implicit
int declarations, but this was an unintended source model. The corrected
extractor identifies actual definition lines, retains the complete declaration
prefix, and independently reproduces nine functions / 708 bytes in
`initialization/continued_4c02c/delivery_second_explicit_strict`,
`delivery_third_explicit_strict` and `delivery_fourth_explicit_strict`.

Root integrated the corrected prefixes and checked complete ROM equality.
At that stage, copied `0804DBF0` had provisional local word interfaces. Its
later exact definition in `src/continued_command_helpers.c` establishes an
unsigned slot-byte load minus one as a full signed-word result, including -1.
The canonical `s32(u32)` declaration uses explicit byte narrowing in the callee;
older private declarations were removed across production callers. The
twenty-fifth full-ROM check passes every caller with the consolidated interface.
Matching access behavior still does not identify original formal widths.
No production compiler setting changed.
