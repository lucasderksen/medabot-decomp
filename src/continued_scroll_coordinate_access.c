#include "global.h"
#include "continued_commands.h"
#include "bg_scroll.h"

extern u8 gUnknown_030057E0[];

void sub_08052A10(u32 valueWord)
{
    u16 value = valueWord;
    gBgScroll1.x = value;
    gBgScroll2.x = value;
    gBgScroll3.x = value;
}

void sub_08052A30(u32 valueWord)
{
    u16 value = valueWord;
    gBgScroll1.y = value;
    gBgScroll2.y = value;
    gBgScroll3.y = value;
}

u32 sub_08052A50(void)
{
    u32 address = (u32)gUnknown_030057E0;
    u32 offset = 0xC48;
    return *(u16 *)(address + offset);
}

u32 sub_08052A64(void)
{
    u32 address = (u32)gUnknown_030057E0;
    u32 offset = 0xC4A;
    return *(u16 *)(address + offset);
}
