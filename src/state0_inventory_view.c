

#include "state0_callbacks.h"
#include "state0_inventory_view.h"
#include "state0_work.h"
#include "state0_inventory.h"
#include "display_helpers.h"
#include "graphics.h"
#include "compression.h"
#include "frame.h"
#include "main.h"
#include "input.h"
#include "bg_scroll.h"

extern const void *const gUnknownPointers_083B6590[];
extern const u8 *const gUnknownPointers_083AC614[];
void sub_08009CDC(void);
void sub_08009D30(void);
void sub_08009DA0(void);
void sub_080096BC(void);
void sub_08009750(void);
void sub_080097E0(void);

void ScrollBg3Diagonally(void)
{
    if (gFrameCounter & 1)
    {
        gBgScroll3.x++; gBgScroll3.y++;
    }
}

void sub_0800941C(void)
{
    gState0TypedWork.bytes[0x3F] = (u32)gState0TypedWork.bytes[0x3D] / 6;
    gState0TypedWork.bytes[0x40] = (u32)gState0TypedWork.bytes[0x3D] % 6;
}

void sub_0800944C(void)
{
    u32 i;
    struct InventoryRecord *record;
    gState0TypedWork.bytes[0x41] = 0;
    for (i = 0; i < 30; i++)
    {
        record = &gInventoryRecords[i];
        if (record->byte0 & 128) gState0TypedWork.bytes[0x41]++;
    }
}

void sub_08009484(void)
{
    u8 position = 0;
    u8 index;
    for (index = gState0TypedWork.bytes[0x3F] * 6; index < gState0TypedWork.bytes[0x3F] * 6 + 6; position++, index++)
    {
        struct InventoryRecord *records = gInventoryRecords;
        struct InventoryRecord *record = &records[index];
        if (record->byte0 & 128)
            CpuFastSet((const u8 *)0x084C29D8 + record->byte1 * 128, (u8 *)0x06006600 + position * 128, 32);
        else
            CpuFastSet((const void *)0x084C38D8, (u8 *)0x06006600 + position * 128, 32);
    }
    CopyTilemapRect(2, 12, 4, 4, gUnknownPointers_083B4C60[80], *(volatile u16 *)0x0400000A, 0x200);
}

void sub_08009540(void)
{
    u8 position = 0;
    u8 index;
    HideFrameObjects(10, 60);
    for (index = gState0TypedWork.bytes[0x3F] * 6; index < gState0TypedWork.bytes[0x3F] * 6 + 6; position++, index++)
    {
        struct InventoryRecord *records = gInventoryRecords;
        struct InventoryRecord *record = &records[index];
        if (record->byte0 & 128)
        {
            CopyBytes(gUnknownPointers_083B6590[record->byte1], &gState0TypedWork.bytes[0x9E], 11);
            PlaceAlignedTextObjects(&gState0TypedWork.bytes[0x9E], (u8)(position * 10 + 10), 6, position * 2 + 4, 7, 8, 1, 2);
        }
        else
        {
            FillTextWithHyphens(&gState0TypedWork.bytes[0x9E], 9);
            PlaceAlignedTextObjects(&gState0TypedWork.bytes[0x9E], (u8)(position * 10 + 10), 6, position * 2 + 4, 7, 8, 1, 2);
        }
    }
}

void sub_08009620(void)
{
    u32 index;
    u32 row;
    index = gState0TypedWork.bytes[0x3F] * 6;
    if (index < (u32)(gState0TypedWork.bytes[0x3F] * 6 + 6))
    {
        volatile u16 *control = (volatile u16 *)0x0400000A;
        u32 blank = 0xD32C;
        row = 4;
        do
        {
            struct InventoryRecord *records = gInventoryRecords;
            struct InventoryRecord *record = &records[index];
            if (record->byte0 & 128)
                sub_080426F0(record->byte5, 14, (u8)row, *control, 0xD314);
            else
            {
                FillTilemapRectSequential(1, 2, 14, row, *control, blank);
                FillTilemapRectSequential(1, 2, 15, row, *control, blank);
            }
            row += 2;
            index++;
        } while (index < (u32)(gState0TypedWork.bytes[0x3F] * 6 + 6));
    }
}

