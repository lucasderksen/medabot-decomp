#include "state0_next_helpers.h"
#include "state0_work.h"
#include "frame.h"

void sub_08010040(void)
{
    gFrameObjects[4].flags = 0xD204;
    gFrameObjects[4].screenX = 168;
    gFrameObjects[4].screenY = gState0TypedWork.bytes[0x4A] * 16 + 56;
    gFrameObjects[4].frameAndGroup = 0x307;
    gFrameObjects[4].palette = 14;
    gFrameObjects[4].scaleX = 64;
    gFrameObjects[4].scaleY = 64;
    gFrameObjects[4].tableSelector = 0;
    gFrameObjects[4].unknown23[6] = 0;
    gFrameObjects[4].unknown23[4] = 0;
    gFrameObjects[4].priority = 193;
}
