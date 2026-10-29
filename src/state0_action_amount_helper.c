#include "state0_next_helpers.h"
#include "state0_work.h"

/* Partial view of the observed stores; original work allocation is unknown. */
struct ObservedActionAmountWork {
    u8 unknown00[0xC8];
    u16 amountC8;
    u16 remainderCA;
    u16 amountCC;
    u8 unknownCE[3];
    u8 hasRemainderD1;
};

struct ObservedActionAmountRecord { u8 unknown00[0x59]; u8 amount59; };

void sub_08034F68(u32 row, u32 index, s32 amount)
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
    if (available > amount) {
        struct ObservedActionAmountWork *work = (void *)gState0TransferWork.bytes;
        work->amountC8 = amount;
        work->amountCC = amount;
        work->remainderCA = 0;
        work->hasRemainderD1 = 0;
    } else {
        struct ObservedActionAmountWork *work = (void *)gState0TransferWork.bytes;
        work->amountC8 = available;
        work->amountCC = available;
        work->remainderCA = amount - available;
        work->hasRemainderD1 = 1;
    }
}
