#include "object_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "graphics.h"
#include "compression.h"
#include "bg_scroll.h"
#include "display_helpers.h"
#include "state0_work.h"
#include "state0_inventory.h"

extern u8 gUnknown_03000440[];

void sub_080415BC(void)
{
    gBgScroll0.x = 0;
    gBgScroll0.y = 0;
    gBgScroll1.x = 0;
    gBgScroll1.y = 0;
    gBgScroll2.x = 0;
    gBgScroll2.y = 0;
    gBgScroll3.x = 0;
    gBgScroll3.y = 0;
}

void sub_080415E8(u8 first, u8 second, u8 third)
{
    sub_0803F624(gObjectParameterWork, 8, 0);
    gObjectParameterWork[2] = first;
    gObjectParameterWork[3] = 0x7F;
    gObjectParameterWork[4] = second;
    gObjectParameterWork[5] = third;
}

void sub_08041624(u8 first, u8 second, u8 third, u8 fourth)
{
    sub_0803F624(gObjectParameterWork, 8, 0);
    gObjectParameterWork[2] = first;
    gObjectParameterWork[3] = fourth;
    gObjectParameterWork[4] = second;
    gObjectParameterWork[5] = third;
}

u32 sub_08041674(void)
{
    gObjectCallbacks_083B2994[gUnknown_03000440[0x29]]();
    return gUnknown_03000440[0x28];
}

void sub_08041BF4(void)
{
    gUnknown_03000440[0x28] = (gUnknown_03000440[0x2A] << 4) + 1;
    gUnknown_03000440[0x29]++;
}

void sub_08041C14(u8 index, u8 operation, u16 value)
{
    switch ((operation & 0xC) >> 2)
    {
    default: gFrameObjects[index].screenX = value; break;
    case 1: gFrameObjects[index].screenX = value + 1; break;
    case 3: gFrameObjects[index].screenX = value - 1; break;
    }
}

void sub_08041C5C(u8 index, u8 operation, u16 value)
{
    switch ((operation & 0xC) >> 2)
    {
    default: gFrameObjects[index].screenY = value; break;
    case 1: gFrameObjects[index].screenY = value + 1; break;
    case 3: gFrameObjects[index].screenY = value - 1; break;
    }
}

u32 sub_08041CA4(void)
{
    gUnknown_03000440[4] = 0;
    gObjectCallbacks_083B29CC[gUnknown_03000440[0x1B]]();
    if (gUnknown_03000440[4] > 7)
        return 1;
    return 0;
}

u32 sub_08041CD4(void)
{
    gUnknown_03000440[4] = 0;
    gObjectCallbacks_083B29E4[gUnknown_03000440[0x1B]]();
    if (gUnknown_03000440[4] > 7)
        return 1;
    return 0;
}

void sub_08041D04(const u8 *source, u8 *destination, u8 size)
{
    u32 i;
    for (i = 0; i < size; i++)
        *destination++ = *source++;
}

void sub_08041D28(void)
{
    u32 i;
    for (i = 0; i <= 29; i++)
        gInventoryRecords[i].byte0 = i;
}

u32 sub_08041D3C(u8 identifier)
{
    u32 i;
    for (i = 0; i <= 29; i++)
    {
        if ((gInventoryRecords[i].byte0 & 0x80) && gInventoryRecords[i].byte1 == identifier)
            return i + 1;
    }
    return 0;
}

void sub_08041FE4(u8 identifier)
{
    u32 i;
    for (i = 0; i <= 29; i++)
    {
        if ((gInventoryRecords[i].byte0 & 0x80) && gInventoryRecords[i].byte1 == identifier)
        {
            u8 flags = gInventoryRecords[i].byte0 & 0x1F;
            sub_0803F624(&gInventoryRecords[i], 64, 0);
            gInventoryRecords[i].byte0 = flags;
            return;
        }
    }
}

u32 sub_080420C4(u8 value, u8 first, u8 second, u8 third, u8 fourth)
{
    if (fourth != 0 && value >= fourth)
        return 4;
    if (third != 0 && value >= third)
        return 3;
    if (second != 0 && value >= second)
        return 2;
    if (first != 0 && value >= first)
        return 1;
    return 0;
}

u32 sub_08042114(u8 index, u8 row)
{
    u8 *base = gObjectHalfwordBytes;
    u32 offset = row * 240 + index * 2;
    u32 value = base[offset] << 8;
    offset++;
    return base[offset] | value;
}

void sub_0804213C(u8 index, u8 row, u8 increment)
{
    u8 *base = gObjectHalfwordBytes;
    u8 *entry = &base[row * 240 + index * 2];
    s32 value = *entry + increment;
    if (value > 99)
        *entry = 99;
    else
        *entry = value;
}

void sub_08042170(u8 index, u8 row, u8 decrement)
{
    u8 *base = gObjectHalfwordBytes;
    u8 *entry = &base[row * 240 + index * 2];
    s32 value = *entry - decrement;
    if (value < 0)
        value = 0;
    *entry = value;
}

