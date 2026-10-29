#include "global.h"
#include "continued_commands.h"

extern u8 gUnknown_030057E0[];

struct ActionWorkView
{
    u8 unknown00[0x7DC];
    u8 x;
    u8 y;
    u8 flags;
    u8 selector;
};

void sub_080506BC(void)
{
    s32 i;
    for (i = 0; i <= 5; i++)
    {
        u8 *base = gUnknown_030057E0;
        struct ActionWorkView *work = (struct ActionWorkView *)(base + i * 4);
        u32 flags = work->flags;
        if ((flags >> 7) && (s32)(flags << 25) >= 0)
            sub_080503FC((u8)i, work->selector, work->x, work->y);
    }
}
