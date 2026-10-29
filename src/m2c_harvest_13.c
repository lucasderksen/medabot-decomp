/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "dialogue_messages.h"
#include "background_state.h"
#include "continued_late_graphics.h"
#include "display_effects.h"
#include "display_helpers.h"
#include "effect_work.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "main.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s32 gState0NextCommands_083B6100;
extern s32 gUnknown_0300198A;
extern void *gUnknown_03007014;
s16 sub_0807CD2C(s16, s32);
s32 sub_080158D0(u8);
s32 sub_08019108(s32);
s32 sub_080191C0(s32);
s32 sub_080191E4(s32);
s32 sub_0801922C(s32);
s32 sub_08019264(s32);
s32 sub_0801928C(s32);
s32 sub_080192B8(s32);
s32 sub_080192E8(s32);
s32 sub_0801932C(s32);
s32 sub_08035F20();
s32 sub_0803D4AC();
s32 sub_0803E894();
s32 sub_0803ED6C();
void sub_08066D8C(void);
s32 sub_0806E484();
s32 sub_08072734(s32);
s32 sub_08073718(void *);
s32 sub_08073C3C(void *, s32);
s32 sub_08073D70(void *, s32);
s32 sub_08073DB8(void *, s32, s32, s32, s32, s32, s32, s32);
s32 sub_08073DF4();
s32 sub_08074540();
s32 sub_0807CEC8(s32, s32);
u32 sub_08075130();

void sub_080190B8(s32 arg0);
s32 sub_0801AF6C(u32 arg0);
s32 sub_0801AFB8(u32 arg0);
void sub_0801EB5C(void);
void sub_080206E8(void);
void sub_08021000(void);
void sub_0802494C(void);
void sub_08030990(void);
void sub_080310A0(void);
void sub_08031218(void);
void sub_080315B0(void);
void sub_080318CC(void);
void sub_08031994(void);
void sub_08036370(s32 arg0, s32 arg1);
void sub_08039540(void);
void sub_0803D9A0(void);
void sub_0803DBB8(void);
void sub_0803E1FC(void);
void sub_0803E634(void);
void sub_08067B28(void);
void sub_0806E4CC(void);
void sub_08073E24(void *arg0);
void sub_08074780(void);

void sub_080190B8(s32 arg0) {
  u8 *new_var;
  new_var = gSetupBuffer_03000590;
  *((s8 *) (((s8 *) ((arg0 << 8) + new_var)) + 0xBB)) = 0;
  sub_08019108(arg0);
  sub_080191C0(arg0);
  sub_080191E4(arg0);
  sub_0801922C(arg0);
  sub_08019264(arg0);
  sub_0801928C(arg0);
  sub_080192B8(arg0);
  sub_080192E8(arg0);
  sub_0801932C(arg0);
}

s32 sub_0801AF6C(u32 arg0) {
  u8 temp_r0_2;
  int new_var;
  u8 *new_var2;
  void *temp_r0;
  if (gState0TransferWork.bytes[0x51] != 0)
  {
    new_var2 = gSetupBuffer_03000590;
    temp_r0 = (arg0 << 8) + new_var2;
    temp_r0_2 = *((u8 *) (((s8 *) temp_r0) + 0xC1));
    new_var = 0x50;
    if (temp_r0_2 != new_var)
    {
      *((u8 *) (((s8 *) temp_r0) + 0xC1)) = (u8) (temp_r0_2 + 1);
      gState0TransferWork.bytes[0x51] -= 1;
      sub_08015C40(arg0);
      sub_08015E68(arg0);
      return 0;
    }
  }
  return 1;
}

s32 sub_0801AFB8(u32 arg0) {
  u8 temp_r0_2;
  void *temp_r0;
  u8 *new_var;
  if (gState0TransferWork.bytes[0x51] != 0)
  {
    new_var = gSetupBuffer_03000590;
    temp_r0 = (arg0 << 8) + new_var;
    temp_r0_2 = *((u8 *) (((s8 *) temp_r0) + 0xC1));
    if (temp_r0_2 != 0)
    {
      *((u8 *) (((s8 *) temp_r0) + 0xC1)) = (u8) (temp_r0_2 - 1);
      gState0TransferWork.bytes[0x51] -= 1;
      sub_08015C40(arg0);
      sub_08015E68(arg0);
      return 0;
    }
  }
  return 1;
}

