#ifndef GUARD_SPRITE_LAYOUTS_H
#define GUARD_SPRITE_LAYOUTS_H

#include "global.h"

/* ROM renderer 08001520 consumes a four-byte header and eight-byte parts. */
struct SpriteFrameHeader { u16 count; u16 reserved; };
struct SpriteFramePart { u16 attributes; u16 tileAndPalette; s16 x; s16 y; };

extern const u16 gObjectPaletteBanks_0807C210[53][16];

#endif
