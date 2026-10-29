#include "state0_next_helpers.h"
#include "state0_work.h"

u32 sub_080331F8(u32 first)
{
    u32 index = 0;
    u32 base = (u32)gSetupBuffer_03000590;
    u32 offset = first * 256;
    u8 *entry;
    base += 0x49;
    entry = (u8 *)(offset + base);
    do
    {
        if (entry[0x10] != 0 && *entry == 0x16)
            return 0;
        entry += 24;
        index++;
    } while (index <= 2);
    return 1;
}

void sub_08033550(void)
{
    u32 base = (u32)gSetupBuffer_03000590;
    u8 *work = gState0TransferWork.bytes;
    u32 recordOffset = work[0x5D] * 24 + work[0x5C] * 256;
    u8 *entry = (u8 *)(recordOffset + (u32)base);
    u8 *selected = entry;
    u32 offset;
    u8 *link;
    selected += 0x57;
    offset = (*selected - 1) * 24;
    entry += 0x56;
    offset += (*entry - 1) * 256;
    link = (u8 *)(offset + base);
    link += 0x59;
    if (*link != 0)
        work[0x51] = 1;
}