void sub_0801EB5C(void) {
  struct 
  {
    u8 unknown00[0x5C];
    u16 word5C;
    u8 unknown5E[0x28];
    u16 word86;
  } *new_var2;
  int new_var;
  s32 *new_var3;
  new_var = 0xFF;
  new_var3 = &gState0NextCommands_083B6100;
  sub_08040BD8(*((u8 **) (((s8 *) new_var3) + 0x78)), 0xAU);
  if (gFrameObjects[0xA].commandStopped == new_var)
  {
    sub_08040CD0(0xAU, 1U);
    gState0TransferWork.bytes[0xAA] += 1;
  }
  new_var2 = (void *) &gState0TypedWork.widths;
  if ((*new_var2).word86 == 0x12)
  {
    sub_08035F20();
  }
  gState0TypedWork.widths.word86 += 1;
}

void sub_080206E8(void) {
  int new_var;
  new_var = 0x88;
  sub_08040BD8(*((u8 **) (((s8 *) (&gState0NextCommands_083B6100)) + new_var)), 0x21U);
  if (gFrameObjects[0x21].commandStopped == 0xFF)
  {
    sub_08040CD0(0x21U, 1U);
    gState0TransferWork.bytes[0xAA] += 1;
  }
}

void sub_08021000(void) {
  s8 *new_var;
  new_var = (s8 *) (&gState0NextCommands_083B6100);
  sub_08040BD8(*((u8 **) (new_var + 0x8C)), 0x21U);
  if (gFrameObjects[0x21].commandStopped == 0xFF)
  {
    gState0TransferWork.bytes[0xAA] += 1;
  }
}

void sub_0802494C(void) {
  s32 *new_var;
  new_var = &gState0NextCommands_083B6100;
  sub_08040BD8(*((u8 **) (((s8 *) new_var) + 0x88)), 0x21U);
  if (gFrameObjects[0x21].commandStopped == 0xFF)
  {
    sub_08040CD0(0x21U, 1U);
    sub_080158D0(gState0TransferWork.bytes[0x88]);
    gState0TransferWork.bytes[0xAA] += 1;
  }
}

void sub_08030990(void) {
  u8 **new_var;
  unsigned int new_var2;
  s32 *new_var3;
  new_var3 = &gState0NextCommands_083B6100;
  new_var = (u8 **) (((s8 *) new_var3) + 0x54);
  sub_08040BD8(*new_var, 3U);
  if (0xFF == gFrameObjects[3].commandStopped)
  {
    new_var2 = 3U;
    sub_08040CD0(new_var2, 1U);
    gUnknown_0300137C += 1;
  }
}

void sub_080310A0(void) {
  const void * const *new_var;
  if (gState0TypedWork.bytes[0x9C] == 1)
  {
    sub_0803F63C(gUnknown_03002B74, &gState0TypedWork.bytes[0x9E], 0xEU);
  }
  else
    if (gState0TypedWork.bytes[0x89] != 1)
  {
    sub_0803F63C(gState0EncounterLabels_083C40B8[gState0TransferWork.bytes[0]], &gState0TypedWork.bytes[0x9E], 0x12U);
  }
  else
  {
    sub_0803F63C(&gUnknown_0300198A, &gState0TypedWork.bytes[0x9E], 0x12U);
  }
  new_var = gState0FixedMessages_083C6744;
  if (sub_0803FB3C(*((void **) (((s8 *) new_var) + 8))) != 0)
  {
    gUnknown_0300137C += 1;
  }
}

