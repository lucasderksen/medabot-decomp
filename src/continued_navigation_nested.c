#include "input.h"
#include "continued_late_graphics.h"

void sub_08058B90(u32 category, u32 subindex, s32 limit)
{
    u8 *const *values;
    u32 changed = 0;
    u8 keys = *(u8 *)&gRepeatedKeys;
    if (keys & KEY_LEFT)
    {
        u8 *destination;
        s32 value;
        values = gNavigationNestedBytePointers_083D62C8[category];
        destination = values[subindex];
        value = *destination;
        value--;
        if (value == -1)
            value = limit - 1;
        *destination = value;
        changed = 1;
    }
    else
    {
        u32 right = KEY_RIGHT;
        right &= keys;
        if (right)
        {
            u8 *destination;
            s32 value;
            values = gNavigationNestedBytePointers_083D62C8[category];
            destination = values[subindex];
            value = *destination;
            value++;
            if (value >= limit)
                value = 0;
            *destination = value;
            changed = 1;
        }
    }
    if (changed && category == 5)
        sub_08059960();
}
