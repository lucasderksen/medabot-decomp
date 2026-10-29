/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "state0_work.h"

struct FamilySoundRecord {u8 *bytes;u8 pad4[12];u32 control;u8 pad14[0x26];u8 channel;u8 pad3B;u8 active;};

extern const u8 gUnknown_080AFB88[];
extern u8 gUnknown_03002420;
extern void sub_08073AE4(u32, u32 *);
extern void sub_08073C84(void *);
extern void sub_08073CDC(void *);
extern volatile u32 *const gUnknown_08486E5C[];

void sub_08060D28(u8 *arg0,const u8 *arg1,u32 unused2,u32 arg3);
void sub_08073D70(struct FamilySoundRecord *arg0,u32 arg1);

void sub_08060D28(u8 *arg0,const u8 *arg1,u32 unused2,u32 arg3) {

 const u8 *table=gUnknown_080AFB88;
 const u8 *selector=&gUnknown_03002420;
 u32 var_r3=arg3;
 const u8 *var_r2=(const u8 *)(var_r3+(u32)arg1);
 do { arg0[var_r3]=*var_r2;var_r2++;var_r3++; } while(*var_r2!=0xFF);
 arg0[var_r3]=arg1[var_r3];
 var_r3++;
 arg0[var_r3]=arg1[var_r3];
 arg0[2]=*(const u8 *)((u32)*selector+(u32)table);
}

void sub_08073D70(struct FamilySoundRecord *arg0,u32 arg1) {

 sub_08073C84(arg0);
 if(arg0->active) {
  sub_08073CDC(arg0);
  sub_08073AE4(arg0->channel,(u32 *)(arg0->bytes + (arg1+0x10)));
  *gUnknown_08486E5C[arg0->channel-1]=arg0->control;
 }
}
