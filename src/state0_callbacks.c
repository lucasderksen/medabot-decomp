#include "state0_callbacks.h"
#include "input.h"
#include "compression.h"
#include "bg_scroll.h"
#include "graphics.h"
#include "frame.h"
#include "interrupts.h"

void sub_080025B4(void)
{
    const u8 *held = (const u8 *)&gHeldKeys;
    const u8 *pressed;
    if (*held & KEY_UP)
        gBgScroll1.y++;
    if (*held & KEY_DOWN)
        gBgScroll1.y--;
    if (*held & KEY_LEFT)
        gBgScroll1.x++;
    if (*held & KEY_RIGHT)
        gBgScroll1.x--;
    pressed = (const u8 *)&gNewKeys;
    if (*pressed & KEY_B)
        gUnknown_03000440[0x88] ^= 1;
    if (*pressed & KEY_A)
    {
        gUnknown_03000440[0xE] = 0;
        gUnknown_0300137C++;
        gUnknown_03000440[0x85] ^= 1;
    }
    if (*pressed & KEY_B)
    {
        gMainSubstate = 1;
        gUnknown_0300137C = 0;
    }
    if (*pressed & KEY_START)
    {
        sub_0803FAA0(0, 0, 0);
        gUnknown_0300137C += 2;
    }
    if (*pressed & KEY_SELECT)
    {
        sub_0803FAA0(0, 0, 0);
        gUnknown_0300137C += 3;
    }
}

void sub_080026A4(void)
{
    if ((u8)sub_0803F51C(0, 1, 8, 4, gUnknown_03000440[0x88], gUnknown_03000440[0x85]) == 1)
        gUnknown_0300137C = 1;
}

void sub_080026E0(void)
{
    gUnknown_03002B70[4] = 0x17;
    gUnknown_03002B70[5] = 0x29;
    gUnknown_03002B70[6] = 0x2C;
    gUnknown_03002B70[7] = 0x25;
    gUnknown_03002B70[8] = 0;
    gUnknown_03002B70[9] = 0x2E;
    gUnknown_03002B70[10] = 0x1F;
    gUnknown_03002B70[11] = 0x2D;
    gUnknown_03002B70[12] = 0x2E;
    gUnknown_03002B70[13] = 0xFE;
    if ((u8)sub_0803FB3C(gUnknownPointers_083B5578[0]) == 1)
        gUnknown_0300137C = 1;
}

void sub_08002730(void)
{
    if (sub_0803FB3C(gUnknownPointers_083B5578[1]))
    {
        sub_080415E8(0, 0x16, 7);
        gUnknown_0300137C++;
    }
}

void sub_0800275C(void)
{
    if (sub_08041674())
    {
        sub_0803FB0C();
        gUnknown_0300137C++;
    }
}

void sub_0800277C(void)
{
    const void *data;
    if (gUnknown_03000440[0x28] & 0xF0)
        data = gUnknownPointers_083B5578[3];
    else
        data = gUnknownPointers_083B5578[2];
    if (sub_0803FB3C(data))
        gUnknown_0300137C = 1;
}

void sub_080027BC(void)
{
    gUnknownCallbacks_083AC404[gUnknown_0300137C]();
}

void sub_080027DC(void)
{
    *(volatile u16 *)0x04000000 = 0x1F60;
    *(volatile u16 *)0x04000008 = 0x0500;
    LeDecompress((const u8 *)0x084C1E24, (void *)0x06001800);
    LeDecompress((const u8 *)0x084C200C, (void *)0x06001B00);
    LeDecompress((const u8 *)0x084C2150, (void *)0x06001E00);
    LeDecompress((const u8 *)0x084C22E8, (void *)0x06002100);
    LeDecompress((const u8 *)0x084871A4, (void *)0x06002400);
    {
        volatile u32 *dma = (volatile u32 *)0x040000D4;
        dma[0] = 0x08488520;
        dma[1] = 0x050001E0;
        dma[2] = 0x80000010;
        (void)dma[2];
        LeDecompress((const u8 *)0x084C8034, (void *)0x06017400);
        dma[0] = 0x084E43D8;
        dma[1] = 0x050003E0;
        dma[2] = 0x80000010;
        (void)dma[2];
    }
    sub_08074B88(6);
    gUnknown_03000440[0x84] = 0;
    gUnknown_0300137C++;
}

