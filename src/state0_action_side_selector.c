#include "global.h"
#include "state0_next_helpers.h"

u32 GetOtherSlotGroupStart(u32 first)
{
    if (first > 2)
        first = 0;
    else
        first = 3;
    return first;
}

