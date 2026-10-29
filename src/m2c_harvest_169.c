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
#include "state0_work.h"
#include "tile_text.h"

struct Dma6D6E4Registers { const void *volatile source; void *volatile destination; volatile u32 control; };
struct Work6D6E4 { u16 mode; u16 selection; u8 pad04[40]; };

extern struct Work6D6E4 gGraphicsTransferCounter;

void sub_0806D6E4(void);

void sub_0806D6E4(void) {
    s32 sp0;
    struct Dma6D6E4Registers *dma;

    sp0 = 0;
    dma = (struct Dma6D6E4Registers *)0x040000D4;
    dma->source = &sp0;
    dma->destination = (void *)0x06000000;
    dma->control = 0x85006000U;
    (void)dma->control;
    sp0 = 0;
    dma->source = &sp0;
    dma->destination = (void *)0x05000000;
    dma->control = 0x85000100U;
    (void)dma->control;
    sp0 = 0;
    dma->source = &sp0;
    dma->destination = (void *)0x07000000;
    dma->control = 0x85000100U;
    (void)dma->control;
    sp0 = 0;
    dma->source = &sp0;
    dma->destination = gFrameObjects;
    dma->control = 0x85000800U;
    (void)dma->control;
    sp0 = 0;
    dma->source = &sp0;
    dma->destination = &gGraphicsTransferCounter;
    dma->control = 0x8500000BU;
    (void)dma->control;
    *(volatile u16 *)0x04000000 = 0x61;
    gGraphicsTransferCounter.mode = 3;
    gGraphicsTransferCounter.selection = 2;
    gBgScroll0.x = 0;
    gBgScroll0.y = 0;
    gBgScroll1.x = 0;
    gBgScroll1.y = 0;
    gBgScroll2.x = 0;
    gBgScroll2.y = 0;
    gBgScroll3.x = 0;
    gBgScroll3.y = 0;
    gUnknown_0300137C = 4;
}
