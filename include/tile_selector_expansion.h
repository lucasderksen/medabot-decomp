#ifndef GUARD_STAGED_TILE_SELECTOR_EXPANSION_H
#define GUARD_STAGED_TILE_SELECTOR_EXPANSION_H

#include "global.h"

/* Nine observed word slots. Signed dimensions/offsets preserve /2 and %2;
 * attributes is explicitly narrowed at each call to the seven-slot helper. */
void sub_08048E24(const u8 *source, u16 *destination, s32 height, s32 width,
                 u32 unused4, u32 unused5, s32 rowOffset, s32 columnOffset,
                 u32 attributes);

#endif
