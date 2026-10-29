#include "state0_work.h"
#include "state0_next_helpers.h"
#include "state0_next_helpers.h"

void sub_08015564(u32 first, u32 second)
{
    u8 *base = gSetupBuffer_03000590;
    u32 offset = first * 256;
    u8 *record = base + offset;
    record[0xDD] = second;
    if (second == 0)
        return;
    if (second <= 3)
    {
        u8 *pair;
        u8 value;
        second--;
        pair = (u8 *)(second * 24 + offset + (u32)base);
        value = pair[0x56];
        record[0xE0] = value;
        value = pair[0x57];
        record[0xE1] = value;
    }
}