void sub_080028AC(void)
{
    if (gUnknown_03000440[0x84] <= 12)
        sub_0803F15C(12, 2, 18, 1, gUnknownPointers_083B4C60[gUnknown_03000440[0x84] + 19], *(volatile u16 *)0x04000008, 0);
    if ((u8)(gUnknown_03000440[0x84] - 2) <= 12)
        sub_0803F15C(12, 2, 18, 3, gUnknownPointers_083B4C60[gUnknown_03000440[0x84] + 30], *(volatile u16 *)0x04000008, 0);
    if ((u8)(gUnknown_03000440[0x84] - 4) <= 12)
        sub_0803F15C(12, 2, 18, 5, gUnknownPointers_083B4C60[gUnknown_03000440[0x84] + 41], *(volatile u16 *)0x04000008, 0);
    if ((u8)(gUnknown_03000440[0x84] - 6) <= 12)
        sub_0803F15C(12, 2, 18, 7, gUnknownPointers_083B4C60[gUnknown_03000440[0x84] + 52], *(volatile u16 *)0x04000008, 0);
    if (gUnknown_03000440[0x84] == 10)
    {
        LeDecompress((const u8 *)0x084872B0, (void *)0x06002400);
        LoadLeTilemap(21, 9, (const u8 *)0x0848812C, *(volatile u16 *)0x04000008, 0x120);
    }
    if (gUnknown_03000440[0x84] == 12)
    {
        LeDecompress((const u8 *)0x084871A4, (void *)0x06002400);
        LoadLeTilemap(21, 9, (const u8 *)0x084880E0, *(volatile u16 *)0x04000008, 0x120);
    }
    gUnknown_03000440[0x84]++;
    if (gUnknown_03000440[0x84] > 18)
    {
        sub_08041164(gUnknown_03000440 + 0x9E, *(u32 *)gUnknown_03002B70);
        sub_08040DB8(gUnknown_03000440 + 0x9E, 10, 23, 10, 5, 15, 2, 0);
        gUnknown_03000440[0x8E] = 0;
        sub_08003300();
        gUnknown_0300137C++;
    }
}

void sub_08002A2C(void)
{
    const u8 *repeated;
    const u8 *pressed;
    sub_08040BD8(gUnknownPointers_083B6100[0], 0);
    repeated = (const u8 *)&gRepeatedKeys;
    if (*repeated & KEY_UP)
    {
        sub_08074DE0(2);
        gUnknown_03000440[0x8E] = (gUnknown_03000440[0x8E] - 1) & 3;
        gFrameObjects[0].screenY = (gUnknown_03000440[0x8E] << 4) + 8;
    }
    if (*repeated & KEY_DOWN)
    {
        sub_08074DE0(2);
        gUnknown_03000440[0x8E] = (gUnknown_03000440[0x8E] + 1) & 3;
        gFrameObjects[0].screenY = (gUnknown_03000440[0x8E] << 4) + 8;
    }
    pressed = (const u8 *)&gNewKeys;
    if (*pressed & KEY_B)
    {
        sub_080750F0(0x10);
        sub_08074DE0(5);
        sub_08040CD0(0, 1);
        sub_08040CD0(10, 7);
        gUnknown_03000440[0x84] = 0;
        gUnknown_0300137C = 3;
    }
    else if (*pressed & KEY_A)
    {
        sub_08074DE0(4);
        gUnknown_0300137C = 6;
    }
}

void sub_08002AF8(void)
{
    if (gUnknown_03000440[0x84] <= 12)
        sub_0803F15C(12, 2, 18, 1, gUnknownPointers_083B4C60[31 - gUnknown_03000440[0x84]], *(volatile u16 *)0x04000008, 0);
    if ((u8)(gUnknown_03000440[0x84] - 2) <= 12)
        sub_0803F15C(12, 2, 18, 3, gUnknownPointers_083B4C60[46 - gUnknown_03000440[0x84]], *(volatile u16 *)0x04000008, 0);
    if ((u8)(gUnknown_03000440[0x84] - 4) <= 12)
        sub_0803F15C(12, 2, 18, 5, gUnknownPointers_083B4C60[61 - gUnknown_03000440[0x84]], *(volatile u16 *)0x04000008, 0);
    if ((u8)(gUnknown_03000440[0x84] - 6) <= 12)
        sub_0803F15C(12, 2, 18, 7, gUnknownPointers_083B4C60[76 - gUnknown_03000440[0x84]], *(volatile u16 *)0x04000008, 0);
    if (gUnknown_03000440[0x84] == 10)
    {
        LeDecompress((const u8 *)0x084872B0, (void *)0x06002400);
        LoadLeTilemap(21, 9, (const u8 *)0x0848812C, *(volatile u16 *)0x04000008, 0x120);
    }
    if (gUnknown_03000440[0x84] == 12)
        sub_0803EF8C(9, 4, 21, 9, *(volatile u16 *)0x04000008, 0);
    gUnknown_03000440[0x84]++;
    if (gUnknown_03000440[0x84] > 18)
        sub_08044094();
}