void sub_080421A0(void)
{
    u32 i;
    for (i = 0; i <= 8; i++)
        gUnknownRecords_030017A0[i].byte7 = i;
}

void sub_0804169C(void)
{
    LeDecompress(gUnknownBytes_08487388, (void *)0x06002600);
    LeDecompress(gUnknownBytes_08487408, (void *)0x060026E0);
    LeDecompress(gUnknownBytes_084C88B8, (void *)0x06017E00);
    LoadLeTilemap(0, 21, gUnknownBytes_0848816C, (*(volatile u16 *)0x04000008), 0x130);
    LoadLeTilemap(2, 22, gUnknownBytes_084881B4, (*(volatile u16 *)0x04000008), 0x137);
    CpuFastSet(gUnknownWords_084E43F8, (void *)0x050003C0, 8);
    gUnknown_03000440[0x29]++;
}

void sub_0804172C(void)
{
    sub_0803EF8C(8, 6, gUnknown_03000440[0x2C], gUnknown_03000440[0x2D], (*(volatile u16 *)0x04000008), 0);
    sub_0803EF8C(8, 6, 0, 21, (*(volatile u16 *)0x04000008), 0);
    gUnknown_03000440[0x29]++;
}

void sub_08041BA4(void)
{
    gFrameObjects[gUnknown_03000440[0x2B]].scaleX -= 8;
    gFrameObjects[gUnknown_03000440[0x2B]].scaleY -= 8;
    if (gFrameObjects[gUnknown_03000440[0x2B]].scaleX == 0)
    {
        sub_08040CD0(gUnknown_03000440[0x2B], 1);
        gUnknown_03000440[0x29]++;
    }
}

u32 sub_08042218(void)
{
    u32 i;
    for (i = 0; i <= 8; i++)
        if (gUnknownRecords_030017A0[i].unknown00[0] == 0)
            return 0;
    return 1;
}


void sub_0804177C(void)
{
    u32 offset = gUnknown_03000440[0x2D] * 64;
    u16 *start = (u16 *)(gUnknown_03000440[0x2C] * 2 + 0x06002800);
    u16 *destination = (u16 *)(offset + (u32)start);
    u16 *row = destination;
    const u16 *source;
    u32 i, j;
    for (i = 0; i <= 1; i++)
    {
        for (j = 0; j <= 7; j++)
            *destination++ = 0;
        row += 32;
        destination = row;
    }
    source = (const u16 *)0x06002D40;
    for (j = 0; j <= 7; j++)
        *destination++ = *source++;
    row += 32;
    destination = row;
    source = (const u16 *)0x06002E80;
    for (j = 0; j <= 7; j++)
        *destination++ = *source++;
    row += 32;
    destination = row;
    for (i = 0; i <= 1; i++)
    {
        for (j = 0; j <= 7; j++)
            *destination++ = 0;
        row += 32;
        destination = row;
    }
    gUnknown_03000440[0x29]++;
}

void sub_08041818(void)
{
    u32 offset = gUnknown_03000440[0x2D] * 64;
    u16 *start = (u16 *)(gUnknown_03000440[0x2C] * 2 + 0x06002800);
    u16 *destination = (u16 *)(offset + (u32)start);
    u16 *row = destination;
    const u16 *source;
    const u16 *sourceRow;
    u32 i, j;
    for (j = 0; j <= 7; j++)
        *destination++ = 0;
    row += 32;
    source = (const u16 *)0x06002D40;
    sourceRow = source;
    destination = row;
    for (i = 0; i <= 1; i++)
    {
        for (j = 0; j <= 7; j++)
            *destination++ = *source++;
        row += 32;
        destination = row;
        sourceRow += 32;
        source = sourceRow;
    }
    source = (const u16 *)0x06002E40;
    sourceRow = source;
    for (i = 0; i <= 1; i++)
    {
        for (j = 0; j <= 7; j++)
            *destination++ = *source++;
        row += 32;
        destination = row;
        sourceRow += 32;
        source = sourceRow;
    }
    for (j = 0; j <= 7; j++)
        *destination++ = 0;
    gUnknown_03000440[0x29]++;
}

void sub_080418C0(void)
{
    u32 offset = gUnknown_03000440[0x2D] * 64;
    u16 *start = (u16 *)(gUnknown_03000440[0x2C] * 2 + 0x06002800);
    u16 *destination = (u16 *)(offset + (u32)start);
    u16 *row;
    const u16 *source = (const u16 *)0x06002D40;
    const u16 *sourceRow = source;
    u32 i, j;
    row = destination;
    for (i = 0; i <= 5; i++)
    {
        for (j = 0; j <= 7; j++)
            *destination++ = *source++;
        row += 32;
        destination = row;
        sourceRow += 32;
        source = sourceRow;
    }
    gUnknown_03000440[0x29]++;
}

