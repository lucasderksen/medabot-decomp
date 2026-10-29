#include "state0_next_helpers.h"
#include "state0_work.h"

void sub_080335A0(void)
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
    entry += 0xBA;
    if (*entry != 2)
        work[0x51] = 1;
}

void sub_08033618(void)
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
    entry += 0x58;
    if (*entry == 0)
        work[0x51] = 1;
}

void sub_08033658(void)
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
    entry += 0xC1;
    if (*entry == 0)
        work[0x51] = 1;
}

void sub_080335E0(void)
{
    u32 base = (u32)gSetupBuffer_03000590;
    u8 *work = gState0TransferWork.bytes;
    u8 *selected = work + 0x5D;
    s32 offset = *selected * 24;
    u8 *side = work + 0x5C;
    u32 sideIndex = *side;
    u8 *entry = (void *)(offset + sideIndex * 256 + base);
    u32 linked;
    entry += 0x56;
    linked = *entry - 1;
    if (linked == sideIndex)
        work[0x51] = 1;
}

void sub_08033698(void)
{
    u8 *work = gState0TransferWork.bytes;
    u8 *side = work + 0x5C;
    if (work[sub_0801554C(*side, 1) * 8 + 0x2A] == 0 ||
        work[sub_0801554C(*side, 1) * 8 + 0x2B] != 0x33)
        work[0x51] = 1;
}
