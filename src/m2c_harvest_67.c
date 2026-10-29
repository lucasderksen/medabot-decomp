/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "display_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "graphics.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s32 gUnknown_0300059A;
extern s32 gUnknown_03000660;
s32 sub_08035740(void *, s16, s32);

void sub_08015B3C(u32 value);
void sub_08020004(void);
void sub_0802AFB0(void);
s32 sub_0806B484(u32 inputIndex);

void sub_08015B3C(u32 value) {
    if (value <= 2U) {
        sub_08040D0C(0xAU, 0xAU);
        sub_08040DB8((value << 8) + (u8 *) &gUnknown_0300059A, 0xAU, 1, 0xE, 0xAU, 0xFU, 0U, 1U);
        return;
    }
    sub_08040D0C(0x14U, 0xDU);
    sub_08040DB8((value << 8) + (u8 *) &gUnknown_0300059A, 0x14U, 0x13, 0xE, 0xAU, 0xFU, 0U, 1U);
}

void sub_08020004(void) {
    sub_0803F63C((gState0TransferWork.bytes[0x51] << 8) + (u8 *) &gUnknown_0300059A, gDebugMenuTextBuffer, 0xEU);
    gState0TransferWork.bytes[0xA6] = 0x14;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802AFB0(void) {
    sub_08035740((gState0TransferWork.bytes[0x87] << 8) + (u8 *) &gUnknown_03000660, (*(s16 *)((u8 *)(&gState0TransferWork) + 0xEC)), 0xFF);
    gState0TransferWork.bytes[0xAA] += 1;
}

s32 sub_0806B484(u32 inputIndex) {
    s32 arg0 = (s32)inputIndex;
    u32 shifted;
    u8 *base;
    u8 temp_r0_2;
    void *temp_r0;

    shifted = arg0 << 0x18;
    base = (u8 *) gFrameObjects;
    temp_r0 = (u8 *) ((shifted >> 0x12) + (u32) base);
    temp_r0_2 = (*(u8 *)((u8 *)(temp_r0) + 0x27));
    if (temp_r0_2 != 0) {
        (*(u8 *)((u8 *)(temp_r0) + 0x27)) = (u8) (temp_r0_2 - 1);
    }
    return 1;
}
