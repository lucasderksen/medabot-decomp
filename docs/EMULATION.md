# Repeatable emulator traces

`tools/emulator.py` runs an optional Windows x64 mGBA libretro core through
libretro API version 1. The frontend records scripted button input, rendered
frames, and changes to four observed RAM state words. It uses mGBA's built-in
BIOS emulation, discards audio, and does not persist cartridge save data.

```powershell
python tools/bootstrap_emulator.py
python tools/emulator.py --rom build/medabots.gba --frames 1200 --inputs config/emulation/title.json --output-dir build/emulator/title
python tools/emulator.py --rom build/medabots.gba --frames 1500 --inputs config/emulation/new_game_menu.json --output-dir build/emulator/menu
python tools/emulator.py --rom build/medabots.gba --frames 2100 --inputs config/emulation/opening_scene.json --output-dir build/emulator/opening
```

Output directories must remain under `build/`. Each contains `trace.json`,
`last.png`, and an image for each state transition. `--capture 600,1199` also
captures selected zero-based frames. Input scripts contain inclusive `start`
and `end` frame numbers with a `buttons` list. Supported names are A, B, START,
SELECT, UP, DOWN, LEFT, RIGHT, L and R.

## Core provenance

The downloaded core reports `mGBA 0.11-212-7a12d6d`, corresponding to
[libretro/mgba commit 7a12d6d4b9acb14c0ae62c9166b6a2f3d08007f6](https://github.com/libretro/mgba/commit/7a12d6d4b9acb14c0ae62c9166b6a2f3d08007f6).
The distribution is from the official
[Windows x64 libretro buildbot](https://buildbot.libretro.com/nightly/windows/x86_64/latest/mgba_libretro.dll.zip).
mGBA is distributed under MPL 2.0; its license is downloaded alongside the core.
The frontend was checked against the
[libretro API header](https://github.com/libretro/libretro-common/blob/master/include/libretro.h)
and mGBA's core interface. These downloaded files remain ignored tooling.

| File | SHA-256 |
| --- | --- |
| `mgba_libretro.dll.zip` | `1bc924e7b20a0cba5e352cbbf75777571b66a4771d61c13eed2bba3569af60fe` |
| `mgba_libretro.dll` | `6af3783821b69bba6cad654cf73f3e1fceb3b2549dbb933a47ff20ba88f49bfa` |

The bootstrap and frontend verify these hashes. The buildbot's `latest` archive
can change; a changed archive is rejected rather than silently substituting a
different core. A later update requires deliberate review and new verification.
No original Nintendo BIOS is required or downloaded.

## Observed startup

The rebuilt ROM was run from a fresh emulated cartridge. Its complete-ROM hash
matches the supplied Metabee Europe rev0 dump. These scripted observations
identify contexts reached during startup:

| Scenario | Final observed screen | Main / substate / callback |
| --- | --- | --- |
| 600 frames, no buttons | Animated character intro | `3 / 1 / 11` |
| 1200 frames, Start at 650–653 | Title screen | `3 / 2 / 8` |
| 1500 frames, additional Start at 1200–1203 | New Game/options menu | `2 / 3 / 4` |
| 2100 frames, additional A at 1500–1503 | Opening story inside the shop | `1 / 1 / 5` |

Main state 3 includes both the intro and title sequence. Longer local
traces also advanced dialogue and reached a dialogue-free shop scene. State zero
was not reached through this startup sequence, so its screen names remain
provisional.

The recorded words are main state `0300178C`, substate `03002B8C`, callback index
`0300137C`, and render mode `03000430`. Memory descriptors provided by the core
are copied immediately because mGBA builds that descriptor array on its stack.
Canonical RAM regions are read through those descriptors. State changes trigger
captures after each completed emulator frame.

## Validation limits

This establishes boot and the observed startup path in one software emulator.
It does not validate every gameplay branch, cartridge link hardware, EEPROM
timing, audio output, or original hardware behavior. Byte-identical rebuilding
remains the integration requirement. Pure tests separately verify supported
pixel formats, padded rows, truncated-frame rejection, PNG pixels and checksums.
