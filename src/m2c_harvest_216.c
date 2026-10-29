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
#include "display_helpers.h"
#include "effect_work.h"
#include "frame.h"
#include "gba.h"
#include "input.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinuedLargeWork27 {u8 before[0xC2E];u8 flags;};
struct ContinuedPhaseWork27 {u8 before[0xAA];u8 phase;};
struct ContinuedFlagWork27 {u8 before[0xF8];u8 flags;};
struct ContinueTestWork {u8 pad[0x87];u8 bank;u8 pad2[0x1F];u8 part;u8 pad3[0x10];u8 action;u8 pad4[6];u8 kind;};
struct SceneWork6030C {u8 pad0[0x36];s16 tileBase;};
struct Dma6E1EC {u32 source,destination,control;};
struct ResetGraphicsWork6E1EC {u16 flags,bank;u8 pad4[8];u16 selection;u8 padE[2];};
struct ResetFreshWork6E1EC {u8 pad0;u8 selection;};

extern const u32 gPalette6030C080AFB00[8];
extern const u32 gPalette6030C08792E9C[56];
extern const u8 gAsset6030C08792F7C[];
extern const u8 gTilemap6030C08793EC4[];
extern const u8 gTilemap6030C08794060[];
extern const u8 gTilemap6030C087941B8[];
extern const u8 gTiles6030C08787144[];
extern const u8 gUnknown_083AD530[];
extern const void *const gUnknownPointers_083CF530[];
extern struct ContinueTestWork gUnknown_03001800;
extern struct ResetFreshWork6E1EC gResetFreshWork6E1EC;
extern struct ResetGraphicsWork6E1EC gResetGraphicsWork6E1EC;
extern u32 sub_080330F4(s32);
extern u32 sub_08035AAC(u32,u32,u32);
extern u32 sub_08035AFC(u32,u32,u32);
extern u32 sub_08035B4C(u32,u32,u32);
extern u8 gContinuedWork_030057E0[0xC2F];
extern u8 gScratch6030C02030000[];
extern u8 gUnknown_03001988[2];
extern void sub_0803836C(void);
extern void sub_0803D4AC(void);
extern void sub_0803E894(void);

void sub_08018A54(void);
void sub_0802121C(void);
void sub_0802167C(void);
void sub_0802463C(void);
void sub_0802D758(void);
void sub_0803934C(void);
void sub_0803B884(void);
void sub_0803DEB0(void);
void sub_08042238(u8 arg0);
void sub_0806030C(void);
void sub_0806E1EC(void);

void sub_08018A54(void) {
    s32 temp_r1;

    if (gState0TypedWork.bytes[0x89] == 1) {
        sub_08074B88(9U);
        return;
    }
    temp_r1 = 0xF0 & ((struct ContinuedLargeWork27 *)gContinuedWork_030057E0)->flags;
    if (temp_r1 != 0) {
        if (temp_r1 == 0x10) {
            sub_08074B88(0xCU);
            return;
        }
        sub_08074B88(0xDU);
        return;
    }
    {const u8 *table=gUnknown_083AD530;u32 key=gMainByte_03000B94;
    sub_08074B88(*(const u8 *)(key+(u32)table));}
}

void sub_0802121C(void) {

 u32 snapshot;
 gState0TypedWork.widths.word86-=1;
 snapshot=gState0TypedWork.bytes[0x89];
 if(!snapshot && ((*(u8 *)&gRepeatedKeys)&1)) gState0TypedWork.widths.word86=snapshot;
 {u32 remaining=gState0TypedWork.widths.word86;
 if(remaining==0) {
  u8 *work=gState0TransferWork.bytes;
  switch((s32)work[0x51]) {
  case 0:case 1:case 2:
   gFrameObjects[0x21].unknown23[4]=remaining;
   work[0xAA]++;break;
  case 3:sub_08074DE0(0x52);work[0xAA]=0x20;break;
  }
 }
 }
}

