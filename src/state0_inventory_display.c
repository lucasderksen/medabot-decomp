#include "state0_callbacks.h"
#include "state0_work.h"
#include "state0_display.h"
#include "display_helpers.h"

#include "state0_inventory.h"

void sub_08005AD0(void)
{
    u8 *work;
    sub_08040D0C(10, 10);
    work = gState0TypedWork.bytes;
    if (work[0x97] <= 29)
        sub_08040DB8(gInventoryNames[work[0x97]], 10, 1, 13, 10, 15, 0, 2);
    else
    {
        sub_08042678(work + 0x9E, 10);
        sub_08040DB8(work + 0x9E, 10, 1, 13, 10, 15, 0, 2);
    }
}

void sub_08005B44(void)
{
    u8 *work = gState0TypedWork.bytes;
    if (work[0x97] <= 29)
        CpuFastSet(gUnknownBytes_084C29D8 + gInventoryRecords[work[0x97]].byte1 * 128, (void *)0x06007800, 32);
    else
        CpuFastSet(gUnknownBytes_084C38D8, (void *)0x06007800, 32);
    sub_08042698(2, 2, 16, 9, *(volatile u16 *)0x0400000A, 0x63C0);
}

void sub_08005BB4(void)
{
    u8 *work = gState0TypedWork.bytes;
    if (work[0x97] <= 29)
        sub_080426F0(gInventoryRecords[work[0x97]].byte5, 26, 9, *(volatile u16 *)0x0400000A, 0xD3A4);
    else
        sub_080426F0(255, 26, 9, *(volatile u16 *)0x0400000A, 0xD3A4);
}

void sub_08005C10(void)
{
    u8 *work;
    sub_08040D0C(20, 10);
    work = gState0TypedWork.bytes;
    if (work[0x97] <= 29)
    {
        sub_0803F63C(gUnknownPointers_083B6590[gInventoryRecords[work[0x97]].byte1], work + 0x9E, 11);
        sub_08040DB8(work + 0x9E, 20, 18, 9, 7, 12, 1, 2);
    }
    else
    {
        sub_08042678(work + 0x9E, 9);
        sub_08040DB8(work + 0x9E, 20, 18, 9, 7, 12, 1, 2);
    }
}

void sub_08005C9C(void)
{
    u8 *work;
    sub_08040D0C(30, 14);
    work = gState0TypedWork.bytes;
    if (work[0x98] <= 119)
    {
        sub_08041D04(gPartTextPointers_083BBB4C[work[0x98] * 4 + 0], work + 0x9E, 15);
        sub_08040DB8(work + 0x9E, 30, 18, 11, 10, 13, 1, 2);
    }
    else
    {
        sub_08042678(work + 0x9E, 13);
        sub_08040DB8(work + 0x9E, 30, 18, 11, 10, 13, 1, 2);
    }
}

void sub_08005D1C(void)
{
    u8 *work = gState0TypedWork.bytes;
    if (work[0x98] <= 119)
    {
        if (work[0x97] <= 29)
        {
            sub_08042B58(work[0x98], 0, work + 0xEE);
            sub_08041D04(gInventoryMetadata_083B62D8 + gInventoryRecords[work[0x97]].byte1 * 16, work + 0x10E, 16);
            if (work[0xEE] == work[0x10F])
                sub_08042698(2, 2, 16, 11, *(volatile u16 *)0x0400000A, ((u32)work[0x115] * 0x40000 + 0xD3400000) >> 16);
            else
                sub_08042698(2, 2, 16, 11, *(volatile u16 *)0x0400000A, 0xD340);
        }
        else
            sub_0803EF8C(2, 2, 16, 11, *(volatile u16 *)0x0400000A, 0);
    }
    else
        sub_0803EF8C(2, 2, 16, 11, *(volatile u16 *)0x0400000A, 0);
}

void sub_08005E00(void)
{
    u8 *work;
    sub_08040D0C(44, 14);
    work = gState0TypedWork.bytes;
    if (work[0x99] <= 119)
    {
        sub_08041D04(gPartTextPointers_083BBB4C[work[0x99] * 4 + 1], work + 0x9E, 15);
        sub_08040DB8(work + 0x9E, 44, 18, 13, 10, 13, 1, 2);
    }
    else
    {
        sub_08042678(work + 0x9E, 13);
        sub_08040DB8(work + 0x9E, 44, 18, 13, 10, 13, 1, 2);
    }
}

