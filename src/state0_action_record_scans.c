#include "state0_work.h"
#include "state0_next_helpers.h"

void sub_080336DC(void)
{
    u8 *work = gState0TransferWork.bytes;
    u32 outer;
    u8 *savedWork;
    u8 *entryBase;
    u32 base;
    u32 conditionBase;
    u32 offset;
    u32 stride;
    work[0x60] = sub_08032FB8(work[0x5C]);
    outer = 0;
    base = (u32)gSetupBuffer_03000590;
    offset = work[0x60];
    savedWork = work;
    offset *= 256;
    conditionBase = base + 0x40;
    work = (void *)(offset + conditionBase);
    entryBase = (void *)(base + 0x4A);
    stride = 256;
    do
    {
        if (*work)
        {
            u32 inner = 0;
            u8 *entry = (void *)((gTransferByte_03001860 + outer) * 256 + (u32)entryBase);
            do
            {
                if (entry[0x0F])
                {
                    u32 kind = entry[0];
                    if (kind == 0)
                        return;
                    if (kind == 1)
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

void sub_08033754(void)
{
    u8 *work = gState0TransferWork.bytes;
    u32 outer;
    u8 *savedWork;
    u8 *entryBase;
    u32 base;
    u32 conditionBase;
    u32 offset;
    u32 stride;
    work[0x60] = sub_08032FB8(work[0x5C]);
    outer = 0;
    base = (u32)gSetupBuffer_03000590;
    offset = work[0x60];
    savedWork = work;
    offset *= 256;
    conditionBase = base + 0x40;
    work = (void *)(offset + conditionBase);
    entryBase = (void *)(base + 0x4A);
    stride = 256;
    do
    {
        if (*work)
        {
            u32 inner = 0;
            u8 *entry = (void *)((gTransferByte_03001860 + outer) * 256 + (u32)entryBase);
            do
            {
                if (entry[0x0F])
                {
                    u32 kind = entry[0];
                    if (kind == 2)
                        return;
                    if (kind == 3)
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
