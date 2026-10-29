/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "utility_helpers.h"

extern s32 gState0NextCommands_083B6100;
s32 sub_0803E894();
s32 sub_0803ED6C();
u8 sub_0807CEC8(u8, s32);
u8 sub_0807CF40(u8, s32);

void sub_08018C78(void);
void sub_080201DC(void);
void sub_08031918(void);
void sub_0803CF7C(void);
void sub_0803DC58(void);
void sub_0803E120(void);

void sub_08018C78(void) {
    __typeof__(gFrameObjects[0]) *array0;
    array0 = gFrameObjects;
    array0[1].frameAndGroup = sub_0807CEC8(gState0TransferWork.bytes[0x57], 0xA) + 0x624;
    array0[2].frameAndGroup = sub_0807CF40(gState0TransferWork.bytes[0x57], 0xA) + 0x624;
}

void sub_080201DC(void) {
    u8 *work0;
    u32 temp_r1;

    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0xDC)), 0xBU);
    if (gFrameObjects[0xA].byte2B == 0x28) {
        sub_08040CD0(0xBU, 1U);
        gState0TransferWork.bytes[0xAA] += 1;
        return;
    }
    temp_r1 = gFrameObjects[0xA].unknown2C[0] + 1;
    gFrameObjects[0xA].unknown2C[0] = temp_r1;
    if (temp_r1 & 1) {
        gFrameObjects[0xA].screenY = (u16) gFrameObjects[0xA].screenY - 1;
        gFrameObjects[0xA].byte2B += 1;
    }
}

void sub_08031918(void) {
    u8 *late0;
    gState0TransferWork.bytes[0x164] = 1;
    late0 = (u8 *) gSetupBuffer_03000590;
    gState0TransferWork.bytes[0xA8] = (*(u8 *)((u8 *)((late0 + (gState0TransferWork.bytes[0x87] << 8))) + 0xA8)) + 0x50;
    (*(s8 *)((u8 *)((late0 + (gState0TransferWork.bytes[0x87] << 8))) + 0xE0)) = 0;
    (*(s8 *)((u8 *)((late0 + (gState0TransferWork.bytes[0x87] << 8))) + 0xE1)) = 0;
    gMainSubstate = 9;
    gUnknown_0300137C = 0;
}

void sub_0803CF7C(void) {
    __typeof__(gFrameObjects[0]) *array0;
    struct FrameObject *temp_r0;
    struct FrameObject *temp_r0_3;
    u8 temp_r0_2;
    u8 temp_r0_4;

    array0 = gFrameObjects;
    temp_r0 = &array0[gState0TypedWork.bytes[0x12F]];
    temp_r0_2 = temp_r0->unknown2C[0];
    if (temp_r0_2 != 0) {
        temp_r0->unknown2C[0] = temp_r0_2 - 1;
    }
    temp_r0_3 = &array0[gState0TypedWork.bytes[0x12F]];
    temp_r0_4 = temp_r0_3->byte2B;
    if (temp_r0_4 != 0) {
        temp_r0_3->byte2B = temp_r0_4 - 1;
        return;
    }
    sub_0804422C((u32) gState0TypedWork.bytes[0x12F]);
}

void sub_0803DC58(void) {
    u32 var_r0;

    sub_08043CD4();
    if (gState0TypedWork.bytes[0x138] == 0) {
        gUnknown_0300137C = gUnknown_0300137C + 1;
    } else {
        gUnknown_0300137C = 0x30;
    }
}

void sub_0803E120(void) {
    u32 var_r0;

    sub_0803E894();
    sub_0803ED6C();
    gState0TypedWork.widths.word86 += 1;
    if ((&gState0TransferWork.bytes[0x19A])[gState0TransferWork.bytes[0x1A2]] == 4) {
        gUnknown_0300137C = gUnknown_0300137C + 1;
    } else {
        gUnknown_0300137C = 0x48;
    }
}
