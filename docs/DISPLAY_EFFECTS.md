# Palette-bank effects and work initialization

The reference interval `0x0803F684..0x0803FB0C` contains five Thumb functions,
including literal pools and zero alignment bytes. Names remain address-based;
the behavioral descriptions below are inferred from the machine code.

| Start | End | Bytes | Behavior |
|---|---|---:|---|
| 0803F684 | 0803F788 | 260 | Blend selected BG palette banks, then apply immediately |
| 0803F788 | 0803F890 | 264 | Blend selected BG banks, then schedule the palette callback |
| 0803F890 | 0803F998 | 264 | Blend selected OBJ banks, then schedule the palette callback |
| 0803F998 | 0803FAA0 | 264 | Blend selected OBJ banks, then apply immediately |
| 0803FAA0 | 0803FB0C | 108 | Initialize callback work and its default graphics/palette assets |

## Matching source

The initializer has matching C under the default agbcc settings. Its isolated
strict specification is `build/experiments/initialization/display_effects/spec.json`;
verification results are in `display_effects/strict/results.json`.
All four palette-loop candidates currently have the correct section sizes but
five differing bytes each. They remain in the experimental candidate source
and are excluded from `src/display_effects.c`.

## Initializer evidence

`sub_0803FAA0` reduces its first three arguments to bytes, clears the first
`0x28` bytes of callback work at `0x03000440`, and stores the three bytes at
offsets 0, 1, and 2. It writes unsigned `0xFF` at offset `0x0F` and signed `-1`
at offsets `0x10` and `0x11`. The local `EffectWorkPrefix` declaration preserves
this field layout and the original instruction sequence. It is a view of the
observed prefix, not a claim that the original program used this structure.

The initializer calls the matching graphics-loader helper at `0x0803F3A8`, then
copies sixteen colors from `0x084C7F34` to BG palette slot 14 at `0x050001C0`.
When the third argument's low byte equals one, it additionally calls the matching
BG0 map setup at `0x0803F3E0`. Other fields beyond this cleared prefix are not
defined by these observations.

## Palette-loop evidence

All four loops reduce the color and selection mask to sixteen bits and clamp
the unsigned weight to 32. Each mask bit selects one sixteen-color palette bank.
Selected colors blend their packed RGB555 components toward the supplied color:
`((sourceComponent*(32-weight) + targetComponent*weight) >> 5)`.
The green and blue results are masked again with `0x03E0` and `0x7C00` before
packing; red uses the low five bits. Unselected banks copy their saved entries
unchanged, including the source high bit.

BG source/output buffers are `0x0202FA00` and `0x0202FE00`. OBJ source/output
buffers are `0x0202F800` and `0x0202FC00`. Immediate helpers use CpuFastSet count
`0x80` (128 words, 512 bytes) to copy their output to the corresponding hardware
palette region. Deferred helpers store the Thumb address of
`ApplyBlendedPalettes` in the one-shot callback at `0x03000B98`; that callback
copies both BG and OBJ output buffers during the reconstructed VBlank work.

The instruction streams of the four blending bodies are identical apart from
their buffer literals and final application/callback sequence. This is useful
matching evidence, but does not establish whether their original source used
duplicated functions or a macro.
