#include "state0_next_helpers.h"
#include "state0_work.h"


void sub_08033364(void)
{
    u8 *work = gState0TransferWork.bytes;
    u32 side = sub_0801554C(work[0x5C], 0);
    u8 *entry = work + side * 8;
    entry += 0x2A;
    if (*entry == 0)
        work[0x51] = 1;
}


void sub_080333D4(void)
{
    gState0TransferWork.bytes[0x51] = 1;
}



u32 sub_0801554C(u32 first, u32 second)
{
    if (second == 0)
    {
        if (first <= 2)
            return 0;
        else
            return 1;
    }
    else
    {
        if (first <= 2)
            return 1;
        else
            return 0;
    }
}

u32 sub_08032FC4(u32 first)
{
    if (first <= 2)
        return 0;
    return 3;
}
