/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_command_handlers.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "render_work.h"
#include "rom_libc.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "utility_helpers.h"

struct ScriptState6ED08 {
    u8 unknown00[0x10];
    s8 active;
    u8 wait;
    u8 position;
};

extern const s8 gUnknown_080B010C[];
extern const u8 gUnknown_080B0120[];
extern struct ScriptState6ED08 gCounter6ED08_03001800;

s32 sub_0807190C(u8 index);
s32 sub_080719B8(u8 index);
s32 sub_080722B0(void);

s32 sub_0807190C(u8 index) {

    s8 steps[8];
    struct FrameObject *object;

    memcpy(steps, gUnknown_080B010C, 8);
    {
    u32 root = (u32)gFrameObjects;
    object = (struct FrameObject *)(root + (index << 6));
    }
    if (object->commandOffset <= 7) {
        if (object->unknown1A == steps[object->commandOffset]) {
            object->screenX++;
            object->commandOffset++;
        }
    } else {
        object->screenX++;
    }
    {
    u32 root = (u32)gFrameObjects;
    object = (struct FrameObject *)(root + (index << 6));
    }
    if (object->commandOffset == 4 && object->commandStopped != 0xFF)
        sub_08071DB8(1, object->commandStopped, 0);
    object = &gFrameObjects[index];
    if (object->screenX == 0xC9)
        object->flags = (object->flags & 0xF7FF) | 0xC00;
    else if (object->screenX > 0xCF)
        return 0xFF;
    return 1;
}

s32 sub_080719B8(u8 index) {

    s8 steps[8];
    struct FrameObject *object;

    memcpy(steps, gUnknown_080B010C, 8);
    {
    u32 root = (u32)gFrameObjects;
    object = (struct FrameObject *)(root + (index << 6));
    }
    if (object->commandOffset <= 7) {
        if (object->unknown1A == steps[object->commandOffset]) {
            object->screenX--;
            object->commandOffset++;
        }
    } else {
        object->screenX--;
    }
    {
    u32 root = (u32)gFrameObjects;
    object = (struct FrameObject *)(root + (index << 6));
    }
    if (object->commandOffset == 4 && object->commandStopped != 0xFF)
        sub_08071DB8(2, object->commandStopped, 0);
    object = &gFrameObjects[index];
    if (object->screenX == 0x1F)
        object->flags = (object->flags & 0xF7FF) | 0xC00;
    else if (object->screenX <= 0x18)
        return 0xFF;
    return 1;
}

s32 sub_080722B0(void) {

    u8 script[9];
    u32 fill;

    memcpy(script, gUnknown_080B0120, 9);
    gFrameObjects[2].screenY = 0xC8;
    gFrameObjects[3].screenY = 0xC8;
    gFrameObjects[4].screenY = 0xC8;
    gFrameObjects[5].screenY = 0xC8;
    fill = 0x200;
    {
        volatile u32 *dma = (volatile u32 *)0x040000D4;
        dma[0] = (u32)&fill;
        dma[1] = (u32)gRenderWork->objects;
        dma[2] = 0x85000100;
        dma[2];
    }
    sub_080446B4(0, 0x2B, 0x2B, 0x2B, 0x2B, 0x40, 0x42, 2, 8, 0, 1, 0);
    switch (script[gCounter6ED08_03001800.position]) {
    case 0:
        if (script[gCounter6ED08_03001800.position + 1] < gCounter6ED08_03001800.wait++) {
            gCounter6ED08_03001800.position += 2;
            gCounter6ED08_03001800.wait = 0;
        }
        break;
    case 1:
        sub_08074DE0(script[gCounter6ED08_03001800.position + 1]);
        gCounter6ED08_03001800.position += 2;
        gCounter6ED08_03001800.wait = 0;
        break;
    case 2:
        break;
    }
    if (sub_08044A3C(0, 0x2C, 0) != 0) {
        gCounter6ED08_03001800.active = 0;
        return 1;
    }
    return 0;
}
