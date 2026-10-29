#include "state0_next_helpers.h"
#include "state0_work.h"
#include "object_helpers.h"
#include "equipment_helpers.h"

extern u8 gUnknown_030057E0[];

void sub_08011DB0(void)
{
    u32 zero = 0;
    volatile u32 *dma = (volatile u32 *)0x040000D4;
    dma[0] = (u32)&zero;
    dma[1] = (u32)gState0TransferWork.bytes;
    dma[2] = 0x85000100;
    (void)dma[2];
    sub_08011DE4();
    sub_08011E20();
}

void sub_08011DE4(void)
{
    sub_08041D04((const u8 *)((u32)gEquipmentTable_083BEC10 + gUnknown_030057E0[0x7FE] * 8),
                gUnknown_0300052E, 2);
    gState0TransferWork.bytes[0x38] = gUnknown_0300052E[1];
}

void sub_08011E20(void)
{
    u32 condition = gUnknown_030057E0[0xC2D];
    u8 *work = gUnknown_030057E0;
    if (condition == 0)
    {
        u32 random;
        u32 value;
        const u8 *source = (const u8 *)((u32)gState0EquipmentChoices_083BF210 + work[0x7FE] * 4);
        u8 *choices = gUnknown_0300052E;
        sub_08041D04(source, choices, 4);
        random = (u32)sub_08043C94();
        if (random <= 39)
            value = choices[0];
        else if (random <= 69)
            value = choices[1];
        else if (random <= 89)
            value = choices[2];
        else
            value = choices[3];
        work[0xC2A] = value;
    }
    sub_08041D04(gState0EncounterRecords_083C1B80[work[0xC2A]],
                gState0TransferWork.bytes, 40);
    if (gState0TransferWork.bytes[3] == 0)
    {
        u32 i;
        u32 offset;
        i = 0;
        offset = 0;
        do
        {
            u8 *record = gState0TransferWork.bytes + offset;
            u8 first, second, third;
            u32 fourth;
            /* Four independent random draws precede all four writes. */
            first = sub_08011F20(record[4], record[5], record[6], record[7]);
            second = sub_08011F20(record[4], record[5], record[6], record[7]);
            third = sub_08011F20(record[4], record[5], record[6], record[7]);
            fourth = sub_08011F20(record[4], record[5], record[6], record[7]);
            record[4] = first;
            record[5] = second;
            record[6] = third;
            record[7] = fourth;
            offset += 12;
            i++;
        } while (i <= 2);
    }
}

u32 sub_08011F20(u32 first, u32 second, u32 third, u32 fourth)
{
    u32 random = (u32)sub_08043C94();
    if (random <= 39)
        return first;
    if (random <= 69)
        return second;
    if (random <= 89)
        return third;
    return fourth;
}