void sub_080096BC(void)
{
    u8 *work = gState0TypedWork.bytes;
    u8 *selected;
    struct InventoryRecord *records;
    struct InventoryRecord *record;
    u32 owned;
    u32 index = work[0x3F] * 6 + work[0x40];
    selected = &work[0x3D];
    *selected = index;
    HideFrameObjects(70, 10);
    records = gInventoryRecords;
    record = &records[*selected];
    owned = (u8)(record->byte0 & 128);
    if (owned)
    {
        u8 *names = (u8 *)records;
        u32 offset = *selected * 64;
        names += 10;
        names += offset;
        PlaceAlignedTextObjects(names, 70, 19, 3, 10, 9, 0, 2);
    }
    else
    {
        FillTextWithHyphens(&work[0x9E], 10);
        PlaceAlignedTextObjects(&work[0x9E], 70, 19, 3, 10, 9, owned, 2);
    }
}

void sub_08009750(void)
{
    u8 *work = gState0TypedWork.bytes;
    struct InventoryRecord *records;
    struct InventoryRecord *record;
    u32 index = work[0x3F] * 6 + work[0x40];
    work[0x3D] = index;
    records = gInventoryRecords;
    record = &records[work[0x3D]];
    if (record->byte0 & 128)
    {
        LeDecompress(gUnknownPointers_083AC614[record->byte1 * 5 + ((u8 *)record)[8]], (void *)0x06010000);
        gFrameObjects[0].flags = 0xC804;
        gFrameObjects[0].screenX = 192;
        gFrameObjects[0].screenY = 80;
        gFrameObjects[0].frameAndGroup = 0x200;
        gFrameObjects[0].palette = 13;
        gFrameObjects[0].tableSelector = 0;
        gFrameObjects[0].priority = 64;
    }
    else HideFrameObjects(0, 1);
}

void sub_080097E0(void)
{
    u8 *work = gState0TypedWork.bytes;
    u8 *selected;
    struct InventoryRecord *records;
    struct InventoryRecord *record;
    u8 *buffer;
    u32 index = work[0x3F] * 6 + work[0x40];
    selected = &work[0x3D];
    *selected = index;
    HideFrameObjects(80, 6);
    records = gInventoryRecords;
    record = &records[*selected];
    if (record->byte0 & 128)
    {
        if (record->byte5 != 100)
        {
            buffer = &work[0x9E];
            FormatDecimalString(buffer, *(u16 *)&record->unknown02[0]);
        }
        else
        {
            buffer = &work[0x9E];
            FillTextWithHyphens(buffer, 5);
        }
        PlaceAlignedTextObjects(buffer, 80, 19, 17, 6, 10, 2, 2);
    }
    else
    {
        buffer = &work[0x9E];
        FillTextWithHyphens(buffer, 5);
        PlaceAlignedTextObjects(buffer, 80, 19, 17, 6, 10, 2, 2);
    }
}

void sub_0800988C(void)
{
    gFrameObjects[1].flags = 0xC804;
    gFrameObjects[1].screenX = 36;
    gFrameObjects[1].screenY = 24;
    gFrameObjects[1].frameAndGroup = 0x302;
    gFrameObjects[1].palette = 14;
    gFrameObjects[1].tableSelector = 0;
    gFrameObjects[1].priority = 64;
    gFrameObjects[2].flags = 0xC804;
    gFrameObjects[2].screenX = 124;
    gFrameObjects[2].screenY = 24;
    gFrameObjects[2].frameAndGroup = 0x303;
    gFrameObjects[2].palette = 14;
    gFrameObjects[2].tableSelector = 0;
    gFrameObjects[2].priority = 64;
}

void sub_08009900(void)
{
    gFrameObjects[3].flags = 0xC804;
    gFrameObjects[3].screenX = 24;
    gFrameObjects[3].screenY = gState0TypedWork.bytes[0x40] * 16 + 40;
    gFrameObjects[3].frameAndGroup = 0x307;
    gFrameObjects[3].palette = 14;
    gFrameObjects[3].tableSelector = 0;
    gFrameObjects[3].priority = 65;
}

void sub_0800994C(void)
{
    if (gFrameCounter & 8)
    {
        gFrameObjects[1].flags &= 0xBFFF;
        gFrameObjects[2].flags &= 0xBFFF;
    }
    else
    {
        gFrameObjects[1].flags |= 0x4000;
        gFrameObjects[2].flags |= 0x4000;
    }
}

void sub_080099A4(void)
{
    if (*(u8 *)&gRepeatedKeys & 64)
    {
        if (!gState0TypedWork.bytes[0x40]) gState0TypedWork.bytes[0x40] = 5;
        else gState0TypedWork.bytes[0x40]--;
    }
    if (*(u8 *)&gRepeatedKeys & 128)
    {
        if (gState0TypedWork.bytes[0x40] == 5) gState0TypedWork.bytes[0x40] = 0;
        else gState0TypedWork.bytes[0x40]++;
    }
    if (*(u8 *)&gRepeatedKeys & 192)
    {
        PlaySoundEffect(2);
        gFrameObjects[3].screenY = gState0TypedWork.bytes[0x40] * 16 + 40;
        sub_080096BC(); sub_08009750(); sub_080097E0();
        sub_08009CDC(); sub_08009D30(); sub_08009DA0();
    }
}

