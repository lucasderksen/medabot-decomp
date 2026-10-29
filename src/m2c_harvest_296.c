/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "main_callbacks.h"


s32 sub_0806E038(u8 arg0);

s32 sub_0806E038(u8 arg0) {

    s16 var_r0;
    struct FrameObject *temp_r1;
    struct FrameObject *temp_r3;
    u8 temp_r4;
    u32 initialRoot;

    temp_r4 = arg0;
    initialRoot=(u32)gFrameObjects;
    temp_r3 = (struct FrameObject*)(initialRoot+((u32)temp_r4<<6));
    if (1 & temp_r3->commandStopped) {
        var_r0 = 0x73;
        temp_r3->screenY = var_r0;
    } else {
        var_r0 = 0xC8;
        temp_r3->screenY = var_r0;
    }
    temp_r1 = &gFrameObjects[temp_r4];
    temp_r1->commandStopped += 1;
    return 1;
}
