#include "state0_work.h"
#include "state0_next_helpers.h"
#include "tile_text.h"

void sub_0800F8D8(void)
{
    u8 *work = gState0TypedWork.bytes;
    switch (work[0x3E])
    {
    case 0:
    {
        volatile u16 *control = (volatile u16 *)0x0400000A;
        sub_08042698(12, 1, 14, 6, *control, 0x5300);
        sub_08042698(12, 1, 14, 7, *control, 0x530C);
        sub_08042698(12, 1, 14, 8, *control, 0x5318);
        sub_08042698(12, 1, 14, 9, *control, 0x5324);
        break;
    }
    case 1:
    case 2:
    {
        volatile u16 *control = (volatile u16 *)0x0400000A;
        sub_08042698(12, 1, 14, 6, *control, 0x5300);
        sub_08042698(12, 1, 14, 7, *control, 0x530C);
        sub_08042698(12, 1, 14, 8, *control, 0x5318);
        sub_08042698(12, 1, 14, 9, *control, 0x5330);
        sub_08042698(12, 1, 14, 10, *control, 0x533C);
        break;
    }
    case 3:
    {
        volatile u16 *control = (volatile u16 *)0x0400000A;
        sub_08042698(12, 1, 14, 6, *control, 0x5300);
        sub_08042698(12, 1, 14, 7, *control, 0x5348);
        sub_08042698(12, 1, 14, 8, *control, 0x5354);
        sub_08042698(12, 1, 14, 9, *control, 0x5360);
        sub_08042698(12, 1, 14, 10, *control, 0x536C);
        sub_08042698(12, 1, 14, 11, *control, 0x5378);
        break;
    }
    }
}
