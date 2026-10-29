/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct ContinuedSetup22CD0 {u8 prefix[0x59];u8 equipped;u8 tail[0xA6];};
struct FrameWork6CC80 {
 u8 pad000[0x406];u16 frame16;
 u8 pad408[0x3E];u16 frame17;
 u8 pad448[0x3E];u16 frame18;
 u8 pad488[0x52];u16 timer;
 u8 pad4DC[4];u8 phase;u8 mode;
};

extern u32 sub_0803725C(void);
extern void sub_0803579C(u32,u32);
extern void sub_08035814(u32);
extern void sub_08037280(u32,u32);

void sub_08021370(void);
void sub_08022CD0(void);
void sub_0806CC80(void);

void sub_08021370(void) {
    if(gFrameObjects[0x21].unknown23[4]==0x10) {
        if(gState0TransferWork.bytes[0x51]==2)gState0TransferWork.bytes[0xAA]=0x14;
        else {sub_08074DE0(0x3E);gState0TransferWork.bytes[0xAA]=0xE;}
    } else {
        if(gFrameObjects[0x21].unknown23[4]<=7)gFrameObjects[0x21].scaleX+=8;
        else gFrameObjects[0x21].scaleX-=8;
        gFrameObjects[0x21].unknown23[4]++;
    }
}

void sub_08022CD0(void) {
    u8 *work=gState0TransferWork.bytes;
    u8 *bank=work+0x87;
    u32 initialBank=*bank;
    u8 *part=work+0xA7;
    struct ContinuedSetup22CD0 *setup;
    sub_0803579C(initialBank,*part);
    sub_08035814(*bank);
    if(sub_0803725C()!=0) {work[0xA6]=0x1A;work[0xAA]++;}
    else {
        setup=(struct ContinuedSetup22CD0 *)gSetupBuffer_03000590;
        if(setup[work[0x88]].equipped!=0) {work[0xA6]=9;work[0xAA]++;}
        else {sub_08036270();sub_08037280(*bank,*part);work[0xAA]=4;}
    }
}

void sub_0806CC80(void) {
    u32 blink;
    u16 frame;
    if (((struct FrameWork6CC80 *)gFrameObjects)->phase != 0) {
        switch (((struct FrameWork6CC80 *)gFrameObjects)->mode) {
        case 0:
            blink = ((struct FrameWork6CC80 *)gFrameObjects)->timer & 4;
            frame = 27;
            if (blink)
                frame = 26;
            ((struct FrameWork6CC80 *)gFrameObjects)->frame17 = frame;
            ((struct FrameWork6CC80 *)gFrameObjects)->frame18 = 28;
            ((struct FrameWork6CC80 *)gFrameObjects)->frame16 = 31;
            break;
        case 1:
            ((struct FrameWork6CC80 *)gFrameObjects)->frame17 = 26;
            ((struct FrameWork6CC80 *)gFrameObjects)->frame18 = 28;
            ((struct FrameWork6CC80 *)gFrameObjects)->frame16 = 30;
            break;
        case 2:
            ((struct FrameWork6CC80 *)gFrameObjects)->frame17 = 26;
            blink = ((struct FrameWork6CC80 *)gFrameObjects)->timer & 4;
            frame = 29;
            if (blink)
                frame = 28;
            ((struct FrameWork6CC80 *)gFrameObjects)->frame18 = frame;
            ((struct FrameWork6CC80 *)gFrameObjects)->frame16 = 32;
            break;
        }
    } else {
        ((struct FrameWork6CC80 *)gFrameObjects)->frame17 = 26;
        ((struct FrameWork6CC80 *)gFrameObjects)->frame18 = 28;
        ((struct FrameWork6CC80 *)gFrameObjects)->frame16 = 30;
    }
}
