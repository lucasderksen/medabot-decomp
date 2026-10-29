/*
 * sub_080697B4: not matching yet. The build assembles asm/non_matching/sub_080697B4.inc
 * in its place; the C below is the closest attempt (docs/drafts/README.md).
 */

#include "global.h"
#include "action_aux_data.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"
#include "link_tiles.h"
#include "main_callbacks.h"
#include "map_object_spawns.h"
#include "pose_channels.h"
#include "post_dispatch.h"
#include "record_helpers.h"
#include "rom_libc.h"
#include "scene_graphics_loads.h"
#include "sound_voice.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_display.h"
#include "state0_work.h"
#include "tile_text.h"

NONMATCH("asm/non_matching/sub_080697B4.inc", void sub_080697B4(u8 selector, u8 x, u8 y))
{
    u8 widths[8];
    u8 heights[8];
    u16 offsets[8];
    struct LinkTilePatternPointers patterns;
    u16 bases[8];
    u16 tile;
    s32 row;
    s32 column;
    u32 source;
    u32 mode;
    u32 vram;
    memcpy(widths, gLinkTileWidths, 8);
    memcpy(heights, gLinkTileHeights, 8);
    memcpy(offsets, gLinkTileOffsets, 16);
    patterns = gLinkTilePatterns;
    memcpy(bases, gLinkTileBases, 16);
    mode = selector & 7;
    source = (u32)patterns.items[mode];
    for (row = 0; row < heights[mode]; row++) {
        u32 position = (u32)x << 16;
        for (column = 0; column < widths[mode]; column++) {
            u32 value;
            volatile struct DmaTransfer *dma = (volatile struct DmaTransfer *)0x040000D4;
            if (mode > 4) value = row * 6 + column + offsets[mode];
            else value = offsets[mode] + *(const u16 *)source;
            tile = bases[mode] + value;
            if (mode <= 3) {
                dma->source = &tile;
                vram = (position >> 16) * 2 + 0x0600F800;
            } else {
                dma->source = &tile;
                vram = (position >> 16) * 2 + 0x0600E800;
            }
            dma->destination = (void *)(((u32)(u16)(row + y) << 6) + vram);
            dma->control = 0x80000001;
            (void)dma->control;
            source += 2;
            position += 0x10000;
        }
    }
}
END_NONMATCH
