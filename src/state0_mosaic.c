#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_callbacks.h"

void sub_08010328(void)
{
    *(volatile u16 *)0x0400004C = gState0TypedWork.bytes[0x84] + (gState0TypedWork.bytes[0x84] << 4);
    gState0TypedWork.bytes[0x84] += 2;
    if (gState0TypedWork.bytes[0x84] == 16)
        gUnknown_0300137C = 5;
}

void sub_08010358(void)
{
    gState0TypedWork.bytes[0x84] = 16;
    gUnknown_0300137C++;
}

void sub_08010374(void)
{
    gState0TypedWork.bytes[0x84] -= 2;
    *(volatile u16 *)0x0400004C = gState0TypedWork.bytes[0x84] + (gState0TypedWork.bytes[0x84] << 4);
    if (!gState0TypedWork.bytes[0x84])
        gUnknown_0300137C = 5;
}
