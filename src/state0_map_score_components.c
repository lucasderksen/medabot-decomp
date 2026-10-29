#include "state0_next_helpers.h"
#include "state0_work.h"


void sub_08012584(void)
{
    u8 *work = gState0TransferWork.bytes;
    work += 0x16C;
    *(u16 *)work = 0;
    sub_080125B4();
    sub_08012608();
    sub_0801264C();
    sub_080126EC();
    sub_0801275C();
    sub_0801277C();
}

void sub_080125B4(void)
{
    u32 total = 0;
    u32 i = 0;
    u8 *work = gState0TransferWork.bytes;
    u8 *buffer = gSetupBuffer_03000590;
    u8 *active = buffer + 0x3BA;
    u8 *record = buffer + 0x300;
    do
    {
        if (*active)
            total += record[5];
        active += 256;
        record += 256;
        i++;
    } while (i <= 2);
    *(u16 *)(work + 0x16C) += total / 3;
}

void sub_08012608(void)
{
    u32 count = 0;
    u32 i = 0;
    u8 *work = gState0TransferWork.bytes;
    u8 *buffer = gSetupBuffer_03000590;
    u8 *active = buffer + 0x3BA;
    do
    {
        if (*active)
            count++;
        active += 256;
        i++;
    } while (i <= 2);
    *(u16 *)(work + 0x16C) += count * 8;
}

void sub_080126EC(void)
{
    u32 i = 0;
    u32 score = 0;
    u8 *work = gState0TransferWork.bytes;
    u8 *buffer = gSetupBuffer_03000590;
    u8 *last = buffer + 0x3A1;
    u8 *third = buffer + 0x389;
    u8 *first = buffer + 0x359;
    do
    {
        if (last[0x19])
        {
            if (first[0] == 0)
                score += 8;
            if (first[0x18] == 0)
                score += 16;
            if (third[0] == 0)
                score += 16;
            if (last[0] == 0)
                score += 16;
        }
        last += 256;
        third += 256;
        first += 256;
        i++;
    } while (i <= 2);
    *(u16 *)(work + 0x16C) += score * 2;
}

void sub_0801275C(void)
{
    u8 *work = gState0TransferWork.bytes;
    *(u16 *)(work + 0x16C) += work[0x16B] * 5;
}

void sub_0801277C(void)
{
    u32 i = 0;
    u32 score = 0;
    u8 *work = gState0TransferWork.bytes;
    u8 *buffer = gSetupBuffer_03000590;
    u8 *third = buffer + 0x382;
    u8 *first = buffer + 0x352;
    u8 *active = buffer + 0x3BA;
    do
    {
        if (*active)
        {
            score += first[0];
            score += first[0x18];
            score += third[0];
            score += third[0x18];
        }
        third += 256;
        first += 256;
        active += 256;
        i++;
    } while (i <= 2);
    *(u16 *)(work + 0x16C) += score;
}
