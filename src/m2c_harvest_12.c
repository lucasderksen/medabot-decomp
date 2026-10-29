/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "display_effects.h"
#include "display_helpers.h"
#include "effect_work.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "initialization.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "object_numeric_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s16 gUnknown_030018E8;
extern s32 gState0NextCommands_083B6100;
extern s32 gUnknown_0202F800;
extern void *gUnknown_03007014;
s32 sub_08018D0C(u32);
s32 sub_08018DF4(u32);
s32 sub_08036BF4(s32);
s32 sub_0803E894();
void sub_0803EA38(void);
s32 sub_0803EB0C();
s32 sub_08062B48(u8, u8, s32);
s32 sub_08067C04();
s32 sub_08068460(s32, s32, s32);
s32 sub_0806B718(s32);
s32 sub_0806E10C(s32, s32);
s32 sub_080736A0(void *);
s32 sub_08073784(void *);
void sub_080737E8(void *);
s32 sub_08074540();
s8 sub_0807CEC8(s32, s32);
s8 sub_0807CF40(s32, s32);

void sub_08018CBC(void);
void sub_0801A118(void *arg0, s32 arg1, s32 arg2);
void sub_0801EA94(void);
void sub_0801F290(void);
void sub_08020428(void);
void sub_08020530(void);
void sub_08021638(void);
void sub_08022708(void);
void sub_08035814(s32 arg0);
s32 sub_0803725C(void);
void sub_0803DAEC(void);
void sub_0803DF98(void);
void sub_0803EB30(void);
void sub_0805FA18(void);
void sub_080625F0(void);
void sub_08063208(void);
void sub_08063EBC(void);
void sub_080666C8(void);
void sub_08068328(void);
void sub_0806C660(void);
void sub_0806DCC0(void);
void sub_08071744(void);
void sub_0807474C(void);
void sub_080747B8(void);
void sub_080747F4(void);

void sub_08018CBC(void) {
  u8 *new_var;
  u32 var_r5;
  void *temp_r4;
  gState0TransferWork.bytes[0x55] = 0;
  var_r5 = 0;
  do
  {
    new_var = gSetupBuffer_03000590;
    temp_r4 = (var_r5 << 8) + new_var;
    if ((*((u8 *) (((s8 *) temp_r4) + 0x40))) != 0)
    {
      if ((*((u8 *) (((s8 *) temp_r4) + 0xC4))) != 0)
      {
        sub_08018D0C(var_r5);
      }
      if ((*((u8 *) (((s8 *) temp_r4) + 0xC9))) != 0)
      {
        sub_08018DF4(var_r5);
      }
    }
    var_r5 += 1;
  }
  while (var_r5 <= 5U);
}

void sub_0801A118(void *arg0, s32 arg1, s32 arg2) {
  s8 var_r0;
  if (arg2 != 0)
  {
    var_r0 = var_r0;
    var_r0 = 0xB;
  }
  else
  {
    var_r0 = 0xA;
  }
  *((s8 *) (((s8 *) arg0) + 0)) = var_r0;
  *((s8 *) (((s8 *) arg0) + 1)) = sub_0807CEC8(arg1, 0xA);
  *((s8 *) (((s8 *) arg0) + 2)) = sub_0807CF40(arg1, 0xA);
}

