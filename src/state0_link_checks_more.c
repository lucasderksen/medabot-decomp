#include "state0_next_helpers.h"
#include "state0_work.h"

void sub_08033394(void)
{
    u32 base = (u32)gSetupBuffer_03000590;
    u8 *work = gState0TransferWork.bytes;
    u8 *entry;
    u32 linked;
    {
        s32 offset = work[0x5D] * 24 + work[0x5C] * 256;
        u8 *record = (void *)(offset + base);
        record += 0x56;
        linked = *record - 1;
    }
    entry = (void *)(linked * 256 + base);
    entry += 0xC9;
    if (*entry == 0)
        work[0x51] = 1;
}

void sub_08033490(void)
{
    u32 base = (u32)gSetupBuffer_03000590;
    u8 *work = gState0TransferWork.bytes;
    u8 *entry;
    u32 linked;
    {
        s32 offset = work[0x5D] * 24 + work[0x5C] * 256;
        u8 *record = (void *)(offset + base);
        record += 0x56;
        linked = *record - 1;
    }
    entry = (void *)(linked * 256 + base);
    entry += 0xC4;
    if (*entry != 0 || sub_080331F8(linked) == 0)
        work[0x51] = 1;
}
