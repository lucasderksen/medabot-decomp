# Medabots - Metabee decompilation

[![Progress](https://github.com/lucasderksen/medabot-decomp/actions/workflows/progress.yml/badge.svg)](https://github.com/lucasderksen/medabot-decomp/actions/workflows/progress.yml)
[![Code](https://bytematch.dev/lucasderksen/medabot-decomp.svg?label=Code&measure=matched_code_percent)](https://bytematch.dev/lucasderksen/medabot-decomp)
[![Data](https://bytematch.dev/lucasderksen/medabot-decomp.svg?label=Data&measure=matched_data_percent)](https://bytematch.dev/lucasderksen/medabot-decomp)
[![Functions](https://bytematch.dev/lucasderksen/medabot-decomp.svg?label=Functions&measure=matched_functions)](https://bytematch.dev/lucasderksen/medabot-decomp)

A matching decompilation of **Medabots - Metabee (Europe)** for the Game Boy
Advance. The source rebuilds the original cartridge image byte for byte. The
approach follows [pret/pokefirered](https://github.com/pret/pokefirered): keep
the exact ROM layout, replace each interval with C (or assembly where C cannot
produce it), and compare every rebuild against the original dump.

![Progress history](../progress/progress.svg)

## Status

- **3,526 of 3,540 functions** match as C or assembly (98.1% of the code bytes).
  The 14 functions left, 9,148 bytes, are still copied from the ROM; their
  closest drafts and blockers are in [docs/drafts/README.md](docs/drafts/README.md).
- **All data is source.** Every byte after the code is a typed C array. Tables
  with a known layout have named types and symbols; bytes whose consumer is
  not identified yet are labelled `gUnknown_<address>` arrays.
- Code is compiled with [agbcc](https://github.com/pret/agbcc) (GCC 2.9 for
  Thumb) using the standard `-O2 -mthumb-interwork` settings; per-function flag
  profiles are recorded in `config/segments.json`.
- Most functions still have address names (`sub_08xxxxxx`). Naming is the
  next phase.
- Three functions use a marked *fake match* (a register pin) and five fall off
  the end like the reference. `grep -rn "FAKE MATCH" src` lists the former.

Progress is measured from `config/segments.json` on every push to `main` by
[.github/workflows/progress.yml](.github/workflows/progress.yml). The workflow
keeps a history chart on the `progress` branch and uploads an objdiff-format
report (`A8BP_report`) for [bytematch.dev](https://bytematch.dev).
`python tools/progress_report.py` and `python tools/objdiff_report.py` print the
same numbers locally.

## Reference ROM

| Property | Value |
| --- | --- |
| Version | Medabots - Metabee, Europe, revision 0 |
| Header title | `MEDABOTSMTBV` |
| Game code | `A8BP` |
| Size | 8,388,608 bytes (8 MiB) |
| SHA-1 | `cd3d674e88f40a0707b150c4293588a659001d29` |
| SHA-256 | `4c64595190db3b4f50062d90a446fcab590f4e31c01830384558deca0691a26d` |

The build needs your own dump of this cartridge: the 14 unmatched functions and
the Nintendo logo in the header are still read from it. Put the `.gba` file in
the project root; the first build finds it, checks its hash and copies it to
`baserom.gba`. A different version or a modified dump is rejected. ROMs, build
products and downloaded tools are never committed.

## Building

Requirements: Python 3.11 or newer and Git. On Windows the historical compiler
also uses Git Bash and a MinGW GCC to build itself. From the project root:

```powershell
python tools/bootstrap.py --analysis
python tools/compiler_agbcc.py bootstrap
python tools/compiler_libgcc.py bootstrap
python tools/build.py
```

The first command downloads the pinned
[Arm GNU Toolchain 14.3.Rel1](https://learn.arm.com/install-guides/gcc/arm-gnu/)
into `tools/toolchain/` (and Capstone for analysis); it does not change the
system PATH. The second builds the pinned agbcc from source under
`tools/downloads/agbcc/`; the third builds its `old_agbcc` variant for the GNU
runtime in `src/libgcc/`. `make setup`, `make`, `make test` and `make clean`
wrap the same commands.

A successful build ends with `MATCH: all 8,388,608 bytes are identical.` and
writes `build/medabots.gba`, `.elf`, `.map` and a disassembly. Any difference
fails the build and reports the interval and the first differing bytes. To use
a dump outside the project root, pass `--rom <path>`.

On Linux and macOS, install an `arm-none-eabi` toolchain yourself and put it on
PATH or set `ARM_TOOLCHAIN` to its `bin` directory. The bootstrap scripts
currently support Windows x64 only.

## Repository layout

| Path | Contents |
| --- | --- |
| `src/` | Game, runtime (`libgcc/`, `libc/`) and data sources |
| `asm/` | Header, startup, BIOS wrappers, call trampolines and libgcc assembly |
| `include/` | Shared declarations, struct layouts and RAM/IO definitions |
| `config/` | `segments.json` (every ROM interval, its source and flags), `symbols.json`, ROM description |
| `data/` | Data includes for the C sources: audio samples, compressed graphics streams and frames |
| `tools/` | Build, matching, analysis and progress tools |
| `tests/` | Unit tests for the tools (`python -m unittest discover -s tests`) |
| `docs/` | Compiler idioms, formats, struct and data notes |

## Contributing

Every change must keep the full ROM byte-identical. Start with
[AGENTS.md](AGENTS.md) for the matching workflow and the accepted source
forms, [docs/IDIOMS.md](docs/IDIOMS.md) for agbcc idioms that reproduced the
reference, and [docs/M2C.md](docs/M2C.md) for draft generation.

The main tools:

- `tools/m2c_candidate.py <address> --match` decodes one function with
  [m2c](https://github.com/matt-kempster/m2c) and compiles the draft through the
  real agbcc profile.
- `tools/match.py <spec>` and `tools/asm_diff.py <spec>` compare a candidate
  with the ROM in isolation and show an aligned instruction diff.
- `tools/permute.py <name>` runs
  [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) on a
  near-miss and byte-verifies any score-0 result.
- `tools/le_codec.py` unpacks the game's custom `Le` graphics compression
  ([docs/COMPRESSION.md](docs/COMPRESSION.md)).
- `tools/emulator.py` runs optional mGBA traces ([docs/EMULATION.md](docs/EMULATION.md)).

This project is developed with AI coding agents under human review. AI
contributions are welcome when they meet the same standard: byte-identical
output, accurate notes, and address names rather than invented ones when the
meaning is not established.

## License

The code, tools and documentation in this repository are licensed under the
[GNU General Public License v3.0](LICENSE). This grants no rights to the game
itself: Medabots, its characters, graphics, music and text belong to their
respective owners. This project is not affiliated with or endorsed by them.

## Credits

- [pret](https://github.com/pret) for agbcc and the GBA decompilation approach.
- [m2c](https://github.com/matt-kempster/m2c) and
  [decomp-permuter](https://github.com/simonlindholm/decomp-permuter).
- [objdiff](https://github.com/encounter/objdiff) for the progress report format.
