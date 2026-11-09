/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "action_aux_data.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "link_tiles.h"
#include "main_callbacks.h"
#include "map_object_spawns.h"
#include "pose_channels.h"
#include "post_dispatch.h"
#include "record_helpers.h"
#include "rom_libc.h"
#include "sprite_layouts.h"
#include "state0_work.h"
#include "tile_text.h"


void sub_080697B4(u8 selector, u8 x, u8 y);

void sub_080697B4(u8 selector, u8 x, u8 y) {

    u8 widths[8];
    u8 heights[8];
    u16 offsets[8];
    struct LinkTilePatternPointers patterns;
    u16 bases[8];
    u16 tile;
    s32 i;
    s32 j;
    const u16 *pattern;

    memcpy(widths, gLinkTileWidths, 8);
    memcpy(heights, gLinkTileHeights, 8);
    memcpy(offsets, gLinkTileOffsets, 16);
    patterns = gLinkTilePatterns;
    memcpy(bases, gLinkTileBases, 16);
    selector &= 7;
    pattern = patterns.items[selector];
    for (i = 0; i < heights[selector]; i++) {
        for (j = 0; j < widths[selector]; j++) {
            if (selector > 4)
                tile = i * 6 + j + offsets[selector] + bases[selector];
            else
                tile = *pattern + offsets[selector] + bases[selector];
            if (selector <= 3) {
                volatile u32 *dma = (volatile u32 *)0x040000D4;
                dma[0] = (u32)&tile;
                dma[1] = (u32)((u16 *)0x0600F800 + (u16)(i + y) * 32 + (u16)(x + j));
                dma[2] = 0x80000001;
                dma[2];
            } else {
                volatile u32 *dma = (volatile u32 *)0x040000D4;
                dma[0] = (u32)&tile;
                dma[1] = (u32)((u16 *)0x0600E800 + (u16)(i + y) * 32 + (u16)(x + j));
                dma[2] = 0x80000001;
                dma[2];
            }
            pattern++;
        }
    }
}