void sub_08005E84(void)
{
    u8 *work = gState0TypedWork.bytes;
    if (work[0x99] <= 119)
    {
        if (work[0x97] <= 29)
        {
            sub_08042B58(work[0x99], 1, work + 0xEE);
            sub_08041D04(gInventoryMetadata_083B62D8 + gInventoryRecords[work[0x97]].byte1 * 16, work + 0x10E, 16);
            if (work[0xEE] == work[0x10F])
                sub_08042698(2, 2, 16, 13, *(volatile u16 *)0x0400000A, ((u32)work[0x115] * 0x40000 + 0xD3400000) >> 16);
            else
                sub_08042698(2, 2, 16, 13, *(volatile u16 *)0x0400000A, 0xD340);
        }
        else
            sub_0803EF8C(2, 2, 16, 13, *(volatile u16 *)0x0400000A, 0);
    }
    else
        sub_0803EF8C(2, 2, 16, 13, *(volatile u16 *)0x0400000A, 0);
}

void sub_08005F68(void)
{
    u8 *work;
    sub_08040D0C(58, 14);
    work = gState0TypedWork.bytes;
    if (work[0x9a] <= 119)
    {
        sub_08041D04(gPartTextPointers_083BBB4C[work[0x9a] * 4 + 2], work + 0x9E, 15);
        sub_08040DB8(work + 0x9E, 58, 18, 15, 10, 13, 1, 2);
    }
    else
    {
        sub_08042678(work + 0x9E, 13);
        sub_08040DB8(work + 0x9E, 58, 18, 15, 10, 13, 1, 2);
    }
}

void sub_08005FEC(void)
{
    u8 *work = gState0TypedWork.bytes;
    if (work[0x9a] <= 119)
    {
        if (work[0x97] <= 29)
        {
            sub_08042B58(work[0x9a], 2, work + 0xEE);
            sub_08041D04(gInventoryMetadata_083B62D8 + gInventoryRecords[work[0x97]].byte1 * 16, work + 0x10E, 16);
            if (work[0xEE] == work[0x10F])
                sub_08042698(2, 2, 16, 15, *(volatile u16 *)0x0400000A, ((u32)work[0x115] * 0x40000 + 0xD3400000) >> 16);
            else
                sub_08042698(2, 2, 16, 15, *(volatile u16 *)0x0400000A, 0xD340);
        }
        else
            sub_0803EF8C(2, 2, 16, 15, *(volatile u16 *)0x0400000A, 0);
    }
    else
        sub_0803EF8C(2, 2, 16, 15, *(volatile u16 *)0x0400000A, 0);
}

void sub_080060D0(void)
{
    u8 *work;
    sub_08040D0C(72, 14);
    work = gState0TypedWork.bytes;
    if (work[0x9b] <= 119)
    {
        sub_08041D04(gPartTextPointers_083BBB4C[work[0x9b] * 4 + 3], work + 0x9E, 15);
        sub_08040DB8(work + 0x9E, 72, 18, 17, 10, 13, 1, 2);
    }
    else
    {
        sub_08042678(work + 0x9E, 13);
        sub_08040DB8(work + 0x9E, 72, 18, 17, 10, 13, 1, 2);
    }
}

void sub_08006154(void)
{
    u8 *work = gState0TypedWork.bytes;
    if (work[0x9b] <= 119)
    {
        if (work[0x97] <= 29)
        {
            sub_08042B58(work[0x9b], 3, work + 0xEE);
            sub_08041D04(gInventoryMetadata_083B62D8 + gInventoryRecords[work[0x97]].byte1 * 16, work + 0x10E, 16);
            if (work[0xEE] == work[0x10F])
                sub_08042698(2, 2, 16, 17, *(volatile u16 *)0x0400000A, ((u32)work[0x115] * 0x40000 + 0xD3400000) >> 16);
            else
                sub_08042698(2, 2, 16, 17, *(volatile u16 *)0x0400000A, 0xD340);
        }
        else
            sub_0803EF8C(2, 2, 16, 17, *(volatile u16 *)0x0400000A, 0);
    }
    else
        sub_0803EF8C(2, 2, 16, 17, *(volatile u16 *)0x0400000A, 0);
}


#include "state0_callbacks.h"
#include "state0_work.h"
#include "state0_display.h"
#include "state0_inventory.h"

