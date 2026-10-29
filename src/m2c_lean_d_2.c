/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "link_menu.h"
#include "object_numeric_helpers.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_voice.h"
#include "sprite_layouts.h"
#include "state0_display.h"
#include "state0_work.h"
#include "tile_text.h"

struct Dma6FF2C { u32 source, destination, control; };
struct Bridge6FF2C
{
    u8 unknown00[0xEC];
    u8 column;
    u8 step;
};

extern const u8 gBridgeSteps_08485AEC[];
extern struct Bridge6FF2C gBridge6FF2C asm("gCounter6ED08_03001800");

s32 sub_0806FF2C(u8 index);

s32 sub_0806FF2C(u8 index) {

    u16 tile[1];
    u8 x;
    u32 object;

    tile[0] = 0xD2;
    if (gBridge6FF2C.step > 2)
        return 1;
    if (gBridgeSteps_08485AEC[gBridge6FF2C.step * 4 + index * 12 + 2] <= (x = gBridgeSteps_08485AEC[gBridge6FF2C.step * 4 + index * 12]) + gBridge6FF2C.column) {
        gFrameObjects[gBridge6FF2C.step + 0xB].screenY = gBridgeSteps_08485AEC[gBridge6FF2C.step * 4 + index * 12 + 3] * 8;
        gBridge6FF2C.column = 0;
        gBridge6FF2C.step++;
        return 0;
    }
    if (gBridge6FF2C.column <= 1) {
        u8 row = gBridgeSteps_08485AEC[gBridge6FF2C.step * 4 + index * 12 + 3];
        u8 y;
        if (row + gBridge6FF2C.column < (y = gBridgeSteps_08485AEC[gBridge6FF2C.step * 4 + index * 12 + 1])) {
            u32 twice = gBridge6FF2C.step * 2;
            u32 base = gBridge6FF2C.column + 0xE;
            object = twice + base;
            sub_08048864(object, 0xC400, 0x303, 0, 3);
            gFrameObjects[object].screenX = (gBridgeSteps_08485AEC[gBridge6FF2C.step * 4 + index * 12] + gBridge6FF2C.column) * 8;
            gFrameObjects[object].screenY = (gBridgeSteps_08485AEC[gBridge6FF2C.step * 4 + index * 12 + 1] - gBridge6FF2C.column) * 8 - 4;
        } else if (y + gBridge6FF2C.column < row) {
            u32 twice = gBridge6FF2C.step * 2;
            u32 base = gBridge6FF2C.column + 0xE;
            object = twice + base;
            sub_08048864(object, 0xE400, 0x303, 0, 3);
            gFrameObjects[object].screenX = (gBridgeSteps_08485AEC[gBridge6FF2C.step * 4 + index * 12] + gBridge6FF2C.column) * 8;
            gFrameObjects[object].screenY = (gBridgeSteps_08485AEC[gBridge6FF2C.step * 4 + index * 12 + 1] + gBridge6FF2C.column) * 8 + 0xC;
        } else {
            u32 cell = gBridge6FF2C.column + (x + (row << 5));
            volatile struct Dma6FF2C *dma = (void *)0x040000D4;
            dma->source = (u32)tile;
            dma->destination = cell * 2 + 0x0600F800;
            dma->control = 0x80000001;
            (void)dma->control;
        }
    } else {
        u32 cell = gBridge6FF2C.column + (x + (gBridgeSteps_08485AEC[gBridge6FF2C.step * 4 + index * 12 + 3] << 5));
        volatile struct Dma6FF2C *dma = (void *)0x040000D4;
        dma->source = (u32)tile;
        dma->destination = cell * 2 + 0x0600F800;
        dma->control = 0x80000001;
        (void)dma->control;
    }
    gBridge6FF2C.column++;
    return 0;
}
