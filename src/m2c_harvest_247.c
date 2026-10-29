/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_commands.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "record_helpers.h"

struct FamilyRecord351E8 {u8 pad[0x95];u8 a,b,c,d,e;u8 pad9A[7];u8 active;u8 outA,outB,outC,outD,outE;u8 remaining[0x59];};
struct FamilyWork4C588 {u8 pad[0xC94];u8 mode,amount,step;};

extern s32 sub_0803D424(void);
extern struct FamilyRecord351E8 gUnknown_03000590[];
extern struct FamilyWork4C588 gFamilyWork4C588;
extern void (*const gUnknown_083AF8C0[])(void);
extern void *sub_0804D938(u32 identifier);
extern void sub_0803D4AC(void);
extern void sub_0804D8CC(u32 mode);
extern void sub_0805218C(u32 index,u32 value,void *record);
extern volatile u16 *const gUnknown_08486E64[];

void sub_080351E8(u32 bank);
void sub_080393EC(void);
void sub_0804C588(void);
void sub_08073B2C(s32 arg0);

void sub_080351E8(u32 bank) {

 struct FamilyRecord351E8 *setup=gUnknown_03000590;
 struct FamilyRecord351E8 *record=&setup[bank];
 if(record->active!=0) {
 record->outA=record->a;record->outB=record->b;record->outC=record->c;record->outD=record->d;record->outE=record->e;
 }
}

void sub_080393EC(void) {

 s32 initial=sub_0803D424();
 gFrameObjects[0].unknown23[6]=initial;
 if((s32)((u32)initial<<24)<0) {
  s32 value;
  do {sub_0803D4AC();value=sub_0803D424();gFrameObjects[0].unknown23[6]=value;}while((s32)((u32)value<<24)<0);
 }
 gUnknown_083AF8C0[gFrameObjects[0].unknown23[6]]();
}

void sub_0804C588(void) {

 struct FamilyWork4C588 *work;
 u8 *record;
 sub_0804D8CC(3);work=&gFamilyWork4C588;
 {u32 mode=(u32)work->mode<<8;record=sub_0804D938(work->amount|mode);}
 if(record!=0) {
  u32 flags=record[4];
  if(flags&0x40u) {
   u32 index=((((u32)flags<<27)>>3)+0x31000000u)>>24;
   sub_0805218C(index,work->step,record);
  }
 }
}

void sub_08073B2C(s32 arg0) {

    volatile u16 *temp_r3;

    temp_r3 = gUnknown_08486E64[(u32)arg0-1U];
    *temp_r3 = (0x499F & *temp_r3) | 0x8440;
    *temp_r3 = (0x499F & *temp_r3) | 0x440;
}
