/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "effect_work.h"
#include "frame.h"
#include "frame_objects.h"
#include "input.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct ContinuedTypedPhase29 {u8 before[0x84];u8 phase;u8 gap[4];u8 mode;};
struct ContinuedTransferPhase29 {u8 before[0x60];u8 first;u8 middle[0x49];u8 phase;};
struct SpriteWork62C28 {u8 pad0[0x7A];u8 mode;};
struct ScriptSlots640EC {u8 pad0[0x64];const void *selected;};
struct TimerWork640EC {u8 pad0[0x3C];u16 timer;};
struct DigitWork6FE44 {u8 pad0[0xF0];u16 left,right;};
struct Dma6FE44 {u32 source,destination,control;};

extern const struct ScriptSlots640EC gScriptSlots640EC;
extern const void * const gGraphicsTable62C28[];
extern struct DigitWork6FE44 gDigitWork6FE44;
extern u32 sub_0807CEC8(u32,u32),sub_0807CF40(u32,u32);
extern u8 gUnknown_030004F2[];
extern u8 gUnknown_03000506[];
extern void sub_08062D60(void);

void sub_0802761C(void);
void sub_08062C28(u32 arg0, u32 arg1);
void sub_080640EC(void);
void sub_0806FE44(void);

void sub_0802761C(void) {

    u32 i=0;
    u8 *setup=gSetupBuffer_03000590;
    u8 *first=&gTransferByte_03001860;
    do{
        u32 bank=*first;
        u32 slot=bank+i;
        if(*(u8 *)((slot<<8)+(u32)setup+0x40)){
            switch(i){
            case 0:sub_0801A574(gDebugMenuTextBuffer,slot,0x21);break;
            case 1:sub_0801A574(gUnknown_030004F2,bank+1,0x21);break;
            case 2:sub_0801A574(gUnknown_03000506,bank+2,0x21);break;
            }
        }
        i++;
    }while(i<=2);
    {
        struct ContinuedTypedPhase29 *initial=(struct ContinuedTypedPhase29 *)&gState0TypedWork;
        struct ContinuedTypedPhase29 *work;
        u8 *phase=&initial->phase;
        u32 next=*phase+1;
        u32 mode;
        *phase=next;
        mode=initial->mode;
        work=initial;
        if(mode==0 && (*(u8 *)&gRepeatedKeys&1) && (u8)next>0x32)*phase=0x78;
        if(work->phase==0x78){
            struct ContinuedTransferPhase29 *transfer=(struct ContinuedTransferPhase29 *)&gState0TransferWork;
            sub_08040CD0((u8)(transfer->first*4+0x21),0xC);
            transfer->phase++;
        }
    }
}

void sub_08062C28(u32 arg0, u32 arg1) {

    u32 zero;
    u32 flags;
    struct FrameObject *frames;
    LeDecompress(gGraphicsTable62C28[arg0*5+arg1], (void *)0x06010000);
    frames=gFrameObjects;
    zero=0;
    flags=frames->flags=0x8A24;
    if ((s8) ((struct SpriteWork62C28 *)gMainContextPointer_03006F74)->mode == 0) {
        frames->flags = flags | 0x4000;
    }
    frames->screenX = 0xB8;
    frames->screenY = 0x38;
    frames->frameAndGroup = 0x200;
    frames->palette = zero;
    frames->tableSelector = zero;
    frames->priority = 0x40;
    frames->scaleX = 0x40;
    frames->scaleY = 0x40;
}

void sub_080640EC(void) {

    s32 temp_r0;

    if (sub_0803FB3C(gScriptSlots640EC.selected) != 0) {
        sub_08062D60();
        temp_r0 = ((struct TimerWork640EC *)gMainContextPointer_03006F74)->timer - 1;
        ((struct TimerWork640EC *)gMainContextPointer_03006F74)->timer = temp_r0;
        if ((s32) ((u32)temp_r0 << 0x10) < 0) {
            gUnknown_0300137C += 1;
            ((struct TimerWork640EC *)gMainContextPointer_03006F74)->timer = 0U;
        }
    }
}

void sub_0806FE44(void) {

    u16 sp0[7];
    u32 zero;
    u16 *out,*out1,*out2,*out3,*out4,*out5;
    u32 tileBase;
    volatile struct Dma6FE44 *dma;
    u16 temp_r4;
    u16 temp_r4_2;
    u16 temp_r5;
    u16 temp_r6;

    temp_r5 = gDigitWork6FE44.left;
    temp_r6 = sub_0807CF40(gDigitWork6FE44.right, 0x3E8);
    out=sp0;
    {u32 digit=sub_0807CF40(temp_r5, 0xA);
    tileBase=0x90C8;
    digit+=tileBase;
    zero=0;
    out[3]=(u16)digit;}
    temp_r4 = sub_0807CEC8(temp_r5, 0xA);
    out1=sp0;
    out1[1] = (s16) (sub_0807CF40(temp_r4, 0xA) + tileBase);
    temp_r4=(u16)sub_0807CEC8(temp_r4,0xA);
    out2=sp0;
    out2[0]=(u16)(sub_0807CF40(temp_r4,0xA)+tileBase);
    sp0[2] = zero;
    out3=sp0;
    out3[6] = (s16) (sub_0807CF40(temp_r6, 0xA) + tileBase);
    temp_r4_2 = sub_0807CEC8(temp_r6, 0xA);
    out4=sp0;
    out4[5] = (s16) (sub_0807CF40(temp_r4_2, 0xA) + tileBase);
    temp_r4_2=(u16)sub_0807CEC8(temp_r4_2,0xA);
    out5=sp0;
    out5[4]=(u16)(sub_0807CF40(temp_r4_2,0xA)+tileBase);
    dma=(volatile struct Dma6FE44 *)0x040000D4;
    dma->source=(u32)sp0;
    dma->destination=0x0600F86C;
    dma->control=0x80000007;
    (void)dma->control;
}
