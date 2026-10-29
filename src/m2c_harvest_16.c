/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_graphics.h"
#include "continued_late_graphics.h"
#include "coordinate_helpers.h"
#include "display_effects.h"
#include "display_helpers.h"
#include "effect_work.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "post_dispatch.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

s32 sub_08035AAC(u8, u8, u8);
s32 sub_08035AFC(u8, u8, u8);
s32 sub_08035B4C(u8, u8, u8);
s32 sub_0803D4AC();
s32 sub_08062B48(u8, u8, s32);
s32 sub_080724B0();
s32 sub_0807266C(s32);
s32 sub_080727D0();
s32 sub_08072818(s32);
s32 sub_08073C84(void *);
s32 sub_0807495C();

void sub_08015F78(void);
void sub_08016068(void);
void sub_080168F4(void);
void sub_0801767C(void);
u32 sub_0801AC24(s32 arg0);
u32 sub_0801AC6C(void);
void sub_080202E0(void);
void sub_080230C8(void);
void sub_08023224(void);
void sub_0802DF48(void);
void sub_0802DF98(void);
void sub_08030FB4(void);
void sub_08030FEC(void);
void sub_08031048(void);
void sub_080319E0(void);
void sub_08035740(u8 *arg0, s32 arg1, u32 arg2);
void sub_080392D8(void);
void sub_08039568(void);
void sub_0803ADE8(void);
void sub_0803D608(void);
void sub_0803E674(void);
void sub_0804AB48(void);
void sub_0804AE78(void);
void sub_0804AF8C(void);
void sub_0804E920(void);
void sub_0804F85C(void);
void sub_080574C8(void);
void sub_08057D7C(void);
void sub_080638E8(void);
s32 sub_080672F4(u8 *arg0);
void sub_08071778(void);
void sub_08072660(void);
void sub_08072BAC(void *arg0);
void sub_08072C34(void *arg0);
void sub_08072D5C(void);
void sub_08072FF4(s32 arg0);
void sub_08073F98(void *arg0);
void sub_08074024(void);

void sub_08015F78(void) {
    u32 var_r4;

    var_r4 = 0;
    do {
        sub_08015F90(var_r4);
        var_r4 += 1;
    } while (var_r4 <= 5U);
}

void sub_08016068(void) {
    u32 var_r4;

    var_r4 = 0;
    do {
        sub_08016080(var_r4);
        var_r4 += 1;
    } while (var_r4 <= 5U);
}

void sub_080168F4(void) {
    switch (gState0TransferWork.bytes[0x82]) {      /* irregular */
    case 0:
        if (8 & gState0TypedWork.bytes[0x84]) {
            sub_08016894(1U);
            return;
        }
        sub_08016894(0U);
        return;
    case 1:
        if (8 & gState0TypedWork.bytes[0x84]) {
            sub_080167BC(1U);
            return;
        }
        sub_080167BC(0U);
        return;
    case 2:
        if (8 & gState0TypedWork.bytes[0x84]) {
            sub_08016804(1U);
            return;
        }
        sub_08016804(0U);
        return;
    case 3:
        if (8 & gState0TypedWork.bytes[0x84]) {
            sub_0801684C(1U);
            return;
        }
        sub_0801684C(0U);
        return;
    }
}

void sub_0801767C(void) {
    switch (gState0TransferWork.bytes[0x82]) {      /* irregular */
    case 0:
        if (8 & gState0TypedWork.bytes[0x84]) {
            sub_08017130(1U);
            return;
        }
        sub_08017130(0U);
        return;
    case 1:
        if (8 & gState0TypedWork.bytes[0x84]) {
            sub_08017178(1U);
            return;
        }
        sub_08017178(0U);
        return;
    case 2:
        if (8 & gState0TypedWork.bytes[0x84]) {
            sub_080171C0(1U);
            return;
        }
        sub_080171C0(0U);
        return;
    case 3:
        if (8 & gState0TypedWork.bytes[0x84]) {
            sub_08017208(1U);
            return;
        }
        sub_08017208(0U);
        return;
    }
}

u32 sub_0801AC24(s32 arg0) {
    u32 temp_r0;

    if ((gMainByte_03001360 == 0) || (gState0TypedWork.bytes[0x89] == 1)) {
        temp_r0 = sub_0803FB3C(gState0FixedMessages_083C6744[arg0]);
        if (temp_r0 != 0) {
            gState0TypedWork.bytes[0x1B] = 0;
        }
        return temp_r0;
    }
    return 1U;
}

