#include "state0_next_helpers.h"
#include "state0_work.h"
#include "global.h"
#include "state0_next_helpers.h"

void sub_08034728(void)
{
    u32 count = 0;
    u8 *entries = gSetupBuffer_03000590;
    u8 *selected = gState0TransferWork.bytes + 0x87;
    u32 row = *selected;
    u16 *sum = (void *)(selected + 0x65);
    row *= 256;
    entries += 0x4A;
    entries += row;
    do
    {
        if (entries[0xF])
        {
            u32 kind = entries[0];
            if (kind == 2)
                goto add;
            if (kind != 3)
                goto next;
add:
            *sum += entries[4];
        }
next:
        entries += 24;
        count++;
    } while (count <= 2);
    sub_08034F08();
}

void sub_080347BC(void)
{
    u32 count = 0;
    u16 *sum = (void *)(gState0TransferWork.bytes + 0xEC);
    u32 base = (u32)gSetupBuffer_03000590;
    u8 *selected = (u8 *)sum - 0x65;
    u32 row = *selected * 256;
    u8 *record;
    base += 0x4C;
    record = (void *)(row + base);
    do
    {
        s32 delta = record[0] - record[0xD];
        *sum += delta;
        record += 24;
        count++;
    } while (count <= 3);
    sub_08034F08();
}
