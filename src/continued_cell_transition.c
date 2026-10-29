#include "continued_commands.h"
#include "later_graphics.h"

extern u8 gUnknown_030057E0[];

u32 sub_080525BC(u32 input)
{
    u8 direction = input;
    u8 *work = gUnknown_030057E0;
    u8 *selected = work + 0xC5C;
    u32 cell;
    u32 result;
    if (*selected == 2)
    {
        cell = (u8)sub_080524C8(direction);
        if (cell == 0 || cell == 2)
        {
            *selected = work[0xC69];
            sub_08051E38(0);
        }
    }
    cell = (u8)sub_080524C8(direction);
    {
        u32 address = (u32)gUnknown_030057E0;
        address += 0xC10;
        result = *(u8 *)(cell + address);
    }
    if (result)
        sub_08052E0C(direction);
    return result;
}
