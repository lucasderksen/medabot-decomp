/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct FamilyBank87 {u8 pad[0x87];u8 bank;};
struct Work6E90C{u16 main,sub,previous,pad6;s32 counter;};
struct Work6F8D8{u16 main,sub,previous,pad6;s32 counter;u16 limit;u8 padE[0xE6];u16 left,right;};

extern const s8 gUnknown_08485924[64];
extern s32 sub_08036BB8(u8*,s32,s32);
extern struct FamilyBank87 gFamilyWork3D2A8;
extern struct Work6E90C gWaitWork6E90C;
extern struct Work6F8D8 gWaitWork6F8D8;
extern void sub_080362C4(s32);
extern void sub_08036340(s32);
extern void sub_08036370(s32,s32);
extern void sub_080364A8(s32,u32);

void sub_0803D2A8(void);
void sub_0806CF7C(void);
void sub_0806E90C(void);
void sub_0806F8D8(void);

void sub_0803D2A8(void) {

    s32 total=0;
    struct FrameObject *frames=gFrameObjects;
    struct FrameObject *temp_r0_2;
    struct FrameObject *temp_r1;
    u8 *temp_r5;
    u8 *base;
    u8 temp_r0;
    u8 temp_r0_3;

    temp_r1 = &frames[gState0TypedWork.bytes[0x12F]];
    temp_r0 = temp_r1->byte2B;
    if (temp_r0 != 0) {
        temp_r1->byte2B = temp_r0 - 1;
        return;
    }
    if (temp_r1->unknown2C[2] != 0) {
        struct FamilyBank87 *work;
        sub_080362C4(temp_r1->unknown2C[1]);
        sub_08036340(frames[gState0TypedWork.bytes[0x12F]].unknown2C[1]);
        sub_08036370(frames[gState0TypedWork.bytes[0x12F]].unknown2C[1], (work=&gFamilyWork3D2A8)->bank);
        sub_080364A8(frames[gState0TypedWork.bytes[0x12F]].unknown2C[1], work->bank);
        frames[gState0TypedWork.bytes[0x12F]].unknown2C[2] = total;
    }
    temp_r0_2 = &frames[gState0TypedWork.bytes[0x12F]];
    temp_r0_3 = temp_r0_2->unknown2C[0];
    if (temp_r0_3 != 0) {
        temp_r0_2->unknown2C[0] = temp_r0_3 - 1;
        return;
    }
    temp_r5 = (base=gState0TransferWork.bytes+0xD6) - 0x4F;
    total = sub_08036BB8(base, *temp_r5, 0);
    total += sub_08036BB8(base + 2, *temp_r5, 1);
    total += sub_08036BB8(base + 4, *temp_r5, 2);
    total += sub_08036BB8(base + 6, *temp_r5, 3);
    sub_08036370(frames[gState0TypedWork.bytes[0x12F]].unknown2C[1], *temp_r5);
    sub_080364A8(frames[gState0TypedWork.bytes[0x12F]].unknown2C[1], *temp_r5);
    if (total == 4) {
        sub_08040CD0(gState0TypedWork.bytes[0x12F], 1U);
    }
}

void sub_0806CF7C(void) {

 struct FrameObject *root=gFrameObjects;
 const s8 *table=gUnknown_08485924;
 struct FrameObject *frame=&root[40];
 u8 *command=&root[40].commandDelay;
 s32 count=7;
 do{
  switch(*command){
   case 1:case 2:{
    u16 phase=frame->unknown1A;u32 masked=phase&8;u32 tile,tableIndex;
    tile=17;if(masked)tile=16;
    frame->frameAndGroup=tile;
    tableIndex=63;tableIndex&=phase;
    frame->screenY=(u16)frame->screenY-*(const s8 *)(tableIndex+(u32)table);
    break;
   }
   case 3:{
    u16 phase=frame->unknown1A;s32 value=phase-1;
    if(value<0)value=phase+2;
    frame->frameAndGroup=(value>>2)+19;
    break;
   }
  }
  frame++;command=(u8 *)((u32)command+64U);count--;
 }while(count>=0);
}

void sub_0806E90C(void) {

 u32 value=(u32)gWaitWork6E90C.counter;
 struct Work6E90C *work=&gWaitWork6E90C;
 if(value!=0 && work->counter>60){work->counter=0;work->previous=6;gUnknown_0300137C=2;return;}
 work->counter=(s32)((u32)work->counter+1U);
}

void sub_0806F8D8(void) {

 struct Work6F8D8 *work=&gWaitWork6F8D8;s32 before,value;
 work->left+=16;work->right-=16;
 value=work->counter;before=value;value=(s32)((u32)value+1U);work->counter=value;
 if(before>58){work->counter=0;work->previous=6;work->limit=16;gUnknown_0300137C=2;}
}
