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
#include "frame.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ResetBytes42 {u8 beforeA1[0xA1];u8 fields[5];};
struct Work309C8 {u8 before87[0x87];u8 bank;u8 beforeA6[0x1E];u8 mode;};

extern const u8 gUnknown_083AD579[];
extern s32 sub_0807CD2C(s32,s32);
extern struct ResetBytes42 gGraphicsTransferCounter;
extern struct Work309C8 gCounter6ED08_03001800;

u32 sub_08018FB8(u32 bank,u32 slot,u32 amount);
void sub_0801AED4(void);
void sub_0801C0A0(u32 bank);
void sub_080309C8(void);
void sub_08035410(u32 arg0, u8 *arg1, u8 *arg2);
void sub_0805BDB8(void);
void sub_08066C8C(u16 angle);
void sub_08066D0C(u16 angle);

u32 sub_08018FB8(u32 bank,u32 slot,u32 amount) {

 u32 savedAmount=amount;
 u8 *root=gSetupBuffer_03000590;
 u8 *setup=(u8 *)((slot*0x18)+(bank<<8)+(u32)root);
 u8 *field=setup+0x59;
 u32 current=*field;
 u32 remaining=current-savedAmount;
 u32 result;
 if((s32)remaining>=0){
  *field=remaining;
  result=savedAmount;
 }else{
  *field=0;
  result=((savedAmount-current)<<8)+current;
 }
 return result;
}

void sub_0801AED4(void) {

 u32 zero;
 u8 *root=(u8 *)&gGraphicsTransferCounter;
 u8 *cursor=root+0xA1;
 zero=0;
 *cursor++=zero;
 *cursor++=zero;
 *cursor++=zero;
 *cursor++=zero;
 *cursor=zero;
}

void sub_0801C0A0(u32 bank) {

 u8 *root=gSetupBuffer_03000590;
 u8 *setup=(u8 *)((bank<<8)+(u32)root);
 const u8 *table=gUnknown_083AD579;
 u8 *field=setup+0xE0;
 *field=table[*field];
}

void sub_080309C8(void) {

 u32 setupRoot=(u32)gSetupBuffer_03000590;
 struct Work309C8 *work=&gCounter6ED08_03001800;
 u8 *record=(u8 *)(setupRoot+((u32)work->bank<<8));
 if(record[0xBD]&1) {work->mode=4;gUnknown_0300137C=0x20;}
 else if(record[0xDD]==0) gUnknown_0300137C=0x10;
 else gUnknown_0300137C++;
}

void sub_08035410(u32 arg0, u8 *arg1, u8 *arg2) {

    struct FrameObject *temp_r2;
    u32 temp_r0;
    u8 temp_r0_2;
    u8 temp_r1;

    { u32 root = (u32)gFrameObjects; temp_r2 = (struct FrameObject *)(root + (arg0 << 6)); }
    temp_r2->flags |= 0x8000;
    temp_r1 = *arg2;
    if (temp_r1 == 0) {
        temp_r0 = *arg1 + 1;
        *arg1 = temp_r0;
        if (temp_r0 & 1) {
            temp_r2->flags &= 0x7FFF;
        }
    } else {
        temp_r0_2 = *arg1;
        if (temp_r0_2 == temp_r1) {
            *arg1 = 0;
            temp_r2->flags &= 0x7FFF;
            *arg2 -= 1;
            return;
        }
        *arg1 = temp_r0_2 + 1;
    }
}

void sub_0805BDB8(void) {

 s32 count=0;
 do{
  u32 screen=((u32)(*(volatile u16*)0x04000008>>8)&31)<<11;
  u32 rowRoot=(u32)(volatile u16*)(count*0xC0+0x060002CE);
  volatile u16 *tiles=(void*)(screen+rowRoot);
  s32 next=count+1;
  count=15;
  do{*tiles=(*tiles&0xFFF)|0x8000;tiles++;count--;}while(count>=0);
  count=next;
 }while(count<=2);
}

void sub_08066C8C(u16 angle) {

 s32 index=0;
 u32 contextSlot=(u32)&gMainContextPointer_03006F74;
 u32 tableRoot=(u32)gAffineSineTable_080AE8F4;
 do{
  u32 workRoot=(u32)*(void**)contextSlot;
  u8 *record=(void*)(workRoot+(index<<4));
  s16 *scale=(s16*)(record+0xD0);
  s32 first=*scale;
  u32 phase=(sub_0807CD2C(index<<8,18)+angle)&255;
  s32 x=(first**(s16*)((phase<<1)+tableRoot))>>8;
  s32 y;
  *(s16*)(record+0xD8)=x;
  y=((s32)*scale**(s16*)(((phase+64)<<1)+tableRoot))>>8;
  *(s16*)(record+0xDA)=y;
  index++;
 }while(index<=17);
}

void sub_08066D0C(u16 angle) {

 s32 index=0;
 u32 contextSlot=(u32)&gMainContextPointer_03006F74;
 u32 tableRoot=(u32)gAffineSineTable_080AE8F4;
 do{
  u32 workRoot=(u32)*(void**)contextSlot;
  u8 *record=(void*)(workRoot+(index<<4));
  s16 *scale=(s16*)(record+0xD0);
  s32 first=*scale;
  u32 phase=(sub_0807CD2C(index<<8,18)+angle)&255;
  s32 x=(first**(s16*)((phase<<1)+tableRoot))>>8;
  s32 y;
  *(s16*)(record+0xD8)=x;
  y=((s32)*scale**(s16*)(((phase+64)<<1)+tableRoot))>>8;
  *(s16*)(record+0xDA)=y;
  index++;
 }while(index<=17);
}
