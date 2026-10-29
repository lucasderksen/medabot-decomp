/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "display_helpers.h"
#include "effect_work.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"
#include "input.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern const void *const gUnknown_08484F98[];
extern s32 gUnknown_0202F800;
extern s32 gUnknown_0202F980;
extern s32 gUnknown_0202F9A0;
extern s32 gUnknown_0202FB00;
extern s32 gUnknown_0202FB20;
extern s32 gUnknown_03000660;
extern s32 gUnknown_084C7F74;
extern s32 gUnknown_084C7F94;
extern s32 gUnknown_084F3F80;
extern s32 gUnknown_0850F3F8;
extern s32 gUnknown_0850F498;
extern s32 sub_08035740(void *, s16, s32);
extern u8 gUnknown_084C50D0;
extern u8 gUnknown_084C5250;
extern u8 gUnknown_084E823C;
extern u8 gUnknown_084F0FD4;
extern void sub_080605A0(void);
extern void sub_08060620(void);
s32 sub_08036B50(u8 *, s32);
s32 sub_08037330(u8, u8, s32);
s32 sub_080373D4(u8);
s32 sub_0803E7C0();
s32 sub_0803E7F0();
s32 sub_0803E83C();
s32 sub_0803E870();

void sub_08023658(void);
void sub_08026A24(void);
void sub_0802F5D8(void);
void sub_0803D74C(void);
void sub_08041A28(void);
void sub_0805FADC(void);
void sub_0805FB14(void);
void sub_08060A1C(void);
s32 sub_0806DFC0(s32 arg0);