void sub_08009A38(void)
{
    if (*(u8 *)&gRepeatedKeys & 32)
    {
        if (!gState0TypedWork.bytes[0x3F]) gState0TypedWork.bytes[0x3F] = 4;
        else gState0TypedWork.bytes[0x3F]--;
    }
    if (*(u8 *)&gRepeatedKeys & 16)
    {
        if (gState0TypedWork.bytes[0x3F] == 4) gState0TypedWork.bytes[0x3F] = 0;
        else gState0TypedWork.bytes[0x3F]++;
    }
    if (*(u8 *)&gRepeatedKeys & 48)
    {
        const void *const *assets;
        u32 index;
        PlaySoundEffect(2);
        assets = gUnknownPointers_083B4C60;
        index = gState0TypedWork.bytes[0x3F] + 75;
        CopyTilemapRect(10, 2, 5, 2, assets[index], *(volatile u16 *)0x0400000A, 0x200);
        sub_08009484(); sub_08009540(); sub_08009620();
        sub_080096BC(); sub_08009750(); sub_080097E0();
        sub_08009CDC(); sub_08009D30(); sub_08009DA0();
    }
}


#include "state0_callbacks.h"
#include "state0_inventory_view.h"
#include "state0_work.h"
#include "state0_inventory.h"
#include "display_helpers.h"
#include "graphics.h"
#include "compression.h"
#include "frame.h"
#include "main.h"
#include "input.h"

void sub_08009AF8(void);
void sub_08009CDC(void);
void sub_08009D30(void);
void sub_08009DA0(void);
extern const void *const gUnknownPointers_083B6590[];

void sub_08009AF8(void)
{
    u8 *work = gState0TypedWork.bytes;
    if (work[0x3E] & 128)
    {
        u32 selected = work[0x3E] & 127;
        if ((u8)(selected / 6) == work[0x3F])
        {
            if (gFrameCounter & 1)
            {
                gFrameObjects[5].flags = 0xC804;
                gFrameObjects[5].screenX = 25;
                gFrameObjects[5].screenY = (u8)(selected % 6) * 16 + 42;
                gFrameObjects[5].frameAndGroup = 0x307;
                gFrameObjects[5].palette = 14;
                gFrameObjects[5].tableSelector = 0;
                gFrameObjects[5].priority = 64;
            }
            else gFrameObjects[5].flags &= 0xBFFF;
        }
        else gFrameObjects[5].flags &= 0xBFFF;
    }
    else gFrameObjects[5].flags &= 0xBFFF;
}

void sub_08009BC8(void)
{
    if (*(u8 *)&gNewKeys & 4)
    {
        u8 *work;
        u8 *marked;
        u8 *page;
        u32 current;
        PlaySoundEffect(2);
        work = gState0TypedWork.bytes;
        marked = &work[0x3E];
        if (*marked & 128)
        {
            u32 source;
            *marked &= 127;
            source = *marked;
            page = &work[0x3F];
            current = *page * 6 + work[0x40];
            if (source != current)
            {
                struct InventoryRecord *records;
                const void *const *assets;
                u32 assetIndex;
                u32 sourceOffset = source * 64;
                records = gInventoryRecords;
                SwapBytes((u8 *)records + sourceOffset, (u8 *)records + current * 64, 64);
                assets = gUnknownPointers_083B4C60;
                assetIndex = *page + 75;
                CopyTilemapRect(10, 2, 5, 2, assets[assetIndex], *(volatile u16 *)0x0400000A, 0x200);
                sub_08009484(); sub_08009540(); sub_08009620();
                sub_080096BC(); sub_08009750(); sub_080097E0();
                sub_08009CDC(); sub_08009D30(); sub_08009DA0();
            }
            *marked = 0;
            sub_08009AF8();
        }
        else
        {
            s32 chosen = work[0x3F] * 6 + work[0x40];
            *marked = chosen - 128;
            sub_08009AF8();
        }
    }
}

u32 sub_08009CAC(u8 index)
{
    struct InventoryRecord *records = gInventoryRecords;
    struct InventoryRecord *record = &records[index];
    if (record->byte0 & 128)
    {
        if (record->byte0 & 64) return sub_0804384C(record->byte1);
    }
    return 255;
}

