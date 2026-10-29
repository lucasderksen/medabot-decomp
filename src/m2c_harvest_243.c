/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
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

struct ContinuedSetup32 {u8 before[0xA2];u8 kind;u8 gap[0x1A];u8 flags;};
struct ContinuedPending32 {u8 before[0x51];u8 mode;u8 gap[0x58];u8 phase;u8 gap2[0x35];u8 pending[3];};
struct ContinuedPhase32 {u8 before[0xAA];u8 phase;};
struct ContinuedRecord32 {u8 before[0x2A];u8 active,kind;};
struct ContinuedLookup32 {u8 before[0x51];u8 mode,kind;u8 middle[0x37];u8 index;};
struct ContinuedCommands32 {u8 before[0xF8];const u8 *commands;};
struct ContinuedKind32 {u8 before[0xA6];u8 kind;};
struct ContinueFlagWork {u8 pad[0x88];u8 bank;u8 gap[0x65];s16 value;};
struct TimerWork6445C { u8 pad[0x3A]; u16 delay; s16 timer; };
struct FadeWork7244C { u8 pad[0x50]; u8 flags,pad51[13],setting,delay; s8 repeat; u8 pad61[5],volume; };
struct PitchWork726D4 { u8 pad0[0x34]; u32 step,offset; u8 pad3C[12]; u16 note; u8 pad4A[12]; u8 length,range,scale,delay,duration; };

extern const struct ContinuedCommands32 gState0NextCommands_083B6100;
extern struct ContinueFlagWork gUnknown_03001800;
extern struct TimerWork6445C *gTimerRoot6445C;
extern u32 sub_08033184(u32);
extern u32 sub_08038E9C(void);extern s32 sub_08038F84(void);extern void sub_08039068(void);
extern u32 sub_080732B8(u32);
extern u32 sub_0807CEC8(u32,u32);
extern void sub_0801A0A4(u32,u32);
extern void sub_08036CCC(u32,u32,s32);
extern void sub_08036FA0(u32);
extern void sub_08062D60(void);
extern void sub_080723F8(void *);

u32 sub_08019FBC(u32 selected,u32 mode);
u32 sub_0801A030(u32 selected,u32 mode);
void sub_0801FE14(void);
void sub_08021300(void);
void sub_08021DAC(void);
void sub_080229C0(void);
void sub_08025AAC(void);
void sub_08026F6C(void);
void sub_0802E140(void);
void sub_0802E5D4(void);
void sub_0802F89C(void);
void sub_08038E54(void);
void sub_0806445C(void);
void sub_0807244C(struct FadeWork7244C *work);
void sub_080726D4(struct PitchWork726D4 *work);

u32 sub_08019FBC(u32 selected,u32 mode) {

    u32 result=0;
    u8 *initialSetup=gSetupBuffer_03000590;
    struct ContinuedSetup32 *record=(struct ContinuedSetup32 *)((selected<<8)+(u32)initialSetup);
    if(!(record->flags&4)){
        if(selected<=2){
            if(gFrameObjects[selected*4+0x5D].screenX==0x68)result=1;
        }else{
            if(gFrameObjects[selected*4+0x5D].screenX==0x88)result=1;
        }
        if(mode==0 && result){sub_0801A0A4(selected,((struct ContinuedSetup32 *)((selected<<8)+(u32)gSetupBuffer_03000590))->kind);}
    }
    return result;
}

u32 sub_0801A030(u32 selected,u32 mode) {

    u32 result=0;
    u8 *initialSetup=gSetupBuffer_03000590;
    struct ContinuedSetup32 *record=(struct ContinuedSetup32 *)((selected<<8)+(u32)initialSetup);
    if(record->flags&4){
        if(selected<=2){
            if(gFrameObjects[selected*4+0x5D].screenX==0x28)result=1;
        }else{
            if(gFrameObjects[selected*4+0x5D].screenX==0xC8)result=1;
        }
        if(mode==0 && result){sub_0801A0A4(selected,((struct ContinuedSetup32 *)((selected<<8)+(u32)gSetupBuffer_03000590))->kind);}
    }
    return result;
}

void sub_0801FE14(void) {

    u32 i=0;
    struct ContinuedPending32 *work=(struct ContinuedPending32 *)&gState0TransferWork;
    u8 *mode=&work->mode;
    u32 zero=0,next;
    u8 *phase;
    for(;i<=2;i++){
        u8 *base=work->pending;
        u8 *pending=(u8 *)(i+(u32)base);
        u8 value=*pending;
        if(value){
            *mode=value-1;*pending=zero;
            sub_080158F8();sub_0801A0D0();sub_08036FA0(*mode);
            phase=&work->phase;next=2;goto store;
        }
    }
    phase=&work->phase;next=*phase+1;
store:
    *phase=next;
}

void sub_08021300(void) {

    struct ContinuedLookup32 *initial=(struct ContinuedLookup32 *)&gState0TransferWork;
    struct ContinuedRecord32 *record=(struct ContinuedRecord32 *)(initial->index*8+(u32)initial);
    u8 active=record->active;
    struct ContinuedLookup32 *work=initial;
    if(active && record->kind==work->kind){
        gFrameObjects[0x21].unknown23[4]=0;
        ((struct ContinuedPhase32 *)work)->phase++;
    }else if(work->mode==2){
        ((struct ContinuedPhase32 *)work)->phase=0x14;
    }else{
        sub_08074DE0(0x3E);
        ((struct ContinuedPhase32 *)work)->phase=0xE;
    }
}

