#include "global.h"
#include "gba.h"
#include "frame.h"
#include "frame_objects.h"
#include "object_helpers.h"
#include "main.h"
#include "main_callbacks.h"
#include "bg_scroll.h"
#include "continued_late_graphics.h"


void sub_0805E2D8(u32 word)
{
    u16 value = word;
    gFrameObjects[20].frameAndGroup = gMain2FrameChoices_080AF980[value & 3];
}

u32 sub_0805E300(const u8 *source)
{
    u32 width = 0;
    s32 count = 0;
    while (count < 10 && *source != 0xFE)
    {
        width += gGlyphMetrics_083B4E08[*source * 2];
        source++;
        count++;
    }
    return width;
}

void sub_0805E404(void)
{
    gMain2SaveCallbacks_084836D8[gUnknown_0300137C]();
    if (gFrameCounter & 1)
    {
        gBgScroll3.x++;
        gBgScroll3.y++;
    }
    sub_0805E2D8((u16)(gFrameCounter >> 3));
}

void sub_0805E450(void)
{
    sub_08040CD0(0, 128);
    sub_080415BC();
    *(volatile u16 *)0x04000000 = 0x60;
    gUnknown_0300137C++;
}