void sub_08041920(void)
{
    gFrameObjects[gUnknown_03000440[0x2B]].flags = 0xD204;
    gFrameObjects[gUnknown_03000440[0x2B]].screenX = gUnknown_03000440[0x2C] * 8 + 20;
    gFrameObjects[gUnknown_03000440[0x2B]].screenY = gUnknown_03000440[0x2D] * 8 + gUnknown_03000440[0x2A] * 16 + 16;
    gFrameObjects[gUnknown_03000440[0x2B]].frameAndGroup = 0x307;
    gFrameObjects[gUnknown_03000440[0x2B]].palette = 14;
    gFrameObjects[gUnknown_03000440[0x2B]].tableSelector = 0;
    gFrameObjects[gUnknown_03000440[0x2B]].scaleX = 1;
    gFrameObjects[gUnknown_03000440[0x2B]].scaleY = 1;
    gFrameObjects[gUnknown_03000440[0x2B]].priority = 0xFF;
    gUnknown_03000440[0x84] = 1;
    gUnknown_03000440[0x29]++;
}

void sub_080419CC(void)
{
    gFrameObjects[gUnknown_03000440[0x2B]].scaleX += 8;
    gFrameObjects[gUnknown_03000440[0x2B]].scaleY += 8;
    if (gFrameObjects[gUnknown_03000440[0x2B]].scaleX > 63)
    {
        gFrameObjects[gUnknown_03000440[0x2B]].scaleX = 64;
        gFrameObjects[gUnknown_03000440[0x2B]].scaleY = 64;
        gUnknown_03000440[0x29]++;
    }
    gUnknown_03000440[0x84] = 0;
}

void sub_0804253C(u8 mode, u16 control, u16 duration)
{
    u32 effect;
    u32 first;
    u32 second;
    u32 brightness;
    gUnknown_03000440[0x90] = mode;
    *(u16 *)(gUnknown_03000440 + 0x92) = duration;
    *(u16 *)(gUnknown_03000440 + 0x94) = 0;
    switch (mode)
    {
    case 1: effect = 0x40; first = 16; second = 16; brightness = 16; break;
    case 2: effect = 0x40; first = 0; second = 0; brightness = 0; break;
    case 3: effect = 0x80; first = 16; second = 16; brightness = 16; break;
    case 4: effect = 0x80; first = 0; second = 0; brightness = 0; break;
    case 5: effect = 0xC0; first = 16; second = 16; brightness = 16; break;
    case 6: effect = 0xC0; first = 0; second = 0; brightness = 0; break;
    default: effect = 0; first = 0; second = 0; brightness = 0; break;
    }
    *(volatile u16 *)0x04000052 = ((second & 31) << 8) | (first & 31);
    *(volatile u16 *)0x04000054 = brightness & 31;
    *(volatile u16 *)0x04000050 = effect | control;
}

/* The matching caller initializes mode to 1..6. The original default path
 * consumes uninitialized coefficient registers; it has no defined C value. */
u32 sub_080425DC(void)
{
    u8 *base = gUnknown_03000440;
    u8 *work;
    u32 mode;
    u16 first;
    u16 second;
    u16 brightness;
    u16 previous = *(u16 *)(base + 0x94);
    *(u16 *)(base + 0x94) = previous + *(u16 *)(base + 0x92);
    mode = base[0x90] - 1;
    work = base;
    switch (mode)
    {
    case 0: case 2: case 4:
        first = 16 - (*(u16 *)(work + 0x94) >> 4);
        second = first;
        brightness = first;
        break;
    case 1: case 3: case 5:
        first = *(u16 *)(work + 0x94) >> 4;
        second = first;
        brightness = first;
        break;
    }
    *(volatile u16 *)0x04000052 = ((second & 31) << 8) | (first & 31);
    *(volatile u16 *)0x04000054 = brightness & 31;
    if (*(u16 *)(work + 0x94) > 255)
        return 1;
    return 0;
}


#include "object_helpers.h"
#include "frame.h"
#include "state0_inventory.h"

extern struct ObjectSortEntry gObjectSortEntries[];
extern u16 gObjectFourthKey;
extern u8 gObjectCountPairs[64][2];
void sub_0804242C(u8 count);

/* Sorting is performed by the original callee; ties use its second halfword. */
s32 sub_0804206C(void)
{
    u32 fill = 0;
    u32 i;
    s32 first;
    s32 fourth;
    CpuFastSet(&fill, gObjectSortEntries, CPU_SET_FILL | 0x80);
    for (i = 0; i <= 29; i++)
        gObjectSortEntries[i].key = gInventoryRecords[i].byte5;
    sub_0804242C(30);
    first = gObjectSortEntries[0].key;
    fourth = gObjectFourthKey;
    return (first - fourth) / 2 + fourth;
}

u32 sub_08042278(u8 input)
{
    u32 i;
    u8 key = input & 0x3F;
    for (i = 0; i <= 63; i++)
        if ((gObjectCountPairs[i][0] & 0x80) && (gObjectCountPairs[i][0] & 0x7F) == key)
            return gObjectCountPairs[i][1];
    return 0;
}
