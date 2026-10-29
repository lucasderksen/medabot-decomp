/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "compression.h"
#include "continued_commands.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s32 gContinuedWork_030057E0;
extern s32 gState0NextCommands_083B6100;
extern s32 gUnknown_0850F8F8;
extern u8 gUnknown_084CE3E8;
s32 sub_0803556C();
s32 sub_08037330(u8, u8, s32);
s32 sub_0806C3A0();
s32 sub_0806C88C();
s32 sub_0806C958();
s32 sub_0806CF7C();
s32 sub_0806CFEC();
s32 sub_0806D138();
s32 sub_080701F8();

void sub_08020FB8(void);
void sub_080219C0(void);
void sub_08022990(void);
void sub_08023564(void);
void sub_080235AC(void);
void sub_080235E8(void);
void sub_08023988(void);
void sub_08023C18(void);
void sub_08023E18(void);
void sub_08023F80(void);
void sub_08026628(void);
void sub_080272EC(void);
void sub_0802DFE8(void);
void sub_08030354(void);
unsigned int sub_080330E8(void);
void sub_08038804(void);
void sub_0803E9BC(void);
void sub_0804C444(void);
void sub_0806BC94(void);
void sub_0806BCC4(void);
void sub_0806F914(void);
void sub_080727D0(void *arg0);
void sub_08072B20(void *arg0, u32 arg1);
void sub_08072B50(void *arg0, s8 arg1);
void sub_08072BB8(void *arg0);

void sub_08020FB8(void) {
    u8 *work0;
    LeDecompress(&gUnknown_084CE3E8, (void *)0x06014800);
    CpuFastSet(&gUnknown_0850F8F8, (void *)0x050002E0, 8U);
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040B90((*(u8 **)((u8 *)(work0) + 0x8C)), 0x21U);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_080219C0(void) {
    u8 *work0;
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0xE4)), 0x21U);
    if (gFrameObjects[0x21].commandStopped == 0xFF) {
        sub_08040B90((*(u8 **)((u8 *)(work0) + 0xEC)), 0x21U);
        gState0TypedWork.widths.word86 = 0x3C;
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_08022990(void) {
    u8 *work0;
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0xF8)), 0x21U);
    if (sub_080355F0(0x21U) != 0) {
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_08023564(void) {
    u8 *work0;
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0x100)), 0x21U);
    if (gFrameObjects[0x21].commandStopped == 0xFF) {
        gState0TypedWork.widths.word86 = 0x3C;
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_080235AC(void) {
    u8 *work0;
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040B90((*(u8 **)((u8 *)(work0) + 0x104)), 0x21U);
    sub_08074DE0(0x4DU);
    gState0TypedWork.bytes[0x84] = 0;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_080235E8(void) {
    u8 *work0;
    gState0TypedWork.bytes[0x84] += 1;
    sub_08037330(gState0TransferWork.bytes[0x87], gState0TypedWork.bytes[0x84], 2);
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0x104)), 0x21U);
    if (gFrameObjects[0x21].commandStopped == 0xFF) {
        sub_08040CD0(0x21U, 1U);
        gState0TypedWork.widths.word86 = 0x3C;
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_08023988(void) {
    u8 *work0;
    gState0TypedWork.bytes[0x84] = 0x43;
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040B90((*(u8 **)((u8 *)(work0) + 0x10C)), 0x21U);
    sub_08074DE0(0x4EU);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08023C18(void) {
    u8 *work0;
    gState0TypedWork.bytes[0x84] = 0x46;
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040B90((*(u8 **)((u8 *)(work0) + 0x118)), 0x21U);
    sub_08074DE0(0x4EU);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08023E18(void) {
    u8 *work0;
    gState0TypedWork.bytes[0x84] = 0x44;
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040B90((*(u8 **)((u8 *)(work0) + 0x110)), 0x21U);
    sub_08074DE0(0x4EU);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08023F80(void) {
    u8 *work0;
    gState0TypedWork.bytes[0x84] = 0x43;
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040B90((*(u8 **)((u8 *)(work0) + 0x10C)), 0x21U);
    sub_08074DE0(0x4EU);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08026628(void) {
    u8 *work0;
    if (gState0TypedWork.widths.word86 == 0x5A) {
        gState0TransferWork.bytes[0xAA] += 1;
        return;
    }
    gState0TypedWork.widths.word86 += 1;
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0x12C)), 0x21U);
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0x130)), 0x22U);
}

void sub_080272EC(void) {
    u8 *work0;
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0x168)), 0x21U);
    if (gFrameObjects[0x21].commandStopped == 0xFF) {
        gState0TypedWork.widths.word86 = 0;
        sub_08074DE0(0x73U);
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_0802DFE8(void) {
    u8 *work0;
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040B90((*(u8 **)((u8 *)(work0) + 0x1A4)), 0x21U);
    gState0TransferWork.bytes[0xAA] = 4;
}

void sub_08030354(void) {
    u8 *work0;
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0x1BC)), 0x25U);
    if (gFrameObjects[0x25].commandStopped == 0xFF) {
        gState0TypedWork.widths.word86 = 0;
        sub_08040CD0(0x25U, 1U);
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

unsigned int sub_080330E8(void) {
  sub_0803556C();
}

void sub_08038804(void) {
    u8 *work0;
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0x1B0)), gState0TypedWork.bytes[0x12F]);
    if (gFrameObjects[gState0TypedWork.bytes[0x12F]].commandStopped == 0xFF) {
        sub_08040CD0(gState0TypedWork.bytes[0x12F], 1U);
    }
}

