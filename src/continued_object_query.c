#include "global.h"
#include "frame.h"

u32 sub_08050710(void)
{
    s32 i;
    for (i = 0; i <= 5; i++)
        if (!(gFrameObjects[i + 79].flags & 0x4000) && gFrameObjects[i + 79].unknown2C[2] == 0)
            break;
    if (i == 6)
        return 5;
    return i;
}