void sub_08021DAC(void) {

    u8 *work=gState0TransferWork.bytes;
    work[work[0x89]*8+0x2A]=0;
    work[work[0x89]*8+0x2B]=0;
    work[work[0x89]*8+0x2C]=0;
    work[work[0x89]*8+0x2D]=0;
    ((struct ContinuedPhase32 *)work)->phase++;
}

void sub_080229C0(void) {

    sub_08040BD8(gState0NextCommands_083B6100.commands,0x21);
    if(gFrameObjects[0x21].scaleX==8){
        sub_08040CD0(0x21,1);
        ((struct ContinuedPhase32 *)&gState0TransferWork)->phase++;
    }else gFrameObjects[0x21].scaleX-=8;
}

void sub_08025AAC(void) {

    u8 *setup=gSetupBuffer_03000590;
    u8 *work=gState0TransferWork.bytes;
    u8 *record=(u8 *)(work[0xA7]*24+(work[0x87]<<8)+(u32)setup);
    u8 kind=record[0x49];
    u8 *retained=work;
    if(kind==0x2E)((struct ContinuedKind32 *)retained)->kind=0x31;
    else ((struct ContinuedKind32 *)retained)->kind=0x32;
    ((struct ContinuedPhase32 *)retained)->phase++;
}

void sub_08026F6C(void) {

    u8 *work=gState0TransferWork.bytes;
    u16 *amount=(u16 *)(work+0xCA);
    u32 chosen;
    if(*amount && (chosen=sub_08033184(work[0x88]))!=0){
        chosen-=1;
        work[0xD0]=chosen;work[0x8B]=chosen;
        sub_08036CCC(work[0x87],work[0xD0],*amount);
        ((struct ContinuedPhase32 *)work)->phase=0x10;
    }else ((struct ContinuedPhase32 *)work)->phase++;
}

void sub_0802E140(void) {

    u32 reached=0,i=0;
    u8 *work=gState0TransferWork.bytes;
    u8 *selected=work+0xD2;
    struct FrameObject *frames=gFrameObjects;
    struct FrameObject *frame=(struct FrameObject *)(0x840+(u32)frames);
    do{
        if(*(u8 *)(i+(u32)selected)){
            if(frame->scaleX==0x40)reached=1;
            else{frame->scaleX-=8;frame->scaleY-=8;}
        }
        frame++;i++;
    }while(i<=2);
    if(reached){gState0TypedWork.widths.word86=0x3C;((struct ContinuedPhase32 *)work)->phase++;}
}

void sub_0802E5D4(void) {

    u32 reached=0,i=0;
    u8 *work=gState0TransferWork.bytes;
    u8 *selected=work+0xD2;
    struct FrameObject *frames=gFrameObjects;
    struct FrameObject *frame=(struct FrameObject *)(0x280+(u32)frames);
    do{
        if(*(u8 *)(i+(u32)selected)){
            if(frame->scaleX==0x40)reached=1;
            else{frame->scaleX+=4;frame->scaleY+=4;}
        }
        frame++;i++;
    }while(i<=2);
    if(reached){gState0TypedWork.widths.word86=0x3C;((struct ContinuedPhase32 *)work)->phase++;}
}

void sub_0802F89C(void) {

    u32 found=0,i=0;
    u8 *work=gState0TransferWork.bytes;
    u8 *selected=work+0xD2;
    u16 *amount=(u16 *)(work+0xD6);
    do{if(*(u8 *)(i+(u32)selected) && *amount)found=1;amount++;i++;}while(i<=2);
    if(!found)((struct ContinuedPhase32 *)work)->phase++;
    else ((struct ContinuedPhase32 *)work)->phase+=2;
}

void sub_08038E54(void) {
struct ContinueFlagWork *root=&gUnknown_03001800;u8 *setup;u8 *record;u32 flags;root->value=0;setup=gSetupBuffer_03000590;record=(u8 *)(((u32)root->bank<<8)+(u32)setup);flags=record[0xBC];{u32 first=4u;first&=flags;if(first){u32 second=8u;second&=flags;if(second){sub_08038E9C();return;}}}if(sub_08038F84()==0)sub_08039068();}

void sub_0806445C(void) {

 struct FrameObject *frame;
 struct TimerWork6445C *work;
 sub_08062D60();
 work = gTimerRoot6445C;
 if (--work->timer < 0) {
  work->delay = 0x280;
  gUnknown_0300137C += 1;
  return;
 }
 if (work->timer <= 7) {
  frame=gFrameObjects;
  frame->scaleX = 0x40 - work->timer * 8;
 } else {
  gFrameObjects->scaleX = 1;
  frame=gFrameObjects;
 }
 work = gTimerRoot6445C;
 if (work->timer > 1) {
  frame->scaleY = work->timer * 4 + 0x38;
  frame->screenY = 0x38 - (work->timer - 2) * 8;
 }
}

void sub_0807244C(struct FadeWork7244C *work) {

 s32 next;
 s32 before;
 u8 repeat;
 if (--work->delay==0) {
  repeat=(u8)work->repeat;
  if (work->repeat==0) {sub_080723F8(work);return;}
  work->repeat=repeat-1;
  next=work->volume;
  before=next;
  next--;
  if(next<0)next=0;
  if(before!=next) {work->volume=next;work->flags|=2;}
  work->delay=work->setting>>4;
 }
}

void sub_080726D4(struct PitchWork726D4 *work) {

 u32 upper,lower;
 u32 zero;
 work->delay = work->length;
 zero = 0;
 work->duration = work->range >> 1;
 upper = sub_080732B8((u32)work->note + 2);
 lower = sub_080732B8(work->note);
 work->step = sub_0807CEC8(((s32)(u16)upper-(s32)(u16)lower)*work->scale,work->duration);
 work->offset = zero;
}