void sub_08002C34(void)
{
    switch (gUnknown_03000440[0x8E])
    {
    case 0:
        sub_0803EF8C(13, 10, 17, 3, *(volatile u16 *)0x04000008, 0);
        gUnknown_03000440[0x88] = 1;
        break;
    case 1:
        sub_0803EF8C(13, 2, 17, 1, *(volatile u16 *)0x04000008, 0);
        sub_0803EF8C(13, 8, 17, 5, *(volatile u16 *)0x04000008, 0);
        gUnknown_03000440[0x88] = 3;
        break;
    case 2:
        sub_0803EF8C(13, 4, 17, 1, *(volatile u16 *)0x04000008, 0);
        sub_0803EF8C(13, 6, 17, 7, *(volatile u16 *)0x04000008, 0);
        gUnknown_03000440[0x88] = 5;
        break;
    default:
        sub_0803EF8C(13, 6, 17, 1, *(volatile u16 *)0x04000008, 0);
        sub_0803EF8C(13, 4, 17, 9, *(volatile u16 *)0x04000008, 0);
        gUnknown_03000440[0x88] = 7;
        break;
    }
    sub_08040CD0(0, 1);
    sub_08040CD0(10, 7);
    gUnknown_0300137C++;
}

void sub_08002D48(void)
{
    sub_0803F15C(12, 2, 18, gUnknown_03000440[0x88] - 1,
        gUnknownPointers_083B4C60[gUnknown_03000440[0x8E] * 13 + 31], *(volatile u16 *)0x04000008, 0);
    sub_0803EF8C(12, 1, 18, gUnknown_03000440[0x88] + 1, *(volatile u16 *)0x04000008, 0);
    gUnknown_03000440[0x88]--;
    if (gUnknown_03000440[0x88] == 0)
    {
        LeDecompress((const u8 *)0x084C2430, (void *)0x060017E0);
        SnapshotPalettes();
        gUnknown_03000440[0x84] = 0;
        if (gUnknown_03000440[0x8E] == 0)
            sub_080750F0(0x10);
        gUnknown_0300137C++;
    }
}

void sub_08002DF4(void)
{
    if (gUnknown_03000440[0x8E] != 2 && gUnknown_03000440[0x84] <= 16)
    {
        sub_0803F684(0, gUnknown_03000440[0x84] * 2, 0x1FFF);
        sub_0803F998(0, gUnknown_03000440[0x84] * 2, 0xFFFF);
        gUnknown_03000440[0x84]++;
    }
    sub_0803F15C(12, 2, 18 - gUnknown_03000440[0x88], 0,
        gUnknownPointers_083B4C60[gUnknown_03000440[0x8E] * 13 + 31], *(volatile u16 *)0x04000008, 0);
    sub_0803F15C(1, 2, 30 - gUnknown_03000440[0x88], 0,
        gUnknownPointers_083B4C60[71], *(volatile u16 *)0x04000008, 0);
    gUnknown_03000440[0x88]++;
    if (gUnknown_03000440[0x88] == 19)
        gUnknown_0300137C++;
}

void sub_08002EC4(void)
{
    switch (gUnknown_03000440[0x8E])
    {
    case 0:
        sub_08074B88(7);
        gUnknown_03000440[0x8F] = 0;
        gMainSubstate = 2;
        gUnknown_0300137C = 0;
        sub_08040CD0(40, 87);
        break;
    case 1:
        gMainState = 2;
        gMainSubstate = 4;
        gUnknown_0300137C = 0;
        sub_08040CD0(40, 87);
        break;
    case 2:
        sub_0804765C(1);
        break;
    default:
        gUnknown_03000588 = 0;
        gMainState = 2;
        gMainSubstate = 5;
        gUnknown_0300137C = 0;
        sub_08040CD0(40, 87);
        break;
    }
}

void sub_08002F70(void)
{
    gUnknown_03000588 = 1;
    if (gUnknown_03000440[0x8E] != 2)
    {
        *(volatile u16 *)0x04000000 &= 0xF1FF;
        {
            volatile u32 *dma = (volatile u32 *)0x040000D4;
            dma[0] = 0x084E43D8;
            dma[1] = 0x0202F9E0;
            dma[2] = 0x84000008;
            (void)dma[2];
        }
        sub_080480E4();
        sub_08048830();
        sub_080497E0(64, 0x2F00, 5, 16, 16, 16, 12, 10, 0);
        *(volatile u16 *)0x04000000 |= 0xF60;
    }
    gUnknown_03000440[0x88] = 18;
    gUnknown_03000440[0x84] = 0;
    gUnknown_0300137C++;
}

