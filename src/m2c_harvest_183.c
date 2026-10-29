/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "main_callbacks.h"
#include "object_numeric_helpers.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Continued381E0SelectedRoot { u8 pad00[0x12F]; u8 selected12F; };
struct Continued382F4SelectedRoot { u8 pad00[0x12F]; u8 selected12F; };
struct CommandFrame6B530 {u8 pad00[6];u16 frame;u8 pad08[0x12];u16 timer;u8 pad1C[4];u8 state;u8 command;u8 byte22;u8 byte23;u8 pad24[3];u8 byte27;u8 pad28[8];u16 saved;u8 pad32[0xE];};
struct CommandTable6B530 {u8 pad00[8];u16 first;u8 pad0A[0xE];u16 second;u8 pad1A[0x1E];u16 third;u8 pad3A[0x1E];u16 fourth;u8 pad5A[0x1E];u16 fifth;};
struct Dma6EEA8 {const void *volatile source;void *volatile destination;volatile u32 control;};
struct Graphics6EEA8 {u8 pad00[4];u16 saved;u8 pad06[6];u16 incoming;};
struct FrameWork6EEA8 {u8 pad00[0xC2];s16 x3;u8 padC4[0x17E];s16 x9;s16 y9;u8 pad246[0x3C];s16 x10;s16 y10;};

extern const struct CommandTable6B530 gFrameCommandTable084857FC;
extern const u8 gUnknown_087BF688[];
extern const u8 gUnknown_087C1BB4[512];
extern const u8 gUnknown_087C1DB4[];
extern const u8 gUnknown_087C2000[];
extern const u8 gUnknown_087C9AE8[];
extern const u8 gUnknown_087C9DCC[];
extern const u8 gUnknown_087C9E88[];
extern const u8 gUnknown_087C9ED8[];
extern const u8 gUnknown_087C9EE8[32];
extern const u8 gUnknown_087C9F08[32];
extern const u8 gUnknown_087C9F28[32];
extern struct Graphics6EEA8 gGraphicsWork6EEA803001800;
extern void sub_08068460(u8,u8,u16);
extern void sub_080700C8(void);
extern void sub_08070108(void);
extern void sub_08070170(void);
extern void sub_080701A8(void);

void sub_080381E0(void);
void sub_080382F4(void);
void sub_0806B530(u8 index,u8 state,u8 first,u8 second);
void sub_0806EEA8(void);

void sub_080381E0(void) {
    struct FrameObject *firstFrames = gFrameObjects;
    struct FrameObject *frames;
    u8 *laterWork;
    u8 *work;
    u8 *selected;
    struct FrameObject *temp_r0;
    struct FrameObject *temp_r1;
    u8 temp_r3;


    u32 finalIndex;

    work = gState0TypedWork.bytes;
    selected = work + 0x12F;
    temp_r1 = &firstFrames[*selected];
    temp_r3 = temp_r1->unknown2C[1];
    frames = firstFrames;
    laterWork = work;
    if (temp_r3 == 0x23) {
        temp_r1->unknown23[6] += 1;
        return;
    }
    if (!(1 & gState0TransferWork.bytes[0xF8])) {
        temp_r1->angle = (temp_r1->angle - 0x10) & 0x3FF;
    } else {
        temp_r1->angle = (temp_r1->angle + 0x10) & 0x3FF;
    }

    finalIndex = ((struct Continued381E0SelectedRoot *)laterWork)->selected12F;
    temp_r0 = (struct FrameObject *)((finalIndex << 6) + (u32)frames);
    temp_r0->unknown2C[1] += 1;
}

