#include "global.h"
#include "gba.h"
#include "main.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "object_helpers.h"
#include "frame_objects.h"
#include "display_effects.h"
#include "effect_work.h"
#include "bg_scroll.h"
#include "main_callbacks.h"
struct Main2PhaseWork { u8 unknown00[0x84]; u8 phase; };
#define PHASE_WORK ((struct Main2PhaseWork *)gUnknown_03000440)
#define CONTEXT ((u8 *)gMainContextPointer_03006F74)
#define DISPCNT (*(volatile u16 *)0x04000000)

void sub_0805D658(void)
{
    if (sub_08041CA4())
        gUnknown_0300137C++;
}

void sub_0805D674(void)
{
    if (PHASE_WORK->phase <= 8)
    {
        sub_0803F684(0, PHASE_WORK->phase * 4, 0xFFFF);
        sub_0803F998(0, PHASE_WORK->phase * 4, 0xFFFF);
        PHASE_WORK->phase++;
    }
    else
    {
        u32 zero;
        DISPCNT &= 0xFDFF;
        zero = 0;
        CpuFastSet(&zero, (void *)0x06000000, 0x01006000);
        sub_080476E8(4);
    }
}

void sub_0805D6E4(u32 frameWord)
{
    u16 frame = frameWord;
    gFrameObjects[0].frameAndGroup = gMain2FrameChoices_080AF958[frame & 3];
}

void sub_0805D704(void)
{
    const MainCallback *callbacks = gMain2Subcallbacks_0848360C + 25;
    callbacks[gUnknown_0300137C]();
    if (gFrameCounter & 1)
    {
        gBgScroll3.x++;
        gBgScroll3.y++;
    }
    sub_0805D6E4((u16)(gFrameCounter >> 3));
}

void sub_0805D750(void)
{
    u32 zero = 0;
    CpuFastSet(&zero, CONTEXT, 0x01000100);
    sub_080415BC();
    DISPCNT = 0x0160;
    gUnknown_0300137C++;
}

void sub_0805DAB0(void)
{
    if (sub_0803FB3C(gMain2ScriptSlots_0848521C[9]))
        gUnknown_0300137C++;
}
