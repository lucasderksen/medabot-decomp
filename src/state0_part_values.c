#include "state0_work.h"
#include "state0_next_helpers.h"
#include "state0_callbacks.h"
#include "tile_text.h"

void sub_0800FA7C(void)
{
    u8 *work = gState0TypedWork.bytes;
    switch (work[0x3E])
    {
    case 0:
    {
        u8 first = work[0xF2];
        volatile u16 *control = (volatile u16 *)0x0400000A;
        sub_08042838(first, 26, 6, 3, *control, 0x53C4);
        sub_08042838(work[0xF3], 26, 7, 3, *control, 0x53C4);
        sub_08042838(work[0xF4], 26, 8, 3, *control, 0x53C4);
        sub_08042838(work[0xF6], 26, 9, 3, *control, 0x53C4);
        if (work[0xF5])
            sub_08042698(2, 1, 25, 8, *control, 0x5384);
        else
            sub_0803EF8C(2, 1, 25, 8, *control, 0);
        break;
    }
    case 1:
    case 2:
    {
        u8 first = work[0xF2];
        volatile u16 *control = (volatile u16 *)0x0400000A;
        sub_08042838(first, 26, 6, 3, *control, 0x53C4);
        sub_08042838(work[0xF3], 26, 7, 3, *control, 0x53C4);
        sub_08042838(work[0xF4], 26, 8, 3, *control, 0x53C4);
        sub_08042838(work[0xF6], 26, 9, 3, *control, 0x53C4);
        sub_08042838(work[0xF7], 26, 10, 3, *control, 0x53C4);
        if (work[0xF5])
            sub_08042698(2, 1, 25, 8, *control, 0x5384);
        else
            sub_0803EF8C(2, 1, 25, 8, *control, 0);
        break;
    }
    case 3:
    {
        u8 first = work[0xF2];
        volatile u16 *control = (volatile u16 *)0x0400000A;
        sub_08042838(first, 26, 6, 3, *control, 0x53C4);
        sub_08042838(work[0xF3], 26, 7, 3, *control, 0x53C4);
        sub_08042838(work[0xF4], 26, 8, 3, *control, 0x53C4);
        sub_08042838(work[0xF5], 26, 9, 3, *control, 0x53C4);
        sub_08042838(work[0xF6], 26, 10, 3, *control, 0x53C4);
        sub_08042838(work[0xF7], 26, 11, 3, *control, 0x53C4);
        break;
    }
    }
}
