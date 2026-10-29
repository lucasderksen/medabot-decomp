#include "main.h"
#include "state0_callbacks.h"
#include "input.h"
#include "compression.h"
#include "bg_scroll.h"
#include "graphics.h"
#include "frame.h"
#include "interrupts.h"

void sub_08003374(void)
{
    gUnknownCallbacks_083AC454[gUnknown_0300137C]();
}

void sub_08003394(void)
{
    sub_080415BC();
    *(volatile u16 *)0x04000000 &= 0xF1FF;
    *(volatile u16 *)0x0400000A = 0x1805;
    *(volatile u16 *)0x0400000C = 0x1906;
    *(volatile u16 *)0x0400000E = 0x1A07;
    LeDecompress((const u8 *)0x084E4678, (void *)0x06004000);
    sub_08003904();
    LoadLeTilemap(0, 0, (const u8 *)0x084F0C40, *(volatile u16 *)0x0400000A, 0);
    LoadLeTilemap(0, 0, (const u8 *)0x084F17DC, *(volatile u16 *)0x0400000C, 0);
    LoadLeTilemap(0, 0, (const u8 *)0x084F24CC, *(volatile u16 *)0x0400000E, 0);
    {
        volatile u32 *dma = (volatile u32 *)0x040000D4;
        dma[0] = 0x084F3A80;
        dma[1] = 0x0202FA00;
        dma[2] = 0x84000060;
        (void)dma[2];
    }
    sub_0803F15C(4, 4, 5, 9, gUnknownPointers_083B4C60[72], *(volatile u16 *)0x0400000A, 0);
    *(volatile u16 *)0x04000000 |= 0x1F60;
    gUnknown_03000440[0x84] = 0;
    gUnknown_0300137C++;
}

void sub_080034A4(void)
{
    sub_080039BC();
    if (gUnknown_03000440[0x84] <= 8)
    {
        sub_0803F684(0, 32 - gUnknown_03000440[0x84] * 4, 0x1FFF);
        sub_0803F998(0, 32 - gUnknown_03000440[0x84] * 4, 0xFFFF);
        gUnknown_03000440[0x84]++;
    }
    else
    {
        sub_0800393C();
        gUnknown_0300137C++;
    }
}

void sub_08003504(void)
{
    const u8 *pressed;
    sub_080039BC();
    sub_08040BD8(gUnknownPointers_083B6100[0], 0);
    if (*(const u8 *)&gRepeatedKeys & KEY_UP)
    {
        if (gUnknown_03000440[0x8F] == 0)
            gUnknown_03000440[0x8F] = 2;
        else
            gUnknown_03000440[0x8F]--;
        sub_08074DE0(2);
        sub_08003904();
        gFrameObjects[0].screenX = 136 - gUnknown_03000440[0x8F] * 8;
        gFrameObjects[0].screenY = gUnknown_03000440[0x8F] * 24 + 32;
    }
    if (*(const u8 *)&gRepeatedKeys & KEY_DOWN)
    {
        if (gUnknown_03000440[0x8F] == 2)
            gUnknown_03000440[0x8F] = 0;
        else
            gUnknown_03000440[0x8F]++;
        sub_08074DE0(2);
        sub_08003904();
        gFrameObjects[0].screenX = 136 - gUnknown_03000440[0x8F] * 8;
        gFrameObjects[0].screenY = gUnknown_03000440[0x8F] * 24 + 32;
    }
    pressed = (const u8 *)&gNewKeys;
    if (*pressed & KEY_B)
    {
        sub_08074DE0(5);
        gUnknown_0300137C++;
    }
    if (*pressed & KEY_A)
    {
        sub_08074DE0(4);
        sub_08040B90(gUnknownPointers_083B6100[1], 0);
        sub_0804253C(6, 63, 32);
        gUnknown_03000440[0x84] = 0;
        gUnknown_0300137C = 8;
    }
}

void sub_08003620(void)
{
    sub_080039BC();
    sub_08040CD0(0, 1);
    SnapshotPalettes();
    gUnknown_03000440[0x84] = 0;
    sub_080750F0(8);
    gUnknown_0300137C++;
}

void sub_08003654(void)
{
    sub_080039BC();
    if (gUnknown_03000440[0x84] <= 8)
    {
        sub_0803F684(0, gUnknown_03000440[0x84] * 4, 0x1FFF);
        sub_0803F998(0, gUnknown_03000440[0x84] * 4, 0xFFFF);
        gUnknown_03000440[0x84]++;
    }
    else
        gUnknown_0300137C++;
}

