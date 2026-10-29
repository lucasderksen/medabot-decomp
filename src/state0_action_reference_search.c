#include "state0_next_helpers.h"
#include "state0_work.h"

/* Full observed word slots; original complete RAM extent unknown. */
u32 sub_08037830(u32 first, u32 second)
{
    u32 selected = sub_08033074();
    u32 forward = sub_080424B8() & 1;
    u32 tested = 0;
    u8 *entries = gSetupBuffer_03000590;
    u8 *comparison = entries + second * 256 + 0x91;
    do {
        u32 row = first + selected;
        u8 *base = (u8 *)(row * 256 + (u32)entries);
        if (base[0x40] && base[0x91] == *comparison)
            return row;
        if (forward) {
            selected++;
            if (selected > 2)
                selected = 0;
        } else {
            if (selected == 0)
                selected = 2;
            else
                selected--;
        }
        tested++;
    } while (tested <= 2);
    return 255;
}
