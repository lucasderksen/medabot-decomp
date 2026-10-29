/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_late_graphics.h"
#include "frame.h"
#include "frame_command_handlers.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct FrameTimerView { u8 unknown00[0x30]; u16 baseFrame; u16 timer; };

extern const s8 gUnknown_080B00C8[];
extern s32 sub_0806B718(u8);

s32 sub_0806B1FC(u32 arg);
s32 sub_0806E074(u8 index);
s32 sub_080706A4(u8 index);

s32 sub_0806B1FC(u32 arg) {

    u8 index = arg;
    u32 root = (u32)gFrameObjects;
    struct FrameObject *object = (struct FrameObject *)(root + (index << 6));

    if (object->unknown1A <= 15)
        object->screenY += 2;
    if ((u16)(object->unknown1A - 0xD2) <= 15)
        object->screenY -= 2;
    if (object->unknown1A > 0xE1) {
        sub_0806B718(index);
        return 0;
    }
    return 1;
}

s32 sub_0806E074(u8 index) {

    u32 root = (u32)gFrameObjects;
    struct FrameObject *object = (struct FrameObject *)(root + (index << 6));

    if ((u16)((struct FrameTimerView *)object)->timer < object->unknown1A) {
        if (object->commandStopped > 7) {
            object->screenX = 300;
            object->commandStopped = 0;
            ((struct FrameTimerView *)object)->timer = (NextRandom(0) & 0x1FF) + 0x20;
            object->frameAndGroup = ((struct FrameTimerView *)object)->baseFrame;
            object->unknown1A = 0;
        } else if (gUnknown_0300137C == 9 && object->commandStopped == 0) {
            ((struct FrameTimerView *)object)->timer = -1;
            object->unknown1A = 0;
        } else {
            if (++gFrameObjects[index].commandStopped != 1)
                gFrameObjects[index].frameAndGroup++;
            else
                gFrameObjects[index].screenX = 0x78;
        }
    }
    return 1;
}

s32 sub_080706A4(u8 index) {

    if (index & 1) {
        gFrameObjects[index].screenY = gFrameObjects[index].unknown23[0] - gUnknown_080B00C8[gFrameObjects[index].commandOffset & 0x3F];
    } else {
        u32 root = (u32)gFrameObjects;
        struct FrameObject *object = (struct FrameObject *)(root + (index << 6));
        u8 *base = object->unknown23;
        object->screenY = (*base) + gUnknown_080B00C8[object->commandOffset & 0x3F];
    }
    gFrameObjects[index].commandOffset += 1 + gFrameObjects[index].commandStopped;
    return 1;
}
