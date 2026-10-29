/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "action_scene_data.h"
#include "continued_late_graphics.h"
#include "frame.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"


void sub_08002574(void);
void sub_080191A4(s32 arg0, s32 arg1);
void sub_0801932C(s32 arg0);
void sub_08028034(void);
u8 sub_08034E94(void);
u32 sub_08035590(s32 arg0);
s32 sub_08035DD4(s32 arg0);
void sub_08072B64(void *arg0);
void sub_08072C64(void *arg0);
void sub_08072CA0(void *arg0);
void sub_08072D4C(void *arg0);

void sub_08002574(void) {
  s16 *new_var;
  int new_var2;
  *((s16 *) (((s8 *) ((void *) 0x04000050)) + 0)) = 0;
  *((s16 *) (((s8 *) ((void *) 0x04000050)) + 4)) = 0;
  *((s16 *) (((s8 *) ((void *) 0x04000000)) + 0)) = 0x1260;
  new_var = (s16 *) (((s8 *) ((void *) 0x04000000)) + 0xA);
  new_var2 = 0x5E09;
  *new_var = new_var2;
  gState0TypedWork.bytes[0x85] = 1;
  gUnknown_0300137C = gUnknown_0300137C + 1;
}

void sub_080191A4(s32 arg0, s32 arg1) {
  u8 *new_var;
  s32 var_r0;
  void *temp_r0;
  new_var = gSetupBuffer_03000590;
  temp_r0 = (arg0 << 8) + new_var;
  var_r0 = (*((u8 *) (((s8 *) temp_r0) + 0xBB))) - arg1;
  if (var_r0 < 0)
  {
    var_r0 = 0;
  }
  *((u8 *) (((s8 *) temp_r0) + 0xBB)) = (u8) var_r0;
}

void sub_0801932C(s32 arg0) {
  u8 *new_var;
  void *temp_r0;
  new_var = gSetupBuffer_03000590;
  temp_r0 = ((arg0 << 1) << 7) + new_var;
  if (((u32) (*((u8 *) (((s8 *) temp_r0) + 0xBB)))) > 0x1FU)
  {
    *((u8 *) (((s8 *) temp_r0) + 0xBB)) = 0x1FU;
  }
}

void sub_08028034(void) {
  u8 temp_r0;
  temp_r0 = (gFrameObjects[0x21].scaleX = gFrameObjects[0x21].scaleX + 8);
  if (temp_r0 == 0x40)
  {
    gState0TypedWork.widths.word86 = 0x3C;
    gFrameObjects[0x21].unknown23[4] = 0;
    gState0TransferWork.bytes[0xAA] += 1;
  }
}

u8 sub_08034E94(void) {
  const u8 *new_var;
  new_var = gActionBytePointers_083C6CA8[gState0TransferWork.bytes[0xA8]];
  return new_var[*((u16 *) (((s8 *) (&gState0TransferWork)) + 0xBC))];
}

u32 sub_08035590(s32 arg0) {
  u8 *new_var;
  u32 var_r1;
  u8 temp_r1;
  void *temp_r2;
  new_var = gSetupBuffer_03000590;
  temp_r2 = (arg0 << 8) + new_var;
  temp_r1 = *((u8 *) (((s8 *) temp_r2) + 0x71));
  var_r1 = ((u32) ((0 - temp_r1) | temp_r1)) >> 0x1F;
  if ((*((u8 *) (((s8 *) temp_r2) + 0x89))) != 0)
  {
    var_r1 += 3;
  }
  if ((*((u8 *) (((s8 *) temp_r2) + 0xA1))) != 0)
  {
    var_r1 += 5;
  }
  return var_r1;
}

s32 sub_08035DD4(s32 arg0) {
  int new_var;
  if (((u32) (arg0 + 0xFFFFFED8)) > 0xA8U)
  {
    new_var = 1;
    if (new_var)
    {
      return new_var;
    }
  }
  return 0;
}

void sub_08072B64(void *arg0) {
  u8 *temp_r1;
  unsigned char new_var;
  temp_r1 = *((u8 **) (((s8 *) arg0) + 0x14));
  new_var = (unsigned char) (*temp_r1);
  *((u8 *) (((s8 *) arg0) + 0x6A)) = (u8) new_var;
  *((u8 **) (((s8 *) arg0) + 0x14)) = (u8 *) (temp_r1 + 1);
}

void sub_08072C64(void *arg0) {
  u8 new_var3;
  u8 *temp_r1;
  s8 *new_var2;
  u8 *new_var;
  temp_r1 = *((u8 **) (((s8 *) arg0) + 0x14));
  new_var3 = (u8) (*temp_r1);
  *((u8 *) (((s8 *) arg0) + 0x55)) = new_var3;
  new_var = temp_r1;
  new_var2 = (s8 *) arg0;
  *((u8 **) (new_var2 + 0x14)) = (u8 *) (new_var + 1);
}

void sub_08072CA0(void *arg0) {
  u8 *temp_r1;
  s8 *new_var3;
  u8 *new_var;
  u8 new_var2;
  u8 new_var4;
  temp_r1 = *((u8 **) (((s8 *) arg0) + 0x14));
  new_var4 = *temp_r1;
  new_var = (u8 *) (((s8 *) arg0) + 0x6E);
  new_var3 = ((s8 *) arg0) + 0x14;
  new_var2 = new_var4;
  *new_var = (u8) new_var2;
  *((u8 **) new_var3) = (u8 *) (temp_r1 + 1);
}

void sub_08072D4C(void *arg0) {
  u8 *temp_r1;
  u8 new_var;
  temp_r1 = *((u8 **) (((s8 *) arg0) + 0x14));
  new_var = (u8) (*temp_r1);
  *((u8 *) (((s8 *) arg0) + 0x63)) = new_var;
  *((u8 **) (((s8 *) arg0) + 0x14)) = (u8 *) (temp_r1 + 1);
}
