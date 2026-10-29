#include "continued_commands.h"
#include "frame.h"
#include "later_graphics.h"

extern u8 gLaterBuffer_03006D20[];

void sub_08050C94(void)
{
    s32 index;
    sub_08049714(gFrameObjects, 0xA00);
    sub_08049318();
    for (index = 0; index < 32; index++)
        sub_08049374((u8)index);
}

void sub_08050CC0(void)
{
    gLaterBuffer_03006D20[11] = 0;
}
