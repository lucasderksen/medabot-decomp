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
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinuedScaleFrame21 {
 u8 prefix[0x840];u16 flags;s16 screenX,screenY;u16 frameAndGroup;u8 scaleX,scaleY,palette,priority;
 u8 gapC[0xC];u16 angle,unknown1A;u8 tableSelector,affineIndex;u8 gap1E[6];u8 kind;u8 gap25[0xB];u16 savedX;s16 savedY;u8 gap34[0xC];
};
struct ContinuedActionWork { u8 pad00[0x60]; u8 byte60; u8 pad61[0x26]; u8 selected87; };
struct ContinuedSetupRecord { u8 pad00[0xE0]; u8 byteE0; u8 padE1[0x1F]; };
struct ContinuedNibbleWork { u8 pad00[0x1A0]; u8 input1A0; u8 pad1A1; u8 count1A2; u8 scaled1A3; };
struct LocalInitContext65D44 {
    u8 unknown00[5];
    u8 byte05;
    u8 unknown06[0x34];
    s16 phase3A;
    u8 unknown3C[0x3E];
    u8 byte7A;
};
struct LocalResetTransferWork { u16 mode; s16 selection; s16 position; u16 group; s32 counter; s16 source; u8 pad0E[0xE6]; u16 blend; u16 brightness; };
struct LocalDma3Registers { const void *volatile source; void *volatile destination; volatile u32 control; };

extern const u8 *const gState0NextCommands_083B6100[];
extern const u8 gUnknown_0850F458[32];
extern const u8 gUnknown_0879BC34[512];
extern const u8 gUnknown_0879BE34[];
extern const u8 gUnknown_0879D260[];
extern const u8 gUnknown_0879D454[];
extern const u8 gUnknown_0879D594[];
extern s32 sub_08074CE0(void);
extern struct ContinuedNibbleWork gUnknown_03001800;
extern struct LocalResetTransferWork gGraphicsTransferCounter;
extern u32 sub_08032FB8(u32);
extern u32 sub_08033090(u32);
extern u32 sub_08037830(u32, u32);
extern u8 gUnknown_02030000[];
extern void sub_08034F08(void);
extern void sub_08035528(u32);
extern void sub_080355C4(u32);

void sub_0802503C(void);
void sub_080282E0(void);
void sub_08034AF4(void);
void sub_0803EB5C(void);
void sub_08065D44(void);
void sub_0806EC30(void);

void sub_0802503C(void) {
    u8 *work=gState0TransferWork.bytes;
    struct ContinuedScaleFrame21 *frames;
    u8 command;
    if(1&work[0xF8]) {
        struct ContinuedScaleFrame21 *initial=(struct ContinuedScaleFrame21 *)gFrameObjects;
        initial->flags&=0xEFFF;
    }
    frames=(struct ContinuedScaleFrame21 *)gFrameObjects;
    frames->scaleX=0x40;
    frames->scaleY=0x40;
    frames->angle=0;
    frames->palette=7;
    frames->screenX=(u16)gFrameObjects[work[0x88]*4+0x5D].screenX;
    frames->screenY=(u16)gFrameObjects[work[0x88]*4+0x5D].screenY-12;
    gState0TypedWork.bytes[0x84]=0x47;
    command=gState0TypedWork.bytes[0x84];
    sub_08040B90(gState0NextCommands_083B6100[command],0x21);
    sub_08074DE0(0x4F);
    work[0xAA]++;
}

void sub_080282E0(void) {
    if(gFrameObjects[0x21].unknown23[4]==0x10) {
        sub_08074DE0(0x28);
        gFrameObjects[0x21].unknown23[4]=0;
        gState0TransferWork.bytes[0xAA]++;
    } else {
        if(!(1&gState0TransferWork.bytes[0xF8]))gFrameObjects[0x21].screenX-=1;
        else gFrameObjects[0x21].screenX+=1;
        gFrameObjects[0x21].unknown23[4]++;
    }
}

void sub_08034AF4(void) {
 struct ContinuedActionWork *work = (void *)gState0TransferWork.bytes;
 u8 *selected = &work->selected87;
 u8 *first;
 u32 result;
 {
  u32 side = sub_08032FB8(*selected);
  first = &work->byte60;
  *first = side;
 }
 result = sub_08037830(*first, *selected);
 if (result != 255) {
  struct ContinuedSetupRecord *records = (void *)gSetupBuffer_03000590;
  records[*selected].byteE0 = result + 1;
 } else {
  u32 next;
  *first = sub_08032FB8(*selected);
  next = sub_08033090(*first);
  {
   struct ContinuedSetupRecord *records = (void *)gSetupBuffer_03000590;
   records[*selected].byteE0 = next + 1;
  }
 }
 {
  struct ContinuedActionWork *laterWork = (void *)gState0TransferWork.bytes;
  u8 *laterSelected = &laterWork->selected87;
  sub_08035528(*laterSelected);
  sub_080355C4(*laterSelected);
 }
 sub_08034F08();
}

