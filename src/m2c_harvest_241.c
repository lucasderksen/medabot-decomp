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
#include "display_helpers.h"
#include "effect_work.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
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

struct ContinuedFinalFrames31 {u8 before[0x1E00];struct FrameObject last[8];};
struct ContinuedSetup30 {u8 before[0xC9];u8 mode,zero,first,second;u8 tail[0x33];};
struct ContinuedPhaseWork30 {u8 before[0xAA];u8 phase;};
struct ContinuedPhase31 {u8 before[0xAA];u8 phase;};
struct ContinuedYBacking31 {u8 before[0x844];u16 ys[0xBDE];};
struct ContinuedInput31 {u8 before[0xEC];u16 value;};
struct ContinueCallbackWork {u8 pad[0x163];u8 again;u8 gap[0x4A];u8 skip;};
struct AnimationRecord6B4C8 { u16 frame; s16 duration; u8 next; u8 pad[3]; };
struct ScriptWork6E3C4 { u8 pad0[4]; u16 mode; u8 pad6[6]; u16 selection; };
struct DigitWork700C8 { u8 pad[0xD0]; u8 position,padD1; u16 digits[13]; };
struct FillWork70170 { u8 pad[0xF0]; u16 first,second; };
struct ScriptWork72C74 { u8 pad0[0x14]; const u8 *script; u8 pad18[0x3E]; u8 length,low,high; };
struct CommandWork73FC0 { u8 pad[0x3E]; u8 command; };

extern const struct AnimationRecord6B4C8 gAnimationRecords6B4C8[];
extern const u8 *const gState0NextCommands_083B6100[];
extern const void *const gScriptTable6E3C4[];
extern struct ContinueCallbackWork gUnknown_03001800;
extern struct DigitWork700C8 gDigitWork700C8;
extern struct FillWork70170 gFillWork70170;
extern struct ScriptWork6E3C4 gScriptWork6E3C4;
extern u32 sub_08034E94(void);
extern void (*const gUnknown_083AF180[])(void);
extern void sub_08073DF4(void *);
extern void sub_08073E24(void *);
extern void sub_08073EC8(void *);
extern void sub_08073F6C(void *);
extern void sub_08073F98(void *);

s32 sub_0801ADE8(u32 direction);
void sub_08022010(void);
void sub_080220A0(void);
void sub_0802BBA8(void);
void sub_0802BC1C(void);
void sub_08033840(void);
void sub_0806B4C8(void);
void sub_0806E3C4(void);
u32 sub_080700C8(void);
u32 sub_08070170(void);
void sub_080707BC(u32 arg0,u8 arg1,u8 arg2);
void sub_08072C74(struct ScriptWork72C74 *work);
void sub_08073FC0(struct CommandWork73FC0 *work);

s32 sub_0801ADE8(u32 direction) {

    s32 finished=1;
    u32 i=0;
    struct ContinuedFinalFrames31 *frames=(struct ContinuedFinalFrames31 *)&gFrameObjects;
    u32 groupMask=3;
    struct FrameObject *frame=frames->last;
    u32 cursor=(u32)&frames->last[0].commandOffset;
    do{
        u8 *bytes=(u8 *)cursor;
        u32 tick=bytes[0]+1;
        bytes[0]=tick;
        if(!(tick%4)){
            u32 group=(bytes[1]+1)&groupMask;
            bytes[1]=group;frame->frameAndGroup=group+0x616;
        }
        if(bytes[5]!=bytes[3]){
            finished=0;
            if(bytes[6])bytes[6]--;
            else{
                u32 steps;
                if(direction<=2)frame->screenX=(u16)frame->screenX+4;
                else frame->screenX=(u16)frame->screenX-4;
                steps=bytes[7]+1;bytes[7]=steps;
                if(!(steps&1))bytes[3]++;
            }
        }
        frame++;cursor+=64;i++;
    }while(i<=7);
    return finished;
}

