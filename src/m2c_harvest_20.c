/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "frame_objects.h"
#include "input.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

s32 sub_08015BF4(u8);
void sub_08019184(u32, u32);
s32 sub_080191A4(s32, u8);
u8 sub_0807CEC8(u8, s32);

void sub_08016DA4(void);
void sub_08017914(void);
void sub_080191C0(s32 arg0);
void sub_0801928C(s32 arg0);
void sub_0801C298(void);
void sub_08023C50(void);
void sub_08026CBC(void);
s32 sub_08033224(s32 arg0);
s32 sub_08033240(s32 arg0);
s32 sub_080332B4(s32 arg0);
s32 sub_080332D0(s32 arg0);

void sub_08016DA4(void) {
    u8 *base0 = (u8 *) gSetupBuffer_03000590;
    u8 var_r1;

    var_r1 = (*(u8 *)((u8 *)((base0 + (gState0TransferWork.bytes[0x80] << 8))) + 0xDD));
    if ((u32) var_r1 > 3U) {
        var_r1 = 0;
    }
    gState0TransferWork.bytes[0x82] = var_r1;
}

void sub_08017914(void) {
    u8 *base0 = (u8 *) gSetupBuffer_03000590;
    if ((*(u8 *)((u8 *)((base0 + (gState0TransferWork.bytes[0x80] << 8))) + 0xC1)) == 0x50) {
        sub_08015BF4(gState0TransferWork.bytes[0x80]);
        return;
    }
    sub_08015BA8((u32) gState0TransferWork.bytes[0x80]);
}

void sub_080191C0(s32 arg0) {
    u8 *base0 = (u8 *) gSetupBuffer_03000590;
    if ((*(u8 *)((u8 *)((base0 + (arg0 << 8))) + 0xA1)) == 0) {
        sub_08019184(arg0, 6);
    }
}

void sub_0801928C(s32 arg0) {
    u8 *base0 = (u8 *) gSetupBuffer_03000590;
    sub_080191A4(arg0, sub_0807CEC8((*(u8 *)((u8 *)((base0 + (arg0 << 8))) + 0xA2)), 0x14));
}

void sub_0801C298(void) {
  u8 new_var2;
  unsigned int new_var;
  gState0TransferWork.bytes[0x9D] += 1;
  if ((gState0TypedWork.bytes[0x89] == 0) && (new_var2 = 1 & gRepeatedKeys))
  {
    gState0TransferWork.bytes[0x9D] = 0x3C;
  }
  new_var = 3U;
  new_var2 = gState0TransferWork.bytes[0x9D];
  if (new_var2 == 0x3C)
  {
    sub_08040CD0(new_var, 1U);
    gState0TransferWork.bytes[0x9C] += 1;
  }
}

void sub_08023C50(void) {
    u8 *base0 = (u8 *) gSetupBuffer_03000590;
    (*(s8 *)((u8 *)((base0 + (gState0TransferWork.bytes[0x88] << 8))) + 0xBF)) = 1;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08026CBC(void) {
    u8 *base0 = (u8 *) gSetupBuffer_03000590;
    if ((*(u8 *)((u8 *)((base0 + (gState0TransferWork.bytes[0x88] << 8))) + 0x59)) == 0) {
        sub_08035234((u32) gState0TransferWork.bytes[0x88]);
    }
    gState0TransferWork.bytes[0xAA] += 1;
}

s32 sub_08033224(s32 arg0) {
    u8 *buffer = gSetupBuffer_03000590;
    u8 *record = buffer + (arg0 << 8);
    if (record[0xC4] != 0)
        return 0;
    return 1;
}

s32 sub_08033240(s32 arg0) {
    u8 *buffer = gSetupBuffer_03000590;
    u8 *record = buffer + (arg0 << 8);
    if (record[0xC9] != 0)
        return 0;
    return 1;
}

s32 sub_080332B4(s32 arg0) {
    u8 *buffer = gSetupBuffer_03000590;
    u8 *record = buffer + (arg0 << 8);
    if (record[0x58] != 0)
        return 1;
    return 0;
}

s32 sub_080332D0(s32 arg0) {
    u8 *buffer = gSetupBuffer_03000590;
    u8 *record = buffer + (arg0 << 8);
    if (record[0xC1] != 0)
        return 1;
    return 0;
}
