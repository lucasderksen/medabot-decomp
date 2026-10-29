/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "display_effects.h"
#include "display_helpers.h"
#include "effect_work.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "graphics.h"
#include "input.h"
#include "main.h"
#include "main_callbacks.h"
#include "object_numeric_helpers.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct E4 { u8 count; u8 b[3]; };
struct SetupRec { u8 bytes[0x100]; };
struct CO
{
  u8 pad[0x13];
  u8 f13;
  u8 f14;
  u8 f15;
  s8 f16[1];
};
struct CounterView { u16 a0; u16 a2; u16 a4; u16 a6; s32 w8; u8 pad[0xEE - 0xC]; u8 bEE; };
struct T73 { s32 w0; s32 w4; s32 w8; s32 wC; s32 w10; s32 w14; u8 pad[0x1C]; s16 h34; s16 h36; s16 h38; u8 b3A; s8 b3B; s8 b3C; s8 b3D; s8 b3E; s8 b3F; s8 b40; };

extern const u16 gUnknown_083ABC08[];
extern const u16 gUnknown_083ABC32[][4];
extern const u16 gUnknown_083ABC42[];
extern const u8 gUnknown_083ABC0C[][16];
extern struct CounterView gCounter6ED08_03001800;
extern struct E4 gUnknown_083AD502[];
extern u16 gUnknown_03000030[];
extern u16 gUnknown_03000170[];
extern u16 gUnknown_030002B0[];
extern u32 gUnknown_0850F8F8[];
extern u8 *gFamilySoundRoot74028;
extern u8 gUnknown_03001800[];
extern u8 gUnknown_08484FE5[];
extern u8 gUnknown_08485014[];
extern u8 gUnknown_084CE3E8;
s32 sub_08068888();

void sub_080164F4(u32 value);
void sub_08021BD8(void);
void sub_080306B8(void);
void sub_0803496C(void);
void sub_08042028(void *arg0);
void sub_08059434(u32 index, u32 value, unsigned short digits, u32 x, u32 y);
void sub_0805B5BC(struct FrameObject *object);
void sub_08061594(void);
void sub_08063644(void);
void sub_080648E0(void);
void sub_0806495C(void);
void sub_08064A08(void);
void sub_08067A70(void);
void sub_0806D5B4(void);
void sub_0806EB28(void);
s32 sub_080705E0(u8 arg0);
void sub_08073CDC(u8 *arg0);
void sub_08073DB8(struct T73 *o, s32 arg1, s32 arg2, s8 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);

void sub_080164F4(u32 value) {

    s32 var_r5;
    u16 *p;
    struct FrameObject *objs;
    u32 i;
    u8 count;
    u8 temp_r0;

    count = gUnknown_083AD502[value].count;
    i = 0;
    if (i < count) {
        objs = gFrameObjects;
        p = &objs[0x3C].frameAndGroup;
        do {
            if ((*(u8 *)((u8 *)(p) + 0x1E)) != 0) {
                var_r5 = 0x12;
            } else {
                var_r5 = 0x16;
            }
            (*(u8 *)((u8 *)(p) + 0x1B)) = (*(u8 *)((u8 *)(p) + 0x1B)) + 1;
            if (!((*(u8 *)((u8 *)(p) + 0x1B)) & 3)) {
                temp_r0 = ((*(u8 *)((u8 *)(p) + 0x1C)) + 1) & 3;
                (*(u8 *)((u8 *)(p) + 0x1C)) = temp_r0;
                *p = var_r5 + (temp_r0 | 0x600);
            }
            p = (u16 *)((u8 *)p + 0x40);
            i++;
        } while (i < count);
    }
}

void sub_08021BD8(void) {

    u32 i;
    u8 *b;

    LeDecompress(&gUnknown_084CE3E8, (void *)0x06014800);
    CpuFastSet(gUnknown_0850F8F8, (void *)0x050002E0, 8U);
    b = (u8 *)gUnknownPointers_083B6100;
    sub_08040B90(*(u8 **)(b + 0x8C), 0x21U);
    sub_08040B90(*(u8 **)(b + 0x8C), 0x22U);
    sub_08040B90(*(u8 **)(b + 0x8C), 0x23U);
    sub_08040D44(0x21U, 3U);
    for (i = 0; i <= 5; i++) {
        if (gSetupBuffer_03000590[(i << 8) + 0x40] != 0) {
            gFrameObjects[0x5A + i * 4].unknown23[0] = 0;
            gFrameObjects[0x5B + i * 4].unknown23[0] = 0;
            gFrameObjects[0x5C + i * 4].unknown23[0] = 0;
            gFrameObjects[0x5D + i * 4].unknown23[0] = 0;
        }
    }
    gState0TypedWork.widths.word86 = 0;
    gUnknown_03001800[0xAA] += 1;
}

