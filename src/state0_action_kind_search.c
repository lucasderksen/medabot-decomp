#include "state0_next_helpers.h"
#include "state0_work.h"

/* Observed full-word slots; original complete RAM extent is unknown. */
u32 sub_08037798(u32 first)
{
    u32 selected = sub_08033074();
    u32 forward = sub_080424B8() & 1;
    u32 tested = 0;
    u8 *entries = gSetupBuffer_03000590;
    do {
        u32 row = first + selected;
        u32 scaled = row * 256;
        u8 *base = (u8 *)(scaled + (u32)entries);
        if (base[0x40]) {
            u32 flags = base[0xBD];
            u32 checked;
            if ((flags & 8) ? (flags & 8) :
                ((checked = 16), (checked &= flags))) {
                u32 record = base[0xDE] - 1;
                if (entries[record * 24 + scaled + 0x59])
                    return row;
            }
        }
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
