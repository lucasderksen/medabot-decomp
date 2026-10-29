#include "equipment_helpers.h"
#include "object_helpers.h"
#include "tile_text.h"
#include "state0_inventory.h"
#include "state0_work.h"
extern u8 gUnknown_03000440[];

void sub_08043560(u32 index, u32 row, u32 byteOffset, u32 subtract, u32 amount)
{
    if (subtract)
        gObjectHalfwordBytes[row * 240 + index * 2 + byteOffset] -= amount;
    else
    {
        u32 value = gObjectHalfwordBytes[row * 240 + index * 2 + byteOffset] + amount;
        if (value > 99)
            value = 99;
        gObjectHalfwordBytes[row * 240 + index * 2 + byteOffset] = value;
    }
}


void sub_080435B0(u32 value, u32 x, u32 y, u32 control, u16 entry)
{
    if (value == 255)
        sub_08042698(2, 2, x, y, control, (u16)(entry + 0x101C));
    else if (value >> 2)
        sub_08042698(2, 2, x, y, control, (u16)(entry + value * 4 + 0x1000));
    else
        sub_08042698(2, 2, x, y, control, (u16)(entry + value * 4));
}


u32 sub_08043814(u8 record, u8 first, u8 second, u8 third, u8 fourth)
{
    if (record != 30 && first <= 119 && second <= 119 && third <= 119 && fourth <= 119)
        return 1;
    return 0;
}


u32 sub_0804384C(u8 record)
{
    u32 i;
    if (record <= 29)
        goto search;
    goto missing;
found:
    return i;
search:
    for (i = 0; i <= 8; i++)
        if (gUnknownRecords_030017A0[i].unknown00[0] > 1
            && gUnknownRecords_030017A0[i].unknown00[2] == record)
            goto found;
missing:
    return 255;
}



#include "equipment_helpers.h"
#include "object_helpers.h"
#include "graphics.h"
#include "compression.h"
#include "main.h"
#include "interrupts.h"
#include "bg_scroll.h"
#include "state0_work.h"
#include "display_helpers.h"
extern void VBlankIntrWait(void);

void sub_08043B58(void)
{
    VBlankIntrWait();
    *(volatile u16 *)0x040000BA = 0;
    gUnknownCallback_03000B98 = DummyInterruptHandler;
}

void sub_08043B7C(u32 index, u32 shadowPalette)
{
    const u8 *const *base = gEquipmentAssets_083B2578;
    u32 offset = index * 4;
    LeDecompress(base[index * 4], (void *)0x06008000);
    LoadLeTilemap(0, 0, gEquipmentAssets_083B2578[offset + 2], *(volatile u16 *)0x0400000C, 0);
    LoadLeTilemap(0, 0, gEquipmentAssets_083B2578[offset + 3], *(volatile u16 *)0x0400000E, 0);
    if (shadowPalette)
        CpuFastSet(gEquipmentAssets_083B2578[offset + 1], gEquipmentPaletteShadow, 64);
    else
        CpuFastSet(gEquipmentAssets_083B2578[offset + 1], (void *)0x05000000, 64);
}

void sub_08043C08(u32 index, u32 shadowPalette)
{
    const u8 *const *base = gEquipmentAssets_083B2628;
    u32 offset = index * 5;
    LeDecompress(base[offset], (void *)0x06008000);
    LoadLeTilemap(0, 0, gEquipmentAssets_083B2628[offset + 3], *(volatile u16 *)0x0400000C, 0);
    LoadLeTilemap(0, 0, gEquipmentAssets_083B2628[offset + 4], *(volatile u16 *)0x0400000E, 0);
    if (shadowPalette)
        CpuFastSet(gEquipmentAssets_083B2628[offset + 2], gEquipmentPaletteShadow, 64);
    else
        CpuFastSet(gEquipmentAssets_083B2628[offset + 2], (void *)0x05000000, 64);
}

s32 sub_08043C94(void)
{
    s32 value = sub_080424B8();
    return value * 100 / 255;
}