void sub_080382F4(void) {
    struct FrameObject *firstFrames = gFrameObjects;
    struct FrameObject *frames;
    u8 *laterWork;
    u8 *work;
    u8 *selected;
    struct FrameObject *temp_r0;
    struct FrameObject *temp_r1;
    u8 temp_r3;


    u32 finalIndex;

    work = gState0TypedWork.bytes;
    selected = work + 0x12F;
    temp_r1 = &firstFrames[*selected];
    temp_r3 = temp_r1->unknown2C[1];
    frames = firstFrames;
    laterWork = work;
    if (temp_r3 == 0x5A) {
        temp_r1->unknown23[6] += 1;
        return;
    }
    if (1 & gState0TransferWork.bytes[0xF8]) {
        temp_r1->angle = (temp_r1->angle - 0x10) & 0x3FF;
    } else {
        temp_r1->angle = (temp_r1->angle + 0x10) & 0x3FF;
    }

    finalIndex = ((struct Continued382F4SelectedRoot *)laterWork)->selected12F;
    temp_r0 = (struct FrameObject *)((finalIndex << 6) + (u32)frames);
    temp_r0->unknown2C[1] += 1;
}

void sub_0806B530(u8 index,u8 state,u8 first,u8 second) {

 if(state==0){
  struct CommandFrame6B530 *f;
  struct FrameObject *base=gFrameObjects;
  f=(struct CommandFrame6B530 *)(base+index);
  f->state=state;f->command=state;f->byte22=state;
  f->frame=f->saved;f->timer=state;return;
 }
 {struct FrameObject *base=gFrameObjects;
 if(((struct CommandFrame6B530 *)(base+index))->state!=0)return;}
 switch(state){
 case 1: {
  struct CommandFrame6B530 *f;
  f=(struct CommandFrame6B530 *)gFrameObjects+index;
  f->state=1;f->command=1;f->byte22=first;f->byte23=second;
  f->saved=0x33;f->frame=gFrameCommandTable084857FC.first;break;}
 case 2: {
  struct CommandFrame6B530 *f;
  f=(struct CommandFrame6B530 *)gFrameObjects+index;
  f->state=2;f->command=3;f->byte22=first>>1;
  f->saved=0x33;f->frame=gFrameCommandTable084857FC.second;break;}
 case 3: {
  struct CommandFrame6B530 *f;
  f=(struct CommandFrame6B530 *)gFrameObjects+index;
  f->state=3;f->command=7;f->byte22=first>>1;
  f->saved=0x33;f->frame=gFrameCommandTable084857FC.third;break;}
 case 4: {
  struct CommandFrame6B530 *f;
  f=(struct CommandFrame6B530 *)gFrameObjects+index;
  f->state=4;f->command=0xB;f->byte22=first;
  f->saved=0x100;f->frame=gFrameCommandTable084857FC.fourth;break;}
 case 5: {
  struct CommandFrame6B530 *f;
  f=(struct CommandFrame6B530 *)gFrameObjects+index;
  f->state=5;f->command=0xF;f->byte22=first;
  f->saved=0x107;f->frame=gFrameCommandTable084857FC.fifth;break;}
 case 6: {
  struct CommandFrame6B530 *f;
  f=(struct CommandFrame6B530 *)gFrameObjects+index;
  f->state=6;f->command=0;f->byte22=first;
  f->saved=0x10B;f->frame=0x10B;break;}
 case 7: {
  struct CommandFrame6B530 *f;
  f=(struct CommandFrame6B530 *)gFrameObjects+index;
  f->state=7;f->command=0;
  f->saved=first+0x108;f->frame=first+0x108;break;}
 case 8: {
  struct CommandFrame6B530 *f;
  f=(struct CommandFrame6B530 *)gFrameObjects+index;
  f->state=8;f->command=0;f->byte23=second;
  f->saved=first+0x10C;f->frame=first+0x10C;break;}
 case 10: {
  struct CommandFrame6B530 *f;
  f=(struct CommandFrame6B530 *)gFrameObjects+index;
  f->state=10;f->command=(first<<2)+0x14;f->byte27=0;
  f->saved=first*12+0x6F;f->frame=first*12+0x6F;break;}
 }
 ((struct CommandFrame6B530 *)gFrameObjects)[index].timer=0;
}

