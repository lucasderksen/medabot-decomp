#include "frame_objects.h"
#include "display_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_next_helpers.h"
/* Physical access coverage only, not the original object type or size. */
struct ObservedActionWork {
    u8 unknown00[0x87];
    u8 selected87;
    u8 unknown88[0x56];
    u8 selectedDE;
};


void sub_08033A2C(void)
{
    u8 *setup = gSetupBuffer_03000590;
    struct ObservedActionWork *work = (void *)gState0TransferWork.bytes;
    if (!setup[work->selected87 * 256 + 0xE0])
        sub_08035478(work->selected87);
    if (!setup[work->selected87 * 256 + 0xE1])
        sub_08035528(work->selected87);
    sub_080355C4(work->selected87);
    sub_08034F08();
}