void sub_08043CA8(void)
{
    gBgScroll0.x = 0; gBgScroll0.y = 0;
    gBgScroll1.x = 0; gBgScroll1.y = 0;
    gBgScroll2.x = 0; gBgScroll2.y = 0;
    gBgScroll3.x = 0; gBgScroll3.y = 0;
}

void sub_08043DF8(void)
{
    u8 *work = gState0TransferWork.bytes;
    if (work[0x3C])
    {
        *(volatile u16 *)0x04000052 = (work[0x3D] << 8) | work[0x3E];
        *(volatile u16 *)0x04000054 = 0;
        *(volatile u16 *)0x04000050 = 0x1844;
    }
    else
        sub_0804253C(0, 0, 0);
}

void sub_08043E48(void)
{
    sub_08043CD4();
}

void sub_08043E54(void)
{
    u8 *work = gState0TransferWork.bytes;
    sub_0803F63C(gEquipmentTable_083C3CDC[work[0x38]], work + 0x74, 8);
}

void sub_08043F9C(void)
{
    u8 *work = gState0TransferWork.bytes;
    if (work[0x77])
    {
        *(volatile u16 *)0x04000052 = (work[0x78] << 8) | work[0x79];
        *(volatile u16 *)0x04000054 = 0;
        *(volatile u16 *)0x04000050 = 0x1844;
    }
    else
        sub_0804253C(0, 0, 0);
}

void sub_08043FEC(u32 index)
{
    u8 *work = gState0TransferWork.bytes;
    u32 frameOffset;
    u32 counter = work[0x7D] + 1;
    u32 zero = 0;
    work[0x7D] = counter;
    if (work[0x7D] > 2)
    {
        work[0x7D] = zero;
        work[0x7C] = (work[0x7C] + 1) & 127;
        sub_08041D04(gEquipmentWidths_083C4238 + index, work + 0x7E, 1);
        frameOffset = index * 128 + work[0x7C];
        sub_08041D04((const u8 *)gEquipmentFrames_083C4243 + frameOffset, work + 0x7F, 1);
        if (work[0x7F] == 255)
        {
            work[0x7C] = zero;
            sub_08041D04(gEquipmentFrames_083C4243[index], work + 0x7F, 1);
        }
        CpuSet(gEquipmentTiles_02027000 + work[0x7E] * work[0x7F] * 32,
               (void *)0x06008020, work[0x7E] * 8 | CPU_SET_32BIT);
    }
}


#include "equipment_helpers.h"
#include "object_helpers.h"
extern u8 gEquipmentWork[];

void sub_0804387C(void)
{
    u8 *work = gEquipmentWork;
    u32 copied, zero;
    u8 *first;
    sub_08041D04((const u8 *)((u32)gEquipmentTable_083BEC10 + work[0x7FE] * 8), gUnknown_0300052E, 1);
    copied = gUnknown_0300052E[0];
    first = work + 0xC29;
    zero = 0;
    *first = copied;
    work[0xC2B] = zero;
}



#include "equipment_helpers.h"
#include "main.h"
extern u16 gEquipmentScanlineA[];
extern u16 gEquipmentScanlineB[];
struct EquipmentDmaRegisters { u32 source, destination, control; };

void sub_08043AE0(void)
{
    volatile struct EquipmentDmaRegisters *channel = (volatile struct EquipmentDmaRegisters *)0x040000B0;
    u16 *source;
    if (!(gFrameCounter & 1))
        source = gEquipmentScanlineB;
    else
        source = gEquipmentScanlineA;
    *(volatile u16 *)0x04000010 = source[0];
    *(volatile u16 *)0x04000012 = source[1];
    *(volatile u16 *)0x04000014 = source[2];
    *(volatile u16 *)0x04000016 = source[3];
    *(volatile u16 *)0x04000018 = source[4];
    *(volatile u16 *)0x0400001A = source[5];
    *(volatile u16 *)0x0400001C = source[6];
    *(volatile u16 *)0x0400001E = source[7];
    *(volatile u16 *)0x040000BA = 0;
    channel->source = (u32)(source + 8);
    channel->destination = 0x04000010;
    channel->control = 0xA6600004;
}



