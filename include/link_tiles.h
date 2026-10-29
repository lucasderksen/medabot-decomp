#ifndef GUARD_LINK_TILES_H
#define GUARD_LINK_TILES_H

#include "global.h"

struct LinkTilePatternPointers
{
    const u16 *items[8];
};

extern const u8 gLinkTileWidths[8];
extern const u8 gLinkTileHeights[8];
extern const u16 gLinkTileOffsets[8];
extern const struct LinkTilePatternPointers gLinkTilePatterns;
extern const u16 gLinkTileBases[8];
extern const u16 gLinkTilePattern0[2][2];
extern const u16 gLinkTilePattern1[10][1];
extern const u16 gLinkTilePattern2[10][2];
extern const u16 gLinkTilePattern3[2][2];
extern const u16 gLinkTilePattern4[5][8];

#endif