void sub_08009CDC(void)
{
    u8 *work = gState0TypedWork.bytes;
    u32 selected = work[0x3F] * 6 + work[0x40];
    u32 record;
    work[0x3D] = selected;
    record = sub_08009CAC(work[0x3D]);
    if (record != 255)
    {
        struct State0Record8 *entries = gUnknownRecords_030017A0;
        struct State0Record8 *entry = &entries[record];
        sub_08042D94(entry->byte3, entry->byte4, entry->byte5, entry->byte6, 2);
    }
}

void sub_08009D30(void)
{
    u8 *work = gState0TypedWork.bytes;
    u32 selected = work[0x3F] * 6 + work[0x40];
    u32 record;
    u32 zero;
    u8 *field = &work[0x3D];
    zero = 0;
    *field = selected;
    record = sub_08009CAC(work[0x3D]);
    if (record != 255)
    {
        struct State0Record8 *entries = gUnknownRecords_030017A0;
        struct State0Record8 *entry = &entries[record];
        sub_08042E58(entry->byte3, entry->byte4, entry->byte5, entry->byte6, 2, 100, 224, 120, zero, 2, zero);
    }
    else HideFrameObjects(100, 4);
}

void sub_08009DA0(void)
{
    u8 *work = gState0TypedWork.bytes;
    u32 selected = work[0x3F] * 6 + work[0x40];
    u32 record;
    work[0x3D] = selected;
    record = sub_08009CAC(work[0x3D]);
    if (record != 255)
    {
        struct State0Record8 *entries = gUnknownRecords_030017A0;
        struct State0Record8 *entry = &entries[record];
        if (entry->byte6 <= 119)
        {
            CopyPartMetadataSlot(entry->byte6, 3, &work[0x10E]);
            sub_080435B0(work[0x10F] - 100, 27, 17, *(volatile u16 *)0x0400000A, 0x83A0);
        }
        else sub_080435B0(255, 27, 17, *(volatile u16 *)0x0400000A, 0x83A0);
    }
    else sub_080435B0(255, 27, 17, *(volatile u16 *)0x0400000A, 0x83A0);
}

void sub_08009E4C(void)
{
    struct InventoryRecord *records = gInventoryRecords;
    struct InventoryRecord *record = &records[gState0TypedWork.bytes[0x3D]];
    CpuFastSet((const u8 *)0x084C29D8 + record->byte1 * 128, (void *)0x06006600, 32);
    FillTilemapRectSequential(2, 2, 2, 3, *(volatile u16 *)0x0400000A, 0x6330);
}

void sub_08009EA0(void)
{
    struct InventoryRecord *records = gInventoryRecords;
    struct InventoryRecord *record = &records[gState0TypedWork.bytes[0x3D]];
    CpuFastSet((const u8 *)0x084C29D8 + record->byte1 * 128, (void *)0x06007800, 32);
    FillTilemapRectSequential(2, 2, 2, 3, *(volatile u16 *)0x0400000A, 0x63C0);
}

void sub_08009EF4(void)
{
    const void *const *names;
    struct InventoryRecord *records;
    struct InventoryRecord *record;
    u8 *work;
    u8 *buffer;
    HideFrameObjects(10, 10);
    names = gUnknownPointers_083B6590;
    records = gInventoryRecords;
    work = gState0TypedWork.bytes;
    record = &records[work[0x3D]];
    {
        const void *name = names[record->byte1];
        buffer = &work[0x9E];
        CopyBytes(name, buffer, 11);
    }
    PlaceAlignedTextObjects(buffer, 10, 4, 3, 7, 13, 1, 1);
}

void sub_08009F50(void)
{
    HideFrameObjects(20, 10);
    PlaceAlignedTextObjects(gInventoryNames[gState0TypedWork.bytes[0x3D]], 20, 18, 3, 10, 12, 0, 1);
}

void sub_08009F90(void)
{
    struct InventoryRecord *records = gInventoryRecords;
    struct InventoryRecord *record = &records[gState0TypedWork.bytes[0x3D]];
    sub_080426F0(record->byte5, 12, 3, *(volatile u16 *)0x0400000A, 0xC314);
}

void sub_08009FC8(void)
{
    struct InventoryRecord *records = gInventoryRecords;
    struct InventoryRecord *record = &records[gState0TypedWork.bytes[0x3D]];
    sub_080426F0(record->byte5, 12, 3, *(volatile u16 *)0x0400000A, 0xC3A4);
}
