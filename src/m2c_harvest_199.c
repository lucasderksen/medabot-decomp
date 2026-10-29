/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "display_effects.h"
#include "display_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "later_graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinuedContext185A8 {u8 prefix[0x3C];u8 mode,choice;};
struct ContinuedPartnerFrame25378 {u16 flags;s16 x,y;u16 group;u8 scaleX,scaleY,palette,priority;u8 gapC[0xC];u16 angle,unknown1A;u8 selector;u8 gap1D[6];u8 byte23,kind;u8 gap25[0xB];u16 savedX;s16 savedY;u8 gap34[0xC];};
struct ContinuedPartnerFrames25378 {u8 prefix[0x840];struct ContinuedPartnerFrame25378 first,second;};
struct ContinuedSetup25A18 {u8 prefix[0xC9];u8 mode,zero,first,second;u8 tail[0x33];};
struct ContinuedSelections2C440 {u8 prefix[0xD2];u8 selected[3];u8 gapD5;u16 second[3];};
struct ContinuedFrame37ScriptInit {u8 prefix[0x940];struct FrameObject frame;};
struct Continued31AFCWork {u8 prefix[0x5C];u8 owner,other,selected,found,cursor,slots[3];};
struct ChoiceWork644D8 {u8 pad0[0x3A];s16 timer;u8 pad3C[0x3E];s8 mode;};
struct EnvelopeWorkInitQ14 {u8 pad0[0x5B];u8 attack;u8 decay;u8 pad5D[2];u8 countdown;s8 step;u8 state;};

extern const u16 gPitchScale083ABC46[12];
extern const u8 *const gState0NextCommands_083B6100[];
extern const u8 *gUnknown_083B6200;
extern const u8 *gUnknown_083B6204;
extern const u8 gUnknown_083AD524[];
extern const u8 gUnknown_084D7638[];
extern const u8 gUnknown_0850FD78[32];
extern const void *gState0NextText_083B4C60[];
extern s32 sub_08032FD0(u32,u32);
extern s32 sub_08032FFC(void);
extern s32 sub_080330E8(s32);
extern s32 sub_08033154(u32,u32);
extern s32 sub_080724B0(void *);
extern s32 sub_0807CD2C(s32, s32);
extern s32 sub_0807CDF8(s32, s32);
extern u32 sub_0803301C(void);
extern u32 sub_08033184(u32);
extern u32 sub_08036E54(u32);
extern void sub_08017A7C(u32,u32,u32);
extern void sub_08017C50(u32);
extern void sub_080356B4(u32);
extern void sub_08062ED8(void);
extern void sub_080724D8(void *);
extern void sub_08074DE0(u32);

void sub_080185A8(void);
void sub_0801DF60(void);
void sub_08023E94(void);
void sub_080242F8(void);
void sub_08025A18(void);
void sub_08026EF8(void);
void sub_0802C440(void);
void sub_0803029C(void);
void sub_08031AFC(void);
void sub_080644D8(void);
void sub_0807250C(struct EnvelopeWorkInitQ14 *work);
u32 sub_08073B68(s32 arg0);

void sub_080185A8(void) {
 const u8 *table=gUnknown_083AD524;
 struct ContinuedContext185A8 *context=(struct ContinuedContext185A8 *)&gState0TypedWork;
 u8 *choice=&context->choice;
 u32 selection=context->mode*3+*choice;
 u32 offset=selection*2;
 u32 first=*(const u8 *)(offset+(u32)table);
 offset++;
 sub_08017A7C(selection,first,*(const u8 *)(offset+(u32)table));
 sub_08040CD0(8,1);
 sub_08017C50(1);
}

void sub_0801DF60(void) {
    sub_0803F15C(0x1EU, 1U, 0U, (u32) gState0TypedWork.bytes[0x84], gState0NextText_083B4C60[0x69], (u32) *(volatile u16 *)0x04000008, 0U);
    sub_0803F15C(0x1EU, 1U, 0U, 0x13 - gState0TypedWork.bytes[0x84], gState0NextText_083B4C60[0x69], (u32) *(volatile u16 *)0x04000008, 0U);
    if (gState0TypedWork.bytes[0x84] == 9) {
        gState0TransferWork.bytes[0x1AE] = 1;
        gState0TransferWork.bytes[0xAA] = (u8) (gState0TransferWork.bytes[0xAA] + 1);
        return;
    }
    gState0TypedWork.bytes[0x84] += 1;
}

