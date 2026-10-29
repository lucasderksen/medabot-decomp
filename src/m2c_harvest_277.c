/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "graphics.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"

struct WordRead33 {u8 before14[0x14];const u8 *cursor;};

extern const MainCallback gUnknown_084859D8[];
extern const u8 gUnknown_083AF4B0[];
extern s32 sub_080724B0(void *);
extern u32 sub_08035590(u32);
extern void sub_0806E404(void);

u32 sub_0801BF64(u16 *timer,u32 limit);
u32 sub_0803556C(u32 bank);
void sub_0806E460(void);
void sub_0807258C(void *record);
u32 sub_08072880(void *record);

u32 sub_0801BF64(u16 *timer,u32 limit) {

 u16 shortLimit=(u16)limit;
 u32 value=*timer;
 if(value!=shortLimit){value++;*timer=value;}
 return value;
}

u32 sub_0803556C(u32 bank) {

 const u8 *table=gUnknown_083AF4B0;
 u32 row=sub_08035590(bank);
 u32 random=sub_080424B8();
 return *(const u8 *)((row<<3)+(random&7)+(u32)table);
}

void sub_0806E460(void) {

 gUnknown_084859D8[gUnknown_0300137C]();
 sub_0806E404();
}

void sub_0807258C(void *record) {

 s32 result=sub_080724B0(record);
 u8 *cursor;
 if(result==0){
  cursor=(u8 *)record+0x5F;
  *cursor++=1;
  *cursor++=result;
  *cursor=1;
 }
}

u32 sub_08072880(void *record) {

 struct WordRead33 *work=record;
 const u8 *p=work->cursor;
 u32 result=(u32)p[0]+((u32)p[1]<<8)+((u32)p[2]<<16)+((u32)p[3]<<24);
 work->cursor=p+4;
 return result;
}
