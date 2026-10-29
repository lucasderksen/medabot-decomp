/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "composite_graphics.h"
#include "continued_scene_records.h"
#include "coordinate_helpers.h"
#include "fallback_map_assets.h"
#include "frame.h"
#include "main_callbacks.h"
#include "map_metadata.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "state0_work.h"
#include "tile_text.h"

extern u8 gUnknown_083AD4F0[];
extern u8 gUnknown_083AD4F6[];
extern u8 gUnknown_083AD4FC[];

s32 sub_08016154(u32 index, u32 reverse);

s32 sub_08016154(u32 index, u32 reverse) {

    s32 done;
    u32 t;
    u32 step;
    struct FrameObject *object;
    union { struct TileCoordinates tile; s32 packed; } c;
    u32 root;

    done = 0;
    gFrameObjects[index].flags &= 0xFFDF;
    root = (u32)gFrameObjects;
    if (reverse == 0) {
        u32 base = (u32)gUnknown_083AD4F6;
        u32 offset = gCounter6ED08_03001800.buffer64[0x1D];
        t = *(const u8 *)(base + offset);
    } else {
        u32 base = (u32)gUnknown_083AD4FC;
        u32 offset = gCounter6ED08_03001800.buffer64[0x1D];
        t = *(const u8 *)(base + offset);
    }
    step = index - t;
    if (step > 5) {
        step += 6;
    }
    if (reverse == 0) {
        ((struct FrameObject *)((index << 6) + root))->commandDelay += 6;
    } else {
        ((struct FrameObject *)((index << 6) + root))->commandDelay -= 6;
    }
    do {
    object = &gFrameObjects[index];
    if (++object->commandOffset == 7) {
        done = 1;
        {
            u32 base = (u32)gUnknown_083AD4F0;
            u32 offset = step;
            object->commandDelay = *(const u8 *)(base + offset);
        }
        object->commandOffset = 0;
        object->commandStopped = 0;
    }
    } while (0);
    c.tile = sub_08042CA0(object->commandDelay, 0x18, 0x78, 0x80, 8, 0);
    object->screenX = c.packed;
    object->screenY = c.packed >> 16;
    object->frameAndGroup = index + 0x60C;
    if (object->screenY > 0x87)
        object->palette = 8;
    else if (object->screenY > 0x7B)
        object->palette = 9;
    else
        object->palette = 10;
    gFrameObjects[index].tableSelector = 0;
    gFrameObjects[index].scaleY = 0x40 - (0x90 - gFrameObjects[index].screenY) / 2;
    gFrameObjects[index].scaleX = 0x40 - (0x90 - gFrameObjects[index].screenY) / 2;
    gFrameObjects[index].priority = gFrameObjects[index].screenY - 0x70;
    return done;
}
