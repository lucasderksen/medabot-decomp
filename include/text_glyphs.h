#ifndef GUARD_TEXT_GLYPHS_H
#define GUARD_TEXT_GLYPHS_H
#include "global.h"

/* Two native 8x16, 4-bpp glyph banks. Each glyph is sixteen little-endian
 * packed-pixel row words. Metrics are 256 (width, auxiliary byte) pairs;
 * only the width is consumed by 08040038/080402B4. */
#define TEXT_GLYPH_COUNT 135
#define TEXT_GLYPH_BYTES 64
extern const u8 gGlyphs_084BFC64[TEXT_GLYPH_COUNT * TEXT_GLYPH_BYTES];
extern const u8 gGlyphs_084C59A4[TEXT_GLYPH_COUNT * TEXT_GLYPH_BYTES];
extern const u8 gGlyphMetrics_083B4E08[256 * 2];
extern const u8 gGlyphMetrics_083B5008[256 * 2];

#endif
