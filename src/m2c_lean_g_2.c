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
#include "continued_blend_work.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"
#include "initialization.h"
#include "link_menu.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "render_work.h"
#include "scene_view.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_display.h"
#include "state0_work.h"
#include "tile_text.h"

struct PlacementView45120 { u16 unknown00; s16 x; u8 y; u8 pad5; s8 key; u8 affineMode:2; u8 objMode:2; u8 rest:4; };
struct OamData45120 {
    u32 y:8;
    u32 affineMode:2;
    u32 objMode:2;
    u32 mosaic:1;
    u32 bpp:1;
    u32 shape:2;
    u32 x:9;
    u32 matrixNum:3;
    u32 hFlip:1;
    u32 vFlip:1;
    u32 size:2;
    u16 tileNum:10;
    u16 priority:2;
    u16 paletteNum:4;
    u16 affineParam;
};


u32 sub_08045120(struct OamEntry *objects, const void *source, const void *palette, const u32 *header, const struct RecordObjectPlacement *placement, u8 bank, u16 tile);

u32 sub_08045120(struct OamEntry *objects, const void *source, const void *palette, const u32 *header, const struct RecordObjectPlacement *placement, u8 bank, u16 tile) {

    u16 width;
    u16 dims[2];
    u32 value;
    u32 descriptor;
    u8 row;
    u8 column;
    u32 y;
    const u32 *layout;

    value = sub_08044E64(((*header << 26) >> 30) << 14, ((*header << 24) >> 30) << 30);
    dims[0] = value >> 16;
    dims[1] = value;
    value = dims[0] * dims[1];
    if (!(0xF & *(const u8 *)header))
        value >>= 1;
    {
        u32 t;
        u32 x;

        descriptor = *header;
        t = (descriptor << 20) >> 28;
        x = value * (s16)t;
        t = (descriptor << 16) >> 28;
        value = x * (u16)t;
        x = descriptor << 26;
        x >>= 30;
        t = descriptor;
        sub_08045084(source, x << 14, ((t << 24) >> 30) << 30, (t << 20) >> 28, (t << 16) >> 28,
                     (descriptor << 28) >> 28, tile, value, (void *)0x02030000, 1);
    }
    layout = header;
    if (palette != NULL)
        CpuSet(palette, (void *)(0x05000200 + bank * 32), 0x10);
    value = (dims[0] >> 3) * (dims[1] >> 3);
    for (row = 0; row < ((*layout << 20) >> 28); row++)
    {
        for (column = 0; column < ((*layout << 16) >> 28); column++)
        {
            struct OamData45120 *oam = (struct OamData45120 *)objects;

            y = ((const struct PlacementView45120 *)placement)->y;
            oam->y = row * dims[0] + y;
            oam->affineMode = ((const struct PlacementView45120 *)placement)->affineMode;
            oam->objMode = ((const struct PlacementView45120 *)placement)->objMode;
            oam->mosaic = 0;
            oam->bpp = (*layout << 28) >> 28;
            oam->shape = (*layout << 26) >> 30;
            width = dims[1];
            oam->x = (s16)placement->x + column * width;
            oam->matrixNum = 0;
            oam->hFlip = 0;
            oam->vFlip = 0;
            oam->size = (*layout << 24) >> 30;
            oam->tileNum = tile;
            oam->priority = 0;
            oam->paletteNum = bank;
            tile += value;
            objects++;
        }
    }
    return tile;
}