void sub_080306B8(void) {

    u32 i;
    if ((gState0TypedWork.bytes[0x89] == 0) && (1 & *(u8 *)&gRepeatedKeys)) {
        i = 0;
        do {
            if (gFrameObjects[i + 10].flags & 0x8000) {
                sub_08040CD0(i + 10, 1U);
            }
            i += 1;
        } while (i <= 0x13U);
        gUnknown_03001800[0xAA] += 1;
    }
    if (gState0TypedWork.widths.word86 != 0) {
        gState0TypedWork.widths.word86 -= 1;
        return;
    }
    i = 0;
    do {
        if (gFrameObjects[i + 10].flags & 0x8000) {
            sub_08040CD0(i + 10, 1U);
        }
        i += 1;
    } while (i <= 0x13U);
    gUnknown_03001800[0xAA] += 1;
}

void sub_0803496C(void) {

    u32 i;
    u32 j;
    struct SetupRec *rec;
    u8 *q;
    gUnknown_03001800[0x60] = sub_08032FC4(gUnknown_03001800[0x87]);
    i = 0;
    rec = (struct SetupRec *)gSetupBuffer_03000590;
    for (; i <= 2; i++) {
        if (rec[gUnknown_03001800[0x60] + i].bytes[0xBA] != 0) {
            q = rec->bytes + 0x59;
            for (j = 0; j <= 3; j++) {
                if (q[((gTransferByte_03001860 + i) << 8) + j * 0x18] == 0) {
                    *(u16 *)((u8 *)&gTransferByte_03001860 + 0x8C) += 0xA;
                }
            }
        }
    }
    sub_08034F08();
}

void sub_08042028(void *arg0) {

    struct InventoryRecord *var_r1;
    struct InventoryRecord *var_r5;
    u32 var_r3;
    u8 temp_r2;
    u32 low;
    s32 m;

    var_r3 = 0;
    m = 0x80;
    var_r1 = gInventoryRecords;
    var_r5 = gInventoryRecords;
    do {
        temp_r2 = var_r5->byte0;
        if (!(m & temp_r2)) {
            low = 0x1F & temp_r2;
            sub_0803F63C(arg0, var_r1, 0x40U);
            var_r5->byte0 = (m & var_r5->byte0) | low;
            return;
        }
        var_r5++;
        var_r1++;
        var_r3++;
    } while (var_r3 <= 0x1DU);
}

void sub_08059434(u32 index, u32 value, unsigned short digits, u32 x, u32 y) {

  u32 temp_r2_2;
  u32 var_r5;
  u8 temp_r2;
  u8 temp_r3;
  u8 temp_r5;
  struct CO *w;
  temp_r5 = (u8) digits;
  temp_r2 = (u8) x;
  temp_r3 = (u8) y;
  w = (struct CO *) gContinuedOtherWork_030057A0;
  if (((s8) index) != w->f16[w->f14])
  {
    sub_08059734(value, (u32) temp_r5, (u32) temp_r2, (u32) temp_r3);
    return;
  }
  if (0x10 & w->f15)
  {
    temp_r2_2 = ((u32) (digits << 0x18)) >> 0x1B;
    if (temp_r2_2 != 0)
    {
      var_r5 = temp_r2_2;
      do
      {
        sub_08048888((u32) w->f13);
        w->f13 = (u8) (w->f13 + 1);
        sub_08048888((u32) w->f13);
        w->f13 = (u8) (w->f13 + 1);
        var_r5 -= 1;
      }
      while (var_r5 != 0);
    }
  }
  else
  {
    sub_08059734(value, (u32) temp_r5, (u32) temp_r2, (u32) temp_r3);
  }
}

void sub_0805B5BC(struct FrameObject *object) {

    u8 *ctx = (u8 *)gMainContextPointer_03006F74;
    if (ctx[0x12] != 0) {
        u32 t = ctx[0x13];
        if ((ctx[0x13] >= ctx[0x11]) && (((s32) ctx[0x13]) < (ctx[0x11] + 5))) {
            object->flags |= 0x4000;
        } else {
            object->flags &= 0xBFFF;
        }
    }
}

void sub_08061594(void) {

    u8 buf[0x30];
    u8 *p;
    if (((u8 *)gMainContextPointer_03006F74)[5] == 0) p = gUnknown_08484FE5; else p = gUnknown_08485014;
    sub_08060D28(buf, p);
    if (sub_0803FB3C(buf) != 0) {
        gUnknown_0300137C += 1;
    }
}

