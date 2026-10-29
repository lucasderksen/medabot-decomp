/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_inventory.h"
#include "state0_inventory_confirm.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s32 gState0NextCommands_083B6100;
extern s32 gUnknown_0850FC38;
extern s32 sub_08073BC8();
extern u8 gUnknown_084D6A5C;
s32 sub_08015BF4(u8);
s32 sub_0803D4AC();

void sub_0800B498(void);
void sub_080178CC(void);
void sub_080207CC(void);
void sub_08021950(void);
void sub_08021AFC(void);
void sub_08033434(void);
s32 sub_08037230(s32 arg0, s32 arg1);
void sub_08037FE4(void);
void sub_08038024(void);
void sub_0803805C(void);
void sub_080380B8(void);
void sub_0803858C(void);
void sub_08039CB4(void);
void sub_0803CB54(void);
u32 sub_08073BFC(u32 value, s32 factor);

void sub_0800B498(void) {
    u8 *base0 = (u8 *) gSetupBuffer_03000590;
    u32 var_r6;

    (*(u8 *)((u8 *)((base0 + (gState0TransferWork.bytes[0x80] << 8))) + 9)) = (u8) gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[3];
    var_r6 = 0;
    do {
        (gSetupBuffer_03000590 + 0x18)[var_r6 + (gState0TransferWork.bytes[0x80] << 8)] = (&gInventoryRecords->unknown06[0x12])[var_r6 + (gState0TypedWork.bytes[0x3D] << 6)];
        var_r6 += 1;
    } while (var_r6 <= 7U);
}

void sub_080178CC(void) {
    u8 *base0 = (u8 *) gSetupBuffer_03000590;
    u32 temp_r1;

    if ((*(u8 *)((u8 *)((base0 + (gState0TransferWork.bytes[0x80] << 8))) + 0xC1)) == 0x50) {
        temp_r1 = gState0TransferWork.bytes[0x85] + 1;
        gState0TransferWork.bytes[0x85] = temp_r1;
        if (temp_r1 & 8) {
            sub_08015BF4(gState0TransferWork.bytes[0x80]);
            return;
        }
        sub_08015BA8((u32) gState0TransferWork.bytes[0x80]);
    }
}

void sub_080207CC(void) {
    u8 *base0 = (u8 *) gSetupBuffer_03000590;
    if (4 & (*(u8 *)((u8 *)((base0 + (gState0TransferWork.bytes[0x88] << 8))) + 0xBD))) {
        gState0TransferWork.bytes[0xAA] += 1;
        gState0TransferWork.bytes[0xAB] = 0;
        return;
    }
    gState0TransferWork.bytes[0xA6] = 0x19;
    gState0TransferWork.bytes[0xAA] = 2;
    (*(s8 *)((u8 *)((&gState0TransferWork.bytes[0xA6] + 4)) + 1)) = 1;
}