void sub_0806EEA8(void) {
    u8 reserved[80];
    u32 sp54;
    struct Dma6EEA8 *dma;
    u32 frameZero;
    struct FrameObject *frameBase;
    s16 *var_r4;
    s16 *var_r4_2;
    s32 var_r6;
    s32 var_r5;

    LZ77UnCompVram(gUnknown_087BF688, (void *)0x06000000);
    LZ77UnCompVram(gUnknown_087C9AE8, (void *)0x06008020);
    LZ77UnCompVram(gUnknown_087C9DCC, (void *)0x06008C80);
    LZ77UnCompVram(gUnknown_087C9E88, (void *)0x06009900);
    LZ77UnCompVram(gUnknown_087C9ED8, (void *)0x06009A40);
    dma = (struct Dma6EEA8 *)0x040000D4;
    dma->source = gUnknown_087C1BB4;
    dma->destination = (void *)0x05000000;
    dma->control = 0x84000080;
    (void)dma->control;
    dma->source = gUnknown_087C9EE8;
    dma->destination = (void *)0x05000100;
    dma->control = 0x84000008;
    (void)dma->control;
    dma->source = gUnknown_087C9F08;
    dma->destination = (void *)0x05000120;
    dma->control = 0x84000008;
    (void)dma->control;
    dma->source = gUnknown_087C9F28;
    dma->destination = (void *)0x05000000;
    dma->control = 0x84000008;
    (void)dma->control;
    LZ77UnCompVram(gUnknown_087C1DB4, (void *)0x06007000);
    LZ77UnCompVram(gUnknown_087C2000, (void *)0x06007800);
    frameZero = 0;
    sp54 = frameZero;
    dma->source = &sp54;
    dma->destination = (void *)0x0600F800;
    dma->control = 0x85000200;
    (void)dma->control;
    *(volatile u16 *)0x0400000A = 0x1F09;
    *(volatile u16 *)0x0400000C = 0xE02;
    *(volatile u16 *)0x0400000E = 0xF03;
    sub_08068460(4, 1, 0);
    sub_08048864(9U, 0xC800U, 0x304U, 1U, 3U);
    ((struct FrameWork6EEA8 *)gFrameObjects)->x9 = 8;
    ((struct FrameWork6EEA8 *)gFrameObjects)->y9 = 0xA0;
    sub_08048864(0xAU, 0xC800U, 0x305U, 1U, 3U);
    ((struct FrameWork6EEA8 *)gFrameObjects)->x10 = frameZero;
    ((struct FrameWork6EEA8 *)gFrameObjects)->y10 = 0x90;
    var_r5 = 0;
    var_r4 = &gFrameObjects[0xB].screenX;
    do {
        sub_08048864(var_r5 + 0xB, 0xC400U, var_r5 + 0x300, 0U, 3U);
        (*(s16 *)((u32)var_r4 + 0)) = 0xC0;
        (*(s16 *)((u32)var_r4 + 2)) = 0xC8;
        var_r4 = (s16 *)((u32)var_r4 + 0x40);
        var_r5 += 1;
    } while (var_r5 <= 2);
    var_r5 = 0;
    frameBase=gFrameObjects;
    var_r4_2 = &frameBase[var_r5+3].screenX;
    var_r6 = 0xA0;
    do {
        sub_08048864(var_r5 + 3, 0xC400U, 0x308U, 2U, 3U);
        (*(s16 *)((u32)var_r4_2 + 0)) = var_r6;
        (*(s16 *)((u32)var_r4_2 + 2)) = 0xC8;
        (*(s8 *)((u32)var_r4_2 + 9)) = 0x20;
        var_r4_2 = (s16 *)((u32)var_r4_2 + 0x40);
        var_r6 += 8;
        var_r5 += 1;
    } while (var_r5 <= 5);
    sub_080700C8();
    sub_08070108();
    sub_080701A8();
    sub_08070170();
    *(volatile u16 *)0x04000000 |= 0x1E00;
    *(volatile u16 *)0x04000050 = 0x1844;
    *(volatile u16 *)0x04000052 = 0x80B;
    gGraphicsWork6EEA803001800.saved = (u16) gGraphicsWork6EEA803001800.incoming;
    gUnknown_0300137C = 1;
}
