#include "continued_commands.h"
#include "frame.h"
#include "bg_scroll.h"

extern u8 gUnknown_030057E0[];

void sub_08053108(void)
{
    u8 *objects = (u8 *)gFrameObjects;
    u8 *work = gUnknown_030057E0;
    u16 *position = (u16 *)(work + 0xC6E);
    struct BgScroll *scroll = &gBgScroll1;
    u32 x = *position - scroll->x;
    u32 y;
    *(u16 *)(objects + 0xC02) = x;
    y = *(u16 *)(work + 0xC70) - scroll->y;
    *(u16 *)(objects + 0xC04) = y;
    *(u16 *)(objects + 0x1682) = x;
    y -= 5;
    *(u16 *)(objects + 0x1684) = y;
}
