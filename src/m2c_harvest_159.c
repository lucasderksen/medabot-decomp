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
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "tile_text.h"

struct LocalMenuResetWork { u16 mode0; s16 selection2; u8 pad4[4]; s32 counter8; u8 padC[8]; };
struct LocalMenuResetDma { const void *volatile source; void *volatile destination; volatile u32 control; };

extern s8 gUnknown_03007010;
extern struct LocalMenuResetWork gGraphicsTransferCounter;

void sub_08070914(void);

void sub_08070914(void) {
    s32 sp0;
    struct LocalMenuResetDma *dma;

    sp0 = 0;
    dma = (struct LocalMenuResetDma *)0x040000D4;
    dma->source = &sp0;
    dma->destination = (void *)0x06000000;
    dma->control = 0x85006000;
    (void)dma->control;
    sp0 = 0;
    dma->source = &sp0;
    dma->destination = (void *)0x05000000;
    dma->control = 0x85000100;
    (void)dma->control;
    sp0 = 0;
    dma->source = &sp0;
    dma->destination = gFrameObjects;
    dma->control = 0x85000800;
    (void)dma->control;
    sp0 = 0;
    dma->source = &sp0;
    dma->destination = &gGraphicsTransferCounter;
    dma->control = 0x85000005;
    (void)dma->control;
    sub_08074B88(0U);
    *(volatile u16 *)0x04000000 = 0x60;
    gGraphicsTransferCounter.mode0 = 3;
    gGraphicsTransferCounter.selection2 = 6;
    gBgScroll0.x = 0;
    gBgScroll0.y = 0;
    gBgScroll1.x = 0;
    gBgScroll1.y = 0;
    gBgScroll2.x = 0;
    gBgScroll2.y = 0;
    gBgScroll3.x = 0;
    gBgScroll3.y = 0;
    gUnknown_03007010 = 0;
    gUnknown_0300137C = 3;
}