void sub_0802167C(void) {
    u32 snapshot;

    gState0TypedWork.widths.word86 -= 1;
    snapshot=gState0TypedWork.bytes[0x89];
    if ((snapshot == 0) && (1 & *(u8 *)&gRepeatedKeys)) {
        gState0TypedWork.widths.word86 = snapshot;
    }
    if (gState0TypedWork.widths.word86 == 0) {
        sub_0803F63C(gActionTransferBuffer_03003470, gActionTransferBuffer_03003470 + 0x40, 0x40U);
        sub_0803F63C(gActionTransferBuffer_03003470, gActionTransferBuffer_03003470 + 0x80, 0x40U);
        (*(s16 *)((u8 *)(gActionTransferBuffer_03003470) + 0x32)) = 0x58;
        (*(s8 *)((u8 *)(gActionTransferBuffer_03003470) + 0x24)) = 6;
        (*(s16 *)((u8 *)(gActionTransferBuffer_03003470) + 0x72)) = 0x40;
        (*(s8 *)((u8 *)(gActionTransferBuffer_03003470) + 0x64)) = 6;
        (*(s16 *)((u8 *)((gActionTransferBuffer_03003470 + 0x72)) + 0x40)) = 0x28;
        (*(s8 *)((u8 *)(gActionTransferBuffer_03003470) + 0xA4)) = 6;
        if (!(1 & ((struct ContinuedFlagWork27 *)&gState0TransferWork)->flags)) {
            (*(s16 *)((u8 *)(gActionTransferBuffer_03003470) + 0x30))=0x88;
            (*(s16 *)((u8 *)(gActionTransferBuffer_03003470) + 0x70))=0x88;
            (*(s16 *)((u8 *)(gActionTransferBuffer_03003470) + 0xB0))=0x88;
        } else {
            (*(s16 *)((u8 *)(gActionTransferBuffer_03003470) + 0x30))=0x68;
            (*(s16 *)((u8 *)(gActionTransferBuffer_03003470) + 0x70))=0x68;
            (*(s16 *)((u8 *)(gActionTransferBuffer_03003470) + 0xB0))=0x68;
        }
        gState0TransferWork.bytes[0xAA] = (u8) (gState0TransferWork.bytes[0xAA] + 1);
    }
}

void sub_0802463C(void) {
 u8 *setup=gSetupBuffer_03000590;u8 *initial=gState0TransferWork.bytes;u32 bank=initial[0x88];
 u8 *buffer;u8 *work;
    if (4 & (*(u8 *)((u8 *)(((bank << 8) + setup)) + 0xBD))) {
        sub_08034F68(bank, 0U, 1);
    } else {
        sub_08034F68(bank, 0U, (s32) (*(s16 *)((u8 *)(initial) + 0xEC)));
    }
    buffer=gUnknown_0300052E;work=gState0TransferWork.bytes;
    sub_0801A28C(buffer, (u32) (*(u16 *)((u8 *)(work) + 0xC8)), 1U);
    sub_0801A33C(buffer, (u32) (*(u8 *)((u8 *)(work) + 0x88)), 0x21U);
    sub_08074DE0(0x5BU);
    *(u8 *)((u32)buffer-0x6A) = 0;
    (*(u8 *)((u8 *)(work) + 0xAA)) = (u8) ((*(u8 *)((u8 *)(work) + 0xAA)) + 1);
}

void sub_0802D758(void) {
 s32 found=0;
 u8 *work;
 u8 *setup;
 u8 *flags;
 u8 *first;
 u32 i;
 do {
 sub_0803836C();
 work=gState0TransferWork.bytes;
 work[0x60]=sub_08032FB8(work[0x87]);
 } while(0);
 i=0;setup=gSetupBuffer_03000590;first=work+0x60;flags=work+0xD2;
 do {
  u32 slot=*first+i;
  u32 address=(slot<<8)+(u32)setup;
  if(*(u8 *)(address+0x40) && *(u8 *)(address+0x59) && sub_080331F8(slot)) {
   *(u8 *)(i+(u32)flags)=((s32)sub_080330F4(*first+i))-0x80;found=1;
  }
  i++;
 } while(i<=2);
 if(!found) ((struct ContinuedPhaseWork27 *)&gState0TransferWork)->phase++;
 else ((struct ContinuedPhaseWork27 *)&gState0TransferWork)->phase+=3;
}

void sub_0803934C(void) {
 struct ContinueTestWork *work=&gUnknown_03001800;
 u32 bank=work->bank;
 if(sub_08035AAC(bank,work->part,bank)) {work->action=4;work->kind=2;return;}
 bank=work->bank;
 if(sub_08035AFC(bank,work->part,bank)) {work->action=4;work->kind=3;return;}
 bank=work->bank;
 if(sub_08035B4C(bank,work->part,bank)) {work->action=4;work->kind=4;}
}

void sub_0803B884(void) {
 u32 i=0;
 u32 root=(u32)&gFrameObjects;
 const u8 *source=gUnknown_03001988;
 u32 zero=0;
 u32 cursor=root+0x2A3;
 u32 delay=0x3A;
 do {
  *(u8 *)(cursor+5)=*(const u8 *)(i+(u32)source);
  *(u8 *)cursor=zero;
  *(u8 *)(cursor+6)=delay;
  *(u8 *)(cursor+3)=i+0x56;
  cursor+=0x40;
  i++;
 }while(i<=1);
 sub_08074DE0(0x10);
 sub_0803D4AC();
}

