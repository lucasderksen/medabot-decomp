/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "display_helpers.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "render_work.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"
#include "utility_helpers.h"

struct ContinuedKindRow23 {u8 before[0xC1];u8 kind;u8 tail[0x3E];};
struct ContinuedDisplayChoice23 {u8 before[0x80];u8 bank;u8 selected;u8 choice;};
struct ContinuedPhase31 {u8 before[0xAA];u8 phase;};
struct ContinuedRecord31 {u8 before[0x2A];u8 active,kind;};
struct ContinuedWork31 {u8 before[0x8A];u8 index;};
struct Work080712C8 {u8 pad0[4];u16 mode;};
struct Dma080712C8 {u32 source,destination,control;};
struct Work08072234 {u8 pad0[0x10];u8 phase,delay;};
struct Dma08072234 {u32 source,destination,control;};

extern const u32 gLookup74F74[6];
extern struct ContinuedKindRow23 gUnknown_03000590[];
extern struct Work080712C8 gWork080712C8;
extern struct Work08072234 gWork08072234;
extern u32 sub_08074F4C(u32);
extern u8 gUnknown_030018D2[3];
extern u8 gUnknown_0300199A[6];extern const u8 gUnknown_083AFE18[96];

void sub_08015E68(u32 value);
void sub_08016DCC(void);
void sub_08018BD4(void);
void sub_0801E578(void);
void sub_08027798(void);
void sub_08028078(void);
void sub_0803E8B8(void);
void sub_080712C8(void);
s32 sub_08072234(void);
s32 sub_08074F74(s32 arg0);

void sub_08015E68(u32 value) {

    if (value <= 2U) {
        sub_08042838((u32) gUnknown_03000590[value].kind, 4U, 0x12U, 2U, (u32) *(volatile u16 *)0x0400000A, 0xD220U);
        sub_08042698(1U, 1U, 6U, 0x12U, (u32) *(volatile u16 *)0x0400000A, 0xD21AU);
        sub_08042838(0x50U, 7U, 0x12U, 2U, (u32) *(volatile u16 *)0x0400000A, 0xD220U);
        return;
    }
    sub_08042838((u32) gUnknown_03000590[value].kind, 0x18U, 0x12U, 2U, (u32) *(volatile u16 *)0x0400000A, 0xD220U);
    sub_08042698(1U, 1U, 0x1AU, 0x12U, (u32) *(volatile u16 *)0x0400000A, 0xD21AU);
    sub_08042838(0x50U, 0x1BU, 0x12U, 2U, (u32) *(volatile u16 *)0x0400000A, 0xD220U);
}

void sub_08016DCC(void) {

    void *temp_r1;

    if (((struct ContinuedDisplayChoice23 *)&gState0TransferWork)->choice == 1) {
        sub_08042698(2U, 1U, 0xEU, 0xCU, (u32) *(volatile u16 *)0x04000008, 0xD218U);
        {
        u8 *setup=gSetupBuffer_03000590;
        temp_r1 = (void *)((((struct ContinuedDisplayChoice23 *)&gState0TransferWork)->bank << 8) + (u32)setup);
        sub_08042A90((u32) (*(u8 *)((u8 *)(temp_r1) + 0x58)), (u32) (*(u8 *)((u8 *)(temp_r1) + 0x50)), 0x10U, 0xCU, 0xD21AU, (u32) *(volatile u16 *)0x04000008, 0xD220U);
        }
        return;
    }
    sub_0803EF8C(7U, 1U, 0xEU, 0xCU, (u32) *(volatile u16 *)0x04000008, 0U);
}

void sub_08018BD4(void) {

    if(gState0TypedWork.bytes[0x89]==1){gState0TransferWork.bytes[0x57]=0x28;return;}
    switch(gMainByte_03001788){
    case 0:gState0TransferWork.bytes[0x57]=0x28;break;
    case 1:gState0TransferWork.bytes[0x57]=0x1E;break;
    case 2:gState0TransferWork.bytes[0x57]=0x14;break;
    }
}

void sub_0801E578(void) {

    u8 *setup=gSetupBuffer_03000590;
    u8 *work=gState0TransferWork.bytes;
    u8 *record=(u8 *)(work[0xA7]*24+(work[0x87]<<8)+(u32)setup);
    if(record[0x49]==0x30){
        ((struct ContinuedPhase31 *)work)->phase++;
    }else if(*(u8 *)((work[0x88]<<8)+(u32)(setup+0xBC))&0x20){
        ((struct ContinuedPhase31 *)work)->phase++;
    }else{
        ((struct ContinuedPhase31 *)work)->phase=10;
    }
}

void sub_08027798(void) {

    u32 result=0,i=0;
    u8 *selected=gUnknown_030018D2;
    u32 frame=0x21;
    do{if(*(u8 *)(i+(u32)selected)&0x80)result=sub_080370AC(frame,4);frame+=4;i++;}while(i<=2);
    if(result)((struct ContinuedPhase31 *)&gState0TransferWork)->phase++;
}

void sub_08028078(void) {

    struct ContinuedWork31 *work=(struct ContinuedWork31 *)&gState0TransferWork;
    struct ContinuedRecord31 *record=(struct ContinuedRecord31 *)(work->index*8+(u32)work);
    if(record->active && record->kind==0x5A){
        gFrameObjects[0x21].unknown23[4]=0;
        ((struct ContinuedPhase31 *)work)->phase++;
    }else{
        struct ContinuedPhase31 *phase;
        sub_08074DE0(0x3E);
        phase=(struct ContinuedPhase31 *)&gState0TransferWork;
        phase->phase+=2;
    }
}

void sub_0803E8B8(void) {
u32 selected=sub_080424B8()&0xF;u32 index=0;u8 *choices=gUnknown_0300199A;const u8 *source=gUnknown_083AFE18;source+=selected*6;do{*(u8 *)(index+(u32)choices)=*source;source++;index++;}while(index<=5);}

void sub_080712C8(void) {

    u32 sp0;
    volatile struct Dma080712C8 *dma;

    sp0 = 0;
    dma=(volatile struct Dma080712C8 *)0x040000D4;
    dma->source = (u32)&sp0;
    dma->destination=(u32)gFrameObjects;
    dma->control=0x85000800;
    (void)dma->control;
    gWork080712C8.mode = 0xD;
    gUnknown_0300137C = 5;
}

s32 sub_08072234(void) {

    u32 sp20;
    volatile struct Dma08072234 *dma;

    sp20 = 0x200;
    dma=(volatile struct Dma08072234 *)0x040000D4;
    dma->source = (u32)&sp20;
    dma->destination=(u32)gRenderWork->objects;
    dma->control=0x85000100;
    (void)dma->control;
    sub_080446B4(0U, 0x2BU, 0x2BU, 0x2BU, 0x2BU, 0x40U, 0x42U, 2U, 8U, 0U, 1U, 0U);
    sub_08044A3C(0U, 0x2CU, 0U);
    gWork08072234.phase = (u8) (gWork08072234.phase + 1);
    gWork08072234.delay = 0;
    return 0;
}

s32 sub_08074F74(s32 arg0) {

 u32 index=0;
loop:
 if ((u32)arg0 != sub_08074F4C(gLookup74F74[index])) {
  index++;
  if(index<=5)goto loop;
  return 0;
 }
 return 1;
}
