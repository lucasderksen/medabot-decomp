#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_callbacks.h"
#include "state0_inventory.h"
#include "frame_objects.h"
#include "object_helpers.h"
#include "tile_text.h"

void sub_0800EE34(void)
{
    u32 i = 0;
    u8 *parts = gObjectHalfwordBytes;
    u8 *work = gState0TypedWork.bytes;
    u8 *status = &work[0xF1];
    u32 row = 5;
    volatile u16 *control = (volatile u16 *)0x0400000A;
    for (; i < 4; row += 2, i++)
    {
        u32 group = work[0x3E];
        u32 offset = group * 240;
        u32 page = work[0x3F];
        u32 part = page * 4;
        offset += part * 2;
        offset += i * 2;
        if (parts[offset])
        {
            sub_08042B58(part + i, group, &work[0xEE]);
            if (*status)
                sub_08042698(2, 2, 27, row, *control, 0xA354);
            else
                sub_08042698(2, 2, 27, row, *control, 0xA350);
        }
        else
            sub_0803EF8C(2, 2, 27, row, *control, 0);
    }
}
