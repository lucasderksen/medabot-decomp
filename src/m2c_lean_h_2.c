/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "frame_objects.h"
#include "object_helpers.h"
#include "main_callbacks.h"
#include "record_helpers.h"

struct Main2TileContext60DD4 { u8 pad00[0x36]; s16 tile36; s16 tile38; };
/* Constant addresses: symbol operands would put pool words into .rodata
   under -fno-expensive-optimizations. */
#define CONTEXT (*(struct Main2TileContext60DD4 **)0x03006F74)
#define SCRATCH ((void *)0x02030000)

void sub_08060DD4(void);

void sub_08060DD4(void)
{
    s32 zero;
    u32 vram;
    u32 size;
    u32 size2;
    u32 total;
    u32 block;
    u32 dest;
    u32 mask;

    zero = 0;
    vram = 0x06000000;
    CpuFastSet(&zero, (void *)vram, 0x01006000);
    sub_080415BC();
    sub_08040CD0(0, 0x80);
    *(volatile u16 *)0x04000000 = 0x60;
    *(volatile u16 *)0x04000050 = 0xC42;
    *(volatile u16 *)0x04000052 = 0x10;
    {
        volatile u16 *bg;
        s32 v;
        bg = (volatile u16 *)0x0400000A;
        v = 0x1B05;
        *bg = v;
    }
    sub_0805BA34((const void *)0x0879AA2C, *(volatile u16 *)0x0400000A);
    {
        volatile u16 *bg;
        s32 v;
        bg = (volatile u16 *)0x0400000C;
        v = 0x1A06;
        *bg = v;
    }
    sub_0805BA34((const void *)0x0879ABE0, *(volatile u16 *)0x0400000C);
    {
        s32 v;
        *(volatile u16 *)0x0400000A = v = 0x1E05;
        *(volatile u16 *)0x0400000C = v = 0x1D06;
        *(volatile u16 *)0x0400000E = v = 0x1C07;
    }
    sub_0805BA34((const void *)0x087997FC, *(volatile u16 *)0x0400000A);
    sub_0805BA34((const void *)0x08799A18, *(volatile u16 *)0x0400000C);
    sub_0805BA34((const void *)0x08799C28, *(volatile u16 *)0x0400000E);
    size = sub_08044D0C((const void *)0x08797B10, SCRATCH);
    {
        u32 half, chars;
        chars = 0x4000;
        chars += vram;
        half = size >> 1;
        mask = 0x1FFFFF;
        CpuSet(SCRATCH, (void *)chars, half & mask);
    }
    size2 = LeDecompress((const u8 *)0x084C55CC, (void *)(size + 0x06004000));
    CONTEXT->tile38 = (size >> 5) - 1;
    total = size + size2;
    block = total >> 5;
    sub_0805BAA0(block, 0, 0x1B);
    sub_0805BAA0(block, 0, 0x1A);
    size2 = sub_08044D0C((const void *)0x0879A120, SCRATCH);
    dest = total + 0x06004000;
    CpuSet(SCRATCH, (void *)dest, (size2 >> 1) & mask);
    CONTEXT->tile36 = ((total + size2) >> 5) - 1;
    LeDecompress((const u8 *)0x08785EC0, (void *)(dest + size2));
    LeDecompress((const u8 *)0x08785FB4, (void *)0x06010000);
    LeDecompress((const u8 *)0x084C8034, (void *)0x06017400);
    LeDecompress((const u8 *)0x084C88B8, (void *)0x06017E00);
    (*(u32 *)0x0300137C)++;
}
