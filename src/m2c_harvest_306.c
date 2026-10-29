/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "display_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "main.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct CV { u8 p0[0x60]; u8 b60; u8 p61[0xAA - 0x61]; u8 bAA; u8 pAB[0xD2 - 0xAB]; u8 bD2[3]; u8 pD5; u16 hD6[3]; };
struct SetupRec { u8 bytes[0x100]; };

extern struct CV gCounter6ED08_03001800;
extern u16 gUnknown_083AF7F0[];
extern u32 gUnknown_084E45B8[];
extern u8 gFamilyKeyBytes49558_0300058C;
extern u8 gUnknown_03001800[];
extern u8 gUnknown_0300183C;
extern u8 gUnknown_083AF390[];

void sub_0800EA98(void);
void sub_0801A574(const u8 *source, u32 row, u32 index);
void sub_08029C64(void);
void sub_0802E294(void);
void sub_08031704(void);
u32 sub_080352EC(u32 index, s32 first, s32 second);
void sub_080380F0(void);
void sub_08038650(void);
void sub_0806BF18(void);

void sub_0800EA98(void) {

    s32 v;
    sub_0800EBFC();
    sub_0800F440();
    sub_08041C14(4U, gFrameCounter, 0xA8U);
    sub_080100BC();
    if (1 & gFamilyKeyBytes49558_0300058C) {
        if (gState0TypedWork.bytes[0x4A] == 1) {
            v = (u16) sub_08042114(gState0TypedWork.bytes[0x3D], gState0TypedWork.bytes[0x3E]);
            if (((v >> 8) & 0xFF) == (v & 0xFF)) {
                sub_08074DE0(6U);
                return;
            }
        }
        sub_08074DE0(4U);
        sub_08010040();
        gUnknown_0300137C += 1;
        return;
    }
    if (2 & gFamilyKeyBytes49558_0300058C) {
        sub_08074DE0(5U);
        gState0TypedWork.bytes[0x4A] = 2;
        sub_08010040();
        gUnknown_0300137C += 1;
    }
}

void sub_0801A574(const u8 *source, u32 row, u32 index) {

    s32 temp_r2;
    s8 *var_r2;
    u32 var_r4;
    u8 *pa;
    s8 *pb;
    u8 temp_r0;
    u8 temp_r3;
    u8 *var_r1;
    struct FrameObject *objs;
    const s8 *tbl;

    var_r4 = 0;
    objs = gFrameObjects;
    temp_r2 = index + (row * 4);
    tbl = gFrameStepBytes_083AD533;
    temp_r2 = temp_r2 << 6;
    pa = (u8 *)&objs->screenY;
    var_r1 = pa + temp_r2;
    pb = (s8 *)&objs->commandDelay;
    var_r2 = pb + temp_r2;
loop_1:
    if (source[var_r4] != 0xFE) {
        temp_r3 = (*(u8 *)((u8 *)(var_r1) + 0x1D));
        if ((u32) temp_r3 <= 0x1FU) {
            temp_r0 = (*(u8 *)((u8 *)(var_r1) + 0x1C));
            if (temp_r0 == 0) {
                (*(u16 *)((u8 *)(var_r1) + 0)) = (u16) ((s8) tbl[*(volatile u8 *)(var_r1 + 0x1D)] + (*(u16 *)((u8 *)(var_r1) + 0)));
                (*(u8 *)((u8 *)(var_r1) + 5)) = (u8) ((*(u8 *)((u8 *)(var_r1) + 5)) + 2);
                (*(u8 *)((u8 *)(var_r1) + 0x1D)) = (u8) (temp_r3 + 1);
            } else {
                *var_r2 = temp_r0 - 1;
            }
        }
        var_r1 += 0x40;
        var_r2 += 0x40;
        var_r4 += 1;
        if (var_r4 <= 4U) {
            goto loop_1;
        }
    }
}

