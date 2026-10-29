

#include "state0_inventory_rows.h"
#include "state0_inventory_parts.h"
#include "state0_inventory_view.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "state0_inventory.h"
#include "display_helpers.h"
#include "graphics.h"
#include "frame.h"
#include "main.h"
#include "input.h"

extern const u8 gUnknownBytes_083B7F8C[];
extern const u8 *const gUnknownPointers_083B803C[];
void sub_0800AA1C(void);
void sub_0800AAC0(void);
void sub_0800AB0C(void);
void sub_0800ABA4(void);
void sub_0800AC2C(void);
void sub_0800AED0(void);
void sub_0800AF0C(void);
void sub_0800AF64(void);

void sub_0800A854(void)
{
    gFrameObjects[3].flags = 0xC804;
    gFrameObjects[3].screenX = 8;
    gFrameObjects[3].screenY = gState0TypedWork.bytes[0x46] * 16 + 56;
    gFrameObjects[3].frameAndGroup = 0x307;
    gFrameObjects[3].palette = 14;
    gFrameObjects[3].tableSelector = 0;
    gFrameObjects[3].priority = 65;
}

u32 sub_0800A8A0(void)
{
    if (*(u8 *)&gRepeatedKeys & 64)
    {
        if (!gState0TypedWork.bytes[0x46]) gState0TypedWork.bytes[0x46] = 2;
        else gState0TypedWork.bytes[0x46]--;
    }
    if (*(u8 *)&gRepeatedKeys & 128)
    {
        if (gState0TypedWork.bytes[0x46] == 2) gState0TypedWork.bytes[0x46] = 0;
        else gState0TypedWork.bytes[0x46]++;
    }
    if (*(u8 *)&gRepeatedKeys & 192)
    {
        sub_08074DE0(2);
        gFrameObjects[3].screenY = gState0TypedWork.bytes[0x46] * 16 + 56;
        sub_0800A594();
        return 1;
    }
    return 0;
}

u32 sub_0800A928(void)
{
    if (*(u8 *)&gRepeatedKeys & 48)
    {
        sub_08009E4C(); sub_08009EF4(); sub_08009F50(); sub_08009F90();
        sub_0800A2E8(); sub_0800A594();
        return 1;
    }
    return 0;
}

u32 sub_0800A960(void)
{
    u8 *work = gState0TypedWork.bytes;
    switch (work[0x46])
    {
    case 0:
    {
        struct InventoryRecord *records = gInventoryRecords;
        struct InventoryRecord *record = &records[work[0x3D]];
        if (record->byte5 > 9)
        {
            const u8 *source = gUnknownBytes_083B7F8C + record->byte1 * 3;
            u8 *part = &work[0xEE];
            sub_08041D04(source, part, 3);
            return *part;
        }
        return 52;
    }
    case 1:
    {
        struct InventoryRecord *records = gInventoryRecords;
        struct InventoryRecord *record = &records[work[0x3D]];
        if (record->byte5 > 29)
        {
            sub_08041D04(gUnknownBytes_083B7F8C + record->byte1 * 3, &work[0xEE], 3);
            return work[0xEF];
        }
        return 52;
    }
    default:
    {
        struct InventoryRecord *records = gInventoryRecords;
        struct InventoryRecord *record = &records[work[0x3D]];
        if (record->byte5 > 59)
        {
            sub_08041D04(gUnknownBytes_083B7F8C + record->byte1 * 3, &work[0xEE], 3);
            return work[0xF0];
        }
        return 52;
    }
    }
}

void sub_0800AA1C(void)
{
    const u8 *const *tables = gUnknownPointers_083B803C;
    u8 *work = gState0TypedWork.bytes;
    const u8 *table = tables[work[0x43]];
    { u32 count = table[0]; work[0x45] = count; }
    gFrameObjects[6].flags = 0xC004;
    { u32 index = work[0x44] + 1; const u8 *entry = table + index * 2; gFrameObjects[6].screenX = entry[0] * 8; }
    { u32 index = work[0x44] + 1; gFrameObjects[6].screenY = table[index * 2 + 1] * 8; }
    gFrameObjects[6].frameAndGroup = 0x308;
    gFrameObjects[6].palette = 14;
    gFrameObjects[6].tableSelector = 0;
    gFrameObjects[6].priority = 193;
    sub_08040B90(gUnknownPointers_083B6100[3], 6);
}



