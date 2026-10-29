#include "input.h"
#include "continued_late_graphics.h"

void sub_08058B28(u32 index, s32 limit)
{
    u8 keys = *(u8 *)&gRepeatedKeys;
    u8 left = keys & KEY_LEFT;
    u8 *destination;
    if (left)
    {
        destination = gNavigationBytePointers_083D6274[index];
        *destination -= 1;
        if ((s8)*destination == -1)
            *destination = limit - 1;
    }
    else
    {
        u32 right = KEY_RIGHT;
        right &= keys;
        if (right)
        {
        destination = gNavigationBytePointers_083D6274[index];
        *destination += 1;
        if (*destination >= limit)
            *destination = 0;
        }
    }
}

