/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern struct { u8 b[0x200]; } gCounter6ED08_03001800;
extern u8 gTransferSelectedSlots[];
extern u8 gUnknown_03000491;
extern u8 gUnknown_03001845[];
extern u8 gUnknown_083AF490[];

s32 sub_08007440(u32 arg0);
void sub_0801A5D8(void);
s32 sub_0801B4C8(s32 arg0);
void sub_0801BBC4(void);
u32 sub_080353CC(u32 index);
void sub_08035844(u32 arg0);

s32 sub_08007440(u32 arg0) {

    u32 i;

    if (arg0 == 0) {
        return 1;
    }
    for (i = 0; i < arg0; i++) {
        if ((gTransferSelectedSlots[i] & 0xF) == gUnknown_03000491) {
            return 0;
        }
    }
    return 1;
}

void sub_0801A5D8(void) {

    s32 n;
    s32 m;
    u32 i;
    u32 j;
    u8 *base;
    u8 *a_cur;
    u8 *a_next;
    u8 *k_cur;
    u8 *k_next;
    u8 ta;
    u8 tk;

    n = 5;
    do {
        i = 0;
        m = n - 1;
        while (i < n) {
            base = gUnknown_03001845;
            k_cur = (i * 2 + 1) + base;
            j = i + 1;
            k_next = (j * 2 + 1) + base;
            if ((u32) *k_cur < (u32) *k_next) {
                a_next = (j * 2) + base;
                ta = *a_next;
                tk = *k_next;
                a_cur = (i * 2) + base;
                *a_next = *a_cur;
                *k_next = *k_cur;
                *a_cur = ta;
                *k_cur = tk;
            }
            i = j;
        }
        n = m;
    } while (n != 0);
}

s32 sub_0801B4C8(s32 arg0) {

    s32 var_r3;
    u32 var_r2;
    u8 *var_r1;
    u8 *setup;
    s32 off;

    var_r3 = 0;
    var_r2 = 0;
    setup = gSetupBuffer_03000590;
    off = arg0 << 8;
    var_r1 = setup + 0xBA;
    var_r1 = var_r1 + off;
    do {
        if (*var_r1 == 2) {
            var_r3 += 1;
        }
        var_r1 += 0x100;
        var_r2 += 1;
    } while (var_r2 <= 2U);
    return var_r3;
}

void sub_0801BBC4(void) {

    u32 var_r4;
    u32 var_r6;
    u8 *var_r5;
    u8 *setup;

    var_r4 = 0;
    setup = gSetupBuffer_03000590;
    var_r6 = 0x72000000;
    var_r5 = setup + 0x40;
    do {
        if (*var_r5 != 0) {
            sub_0801BC04(var_r4);
        } else {
            sub_08040D0C((u8) (var_r6 >> 0x18), 1U);
        }
        var_r6 += 0x01000000;
        var_r5 += 0x100;
        var_r4 += 1;
    } while (var_r4 <= 5U);
}

u32 sub_080353CC(u32 index) {

    struct FrameObject *temp_r3;
    struct FrameObject *objs;

    objs = gFrameObjects;
    temp_r3 = &objs[index];
    if (0x8000 & temp_r3->flags) {
        if (temp_r3->unknown23[0] != 0x20) {
            temp_r3->screenY = (u16) temp_r3->screenY + gUnknown_083AF490[temp_r3->unknown23[0]] & 0xFF;
            temp_r3->unknown23[0] += 1;
            return 0U;
        }
    }
    return 1U;
}

void sub_08035844(u32 arg0) {

    u8 *g;
    u16 *p;
    u8 *setup;

    g = gCounter6ED08_03001800.b;
    p = (u16 *)(g + 0xEE);
    setup = gSetupBuffer_03000590;
    *p = *p + setup[(arg0 << 8) + 5];
    *p = *p + sub_0803576C(arg0);
    *p = (sub_080424B8() & 7) + *p;
}