void sub_0800ABA4(void)
{
    const void *const *assets = gUnknownPointers_083B4C60;
    struct InventoryRecord *records = gInventoryRecords;
    u32 assetIndex = records[gState0TypedWork.bytes[0x3D]].unknown06[3] + 81;
    sub_0803F15C(16, 2, 6, 10, assets[assetIndex], *(volatile u16 *)0x0400000A, 0x200);
}

void sub_0800ABF0(void)
{
    if (*(u8 *)&gRepeatedKeys & 48)
    {
        sub_08009E4C(); sub_08009EF4(); sub_08009F50(); sub_08009F90();
        sub_0800AB0C(); sub_0800ABA4(); sub_0800AED0(); sub_0800AF0C(); sub_0800AF64();
    }
}

void sub_0800AC2C(void)
{
    gFrameObjects[1].flags = 0xC804;
    gFrameObjects[1].screenX = gState0TypedWork.bytes[0x46] * 16 + 56;
    gFrameObjects[1].screenY = 52;
    gFrameObjects[1].frameAndGroup = 0x300;
    gFrameObjects[1].palette = 14;
    gFrameObjects[1].tableSelector = 0;
    gFrameObjects[1].priority = 64;
    gFrameObjects[2].flags = 0xC804;
    gFrameObjects[2].screenX = gState0TypedWork.bytes[0x46] * 16 + 56;
    gFrameObjects[2].screenY = 76;
    gFrameObjects[2].frameAndGroup = 0x301;
    gFrameObjects[2].palette = 14;
    gFrameObjects[2].tableSelector = 0;
    gFrameObjects[2].priority = 64;
}

void sub_0800ACA8(void)
{
    gFrameObjects[3].flags = 0xC804;
    gFrameObjects[3].screenX = gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[3] * 16 + 48;
    gFrameObjects[3].screenY = 48;
    gFrameObjects[3].frameAndGroup = 0x305;
    gFrameObjects[3].palette = 14;
    gFrameObjects[3].tableSelector = 0;
    gFrameObjects[3].priority = 64;
}

void sub_0800AD00(void)
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




void sub_0800AED0(void)
{
    u32 record = sub_08009CAC(gState0TypedWork.bytes[0x3D]);
    if (record != 255)
    {
        struct State0Record8 *entries = gUnknownRecords_030017A0;
        struct State0Record8 *entry = &entries[record];
        sub_08042D94(entry->byte3, entry->byte4, entry->byte5, entry->byte6, 2);
    }
}

void sub_0800AF0C(void)
{
    u32 record = sub_08009CAC(gState0TypedWork.bytes[0x3D]);
    if (record != 255)
    {
        struct State0Record8 *entries = gUnknownRecords_030017A0;
        struct State0Record8 *entry = &entries[record];
        sub_08042E58(entry->byte3, entry->byte4, entry->byte5, entry->byte6, 2, 100, 24, 64, 0, 2, 0);
    }
    else sub_08040D0C(100, 4);
}

void sub_0800AF64(void)
{
    u8 *work = gState0TypedWork.bytes;
    u32 record = sub_08009CAC(work[0x3D]);
    if (record != 255)
    {
        struct State0Record8 *entries = gUnknownRecords_030017A0;
        struct State0Record8 *entry = &entries[record];
        if (entry->byte6 <= 119)
        {
            sub_08042B58(entry->byte6, 3, &work[0x10E]);
            sub_080435B0(work[0x10F] - 100, 2, 10, *(volatile u16 *)0x0400000A, 0x83A0);
        }
        else sub_080435B0(255, 2, 10, *(volatile u16 *)0x0400000A, 0x83A0);
    }
    else sub_080435B0(255, 2, 10, *(volatile u16 *)0x0400000A, 0x83A0);
}
