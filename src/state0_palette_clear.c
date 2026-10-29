#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_callbacks.h"
#include "gba.h"


void sub_0801053C(void)
{
    u32 first;
    u32 second;
    sub_08011DB0();
    gState0TypedWork.bytes[0x132] = 0;
    first = 0;
    CpuFastSet(&first, (void *)0x05000200, 0x01000080);
    second = 0;
    CpuFastSet(&second, (void *)0x05000000, 0x01000080);
    gUnknown_0300137C++;
}
