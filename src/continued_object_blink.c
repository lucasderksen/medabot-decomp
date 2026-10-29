#include "global.h"
#include "frame.h"
#include "continued_commands.h"
#include "packed_fields.h"
#include "later_graphics.h"

extern u8 gLaterBuffer_03006D20[];
extern u8 gUnknown_030057E0[];

struct BlinkFrameView
{
    u16 flags;
    u8 unknown02[0x2B];
    u8 unknown2D;
    u8 unknown2E[4];
    u16 savedFlags;
    u8 unknown34[12];
};

u32 sub_0805082C(u32 indexWord)
{
    u8 index = indexWord;
    u32 result = 0;
    u8 *initial = gLaterBuffer_03006D20;
    u8 phase = initial[0];
    u8 *work = initial;
    if (phase)
    {
        if (work[2])
            work[2]--;
        else
        {
            work[1]++;
            work[2] = work[3];
        }
        if (work[1] & 1)
        {
            struct BlinkFrameView *base = (struct BlinkFrameView *)gFrameObjects;
            base[index].unknown2D = 1;
            base[index].flags = 0;
        }
        else
        {
            struct BlinkFrameView *base = (struct BlinkFrameView *)gFrameObjects;
            base[index].unknown2D = 0;
            base[index].flags = base[index].savedFlags;
        }
        work[0]--;
    }
    else
    {
        struct BlinkFrameView *base = (struct BlinkFrameView *)gFrameObjects;
        base[index].unknown2D = 0;
        base[index].flags = base[index].savedFlags;
        result = 1;
    }
    return result;
}

