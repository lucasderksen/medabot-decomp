#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_callbacks.h"
#include "frame.h"
#include "input.h"

void sub_080100BC(void)
{
    if (*(u8 *)&gRepeatedKeys & 64)
    {
        if (!gState0TypedWork.bytes[0x4A])
            gState0TypedWork.bytes[0x4A] = 2;
        else
            gState0TypedWork.bytes[0x4A]--;
    }
    if (*(u8 *)&gRepeatedKeys & 128)
    {
        if (gState0TypedWork.bytes[0x4A] == 2)
            gState0TypedWork.bytes[0x4A] = 0;
        else
            gState0TypedWork.bytes[0x4A]++;
    }
    if (*(u8 *)&gRepeatedKeys & 192)
    {
        sub_08074DE0(2);
        gFrameObjects[4].screenY = gState0TypedWork.bytes[0x4A] * 16 + 56;
    }
}
