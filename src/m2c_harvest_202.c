/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "sound_tables.h"
#include "background_state.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "interrupts.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct ContinuedRefreshSetup1902C {u8 prefix[0x40];u8 active;u8 gap41[0x88];u8 mode;u8 tailCA[0x36];};
struct ContinuedSetup19EF0 {u8 prefix[0x40];u8 active;u8 tail[0xBF];};
struct ContinuedSetup1EC3C {u8 prefix[0xD6];u8 flags;u8 tail[0x29];};
struct ContinuedSetup247C8 {u8 prefix[0xBD];u8 flags;u8 tail[0x42];};
struct Continued3133CWork {u8 prefix[0x89];u8 mode;u8 gap[0xA8];u8 pending;};
struct Continued31390Frame {u8 prefix[0x840];struct FrameObject frame;};
struct DmaRegisters68978 {u32 source;u32 destination;u32 control;};

extern const u8 gFrameSequence080AFAF8[8];
extern const u8 gUnknown_084D819C[];
extern const u8 gUnknown_084D8F0C[];
extern s32 gTransferStep03000000;
extern s32 sub_0803725C(void);
extern s32 sub_0807CD2C(s32,s32);
extern s32 sub_0807CDF8(s32,s32);
extern u16 gTransferOffsets03000008[];
extern u32 sub_08033184(u32);
extern u32 sub_0803325C(u32);
extern u32 sub_08073B68(s32);
extern u8 gTransferDivisor03000005;
extern u8 gUnknown_030018D2[3];
extern void sub_0801A4F4(u8 *,u32,u32,s32,s32);
extern void sub_0801BC5C(s32 choice);
extern void sub_080351E8(u32);
extern void sub_0803579C(u32,u32);
extern void sub_08035814(u32);
extern void sub_08036CCC(u32,u32,s32);
extern void sub_08037280(u32,u32);
extern void sub_080372D4(u32,u32,s32);
extern void sub_0803D4AC(void);
extern void sub_08074DE0(u32);

void sub_08019078(void);
u32 sub_08019EF0(void);
void sub_0801EC3C(void);
void sub_0801F1C8(void);
void sub_08020AD0(void);
void sub_080247C8(void);
void sub_08026484(void);
void sub_0802DA60(void);
void sub_0803133C(void);
void sub_08031390(void);
void sub_08031538(void);
void sub_0803B374(void);
void sub_08060248(void);
s32 sub_08068978(void);
u32 sub_08073BC8(s32 input);

void sub_08019078(void) {
 u32 bank=0;
 struct ContinuedRefreshSetup1902C *setup=(struct ContinuedRefreshSetup1902C *)gSetupBuffer_03000590;
 do {
  if (setup[bank].active && (u8)(setup[bank].mode-15)>1) {
   sub_08019544(bank);
  }
  bank++;
 } while (bank<=5);
}

u32 sub_08019EF0(void) {
 s32 first=0,second=0;
 u32 bank;
 struct ContinuedSetup19EF0 *setup;
 if(gState0TypedWork.bytes[0x89]!=1 || !gUnknown_03000B90) {
  bank=0;
  setup=(struct ContinuedSetup19EF0 *)gSetupBuffer_03000590;
  do {
   if(setup[bank].active) {first+=sub_08019FBC(bank,0);second+=sub_0801A030(bank,0);}
   bank++;
  }while(bank<=5);
 }else {
  bank=3;
  setup=(struct ContinuedSetup19EF0 *)gSetupBuffer_03000590;
  do {
   if(setup[bank].active) {first+=sub_08019FBC(bank,0);second+=sub_0801A030(bank,0);}
   bank++;
  }while(bank<=5);
  bank=0;
  setup=(struct ContinuedSetup19EF0 *)gSetupBuffer_03000590;
  do {
   if(setup[bank].active) {first+=sub_08019FBC(bank,0);second+=sub_0801A030(bank,0);}
   bank++;
  }while(bank<=2);
 }
 if(first || second) return 1;
 return 0;
}