void sub_0803DEB0(void) {
    const void *var_r0;

    sub_0803E894();
    if (gState0TypedWork.bytes[0x9C] == 1) {
        var_r0 = gUnknownPointers_083CF530[2];
    } else {
        var_r0 = gUnknownPointers_083CF530[3];
    }
    if (sub_0803FB3C(var_r0) != 0) {
        gUnknown_0300137C += 1;
    }
}

void sub_08042238(u8 arg0) {
    struct State0Record8 *var_r1;
    u32 var_r4;
    u32 one;
    u32 duration;
    u32 temp_r2;
    u32 temp_r3;

    var_r4 = 0;
    one=1;
    temp_r3=arg0 & one;
    temp_r2 = temp_r3 + 0x78;
    var_r1 = gUnknownRecords_030017A0;
    duration=0x1E;
    while(var_r4<=8) {
    if (var_r1->unknown00[0] == 0) {
        var_r1->unknown00[0] = one;
        var_r1->unknown00[1] = temp_r3;
        var_r1->unknown00[2] = duration;
        var_r1->byte3 = temp_r2;
        var_r1->byte4 = temp_r2;
        var_r1->byte5 = temp_r2;
        var_r1->byte6 = temp_r2;
        return;
    }
    var_r1 += 1;
    var_r4 += 1;
    }
}

void sub_0806030C(void) {
    u32 var_r4;
    u16 backgroundControl;
    volatile u16 *bg0,*bg1;
    void *scratch;
    const void *compressed;
    struct SceneWork6030C *work;

    bg0=(volatile u16 *)0x04000008;
    backgroundControl=0x1F04;
    *bg0 = backgroundControl;
    bg1=(volatile u16 *)0x0400000A;
    backgroundControl-=0xFF;
    *bg1 = backgroundControl;
    scratch=(void *)0x0400000E;
    backgroundControl=0x3C07;
    *(volatile u16 *)scratch = backgroundControl;
    sub_0805BA34(gTilemap6030C08793EC4, (u32) *bg0);
    sub_0805BA34(gTilemap6030C08794060, (u32) *bg1);
    sub_0805BA34(gTilemap6030C087941B8, (u32) *(volatile u16 *)scratch);
    compressed=gAsset6030C08792F7C;
    scratch=gScratch6030C02030000;
    var_r4 = sub_08044D0C(compressed, scratch);
    CpuSet(scratch, (void *)0x06004000, (u32) ((var_r4 + (var_r4 >> 0x1F)) << 0xA) >> 0xB);
    work=(struct SceneWork6030C *)gMainContextPointer_03006F74;
    if ((s32) var_r4 < 0) {
        var_r4 += 0x1F;
    }
    work->tileBase = (s16) (((s32) var_r4 >> 5) - 1);
    CpuFastSet(gPalette6030C08792E9C, (void *)0x05000000, 0x38U);
    CpuFastSet(gPalette6030C080AFB00, (void *)0x05000200, 8U);
    LeDecompress(gTiles6030C08787144, (void *)0x06010000);
    gFrameObjects->flags = 0xC000;
    gFrameObjects->tableSelector = 2;
    gFrameObjects->palette = 0;
    gFrameObjects->frameAndGroup = 0x112;
    gFrameObjects->screenX = 0x70;
    gFrameObjects->screenY = 0x18;
    gFrameObjects->unknown1A = 0;
    gUnknown_0300137C += 1;
}

void sub_0806E1EC(void) {
    u32 sp0;
    volatile struct Dma6E1EC *dma;

    sp0 = 0;
    dma=(volatile struct Dma6E1EC *)0x040000D4;
    dma->source=(u32)&sp0;
    dma->destination=0x06000000;
    dma->control = 0x85006000;
    (void)dma->control;
    sp0 = 0;
    dma->source=(u32)&sp0;
    dma->destination=0x05000000;
    dma->control = 0x85000100;
    (void)dma->control;
    sp0 = 0;
    dma->source=(u32)&sp0;
    dma->destination=(u32)gFrameObjects;
    dma->control = 0x85000800;
    (void)dma->control;
    sp0 = 0;
    dma->source=(u32)&sp0;
    dma->destination=(u32)&gResetGraphicsWork6E1EC;
    dma->control = 0x85000004;
    (void)dma->control;
    *(volatile u16 *)0x04000000 = 0x60;
    gResetGraphicsWork6E1EC.flags = 3;
    gResetGraphicsWork6E1EC.bank = 3;
    gResetGraphicsWork6E1EC.selection = (u16) gResetFreshWork6E1EC.selection;
    gBgScroll0.x = 0;
    gBgScroll0.y = 0;
    gBgScroll1.x = 0;
    gBgScroll1.y = 0;
    gBgScroll2.x = 0;
    gBgScroll2.y = 0;
    gBgScroll3.x = 0;
    gBgScroll3.y = 0;
    gUnknown_0300137C = 3;
}