void sub_08023658(void) {
    gState0TypedWork.bytes[0x84] += 1;
    sub_08037330(gState0TransferWork.bytes[0x87], gState0TypedWork.bytes[0x84], 2);
    if ((gState0TypedWork.bytes[0x89] == 0) && (1 & *(u8 *) &gRepeatedKeys)) {
        sub_080373D4(gState0TransferWork.bytes[0x87]);
        gState0TransferWork.bytes[0xAA] += 1;
        return;
    }
    if (gState0TypedWork.widths.word86 != 0) {
        gState0TypedWork.widths.word86 -= 1;
        return;
    }
    sub_080373D4(gState0TransferWork.bytes[0x87]);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08026A24(void) {
    sub_08036B50(gDebugMenuTextBuffer, 0xA);
    sub_08036B50(gDebugMenuTextBuffer + 0x14, 0xE);
    sub_08036B50(gDebugMenuTextBuffer + 0x28, 0x12);
    if (sub_08036B50(gDebugMenuTextBuffer + 0x3C, 0x16) != 0) {
        *(u16 *) (gDebugMenuTextBuffer - 0x18) = 0x3C;
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_0802F5D8(void) {
    u8 *work = gState0TransferWork.bytes;
    u32 index = work[0x87] << 8;
    u8 *base = (u8 *) &gUnknown_03000660;
    u8 *record = (u8 *) (index + (u32) base);
    record += 5;
    sub_08035740(record, *(s16 *) (work + 0xEC), 0xFF);
    work[0xAA]++;
}

void sub_0803D74C(void) {
    s32 sp8;
    s32 spC;
    s32 sp10;

    sub_08043CA8();
    sp8 = 0;
    CpuFastSet(&sp8, (void *)0x05000200, 0x01000080U);
    spC = 0;
    CpuFastSet(&spC, (void *)0x05000000, 0x01000080U);
    *(u16 *)0x04000000 &= 0xE0FF;
    *(u16 *)0x04000008 = 0x500;
    *(u16 *)0x0400000A = 0x1801;
    (*(s16 *)((u8 *)((void *)0x0400000C) + 0)) = 0x590A;
    (*(s16 *)((u8 *)((void *)0x0400000C) + 2)) = 0x5B0B;
    LeDecompress(&gUnknown_084E823C, (void *)0x06004000);
    LeDecompress(&gUnknown_084C50D0, (void *)0x06006000);
    LeDecompress(&gUnknown_084C5250, (void *)0x06006200);
    LeDecompress(gMain2SharedObjectTiles_084C8034, (void *)0x06017400);
    sub_0803EF8C(0x20U, 0x20U, 0U, 0U, (u32) *(u16 *)0x04000008, 0U);
    sub_0803EF8C(0x20U, 0x20U, 0U, 0U, (u32) *(u16 *)0x0400000A, 0U);
    LoadLeTilemap(0U, 0U, &gUnknown_084F0FD4, (u32) *(u16 *)0x0400000A, 0x200U);
    CpuFastSet(&gUnknown_084F3F80, gEquipmentPaletteShadow, 0x70U);
    CpuFastSet(&gUnknown_084C7F74, &gUnknown_0202FB00, 8U);
    CpuFastSet(&gUnknown_084C7F94, &gUnknown_0202FB20, 8U);
    CpuFastSet(&gUnknown_0850F498, &gUnknown_0202F800, 0x40U);
    CpuFastSet(&gUnknown_0850F3F8, &gUnknown_0202F980, 8U);
    CpuFastSet((u8 *) &gUnknown_0850F3F8 + 0xFFFFFEA0, &gUnknown_0202F9A0, 8U);
    sub_08043B7C((u32) gState0TransferWork.bytes[0x38], 1U);
    sp10 = 0;
    CpuFastSet(&sp10, gFrameObjects, 0x01000800U);
    *(u16 *)0x04000000 |= 0x1F60;
    sub_0803E7C0();
    sub_0803E7F0();
    sub_0803E83C();
    sub_0803E870();
    sub_08043DF8();
    sub_08074B88(8U);
    gState0TypedWork.bytes[0x84] = 0;
    gUnknown_0300137C += 1;
}

void sub_08041A28(void) {
    if (0xC0 & *(u8 *) &gNewKeys) {
        sub_08074DE0(2U);
        gState0TypedWork.bytes[0x2A] ^= 1;
        gFrameObjects[gState0TypedWork.bytes[0x2B]].screenY = (gState0TypedWork.bytes[0x2A] * 0x10) + 0x48;
    }
    sub_08041C14(gState0TypedWork.bytes[0x2B], gState0TypedWork.bytes[0x84], (u16) ((u32) ((gState0TypedWork.bytes[0x2C] << 0x13) + 0x140000) >> 0x10));
    gState0TypedWork.bytes[0x84] += 1;
    if (2 & *(u8 *) &gNewKeys) {
        sub_08074DE0(5U);
        gState0TypedWork.bytes[0x2A] = 1;
        gFrameObjects[gState0TypedWork.bytes[0x2B]].screenX = (gState0TypedWork.bytes[0x2C] * 8) + 0x14;
        gFrameObjects[gState0TypedWork.bytes[0x2B]].screenY = (gState0TypedWork.bytes[0x2A] * 0x10) + 0x48;
        gState0TypedWork.bytes[0x84] = 0;
        gState0TypedWork.bytes[0x29] += 1;
    }
    if (1 & *(u8 *) &gNewKeys) {
        sub_08074DE0(4U);
        gFrameObjects[gState0TypedWork.bytes[0x2B]].screenX = (gState0TypedWork.bytes[0x2C] * 8) + 0x14;
        gState0TypedWork.bytes[0x84] = 0;
        gState0TypedWork.bytes[0x29] += 1;
    }
}

void sub_0805FADC(void) {
    if (sub_0803FB3C(gMain2ScriptSlots_0848521C[5]) != 0) {
        u16 *context = gMainContextPointer_03006F74;
        u16 count = context[1]++;
        if (count > 0x3C)
            gUnknown_0300137C = 8;
    }
}

void sub_0805FB14(void) {
    if (sub_0803FB3C(gMain2ScriptSlots_0848521C[6]) != 0) {
        u16 *context = gMainContextPointer_03006F74;
        u16 count = context[1]++;
        if (count > 0x3C)
            gUnknown_0300137C = 8;
    }
}

void sub_08060A1C(void) {
    u32 index = *((u8 *) gMainContextPointer_03006F74 + 0x17);
    const void *const *scripts = gUnknown_08484F98;
    index <<= 2;
    if (sub_0803FB3C(*(const void **) (index + (u32) scripts)) != 0)
        gUnknown_0300137C++;
    sub_080605A0();
    sub_08060620();
}

s32 sub_0806DFC0(s32 arg0) {
    u32 shifted;
    u8 *base;
    u8 temp_r0;
    void *temp_r1;

    shifted = arg0 << 0x18;
    base = (u8 *) gFrameObjects;
    temp_r1 = (u8 *) ((shifted >> 0x12) + (u32) base);
    shifted = arg0 << 0x18;
    base = (u8 *) gFrameObjects;
    temp_r0 = (*(u8 *)((u8 *)(temp_r1) + 0x22));
    if ((u32) temp_r0 > 0xFU) {
        return 0;
    }
    if (temp_r0 != 0) {
        (*(u16 *)((u8 *)(temp_r1) + 6)) = (u16) ((*(u16 *)((u8 *)(temp_r1) + 6)) + 1);
    }
    (*(u8 *)((u8 *)(temp_r1) + 0x22)) = (u8) ((*(u8 *)((u8 *)(temp_r1) + 0x22)) + 1);
    return 1;
}