void sub_08003018(void)
{
    if (gUnknown_03000440[0x8E] != 2 && gUnknown_03000440[0x84] <= 16)
    {
        sub_08049A6C();
        sub_0803F684(0, 32 - gUnknown_03000440[0x84] * 2, 0x1FFF);
        sub_0803F998(0, 32 - gUnknown_03000440[0x84] * 2, 0xFFFF);
        gUnknown_03000440[0x84]++;
    }
    gUnknown_03000440[0x88]--;
    sub_0803F15C(12, 2, 18 - gUnknown_03000440[0x88], 0,
        gUnknownPointers_083B4C60[gUnknown_03000440[0x8E] * 13 + 31], *(volatile u16 *)0x04000008, 0);
    sub_0803EF8C(1, 2, 17 - gUnknown_03000440[0x88], 0, *(volatile u16 *)0x04000008, 0);
    if (gUnknown_03000440[0x88] == 0)
    {
        gUnknownCallback_030017F0 = DummyInterruptHandler;
        gUnknown_03000440[0x88] = gUnknown_03000440[0x8E] * 2 + 1;
        gUnknown_03000440[0x84] = 0;
        gUnknown_0300137C++;
    }
}

void sub_08003104(void)
{
    sub_0803F15C(12, 2, 18, gUnknown_03000440[0x84] + 1,
        gUnknownPointers_083B4C60[gUnknown_03000440[0x8E] * 13 + 31], *(volatile u16 *)0x04000008, 0);
    sub_0803EF8C(12, 1, 18, gUnknown_03000440[0x84], *(volatile u16 *)0x04000008, 0);
    if (gUnknown_03000440[0x84] + 1 == gUnknown_03000440[0x88])
    {
        switch (gUnknown_03000440[0x8E])
        {
        case 0:
            sub_0803F15C(12, 2, 18, 3, gUnknownPointers_083B4C60[44], *(volatile u16 *)0x04000008, 0);
            sub_0803F15C(12, 2, 18, 5, gUnknownPointers_083B4C60[57], *(volatile u16 *)0x04000008, 0);
            sub_0803F15C(12, 2, 18, 7, gUnknownPointers_083B4C60[70], *(volatile u16 *)0x04000008, 0);
            break;
        case 1:
            sub_0803F15C(12, 2, 18, 1, gUnknownPointers_083B4C60[31], *(volatile u16 *)0x04000008, 0);
            sub_0803F15C(12, 2, 18, 5, gUnknownPointers_083B4C60[57], *(volatile u16 *)0x04000008, 0);
            sub_0803F15C(12, 2, 18, 7, gUnknownPointers_083B4C60[70], *(volatile u16 *)0x04000008, 0);
            break;
        case 2:
            sub_0803F15C(12, 2, 18, 1, gUnknownPointers_083B4C60[31], *(volatile u16 *)0x04000008, 0);
            sub_0803F15C(12, 2, 18, 3, gUnknownPointers_083B4C60[44], *(volatile u16 *)0x04000008, 0);
            sub_0803F15C(12, 2, 18, 7, gUnknownPointers_083B4C60[70], *(volatile u16 *)0x04000008, 0);
            break;
        default:
            sub_0803F15C(12, 2, 18, 1, gUnknownPointers_083B4C60[31], *(volatile u16 *)0x04000008, 0);
            sub_0803F15C(12, 2, 18, 3, gUnknownPointers_083B4C60[44], *(volatile u16 *)0x04000008, 0);
            sub_0803F15C(12, 2, 18, 5, gUnknownPointers_083B4C60[57], *(volatile u16 *)0x04000008, 0);
            break;
        }
        LoadLeTilemap(21, 9, (const u8 *)0x084880E0, *(volatile u16 *)0x04000008, 0x120);
        sub_08041164(gUnknown_03000440 + 0x9E, *(u32 *)gUnknown_03002B70);
        sub_08040DB8(gUnknown_03000440 + 0x9E, 10, 23, 10, 5, 15, 2, 0);
        sub_08003300();
        gUnknown_0300137C = 2;
    }
    else
        gUnknown_03000440[0x84]++;
}

void sub_08003300(void)
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
    gFrameObjects[0].screenX = 0x88;
    gFrameObjects[0].screenY = (gUnknown_03000440[0x8E] << 4) + 8;
    gFrameObjects[0].palette = 14;
    gFrameObjects[0].tableSelector = 0;
    gFrameObjects[0].priority = 255;
    sub_08040B90(gUnknownPointers_083B6100[0], 0);
}