void sub_0801EC3C(void) {
 u8 *setup=gSetupBuffer_03000590;
 u8 *work=gState0TransferWork.bytes;
 u32 partOffset=work[0xA7]*24;
 u32 bankOffset=work[0x87]<<8;
 u8 *part=(u8 *)(partOffset+bankOffset+(u32)setup);
 if(part[0x49]==0x30) {
  u32 remaining=*(u16 *)(work+0xEC)-1;
  *(u16 *)(work+0xEC)=remaining;
  if(remaining<<16) work[0xAA]=0x20;
  else work[0xAA]++;
 } else if((((struct ContinuedSetup1EC3C *)(setup+bankOffset))->flags&2 || part[0x4F]) && *(u16 *)(work+0xCA)) work[0xAA]=0x20;
 else work[0xAA]++;
}

void sub_0801F1C8(void) {
 u8 *work=gState0TransferWork.bytes;
 u32 selected=sub_08033184(work[0x88]);
 if(selected) {
  u32 index=selected-1;
  work[0xD0]=index;
  work[0x8B]=index;
  sub_08036CCC(work[0x88],work[0xD0],*(s16 *)(work+0xEC));
  work[0xAA]=0x3E;
 }else work[0xAA]++;
}

void sub_08020AD0(void) {
 u8 *work=gState0TransferWork.bytes;
 u32 selected;
 u8 *setup,*part;u32 partOffset,bankOffset;
 sub_080351E8(work[0x88]);
 setup=gSetupBuffer_03000590;partOffset=work[0xA7]*24;bankOffset=work[0x87]<<8;
 part=(u8 *)(partOffset+bankOffset+(u32)setup);
 if(part[0x4F] && *(u16 *)(work+0xCA) && (selected=sub_0803325C(work[0x88]))) {
  u32 index=selected-1;
  work[0xD0]=index;
  work[0x8B]=index;
  sub_080372D4(work[0x88],work[0xD0],*(u16 *)(work+0xCA));
  work[0xAA]=0xF;
 }else work[0xAA]++;
}

void sub_080247C8(void) {
 struct ContinuedSetup247C8 *setup=(struct ContinuedSetup247C8 *)gSetupBuffer_03000590;
 u8 *work=gState0TransferWork.bytes;
 setup[work[0x88]].flags|=1;
 work[0xAA]++;
}

void sub_08026484(void) {
 u8 *work=gState0TransferWork.bytes;
 u8 *bank=work+0x87;
 u32 firstBank=*bank;
 u8 *part=work+0xA7;
 s32 ready;
 sub_0803579C(firstBank,*part);
 sub_08035814(*bank);
 ready=sub_0803725C();
 if(ready) {
  work[0xAB]=1;
  work[0xA6]=0x1A;
  work[0xAA]++;
 }else {
  sub_08036270();
  sub_08037280(*bank,*part);
  work[0xAB]=ready;
  work[0xAA]=4;
 }
}

void sub_0802DA60(void) {
 u32 i=0;
 u8 *selected=gUnknown_030018D2;
 u32 angle=0,offset=0x840,start=0x21000000;
 do {
  if(*(u8 *)(i+(u32)selected)) {
   struct FrameObject *frame;
   sub_08040D44(start>>24,1);
   frame=(struct FrameObject *)(offset+(u32)gFrameObjects);
   frame->flags|=0x220;
   frame->scaleX=0x80;
   frame->scaleY=0x80;
   frame->angle=angle;
  }
  offset+=64;start+=0x1000000;i++;
 }while(i<=2);
 gState0TransferWork.bytes[0xAA]++;
}

void sub_0803133C(void){
 struct Continued3133CWork *work;
 gUnknownCallback_030017F0=DummyInterruptHandler;
 work=(void *)&gState0TypedWork;
 work->pending=1;
 if(work->mode!=1){gMainSubstate=6;gUnknown_0300137C=48;}
 else {gMainSubstate=10;gUnknown_0300137C=32;}
}