void sub_0803E9BC(void) {
    u8 *work0;
    sub_08040CD0(4U, 1U);
    gFrameObjects[4].flags = 0xC400;
    gFrameObjects[4].screenX = 0x9A;
    gFrameObjects[4].screenY = 0x58;
    gFrameObjects[4].tableSelector = 0;
    gFrameObjects[4].priority = 0x80;
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040B90((*(u8 **)((u8 *)(work0) + 0x1C0)), 4U);
}

void sub_0804C444(void) {
    u8 *work0;
    u16 temp_r5;

    work0 = (u8 *) &gContinuedWork_030057E0;
    temp_r5 = (*(u16 *)((u8 *)(work0) + 0xC8A));
    (*(u16 *)((u8 *)(work0) + 0xC8A)) = (u16) ((*(u16 *)((u8 *)(work0) + 0xC8A)) + sub_080532D4((u32) (*(u16 *)((u8 *)(work0) + 0xC8E))));
    (*(u16 *)((u8 *)(work0) + 0xC8A)) = (u16) (temp_r5 + (u8) sub_0804D83C());
}

void sub_0806BC94(void) {
    u8 *work0;
    sub_0806CFEC();
    if (sub_0806C88C() != 0) {
        work0 = (u8 *) &gBackgroundState_03005310;
        (*(s8 *)((u8 *)(work0) + 0x39)) = 1;
        sub_080750F0(0x30U);
        gUnknown_0300137C = 8;
    }
}

void sub_0806BCC4(void) {
    u8 *work0;
    sub_0806C3A0();
    sub_0806D138();
    sub_0806CF7C();
    if (sub_0806C958() != 0) {
        work0 = (u8 *) &gBackgroundState_03005310;
        (*(s8 *)((u8 *)(work0) + 0x39)) = 2;
        sub_080750F0(0x30U);
        gUnknown_0300137C = 8;
    }
}

void sub_0806F914(void) {
    u8 *work0;
    if (sub_080701F8() != 0) {
        work0 = (u8 *) &gState0TransferWork;
        (*(s32 *)((u8 *)(work0) + 8)) = 0;
        (*(s16 *)((u8 *)(work0) + 4)) = 0xA;
        (*(s16 *)((u8 *)(work0) + 0xC)) = 0x11;
    }
}

void sub_080727D0(void *arg0) {
  int new_var;
  u8 var_r0;
  s8 *var_r1;
  if ((*((u8 *) (((s8 *) arg0) + 0x58))) != 0)
  {
    var_r1 = arg0 + 0x59;
    var_r0 = *((u8 *) (((s8 *) arg0) + 0x59));
    if ((var_r0 != 0) || ((*((s32 *) (((s8 *) arg0) + 0x38)) = (s32) ((*((s32 *) (((s8 *) arg0) + 0x38))) + (*((s32 *) (((s8 *) arg0) + 0x34)))), *((u8 *) (((s8 *) arg0) + 0x50)) = (u8) (new_var = 1 | (*((u8 *) (((s8 *) arg0) + 0x50)))), var_r1 = arg0 + 0x5A, var_r0 = *((u8 *) (((s8 *) arg0) + 0x5A)), var_r0 != 0)))
    {
      *var_r1 = var_r0 - 1;
      return;
    }
    *((u8 *) (((s8 *) arg0) + 0x5A)) = (u8) (*((u8 *) (((s8 *) arg0) + 0x57)));
    *((s32 *) (((s8 *) arg0) + 0x34)) = (s32) (0 - (*((s32 *) (((s8 *) arg0) + 0x34))));
  }
}

void sub_08072B20(void *arg0, u32 arg1) {
  u8 *new_var;
  u8 new_var2;
  *((s8 *) (((s8 *) arg0) + 0x69)) = arg1;
  ;
  new_var2 = (u8) (0x51 | (*((u8 *) (((s8 *) arg0) + 0x50))));
  *((u8 *) (((s8 *) arg0) + 0x50)) = new_var2;
}

void sub_08072B50(void *arg0, s8 arg1) {
  int new_var;
  *((s8 *) (((s8 *) arg0) + 0x67)) = arg1;
  new_var = 4 | (*((u8 *) (((s8 *) arg0) + 0x50)));
  *((u8 *) (((s8 *) arg0) + 0x50)) = (u8) new_var;
}

void sub_08072BB8(void *arg0) {
  u8 *temp_r1;
  u8 *temp_r1_2;
  u8 new_var;
  temp_r1 = *((u8 **) (((s8 *) arg0) + 0x14));
  temp_r1_2 = temp_r1;
  new_var = *temp_r1_2;
  *((u8 *) (((s8 *) arg0) + 0x52)) = (u8) new_var;
  temp_r1_2 = temp_r1 + 1;
  *((u8 **) (((s8 *) arg0) + 0x14)) = temp_r1_2;
  *((u8 **) (((s8 *) arg0) + 0x18)) = temp_r1_2;
}
