/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_display.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"
#include "tile_text.h"

extern s32 gUnknown_03000000; extern u8 gUnknown_03000005;
extern s32 sub_0807CD2C(s32,s32); s32 sub_0807CDF8(s32,s32);

void sub_08062BEC(u16 index,u8 row);
void sub_080669EC(s32 *destination,const s32 *source);
s32 sub_08068924(void);
s32 sub_08068B74(void);
void sub_0806D3EC(void);

void sub_08062BEC(u16 index,u8 row) {

 const u8 *source=gPartTextPointers_083BBB4C[index];
 u8 *destination=gDebugMenuTextBuffer;
 u32 count;
 if(row)destination+=20;
 for(count=0;count<=19;count++){
  *destination++=*source++;
  if(*source==0xFE)break;
 }
 *destination=0xFE;
}

void sub_080669EC(s32 *destination,const s32 *source) {

 s32 count=0;
 do{
  u32 offset=(u32)count<<4;
  s32 next=count+1;
  const s32 *src=(const s32 *)(offset+(u32)source);
  s32 *dst=(s32 *)(offset+(u32)destination);
  count=3;
  do{*dst++=*src++;count--;}while(count>=0);
  count=next;
 }while(count<=3);
}

s32 sub_08068924(void) {

 s32 *counter=&gUnknown_03000000; u8 *duration=&gUnknown_03000005;
 s32 period=*duration,value=*counter;
 if(sub_0807CDF8(value,period)==0){
  volatile u16 *brightness=(volatile u16 *)0x04000054;
  *brightness=16U-(u32)sub_0807CD2C(value,period);
 }
 if(*counter==*duration*16)return 1;
 return 0;
}

s32 sub_08068B74(void) {

 s32 *counter=&gUnknown_03000000; u8 *duration=&gUnknown_03000005;
 s32 period=*duration,value=*counter;
 if(sub_0807CDF8(value,period)==0){
  volatile u16 *brightness=(volatile u16 *)0x04000054;
  *brightness=sub_0807CD2C(value,period);
 }
 if(*counter==*duration*16)return 1;
 return 0;
}

void sub_0806D3EC(void) {

 s32 count=0;
 struct FrameObject *root=gFrameObjects;
 u8 *delay=&root[30].commandDelay;
 struct FrameObject *frame=&root[13];
 do{
  s32 y=200;
  if(count<(s32)*delay)y=120;
  frame->screenY=y;frame++;count++;
 }while(count<=2);
}
