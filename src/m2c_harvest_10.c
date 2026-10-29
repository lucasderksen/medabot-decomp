/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s32 gState0FrameBackup;
extern void *gUnknown_03007014;
extern u32 gUnknown_03006F80;
s32 sub_0801ABF8();
s32 sub_0801AEB4();
s32 sub_0801AEF4();
s32 sub_0801AF6C(u8);
s32 sub_0801B0E8(u8);
s32 sub_0801C0BC(s32);
s32 sub_0801C2F0(s32);
void sub_0803EA38(void);
s32 sub_0803EAD8();
s32 sub_08068888();
s32 sub_080733BC(s32, s32);
s32 sub_080734F4(s32, s32);
s32 sub_08073810(s32, s32);
void sub_08073A48(s32);
void sub_0807490C(void *);
s32 sub_080751E4(s32, s32);

void sub_0801C0F8(void);
void sub_08025E88(void);
void sub_08030D58(void);
void sub_08030D90(void);
void sub_08030E14(void);
void sub_0803EB0C(void);
void sub_0803ECF0(void);
void sub_080606A8(void);
void sub_08068E88(void);
void sub_080737E8(void *channel);
void sub_080739C4(s32 arg0);
void sub_080739DC(s32 arg0);
void sub_08073A88(void);
void sub_0807495C(void *arg0);

void sub_0801C0F8(void) {
    sub_0801ABF8();
    gState0TransferWork.bytes[0xA1] += 1;
}

void sub_08025E88(void) {
    s32 var_r4;

    sub_0801C2F0(0);
    var_r4 = sub_0801AF6C(gState0TransferWork.bytes[0x87]);
    if (0x8000 & gFrameObjects[0x21].flags) {
        gFrameObjects[0x21].flags |= 0x220;
        if (gFrameObjects[0x21].scaleX == 1) {
            sub_08040CD0(0x21U, 1U);
        } else {
            gFrameObjects[0x21].scaleX -= 1;
            gFrameObjects[0x21].scaleY -= 1;
        }
    } else {
        var_r4 += 1;
    }
    if (var_r4 == 2) {
        sub_0801AEF4();
        sub_0801AEB4();
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_08030D58(void) {
    if (sub_0801C0BC(0) != 0) {
        gUnknown_0300137C += 1;
    }
}

void sub_08030D90(void) {
    sub_0801C2F0(0);
    if (sub_0801C0BC(1) != 0) {
        gUnknown_0300137C += 1;
    }
}

void sub_08030E14(void) {
    s32 temp_r5;

    sub_0801C2F0(0);
    temp_r5 = sub_0801AF6C(gState0TransferWork.bytes[0x87]);
    if ((temp_r5 + sub_0801B0E8(gState0TransferWork.bytes[0x87])) == 2) {
        sub_0801AEF4();
        sub_0801AEB4();
        gUnknown_0300137C += 1;
    }
}

void sub_0803EB0C(void) {
    if (4 & gState0TypedWork.widths.word86) {
        sub_0803EA38();
        return;
    }
    sub_0803EAD8();
}

void sub_0803ECF0(void) {
    if (gState0TransferWork.bytes[0x1A0] == 0x60) {
        sub_08074DE0(7U);
    }
}

void sub_080606A8(void) {
    s32 sp0;

    CpuFastSet((void *)0x06002800, &gState0FrameBackup, 0x28U);
    sp0 = 0;
    CpuFastSet(&sp0, (void *)0x06002800, 0x01000200U);
    sub_080415BC();
    sub_08059E50();
    (*(s16 *)((u8 *)((void *)0x04000000) + 0)) = 0x60;
    (*(s16 *)((u8 *)((void *)0x04000000) + 0x50)) = 0x2FF;
    (*(s16 *)((u8 *)(((void *)0x04000000 + 0x50)) + 4)) = 0x10;
    gUnknown_0300137C += 1;
}

void sub_08068E88(void) {
    if (sub_08068888() != 0) {
        gUnknown_0300137C = gUnknown_03006F80;
    }
}

void sub_080737E8(void *channel) {
    sub_080733BC((s32)(u32)channel, 0x04000078);
    sub_080734F4((s32)(u32)channel, 0x0400007C);
    sub_08073604(channel);
}

void sub_080739C4(s32 arg0) {
    sub_08073810(arg0, (s32)((u32)gUnknown_03007014 + 0x690U));
}

void sub_080739DC(s32 arg0) {
    sub_08073810(arg0, (s32)((u32)gUnknown_03007014 + 0x6D8U));
}

void sub_08073A88(void) {
    *(s16 *)0x04000084 = 0x80;
    *(s16 *)0x04000082 = 0x400E;
    *(s16 *)0x04000070 = 0xC0;
    sub_08073A48(0);
    sub_080751E4(7, 7);
}

void sub_0807495C(void *arg0) {
    if ((*(s32 *)((u8 *)(arg0) + 0x14)) != 0) {
        sub_0807490C(arg0);
        (*(s32 (**)())((u8 *)(arg0) + 0xC))();
    }
}
