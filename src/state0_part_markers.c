#include "state0_work.h"
#include "frame.h"
#include "main.h"

void sub_0800FCF0(void)
{
    if (gState0TypedWork.bytes[0x41] > 1)
    {
        gFrameObjects[1].flags = 0xC804;
        gFrameObjects[1].screenX = 12;
        gFrameObjects[1].screenY = 40;
        gFrameObjects[1].frameAndGroup = 0x302;
        gFrameObjects[1].palette = 14;
        gFrameObjects[1].tableSelector = 0;
        gFrameObjects[1].priority = 128;
        gFrameObjects[2].flags = 0xC804;
        gFrameObjects[2].screenX = 84;
        gFrameObjects[2].screenY = 40;
        gFrameObjects[2].frameAndGroup = 0x303;
        gFrameObjects[2].palette = 14;
        gFrameObjects[2].tableSelector = 0;
        gFrameObjects[2].priority = 128;
    }
}

void sub_0800FD74(void)
{
    if (gState0TypedWork.bytes[0x41] > 1)
    {
        if (gFrameCounter & 8)
        {
            gFrameObjects[1].flags &= 0xBFFF;
            gFrameObjects[2].flags &= 0xBFFF;
        }
        else
        {
            gFrameObjects[1].flags |= 0x4000;
            gFrameObjects[2].flags |= 0x4000;
        }
    }
}
