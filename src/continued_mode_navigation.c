#include "continued_late_graphics.h"
#include "input.h"

void sub_080589A4(s32 count)
{
    u32 up = *(u8 *)&gRepeatedKeys & KEY_UP;
    u8 *keys = (u8 *)&gRepeatedKeys;
    if (up)
    {
        u8 *work = gContinuedOtherWork_030057A0;
        u8 selected = work[0x14];
        s8 *modes = (s8 *)(work + 0x16);
        modes[selected]--;
        if (modes[work[0x14]] < 0)
            modes[work[0x14]] = count - 1;
    }
    if (*keys & KEY_DOWN)
    {
        u8 *work = gContinuedOtherWork_030057A0;
        u8 selected = work[0x14];
        s8 *modes = (s8 *)(work + 0x16);
        modes[selected]++;
        if (modes[work[0x14]] >= count)
            modes[work[0x14]] = 0;
    }
}

