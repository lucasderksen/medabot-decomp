#include "input.h"
#include "continued_late_graphics.h"

struct HeldKeyBytes { u8 low; u8 high; };

void sub_08058AB8(u32 index, s32 limit)
{
    s32 amount = 1;
    u8 keys;
    u16 *destination;
    s32 value;
    if (((struct HeldKeyBytes *)&gHeldKeys)->high & 1)
        amount = 16;
    keys = *(u8 *)&gRepeatedKeys;
    if (keys & KEY_LEFT)
    {
        destination = gNavigationHalfwordPointers_083D6268[index];
        value = *destination;
        value -= amount;
        if (value == -1)
            value = limit - 1;
    }
    else
    {
        u32 right = KEY_RIGHT;
        right &= keys;
        if (!right)
            return;
        destination = gNavigationHalfwordPointers_083D6268[index];
        value = *destination;
        value += amount;
        if (value >= limit)
            value = 0;
    }
    *destination = value;
}

