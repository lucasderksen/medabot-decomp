#include "state0_next_helpers.h"
#include "state0_work.h"

void sub_08033F04(void)
{
    u8 *work = gState0TransferWork.bytes;
    if (work[0xDE] != 0 && work[0xDF] == 0x1D && work[0xB8] == 0)
    {
        s16 *value = (void *)(work + 0xEC);
        u32 base = (u32)gSetupBuffer_03000590;
        u32 row = work[0x88] * 256;
        u8 *entry = (void *)(row + base);
        entry += 0xD8;
        if (*value < *(s16 *)entry)
        {
            work[0xB8] = 2;
            work[0xBE] = 1;
        }
    }
    sub_08034F08();
}

void sub_08033F64(void)
{
    u8 *work = gState0TransferWork.bytes;
    if (work[0xDE] != 0 && work[0xDF] == 0x1C && work[0xB8] == 0)
    {
        work[0xB8] = 2;
        work[0xBE] = 5;
    }
    sub_08034F08();
}

void sub_08035754(s16 *value, s32 amount)
{
    if (*value < amount)
        *value = 0;
    else
        *value -= amount;
}

void sub_08035B9C(u32 selected)
{
    u32 index = 0;
    u32 base = (u32)gSetupBuffer_03000590;
    u16 *sum = (void *)(gState0TransferWork.bytes + 0xEC);
    u32 offset = selected * 256;
    u8 *entry;
    base += 0x49;
    entry = (void *)(offset + base);
    do
    {
        if (entry[0x10] != 0 && *entry == 0x35)
            *sum += entry[5];
        entry += 24;
        index++;
    } while (index <= 2);
}