u32 sub_0801AC6C(void) {
    if ((gMainByte_03001360 == 0) || (gState0TypedWork.bytes[0x89] == 1)) {
        return sub_08041CA4();
    }
    return 1U;
}

void sub_080202E0(void) {
    if (gFrameObjects[0xA].byte2B == 0x28) {
        gState0TypedWork.widths.word86 = 0x3C;
        gState0TransferWork.bytes[0xAB] = 0;
        gState0TransferWork.bytes[0xAA] += 1;
        return;
    }
    gFrameObjects[0xA].unknown2C[0] += 1;
    gFrameObjects[0xA].screenY = (u16) gFrameObjects[0xA].screenY + 1;
    gFrameObjects[0xA].byte2B += 1;
}

void sub_080230C8(void) {
    sub_0803F684(0x1084U, (u32) gState0TypedWork.bytes[0x84], 0xFFFFU);
    sub_0803F998(0x1084U, (u32) gState0TypedWork.bytes[0x84], 0xFF00U);
    if (gState0TypedWork.bytes[0x84] == 0x10) {
        gState0TransferWork.bytes[0xAA] += 1;
        return;
    }
    gState0TypedWork.bytes[0x84] += 1;
}

void sub_08023224(void) {
    sub_0803F684(0x1084U, (u32) gState0TypedWork.bytes[0x84], 0xFFFFU);
    sub_0803F998(0x1084U, (u32) gState0TypedWork.bytes[0x84], 0xFF00U);
    if (gState0TypedWork.bytes[0x84] == 0) {
        gState0TransferWork.bytes[0xAA] += 1;
        return;
    }
    gState0TypedWork.bytes[0x84] -= 1;
}

void sub_0802DF48(void) {
    sub_0803F684(0x7FFFU, (u32) gState0TypedWork.bytes[0x84], 0xFFFFU);
    sub_0803F998(0x7FFFU, (u32) gState0TypedWork.bytes[0x84], 0xFF00U);
    if (gState0TypedWork.bytes[0x84] == 0x20) {
        gState0TransferWork.bytes[0xAA] += 1;
        return;
    }
    gState0TypedWork.bytes[0x84] += 2;
}

void sub_0802DF98(void) {
    sub_0803F684(0x1084U, (u32) gState0TypedWork.bytes[0x84], 0xFFFFU);
    sub_0803F998(0x1084U, (u32) gState0TypedWork.bytes[0x84], 0xFF00U);
    if (gState0TypedWork.bytes[0x84] == 0x10) {
        gState0TransferWork.bytes[0xAA] += 1;
        return;
    }
    gState0TypedWork.bytes[0x84] -= 2;
}

void sub_08030FB4(void) {
    if (gFrameObjects[0x21].scaleY == 0x40) {
        gState0TypedWork.widths.word86 = 0;
        gUnknown_0300137C += 1;
        return;
    }
    gFrameObjects[0x21].scaleY -= 8;
}

void sub_08030FEC(void) {
    if (gState0TypedWork.widths.word86 == 0x5A) {
        if (gFrameObjects[0x21].scaleY == 8) {
            sub_08074B88(0x1CU);
            sub_08040CD0(0x21U, 1U);
            sub_0803FAA0(1U, 2U, 0U);
            gUnknown_0300137C += 1;
            return;
        }
        gFrameObjects[0x21].scaleY -= 8;
        return;
    }
    gState0TypedWork.widths.word86 += 1;
}

void sub_08031048(void) {
    if (gState0TypedWork.widths.word86 == 0x5A) {
        if (gFrameObjects[0x21].scaleY == 8) {
            sub_08040CD0(0x21U, 1U);
            sub_0803FAA0(1U, 2U, 0U);
            gUnknown_0300137C += 1;
            return;
        }
        gFrameObjects[0x21].scaleY -= 8;
        return;
    }
    gState0TypedWork.widths.word86 += 1;
}

void sub_080319E0(void) {
    if (gState0TypedWork.widths.word86 == 8) {
        gUnknown_0300137C += 1;
        return;
    }
    gState0TypedWork.widths.word86 += 1;
}

