#include "state0_next_helpers.h"
#include "state0_work.h"
#include "continued_late_graphics.h"
#include "object_helpers.h"
#include "state0_callbacks.h"



u32 sub_08015648(u32 first)
{
    if (first <= 2 || gUnknown_030057E0[0x7FF] > 2)
        return 0;
    return 1;
}

void sub_080156D0(void)
{
    u32 offset = (sub_080424B8() & 31) * 4;
    sub_08041D04(gState0PriorityTable_083AD470 + offset,
                gState0TransferWork.bytes + 0x64, 4);
}

u32 sub_080156F8(u32 first, u32 second)
{
    if (sub_080154E0(first, second) == 0 &&
        sub_08015508(first, second) == 0 &&
        sub_08015528(first, second) == 0 &&
        sub_08033318(first, second) == 0)
        return 0;
    return 1;
}
