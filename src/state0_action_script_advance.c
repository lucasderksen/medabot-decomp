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

void sub_08034F08(void)
{
    struct ObservedActionCommandWork *work = (void *)gState0TransferWork.bytes;
    const u8 *script;
    u32 count;
    work->phaseAA = 0;
    script = gActionBytePointers_083C6CA8[work->scriptA8];
    count = gActionParameterLengths_083C6EB8[script[work->cursorBC]];
    work->cursorBC += count + 1;
}
