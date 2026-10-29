/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "object_numeric_helpers.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sound_voice.h"
#include "sprite_layouts.h"
#include "state0_display.h"
#include "tile_text.h"

struct Point668D4 { s32 x, y; };
struct Row668D4 { u8 pad[0xD2]; s16 x, y, z; };
struct DmaRegs68BC4 { u32 source, destination, control; };
struct Dma69CC0 { u32 source, destination, control; };

extern s32 gTransferStep03000000;
extern s32 gUnknown_0850F498;
extern u16 gTransferOffsets03000008[];
extern u8 *gCtx668D4 asm("gMainContextPointer_03006F74");
extern u8 gTransferDivisor03000005;
extern void sub_08066870(s32 *, s32 *, struct Point668D4 *, struct Point668D4 *);
extern void sub_08069BFC_Int(s32 slot, s32 x, s32 y, s32 mode, s32 increment) asm("sub_08069BFC");

void sub_080668D4(s32 radius);
s32 sub_08068BC4(void);
void sub_08069CC0(void);

void sub_080668D4(s32 radius) {

    s32 points[14];
    s32 out[36];
    struct Point668D4 a, b;
    s32 i;
    s32 angle;
    s32 *src;
    s32 *next;
    s32 *dst;

    next = points;
    for (i = 0; i <= 5; i++) {
        angle = (i << 8) / 6;
        *next++ = radius * gAffineSineTable_080AE8F4[angle];
        *next++ = radius * gAffineSineTable_080AE8F4[angle + 0x40];
    }
    *next++ = points[0];
    *next = points[1];
    src = points;
    next = &points[2];
    dst = out;
    for (i = 0; i < 6; i++) {
        sub_08066870(src, next, &a, &b);
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = a.x;
        *dst++ = a.y;
        *dst++ = b.x;
        *dst++ = b.y;
        next += 2;
    }
    dst = out;
    for (i = 0; i <= 17; i++) {
        {
            u32 root = (u32)gCtx668D4;
            ((struct Row668D4 *)(root + (i << 4)))->x = *dst++ >> 8;
            ((struct Row668D4 *)(root + (i << 4)))->y = *dst++ >> 8;
            ((struct Row668D4 *)(root + (i << 4)))->z = 0x1E;
        }
    }
}

s32 sub_08068BC4(void) {

    u16 fill;
    fill = 0x1111;
    if (gTransferStep03000000 == 0)
        *(volatile u16 *)0x04000000 |= 0x100;
    if (gTransferStep03000000 % gTransferDivisor03000005 == 0) {
        volatile struct DmaRegs68BC4 *dma = (void *)0x040000D4;
        dma->source = (u32)&fill;
        dma->destination = gTransferOffsets03000008[gTransferStep03000000 / gTransferDivisor03000005] + 0x0600C000;
        dma->control = 0x80000001;
        (void)dma->control;
        dma->source = (u32)&fill;
        dma->destination = gTransferOffsets03000008[gTransferStep03000000 / gTransferDivisor03000005] + 0x0600C004;
        dma->control = 0x80000001;
        (void)dma->control;
        dma->source = (u32)&fill;
        dma->destination = gTransferOffsets03000008[gTransferStep03000000 / gTransferDivisor03000005] + 0x0600C008;
        dma->control = 0x80000001;
        (void)dma->control;
        dma->source = (u32)&fill;
        dma->destination = gTransferOffsets03000008[gTransferStep03000000 / gTransferDivisor03000005] + 0x0600C00C;
        dma->control = 0x80000001;
        (void)dma->control;
    }
    if (gTransferStep03000000 == gTransferDivisor03000005 << 4)
        return 1;
    return 0;
}

void sub_08069CC0(void) {

    s32 i;

    do {
    sub_08069BFC_Int(0, 0x2C, 0x22, 0, 4);
    sub_08069BFC_Int(1, -0x20, 0x22, 0, 4);
    sub_08069BFC_Int(2, -0x20, 0x22, 0, 4);
    i = 4;
    sub_08069BFC_Int(3, 0x2C, 0x3A, 0, i);
    i = 0;
    } while (0);
    sub_08069BFC_Int(4, -0x20, 0x3A, 0, 4);
    sub_08069BFC_Int(5, -0x20, 0x3A, 0, 4);
    sub_08069BFC_Int(6, 0x2C, 0x52, 0, 4);
    sub_08069BFC_Int(7, -0x20, 0x52, 0, 4);
    sub_08069BFC_Int(8, -0x20, 0x52, 0, 4);
    for (i = 0; i <= 8; i++)
        sub_08048864(i + 0x14, 0xCC00, 0x110, 0xD, 3);
    for (i = 0; i < 3; i++) {
        gFrameObjects[0x14 + i * 3].screenX = 0x2C;
        gFrameObjects[0x15 + i * 3].screenX = -0x20;
        gFrameObjects[0x16 + i * 3].screenX = -0x20;
        gFrameObjects[0x14 + i].screenY = 0x2D;
        gFrameObjects[0x17 + i].screenY = 0x45;
        gFrameObjects[0x1A + i].screenY = 0x5D;
    }
    {
        volatile struct Dma69CC0 *dma = (void *)0x040000D4;
        dma->source = (u32)&gUnknown_0850F498;
        dma->destination = 0x05000200;
        dma->control = 0x84000040;
        (void)dma->control;
    }
}
