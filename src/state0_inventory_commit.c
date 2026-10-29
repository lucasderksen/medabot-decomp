#include "state0_callbacks.h"
#include "state0_work.h"
#include "state0_display.h"
#include "state0_inventory.h"
#include "display_helpers.h"
#include "frame.h"
#include "main.h"
#include "input.h"

u32 sub_08006E08(volatile u32 part)
{
    if (!part)
        part = gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].unknown00[1] + 120;
    else if (part > 119)
        part = 119;
    else
        part--;
    return part;
}

void sub_08006E44(void)
{
    u8 *work = gState0TypedWork.bytes;
    if (work[0x53]) {
        u32 valid = sub_08043814(work[0x97], work[0x98], work[0x99], work[0x9A], work[0x9B]);
        if (!valid) {
            sub_08042E58(work[0x98], work[0x99], work[0x9A], work[0x9B], 0, 6, 168, 32, work[0x5E], 1, 5);
            work[0x53] = 0;
        }
    } else {
        if (sub_08043814(work[0x97], work[0x98], work[0x99], work[0x9A], work[0x9B])) {
            sub_08043240(6, 8);
            work[0x53] = 1;
        }
    }
}

void sub_08006F14(void)
{
    if (gState0TypedWork.bytes[0x53])
        sub_080432A0(6, 0, 0);
}

void sub_08006FB0(void)
{
    u8 count = 0;
    struct State0Record8 *base;
    u8 *work;
    if (gState0TypedWork.bytes[0x97] == 30) {
        gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].unknown00[0] = 1;
        gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].unknown00[2] = 30;
    } else {
        gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].unknown00[0] = 2;
        gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].unknown00[2] = gInventoryRecords[gState0TypedWork.bytes[0x97]].byte1;
        gInventoryRecords[gState0TypedWork.bytes[0x97]].byte0 |= 0x40;
        count = 1;
    }
    base = gUnknownRecords_030017A0;
    work = gState0TypedWork.bytes;
    base[work[0x51]].byte3 = work[0x98];
    if (work[0x98] <= 119) { sub_08043560(work[0x98], 0, 1, 0, 1); count++; }
    base[work[0x51]].byte4 = work[0x99];
    if (work[0x99] <= 119) { sub_08043560(work[0x99], 1, 1, 0, 1); count++; }
    base[work[0x51]].byte5 = work[0x9A];
    if (work[0x9A] <= 119) { sub_08043560(work[0x9A], 2, 1, 0, 1); count++; }
    base[work[0x51]].byte6 = work[0x9B];
    if (work[0x9B] <= 119) { sub_08043560(work[0x9B], 3, 1, 0, 1); count++; }
    if (count == 5) base[work[0x51]].unknown00[0] = 3;
}

void sub_080070F0(void)
{
    u32 i = 0;
    u8 *count = &gState0TypedWork.bytes[0x41];
    struct InventoryRecord *record = gInventoryRecords;
    do {
        if (record->byte0 & 0x80) {
            if (record->byte0 & 0x40) goto next;
            (*count)++;
        }
next:
        record++;
        i++;
    } while (i <= 29);
}


u32 sub_080437E0(void);

u32 sub_08006C64(void)
{
    volatile u32 category;
    volatile u32 part;
    if ((u8)gNewKeys & 8) {
        u8 *selected;
        u8 *part0;
        u8 *part3;
        u8 *part1;
        u8 *part2;
        struct State0Record8 *base;
        sub_08074DE0(4);
        category = 0;
        if (gState0TypedWork.bytes[0x5A]) category = gState0TypedWork.bytes[0x5A] - 1;
        switch (category) {
        case 0: part = gState0TypedWork.bytes[0x98]; break;
        case 1: part = gState0TypedWork.bytes[0x99]; break;
        case 2: part = gState0TypedWork.bytes[0x9A]; break;
        case 3: part = gState0TypedWork.bytes[0x9B]; break;
        }
        if (sub_080437E0())
            part = sub_080436AC(part, category, 0, gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].unknown00[1]);
        goto cycle;
complete:
        sub_08005C9C(); sub_08005D1C(); sub_08005E00(); sub_08005E84();
        sub_08005F68(); sub_08005FEC(); sub_080060D0(); sub_08006154();
        sub_080063B4(); sub_08006414(); sub_08006444(); sub_0800667C();
        return 1;
cycle:
        part = sub_08006E08(part);
        base = gUnknownRecords_030017A0;
        selected = &gState0TypedWork.bytes[0x51];
        part0 = selected + 0x47;
        part3 = selected + 0x4A;
        part1 = selected + 0x48;
        part2 = selected + 0x49;
        while (1) {
            *part0 = sub_080436AC(part, 0, 0, base[*selected].unknown00[1]);
            *part1 = sub_080436AC(part, 1, 0, base[*selected].unknown00[1]);
            *part2 = sub_080436AC(part, 2, 0, base[*selected].unknown00[1]);
            *part3 = sub_080436AC(part, 3, 0, base[*selected].unknown00[1]);
            if (sub_080437E0()) goto complete;
            switch (category) {
            case 0: part = *part0; break;
            case 1: part = *part1; break;
            case 2: part = *part2; break;
            case 3: part = *part3; break;
            }
            part = sub_080436AC(part, category, 0, base[*selected].unknown00[1]);
            part = sub_08006E08(part);
        }
    }
    return 0;
}