void sub_08029C64(void) {

    u32 var_r4;

    var_r4 = 0;
    do {
        if (gCounter6ED08_03001800.bD2[var_r4] != 0) {
            switch (var_r4) {
            case 0:
                sub_0801A28C(gDebugMenuTextBuffer, gCounter6ED08_03001800.hD6[var_r4], 0U);
                sub_0801A33C(gDebugMenuTextBuffer, gCounter6ED08_03001800.b60 + var_r4, 0x21U);
                break;
            case 1:
                sub_0801A28C(gDebugMenuTextBuffer + 0x14, gCounter6ED08_03001800.hD6[1], 0U);
                sub_0801A33C(gDebugMenuTextBuffer + 0x14, gCounter6ED08_03001800.b60 + 1, 0x21U);
                break;
            case 2:
                sub_0801A28C(gDebugMenuTextBuffer + 0x28, gCounter6ED08_03001800.hD6[2], 0U);
                sub_0801A33C(gDebugMenuTextBuffer + 0x28, gCounter6ED08_03001800.b60 + 2, 0x21U);
                break;
            }
        }
        var_r4 += 1;
    } while (var_r4 <= 2U);
    sub_08074DE0(0x5BU);
    gState0TypedWork.bytes[0x84] = 0;
    gCounter6ED08_03001800.bAA = (u8) (gCounter6ED08_03001800.bAA + 1);
}

void sub_0802E294(void) {

    u32 var_r4;

    var_r4 = 0;
    do {
        if (gCounter6ED08_03001800.bD2[var_r4] != 0) {
            switch (var_r4) {
            case 0:
                sub_0801A28C(gDebugMenuTextBuffer, gCounter6ED08_03001800.hD6[var_r4], 1U);
                sub_0801A33C(gDebugMenuTextBuffer, gCounter6ED08_03001800.b60 + var_r4, 0x21U);
                break;
            case 1:
                sub_0801A28C(gDebugMenuTextBuffer + 0x14, gCounter6ED08_03001800.hD6[1], 1U);
                sub_0801A33C(gDebugMenuTextBuffer + 0x14, gCounter6ED08_03001800.b60 + 1, 0x21U);
                break;
            case 2:
                sub_0801A28C(gDebugMenuTextBuffer + 0x28, gCounter6ED08_03001800.hD6[2], 1U);
                sub_0801A33C(gDebugMenuTextBuffer + 0x28, gCounter6ED08_03001800.b60 + 2, 0x21U);
                break;
            }
        }
        var_r4 += 1;
    } while (var_r4 <= 2U);
    sub_08074DE0(0x5BU);
    gState0TypedWork.bytes[0x84] = 0;
    gCounter6ED08_03001800.bAA = (u8) (gCounter6ED08_03001800.bAA + 1);
}

void sub_08031704(void) {

    struct FrameObject *fo;
    u8 *b;
    u8 *g;
    sub_0801C2F0(0);
    CpuFastSet(gUnknown_084E45B8, (void *)0x050002E0, 8U);
    gFrameObjects[0x21].flags = (((g = gUnknown_03001800)[0x3C] + 2) << 0xA) | 0xC004;
    gFrameObjects[0x21].tableSelector = 0;
    gFrameObjects[0x21].screenX = gFrameObjects[0x5D + g[0x87] * 4].screenX;
    gFrameObjects[0x21].screenY = gFrameObjects[0x5D + g[0x87] * 4].screenY - 4;
    gFrameObjects[0x21].palette = 7;
    gFrameObjects[0x21].priority = 0x81;
    b = (u8 *)gUnknownPointers_083B6100;
    sub_08040B90(*(u8 **)(b + 0x134), 0x21U);
    gFrameObjects[0x22].flags = (((g = gUnknown_03001800)[0x3C] + 2) << 0xA) | 0xC004;
    gFrameObjects[0x22].tableSelector = 0;
    gFrameObjects[0x22].screenX = gFrameObjects[0x5D + g[0x87] * 4].screenX;
    gFrameObjects[0x22].screenY = gFrameObjects[0x5D + g[0x87] * 4].screenY - 4;
    gFrameObjects[0x22].palette = 7;
    gFrameObjects[0x22].priority = (g[0x87] * 4) + 0x59;
    sub_08040B90(*(u8 **)(b + 0x138), 0x22U);
    {struct SetupRec *rec = (struct SetupRec *)gSetupBuffer_03000590; u8 v = rec[g[0x87]].bytes[0xAA];
    g[0x51] = v;}
    gUnknown_0300137C += 1;
}

