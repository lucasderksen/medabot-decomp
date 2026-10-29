#include "state0_next_helpers.h"
#include "frame.h"

void sub_08010170(void)
{
    if (gFrameObjects[4].unknown23[4] != 30)
    {
        if (gFrameObjects[4].unknown23[4] & 4)
            gFrameObjects[4].flags &= 0xBFFF;
        else
            gFrameObjects[4].flags |= 0x4000;
        gFrameObjects[4].unknown23[4]++;
    }
    else
    {
        gFrameObjects[4].flags |= 0x4000;
        gFrameObjects[4].unknown23[6]++;
    }
}
