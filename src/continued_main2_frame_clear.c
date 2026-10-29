#include "global.h"
#include "gba.h"
#include "main.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "frame.h"
#include "compression.h"
#include "bg_scroll.h"
#include "main_callbacks.h"

#define DISPLAY_CONTROL (*(volatile u16 *)0x04000000)

/* This partial view observes only the context halfword at 36. */
struct Main2TileContext
{
    u8 unknown00[0x36];
    u16 halfword36;
};

void sub_0805CB50(void)
{
    const MainCallback *callbacks = gMain2Subcallbacks_0848360C + 10;
    callbacks[gUnknown_0300137C]();
    if (gFrameCounter & 1)
    {
        gBgScroll3.x++;
        gBgScroll3.y++;
    }
}

void sub_0805CBFC(void)
{
    u32 fill = 0;
    CpuFastSet(&fill, gMainContextPointer_03006F74, 0x01000100);
    sub_080415BC();
    DISPLAY_CONTROL = 0x160;
    gUnknown_0300137C++;
}

