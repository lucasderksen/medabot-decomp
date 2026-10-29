/*
 * Byte-verified tilemap copy (lean_a); names and types provisional.
 */

#include "global.h"
#include "graphics.h"

void CopyTilemap(u32 x, u32 y, const struct GraphicsRows *source, u32 control) {
    const u16 *in;
    u16 *out;
    u32 row;
    u32 column;

    u32 screenOffset = ((control >> 8) & 31) << 11;
    u32 xAddress = x * 2 + 0x06000000;
    u16 *base = (u16 *)(screenOffset + xAddress + (y << 6));
    in = source->data;
    if (((0xC000 & control) >> 14) & 1) {
        CopyLargeTilemap(base, source);
        return;
    }
    for (row = 0; row < source->height; row++) {
        out = (u16 *)((u32)base + ((xAddress = row) << 6));
        for (column = 0; column < source->width; column++) {
            *out++ = *in++ + gTilemapEntryOffset;
        }
    }
}