void sub_08031218(void) {
  s8 *new_var;
  if (gState0TypedWork.bytes[0x9C] == 1)
  {
    sub_0803F63C(gUnknown_03002B74, &gState0TypedWork.bytes[0x9E], 0xEU);
  }
  else
    if (gState0TypedWork.bytes[0x89] != 1)
  {
    sub_0803F63C(gState0EncounterLabels_083C40B8[gState0TransferWork.bytes[0]], &gState0TypedWork.bytes[0x9E], 0x12U);
  }
  else
  {
    sub_0803F63C(&gUnknown_0300198A, &gState0TypedWork.bytes[0x9E], 0x12U);
  }
  new_var = (s8 *) gState0FixedMessages_083C6744;
  if (sub_0803FB3C(*((void **) (new_var + 0xC))) != 0)
  {
    gUnknown_0300137C += 1;
  }
}

void sub_080315B0(void) {
  u8 *temp_r4;
  u8 *new_var;
  u8 temp_r0;
  sub_0801A574(gUnknown_0300052E, (u32) gState0TransferWork.bytes[0x87], 0x23U);
  temp_r4 = gUnknown_0300052E - 0x6A;
  temp_r0 = (*temp_r4 = (*temp_r4) + 1);
  if (temp_r0 == 0x78)
  {
    sub_08040CD0(0x21U, 2U);
    new_var = gState0TransferWork.bytes;
    sub_08040CD0(((u32) ((new_var[0x87] << 0x1A) + 0x23000000)) >> 0x18, 4U);
    gUnknown_0300137C += 1;
  }
}

void sub_080318CC(void) {
  u8 (*new_var)[0x1B1];
  const void * const *new_var3;
  u8 *new_var2;
  new_var3 = gUnknownPointers_083B74B8;
  new_var2 = gSetupBuffer_03000590;
  new_var = &gState0TransferWork.bytes;
  sub_0803F63C(new_var3[*((u8 *) (((s8 *) (new_var2 + ((*new_var)[0x87] << 8))) + 0xA8))], gDebugMenuTextBuffer, 0x11U);
  gState0TransferWork.bytes[0xA6] = 0x38;
  gUnknown_0300137C += 1;
}

void sub_08031994(void) {
  int new_var;
  new_var = 4;
  if (sub_0803FB3C(*((void **) (((s8 *) (&gUnknownPointers_083CF530)) + new_var))) != 0)
  {
    gUnknown_0300137C += 1;
  }
}

void sub_08036370(s32 arg0, s32 arg1) {
  s32 var_r5;
  void *temp_r4;
  u8 *new_var2;
  s8 *new_var;
  var_r5 = 5;
  if (arg0 == 0)
  {
    var_r5 = 0x13;
  }
  new_var2 = gSetupBuffer_03000590;
  temp_r4 = (arg1 << 8) + new_var2;
  sub_080363E8(var_r5, 1, 0x40, *((u8 *) (((s8 *) ((arg1 << 8) + new_var2)) + 0x4C)), (s32) (*((u8 *) (((s8 *) (temp_r4 + 0x4C)) + 0xD))));
  new_var = ((s8 *) temp_r4) + 0x64;
  sub_080363E8(var_r5, 4, 0x40, *((u8 *) new_var), (s32) (*((u8 *) (((s8 *) (temp_r4 + 0x64)) + 0xD))));
  sub_080363E8(var_r5, 7, 0x40, *((u8 *) (((s8 *) temp_r4) + 0x7C)), (s32) (*((u8 *) (((s8 *) (temp_r4 + 0x7C)) + 0xD))));
  sub_080363E8(var_r5, 0xA, 0x40, *((u8 *) (((s8 *) temp_r4) + 0x94)), (s32) (*((u8 *) (((s8 *) (temp_r4 + 0x94)) + 0xD))));
}

void sub_08039540(void) {
  int new_var;
 do { if (gState0TransferWork.bytes[0xB7] == 1) { new_var = 0xB7; gState0TransferWork.bytes[0xFD] = gState0TransferWork.bytes[new_var]; } else { gState0TransferWork.bytes[0xFD] = 0; } sub_0803D4AC(); } while (0);
}

void sub_0803D9A0(void) {
  s8 *new_var2;
  int new_var;
  sub_08043CD4();
  if (sub_0803FB3C(*((void **) ((new_var2 = (s8 *) gState0MapMessages_083C2D3C) + (new_var = 4)))) != 0)
  {
    gUnknown_0300137C += 1;
  }
}

