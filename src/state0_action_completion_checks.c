#include "state0_next_helpers.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "state0_next_helpers.h"

void sub_080337CC(void)
{
    u8 *work = gState0TransferWork.bytes;
    u32 outer;
    u8 *savedWork;
    u8 *entryBase;
    u32 base;
    u32 conditionBase;
    u32 offset;
    u32 stride;
    work[0x60] = sub_08032FC4(work[0x5C]);
    outer = 0;
    base = (u32)gSetupBuffer_03000590;
    offset = work[0x60];
    savedWork = work;
    offset *= 256;
    conditionBase = base + 0x40;
    work = (void *)(offset + conditionBase);
    entryBase = (void *)(base + 0x49);
    stride = 256;
    do
    {
        if (*work)
        {
            u32 inner = 0;
            u8 *entry = (void *)((gTransferByte_03001860 + outer) * 256 + (u32)entryBase);
            do
            {
                if (entry[0x10])
                {
                    u32 kind = entry[0];
                    if (kind == 0x34)
                        return;
                }
                entry += 24;
                inner++;
            } while (inner <= 2);
        }
        work += stride;
        outer++;
    } while (outer <= 2);
    savedWork[0x51] = 1;
}

void sub_080338DC(void)
{
    gMainSubstate = 8;
    gUnknown_0300137C = 0x40;
}

void sub_080338F4(void)
{
    volatile u8 complete = 0;
    sub_08034EB8();
    sub_08034F08();
    if (!complete)
    {
        const u8 *const *table = gActionBytePointers_083C6CA8;
        u8 *work = gState0TransferWork.bytes;
        u16 *position = (u16 *)(work + 0xBC);
        u8 *selected = work + 0xAC;
        do
        {
            const u8 *value = table[work[0xA8]];
            value += *position;
            if (*selected == *value)
            {
                sub_08034F08();
                complete = 1;
            }
            else
                sub_08034F08();
        } while (!complete);
    }
    gState0TransferWork.bytes[0x163] = 1;
}

void sub_08033974(void)
{
    volatile u8 complete = 0;
    sub_08034EB8();
    sub_08034F08();
    if (!complete)
    {
        const u8 *const *table = gActionBytePointers_083C6CA8;
        u8 *work = gState0TransferWork.bytes;
        u16 *position = (u16 *)(work + 0xBC);
        do
        {
            const u8 *value = table[work[0xA8]];
            u8 *index = work + 0xAB;
            u8 *selected = work + 0xAC;
            selected += *index;
            value += *position;
            if (*selected == *value)
            {
                sub_08034F08();
                complete = 1;
            }
            else
                sub_08034F08();
        } while (!complete);
    }
    gState0TransferWork.bytes[0x163] = 1;
}