void sub_08063644(void) {

    s16 temp_r4;
    u16 temp_r0;
    u8 *ctx;
    u16 y = 0;

    ctx = (u8 *)gMainContextPointer_03006F74;
    temp_r0 = (*(u16 *)((u8 *)(ctx) + 0x3C));
    (*(u16 *)((u8 *)(ctx) + 0x3C)) = (u16) (temp_r0 + 1);
    temp_r4 = (s16) temp_r0;
    if ((s32) temp_r4 <= 0x10) {
        sub_0803F998(0x7FFFU, 0x20U, 0xFFU);
        (*(s16 *)((u8 *)((void *)0x04000050) + 0)) = 0xE50;
        (*(s16 *)((u8 *)((void *)0x04000050) + 2)) = (s16) (((0x10 - temp_r4) << 8) | temp_r4);
        (*(s16 *)((u8 *)(((void *)0x04000050 + 2)) + 2)) = 8;
    } else {
        s32 z = 0;
        (*(s16 *)((u8 *)((void *)0x04000050) + 0)) = 0xE10;
        (*(s16 *)((u8 *)((void *)0x04000050) + 2)) = (s16) (((0x10 - temp_r4) << 8) | temp_r4);
        (*(s16 *)((u8 *)(((void *)0x04000050 + 2)) + 2)) = 8;
        (*(u16 *)((u8 *)(ctx) + 0x3C)) = y;
        gState0TypedWork.bytes[0x84] = z;
        gUnknown_0300137C += 1;
    }
    sub_08062B48((*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x31)), (*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x33)), 0);
    sub_08062B48((*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x32)), (*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x34)), 1);
    sub_08062C98();
}

void sub_080648E0(void) {

    u16 mask;
    u8 *ctx;
    struct BgScroll *bg;
    bg = &gBgScroll2;
    ctx = gMainContextPointer_03006F74;
    bg->y = (((*(s16 *)(ctx + 0x3A)) * 0x10) + 0x1B8) & (mask = 0x1FF);
    bg->x = ((s32) (0 - (s16) (0x20 & (u16) (*(s16 *)(ctx + 0x3A)))) >> 0x1F) & 0x100;
    (*(s16 *)(ctx + 0x3A)) = (s16) ((u16) (*(s16 *)(ctx + 0x3A)) + 1);
    if (1 & *(u8 *)&gRepeatedKeys) {
        sub_080656DC(ctx + 0x50, 0U, 0U, 1U, 0xC0U);
        gUnknown_0300137C += 1;
    }
}

void sub_0806495C(void) {

    u16 mask;
    if (sub_08065710((u8 *)gMainContextPointer_03006F74 + 0x50) != 0) {
        gUnknown_0300137C = 0;
    }
    gBgScroll2.y = (((*(s16 *)((u8 *)gMainContextPointer_03006F74 + 0x3A)) * 0x10) + 0x1B8) & (mask = 0x1FF);
    gBgScroll2.x = ((s32) (0 - (s16) (0x20 & (u16) (*(s16 *)((u8 *)gMainContextPointer_03006F74 + 0x3A)))) >> 0x1F) & 0x100;
    (*(s16 *)((u8 *)gMainContextPointer_03006F74 + 0x3A)) = (s16) ((u16) (*(s16 *)((u8 *)gMainContextPointer_03006F74 + 0x3A)) + 1);
}

void sub_08064A08(void) {

    s32 i;
    s32 mask;
    s32 value;
    s32 t;
    u8 *ctx;

    mask = 0;
    for (i = 0; i < 30; i++) {
        if (gInventoryRecords[i].byte0 & 0x80) {
            mask |= 1 << gInventoryRecords[i].byte1;
        }
    }
    (*(s8 *)((u8 *)(gMainContextPointer_03006F74) + 0x48)) = 0;
    (*(s8 *)((u8 *)(gMainContextPointer_03006F74) + 0x49)) = 0;
    (*(s8 *)((u8 *)(gMainContextPointer_03006F74) + 0x4A)) = 0;
    (*(s8 *)((u8 *)(gMainContextPointer_03006F74) + 0x4B)) = 0;
    ctx = gMainContextPointer_03006F74;
    t = *(s8 *)(ctx + 0x7A);
    value = 0;
    if (t != 0) {
        value = mask;
    }
    *(s32 *)(ctx + 0x1C) = value;
    gUnknown_0300137C += 1;
}

