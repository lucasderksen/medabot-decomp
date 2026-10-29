#include "state0_next_helpers.h"


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

extern const void *const gUnknownPointers_083B66EC[];
extern const u8 *const gUnknownPointers_083B7048[];
void sub_0800A000(void);
void sub_0800A05C(void);
void sub_0800A0B8(void);
void sub_0800A0FC(void);
void sub_0800A180(void);
void sub_0800A1E4(void);
void sub_0800A2B4(void);

void sub_0800A000(void)
{
    const void *const *names;
    struct InventoryRecord *records;
    u8 *work;
    u8 *record;
    u8 *buffer;
    sub_08040D0C(30, 15);
    names = gUnknownPointers_083B66EC;
    records = gInventoryRecords;
    work = gState0TypedWork.bytes;
    record = (u8 *)&records[work[0x3D]];
    {
        const void *name = names[record[4]];
        buffer = &work[0x9E];
        sub_0803F63C(name, buffer, 14);
    }
    sub_08040DB8(buffer, 30, 10, 7, 8, 11, 1, 1);
}

void sub_0800A05C(void)
{
    const u8 *const *names;
    struct InventoryRecord *records;
    u8 *work;
    u8 *record;
    u8 *buffer;
    sub_08040D0C(45, 13);
    names = gUnknownPointers_083B7048;
    records = gInventoryRecords;
    work = gState0TypedWork.bytes;
    record = (u8 *)&records[work[0x3D]];
    {
        const void *name = names[record[6]];
        buffer = &work[0x9E];
        sub_0803F63C(name, buffer, 14);
    }
    sub_08040DB8(buffer, 45, 10, 10, 10, 10, 1, 1);
}

void sub_0800A0B8(void)
{
 
 sub_08042698(2, 2, 27, 7, *(volatile u16 *)0x0400000A, (u16)(0xD340 + gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[1] * 4));
}

void sub_0800A0FC(void)
{
    if (gState0TypedWork.bytes[0x41] > 1)
    {
        gFrameObjects[1].flags = 0xC804;
        gFrameObjects[1].screenX = 4;
        gFrameObjects[1].screenY = 32;
        gFrameObjects[1].frameAndGroup = 0x302;
        gFrameObjects[1].palette = 14;
        gFrameObjects[1].tableSelector = 0;
        gFrameObjects[1].priority = 64;
        gFrameObjects[2].flags = 0xC804;
        gFrameObjects[2].screenX = 124;
        gFrameObjects[2].screenY = 32;
        gFrameObjects[2].frameAndGroup = 0x303;
        gFrameObjects[2].palette = 14;
        gFrameObjects[2].tableSelector = 0;
        gFrameObjects[2].priority = 64;
    }
}

void sub_0800A180(void)
{
    if (gState0TypedWork.bytes[0x41] > 1)
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
}

void sub_0800A2B4(void)
{
    if (*(u8 *)&gRepeatedKeys & 48)
    {
        sub_08009E4C(); sub_08009EF4(); sub_08009F50(); sub_08009F90();
        sub_0800A000(); sub_0800A05C(); sub_0800A0B8();
    }
}


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

extern const void *const gUnknownPointers_083B66EC[];
extern const u8 *const gUnknownPointers_083B7048[];
void sub_0800A000(void);
void sub_0800A05C(void);
void sub_0800A0B8(void);
void sub_0800A0FC(void);
void sub_0800A180(void);
void sub_0800A1E4(void);
void sub_0800A2B4(void);

extern const u8 gUnknownBytes_083B7F8C[];
extern const u8 gUnknownBytes_083B7E54[];

void sub_0800A2E8(void)
{
    sub_08040D0C(30, 60);
    {
        struct InventoryRecord *records = gInventoryRecords;
        u8 *work = gState0TypedWork.bytes;
        struct InventoryRecord *record = &records[work[0x3D]];
        if (record->byte5 > 9)
        {
            u8 *part;
            u8 *buffer;
            const u8 *source = gUnknownBytes_083B7F8C + record->byte1 * 3;
            part = &work[0xEE];
            sub_08041D04(source, part, 3);
            sub_08041D04(gUnknownBytes_083B7E54 + *part * 6, &work[0x10E], 6);
            {
                const void *name = gUnknownPointers_083B74B8[*part];
                buffer = &work[0x9E];
                sub_0803F63C(name, buffer, 17);
            }
            sub_08040DB8(buffer, 30, 2, 6, 10, 10, 1, 1);
            sub_08042698(2, 2, 12, 6, *(volatile u16 *)0x0400000A, (u16)(0x5300 + work[0x113] * 4));
        }
        else
        {
            u8 *buffer = &work[0x9E];
            sub_08042678(buffer, 13);
            sub_08040DB8(buffer, 30, 2, 6, 10, 10, 1, 1);
            sub_0803EF8C(2, 2, 12, 6, *(volatile u16 *)0x0400000A, 0);
        }
    }
    {
        struct InventoryRecord *records = gInventoryRecords;
        u8 *work = gState0TypedWork.bytes;
        struct InventoryRecord *record = &records[work[0x3D]];
        if (record->byte5 > 29)
        {
            u8 *part = &work[0xef];
            u8 *buffer;
            sub_08041D04(gUnknownBytes_083B7E54 + *part * 6, &work[0x10E], 6);
            {
                const void *name = gUnknownPointers_083B74B8[*part];
                buffer = &work[0x9E];
                sub_0803F63C(name, buffer, 17);
            }
            sub_08040DB8(buffer, 50, 2, 8, 10, 10, 1, 1);
            sub_08042698(2, 2, 12, 8, *(volatile u16 *)0x0400000A, (u16)(0x5300 + work[0x113] * 4));
        }
        else
        {
            u8 *buffer = &work[0x9E];
            sub_08042678(buffer, 13);
            sub_08040DB8(buffer, 50, 2, 8, 10, 10, 1, 1);
            sub_0803EF8C(2, 2, 12, 8, *(volatile u16 *)0x0400000A, 0);
        }
    }
    {
        struct InventoryRecord *records = gInventoryRecords;
        u8 *work = gState0TypedWork.bytes;
        struct InventoryRecord *record = &records[work[0x3D]];
        if (record->byte5 > 59)
        {
            u8 *part = &work[0xf0];
            u8 *buffer;
            sub_08041D04(gUnknownBytes_083B7E54 + *part * 6, &work[0x10E], 6);
            {
                const void *name = gUnknownPointers_083B74B8[*part];
                buffer = &work[0x9E];
                sub_0803F63C(name, buffer, 17);
            }
            sub_08040DB8(buffer, 70, 2, 10, 10, 10, 1, 1);
            sub_08042698(2, 2, 12, 10, *(volatile u16 *)0x0400000A, (u16)(0x5300 + work[0x113] * 4));
        }
        else
        {
            u8 *buffer = &work[0x9E];
            sub_08042678(buffer, 13);
            sub_08040DB8(buffer, 70, 2, 10, 10, 10, 1, 1);
            sub_0803EF8C(2, 2, 12, 10, *(volatile u16 *)0x0400000A, 0);
        }
    }
}


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