void sub_08023E94(void) {
 struct ContinuedPartnerFrames25378 *frames;
 u8 *work;
 u32 slot;
 LeDecompress(gUnknown_084D7638,(void *)0x06014800);
 CpuFastSet(gUnknown_0850FD78,(void *)0x050002E0,8);
 frames=(struct ContinuedPartnerFrames25378 *)gFrameObjects;
 frames->first.flags|=0x8000;
 work=gState0TransferWork.bytes;
 frames->first.savedX=(u16)gFrameObjects[work[0x87]*4+0x5D].screenX;
 frames->first.savedY=(u16)gFrameObjects[work[0x87]*4+0x5D].screenY-4;
 frames->first.kind=6;
 gState0TypedWork.bytes[0x84]=0x42;
 slot=gState0TypedWork.bytes[0x84];
 sub_08040B90(gState0NextCommands_083B6100[slot],0x21);
 gState0TypedWork.widths.word86=0x3C;
 work[0xAA]++;
}

void sub_080242F8(void) {
 struct ContinuedPartnerFrames25378 *frames=(struct ContinuedPartnerFrames25378 *)gFrameObjects;
 u32 finished;
 if(frames->first.flags&0x8000) {
  if(sub_08036AC4(0x21,0)) sub_08040CD0(0x21,1);
  else if(!(gState0TransferWork.bytes[0xF8]&1)) {
   frames->first.x=(u16)frames->first.x-1;
   frames->first.angle=(frames->first.angle-0x10)&0x3FF;
  } else {
   frames->first.x=(u16)frames->first.x+1;
   frames->first.angle=(frames->first.angle+0x10)&0x3FF;
  }
 }
 sub_080353CC(gState0TransferWork.bytes[0x88]*4+0x5A);
 sub_080353CC(gState0TransferWork.bytes[0x88]*4+0x5B);
 sub_080353CC(gState0TransferWork.bytes[0x88]*4+0x5C);
 finished=sub_080353CC(gState0TransferWork.bytes[0x88]*4+0x5D);
 if(gFrameObjects[gState0TransferWork.bytes[0x88]*4+0x5D].unknown23[0]==0x10) {
  gFrameObjects[gState0TransferWork.bytes[0x88]*4+0x5A].screenY=(u16)gFrameObjects[gState0TransferWork.bytes[0x88]*4+0x5A].screenY+8;
  gFrameObjects[gState0TransferWork.bytes[0x88]*4+0x5B].screenY=(u16)gFrameObjects[gState0TransferWork.bytes[0x88]*4+0x5B].screenY-8;
  gFrameObjects[gState0TransferWork.bytes[0x88]*4+0x5C].screenY=(u16)gFrameObjects[gState0TransferWork.bytes[0x88]*4+0x5C].screenY-8;
  gFrameObjects[gState0TransferWork.bytes[0x88]*4+0x5D].screenY=(u16)gFrameObjects[gState0TransferWork.bytes[0x88]*4+0x5D].screenY-8;
  gFrameObjects[gState0TransferWork.bytes[0x88]*4+0x5A].flags|=0x2000;
  gFrameObjects[gState0TransferWork.bytes[0x88]*4+0x5B].flags|=0x2000;
  gFrameObjects[gState0TransferWork.bytes[0x88]*4+0x5C].flags|=0x2000;
  gFrameObjects[gState0TransferWork.bytes[0x88]*4+0x5D].flags|=0x2000;
 }
 sub_080356CC(gState0TransferWork.bytes[0x88]*4+0x5D,gState0TransferWork.bytes[0x88]+0x72);
 if(finished) {
  sub_080356B4(gState0TransferWork.bytes[0x88]+0x72);
  sub_08074DE0(0x41);
  gState0TransferWork.bytes[0xAA]++;
 }
}

void sub_08025A18(void) {
 struct ContinuedSetup25A18 *setup=(struct ContinuedSetup25A18 *)gSetupBuffer_03000590;
 u8 *work=gState0TransferWork.bytes;
 u8 *bank=work+0x88;
 u32 kind,partOffset;
 setup[*bank].zero=0;
 setup[*bank].first=sub_08036E54(*(s16 *)(work+0xE8));
 setup[*bank].second=sub_08036E54(*(s16 *)(work+0xEC));
 partOffset=work[0xA7]*24;
 kind=*(u8 *)(partOffset+(work[0x87]<<8)+(u32)setup+0x49);
 if(kind==0x2E) setup[*bank].mode=kind;
 else setup[*bank].mode=0x2F;
 gState0TransferWork.bytes[0xAA]++;
}

void sub_08026EF8(void) {
 u8 *work=gState0TransferWork.bytes;
 u32 selected=sub_08033184(work[0x87]);
 if (selected) {
  u32 index=selected-1;
  work[0xD0]=index;
  work[0x8B]=index;
  work[0xAA]=2;
 } else work[0xAA]++;
}