void sub_08035740(u8 *arg0, s32 arg1, u32 arg2) {
    u32 temp_r0;

    temp_r0 = *arg0 + arg1;
    if (temp_r0 > arg2) {
        *arg0 = (u8) arg2;
        return;
    }
    *arg0 = (u8) temp_r0;
}

void sub_080392D8(void) {
    if (sub_08035AAC(gState0TransferWork.bytes[0x87], gState0TransferWork.bytes[0xA7], gState0TransferWork.bytes[0x88]) != 0) {
        gState0TransferWork.bytes[0xB8] = 4;
        gState0TransferWork.bytes[0xBF] = 2;
        return;
    }
    if (sub_08035AFC(gState0TransferWork.bytes[0x87], gState0TransferWork.bytes[0xA7], gState0TransferWork.bytes[0x88]) != 0) {
        gState0TransferWork.bytes[0xB8] = 4;
        gState0TransferWork.bytes[0xBF] = 3;
        return;
    }
    if (sub_08035B4C(gState0TransferWork.bytes[0x87], gState0TransferWork.bytes[0xA7], gState0TransferWork.bytes[0x88]) != 0) {
        gState0TransferWork.bytes[0xB8] = 4;
        gState0TransferWork.bytes[0xBF] = 4;
    }
}

void sub_08039568(void) {
    u8 temp_r1;

    temp_r1 = 1 & gState0TransferWork.bytes[0xF6];
    if (temp_r1 != 0) {
        gState0TransferWork.bytes[0xFD] = 1;
    } else {
        gState0TransferWork.bytes[0xFD] = temp_r1;
    }
    sub_0803D4AC();
}

void sub_0803ADE8(void) {
    sub_08040CD0(0xCU, 2U);
    sub_0803D4AC();
}

void sub_0803D608(void) {
    if (gState0TypedWork.widths.word86 == 8) {
        gState0TypedWork.widths.word86 = 0;
        gUnknown_0300137C += 1;
        return;
    }
    gState0TypedWork.widths.word86 += 1;
}

void sub_0803E674(void) {
    sub_0803EF20();
}

void sub_0804AB48(void) {
    sub_0804A210();
}

void sub_0804AE78(void) {

}

void sub_0804AF8C(void) {

}

void sub_0804E920(void) {

}

void sub_0804F85C(void) {

}

void sub_080574C8(void) {
    sub_0804A210();
}

void sub_08057D7C(void) {

}

void sub_080638E8(void) {
    if (sub_08065710(gMainContextPointer_03006F74 + 0x50) != 0) {
        sub_08040CD0(0U, 0x80U);
        gMainSubstate = 0x14;
        gUnknown_0300137C = 0;
        return;
    }
    sub_08062B48((*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x31)), (*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x33)), 0);
    sub_08062B48((*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x32)), (*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x34)), 1);
}

s32 sub_080672F4(u8 *arg0) {
    s32 var_r0;
    s32 var_r1;

    var_r1 = 0;
    if (*arg0 != 0) {
        do {
            var_r1 += 1;
        } while (*(arg0 + var_r1) != 0);
    }
    var_r0 = 0;
    if (var_r1 != 1) {
        var_r0 = var_r1;
    }
    return var_r0;
}

void sub_08071778(void) {
    sub_08074B88(0U);
    sub_08047850(3);
}

void sub_08072660(void) {
    sub_080724B0();
}

void sub_08072BAC(void *arg0) {
    (*(u16 *)((u8 *)(arg0) + 0x4C)) = (u16) ((*(u16 *)((u8 *)(arg0) + 0x4C)) + 1);
}

void sub_08072C34(void *arg0) {
    (*(s32 *)((u8 *)(arg0) + 0x14)) = (s32) (*(s32 *)((u8 *)(arg0) + 0x20));
}

void sub_08072D5C(void) {
    sub_0807495C();
}

void sub_08072FF4(s32 arg0) {
    sub_080727D0();
    sub_0807266C(arg0);
    sub_08072818(arg0);
}

void sub_08073F98(void *arg0) {
    if ((*(s32 *)((u8 *)(arg0) + 0x10)) != 0) {
        sub_08073C84(arg0);
        (*(s32 *)((u8 *)(arg0) + 0xC)) = (s32) ((*(s32 *)((u8 *)(arg0) + 0xC)) | 1);
    }
}

void sub_08074024(void) {

}
