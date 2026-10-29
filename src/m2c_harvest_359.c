/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame_command_handlers.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "main_callbacks.h"
#include "object_numeric_helpers.h"
#include "record_helpers.h"
#include "rom_libc.h"

extern const s8 gUnknown_080B0114[12];

s32 sub_08071A64(u32 arg0);

s32 sub_08071A64(u32 arg0) {

    s8 sp4[12];
    struct FrameObject *temp_r0_3;
    struct FrameObject *temp_r1;
    struct FrameObject *temp_r4;
    u32 var_r4;
    u32 frameRoot, lateRoot;
    u16 half;
    s8 byte;
    u32 temp_r0;
    u32 temp_r0_2;
    u8 temp_r6;

    temp_r6 = (u8)arg0;
    memcpy(sp4, gUnknown_080B0114, 0xCU);
    frameRoot=(u32)gFrameObjects;
    temp_r4=(struct FrameObject *)(frameRoot + ((u32)temp_r6 << 6));
    temp_r0 = temp_r4->commandOffset;
    if ((u32) temp_r0 <= 0xBU) {
        half = temp_r4->unknown1A;
        temp_r0 += (u32)sp4;
        byte = *(s8 *)temp_r0;
        if (half == byte) {
            temp_r4->screenX = (u16) temp_r4->screenX - 1;
            temp_r0_2 = temp_r4->commandOffset + 1;
            temp_r4->commandOffset = temp_r0_2;
            if (((u8)temp_r0_2 == 8) && (temp_r4->commandStopped != 0xFF)) {
                if (temp_r6 == 0) {
                    sub_08048864(1U, 0xCC00U, 0x50EU, 4U, 3U);
                    var_r4 = 1;
                } else {
                    var_r4 = temp_r6 + 1;
                    sub_08048864(var_r4, 0xC800U, 0x50EU, 4U, 3U);
                }
                lateRoot=(u32)gFrameObjects;
                temp_r1=(struct FrameObject *)(lateRoot + (var_r4 << 6));
                temp_r0_3=(struct FrameObject *)(lateRoot + ((u32)temp_r6 << 6));
                temp_r1->screenX = (s16) (u16) temp_r0_3->screenX;
                temp_r1->screenY = 0;
                temp_r1->priority = temp_r0_3->priority - 1;
                sub_08071DB8(3, (u8) var_r4, 0);
            }
        }
        goto successful;
    }
    if (temp_r6 == 0) {
        gFrameObjects->flags = (0xF3FF & gFrameObjects->flags) | 0x800;
        gFrameObjects[1].flags = (0xF3FF & gFrameObjects[1].flags) | 0x800;
    }
    if (temp_r4->commandStopped == 0xFF) {
        temp_r4->commandStopped = 0;
    }
    return 0;
successful:
    return 1;
}