void sub_0803DBB8(void) {
  const void *const *new_var;
  sub_08043CD4();
  new_var = gUnknownPointers_083CF530;
  if (sub_0803FB3C(*((void **) (((s8 *) new_var) + 4))) != 0)
  {
    gUnknown_0300137C += 1;
  }
}

void sub_0803E1FC(void) {
  s8 *new_var;
  sub_0803E894();
  sub_0803ED6C();
  gState0TypedWork.widths.word86 += 1;
  new_var = (s8 *) (&gUnknownPointers_083CF530);
  if (sub_0803FB3C(*((void **) (new_var + 4))) != 0)
  {
    gUnknown_0300137C += 1;
  }
}

void sub_0803E634(void) {
  s8 *new_var;
  new_var = (s8 *) (&gUnknownPointers_083CF530);
  if (sub_0803FB3C(*((void **) (new_var + 0x30))) != 0)
  {
    gUnknown_0300137C += 1;
  }
}

void sub_08067B28(void) {
  s16 temp_r0;
  u32 temp_r0_2;
  sub_08066D8C();
  ;
  if (((s32) (*((s16 *) (((s8 *) gMainContextPointer_03006F74) + 0x3E)))) <= 0xC0)
  {
    sub_0803F684(0U, (u32) sub_0807CD2C(*((s16 *) (((s8 *) gMainContextPointer_03006F74) + 0x3E)), 6), 0xFFFFU);
    sub_0803F998(0U, (u32) sub_0807CD2C(*((s16 *) (((s8 *) gMainContextPointer_03006F74) + 0x3E)), 6), 0xFFFFU);
    *((s16 *) (((s8 *) gMainContextPointer_03006F74) + 0x3E)) = (s16) (((u16) (*((s16 *) (((s8 *) gMainContextPointer_03006F74) + 0x3E)))) + 1);
    return;
  }
  temp_r0_2 = sub_08075130();
  if (temp_r0_2 == 0)
  {
    gUnknown_0300137C = temp_r0_2;
    sub_080476E8(0xCU);
  }
}

void sub_0806E4CC(void) {
  s8 *new_var;
  if (sub_0806E484() != 0)
  {
    new_var = (s8 *) (&gState0TransferWork);
    *((s32 *) (new_var + 8)) = 0;
    gMainState = (u32) (*((u16 *) (new_var + 0)));
    gMainSubstate = (u32) (*((u16 *) (new_var + 2)));
    gUnknown_0300137C = (u32) (*((u16 *) (new_var + 4)));
  }
}

void sub_08073E24(void *arg0) {
  s32 new_var;
  sub_08073DF4();
  sub_08073DB8(arg0, *((s32 *) (((s8 *) arg0) + 0x1C)), 0x20, *((s32 *) (((s8 *) arg0) + 0x24)), *((s32 *) (((s8 *) arg0) + 0x28)), *((s32 *) (((s8 *) arg0) + 0x2C)), (s32) (*((u8 *) (((s8 *) arg0) + 0x30))), (s32) (*((u8 *) (((s8 *) arg0) + 0x31))));
  sub_08073C3C(arg0, *((s32 *) (((s8 *) arg0) + 0x24)));
  new_var = *((s32 *) (((s8 *) arg0) + 4));
  *((s32 *) (((s8 *) arg0) + 0x10)) = (s32) ((0x10000 - sub_0807CEC8(0x01000000, new_var)) | 0x800000);
  sub_08073D70(arg0, 0);
  sub_08072734(*((s32 *) (((s8 *) arg0) + 0x18)));
}

void sub_08074780(void) {
  int new_var;
  sub_08073718(gUnknown_03007014 + 0x244);
  if (sub_08074540() == 0)
  {
    new_var = 0x5F | (*((u8 *) (((s8 *) gUnknown_03007014) + 0xC4)));
    *((u8 *) (((s8 *) gUnknown_03007014) + 0xC4)) = (u8) new_var;
    sub_08073718(gUnknown_03007014 + 0x74);
  }
}
