/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "effect_work.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_part_markers.h"
#include "state0_work.h"
#include "utility_helpers.h"

extern const u8 *const gState0NextCommands_083B6100[];
extern const u8 *const gState0NextScripts_083BE564[];
extern const u8 *const gState0NextScripts_083BEAAC[];
extern const u8 gUnknown_083AD524[12];
extern u8 gUnknown_030018A8[0xC0];
extern void sub_0804422C(u32);

void sub_0800E350(void);
u32 sub_0801827C(void);
void sub_0801B5FC(u32 arg0);
s32 sub_0803325C(u32 arg0);
void sub_0803C5F8(void);

void sub_0800E350(void) {
 const u8 *script;
 sub_0800EBFC();sub_0800F440();sub_0800FD74();
 if(gState0TypedWork.bytes[0x3E]<=2)script=gState0NextScripts_083BE564[sub_0800F6CC()];
 else script=gState0NextScripts_083BEAAC[sub_0800F6CC()];
 if(sub_0803FB3C(script))gUnknown_0300137C++;
}

u32 sub_0801827C(void) {
 const u8 *table=gUnknown_083AD524;u8 *work=gState0TypedWork.bytes,*part=work+0x3D;
 u32 bank=work[0x3C],offset=(bank*3+*part)*2;
 u32 value=*(const u8 *)(offset+(u32)table);
 if(bank)value-=0x10;else value+=0x10;
 return value;
}

void sub_0801B5FC(u32 arg0) {
    s32 sp0;
    s32 sp4;
    s32 sp8;
    s32 spC;
    s32 sp10;
    u8 *setup=gSetupBuffer_03000590;
    u32 clear;
    void *temp_r0;
    u8 *clearByte;

    temp_r0 = (arg0 << 8) + setup;
    clearByte=(u8 *)temp_r0+0xBC;clear=0;
    *clearByte = clear;
    (*(u8 *)((u8 *)(temp_r0) + 0xBD)) = (u8) (0xE5 & (*(u8 *)((u8 *)(temp_r0) + 0xBD)));
    sp0 = clear;
    CpuSet(&sp0, gUnknown_030018A8, 0x05000008U);
    sp4 = clear;
    CpuSet(&sp4, gUnknown_030018A8 + 0x20, 0x05000008U);
    sp8 = clear;
    CpuSet(&sp8, gUnknown_030018A8 + 0x40, 0x05000004U);
    spC = clear;
    CpuSet(&spC, gUnknown_030018A8 + 0x50, 0x05000008U);
    sp10 = clear;
    CpuSet(&sp10, gUnknown_030018A8 + 0xBC, 0x05000001U);
}

s32 sub_0803325C(u32 arg0) {
    u8 *base;
    u32 bank;
    s32 temp_r1;
    s32 var_r5;
    u32 mask;
    u32 var_r2;

    var_r5 = sub_080424B8() & 3;
    temp_r1 = sub_080424B8() & 1;
    var_r2 = 0;
    base = gSetupBuffer_03000590;
    mask=3;
    bank = arg0 << 8;
loop_1:
    if ((*(u8 *)((u8 *)((u8 *)(((u32)var_r5 * 0x18 + bank) + (u32)base)) + 0x59)) == 0) {
        return var_r5 + 1;
    }
    if (temp_r1 != 0) {
        var_r5 += 1;
    } else {
        var_r5 -= 1;
    }
    var_r5 &= mask;
    var_r2 += 1;
    if (var_r2 > 3U) {
        return 0;
    }
    goto loop_1;
}

void sub_0803C5F8(void) {
    struct FrameObject *frames = gFrameObjects;
    const u8 *const *commands;
    struct FrameObject *temp_r0_2;
    struct FrameObject *temp_r2;
    u8 temp_r0;
    u8 temp_r0_3;

    temp_r2 = &frames[gState0TypedWork.bytes[0x12F]];
    temp_r0 = temp_r2->unknown2C[0];
    if (temp_r0 != 0) {
        temp_r2->unknown2C[0] = temp_r0 - 1;
    } else {
        temp_r2->flags |= 0x8000;
        sub_08040BD8((commands=gState0NextCommands_083B6100,commands[frames[gState0TypedWork.bytes[0x12F]].unknown2C[1]]), gState0TypedWork.bytes[0x12F]);
    }
    { struct FrameObject *lateFrames=gFrameObjects;
    temp_r0_2 = &lateFrames[gState0TypedWork.bytes[0x12F]];
    temp_r0_3 = temp_r0_2->byte2B;
    if (temp_r0_3 != 0) {
        temp_r0_2->byte2B = temp_r0_3 - 1;
        return;
    }
    sub_0804422C((u32) gState0TypedWork.bytes[0x12F]);
    }
}
