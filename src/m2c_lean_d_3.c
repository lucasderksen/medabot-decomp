/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "composite_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "scene_view.h"
#include "sound_voice.h"
#include "sprite_layouts.h"
#include "state0_display.h"
#include "tile_text.h"

struct DmaRegs6FBB8 { u32 source, destination, control; };


void sub_0806FBB8(const u16 *src, u8 bg, u8 width, u8 height, u8 x, u8 y, u16 tile, u8 palette);

void sub_0806FBB8(const u16 *src, u8 bg, u8 width, u8 height, u8 x, u8 y, u16 tile, u8 palette) {

    u16 map[0x280];
    volatile u32 fill;
    s32 row;
    s32 col;

    fill = 0;
    {
        volatile struct DmaRegs6FBB8 *dma = (void *)0x040000D4;
        dma->source = (u32)&fill;
        dma->destination = (u32)map;
        dma->control = 0x85000140;
        (void)dma->control;
    }
    for (row = 0; row < height; row++) {
        for (col = 0; col < width; col++)
            map[((row + y) << 5) + col + x] = src[width * row + col] + (palette << 12) + tile;
    }
    {
        volatile struct DmaRegs6FBB8 *dma = (void *)0x040000D4;
        dma->source = (u32)map;
        dma->destination = (bg << 11) + 0x06000000;
        dma->control = 0x80000280;
        (void)dma->control;
    }
}
