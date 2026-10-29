#include "continued_map_data.h"
#include "global.h"
#include "frame.h"
#include "bg_scroll.h"
#include "later_graphics.h"
#include "continued_commands.h"

extern u8 gUnknown_030057E0[];


void sub_0805330C(void)
{
    u8 *work = gUnknown_030057E0;
    sub_080497C0(gSceneEightByteRows_083D2A98 + work[0xC28] * 8,
                 work + 0xC10, 8);
    {
        struct FrameObject *objects = gFrameObjects;
        const u8 *lookup = gFrameByteLookup_083D2A88;
        work += 0xC5C;
        objects[47].unknown23[7] = lookup[*work];
    }
}

void sub_080533E4(u32 index, u32 x, u32 y, u32 mode)
{
    s32 i;
    u8 *base;
    sub_08049318();
    for (i = 0; i <= 31; i++)
        sub_08049374((u8)i);
    base = gLaterBuffer_03005350;
    sub_08049714(base, 0x240);
    *(u32 *)(base + 0x1D4) = index;
    if (index & 0x40)
    {
        u8 *work = gUnknown_030057E0;
        x = *(u16 *)(work + 0xC52);
        y = *(u16 *)(work + 0xC54);
    }
    *(u32 *)(base + 0x1D8) = x;
    *(u32 *)(base + 0x1DC) = y;
    *(u32 *)(base + 0x1E0) = mode;
}