void sub_0802C440(void) {
 u32 firstIndex,firstStart,secondStart;
 const u8 **firstCommands,**secondCommands;
 u8 *selected;
 u16 *second;
 gState0TransferWork.bytes[0x60]=sub_08032FC4(gState0TransferWork.bytes[0x87]);
 firstIndex=0;
 selected=((struct ContinuedSelections2C440 *)&gState0TransferWork)->selected;
 firstCommands=&gUnknown_083B6200;
 firstStart=0x21000000;
 do {
  if(*(u8 *)(firstIndex+(u32)selected)) sub_08040BD8(*firstCommands,firstStart>>24);
  firstStart+=0x1000000;firstIndex++;
 } while(firstIndex<=2);
 gState0TransferWork.bytes[0x60]=sub_08032FB8(gState0TransferWork.bytes[0x87]);
 firstIndex=0;
 secondCommands=&gUnknown_083B6204;
 secondStart=0x24000000;
 second=((struct ContinuedSelections2C440 *)&gState0TransferWork)->second;
 do {
  if(*second) sub_08040BD8(*secondCommands,secondStart>>24);
  secondStart+=0x1000000;second++;firstIndex++;
 } while(firstIndex<=2);
 if(gFrameObjects[0x21].commandStopped==0xFF) {
  sub_08040CD0(0x21,6);
  gState0TypedWork.bytes[0x84]=0;
  gState0TransferWork.bytes[0xAA]++;
 }
}

void sub_0803029C(void){
 struct ContinuedFrame37ScriptInit *frames=(void *)gFrameObjects;
 u8 *work;
 frames->frame.flags=0xC404;frames->frame.tableSelector=0;
 work=gState0TransferWork.bytes;
 frames->frame.screenX=(u16)gFrameObjects[work[0x87]*4+0x5D].screenX;
 frames->frame.screenY=(u16)gFrameObjects[work[0x87]*4+0x5D].screenY-4;
 frames->frame.palette=7;frames->frame.priority=0xF2;
 sub_08040B90(gState0NextCommands_083B6100[0x6F],0x25);
 if(work[0xF8]&1)frames->frame.flags|=0x1000;
 sub_08074DE0(0x30);work[0xAA]++;
}

void sub_08031AFC(void){
 u32 i;u8 *work=gState0TransferWork.bytes;
 work[0x60]=sub_08032FB8(work[0x5C]);i=0;
 {u8 *setup=gSetupBuffer_03000590;u32 address=(u32)work;u8 *cursor=(u8 *)(address+0x60);u8 *slots=(u8 *)(address+0x61);
 do{u32 record=((*cursor)<<8)+(u32)setup;
 if(*(u8 *)(record+0x40)&&sub_08032FD0(*cursor,setup[(*(u8 *)(address+0x5C)<<8)+6]))*(u8 *)(i+(u32)slots)=*cursor+1;
 *cursor+=1;++i;}while(i<=2);}
 if(sub_08032FFC())((struct Continued31AFCWork *)&gState0TransferWork)->selected=sub_0803301C()+1;
 else{u8 *work=gState0TransferWork.bytes;work[0x60]=sub_08032FB8(work[0x5C]);((struct Continued31AFCWork *)work)->selected=sub_08033090(work[0x60])+1;}
 {u8 *work=gState0TransferWork.bytes;u8 *selected=&((struct Continued31AFCWork *)work)->selected;((struct Continued31AFCWork *)work)->found=sub_080330E8(*selected-1)+1;}
 {u8 *work=gState0TransferWork.bytes;sub_08033154(work[0x5C],work[0x5D]);}
}

void sub_080644D8(void) {
 u32 sound;
 s32 mode;
 sub_08062ED8();
 if(((struct ChoiceWork644D8 *)gMainContextPointer_03006F74)->timer==0) {
  sub_0803FAA0(1,0,1);
  gUnknown_0300137C++;
  mode=((struct ChoiceWork644D8 *)gMainContextPointer_03006F74)->mode;
  sound=5;
  if(mode!=0) sound=14;
  sub_08074DE0(sound);
 }
}

void sub_0807250C(struct EnvelopeWorkInitQ14 *work) {
 u32 count;
 if(sub_080724B0(work)==0) {
  count=work->decay>>4;
  work->countdown=count;
  if(count==0) {sub_080724D8(work);return;}
  work->step=-(0xF & work->decay);
  work->state=3;
 }
}

u32 sub_08073B68(s32 arg0) {
    const u16 *table=gPitchScale083ABC46;
    s32 temp_r4;
    s32 var_r1;
    s32 var_r1_2;
    s32 var_r4;

    if (arg0 > 0) {
        temp_r4 = sub_0807CDF8(arg0, 0xC);
        var_r1 = (u32)table[temp_r4] << sub_0807CD2C(arg0, 0xC);
    } else if (arg0 < 0) {
        arg0 = (s32)(0U-(u32)arg0);
        var_r4 = sub_0807CD2C(arg0, 0xC);
        var_r1_2 = sub_0807CDF8(arg0, 0xC);
        if (var_r1_2 != 0) {
            var_r1_2 = 0xC - var_r1_2;
            var_r4 += 1;
        }
        var_r1 = (s32) table[var_r1_2] >> var_r4;
    } else {
        var_r1 = (s32) table[0];
    }
    return (u32) var_r1;
}