void sub_08031390(void){
 struct Continued31390Frame *frames;
 u8 *work;u32 zero;
 LeDecompress(gUnknown_084D8F0C,(void *)0x06014800);
 frames=(void *)gFrameObjects;zero=0;
 frames->frame.flags=0xC404;frames->frame.tableSelector=zero;
 work=gState0TransferWork.bytes;
 frames->frame.screenX=(u16)gFrameObjects[work[0x87]*4+0x5D].screenX;
 frames->frame.screenY=(u16)gFrameObjects[work[0x87]*4+0x5D].screenY-4;
 frames->frame.palette=12;frames->frame.priority=0x80;
 frames->frame.frameAndGroup=0x5800;frames->frame.unknown23[0]=zero;
 sub_08074DE0(0x2A);gUnknown_0300137C++;
}

void sub_08031538(void){
 u8 *buffer;u8 *work;
 LeDecompress(gUnknown_084D819C,(void *)0x06017E00);
 buffer=gUnknown_0300052E;work=gState0TransferWork.bytes;
 sub_0801A28C(buffer,work[0x167],2);
 
 sub_0801A4F4(buffer,work[0x87],0x23,gFrameObjects[work[0x87]*4+0x5D].screenX+24,gFrameObjects[work[0x87]*4+0x5D].screenY+4);
 *(u8 *)((u32)buffer-0x6A)=0;
 gUnknown_0300137C++;
}

void sub_0803B374(void){
 u8 *setup=gSetupBuffer_03000590;u8 *work=gState0TransferWork.bytes;
 u32 offset=work[0x87]*256;u8 *row=(u8 *)(offset+(u32)setup);
 if(row[0xDD]<=3)sub_0801BC5C(*(u8 *)((work[0xA7]*24)+offset+(u32)setup+0x49));
 else sub_0801BC5C(row[0xA8]+0x50);
 sub_0803D4AC();
}

void sub_08060248(void) {
 struct FrameObject *object=gFrameObjects;
 u32 timer=object->unknown1A+1;
 const u8 *sequence;
 object->unknown1A=timer;
 if((u16)timer>0x3F) object->unknown1A=0;
 sequence=gFrameSequence080AFAF8;
 object->frameAndGroup=sequence[(object->unknown1A>>3)&7]+0x100;
}

s32 sub_08068978(void) {
 s16 fill=0;
 volatile u16 *display=(volatile u16 *)0x04000000;
 s32 *counter;
 u8 *divisor;
 const u16 *offsets;
 s32 count;
 u32 firstDivisor;
 volatile struct DmaRegisters68978 *dma;
 u32 control;
 *display|=0x100;
 counter=&gTransferStep03000000;
 divisor=&gTransferDivisor03000005;
 firstDivisor=*divisor;
 count=*counter;
 if(sub_0807CDF8(count,firstDivisor)==0) {
  dma=(volatile struct DmaRegisters68978 *)0x040000D4;
  dma->source=(u32)&fill;
  offsets=gTransferOffsets03000008;
  dma->destination=offsets[sub_0807CD2C(count,*divisor)]+0x0600C000;
  control=0x80000001;
  dma->control=control;
  (void)dma->control;
  dma->source=(u32)&fill;
  dma->destination=offsets[sub_0807CD2C(count,*divisor)]+0x0600C004;
  dma->control=control;
  (void)dma->control;
  dma->source=(u32)&fill;
  dma->destination=offsets[sub_0807CD2C(count,*divisor)]+0x0600C008;
  dma->control=control;
  (void)dma->control;
  dma->source=(u32)&fill;
  dma->destination=offsets[sub_0807CD2C(count,*divisor)]+0x0600C00C;
  dma->control=control;
  (void)dma->control;
 }
 if(*counter==*divisor*16) {
  *display &=0xFEFF;
  return 1;
 }
 return 0;
}

u32 sub_08073BC8(s32 input) {
 s32 quotient;
 s32 remainder;
 u32 factor;
 const u16 *table;
 if(input==0) return 0;
 quotient=input/128;
 remainder=input-quotient*128;
 factor=sub_08073B68(quotient);
 table=gPitchLookupAnchor083ABC5E;
 remainder*=2;
 return ((u32)*(const u16 *)((u32)table+(u32)remainder)*factor)>>12;
}