void sub_08021950(void) {
    u8 *work0;
    LeDecompress(&gUnknown_084D6A5C, (void *)0x06014800);
    CpuFastSet(&gUnknown_0850FC38, (void *)0x050002E0, 8U);
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040B90((*(u8 **)((u8 *)(work0) + 0xE4)), 0x21U);
    if (1 & gState0TransferWork.bytes[0xF8]) {
        gFrameObjects[0x21].flags |= 0x1000;
    }
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08021AFC(void) {
    u8 *work0;
    u32 temp_r0;
    u32 var_r4;

    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0xEC)), 0x21U);
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0xEC)), 0x22U);
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0xEC)), 0x23U);
    temp_r0 = sub_080355F0(0x21U);
    var_r4 = (u32) ((0 - temp_r0) | temp_r0) >> 0x1F;
    if (sub_080355F0(0x22U) != 0) {
        var_r4 += 1;
    }
    if (sub_080355F0(0x23U) != 0) {
        var_r4 += 1;
    }
    if (var_r4 == 3) {
        sub_08040B90((*(u8 **)((u8 *)(work0) + 0xE8)), 0x21U);
        sub_08040B90((*(u8 **)((u8 *)(work0) + 0xE8)), 0x22U);
        sub_08040B90((*(u8 **)((u8 *)(work0) + 0xE8)), 0x23U);
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_08033434(void) {
    __typeof__(gSetupBuffer_03000590[0]) *array0;
    u8 *temp_r0;
    u8 *temp_r2;
    u8 temp_r1;

    array0 = gSetupBuffer_03000590;
    temp_r2 = &array0[(gState0TransferWork.bytes[0x5D] * 0x18) + (gState0TransferWork.bytes[0x5C] << 8)];
    temp_r0 = &array0[(((*(u8 *)((u8 *)(temp_r2) + 0x57)) - 1) * 0x18) + (((*(u8 *)((u8 *)(temp_r2) + 0x56)) - 1) << 8)];
    temp_r1 = (*(u8 *)((u8 *)(temp_r0) + 0x59));
    if ((temp_r1 == 0) || (temp_r1 == (*(u8 *)((u8 *)(temp_r0) + 0x4C)))) {
        gState0TransferWork.bytes[0x51] = 1;
    }
}

s32 sub_08037230(s32 arg0, s32 arg1) {
    __typeof__(gSetupBuffer_03000590[0]) *array0;
    u8 *temp_r0;
    u8 temp_r1;

    array0 = gSetupBuffer_03000590;
    temp_r0 = &array0[(arg1 * 0x18) + (arg0 << 8)];
    temp_r1 = (*(u8 *)((u8 *)(temp_r0) + 0x59));
    if ((temp_r1 != 0) && (temp_r1 != (*(u8 *)((u8 *)(temp_r0) + 0x4C)))) {
        return 0;
    }
    return 1;
}

void sub_08037FE4(void) {
    __typeof__(gFrameObjects[0]) *array0;
    struct FrameObject *temp_r1;
    struct FrameObject *temp_r1_2;
    u8 temp_r0;

    array0 = gFrameObjects;
    temp_r1 = &array0[gState0TypedWork.bytes[0x12F]];
    temp_r0 = temp_r1->scaleX;
    if (temp_r0 == 4) {
        temp_r1->unknown23[6] += 1;
        return;
    }
    temp_r1->scaleX = temp_r0 - 4;
    temp_r1_2 = &array0[gState0TypedWork.bytes[0x12F]];
    temp_r1_2->scaleY -= 4;
}

void sub_08038024(void) {
    __typeof__(gFrameObjects[0]) *array0;
    struct FrameObject *temp_r1;
    u8 temp_r0;

    array0 = gFrameObjects;
    temp_r1 = &array0[gState0TypedWork.bytes[0x12F]];
    temp_r0 = temp_r1->unknown2C[1];
    if (temp_r0 == 0x5A) {
        temp_r1->unknown23[6] += 1;
        return;
    }
    temp_r1->unknown2C[1] = temp_r0 + 1;
}

void sub_0803805C(void) {
    __typeof__(gFrameObjects[0]) *array0;
    struct FrameObject *temp_r1;
    struct FrameObject *temp_r1_2;
    u8 temp_r0;

    array0 = gFrameObjects;
    temp_r1 = &array0[gState0TypedWork.bytes[0x12F]];
    temp_r0 = temp_r1->scaleX;
    if (temp_r0 == 8) {
        temp_r1->unknown23[6] += 1;
        return;
    }
    temp_r1->scaleX = temp_r0 - 8;
    temp_r1_2 = &array0[gState0TypedWork.bytes[0x12F]];
    temp_r1_2->scaleY -= 8;
}

void sub_080380B8(void) {
    __typeof__(gFrameObjects[0]) *array0;
    struct FrameObject *temp_r1;
    u8 temp_r0;

    array0 = gFrameObjects;
    temp_r1 = &array0[gState0TypedWork.bytes[0x12F]];
    temp_r0 = temp_r1->unknown2C[1];
    if (temp_r0 == 0x23) {
        temp_r1->unknown23[6] += 1;
        return;
    }
    temp_r1->unknown2C[1] = temp_r0 + 1;
}

void sub_0803858C(void) {
    __typeof__(gFrameObjects[0]) *array0;
    struct FrameObject *temp_r1;

    array0 = gFrameObjects;
    temp_r1 = &array0[gState0TypedWork.bytes[0x12F]];
    temp_r1->angle = (temp_r1->angle + 0x10) & 0x3FF;
    if (sub_080355F0((u32) gState0TypedWork.bytes[0x12F]) != 0) {
        sub_08040CD0(gState0TypedWork.bytes[0x12F], 1U);
    }
}

void sub_08039CB4(void) {
    u8 *base0 = (u8 *) gSetupBuffer_03000590;
    u8 temp_r2;

    temp_r2 = 0x20 & (*(u8 *)((u8 *)((base0 + (gState0TransferWork.bytes[0x88] << 8))) + 0xBC));
    if (temp_r2 != 0) {
        gState0TransferWork.bytes[0xFD] = 1;
    } else {
        gState0TransferWork.bytes[0xFD] = temp_r2;
    }
    sub_0803D4AC();
}

void sub_0803CB54(void) {
    __typeof__(gFrameObjects[0]) *array0;
    struct FrameObject *temp_r0_3;
    struct FrameObject *temp_r0_4;
    struct FrameObject *temp_r1;
    u16 temp_r0;
    u8 temp_r0_2;

    array0 = gFrameObjects;
    temp_r1 = &array0[gState0TypedWork.bytes[0x12F]];
    temp_r0 = (*(u16 *)((u8 *)(temp_r1) + 0x30));
    if (temp_r0 != 0) {
        (*(u16 *)((u8 *)(temp_r1) + 0x30)) = (u16) (temp_r0 - 1);
        return;
    }
    temp_r0_2 = temp_r1->unknown2C[0];
    if (temp_r0_2 != 0) {
        temp_r1->unknown2C[0] = temp_r0_2 - 1;
        return;
    }
    if (temp_r1->unknown2C[2] != 0) {
        sub_08074DE0((u32) temp_r1->byte2B);
        temp_r0_3 = &array0[gState0TypedWork.bytes[0x12F]];
        temp_r0_3->unknown2C[0] = temp_r0_3->unknown2C[1];
        temp_r0_4 = &array0[gState0TypedWork.bytes[0x12F]];
        temp_r0_4->unknown2C[2] -= 1;
        return;
    }
    sub_08040CD0(gState0TypedWork.bytes[0x12F], 1U);
}

u32 sub_08073BFC(u32 value, s32 factor) {
    if (factor == 0)
        return value;
    return (value * sub_08073BC8(factor)) >> 12;
}
