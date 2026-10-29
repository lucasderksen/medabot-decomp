#include "state0_next_helpers.h"
#include "state0_work.h"

/* Observed fields only; byte output length/full RAM object extent unknown. */
struct ObservedActionCommandWork {
    u8 unknown00[0xA8];
    u8 scriptA8;
    u8 unknownA9;
    u8 phaseAA;
    u8 unknownAB;
    u8 unknownAC[0x10];
    u16 cursorBC;
};

void sub_08034EB8(void)
{
    const u8 *script = gActionBytePointers_083C6CA8[
        ((struct ObservedActionCommandWork *)gState0TransferWork.bytes)->scriptA8];
    struct ObservedActionCommandWork *work = (void *)gState0TransferWork.bytes;
    u32 count = gActionParameterLengths_083C6EB8[script[work->cursorBC]];
    u32 index = 0;
    for (; index < count; index++) {
        u32 outputBase = (u32)work + 0xAC;
        *(u8 *)(index + outputBase) = script[work->cursorBC + index + 1];
    }
}

