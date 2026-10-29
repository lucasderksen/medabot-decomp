#include "compression.h"
#include "frame_objects.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_next_helpers.h"

/* Observed physical object33 fields over the canonical backing, no extent claim. */
struct ObservedActionFrameBacking
{
    u8 unknown000[0x840];
    u16 flags840;
    u16 screenX842;
    u16 screenY844;
    u8 unknown846[4];
    u8 palette84A;
    u8 priority84B;
    u8 unknown84C[0x10];
    u8 table85C;
    u8 unknown85D[5];
    u8 commandStopped862;
};

void sub_0801CCB8(void)
{
    u8 *work = gUnknown_03000440;
    u8 *counter = &work[0x84];
    u8 phase = *counter;
    u16 *position = (u16 *)&work[0x86];
    sub_0803536C(33, phase, *position);
    (*counter)++;
    if (*counter == 90)
    {
        struct ObservedActionFrameBacking *objects = (void *)gFrameObjects;
        objects->screenX842 = *position;
        gState0TransferWork.bytes[0xAA]++;
    }
}