extern const void *const gUnknownPointers_083B66EC[];
extern const u8 *const gUnknownPointers_083B7048[];
void sub_0800A000(void);
void sub_0800A05C(void);
void sub_0800A0B8(void);
void sub_0800A0FC(void);
void sub_0800A180(void);
void sub_0800A1E4(void);
void sub_0800A2B4(void);

extern const u8 gUnknownBytes_083B7F8C[];
extern const u8 gUnknownBytes_083B7E54[];

void sub_0800A594(void)
{
    u8 *work;
    u32 selector;
    sub_08040D0C(90, 15);
    work = gState0TypedWork.bytes;
    selector = work[0x46];
    switch (selector)
    {
    case 0:
    {
        struct InventoryRecord *records = gInventoryRecords;
        struct InventoryRecord *record = &records[work[0x3D]];
        if (record->byte5 > 9)
        {
            const u8 *source = gUnknownBytes_083B7F8C + record->byte1 * 3;
            u8 *buffer;
            u8 *part = &work[0xEE];
            sub_08041D04(source, part, 3);
            sub_08041D04(gUnknownBytes_083B7E54 + *part * 6, &work[0x10E], 6);
            {
                const void *name = gUnknownPointers_083B7048[work[0x10F]];
                buffer = &work[0x9E];
                sub_0803F63C(name, buffer, 14);
            }
            sub_08040DB8(buffer, 90, 19, 7, 10, 11, 1, 1);
            sub_08042838(work[0x110], 25, 10, 2, *(volatile u16 *)0x0400000A, 0xD334);
        }
        else
        {
            u8 *buffer = &work[0x9E];
            sub_08042678(buffer, 13);
            sub_08040DB8(buffer, 90, 19, 7, 10, 11, 1, 1);
            sub_08042838(0, 25, 10, 2, *(volatile u16 *)0x0400000A, 0xD334);
        }
        break;
    }
    case 1:
    {
        struct InventoryRecord *records = gInventoryRecords;
        struct InventoryRecord *record = &records[work[0x3D]];
        if (record->byte5 > 29)
        {
            const u8 *source = gUnknownBytes_083B7F8C + record->byte1 * 3;
            u8 *buffer;
            sub_08041D04(source, &work[0xEE], 3);
            sub_08041D04(gUnknownBytes_083B7E54 + work[0xef] * 6, &work[0x10E], 6);
            {
                const void *name = gUnknownPointers_083B7048[work[0x10F]];
                buffer = &work[0x9E];
                sub_0803F63C(name, buffer, 14);
            }
            sub_08040DB8(buffer, 90, 19, 7, 10, 11, selector, selector);
            sub_08042838(work[0x110], 25, 10, 2, *(volatile u16 *)0x0400000A, 0xD334);
        }
        else
        {
            u8 *buffer = &work[0x9E];
            sub_08042678(buffer, 13);
            sub_08040DB8(buffer, 90, 19, 7, 10, 11, selector, selector);
            sub_08042838(0, 25, 10, 2, *(volatile u16 *)0x0400000A, 0xD334);
        }
        break;
    }
    default:
    {
        struct InventoryRecord *records = gInventoryRecords;
        struct InventoryRecord *record = &records[work[0x3D]];
        if (record->byte5 > 59)
        {
            const u8 *source = gUnknownBytes_083B7F8C + record->byte1 * 3;
            u8 *buffer;
            sub_08041D04(source, &work[0xEE], 3);
            sub_08041D04(gUnknownBytes_083B7E54 + work[0xf0] * 6, &work[0x10E], 6);
            {
                const void *name = gUnknownPointers_083B7048[work[0x10F]];
                buffer = &work[0x9E];
                sub_0803F63C(name, buffer, 14);
            }
            sub_08040DB8(buffer, 90, 19, 7, 10, 11, 1, 1);
            sub_08042838(work[0x110], 25, 10, 2, *(volatile u16 *)0x0400000A, 0xD334);
        }
        else
        {
            u8 *buffer = &work[0x9E];
            sub_08042678(buffer, 13);
            sub_08040DB8(buffer, 90, 19, 7, 10, 11, 1, 1);
            sub_08042838(0, 25, 10, 2, *(volatile u16 *)0x0400000A, 0xD334);
        }
        break;
    }
    }
}
