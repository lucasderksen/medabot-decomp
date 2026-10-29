#include "global.h"
#include "main.h"
#include "bg_scroll.h"
#include "continued_late_graphics.h"
#include "main_callbacks.h"

void sub_0805C0D4(void)
{
    gMain2Subcallbacks_0848360C[gUnknown_0300137C]();
    gBgScroll2.x++;
    gBgScroll2.y++;
    if (gFrameCounter & 1)
    {
        gBgScroll3.x++;
        gBgScroll3.y++;
    }
}
