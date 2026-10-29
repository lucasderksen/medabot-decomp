/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "display_effects.h"
#include "effect_work.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"

struct LocalTransferDispatch {u8 pad00[4];s16 previousState;u8 pad06[2];s32 counter;};

extern const void *const gUnknown_08486D78[];
extern struct LocalTransferDispatch gGraphicsTransferCounter;
extern u32 gPostDispatchWord_03002B70;
extern void sub_08071898(u8,u16,u8);
extern void sub_080718D4(u8,u16);
void sub_08071DB8(u32,u32,u32);

void sub_08060F78(void);
void sub_08071164(void);
void sub_08071630(void);

void sub_08060F78(void) {
    s32 sp10;
    struct FrameObject *temp_r0;
    u8 var_r2;

    sp10 = 0;
    CpuFastSet(&sp10, (void *)0x0600DA80, 0x01000080U);
    sub_08040CD0(0U, 0x80U);
    gFrameObjects[8].flags = 0x8004;
    gFrameObjects[8].tableSelector = 0;
    gFrameObjects[8].palette = 0xE;
    gFrameObjects[8].frameAndGroup = 0x307;
    gFrameObjects[8].screenX = 8;
    gFrameObjects[8].screenY = ((*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 5)) * 0x18) + 0x20;
    gFrameObjects[8].flags |= 0x1200;
    gFrameObjects[8].scaleX = 0x40;
    gFrameObjects[8].scaleY = 0x40;
    gFrameObjects[7].flags = 0xC000;
    gFrameObjects[7].tableSelector = 2;
    gFrameObjects[7].palette = 1;
    gFrameObjects[7].frameAndGroup = 0x1A;
    gFrameObjects[7].screenX = 0x98;
    gFrameObjects[7].screenY = 0;
    var_r2 = 0;
    do {
        temp_r0 = (struct FrameObject *)(((var_r2 + 0xC) * 64) + (u32)gFrameObjects);
        temp_r0->flags = 0x8000;
        temp_r0->tableSelector = 2;
        temp_r0->palette = 0;
        var_r2 += 1;
    } while ((u32) var_r2 <= 3U);
    gFrameObjects[0xD].flags |= 0x1000;
    gFrameObjects[0xF].flags |= 0x2000;
    gFrameObjects[0xD].frameAndGroup = 5;
    gFrameObjects[0xE].frameAndGroup = 5;
    gFrameObjects[0xC].frameAndGroup = 8;
    gFrameObjects[0xF].frameAndGroup = 8;
    gFrameObjects[0xD].screenX = 0x48;
    gFrameObjects[0xD].screenY = 0x2C;
    gFrameObjects[0xE].screenX = 0x58;
    gFrameObjects[0xE].screenY = 0x2C;
    gFrameObjects[0xC].screenX = 0x50;
    gFrameObjects[0xC].screenY = 0x22;
    gFrameObjects[0xF].screenX = 0x50;
    gFrameObjects[0xF].screenY = 0x3E;
    sub_08041164(gDebugMenuTextBuffer, gPostDispatchWord_03002B70);
    sub_08040DB8(gDebugMenuTextBuffer, 0U, 0x15, 1, 7U, 0xFU, 1U, 0U);
    gUnknown_0300137C += 1;
}

void sub_08071164(void) {
    struct LocalTransferDispatch *work=&gGraphicsTransferCounter;
    struct LocalTransferDispatch *scriptWork;
    u32 phase=work->counter;
    scriptWork=work;
    switch(phase) {
    case 0:
        sub_0803FAA0(1,0,0);
        sub_08071898(0x19,0x4B,8);
        gGraphicsTransferCounter.counter++;
        break;
    case 2:
        sub_0803FB0C();
        sub_080718D4(0x19,0x4B);
        sub_08071898(0x16,0x2D,8);
        gGraphicsTransferCounter.counter++;
        break;
    case 4:
        sub_0803FB0C();
        sub_080718D4(0x16,0x2D);
        sub_08071898(0x19,0x4E,8);
        gGraphicsTransferCounter.counter++;
        break;
    case 6:
        sub_0803FB0C();
        sub_080718D4(0x19,0x4B);
        sub_08071898(0x17,0x36,8);
        gGraphicsTransferCounter.counter++;
        break;
    case 8:
        sub_0803FB0C();
        sub_080718D4(0x17,0x36);
        sub_08071898(0x19,0x51,8);
        gGraphicsTransferCounter.counter++;
        break;
    case 10:
        sub_0803FB0C();
        sub_080718D4(0x19,0x4B);
        sub_08071898(0x16,0x2D,8);
        gGraphicsTransferCounter.counter++;
        break;
    case 12:
        sub_0803FB0C();
        sub_080718D4(0x16,0x2D);
        sub_08071898(0x19,0x4B,8);
        gGraphicsTransferCounter.counter++;
        break;
    case 14:
        sub_0803FB0C();
        sub_080718D4(0x16,0x27);
        sub_080718D4(0x17,0x33);
        sub_080718D4(0x19,0x4B);
        sub_08071898(0x18,0x3F,6);
        gGraphicsTransferCounter.counter++;
        break;
    case 1: case 3: case 5: case 7: case 9: case 11: case 13: case 15: 
        if(sub_0803FB3C(gUnknown_08486D78[(scriptWork->counter>>1)])) {
            scriptWork->counter++;
        }
        break;
    default:
        sub_08071898(0x18,0x3F,0xC);
        work->counter=0;
        work->previousState=0xC;
        gUnknown_0300137C=2;
        break;
    }
}

void sub_08071630(void) {
    struct LocalTransferDispatch *work=&gGraphicsTransferCounter;
    struct LocalTransferDispatch *scriptWork;
    u32 phase=work->counter;
    scriptWork=work;
    switch(phase) {
    case 0:
        sub_0803FAA0(1,0,0);
        sub_08071898(0x19,0x4B,8);
        gGraphicsTransferCounter.counter++;
        break;
    case 2:
        sub_0803FB0C();
        sub_080718D4(0x19,0x4B);
        sub_08071898(0x17,0x36,8);
        gGraphicsTransferCounter.counter++;
        break;
    case 4:
        sub_0803FB0C();
        sub_080718D4(0x17,0x36);
        sub_08071898(0x19,0x4B,8);
        gGraphicsTransferCounter.counter++;
        break;
    case 6:
        sub_0803FB0C();
        sub_080718D4(0x17,0x33);
        sub_080718D4(0x19,0x4B);
        sub_08071898(0x18,0x3F,6);
        gGraphicsTransferCounter.counter++;
        break;
    case 1: case 3: case 5: case 7: 
        if(sub_0803FB3C(gUnknown_08486D78[(scriptWork->counter>>1)+0xF])) {
            scriptWork->counter++;
        }
        break;
    default:
        work->counter=0;
        sub_08071898(0x16,0x27,8);
        sub_08071898(0x17,0x33,8);
        sub_08071898(0x19,0x4B,8);
        sub_08071DB8(3,0,0);
        sub_08071DB8(4,0xB,0);
        gUnknown_0300137C++;
        break;
    }
}
