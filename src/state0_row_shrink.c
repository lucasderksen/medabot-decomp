#include "state0_next_helpers.h"
#include "frame.h"
#include "frame_objects.h"

void sub_080101E8(void)
{
    gFrameObjects[4].scaleX -= 8;
    gFrameObjects[4].scaleY -= 8;
    if (!gFrameObjects[4].scaleX)
    {
        sub_08040D0C(4, 1);
        gFrameObjects[4].unknown23[6]++;
    }
}
