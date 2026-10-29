/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "display_effects.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s8 sub_08074CE0();
extern u8 gUnknown_083AD06A[];
extern u8 gUnknown_083AFDF8[];

void sub_0803D71C(void);
void sub_0803E83C(void);
void sub_08065790(void);

void sub_0803D71C(void) {
    gState0TransferWork.bytes[0x38] = gUnknown_083AFDF8[sub_080424B8() & 0x1F];
    gUnknown_0300137C += 1;
}

void sub_0803E83C(void) {
    u8 *var_r4;
    u32 var_r5;
    var_r5 = 0;
    var_r4 = gUnknown_083AD06A;
    do {
        sub_080435B0(0xFFU, var_r4[0], var_r4[1], *(u16 *)0x04000008, 0x8300U);
        var_r4 += 2;
        var_r5 += 1;
    } while (var_r5 <= 2U);
}

void sub_08065790(void) {
    s32 zero;
    s8 value;
    s8 *field;
    value = sub_08074CE0();
    field = (s8 *) gMainContextPointer_03006F74 + 0x7F;
    zero = 0;
    *field = value;
    sub_0803FAA0(1U, 0U, 0U);
    (*(s32 *)((u8 *)(gMainContextPointer_03006F74) + 8)) = zero;
    gUnknown_0300137C += 1;
}
