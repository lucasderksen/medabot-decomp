#include "state0_next_helpers.h"
#include "state0_work.h"
#include "equipment_helpers.h"

/* Partial physical accumulator view; full RAM object size is unknown. */
struct ObservedActionAccumulator {
    u8 unknown00[0xEC];
    s16 valueEC;
};

void sub_08035BD4(void)
{
    struct ObservedActionAccumulator *work = (void *)gState0TransferWork.bytes;
    if (work->valueEC <= 2)
        work->valueEC += sub_080424B8() & 3;
}

void sub_08035BFC(u32 selected, u32 index)
{
    struct ObservedActionAccumulator *work = (void *)gState0TransferWork.bytes;
    s32 initial = work->valueEC;
    u32 base = (u32)gSetupBuffer_03000590;
    u32 offset = index * 24;
    u8 *entry;
    s32 quotient;
    offset += selected * 256;
    entry = (void *)(offset + base);
    entry += 0x54;
    quotient = initial / *entry;
    work->valueEC = quotient;
    if ((u16)quotient == 0)
        work->valueEC = 1;
}
