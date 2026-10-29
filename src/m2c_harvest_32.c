/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

s32 sub_08017C50(s32);
s32 sub_0803579C(u8, u8);
s32 sub_08035814(u8);
s32 sub_0803725C();
s32 sub_08037280(u8, u8);

void sub_08017CE8(void);
void sub_08023018(void);
void sub_08023454(void);
void sub_08023AF0(void);
void sub_080240B8(void);
void sub_08026130(void);
void sub_08072B90(void *arg0);

void sub_08017CE8(void) {
    u32 temp_r1;

    temp_r1 = gState0TypedWork.widths.word86 + 1;
    gState0TypedWork.widths.word86 = temp_r1;
    if (temp_r1 & 8) {
        sub_08017C50(0);
        return;
    }
    sub_08017C50(1);
}

void sub_08023018(void) {
    u8 *var_r1;
    u32 var_r0;

    sub_0803579C(gState0TransferWork.bytes[0x87], gState0TransferWork.bytes[0xA7]);
    sub_08035814(gState0TransferWork.bytes[0x87]);
    if (sub_0803725C() != 0) {
        gState0TransferWork.bytes[0xA6] = 0x1A;
        var_r1 = &gState0TransferWork.bytes[0xA6] + 4;
        var_r0 = gState0TransferWork.bytes[0xAA] + 1;
    } else {
        sub_08036270();
        sub_08037280(gState0TransferWork.bytes[0x87], gState0TransferWork.bytes[0xA7]);
        var_r1 = &gState0TransferWork.bytes[0xAA];
        var_r0 = 4;
    }
    *var_r1 = var_r0;
}

void sub_08023454(void) {
    u8 *var_r1;
    u32 var_r0;

    sub_0803579C(gState0TransferWork.bytes[0x87], gState0TransferWork.bytes[0xA7]);
    sub_08035814(gState0TransferWork.bytes[0x87]);
    if (sub_0803725C() != 0) {
        gState0TransferWork.bytes[0xA6] = 0x1A;
        var_r1 = &gState0TransferWork.bytes[0xA6] + 4;
        var_r0 = gState0TransferWork.bytes[0xAA] + 1;
    } else {
        sub_08036270();
        sub_08037280(gState0TransferWork.bytes[0x87], gState0TransferWork.bytes[0xA7]);
        var_r1 = &gState0TransferWork.bytes[0xAA];
        var_r0 = 4;
    }
    *var_r1 = var_r0;
}

void sub_08023AF0(void) {
    u8 *var_r1;
    u32 var_r0;

    sub_0803579C(gState0TransferWork.bytes[0x87], gState0TransferWork.bytes[0xA7]);
    sub_08035814(gState0TransferWork.bytes[0x87]);
    if (sub_0803725C() != 0) {
        gState0TransferWork.bytes[0xA6] = 0x1A;
        var_r1 = &gState0TransferWork.bytes[0xA6] + 4;
        var_r0 = gState0TransferWork.bytes[0xAA] + 1;
    } else {
        sub_08036270();
        sub_08037280(gState0TransferWork.bytes[0x87], gState0TransferWork.bytes[0xA7]);
        var_r1 = &gState0TransferWork.bytes[0xAA];
        var_r0 = 4;
    }
    *var_r1 = var_r0;
}

void sub_080240B8(void) {
    u8 *var_r1;
    u32 var_r0;

    sub_0803579C(gState0TransferWork.bytes[0x87], gState0TransferWork.bytes[0xA7]);
    sub_08035814(gState0TransferWork.bytes[0x87]);
    if (sub_0803725C() != 0) {
        gState0TransferWork.bytes[0xA6] = 0x1A;
        var_r1 = &gState0TransferWork.bytes[0xA6] + 4;
        var_r0 = gState0TransferWork.bytes[0xAA] + 1;
    } else {
        sub_08036270();
        sub_08037280(gState0TransferWork.bytes[0x87], gState0TransferWork.bytes[0xA7]);
        var_r1 = &gState0TransferWork.bytes[0xAA];
        var_r0 = 4;
    }
    *var_r1 = var_r0;
}

void sub_08026130(void) {
    u8 *var_r1;
    u32 var_r0;

    sub_0803579C(gState0TransferWork.bytes[0x87], gState0TransferWork.bytes[0xA7]);
    sub_08035814(gState0TransferWork.bytes[0x87]);
    if (sub_0803725C() != 0) {
        gState0TransferWork.bytes[0xA6] = 0x1A;
        var_r1 = &gState0TransferWork.bytes[0xA6] + 4;
        var_r0 = gState0TransferWork.bytes[0xAA] + 1;
    } else {
        sub_08036270();
        sub_08037280(gState0TransferWork.bytes[0x87], gState0TransferWork.bytes[0xA7]);
        var_r1 = &gState0TransferWork.bytes[0xAA];
        var_r0 = 4;
    }
    *var_r1 = var_r0;
}

void sub_08072B90(void *arg0) {
  int new_var;
  u8 *temp_r1;
  temp_r1 = *((u8 **) (((s8 *) arg0) + 0x14));
  new_var = *temp_r1;
  *((u8 *) (((s8 *) arg0) + 0x6F)) = (u8) new_var;
  *((u8 **) (((s8 *) arg0) + 0x14)) = (u8 *) (temp_r1 + 1);
  new_var = *((u8 *) (((s8 *) arg0) + 0x50));
  *((u8 *) (((s8 *) arg0) + 0x50)) = (u8) (0x40 | new_var);
}