void sub_0801EA94(void) {
  s32 var_r1;
  int new_var;
  new_var = 2 & gState0TransferWork.bytes[0xF8];
  var_r1 = 0;
  if (!new_var)
  {
    var_r1 = 1;
  }
  sub_08036BF4(var_r1);
  gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0801F290(void) {
  int new_var;
  s8 *new_var2;
  new_var2 = (s8 *) (&gState0NextCommands_083B6100);
  sub_08040BD8(*((u8 **) (new_var2 + 0x80)), 0xAU);
  new_var = 0xAA;
  if (gFrameObjects[0xA].commandStopped == 0xFF)
  {
    sub_08040CD0(0xAU, 1U);
    gState0TypedWork.widths.word86 = 0x3C;
    gState0TransferWork.bytes[new_var] += 1;
  }
}

void sub_08020428(void) {
  int new_var;
  new_var = 0x94;
  sub_08040BD8(*((u8 **) (((s8 *) (&gState0NextCommands_083B6100)) + new_var)), 0xAU);
  if (gFrameObjects[0xA].commandStopped == 0xFF)
  {
    gState0TypedWork.widths.word86 = 0x3C;
    sub_08040CD0(0xAU, 1U);
    gState0TransferWork.bytes[0xAA] += 1;
  }
}

void sub_08020530(void) {
  s8 *new_var;
  new_var = (s8 *) (&gState0NextCommands_083B6100);
  sub_08040BD8(*((u8 **) (new_var + 0x98)), 0xAU);
  if (gFrameObjects[0xA].commandStopped == 0xFF)
  {
    gState0TypedWork.widths.word86 = 0x3C;
    sub_08040CD0(0xAU, 1U);
    gState0TransferWork.bytes[0xAA] += 1;
  }
}

void sub_08021638(void) {
  s32 *new_var;
  new_var = &gState0NextCommands_083B6100;
  sub_08040BD8(*((u8 **) (((s8 *) new_var) + 0xE0)), 0x21U);
  if (gFrameObjects[0x21].commandStopped == 0xFF)
  {
    gState0TypedWork.widths.word86 = 0x3C;
    gState0TransferWork.bytes[0xAA] += 1;
  }
}

void sub_08022708(void) {
  s32 *new_var;
  new_var = &gState0NextCommands_083B6100;
  sub_08040BD8(*((u8 **) (((s8 *) new_var) + 0x70)), 0x21U);
  if (gFrameObjects[0x21].commandStopped == 0xFF)
  {
    sub_08040CD0(0x21U, 1U);
    gState0TransferWork.bytes[0xAA] += 1;
  }
}

void sub_08035814(s32 arg0) {
  void *temp_r1;
  temp_r1 = gSetupBuffer_03000590;
  temp_r1 = (arg0 << 8) + temp_r1;
  if (((u32) ((u8) ((*((u8 *) (((s8 *) temp_r1) + 0xC9))) - 0xD))) <= 1U)
  {
    sub_08035754(&gUnknown_030018E8, (s32) (*((u8 *) (((s8 *) temp_r1) + 0xCC))));
  }
}

s32 sub_0803725C(void) {
  int new_var;
  unsigned long long new_var2;
  sub_08035754(&gUnknown_030018E8, 0x20);
  new_var = 0;
  if (gUnknown_030018E8 == new_var)
  {
    new_var2 = 1;
    if (new_var2)
    {
      return new_var2;
    }
  }
  return 0;
}

void sub_0803DAEC(void) {
  int new_var;
  sub_0803F624(gUnknown_03000490, 0x14U, 0U);
  new_var = 0;
  *gUnknown_03000490 = 1;
  gMainSubstate = 3;
  gUnknown_0300137C = new_var;
}

void sub_0803DF98(void) {
  union State0TypedWork *new_var2;
  union State0TypedWork *new_var;
  unsigned long temp_r0;
  u16 var_r0;
  sub_0803E894();
  if (gState0TypedWork.bytes[0x9C] == 1)
  {
    gMainSerialOutgoingWork.word06 = gState0TransferWork.bytes[0x1A0] + 0x8000;
    sub_0803EB0C();
    temp_r0 = gState0TypedWork.widths.word86 + 1;
    gState0TypedWork.widths.word86 = temp_r0;
    temp_r0 = temp_r0;
    var_r0 = temp_r0;
    goto block_4;
  }
  new_var = &gState0TypedWork;
  sub_0803EB0C();
  gState0TypedWork.widths.word86 = (*new_var).widths.word86 + 1;
  new_var2 = new_var;
  if (sub_08041CA4() != 0)
  {
    var_r0 = (*new_var2).widths.word86;
    block_4:
    if (var_r0 == 0x3C)
    {
      sub_08074DE0(0x39U);
      sub_0803EA38();
      gUnknown_0300137C += 1;
    }

  }
}

void sub_0803EB30(void) {
  u8 temp_r0;
  temp_r0 = gState0TransferWork.bytes[0x1A0];
  temp_r0 = (gState0TransferWork.bytes[0x1A1] = 0x68 - temp_r0);
  if (((u32) temp_r0) <= 0xCU)
  {
    gState0TransferWork.bytes[0x1A1] = 0xC;
  }
}

void sub_0805FA18(void) {
  s8 *new_var;
  new_var = (s8 *) gMain2ScriptSlots_0848521C;
  if (sub_0803FB3C(*((void **) (new_var + 0x10))) != 0)
  {
    sub_08074B88(0U);
 ;
    sub_08074DE0(0U);
    Unknown_0805DEB0();
    *((s16 *) (((s8 *) gMainContextPointer_03006F74) + 2)) = 0;
    gUnknown_0300137C += 1;
  }
}

void sub_080625F0(void) {
  const void * const *new_var2;
  new_var2 = gMain2ScriptSlots_0848521C;
  if (sub_0803FB3C(*((void **) (0x1C + ((s8 *) new_var2)))) != 0)
  {
    int new_var;
    new_var = 1;
    gUnknown_0300137C += new_var;
  }
}

void sub_08063208(void) {
  short new_var;
  new_var = 0x258;
  if (sub_08065710(gMainContextPointer_03006F74 + 0x50) != 0)
  {
    gUnknown_0300137C += 1;
    *((s16 *) (((s8 *) gMainContextPointer_03006F74) + 0x3C)) = new_var;
    sub_0803FAA0(1U, 0U, 1U);
  }
  sub_08062B48(*((u8 *) (((s8 *) gMainContextPointer_03006F74) + 0x31)), *((u8 *) (((s8 *) gMainContextPointer_03006F74) + 0x33)), 0);
}

void sub_08063EBC(void) {
  unsigned int new_var;
  s8 *new_var2;
  s8 *new_var3;
  if (0 != sub_08065710(gMainContextPointer_03006F74 + 0x50))
  {
    CpuFastSet((void *) 0x05000200, &gUnknown_0202F800, 0x40U);
    gUnknown_0300137C += 1;
    new_var3 = (new_var2 = ((s8 *) gMainContextPointer_03006F74) + 0x3C);
    new_var = 0x258;
    *((s16 *) new_var3) = new_var;
    sub_0803FAA0(1U, 0U, 1U);
  }
}

void sub_080666C8(void) {
  void **new_var;
  const void * const *new_var2;
  new_var2 = gMain2ScriptSlots_08485678;
  new_var = (void **) (((s8 *) new_var2) + 0x48);
  if (sub_0803FB3C(*new_var) != 0)
  {
    sub_080415E8(1U, 0x16U, 7U);
    gUnknown_0300137C += 1;
  }
}

void sub_08068328(void) {
  s32 temp_r2_2;
  s16 temp_r2;
  u16 temp_r0;
  sub_08067C04();
  temp_r0 = *((u16 *) (((s8 *) gMainContextPointer_03006F74) + 0x3A));
  *((u16 *) (((s8 *) gMainContextPointer_03006F74) + 0x3A)) = (u16) (temp_r0 + 1);
  temp_r2 = (s16) temp_r0;
  temp_r2_2 = temp_r2;
  if (((s32) temp_r2_2) > 0x3B)
  {
    temp_r2_2 = temp_r2 - 0x3C;
    if (temp_r2_2 <= 0x80)
    {
      sub_0803F998(0x7FFFU, 0x20 - (temp_r2_2 >> 2), 1U);
      return;
    }
    sub_0803FB0C();
    gUnknown_0300137C += 1;
  }
}

void sub_0806C660(void) {
  u16 temp_r0;
  if (gFrameObjects[0x38].commandDelay == 1)
  {
    temp_r0 = (gFrameObjects[0x38].unknown1A = gFrameObjects[0x38].unknown1A + 1);
    if (((u32) temp_r0) > 2U)
    {
      sub_0806B718(0x38);
    }
  }
}

void sub_0806DCC0(void) {
  int new_var;
  sub_08068460(4, 2, 0x7FFF);
  *((s16 *) 0x04000054) = 0;
  sub_08074B88(0U);
  sub_08048864(0U, 0xC400U, 0x21BU, 4U, 3U);
  *((u16 *) 0x04000000) |= 0x300;
  gFrameObjects->screenX = 0x78;
  gFrameObjects->screenY = 0x3C;
  gFrameObjects->priority = 0x10;
  sub_0806E10C(0, 0);
  sub_08048864(1U, 0xC400U, 0x210U, 1U, 3U);
  gFrameObjects[1].screenX = 0x78;
  gFrameObjects[1].screenY = 0x55;
  gFrameObjects[1].priority = 0x20;
  sub_0806E10C(0, 1);
  sub_08048864(3U, 0xC000U, 0x213U, 3U, 3U);
  gFrameObjects[3].screenX = 0x12C;
  gFrameObjects[3].screenY = 0x55;
  gFrameObjects[3].priority = 0x40;
  *((s16 *) (((s8 *) gFrameObjects) + 0xF2)) = 0x80;
  sub_0806E10C(7, 3);
  sub_08048864(4U, 0xC400U, 0x21CU, 5U, 3U);
  gFrameObjects[4].screenX = 0x12C;
  gFrameObjects[4].screenY = 0x3C;
  gFrameObjects[4].priority = (double) 0x10;
  *((s16 *) (((s8 *) gFrameObjects) + 0x132)) = 0x80;
  new_var = 4;
  sub_0806E10C(8, 4);
  *((u16 *) 0x04000000) |= 0x1300;
  *((s16 *) (((s8 *) (&gState0TransferWork)) + new_var)) = 7;
  *((s32 *) (((s8 *) (&gState0TransferWork)) + 8)) = 0;
  gUnknown_0300137C = 1;
}

void sub_08071744(void) {
  s8 *new_var;
  if (gFrameObjects[0xA].commandStopped == 0)
  {
    sub_080750F0(0x20U);
    new_var = (s8 *) (&gState0TransferWork);
    *((s16 *) (new_var + 4)) = 0x11;
    gUnknown_0300137C = 2;
  }
}

void sub_0807474C(void) {
  u8 new_var;
  sub_080736A0(gUnknown_03007014 - -0x1D0);
  if (sub_08074540() == 0)
  {
    new_var = (u8) (0x5F | (*((u8 *) (((s8 *) gUnknown_03007014) + 0x50))));
    *((u8 *) (((s8 *) gUnknown_03007014) + 0x50)) = new_var;
    sub_080736A0(gUnknown_03007014);
  }
}

void sub_080747B8(void) {
  int new_var2;
  void *new_var;
  new_var = gUnknown_03007014 + ((unsigned int) 0x2B8);
  sub_08073784(new_var);
  if (sub_08074540() == 0)
  {
    *((u8 *) (((s8 *) gUnknown_03007014) + 0x138)) = (u8) (new_var2 = 0x7F | (*((u8 *) (((s8 *) gUnknown_03007014) + 0x138))));
    sub_08073784(gUnknown_03007014 + ((short) 0xE8));
  }
}

void sub_080747F4(void) {
  int new_var;
  sub_080737E8(gUnknown_03007014 + 0x32C);
  if (sub_08074540() == 0)
  {
    new_var = 0x5F | (*((u8 *) (((s8 *) gUnknown_03007014) + 0x1AC)));
    *((u8 *) (((s8 *) gUnknown_03007014) + 0x1AC)) = (u8) new_var;
    sub_080737E8(gUnknown_03007014 + 0x15C);
  }
}