void sub_0803EB5C(void) {
 gUnknown_03001800.count1A2 = gUnknown_03001800.input1A0 >> 4;
 switch (gUnknown_03001800.count1A2) {
 case 0: gUnknown_03001800.count1A2 = 5; break;
 case 1: gUnknown_03001800.count1A2 = 4; break;
 case 2: gUnknown_03001800.count1A2 = 3; break;
 case 3: gUnknown_03001800.count1A2 = 2; break;
 case 4: gUnknown_03001800.count1A2 = 1; break;
 case 5: gUnknown_03001800.count1A2 = 0; break;
 case 6: gUnknown_03001800.count1A2 = 0; break;
 }
 gUnknown_03001800.scaled1A3 = gUnknown_03001800.count1A2 * 16 + 24;
}

void sub_08065D44(void) {
    u32 fillZero,frameZero;
    volatile u16 *display;
    volatile u16 *background1,*background2,*background3;
    s32 sp4;
    u32 decompressedSize;

    sp4 = (fillZero=0);
    CpuFastSet(&sp4, (void *)0x06000000, 0x01006000U);
    sub_08040CD0(0U, 0x80U);
    sub_080415BC();
    display=(volatile u16 *)0x04000000;
    *display = 0x60;
    background1=(volatile u16 *)0x0400000A;
    *background1 = 0x1E05;
    background2=(volatile u16 *)0x0400000C;
    *background2 = 0x1D06;
    background3=(volatile u16 *)0x0400000E;
    *background3 = 0x3C07;
    sub_0805BA34(gUnknown_0879D260, (u32) *background1);
    sub_0805BA34(gUnknown_0879D454, (u32) *background2);
    sub_0805BA34(gUnknown_0879D594, (u32) *background3);
    decompressedSize = sub_08044D0C(gUnknown_0879BE34, gUnknown_02030000);
    CpuSet(gUnknown_02030000, (void *)0x06004000, (decompressedSize << 10) >> 11);
    CpuFastSet(gUnknown_0879BC34, (void *)0x05000000, 0x80U);
    CpuFastSet(gUnknownWords_084E43F8, (void *)0x050003C0, 8U);
    LeDecompress(gMain2ObjectTiles_08785FB4, (void *)0x06010000);
    CpuFastSet(gUnknown_0850F458, (void *)0x05000200, 8U);
    gFrameObjects->flags = (frameZero=0,0x8000);
    gFrameObjects->tableSelector = 2;
    gFrameObjects->palette = 0xE;
    gFrameObjects->frameAndGroup = 6;
    gFrameObjects->screenX = 0xC;
    gFrameObjects->screenY = 0x1C;
    sub_080656DC((u8 *)gMainContextPointer_03006F74 + 0x50, 0x10U, 0U, -1U, 0xC0U);
    *display |= 0x200;
    *display |= 0x400;
    *display |= 0x800;
    *display |= 0x1000;
    ((struct LocalInitContext65D44 *)gMainContextPointer_03006F74)->phase3A = fillZero;
    ((struct LocalInitContext65D44 *)gMainContextPointer_03006F74)->byte05 = frameZero;
    ((struct LocalInitContext65D44 *)gMainContextPointer_03006F74)->byte7A = 0xFF;
    if (sub_08074CE0() != 0x18) {
        sub_08074B88(0x18U);
    }
    gUnknown_0300137C += 1;
}

void sub_0806EC30(void) {
    s32 sp0;
    struct LocalDma3Registers *dma;

    sp0 = 0;
    dma = (struct LocalDma3Registers *)0x040000D4;
    dma->source = &sp0;
    dma->destination = (void *)0x06000000;
    dma->control = 0x85006000;
    (void)dma->control;
    sp0 = 0;
    dma->source = &sp0;
    dma->destination = (void *)0x05000000;
    dma->control = 0x85000100;
    (void)dma->control;
    sp0 = 0;
    dma->source = &sp0;
    dma->destination = gFrameObjects;
    dma->control = 0x85000800;
    (void)dma->control;
    sp0 = 0;
    dma->source = &sp0;
    dma->destination = &gGraphicsTransferCounter;
    dma->control = 0x8500003E;
    (void)dma->control;
    *(volatile u16 *)0x04000000 = 0x60;
    gGraphicsTransferCounter.mode = 3;
    gGraphicsTransferCounter.selection = 1;
    gGraphicsTransferCounter.counter = 0;
    gBgScroll0.x = 0;
    gBgScroll0.y = 0;
    gBgScroll1.x = 0;
    gBgScroll1.y = 0;
    gBgScroll2.x = 0;
    gBgScroll2.y = 0;
    gBgScroll3.x = 0;
    gBgScroll3.y = 0;
    gGraphicsTransferCounter.source = 0xB;
    gGraphicsTransferCounter.position = 0xB;
    gGraphicsTransferCounter.group = 1;
    gGraphicsTransferCounter.blend = 0x7C0;
    gGraphicsTransferCounter.brightness = 0x100;
    gMain2Byte_03007008 = 0;
    gUnknown_0300137C = 8;
}
