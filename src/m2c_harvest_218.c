/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "display_helpers.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "record_helpers.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinuedKindWork28 {u8 before[0x51];u8 kind;};
struct ContinuedChoiceWork28 {u8 before[0x8B];u8 choice;};
struct ContinuedBankWork28 {u8 before[0x87];u8 bank;};
struct ContinuedCoordinates28 {u8 before[2];u16 x,y;u8 after[58];};
struct ContinuedPhaseWork28 {u8 before[0xAA];u8 phase;};
struct ContinuePairWork {u8 pad[0x5C];u8 bank,part,pair[2];};
struct Dma69320 {u32 source,destination,control;};
struct PaletteWork71FF8 {u8 pad0[0x10];u8 phase,delay;};
struct Dma71FF8 {u32 source,destination,control;};

extern const u8 *const gDebugMedalMetadata_083B6590[];
extern const u8 *const gState0NextCommands_083B6100[];
extern struct ContinuePairWork gUnknown_03001800;
extern struct PaletteWork71FF8 gPaletteWork71FF803001800;
extern u16 *gPalettePointer71FF80300700C;
extern void sub_08035928(s32,s32);
extern void sub_08035944(s32,s32);

void sub_08017D90(void);
s32 sub_08018FF0(u32 bank,u32 part,s32 amount);
void sub_0801DDDC(void);
void sub_080211C8(void);
void sub_08024DA8(void);
void sub_08026284(void);
void sub_08032F64(void);
void sub_08033154(u32 bank,u32 part);
void sub_08069320(void);
s32 sub_08071FF8(void);

void sub_08017D90(void) {
 const u8 *const *metadata;
 u8 *setup;
 u8 *work;
 u8 *part;
 u32 bank;
 const u8 *record;
 const u8 *label;
 u8 *destination;
 sub_08040D0C(0x16,0xA);
 metadata=gDebugMedalMetadata_083B6590;setup=gSetupBuffer_03000590;work=gState0TypedWork.bytes;
 part=work+0x3D;bank=work[0x3C];
 record=setup+((bank*3+*part)<<8);
 label=metadata[record[1]];
 destination=work+0x9E;
 sub_0803F63C(label,destination,11);
 sub_08040DB8(destination,0x16,13,2,7,12,1,2);
}

s32 sub_08018FF0(u32 bank,u32 part,s32 amount) {
 u8 *setup=gSetupBuffer_03000590;
 u8 *record=(u8 *)((part*24+(bank<<8))+(u32)setup);
 u8 *remainingByte=record+0x59;
 u32 initial=*remainingByte;
 s32 available=initial-1;
 s32 result;
 if((s32)((u32)available-(u32)amount)>=0) {*remainingByte=initial-amount;result=amount;}
 else {*remainingByte=1;result=(((u32)amount-(u32)available)<<8)+available;}
 return result;
}

void sub_0801DDDC(void) {
 u8 *work=gState0TransferWork.bytes;
 u8 *bank=work+0x87;
 u32 bankFirst=*bank;
 u8 *selected=work+0xDE;
 sub_08035928(bankFirst,*selected);
 {u32 bankSnapshot=*bank;u8 *setup=gSetupBuffer_03000590;
  u32 choice=*selected;
  sub_08035944(bankSnapshot,*(u8 *)((((choice-1)<<8)+(u32)setup)+0xDE));}
 work[0xB5]=1;
}

void sub_080211C8(void) {
 u32 scale=gFrameObjects[0x21].scaleX+8;
 gFrameObjects[0x21].scaleX=scale;
 if((u8)scale==0x40) {
  u8 *work;
  u32 selected=((struct ContinuedKindWork28 *)&gState0TransferWork)->kind;
  work=gState0TransferWork.bytes;
  if(selected==3) {gState0TypedWork.widths.word86=1;}
  else {gState0TypedWork.widths.word86=0x3C;}
  work[0xAA]++;
 }
}