void sub_08022010(void) {

    struct ContinuedSetup30 *setup=(struct ContinuedSetup30 *)gSetupBuffer_03000590;
    u8 *work=gState0TransferWork.bytes;
    u8 *bank=work+0x88;
    u8 *mode=&setup[*bank].mode;
    u32 zero=0;
    struct FrameObject *frames;
    struct FrameObject *initial;
    *mode=zero;
    setup[*bank].zero=zero;
    setup[*bank].first=zero;
    setup[*bank].second=zero;
    frames=gFrameObjects;
    {
    u32 frameIndex=*bank*3+0x47;
    initial=&frames[frameIndex];
    {
    initial->flags|=0x8220;
    }
    ((struct FrameObject *)(((*bank*3+0x47)<<6)+(u32)frames))->scaleY=0x40;
    ((struct FrameObject *)(((*bank*3+0x47)<<6)+(u32)frames))->scaleX=0x40;
    }
    sub_08074DE0(0x37);
    ((struct ContinuedPhaseWork30 *)work)->phase++;
}

void sub_080220A0(void) {

    struct FrameObject *frames=gFrameObjects;
    u8 *work=gState0TransferWork.bytes;
    u8 *bank=work+0x88;
    u32 index=*bank*3+0x47;
    struct FrameObject *frame=&frames[index];
    if(frame->scaleX!=4){
        frame->flags|=0x8000;
        ((struct FrameObject *)(((*bank*3+0x47)<<6)+(u32)frames))->scaleY+=4;
        ((struct FrameObject *)(((*bank*3+0x47)<<6)+(u32)frames))->scaleX-=4;
    }
    sub_08040BD8(gState0NextCommands_083B6100[60],0x21);
    if(gFrameObjects[0x21].commandStopped==0xFF){
        sub_08040CD0(0x21,1);
        sub_08040CD0((u8)(gState0TransferWork.bytes[0x88]*3+0x47),1);
        ((struct ContinuedPhase31 *)work)->phase++;
    }
}

void sub_0802BBA8(void) {

    u32 i=0;
    u8 *work=gState0TransferWork.bytes;
    union State0TypedWork *typed=&gState0TypedWork;
    u8 *selected=work+0xD2;
    u16 *timerCursor=&typed->widths.word86;
    struct ContinuedYBacking31 *frames=(struct ContinuedYBacking31 *)&gFrameObjects;
    u16 *y=frames->ys;
    do{if(*(u8 *)(i+(u32)selected) && !(*timerCursor&1))*y=*y-1;y+=32;i++;}while(i<=2);
    {
        u32 timer=typed->widths.word86+1;
        typed->widths.word86=timer;
        if((u16)timer==0x20){typed->widths.word86=0x3C;((struct ContinuedPhase31 *)work)->phase++;}
    }
}

void sub_0802BC1C(void) {

    u32 i;
    u8 *initial,*work,*selected;
    u16 *source,*amounts;
    sub_08040CD0(0x21,3);
    i=0;initial=gState0TransferWork.bytes;selected=initial+0xD2;work=initial;
    source=&((struct ContinuedInput31 *)work)->value;
    amounts=(u16 *)(work+0xD6);
    do{if(*(u8 *)(i+(u32)selected))*amounts=*source;amounts++;i++;}while(i<=2);
    ((struct ContinuedPhase31 *)work)->phase++;
}

void sub_08033840(void) {

    s32 sp0;
    u32 temp_r0;
    u32 temp_r0_2;

    if (sub_0803EED8() == 0) {
        if (gRenderMode == 2) {
            sp0 = 0x200;
            CpuFastSet(&sp0, gRenderWork->objects, 0x01000100U);
        }
        if (gUnknown_03001800.skip == 0) {
            sub_080195C0();
        }
        do {
            gUnknown_03001800.again = 0U;
            temp_r0 = sub_08034E94();
            gUnknown_0300137C = temp_r0;
            if ((s32) temp_r0 > 0x7F) {
                do {
                    sub_08034F08();
                    temp_r0_2 = sub_08034E94();
                    gUnknown_0300137C = temp_r0_2;
                } while ((s32) temp_r0_2 > 0x7F);
            }
            gUnknown_083AF180[gUnknown_0300137C]();
        } while (gUnknown_03001800.again != 0);
    }
}