void sub_08067A70(void) {

    u8 *ctx;
    u8 *c2;
    u16 v;
    u32 zero;
    u32 t;
    sub_08066D8C();
    ctx = gMainContextPointer_03006F74;
    v = *(u16 *)(ctx + 0x3A);
    *(u16 *)(ctx + 0x3A) = v + 1;
    if (sub_08067578((s16)v) != 0) {
        c2 = gMainContextPointer_03006F74;
        zero = 0;
        *(u16 *)(c2 + 0x3A) = zero;
        t = c2[5] + 1;
        c2[5] = t;
        if ((u8)t > 2U) {
            gUnknown_0300137C += 1;
        } else {
            gBgScroll1.y = zero;
            gUnknown_0300137C -= 2;
        }
    }
}

void sub_0806D5B4(void) {

    u32 v = *(volatile u8 *)0x04000006;
    if (v <= 0x9E) {
        *(volatile u16 *)0x04000020 = gUnknown_03000030[v + 1];
        *(volatile u16 *)0x04000028 = gUnknown_03000170[*(volatile u8 *)0x04000006 + 1];
        *(volatile u16 *)0x0400002A = gUnknown_030002B0[*(volatile u8 *)0x04000006 + 1];
    }
}

void sub_0806EB28(void) {

    volatile u16 *dispcnt;
    int shifted;

    if ((gCounter6ED08_03001800.w8 > 0x4C) && ((s8) gCounter6ED08_03001800.bEE >= 0)) {
        shifted = (0x10 - gCounter6ED08_03001800.bEE) << 24;
        *(s16 *)0x04000052 = gCounter6ED08_03001800.bEE | ((u32) shifted >> 16);
        gCounter6ED08_03001800.bEE = (u8) (gCounter6ED08_03001800.bEE - 1);
    }
    if (sub_08068888() != 0) {
        *(dispcnt = (volatile u16 *)0x04000000) &= 0xFBFF;
        gMainState = (u32) gCounter6ED08_03001800.a0;
        gMainSubstate = (u32) gCounter6ED08_03001800.a2;
        gUnknown_0300137C = (u32) gCounter6ED08_03001800.a4;
    }
    gCounter6ED08_03001800.w8 = gCounter6ED08_03001800.w8 + 1;
}

s32 sub_080705E0(u8 arg0) {

  struct FrameObject *objs;
  struct FrameObject *temp_r2;
  u8 new_var2;
  u8 temp_r4;
  struct FrameObject *new_var;
  u8 temp_r3;
  temp_r4 = arg0;
  new_var = gFrameObjects;
  temp_r2 = &gFrameObjects[temp_r4];
  new_var2 = temp_r2->scaleX;
  objs = new_var;
  temp_r3 = new_var2;
  if (((u32) temp_r3) > 0x3FU)
  {
    if (((u32) temp_r2->scaleY) > 0x3FU)
    {
      return 0;
    }
    goto block_4;
  }
  if (((u32) temp_r2->scaleY) <= 0x3FU)
  {
    block_4:
    temp_r2 = (struct FrameObject *)((temp_r4 << 6) + (u32)objs);

    temp_r2->scaleY = temp_r2->scaleY + 8;
    if (temp_r2->scaleY > 0x40U)
    {
      temp_r2->scaleY = 0x40;
    }
  }
  else
  {
    temp_r2->scaleX = temp_r3 + 8;
    if (((u32) temp_r2->scaleX) > 0x40U)
    {
      temp_r2->scaleX = 0x40;
    }
  }
  objs[temp_r4].commandOffset = (u8) (objs[temp_r4].commandOffset + 1);
  return 1;
}

void sub_08073CDC(u8 *arg0) {

    u8 var_r6;
    u16 *reg;

    if (4 & gFamilySoundRoot74028[0x72C]) {
        var_r6 = 3;
    } else {
        if (arg0[0x40] != 0) { var_r6 = arg0[0x40]; } else { var_r6 = arg0[0x3F]; }
    }
    reg = (u16 *)0x04000082;
    *reg = ((*reg & gUnknown_083ABC42[arg0[0x3A] - 1]) & gUnknown_083ABC08[arg0[0x3A] - 1]) | gUnknown_083ABC32[arg0[0x3A] - 1][var_r6] | gUnknown_083ABC0C[arg0[0x3A] - 1][arg0[0x3C]];
}

void sub_08073DB8(struct T73 *o, s32 arg1, s32 arg2, s8 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {

    o->w0 = arg1;
    o->w8 = arg2;
    o->wC = 0;
    o->w14 = 0;
    o->h34 = arg5;
    o->h36 = 0;
    o->h38 = 0;
    o->b3B = arg3;
    o->b3C = arg4;
    o->w4 = 0;
    o->w10 = 0;
    o->b3F = arg6;
    o->b40 = arg7;
}
