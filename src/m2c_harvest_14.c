/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "object_numeric_helpers.h"
#include "state0_work.h"

s32 sub_080191A4(s32, u8);
s8 sub_0807CD2C(s8, s32);
s8 sub_0807CDF8(s8, s32);
u8 sub_0807CEC8(u8, s32);

void sub_08019264(s32 arg0);
void sub_0806D398(void);

void sub_08019264(s32 arg0) {
  u8 *new_var;
  new_var = gSetupBuffer_03000590;
  sub_080191A4(arg0, sub_0807CEC8(*((u8 *) (((s8 *) ((arg0 << 8) + new_var)) + 5)), 0xA));
}

void sub_0806D398(void) {
  unsigned int new_var;
  new_var = 0xC400U;
  sub_08048864(0xBU, 0xC400U, sub_0807CD2C((s8) gState0TransferWork.bytes[0xE], 0xA) + 0x21, 8U, 3U);
  sub_08048864(0xCU, new_var, sub_0807CDF8((s8) gState0TransferWork.bytes[0xE], 0xA) + 0x21, 8U, 3U);
}