void sub_0806B4C8(void) {

 struct FrameObject *frame;
 const struct AnimationRecord6B4C8 *records;
 u8 index = 0;
 s32 duration;
 do {
  frame = &gFrameObjects[index];
  if (frame->commandOffset != 0) {
   records = gAnimationRecords6B4C8;
   duration = records[frame->commandOffset].duration;
   if (duration <= (u8)frame->unknown23[4]++) {
    frame->unknown23[4] = 0;
    frame->commandOffset = records[frame->commandOffset].next;
    frame->frameAndGroup = records[frame->commandOffset].frame;
   }
  }
  index++;
 } while (index <= 19);
}

void sub_0806E3C4(void) {

 const void *const *table = gScriptTable6E3C4;
 struct ScriptWork6E3C4 *work = &gScriptWork6E3C4;
 if (sub_0803FB3C(table[work->selection]) != 0) {
  work->mode = 5;
  gUnknown_0300137C = 2;
 }
}

u32 sub_080700C8(void) {

 struct DigitWork700C8 *work = &gDigitWork700C8;
 u16 *cursor;
 s32 count;
 volatile u32 *dma;
 u32 zero = 0;
 u8 *position;
 u32 reset;
 count = 12;
 cursor = &work->digits[12];
 do {
  *cursor = zero;
  cursor = (u16 *)((u32)cursor - 2);
  count--;
 } while (count >= 0);
 reset = 0;
 position = (u8 *)work + 0xD0;
 *position = reset;
 dma = (volatile u32 *)0x040000D4;
 dma[0] = (u32)(position + 2);
 dma[1] = 0x0600FC44;
 dma[2] = 0x8000000D;
 return dma[2];
}

u32 sub_08070170(void) {

 u16 fill;
 volatile u32 *dma;
 struct FillWork70170 *work = &gFillWork70170;
 work->second = 0;
 work->first = 0;
 fill = 0;
 dma = (volatile u32 *)0x040000D4;
 dma[0] = (u32)&fill;
 dma[1] = 0x0600F86C;
 dma[2] = 0x81000007;
 return dma[2];
}

void sub_080707BC(u32 arg0,u8 arg1,u8 arg2) {

    u8 temp_r5;
    struct FrameObject *temp_r4;
    u32 zero;
    u8 *cursor,*randomCursor;
    struct FrameObject *frameRoot;
    u32 root,delta;
 u8 random;

    frameRoot=gFrameObjects;
    temp_r5 = arg2;
    root=(u32)frameRoot;
    temp_r4=(struct FrameObject *)(root+((u32)arg1<<6));
    cursor=(u8 *)temp_r4+0x20;
    zero=0;
    *cursor = arg0;
    *((u8 *)temp_r4+0x21) = zero;
    if (temp_r5 != 0) {
        random=(u8)(NextRandom(0U)&3U);
        randomCursor=(u8 *)temp_r4+0x22;
        *randomCursor=random;
        delta=temp_r5-4;
        randomCursor++;
        *randomCursor=delta;
    }
    (*(u16 *)((u8 *)(temp_r4) + 0x30)) = (u16) temp_r4->frameAndGroup;
    temp_r4->unknown1A = zero;
}

void sub_08072C74(struct ScriptWork72C74 *work) {

 u8 second;
 work->length = *work->script++;
 second = *work->script++;
 work->high = second >> 4;
 work->low = second & 15;
}

void sub_08073FC0(struct CommandWork73FC0 *work) {

 u8 *command = &work->command;
 switch (*command) {
 case 1: sub_08073E24(work); break;
 case 2: sub_08073EC8(work); break;
 case 3: sub_08073DF4(work); break;
 case 4: sub_08073F98(work); break;
 case 5: sub_08073F6C(work); break;
 default: return;
 }
 *command = 0;
}