#include "equipment_helpers.h"
#include "bg_scroll.h"
#include "state0_work.h"

void sub_08043CD4(void)
{
    if (gState0TransferWork.scroll.first.selector)
    {
        gState0TransferWork.scroll.first.fraction += gState0TransferWork.scroll.first.quarterSpeed;
        if (gState0TransferWork.scroll.first.fraction / 4)
        {
            gState0TransferWork.scroll.first.wholeStep = gState0TransferWork.scroll.first.fraction / 4;
            gState0TransferWork.scroll.first.fraction %= 4;
            if (gState0TransferWork.scroll.first.directions & 1)
            {
                switch (gState0TransferWork.scroll.first.selector)
                {
                case 1: gBgScroll2.y += gState0TransferWork.scroll.first.wholeStep; break;
                case 2: gBgScroll3.y += gState0TransferWork.scroll.first.wholeStep; break;
                }
            }
            if (gState0TransferWork.scroll.first.directions & 2)
            {
                switch (gState0TransferWork.scroll.first.selector)
                {
                case 1: gBgScroll2.y -= gState0TransferWork.scroll.first.wholeStep; break;
                case 2: gBgScroll3.y -= gState0TransferWork.scroll.first.wholeStep; break;
                }
            }
            if (gState0TransferWork.scroll.first.directions & 4)
            {
                switch (gState0TransferWork.scroll.first.selector)
                {
                case 1: gBgScroll2.x += gState0TransferWork.scroll.first.wholeStep; break;
                case 2: gBgScroll3.x += gState0TransferWork.scroll.first.wholeStep; break;
                }
            }
            if (gState0TransferWork.scroll.first.directions & 8)
            {
                switch (gState0TransferWork.scroll.first.selector)
                {
                case 1: gBgScroll2.x -= gState0TransferWork.scroll.first.wholeStep; break;
                case 2: gBgScroll3.x -= gState0TransferWork.scroll.first.wholeStep; break;
                }
            }
        }
    }
}

void sub_08043E78(void)
{
    if (gState0TransferWork.scroll.second.selector)
    {
        gState0TransferWork.scroll.second.fraction += gState0TransferWork.scroll.second.quarterSpeed;
        if (gState0TransferWork.scroll.second.fraction / 4)
        {
            gState0TransferWork.scroll.second.wholeStep = gState0TransferWork.scroll.second.fraction / 4;
            gState0TransferWork.scroll.second.fraction %= 4;
            if (gState0TransferWork.scroll.second.directions & 1)
            {
                switch (gState0TransferWork.scroll.second.selector)
                {
                case 1: gBgScroll2.y += gState0TransferWork.scroll.second.wholeStep; break;
                case 2: gBgScroll3.y += gState0TransferWork.scroll.second.wholeStep; break;
                }
            }
            if (gState0TransferWork.scroll.second.directions & 2)
            {
                switch (gState0TransferWork.scroll.second.selector)
                {
                case 1: gBgScroll2.y -= gState0TransferWork.scroll.second.wholeStep; break;
                case 2: gBgScroll3.y -= gState0TransferWork.scroll.second.wholeStep; break;
                }
            }
            if (gState0TransferWork.scroll.second.directions & 4)
            {
                switch (gState0TransferWork.scroll.second.selector)
                {
                case 1: gBgScroll2.x += gState0TransferWork.scroll.second.wholeStep; break;
                case 2: gBgScroll3.x += gState0TransferWork.scroll.second.wholeStep; break;
                }
            }
            if (gState0TransferWork.scroll.second.directions & 8)
            {
                switch (gState0TransferWork.scroll.second.selector)
                {
                case 1: gBgScroll2.x -= gState0TransferWork.scroll.second.wholeStep; break;
                case 2: gBgScroll3.x -= gState0TransferWork.scroll.second.wholeStep; break;
                }
            }
        }
    }
}
