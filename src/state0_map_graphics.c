#include "state0_next_helpers.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "equipment_helpers.h"
#include "compression.h"
#include "graphics.h"


void sub_0801058C(void)
{
    volatile u32 *dma;
    sub_08043CA8();
    *(volatile u16 *)0x04000000 &= 0xE0FF;
    *(volatile u16 *)0x04000008 = 0x500;
    *(volatile u16 *)0x0400000A = 0x1801;
    *(volatile u16 *)0x0400000C = 0x590A;
    *(volatile u16 *)0x0400000E = 0x5B0B;
    LeDecompress((const u8 *)0x084E823C, (void *)0x06004000);
    LeDecompress((const u8 *)0x084C50D0, (void *)0x06006000);
    LeDecompress((const u8 *)0x084C5250, (void *)0x06006200);
    LeDecompress((const u8 *)0x084C92B0, (void *)0x06012800);
    LeDecompress((const u8 *)0x084C8034, (void *)0x06017400);
    sub_0803EF8C(32, 32, 0, 0, *(volatile u16 *)0x04000008, 0);
    sub_0803EF8C(32, 32, 0, 0, *(volatile u16 *)0x0400000A, 0);
    LoadLeTilemap(0, 0, (const u8 *)0x084F0FD4, *(volatile u16 *)0x0400000A, 512);
    dma = (volatile u32 *)0x040000D4;
    dma[0] = 0x084F3F80;
    dma[1] = 0x0202FA00;
    dma[2] = 0x84000070;
    (void)dma[2];
    dma[0] = 0x084C7F74;
    dma[1] = 0x0202FB00;
    dma[2] = 0x84000008;
    (void)dma[2];
    dma[0] = 0x084C7F94;
    dma[1] = 0x0202FB20;
    dma[2] = 0x84000008;
    (void)dma[2];
    dma[0] = 0x0850F498;
    dma[1] = 0x0202F800;
    dma[2] = 0x84000040;
    (void)dma[2];
    {
        u32 source = 0x0850F3F8;
        dma[0] = source;
        dma[1] = 0x0202F980;
        dma[2] = 0x84000008;
        (void)dma[2];
        source -= 0x160;
        dma[0] = source;
        dma[1] = 0x0202F9A0;
        dma[2] = 0x84000008;
        (void)dma[2];
    }
    dma[0] = 0x084E4558;
    dma[1] = 0x0202F940;
    dma[2] = 0x84000008;
    (void)dma[2];
    dma[0] = 0x084E4538;
    dma[1] = 0x0202F960;
    dma[2] = 0x84000008;
    (void)dma[2];
    sub_08043B7C(gState0TransferWork.bytes[0x38], 1);
    {
        u32 zero = 0;
        dma[0] = (u32)&zero;
        dma[1] = (u32)gFrameObjects;
        dma[2] = 0x85000800;
        (void)dma[2];
    }
    *(volatile u16 *)0x04000000 |= 0x1F60;
    sub_08011F50();
    sub_08011FA0();
    sub_08011FEC();
    sub_08012024();
    sub_080120C8();
    sub_0801214C();
    sub_080121A8();
    sub_08043DF8();
    gUnknown_03000440[0x84] = 0;
    gUnknown_0300137C++;
}
