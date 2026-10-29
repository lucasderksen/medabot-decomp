/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "record_helpers.h"
#include "state0_work.h"

struct ResultRecord {u8 prefix[0xE0];u8 first;s8 second;};

extern s32 sub_0801B700(s32);
extern s32 sub_080330E8(s32);
extern void sub_080191A4(s32, u8);

void sub_080192E8(s32 arg0);
void sub_0801B69C(s32 arg0);
void sub_080385D0(s32 arg0);
s32 sub_08039134(s32 arg0);
void sub_0805B530(s32 arg0, s32 arg1, s32 arg2);

void sub_080192E8(s32 arg0) {
    s32 var_r5;
    u32 var_r6;
    u8 *temp_r1;

    u8 *setup;

    var_r6 = 0;
    setup = gSetupBuffer_03000590;
    var_r5 = 0;
    do {
        temp_r1 = (u8 *)((u32)(var_r5 + (arg0 << 8)) + (u32)setup);
        if (((*(u8 *)((u8 *)(temp_r1) + 0x49)) == 0x28) && ((*(u8 *)((u8 *)(temp_r1) + 0x59)) != 0)) {
            sub_080191A4(arg0, (*(u8 *)((u8 *)(temp_r1) + 0x4E)));
        }
        var_r5 += 0x18;
        var_r6 += 1;
    } while (var_r6 <= 2U);
}

void sub_0801B69C(s32 arg0) {
    s32 temp_r2;
    u8 *temp_r1;
    struct ResultRecord *temp_r4;
    u8 *setup;

    setup=gSetupBuffer_03000590;
    temp_r2 = arg0 << 8;
    temp_r4 = (void *)((u32)temp_r2 + (u32)setup);
    if (((*(u8 *)((u8 *)(temp_r4) + 0xC9)) == 0x2C) && ((temp_r1 = &setup[(((*(u8 *)((u8 *)(temp_r4) + 0xDD)) - 1) * 0x18) + temp_r2], ((u32) (*(u8 *)((u8 *)(temp_r1) + 0x4A)) <= 3U)) || ((*(u8 *)((u8 *)(temp_r1) + 0x49)) == 0x34))) {
        temp_r4->first = (u8) (sub_0801B700(arg0) + 1);
        temp_r4->second = (s8) (sub_080330E8(temp_r4->first - 1) + 1);
    }
}

void sub_080385D0(s32 arg0) {
    u32 var_r2;
    u8 *var_r1;
    s32 key;
    u32 zero;

    var_r2 = 0;
    var_r1 = gState0TransferWork.bytes;
    key=arg0+1;
    zero=0;
    var_r1 += 0x45;
    do {
        if ((*(u8 *)((u8 *)(var_r1) + 0)) == key) {
            (*(u8 *)((u8 *)(var_r1) + 0)) = zero;
            (*(s8 *)((u8 *)(var_r1) + 1)) = zero;
        }
        var_r1 += 2;
        var_r2 += 1;
    } while (var_r2 <= 5U);
}

s32 sub_08039134(s32 arg0) {
    s32 var_r3;
    u32 var_r2;
    u8 *var_r1;

    var_r3 = 0;
    var_r2 = 0;
    var_r1 = gSetupBuffer_03000590;
    arg0 <<= 8;
    var_r1 += 0x59;
    var_r1 += arg0;
    do {
        if (*var_r1 != 0) {
            var_r3 += 1;
        }
        var_r1 += 0x18;
        var_r2 += 1;
    } while (var_r2 <= 3U);
    return var_r3;
}

void sub_0805B530(s32 arg0, s32 arg1, s32 arg2) {
    s16 *var_r1;
    u16 var_r0;

    arg0 *= 2;
    arg0 += 0x0600B000;
    arg1 <<= 6;
    var_r1 = (s16 *)(arg0 + arg1);
    var_r0 = 0;
    if ((s32)var_r0 < arg2) {
        do {
            *var_r1 = 0;
            var_r1 += 1;
            var_r0 += 1;
        } while ((s32) var_r0 < arg2);
    }
}
