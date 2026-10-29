#include "state0_work.h"

u32 sub_08018EE0(u32 bank)
{
    u32 index = 0;
    u32 entry = (u32)gSetupBuffer_03000590;
    int differs;
    bank <<= 8;
    entry += 0x4C;
    entry += bank;
    do
    {
        /* Preserve the reference's separate zero-check and comparison reads. */
        if (*(volatile u8 *)(entry + 13) &&
            (differs = *(u8 *)entry != *(u8 *)(entry + 13)))
        {
            return index + 1;
        }
        entry += 24;
        index++;
    } while (index < 4);
    return 0;
}
