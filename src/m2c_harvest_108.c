/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct SmallCounterWork {u32 prefix[2];s32 counter;u8 active;};

extern void sub_080191A4(s32, u8);

void sub_080192B8(s32 arg0);
s32 sub_0806E014(s32 arg0);
void sub_0806E93C(void);

void sub_080192B8(s32 arg0) {
    u8 temp_r0;
    void *temp_r1;
    u8 *setup;

    setup=gSetupBuffer_03000590;
    temp_r1 = (void*)((u32)(arg0<<8)+(u32)setup);
    temp_r0 = (*(u8 *)((u8 *)(temp_r1) + 0xC4));
    if(temp_r0 == 0) return;
    if(temp_r0 == 38 || temp_r0 == 41)
        sub_080191A4(arg0,(*(u8 *)((u8 *)(temp_r1) + 0xC7)));
}

s32 sub_0806E014(s32 arg0) {
    u32 temp_r1;
    u8 value;
    u32 shifted;
    struct FrameObject *objects;
    void *temp_r0;

    shifted=arg0<<24;
    objects=gFrameObjects;
    shifted>>=18;
    temp_r0=(void*)(shifted+(u32)objects);
    temp_r1 = (*(u8 *)((u8 *)(temp_r0) + 9)) + 8;
    (*(u8 *)((u8 *)(temp_r0) + 9)) = temp_r1;
    value=temp_r1;
    if ((u32) value > 0x3FU) {
        return 0;
    }
    return 1;
}

void sub_0806E93C(void) {
    struct SmallCounterWork *work,*saved;
    s32 count;
    work=(void*)&gState0TransferWork;
    count=work->counter;
    saved=work;
    if (count == 0) {
        saved->active = 1;
        goto block_4;
    }
    if ((s32) count > 0x3C) {
        saved->counter = 0;
        gUnknown_0300137C = 8;
        return;
    }
block_4:
    saved->counter = (s32) (saved->counter + 1);
}
