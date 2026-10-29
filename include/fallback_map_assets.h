#ifndef GUARD_FALLBACK_MAP_ASSETS_H
#define GUARD_FALLBACK_MAP_ASSETS_H
#include "global.h"

/* DMA loaders use 32 palette bytes followed by 128 tile bytes per record. */
struct FallbackMapAsset {
    u16 palette[16];
    u32 tiles[4][8];
};
extern const struct FallbackMapAsset gFallbackMapAssets_080AC72C[6];
#endif
