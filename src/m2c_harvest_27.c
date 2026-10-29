/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s32 gState0NextCommands_083B6100;
extern s32 gUnknown_08510458;
extern u8 gUnknown_084E1A0C;
s32 sub_0801B004(u8);
s32 sub_0801C2F0(s32);

void sub_0801B67C(u32 arg0);
void sub_0801E43C(void);
void sub_08024790(void);
void sub_08026D1C(void);
void sub_0802B7AC(void);
void sub_0802DCDC(void);
void sub_08030DB4(void);
void sub_0803572C(u8 *arg0, s32 arg1);

void sub_0801B67C(u32 arg0) {
    u8 var_r1;

    if (arg0 <= 2U) {
        gState0TransferWork.bytes[0xF8] = 0;
    } else {
        gState0TransferWork.bytes[0xF8] = 3;
    }
}

void sub_0801E43C(void) {
    u8 *base0 = (u8 *) gSetupBuffer_03000590;
    u8 var_r0;

    if (0x40 & (*(u8 *)((u8 *)((base0 + (gState0TransferWork.bytes[0x88] << 8))) + 0xBC))) {
        gState0TransferWork.bytes[0xAA] = gState0TransferWork.bytes[0xAA] + 1;
    } else {
        gState0TransferWork.bytes[0xAA] = 6;
    }
}

void sub_08024790(void) {
    u8 *base0 = (u8 *) gSetupBuffer_03000590;
    u8 var_r0;

    if (4 & (*(u8 *)((u8 *)((base0 + (gState0TransferWork.bytes[0x88] << 8))) + 0xBD))) {
        gState0TransferWork.bytes[0xAA] = gState0TransferWork.bytes[0xAA] + 1;
    } else {
        gState0TransferWork.bytes[0xAA] = 0x15;
    }
}

void sub_08026D1C(void) {
    u8 var_r0;

    if (2 & gState0TransferWork.bytes[0xB8]) {
        gState0TransferWork.bytes[0xAA] = 0x20;
    } else {
        gState0TransferWork.bytes[0xAA] = gState0TransferWork.bytes[0xAA] + 1;
    }
}

void sub_0802B7AC(void) {
    u8 *base0 = (u8 *) gSetupBuffer_03000590;
    u8 var_r0;

    if ((*(u8 *)((u8 *)((base0 + (gState0TransferWork.bytes[0x87] << 8))) + 0xA8)) == 0x1E) {
        gState0TransferWork.bytes[0xA6] = 0x4D;
    } else {
        gState0TransferWork.bytes[0xA6] = 0x4E;
    }
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802DCDC(void) {
    u8 *work0;
    s16 var_r0;

    LeDecompress(&gUnknown_084E1A0C, (void *)0x06014800);
    CpuFastSet(&gUnknown_08510458, (void *)0x050002E0, 8U);
    gFrameObjects[0x21].flags = 0xC404;
    gFrameObjects[0x21].tableSelector = 0;
    gFrameObjects[0x21].screenY = 0xE0;
    gFrameObjects[0x21].palette = 7;
    gFrameObjects[0x21].priority = 0xF0;
    if (!(1 & gState0TransferWork.bytes[0xF8])) {
        gFrameObjects[0x21].screenX = 0xB8;
    } else {
        gFrameObjects[0x21].screenX = 0x40;
    }
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040B90((*(u8 **)((u8 *)(work0) + 0x1A4)), 0x21U);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08030DB4(void) {
    u8 *late0;
    u8 var_r0;

    sub_0801C2F0(0);
    sub_08074DE0(0x51U);
    late0 = (u8 *) gSetupBuffer_03000590;
    if (8 & (*(u8 *)((u8 *)((late0 + (gState0TransferWork.bytes[0x87] << 8))) + 0xC0))) {
        gState0TransferWork.bytes[0x51] = 0x50;
    } else {
        gState0TransferWork.bytes[0x51] = 0x28;
    }
    sub_0801B004(gState0TransferWork.bytes[0x87]);
    gUnknown_0300137C += 1;
}

void sub_0803572C(u8 *arg0, s32 arg1) {
    u8 temp_r0;
    u8 var_r0;

    temp_r0 = *arg0;
    if ((s32) temp_r0 < arg1) {
        *arg0 = 0;
    } else {
        *arg0 = temp_r0 - arg1;
    }
}
