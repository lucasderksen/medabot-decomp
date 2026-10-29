#include "continued_commands.h"

extern u8 gUnknown_030057E0[];

u32 sub_0805273C(u32 input)
{
    u16 value = input;
    u8 *work = gUnknown_030057E0;
    s32 relative = value - *(u16 *)(work + 0xC48);
    return (u8)(relative / 16);
}

u32 sub_08052760(u32 input)
{
    u16 value = input;
    u8 *work = gUnknown_030057E0;
    s32 relative = value - *(u16 *)(work + 0xC4A);
    return (u8)(relative / 16);
}
