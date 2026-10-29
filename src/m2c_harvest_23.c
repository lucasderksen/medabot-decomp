/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_commands.h"
#include "continued_late_graphics.h"
#include "frame.h"
#include "frame_objects.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s32 gContinuedWork_030057E0;
extern s32 gState0NextCommands_083B6100;
s32 sub_08015960(u32, s32, s32);
u32 sub_08016154(u32, s32);
s32 sub_0801AEB4();
s32 sub_0801AEF4();
s32 sub_0801AFB8(u8);
s32 sub_0801C2F0(s32);
s32 sub_080700C8();
s32 sub_08070108();
s32 sub_080701F8();
s32 sub_0807CF40(u32, s32);

void sub_080159BC(void);
u32 sub_08016138(s32 arg0);
void sub_0801FF9C(void);
void sub_08021B78(void);
void sub_0802A31C(void);
void sub_0802AE88(void);
void sub_0802AF6C(void);
void sub_0802F594(void);
void sub_0803185C(void);
void sub_0804D024(void);
void sub_0806F21C(void);
void sub_0806F578(void);
void sub_08072AFC(void *arg0, u8 arg1);
void sub_08072B74(void *arg0);

void sub_080159BC(void) {
    u8 *late0;
    s32 var_r5;
    u32 var_r4;

    var_r4 = 0;
    do {
        late0 = (u8 *) gSetupBuffer_03000590;
        if ((*(u8 *)((u8 *)((late0 + (var_r4 << 8))) + 0x40)) != 0) {
            var_r5 = 0xC8;
            if (var_r4 <= 2U) {
                var_r5 = 0x28;
            }
            sub_08015960(var_r4, var_r5, (sub_0807CF40(var_r4, 3) * 0x18) + 0x24);
        }
        var_r4 += 1;
    } while (var_r4 <= 5U);
}

u32 sub_08016138(s32 arg0) {
  u32 var_r4;
  u32 result;
  var_r4 = 0;
  do
  {
    result = sub_08016154(var_r4, arg0);
    var_r4 += 1;
  }
  while (var_r4 <= 5U);
  return result;
}

void sub_0801FF9C(void) {
    u8 *work0;
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0x88)), 0x21U);
    if (gFrameObjects[0x21].commandStopped == 0xFF) {
        sub_08040CD0(0x21U, 1U);
        sub_08040D0C((u8) ((u32) ((gState0TransferWork.bytes[0x51] << 0x1A) + 0x5A000000) >> 0x18), 4U);
        sub_08040D0C((u8) (gState0TransferWork.bytes[0x51] + 0x72), 1U);
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_08021B78(void) {
    u8 *work0;
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0xE8)), 0x21U);
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0xE8)), 0x22U);
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0xE8)), 0x23U);
    if (gFrameObjects[0x21].commandStopped == 0xFF) {
        sub_08040D0C(0x21U, 3U);
        gState0TypedWork.widths.word86 = 0x3C;
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_0802A31C(void) {
    u8 *work0;
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0x184)), 0x21U);
    if (gFrameObjects[0x21].commandStopped == 0xFF) {
        sub_08040CD0(0x21U, 1U);
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_0802AE88(void) {
    u8 *work0;
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0x190)), 0x21U);
    if (gFrameObjects[0x21].commandStopped == 0xFF) {
        sub_08040CD0(0x21U, 1U);
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_0802AF6C(void) {
    u8 *work0;
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0x194)), 0x21U);
    if (gFrameObjects[0x21].commandStopped == 0xFF) {
        sub_08040CD0(0x21U, 1U);
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_0802F594(void) {
    u8 *work0;
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0x1A0)), 0x21U);
    if (gFrameObjects[0x21].commandStopped == 0xFF) {
        sub_08040CD0(0x21U, 1U);
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_0803185C(void) {
    u8 *work0;
    sub_0801C2F0(0);
    sub_0801AFB8(gState0TransferWork.bytes[0x87]);
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0x134)), 0x21U);
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0x138)), 0x22U);
    if (gFrameObjects[0x21].commandStopped == 0xFF) {
        sub_0801AEF4();
        sub_0801AEB4();
        sub_08040CD0(0x21U, 2U);
        gUnknown_0300137C += 1;
    }
}

void sub_0804D024(void) {
    u8 *work0;
    sub_0804D8CC(3U);
    work0 = (u8 *) &gContinuedWork_030057E0;
    sub_080533E4((u32) (*(u8 *)((u8 *)(work0) + 0xC94)), ((0x7F & (*(u8 *)((u8 *)(work0) + 0xC95))) * 0x10) + (*(u16 *)((u8 *)(work0) + 0xC48)), ((0x7F & (*(u8 *)((u8 *)(work0) + 0xC96))) * 0x10) + (*(u16 *)((u8 *)(work0) + 0xC4A)), 0U);
    (*(s8 *)((u8 *)(work0) + 0xC89)) = 1;
}

void sub_0806F21C(void) {
    u8 *work0;
    if (sub_080701F8() != 0) {
        work0 = (u8 *) &gState0TransferWork;
        (*(s32 *)((u8 *)(work0) + 8)) = 0;
        (*(s16 *)((u8 *)(work0) + 4)) = 7;
        (*(s16 *)((u8 *)(work0) + 0xC)) = 0xC;
    }
}

void sub_0806F578(void) {
    u8 *work0;
    if (sub_080701F8() != 0) {
        sub_080700C8();
        sub_08070108();
        work0 = (u8 *) &gState0TransferWork;
        (*(s32 *)((u8 *)(work0) + 8)) = 0;
        (*(s16 *)((u8 *)(work0) + 4)) = 7;
        (*(s16 *)((u8 *)(work0) + 0xC)) = 0xE;
    }
}

void sub_08072AFC(void *arg0, u8 arg1) {
  u8 temp_r1;
  int new_var;
  temp_r1 = arg1;
  *(((s8 *) arg0) + 0x65) = temp_r1;
  *((u8 *) (((s8 *) (arg0 + 0x65)) + 1)) = temp_r1;
  new_var = 2 | (*((u8 *) (((s8 *) arg0) + 0x50)));
  *((u8 *) (((s8 *) arg0) + 0x50)) = (u8) new_var;
}

void sub_08072B74(void *arg0) {
  u8 *temp_r1;
  u8 new_var;
  temp_r1 = *((u8 **) (((s8 *) arg0) + 0x14));
  new_var = (u8) (*temp_r1);
  *((u8 *) (((s8 *) arg0) + 0x6B)) = new_var;
  *((u8 **) (((s8 *) arg0) + 0x14)) = (u8 *) (temp_r1 + 1);
  if (((u32) (*((u8 *) (((s8 *) arg0) + 0x6B)))) > 0x30U)
  {
    *((u8 *) (((s8 *) arg0) + 0x6B)) = 0x30U;
  }
}