void sub_08024DA8(void) {
 const void *label;
 switch(((struct ContinuedChoiceWork28 *)&gState0TransferWork)->choice) {
 case 1: label=gState0PartMessages_083C6F68[1];break;
 case 2: label=gState0PartMessages_083C6F68[2];break;
 default:label=gState0PartMessages_083C6F68[0];break;
 }
 sub_0803F63C(label,gDebugMenuTextBuffer,14);
 {u8 *work=gState0TransferWork.bytes;work[0xA6]=0x30;work[0xAA]++;}
}

void sub_08026284(void) {
    sub_08040BD8(gState0NextCommands_083B6100[0x4A], 0x21U);
    if (gFrameObjects[0x21].commandStopped == 0xFF) {
        gFrameObjects[0x21].scaleX = 0x80;
        gFrameObjects[0x21].scaleY = 0x80;
        gFrameObjects[0x21].frameAndGroup = 0x5604;
        {u32 bank=((struct ContinuedBankWork28 *)&gState0TransferWork)->bank;
         u32 offset=(bank<<8)+0x1740;
         gFrameObjects[0x21].screenY=((struct ContinuedCoordinates28 *)(offset+(u32)gFrameObjects))->y-4;}
        ((struct ContinuedPhaseWork28 *)&gState0TransferWork)->phase = (u8) (((struct ContinuedPhaseWork28 *)&gState0TransferWork)->phase + 1);
    }
}

void sub_08032F64(void) {
 struct ContinuePairWork *root=&gUnknown_03001800;
 u8 *out=&root->pair[0];u32 zero=0;u8 *setup;u32 part,bank;u8 *record;
 *out=zero;out++;*out=zero;setup=gSetupBuffer_03000590;
 part=root->part*24;bank=root->bank<<8;record=(u8 *)(part+bank+(u32)setup);record[0x56]=zero;
 part=root->part*24;bank=root->bank<<8;record=(u8 *)(part+bank+(u32)setup);record[0x57]=zero;
}

void sub_08033154(u32 bank,u32 part) {
 u32 second;u8 *setup=gSetupBuffer_03000590;
 u8 *record=(u8 *)(part*24+(bank<<8)+(u32)setup);
 u32 first=gUnknown_03001800.pair[0];record[0x56]=first;
 second=gUnknown_03001800.pair[1];record[0x57]=second;
}

void sub_08069320(void) {
    u32 sp0;
    volatile struct Dma69320 *dma;

    sp0 = 0;
    dma=(volatile struct Dma69320 *)0x040000D4;
    dma->source=(u32)&sp0;
    dma->destination=0x06000000;
    dma->control = 0x85006000;
    (void)dma->control;
    *(volatile u16 *)0x04000000 = 0x60;
    sp0 = 0;
    dma->source=(u32)&sp0;
    dma->destination=(u32)gFrameObjects;
    dma->control = 0x85000800;
    (void)dma->control;
    gBgScroll0.x = 0;
    gBgScroll0.y = 0;
    gBgScroll1.x = 0;
    gBgScroll1.y = 0;
    gBgScroll2.x = 0;
    gBgScroll2.y = 0;
    gBgScroll3.x = 0;
    gBgScroll3.y = 0;
}

s32 sub_08071FF8(void) {
    s32 temp_r0;
    volatile struct Dma71FF8 *dma;

    if (1 & gFrameObjects->unknown1A++) {
        temp_r0 = (u16) gFrameObjects->screenY + 1;
        gFrameObjects->screenY = temp_r0;
        if (((u32)temp_r0 << 0x10) == 0) {
            sub_08074DE0(0x59U);
        }
    }
    gFrameObjects->frameAndGroup = (((u16) gFrameObjects->unknown1A >> 2) & 3) + 0x50F;
    if ((s32) gFrameObjects->screenY > 0x3F) {
        sub_08074DE0(7U);
        gPalettePointer71FF80300700C = gEquipmentPaletteShadow;
        gPaletteWork71FF803001800.delay = 0;
        dma=(volatile struct Dma71FF8 *)0x040000D4;
        dma->source=0x05000200;
        dma->destination=(u32)gEquipmentPaletteShadow;
        dma->control=0x84000080;
        (void)dma->control;
        gPaletteWork71FF803001800.phase = (u8) (gPaletteWork71FF803001800.phase + 1);
    }
    return 0;
}