void sub_080036A8(void)
{
    sub_08074B88(6);
    gMainSubstate = 1;
    gUnknown_0300137C = 16;
}

void sub_080036C8(void)
{
    sub_080039BC();
    sub_08040BD8(gUnknownPointers_083B6100[1], 0);
    if (sub_080425DC())
        gUnknown_0300137C++;
}

void sub_080036F4(void)
{
    volatile u32 *dma = (volatile u32 *)0x040000D4;
    dma[0] = 0x06002800;
    dma[1] = 0x02020800;
    dma[2] = 0x84000200;
    (void)dma[2];
    switch (gUnknown_03000440[0x8F])
    {
    case 0:
        sub_0803F624(gUnknown_03000440 + 0x50, 20, 0);
        gMainSubstate = 3;
        gUnknown_0300137C = 0;
        break;
    case 1:
        sub_0803F624(gUnknown_03000440 + 0x3C, 20, 0);
        gMainSubstate = 4;
        gUnknown_0300137C = 0;
        break;
    default:
        sub_0803F624(gUnknown_03000440 + 0x3C, 20, 0);
        gMainSubstate = 5;
        gUnknown_0300137C = 0;
        break;
    }
}

void sub_08003784(void)
{
    volatile u32 *dma;
    sub_080415BC();
    *(volatile u16 *)0x04000000 &= 0xF0FF;
    *(volatile u16 *)0x0400000A = 0x0500;
    *(volatile u16 *)0x0400000A = 0x1805;
    *(volatile u16 *)0x0400000C = 0x1906;
    *(volatile u16 *)0x0400000E = 0x1A07;
    LeDecompress((const u8 *)0x084E4678, (void *)0x06004000);
    sub_08003904();
    dma = (volatile u32 *)0x040000D4;
    dma[0] = 0x02020800;
    dma[1] = 0x06002800;
    dma[2] = 0x84000200;
    (void)dma[2];
    LoadLeTilemap(0, 0, (const u8 *)0x084F0C40, *(volatile u16 *)0x0400000A, 0);
    LoadLeTilemap(0, 0, (const u8 *)0x084F17DC, *(volatile u16 *)0x0400000C, 0);
    LoadLeTilemap(0, 0, (const u8 *)0x084F24CC, *(volatile u16 *)0x0400000E, 0);
    dma[0] = 0x084F3A80;
    dma[1] = 0x05000000;
    dma[2] = 0x84000060;
    (void)dma[2];
    sub_0803F15C(4, 4, 5, 9, gUnknownPointers_083B4C60[72], *(volatile u16 *)0x0400000A, 0);
    *(volatile u16 *)0x04000000 |= 0x1F60;
    sub_0804253C(5, 63, 32);
    gUnknown_03000440[0x84] = 0;
    gUnknown_0300137C++;
}

void sub_080038CC(void)
{
    sub_080039BC();
    if (sub_080425DC())
    {
        sub_0800393C();
        gUnknown_0300137C++;
    }
}

void sub_080038F0(void)
{
    sub_080039BC();
    gUnknown_0300137C = 2;
}

void sub_08003904(void)
{
    const u8 *source;
    switch (gUnknown_03000440[0x8F])
    {
    case 0:
        source = (const u8 *)0x084C2440;
        break;
    case 1:
        source = (const u8 *)0x084C2620;
        break;
    default:
        source = (const u8 *)0x084C27F0;
        break;
    }
    LeDecompress(source, (void *)0x06007E00);
}

void sub_0800393C(void)
{
    LeDecompress((const u8 *)0x084C8714, (void *)0x06016C00);
    {
        volatile u32 *dma = (volatile u32 *)0x040000D4;
        dma[0] = 0x084E43F8;
        dma[1] = 0x050003C0;
        dma[2] = 0x84000008;
        (void)dma[2];
    }
    gFrameObjects[0].flags = 0xC004;
    gFrameObjects[0].screenX = 136 - gUnknown_03000440[0x8F] * 8;
    gFrameObjects[0].screenY = gUnknown_03000440[0x8F] * 24 + 32;
    gFrameObjects[0].palette = 14;
    gFrameObjects[0].tableSelector = 0;
    gFrameObjects[0].priority = 255;
    sub_08040B90(gUnknownPointers_083B6100[0], 0);
}

void sub_080039BC(void)
{
    if (gFrameCounter & 1)
    {
        gBgScroll3.x--;
        gBgScroll3.y++;
    }
}
