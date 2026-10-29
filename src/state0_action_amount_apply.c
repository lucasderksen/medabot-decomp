#include "global.h"
#include "state0_work.h"

/* Observed physical field only; original setup allocation is unknown. */
struct ObservedActionAmountRecord { u8 unknown00[0x59]; u8 amount59; };

void sub_08035164(u32 row, u32 index, s32 amount)
{
    u32 baseWord = (u32)gSetupBuffer_03000590;
    u32 scaled = index * 3;
    struct ObservedActionAmountRecord *record;
    s32 available;
    scaled *= 8;
    row *= 256;
    scaled += row;
    scaled += baseWord;
    record = (struct ObservedActionAmountRecord *)scaled;
    available = record->amount59;
    if (available < amount)
        record->amount59 = 0;
    else
        record->amount59 = (u32)available - (u32)amount;
}
