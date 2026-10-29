/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "composite_graphics.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "display_effects.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "graphics.h"
#include "main.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "object_numeric_helpers.h"
#include "record_helpers.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"
#include "utility_helpers.h"

struct ContinuedSelectionContext17D50 {u8 prefix[0x3C];u8 mode,choice;};
struct ContinuedAssetBank17D50 {u8 prefix;u8 asset;u8 tail[254];};
struct ContinuedRefreshSetup1902C {u8 prefix[0x40];u8 active;u8 gap41[0x88];u8 mode;u8 tailCA[0x36];};
struct Continued2ED34Frames { u8 pad00[0x840]; struct FrameObject frame[3]; };
struct Continued2ED34Work { u8 pad00[0xAA]; u8 phaseAA; };
struct FadeWork5FEC8 {u8 countdown;u8 field1;u16 phase;};
struct FadeWork609D4 {u8 countdown;u8 field1;u16 phase;};
struct ChoiceWork62754 {u8 pad0[0x2A];u8 choice;};
struct DmaRegisters69E1C {u32 source;u32 destination;u32 control;};
struct FrameWork69E1C {u8 pad0[0x42];s16 x;s16 y;u8 pad46[0x14];u16 timer;};
struct GraphicsWork6E96C {u16 field0;u16 field2;u16 field4;u16 field6;s32 counter;};
struct EnvelopeWorkQ14 {u8 pad0[0x50];u8 flags;u8 pad51[0xE];u8 countdown;s8 step;u8 pad61[5];u8 level;};

#include "action_scene_data.h"
extern const u32 gPalette0807C3D0[8];
extern const u8 gUnknown_083C4D90[];
extern struct GraphicsWork6E96C gGraphicsWork6E96C03001800;
extern u8 gUnknown_030018D2[3];
extern void sub_080190B8(s32);
extern void sub_08019184(u32,u32);
extern void sub_080605A0(void);
extern void sub_08060620(void);
extern void sub_08068684(u8,u8,u16);
extern void sub_080724D8(void *);
extern void sub_0807250C(void *);

void sub_08017D50(void);
void sub_0801902C(void);
void sub_080191E4(s32 bank);
void sub_0801BC5C(s32 choice);
void sub_0801C23C(void);
void sub_0802ED34(void);
void sub_08059E68(void);
void sub_0805FEC8(void);
void sub_080609D4(void);
void sub_08062754(void);
void sub_08069E1C(void);
void sub_0806E96C(void);
void sub_080725D0(struct EnvelopeWorkQ14 *work);
void sub_08072618(struct EnvelopeWorkQ14 *work);

void sub_08017D50(void) {
 struct ContinuedAssetBank17D50 *setup=(struct ContinuedAssetBank17D50 *)gSetupBuffer_03000590;
 struct ContinuedSelectionContext17D50 *context=(struct ContinuedSelectionContext17D50 *)gState0TypedWork.bytes;
 u8 *choice=&context->choice;
 u32 bank=context->mode*3+*choice;
 CpuFastSet(gUnknownBytes_084C29D8+(setup[bank].asset<<7),(void *)0x06007800,0x20);
}

void sub_0801902C(void) {
 u32 bank=0;
 struct ContinuedRefreshSetup1902C *setup=(struct ContinuedRefreshSetup1902C *)gSetupBuffer_03000590;
 do {
  if (setup[bank].active && (u8)(setup[bank].mode-15)>1) {
   sub_080190B8(bank);
   sub_08019348(bank);
   sub_08019544(bank);
  }
  bank++;
 } while (bank<=5);
}

void sub_080191E4(s32 bank) {
 u8 *work=gState0TransferWork.bytes;
 u8 *column=work+0x38;
 u8 *setup=gSetupBuffer_03000590;
 s32 offset=(setup[(bank<<8)+0x91]-100)*11+*column;
 const u8 *text=(const u8 *)((u32)gUnknown_083C4D90+offset);
 u8 *destination=gUnknown_0300052E;
 sub_08041D04(text,destination,1);
 sub_08019184(bank,destination[0]);
}

void sub_0801BC5C(s32 choice) {
 const struct ActionGraphicPiece *initial=gUnknown_083CE600[choice];
 const struct ActionGraphicPiece *piece;
 u8 *destination=(u8 *)0x02000000;
 if (initial->units) {
  const struct CompositeGraphicAsset *assets=gUnknown_083B2704;
  piece=initial;
  do {
   sub_08044B28(assets[piece->asset].data,destination);
   destination+=piece->units<<5;
   piece++;
  } while (piece->units);
 }
}

void sub_0801C23C(void) {
 if (gFrameCounter&1) {
  u8 *work;
  u8 *phase;
  s32 updatedY;
  gFrameObjects[3].screenY=(u16)gFrameObjects[3].screenY+1;
  updatedY=gFrameObjects[3].screenY;
  work=gState0TransferWork.bytes;
  if (updatedY==gFrameObjects[work[0x87]*4+0x5D].screenY+4) {
   phase=work+0x9D;
   *phase=0;
   phase--;
   (*phase)++;
  }
 }
}

