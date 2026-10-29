/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "display_helpers.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s32 sub_08037230(s32,s32);
extern s32 sub_0803725C(void);
extern void sub_08034F08(void);
extern void sub_0803579C(u32,u32);
extern void sub_08035814(s32);
extern void sub_08037280(u32,u32);
extern void sub_0803EF8C(u32, u32, u32, u32, u32, u32);
extern void sub_0804253C(u8, u16, u16);
extern void sub_08043CA8(void);

void sub_0801BACC(void);
void sub_08020844(void);
void sub_08021F90(void);
void sub_08033F9C(void);
void sub_0803E4F4(void);

void sub_0801BACC(void) {

    if (0x8000 & gFrameObjects[9].flags) {
        if (gFrameObjects[9].unknown23[1] != 0) {
            gFrameObjects[((gFrameObjects[9].unknown23[2] - 1) * 4) + gFrameObjects[9].unknown23[1] + 0x59].scaleX = 0x40;
            gFrameObjects[((gFrameObjects[9].unknown23[2] - 1) * 4) + gFrameObjects[9].unknown23[1] + 0x59].scaleY = 0x40;
            if (gState0TransferWork.bytes[0x80] == (gFrameObjects[9].unknown23[2] - 1)) {
                if ((u8)(gFrameObjects[9].unknown23[1]-2)<=1U) {
                    gFrameObjects[gState0TransferWork.bytes[0x80]*4+gFrameObjects[9].unknown23[1]+0x59].flags &= 0xFFDF;
                }else {
                    gFrameObjects[gState0TransferWork.bytes[0x80]*4+gFrameObjects[9].unknown23[1]+0x59].flags &= 0xFDDF;
                }
            }
        }
        sub_08040CD0(9U, 1U);
    }
}

void sub_08020844(void) {
 u8 *work=gState0TransferWork.bytes;
 s32 result;
 if(sub_08037230(work[0x88],work[0x8B])==0) {
  sub_0803579C(work[0x87],work[0xA7]);sub_08035814(work[0x87]);
  result=sub_0803725C();
  if(result!=0) {work[0xA6]=0x1A;work[0xAA]=2;work[0xAB]=1;}
  else {
   sub_08037280(work[0x87],work[0xA7]);sub_08036270();work[0xAA]++;work[0xAB]=result;
  }
 }else {work[0xA6]=0x26;work[0xAA]=2;work[0xAB]=1;}
}

void sub_08021F90(void) {

    if (!(1 & gState0TransferWork.bytes[0xF8])) {
        gFrameObjects[0x21].angle=(gFrameObjects[0x21].angle-0x40)&0x3FF;
    } else {
        gFrameObjects[0x21].angle=(gFrameObjects[0x21].angle+0x40)&0x3FF;
    }
    if (sub_080355F0(0x21U) != 0) {
        gFrameObjects[0x21].flags &= 0xFDFF;
        gFrameObjects[0x21].angle = 0;
        gState0TransferWork.bytes[0xAA] = (u8) (gState0TransferWork.bytes[0xAA] + 1);
    }
}

void sub_08033F9C(void) {
    u8 *setup = gSetupBuffer_03000590;
    u8 *work;
    s32 temp_r4;
    s32 item;
    s32 offset;
    u8 *temp_r2;

    work = gState0TransferWork.bytes;
    temp_r4 = work[0x88] << 8;
    temp_r2 = temp_r4 + setup;
    if (0x10 & temp_r2[0xBD]) {
        item = temp_r2[0xDE] - 1;
        offset = item * 0x18;
        offset += temp_r4;
        if ((setup[offset + 0x59] != 0) && (work[0xB7] == 0)
            && (*(s16 *)(work + 0xEC) > *(s16 *)(temp_r2 + 0xD8))) {
            work[0xB7] = 3;
        }
    }
    sub_08034F08();
}

void sub_0803E4F4(void) {
    s32 paletteZero;
    s32 tileFill;
    s32 frameZero;
    u32 zero;
    volatile u16 *display;
    volatile u16 *bg0;
    volatile u16 *bg1;
    volatile u16 *bg2;
    volatile u16 *bg3;
    sub_08043CA8();
    display = (volatile u16 *)0x04000000;
    *display &= 0xE0FF;
    bg0 = (volatile u16 *)0x04000008;
    *bg0 = 0x500;
    bg1 = (volatile u16 *)0x0400000A;
    *bg1 = 0x1801;
    bg2 = (volatile u16 *)0x0400000C;
    *bg2 = 0x1902;
    bg3 = (volatile u16 *)0x0400000E;
    *bg3 = 0x1B03;
    paletteZero = zero = 0;
    CpuFastSet(&paletteZero, (void *)0x05000120, 0x01000008);
    tileFill = 0x11111111;
    CpuFastSet(&tileFill, (void *)0x06004120, 0x01000008);
    sub_0803EF8C(0x20,0x20,0,0,*bg0,0x9209);
    sub_0803EF8C(0x20,0x20,0,0,*bg1,0x9209);
    sub_0803EF8C(0x20,0x20,0,0,*bg2,0x9209);
    sub_0803EF8C(0x20,0x20,0,0,*bg3,0x9209);
    frameZero = zero;
    CpuFastSet(&frameZero, gFrameObjects, 0x01000800);
    *display |= 0x1F60;
    sub_0804253C(5,0x3F,0x20);
    gUnknown_0300137C += 1;
}
