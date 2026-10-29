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
#include "frame.h"
#include "gba.h"
#include "main.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "render_work.h"
#include "rom_libc.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "tile_text.h"

typedef void (*Callback63948)(void);
typedef void (*Callback6463C)(void);
typedef s32 (*FrameCommand7178C)(u32);

extern Callback63948 const gUnknown_080AFBE4[13];
extern Callback6463C const gUnknown_080AFC18[12];
extern FrameCommand7178C const gUnknown_08485BB8[];
extern void sub_0806B718(u8);

void sub_08063948(void);
void sub_0806463C(void);
void sub_0807178C(void);

void sub_08063948(void) {

    Callback63948 sp0[13];
    s32 sp34;

    memcpy(sp0,gUnknown_080AFBE4, 0x34U);
    if (gRenderMode == 2) {
        sp34 = 0x200;
        CpuFastSet(&sp34, gRenderWork->objects, 0x01000100U);
    }
    sp0[gUnknown_0300137C]();
    if (gFrameCounter & 1) {
        gBgScroll3.x += 1;
        gBgScroll3.y += 1;
    }
}

void sub_0806463C(void) {

    Callback6463C sp0[12];
    s32 sp30;

    memcpy(sp0,gUnknown_080AFC18,48);
    if (gRenderMode == 2) {
        sp30 = 0x200;
        CpuFastSet(&sp30, gRenderWork->objects, 0x01000100U);
    }
    sp0[gUnknown_0300137C]();
    if (gFrameCounter & 1) {
        gBgScroll3.x += 1;
        gBgScroll3.y += 1;
    }
}

void sub_0807178C(void) {

    s32 temp_r0;
    struct FrameObject *temp_r4;
    u8 var_r6;
 u32 root;

    var_r6 = 0;
    do {
        root=(u32)gFrameObjects;
 temp_r4=(struct FrameObject*)(root+((u32)var_r6<<6));
        if (temp_r4->commandDelay != 0) {
            temp_r4->unknown1A += 1;
            temp_r0 = gUnknown_08485BB8[temp_r4->commandDelay-1](var_r6);
            switch(temp_r0){
            case 0:temp_r4->commandDelay=0;temp_r4->commandOffset=0;break;
            case 1:break;
            case 0xFF:sub_0806B718(var_r6);break;
            }
        }
        var_r6 += 1;
    } while ((u32) var_r6 <= 0x19U);
}
