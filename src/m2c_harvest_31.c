/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

s32 sub_0801AD10(u8);
s32 sub_0803579C(u8, u8);
s32 sub_08035814(u8);
void sub_0803713C(void);
s32 sub_0803725C();
s32 sub_0803EC50();
s32 sub_0807254C(void *);

void sub_08014E94(void);
void sub_080165D0(void);
void sub_0801C3B0(void);
void sub_08020248(void);
void sub_08020340(void);
void sub_0802217C(void);
void sub_08028350(void);
void sub_080353AC(u32 value);
void sub_08036270(void);
s32 sub_0803EC98(void);
void sub_080725B0(void *arg0);

void sub_08014E94(void) {
    u32 var_r1;
    u32 var_r2;

    var_r1 = 0;
    var_r2 = 0;
    do {
        if ((&gState0TransferWork.bytes[0x41])[var_r1] != 0) {
            var_r2 += 1;
        }
        var_r1 += 1;
    } while (var_r1 <= 2U);
    gState0TransferWork.bytes[0x5A] = var_r2;
    gState0TransferWork.bytes[0x5B] = gState0TransferWork.bytes[2];
}

void sub_080165D0(void) {
    __typeof__(gFrameObjects[0]) *array0;
    s32 temp_r0;
    struct FrameObject *temp_r1;
    u32 var_r0;
    u32 var_r4;

    var_r4 = 0;
    do {
        array0 = gFrameObjects;
        temp_r1 = &array0[var_r4];
        if (temp_r1->scaleY == 1) {
            sub_08040D0C(var_r4, 1U);
        } else {
            temp_r0 = temp_r1->scaleY - 8;
            if (temp_r0 <= 0) {
                var_r0 = 1;
                temp_r1->scaleY = 1;
            } else {
                temp_r1->scaleY = (u8) temp_r0;
                var_r0 = temp_r1->scaleX - 8;
            }
            temp_r1->scaleX = var_r0;
        }
        var_r4 += 1;
    } while ((u32) var_r4 <= 5U);
}

void sub_0801C3B0(void) {
    u8 *var_r1;
    u32 var_r0;

    sub_080164F4((u32) gState0TransferWork.bytes[0x87]);
    sub_08015B3C((u32) gState0TransferWork.bytes[0x87]);
    sub_0801AD10(gState0TransferWork.bytes[0x87]);
    if (gState0TransferWork.bytes[0x9D] == 0) {
        gState0TransferWork.bytes[0x9E] = 1;
        var_r1 = &gState0TransferWork.bytes[0x9E] - 2;
        var_r0 = *var_r1 + 1;
    } else {
        var_r1 = &gState0TransferWork.bytes[0x9C];
        var_r0 = 5;
    }
    *var_r1 = var_r0;
}

void sub_08020248(void) {
    u8 *var_r1;
    u32 var_r0;

    if (gState0TransferWork.bytes[0xB7] == 3) {
        sub_0803713C();
        sub_08040CD0(0xAU, 1U);
        gState0TransferWork.bytes[0xAB] = 1;
        var_r1 = &gState0TransferWork.bytes[0xAB] - 1;
        var_r0 = *var_r1 + 1;
    } else {
        var_r1 = &gState0TransferWork.bytes[0xAA];
        var_r0 = 6;
    }
    *var_r1 = var_r0;
}

void sub_08020340(void) {
    u8 var_r0;

    if (gState0TransferWork.bytes[0xB8] == 2) {
        gState0TransferWork.bytes[0xAA] = 0xB;
    } else if (gState0TransferWork.bytes[0xB8] == 4) {
        gState0TransferWork.bytes[0xAA] = 0xF;
    } else {
        gState0TransferWork.bytes[0xAA] = gState0TransferWork.bytes[0xAA] + 1;
    }
}

void sub_0802217C(void) {
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
        var_r1 = &gState0TransferWork.bytes[0xAA];
        var_r0 = 4;
    }
    *var_r1 = var_r0;
}

void sub_08028350(void) {
    u32 var_r0;
    u32 temp_r0;

    temp_r0 = gFrameObjects[0x21].unknown23[4] + 1;
    gFrameObjects[0x21].unknown23[4] = temp_r0;
    if (temp_r0 & 2) {
        gFrameObjects[0x21].flags = 0x8000 | gFrameObjects[0x21].flags;
    } else {
        gFrameObjects[0x21].flags = 0x7FFF & gFrameObjects[0x21].flags;
    }
    if (gFrameObjects[0x21].unknown23[4] == 0x3C) {
        sub_08040CD0(0x21U, 1U);
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_080353AC(u32 value) {
    u32 temp_r1;

    temp_r1 = value & 2;
    if (temp_r1 != 0) {
        gBgScroll3.y = 2;
        return;
    }
    gBgScroll3.y = temp_r1;
}

void sub_08036270(void) {
    u8 *work = gState0TransferWork.bytes;
    work[work[0x89] * 8 + 0x29]++;
}

s32 sub_0803EC98(void) {
    u32 temp_r0;

    sub_0803EC50();
    if ((s32) gFrameObjects[2].screenY <= (s32) gState0TransferWork.bytes[0x1A1]) {
        gFrameObjects[2].screenY = (s16) gState0TransferWork.bytes[0x1A1];
        return 1;
    }
    temp_r0 = gFrameObjects[2].unknown23[4] + 1;
    gFrameObjects[2].unknown23[4] = temp_r0;
    if (!(temp_r0 & 3) && (gFrameObjects[2].unknown23[1] != 1)) {
        gFrameObjects[2].unknown23[1] -= 1;
    }
    return 0;
}

void sub_080725B0(void *arg0) {
  u8 temp_r0;
  temp_r0 = (*((u8 *) (((s8 *) arg0) + 0x5F))) - 1;
  *((u8 *) (((s8 *) arg0) + 0x5F)) = (*((u8 *) (((s8 *) arg0) + 0x5F))) - 1;
  if ((temp_r0 << 0x18) == 0)
  {
    sub_0807254C(arg0);
  }
}
