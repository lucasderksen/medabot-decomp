/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "frame.h"
#include "object_numeric_helpers.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Dma70D74 {const void *volatile source;void *volatile destination;volatile u32 control;};
struct Graphics70D74 {u8 pad00[0xC];u8 first;u8 second;};
struct FrameWork70D74 {u8 pad00[0x42];s16 x1;s16 y1;u8 pad46[5];u8 priority1;u8 pad4C[0x36];s16 x2;s16 y2;u8 pad86[5];u8 priority2;u8 pad8C[0x36];s16 x3;s16 y3;u8 padC6[5];u8 priority3;u8 padCC[0x36];s16 x4;s16 y4;u8 pad106[5];u8 priority4;u8 pad10C[0x36];s16 x5;s16 y5;u8 pad146[5];u8 priority5;u8 pad14C[0x36];s16 x6;s16 y6;u8 pad186[5];u8 priority6;u8 pad18C[0x36];s16 x7;s16 y7;u8 pad1C6[5];u8 priority7;u8 pad1CC[0x36];s16 x8;s16 y8;u8 pad206[5];u8 priority8;u8 pad20C[0x36];s16 x9;s16 y9;u8 pad246[5];u8 priority9;};

extern const u8 gPalette087C5FF0[192];
extern const u8 gPaletteAnchor0807C870[32];
extern struct Graphics70D74 gGraphicsWork70D7403001800;
extern void sub_08068460(u8,u8,u16);

void sub_08070D74(void);

void sub_08070D74(void) {
    struct Dma70D74 *dma=(struct Dma70D74 *)0x040000D4;

    dma->source = gPalette087C5FF0;
    dma->destination = (void *)0x05000000;
    dma->control = 0x84000030;
    (void)dma->control;
    dma->source = gPaletteAnchor0807C870;
    dma->destination = (void *)0x05000200;
    dma->control = 0x80000010;
    (void)dma->control;
    dma->source = (const void *)((u32)gPaletteAnchor0807C870 - 0x40);
    dma->destination = (void *)0x05000220;
    dma->control = 0x80000010;
    (void)dma->control;
    dma->source = (const void *)((u32)gPaletteAnchor0807C870 - 0xC0);
    dma->destination = (void *)0x05000300;
    dma->control = 0x80000040;
    (void)dma->control;
    dma->source = (const void *)((u32)gPaletteAnchor0807C870 - 0x140);
    dma->destination = (void *)0x05000380;
    dma->control = 0x80000040;
    (void)dma->control;
    *(volatile u16 *)0x0400000A=0x1509;
    *(volatile u16 *)0x0400000C=0x160A;
    *(volatile u16 *)0x0400000E=0x170B;
    *(volatile u16 *)0x04000050=0x1C42;
    *(volatile u16 *)0x04000052=0x80A;
    sub_08048864(6U, 0xC800U, 0x508U, 8U, 3U);
    ((struct FrameWork70D74 *)gFrameObjects)->x6 = 0x40;
    ((struct FrameWork70D74 *)gFrameObjects)->y6 = 0x42;
    ((struct FrameWork70D74 *)gFrameObjects)->priority6 = 0x24;
    sub_08048864(7U, 0xC800U, 0x509U, 8U, 3U);
    ((struct FrameWork70D74 *)gFrameObjects)->x7 = 0x38;
    ((struct FrameWork70D74 *)gFrameObjects)->y7 = 0x3A;
    ((struct FrameWork70D74 *)gFrameObjects)->priority7 = 0x28;
    sub_08048864(8U, 0xC800U, 0x50AU, 8U, 3U);
    ((struct FrameWork70D74 *)gFrameObjects)->x8 = 0x44;
    ((struct FrameWork70D74 *)gFrameObjects)->y8 = 0x3A;
    ((struct FrameWork70D74 *)gFrameObjects)->priority8 = 0x1C;
    sub_08048864(9U, 0xC800U, 0x50BU, 8U, 3U);
    ((struct FrameWork70D74 *)gFrameObjects)->x9 = 0x40;
    ((struct FrameWork70D74 *)gFrameObjects)->y9 = 0x42;
    ((struct FrameWork70D74 *)gFrameObjects)->priority9 = 0x20;
    sub_08048864(2U, 0xC800U, 0x504U, 8U, 3U);
    ((struct FrameWork70D74 *)gFrameObjects)->x2 = 0x50;
    ((struct FrameWork70D74 *)gFrameObjects)->y2 = -0x30;
    ((struct FrameWork70D74 *)gFrameObjects)->priority2 = 0x25;
    sub_08048864(1U, 0xC800U, 0x50DU, 1U, 3U);
    ((struct FrameWork70D74 *)gFrameObjects)->x1 = 0x50;
    ((struct FrameWork70D74 *)gFrameObjects)->y1 = -0x30;
    ((struct FrameWork70D74 *)gFrameObjects)->priority1 = 0x30;
    sub_08048864(3U, 0xC800U, 0x505U, 8U, 3U);
    ((struct FrameWork70D74 *)gFrameObjects)->x3 = 0x28;
    ((struct FrameWork70D74 *)gFrameObjects)->y3 = -0x30;
    ((struct FrameWork70D74 *)gFrameObjects)->priority3 = 0x29;
    sub_08048864(4U, 0xC800U, 0x506U, 8U, 3U);
    ((struct FrameWork70D74 *)gFrameObjects)->x4 = 0x54;
    ((struct FrameWork70D74 *)gFrameObjects)->y4 = -0x30;
    ((struct FrameWork70D74 *)gFrameObjects)->priority4 = 0x1D;
    sub_08048864(5U, 0xC800U, 0x507U, 8U, 3U);
    ((struct FrameWork70D74 *)gFrameObjects)->x5 = 0x50;
    ((struct FrameWork70D74 *)gFrameObjects)->y5 = -0x30;
    ((struct FrameWork70D74 *)gFrameObjects)->priority5 = 0x29;
    gGraphicsWork70D7403001800.first = 1;
    gGraphicsWork70D7403001800.second = 0;
    sub_08068460(4, 2, 0);
    *(volatile u16 *)0x04000000 |= 0x1E00;
    gUnknown_0300137C = 1;
}