u32 sub_080352EC(u32 index, s32 first, s32 second) {

    s32 temp_r0;
    struct FrameObject *temp_r4;
    struct FrameObject *temp_r5;
    struct FrameObject *objs;
    u16 temp_r0_2;
    u16 temp_r6;
    u8 temp_r2;

    temp_r6 = (u16) second;
    objs = gFrameObjects;
    temp_r5 = &objs[index];
    temp_r5->unknown23[2] += gUnknown_083AF390[0xFF - (*(u16 *)((u8 *)(temp_r5) + 0x30))];
    temp_r2 = temp_r5->unknown23[2];
    temp_r5->unknown23[2] = 3 & temp_r2;
    temp_r0 = (u16) temp_r5->screenY - (temp_r2 >> 2);
    temp_r5->screenY = temp_r0;
    if (((s16) temp_r0 >= (s16) first) && ((s16) temp_r0 <= (s16) temp_r6)) {
        temp_r5->screenY = (s16) temp_r6;
        return 1U;
    }
    temp_r4 = &gFrameObjects[index];
    (*(u16 *)((u8 *)(temp_r4) + 0x30)) += temp_r4->unknown23[1];
    if ((*(u16 *)((u8 *)(temp_r4) + 0x30)) > 0xFFU) {
        (*(u16 *)((u8 *)(temp_r4) + 0x30)) = 0xFFU;
    }
    return 0U;
}

void sub_080380F0(void) {

  struct FrameObject *objs;
  struct FrameObject *o;
  u8 *idxp;
  u8 *work;
  objs = gFrameObjects;
  work = gState0TypedWork.bytes;
  idxp = &work[0x12F];
  o = &objs[*idxp];
  if (o->unknown2C[1] == 0x46)
  {
    o->unknown23[6] += 1;
    return;
  }
  o->screenX = (((u16) o->screenX) + gUnknown_083AF7F0[0xF & o->unknown2C[1]]) & 0x1FF;
  o = &objs[*idxp];
  if (1 & o->unknown2C[1])
  {
    o->screenY = ((u16) o->screenY) + 1;
  }
  objs[*idxp].unknown2C[1] += 1;
}

void sub_08038650(void) {

    struct FrameObject *temp_r0;
    struct FrameObject *o;
    u8 *b;
    u32 x;
    if (sub_080355F0(gState0TypedWork.bytes[0x12F]) != 0) {
        b = (u8 *)gUnknownPointers_083B6100;
        sub_08040B90(*(u8 **)(b + 0x1AC), gState0TypedWork.bytes[0x12F]);
        gFrameObjects[gState0TypedWork.bytes[0x12F]].palette = 6;
        gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown23[5] = 0;
        temp_r0 = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
        temp_r0->unknown23[6] += 1;
        sub_0803F63C(&gFrameObjects[gState0TypedWork.bytes[0x12F]], &(&gFrameObjects[3])[gState0TypedWork.bytes[0x12F]], 0x40U);
        sub_08040B90(*(u8 **)(b + 0x1B0), (u8) (gState0TypedWork.bytes[0x12F] + 3));
        gFrameObjects[gState0TypedWork.bytes[0x12F] + 3].priority = (((gState0TypedWork.bytes[0x12F] + 0xDF) + gUnknown_03001800[0x60]) << 2) + 0x59;
        gFrameObjects[gState0TypedWork.bytes[0x12F] + 3].unknown23[6] = 3;
    }
}

void sub_0806BF18(void) {

    s32 i;
    s32 best;
    s16 y;
    s16 sx;
    s16 sy;
    if (gFrameObjects[0x13].commandDelay == 0) {
        best = 0;
        for (i = 0; i < 8; i++) {
            if (gFrameObjects[0x28 + i].commandDelay == 1) {
                y = gFrameObjects[0x28 + i].screenY;
                if (best < y) {
                    best = y;
                    gFrameObjects[0x13].commandDelay = gFrameObjects[0x28 + i].commandDelay;
                    gFrameObjects[0x13].commandOffset = gFrameObjects[0x28 + i].commandOffset;
                    gFrameObjects[0x13].unknown1A = 0;
                }
            }
        }
        return;
    }
    switch (gFrameObjects[0x13].commandOffset) {
    case 0:
        gFrameObjects[0x13].screenX = 0xB8;
        break;
    case 1:
        gFrameObjects[0x13].screenX = 0xC8;
        break;
    case 2:
        gFrameObjects[0x13].screenX = 0xD8;
        break;
    }
    if (4 & gFrameObjects[0x13].unknown1A) {
        sy = 0x47;
    } else {
        sy = 0x49;
    }
    gFrameObjects[0x13].screenY = sy;
    gFrameObjects[0x13].unknown1A += 1;
}
