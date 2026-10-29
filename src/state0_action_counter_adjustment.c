#include "compression.h"
#include "frame_objects.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_next_helpers.h"

/* Only observed physical object33 accesses, over the canonical array backing. */
struct ObservedActionFrameBacking
{
    u8 unknown000[0x840];
    u16 flags840;
    u16 screenX842;
    u16 screenY844;
    u16 frame846;
    u8 scaleX848;
    u8 scaleY849;
    u8 palette84A;
    u8 priority84B;
    u8 unknown84C[0x10];
    u8 table85C;
    u8 unknown85D[6];
    u8 byte863;
};

struct ObservedCounterAccess { u8 unknown00[0x2C]; u8 byte2C; };

void sub_0801CF78(void)
{
    u8 *work = gState0TransferWork.bytes;
    if (work[0x51] != 2)
    {
        u8 *setup = gSetupBuffer_03000590;
        u32 amount = setup[work[0x87] * 256 + 0xA2] >> 1;
        struct ObservedCounterAccess *entry = (void *)&work[work[0x89] * 8];
        u32 value = entry->byte2C;
        if (amount >= value)
            work[0xAA]++;
        else
        {
            entry->byte2C = value - amount;
            work[0xAA] = 45;
        }
    }
    else
    {
        u8 *selected = &work[0x89];
        work[*selected * 8 + 0x2C]--;
        if (work[*selected * 8 + 0x2C] == 0)
            work[0xAA]++;
        else
            work[0xAA] = 46;
    }
}
