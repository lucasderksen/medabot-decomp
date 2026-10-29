#include "continued_commands.h"
#include "frame.h"
#include "continued_commands.h"
#include "packed_fields.h"
#include "later_graphics.h"
#include "post_dispatch.h"
#include "utility_helpers.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03006D20[];
extern void sub_08052E58(u32 first, u32 second, u32 mode);

void sub_0804CE90(void)
{
    u8 *work;
    u32 value;
    sub_0804D8CC(1);
    work = gUnknown_030057E0;
    value = work[0xC94];
    if (value & 0x80)
    {
        u32 low = 15;
        low &= value;
        if (low == 1)
            work[0xC5D] = (work[0xC5D] & 0xDF) | 0x20;
        else
            work[0xC5D] &= 0xDF;
    }
    else
    {
        u32 low = 15;
        low &= value;
        work[0xC33] = low;
    }
}

void sub_0804D094(void)
{
    u8 *work;
    u8 *action;
    u32 zero;
    sub_0804D8CC(2);
    work = gUnknown_030057E0;
    {
        s32 value = sub_0804DBF0(work[0xC94]);
        action = gLaterBuffer_03006D20;
        value += 79;
        zero = 0;
        action[10] = value;
    }
    gFrameObjects[action[10]].unknown23[3] = zero;
    work[0xC89] = 1;
}
