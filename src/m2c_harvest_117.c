/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct SelectionOutput {u8 before88[0x88];u8 first;u8 before8B[2];u8 second;};


void sub_080355C4(u32 selected);
void sub_0803628C(void);
void sub_0806E10C(s8 value,u32 slot);

void sub_080355C4(u32 selected) {
    void *temp_r0;
    u8 *setup;
    struct SelectionOutput *work;

    work=(void*)gState0TransferWork.bytes;
    setup=gSetupBuffer_03000590;
    selected<<=8;
    temp_r0=(void*)(selected+(u32)setup);
    work->first = (*(u8 *)((u8 *)(temp_r0) + 0xE0)) - 1;
    work->second = (*(u8 *)((u8 *)(temp_r0) + 0xE1)) - 1;
}

void sub_0803628C(void) {
    s32 var_r3;
    u32 var_r0;
    void *temp_r2;
    u8 *setup;

    setup=gSetupBuffer_03000590;
    temp_r2=(void*)((gState0TransferWork.bytes[0x88]<<8)+(u32)setup);
    var_r3=(8&(*(u8 *)((u8 *)(temp_r2) + 0xC0)))?0x28:0x14;
    var_r0 = (*(u8 *)((u8 *)(temp_r2) + 0xC1)) + var_r3;
    if (var_r0 > 0x4FU) {
        var_r0 = 0x50;
    }
    (*(u8 *)((u8 *)(temp_r2) + 0xC1)) = (u8) var_r0;
}

void sub_0806E10C(s8 value,u32 slot) {
 struct FrameObject *frames,*object;
 u8 zero,*delay;
 slot<<=24;
 frames=gFrameObjects;
 slot>>=18;
 object=(void*)(slot+(u32)frames);
 *(delay=&object->commandDelay)=(zero=0,value);
 object->commandStopped=zero;
 *(u16*)&object->unknown2C[4]=object->frameAndGroup;
 object->unknown1A=zero;
}