void sub_080059D0(void)
{
    struct State0Record8 *base = gUnknownRecords_030017A0;
    u8 *work = gState0TypedWork.bytes;
    struct State0Record8 *record = &base[work[0x51]];
    if (record->unknown00[2] == 30)
        work[0x97] = 30;
    else {
        u32 mapped = sub_08041D3C(record->unknown00[2]);
        mapped--;
        work[0x97] = mapped;
    }
    gState0TypedWork.bytes[0x98] = gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].byte3;
    gState0TypedWork.bytes[0x99] = gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].byte4;
    gState0TypedWork.bytes[0x9A] = gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].byte5;
    gState0TypedWork.bytes[0x9B] = gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].byte6;
    if (gState0TypedWork.bytes[0x97] != 30)
        gInventoryRecords[gState0TypedWork.bytes[0x97]].byte0 &= 0xBF;
    gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].unknown00[0] = 1;
    if (gState0TypedWork.bytes[0x98] <= 119) sub_08043560(gState0TypedWork.bytes[0x98], 0, 1, 1, 1);
    if (gState0TypedWork.bytes[0x99] <= 119) sub_08043560(gState0TypedWork.bytes[0x99], 1, 1, 1, 1);
    if (gState0TypedWork.bytes[0x9A] <= 119) sub_08043560(gState0TypedWork.bytes[0x9A], 2, 1, 1, 1);
    if (gState0TypedWork.bytes[0x9B] <= 119) sub_08043560(gState0TypedWork.bytes[0x9B], 3, 1, 1, 1);
}



#include "state0_callbacks.h"
#include "state0_work.h"
#include "state0_display.h"
#include "state0_inventory.h"
#include "display_helpers.h"
#include "frame.h"
#include "main.h"

void sub_0804305C(u32,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32);

void sub_08006238(u32 selected)
{
    if (!selected)
        sub_08042698(2, 2, 14, 9, *(volatile u16 *)0x0400000A, 0xC370);
    else
        sub_08042698(2, 2, 14, 9, *(volatile u16 *)0x0400000A, 0xC384);
}

void sub_08006284(u32 selected)
{
    if (!selected)
        sub_08042698(2, 2, 14, 11, *(volatile u16 *)0x0400000A, 0xC374);
    else
        sub_08042698(2, 2, 14, 11, *(volatile u16 *)0x0400000A, 0xC388);
}

void sub_080062D0(u32 selected)
{
    if (!selected)
        sub_08042698(2, 2, 14, 13, *(volatile u16 *)0x0400000A, 0xC378);
    else
        sub_08042698(2, 2, 14, 13, *(volatile u16 *)0x0400000A, 0xC388);
}

void sub_0800631C(u32 selected)
{
    if (!selected)
        sub_08042698(2, 2, 14, 15, *(volatile u16 *)0x0400000A, 0xC37C);
    else
        sub_08042698(2, 2, 14, 15, *(volatile u16 *)0x0400000A, 0xC388);
}

void sub_08006368(u32 selected)
{
    if (!selected)
        sub_08042698(2, 2, 14, 17, *(volatile u16 *)0x0400000A, 0xC380);
    else
        sub_08042698(2, 2, 14, 17, *(volatile u16 *)0x0400000A, 0xC388);
}

void sub_080063B4(void)
{
    u8 *work = gState0TypedWork.bytes;
    if (work[0x9B] <= 119) {
        sub_08042B58(work[0x9B], 3, work + 0xEE);
        sub_080435B0(work[0xEF] - 100, 20, 6, *(volatile u16 *)0x0400000A, 0x8300);
    } else {
        sub_080435B0(255, 20, 6, *(volatile u16 *)0x0400000A, 0x8300);
    }
}

void sub_08006414(void)
{
    u8 *work = gState0TypedWork.bytes;
    sub_08042D94(work[0x98], work[0x99], work[0x9A], work[0x9B], 0);
}

void sub_08006444(void)
{
    u8 *work = gState0TypedWork.bytes;
    sub_0804305C(work[0x98], work[0x99], work[0x9A], work[0x9B], 0, 6, 168, 32, work[0x5E], 1, 5);
}

void sub_08006494(void)
{
    gFrameObjects[1].flags = 0xC804;
    gFrameObjects[1].screenX = 108;
    gFrameObjects[1].screenY = gState0TypedWork.bytes[0x5A] * 16 + 80;
    gFrameObjects[1].frameAndGroup = 0x0302;
    gFrameObjects[1].palette = 14;
    gFrameObjects[1].tableSelector = 0;
    gFrameObjects[1].priority = 64;
    gFrameObjects[2].flags = 0xC804;
    gFrameObjects[2].screenX = 228;
    gFrameObjects[2].screenY = gState0TypedWork.bytes[0x5A] * 16 + 80;
    gFrameObjects[2].frameAndGroup = 0x0303;
    gFrameObjects[2].palette = 14;
    gFrameObjects[2].tableSelector = 0;
    gFrameObjects[2].priority = 64;
}

void sub_08006514(void)
{
    if (gFrameCounter & 8) {
        gFrameObjects[1].flags &= 0xBFFF;
        gFrameObjects[2].flags &= 0xBFFF;
    } else {
        gFrameObjects[1].flags |= 0x4000;
        gFrameObjects[2].flags |= 0x4000;
    }
}
