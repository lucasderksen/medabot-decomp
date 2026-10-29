#include "global.h"
#include "continued_commands.h"
#include "later_graphics.h"

extern u8 gUnknown_030057E0[];


void sub_0804D158(void)
{
    u8 *work;
    u8 *current;
    u8 *argument;
    u32 requested;
    sub_0804D8CC(2);
    work = gUnknown_030057E0;
    argument = work + 0xC94;
    current = work + 0xC5B;
    requested = *argument;
    if (requested == *current)
    {
        u32 changed = 1;
        changed ^= requested;
        *current = changed;
        sub_08052BEC(*current);
        if (work[0xC95] == 0)
        {
            u32 value = *current;
            if (value != 0)
                sub_080497C0(work + 0xC18, work + 0xC10, 8);
            else
            {
                u8 *destination = work + 0xC10;
                sub_080497C0(destination, work + 0xC18, 8);
                destination[0] = value;
                work[0xC11] = value;
                work[0xC12] = value;
                work[0xC13] = value;
                work[0xC14] = value;
                work[0xC15] = value;
                work[0xC16] = value;
                work[0xC17] = value;
            }
        }
    }
}
