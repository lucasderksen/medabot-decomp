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
#include "effect_work.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"
#include "input.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct Phase6113C {u8 pad0[0x84];u8 byte84;};
struct ChoiceContext65A0C {u8 pad0[8];s32 count;};
struct Phase65A0C {u8 pad0[0x1B];u8 byte1B;u8 pad1C[0x68];u8 byte84;};
struct GraphicsWork6DC7C {u16 state,substate,step,flags;s32 count;};
struct GraphicsWork6F1C0 {u16 state,substate,step,flags;s32 count;u16 savedStep;};
struct Dma6F1C0 {u32 source,destination,control;};

extern const u32 gCopySource6113C08488540[8];
extern const u32 gCopySource6113C08797910[128];
extern const void *gPalettePointer6F1C008485A78;
extern struct GraphicsWork6DC7C gGraphicsWork6DC7C03001800;
extern struct GraphicsWork6F1C0 gGraphicsWork6F1C003001800;
extern u32 gCopyDest6113C0202F800[8],gCopyDest6113C0202F9E0[8],gCopyDest6113C0202F9C0[8],gCopyDest6113C0202F820[8];
extern void sub_0803628C(void);
extern void sub_08068684(u8,u8,u16);
extern void sub_0806B718(u8);
extern void sub_0807028C(void);

u32 sub_08016E5C(u32 bank,u32 part);
void sub_0801BB7C(void);
void sub_0801E3C0(void);
void sub_0802473C(void);
void sub_0806113C(void);
void sub_08065A0C(void);
void sub_0806DC7C(void);
void sub_0806F1C0(void);

u32 sub_08016E5C(u32 bank,u32 part) {
 u8 *setup=gSetupBuffer_03000590;
 u32 partOffset=part*24,bankOffset=bank<<8;
 s32 kind=((u8 *)(partOffset+bankOffset+(u32)setup))[0x49];
 switch(kind) {
 case 0x18:case 0x19:case 0x1A:case 0x28:case 0x35:return 1;
 default:return 0;
 }
}

void sub_0801BB7C(void) {
 u32 i=0;
 u8 *work=gState0TransferWork.bytes,*frames=(u8 *)gFrameObjects;
 u16 *destination=(u16 *)(work+0x13C);
 u8 *source=frames+0x1742,*row=work;
 do {
  u32 y;
  *destination=*(u16 *)source;
  y=*(u16 *)(source+2)-4;
  *(u16 *)(row+0x13E)=y;
  destination+=2;source+=256;row+=4;i++;
 }while(i<=5);
}

void sub_0801E3C0(void) {
 u8 *work=gState0TransferWork.bytes;
 work[0xB9]=0;
 if(work[0xB7]&1)work[0xAA]=0x28;
 else if(work[0xB7]&3) {sub_0803628C();work[0xAA]=0xA;}
 else if(work[0xB8]&2)work[0xAA]=0x30;
 else if(work[0xB8]&4)work[0xAA]=0x38;
 else {sub_08036270();sub_0803628C();work[0xAA]++;}
}

void sub_0802473C(void) {
 u8 *work=gState0TransferWork.bytes,*bank=work+0x88;
 u32 remaining;
 sub_08035164(*bank,0,*(u16 *)(work+0xC8));
 {u8 *setup=gSetupBuffer_03000590;u32 offset=*bank<<8;
 remaining=((u8 *)(offset+(u32)setup))[0x59];}
 if(!remaining) {
  sub_08035234(*bank);work[0xD0]=remaining;work[0xAA]=0x1A;
 }else work[0xAA]=0x13;
}

void sub_0806113C(void) {
 *(volatile u16 *)0x04000000|=0x200;
 *(volatile u16 *)0x04000000|=0x400;
 *(volatile u16 *)0x04000000|=0x800;
 *(volatile u16 *)0x04000000|=0x1000;
 CpuFastSet(gUnknownWords_084E43F8,gCopyDest6113C0202F800,8);
 CpuFastSet(gMain2NameTransfer_084E43D8,gCopyDest6113C0202F9E0,8);
 CpuFastSet(gUnknownWords_084E43F8,gCopyDest6113C0202F9C0,8);
 CpuFastSet(gCopySource6113C08488540,gCopyDest6113C0202F820,8);
 CpuFastSet(gCopySource6113C08797910,gEquipmentPaletteShadow,128);
 ((struct Phase6113C *)&gState0TypedWork)->byte84=0;
 gUnknown_0300137C++;
}

void sub_08065A0C(void) {
 const void *const *scripts=gMain2ScriptSlots_08485678;
 struct ChoiceContext65A0C **context=(struct ChoiceContext65A0C **)&gMainContextPointer_03006F74;
 s32 value=(*context)->count;
 u32 offset=0x18;
 if(value)offset=0x1C;
 if(sub_0803FB3C(*(const void *const *)((u32)scripts+offset)) && (*(u8 *)&gNewKeys&1)) {
  sub_08074DE0(13);
  value=(*context)->count+1;
  (*context)->count=value;
  if(value>1) {
   struct Phase65A0C *phase=(struct Phase65A0C *)&gState0TypedWork;
   phase->byte84=0;
   phase->byte1B=0;
   gUnknown_0300137C--;
   return;
  }
  sub_0803FB0C();
 }
}

void sub_0806DC7C(void) {
 struct GraphicsWork6DC7C *work=&gGraphicsWork6DC7C03001800;
 s32 count=work->count;
 if(count>40) {
  work->count=0;
  sub_0806B718(2);
  sub_08068684(4,1,0);
  work->state=2;
  work->substate=3;
  work->step=0;
  gUnknown_0300137C=2;
  return;
 }
 work->count=count+1;
}

void sub_0806F1C0(void) {
 volatile struct Dma6F1C0 *dma;
 sub_0807028C();
 *(volatile u16 *)0x0400004C=255;
 gGraphicsWork6F1C003001800.flags=6;
 gBgScroll0.y=0xFFE4;
 dma=(volatile struct Dma6F1C0 *)0x040000D4;
 dma->source=(u32)gPalettePointer6F1C008485A78;
 dma->destination=0x05000200;
 dma->control=0x80000050;
 (void)dma->control;
 gGraphicsWork6F1C003001800.step=gGraphicsWork6F1C003001800.savedStep;
 gUnknown_0300137C=4;
}