void sub_0802ED34(void) {
 s32 done=0;
 u32 slot=0;
 u8 *selected=gUnknown_030018D2;
 struct Continued2ED34Frames *frames=(void *)&gFrameObjects;
 struct FrameObject *frame=frames->frame;
 do {
  if(*(u8 *)(slot+(u32)selected)) {
   u8 scale=frame->scaleX;
   if(scale==0x40) done=1;
   else { frame->scaleX=scale-4; frame->scaleY-=4; }
  }
  frame++;
  slot++;
 }while(slot<=2);
 if(done) {
  sub_08074DE0(0x51);
  ((struct Continued2ED34Work *)&gState0TransferWork)->phaseAA++;
 }
}

void sub_08059E68(void) {
    s32 sp0;
    u32 bgControl;
    volatile u16 *bgRegister;

    sp0 = 0;
    CpuFastSet(&sp0, (void *)0x06008000, 0x01001000U);
    LeDecompress(gMain2AdditionalTiles_08785EC0, (void *)0x06008020);
    CpuFastSet(gMain2NameTransfer_08483534, (void *)0x05000020, 8U);
    bgRegister=(volatile u16 *)0x0400000C;
    bgControl=0x1608;
    *bgRegister = bgControl;
    *(volatile u16 *)0x04000000 |= 0x400;
}

void sub_0805FEC8(void) {
 struct FadeWork5FEC8 *work=(struct FadeWork5FEC8 *)gMainContextPointer_03006F74;
 u32 previous=work->countdown;
 u32 packed=previous<<24;
 u32 remaining=packed>>24;
 if(remaining!=0) {
  volatile u16 *bldy=(volatile u16 *)0x04000054;
  work->countdown=previous+0xFF;
  *bldy=packed>>25;
  return;
 }
 work->phase=remaining;
 gFrameObjects[1].flags |=0x4000;
 gFrameObjects[1].unknown1A=remaining;
 gUnknown_0300137C++;
}

void sub_080609D4(void) {
 struct FadeWork609D4 *work=(struct FadeWork609D4 *)gMainContextPointer_03006F74;
 u32 previous=work->countdown;
 u8 remaining=previous;
 if(remaining!=0) {
  volatile u16 *bldy=(volatile u16 *)0x04000054;
  u32 next=previous-1;
  work->countdown=next;
  *bldy=(u32)(u8)next*2;
 } else {
  work->phase=remaining;
  sub_0803FAA0(1,2,0);
  gUnknown_0300137C++;
 }
 sub_080605A0();sub_08060620();
}

void sub_08062754(void) {

    if (sub_08041CA4() != 0) {
        if (((struct ChoiceWork62754 *)&gState0TypedWork)->choice == 0) {
            sub_08040D0C(0x61U, 7U);
            sub_08040D0C(0xDU, 0x34U);
            sub_08040D0C(0x45U, 0x1CU);
            gUnknown_0300137C=5;
        } else {
            gUnknown_0300137C=4;
        }

    }
}

void sub_08069E1C(void) {
 u32 zero;
 struct FrameWork69E1C *frames;
 s16 *xPointer;
 volatile struct DmaRegisters69E1C *dma;
 sub_08048864(1,0xC404,0x100,1,3);
 frames=(struct FrameWork69E1C *)gFrameObjects;
 xPointer=&frames->x;
 zero=0;
 *xPointer=0x28;
 frames->y=0x10;
 frames->timer=zero;
 dma=(volatile struct DmaRegisters69E1C *)0x040000D4;
 dma->source=(u32)gPalette0807C3D0;
 dma->destination=0x05000220;
 dma->control=0x84000008;
 (void)dma->control;
}

void sub_0806E96C(void) {
 s32 counter=gGraphicsWork6E96C03001800.counter;
 struct GraphicsWork6E96C *work=&gGraphicsWork6E96C03001800;
 if(counter==0) {*(volatile u16 *)0x04000000 &= 0xFEFF;}
 else if(counter>0x3C) {
  work->counter=0;
  sub_08068684(2,4,0);
  work->field4=10;
  gUnknown_0300137C=2;
  return;
 }
 work->counter++;
}

void sub_080725D0(struct EnvelopeWorkQ14 *work) {
 u32 count=work->countdown-1;
 s32 level;
 u8 *levelPointer;
 work->countdown=count;
 if((u8)count==0xFF) {sub_0807250C(work);return;}
 levelPointer=&work->level;
 level=work->step+*levelPointer;
 if(level > 15) level=15;
 *levelPointer=level;
 work->flags|=2;
}

void sub_08072618(struct EnvelopeWorkQ14 *work) {
 u32 count=work->countdown-1;
 s32 level;
 u8 *levelPointer;
 work->countdown=count;
 if((u8)count==0xFF) {sub_080724D8(work);return;}
 levelPointer=&work->level;
 level=work->step+*levelPointer;
 if(level < 0) level=0;
 *levelPointer=level;
 work->flags|=2;
}
