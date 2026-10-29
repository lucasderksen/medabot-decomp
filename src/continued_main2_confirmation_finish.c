#include "global.h"
#include "main.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "object_helpers.h"
#include "frame_objects.h"
#include "display_effects.h"
#include "effect_work.h"
#include "main_callbacks.h"

struct Main2PhaseWork { u8 unknown00[0x84]; u8 phase; };
#define PHASE_WORK ((struct Main2PhaseWork *)gUnknown_03000440)

#define CONTEXT ((u8 *)gMainContextPointer_03006F74)
#define DISPCNT (*(volatile u16 *)0x04000000)
#define BLDCNT (*(volatile u16 *)0x04000050)
#define BLDY (*(volatile u16 *)0x04000054)

void sub_0805D4A0(void)
{
    void **contextAddress = &gMainContextPointer_03006F74;
    struct FrameObject *object = &gFrameObjects[84];
    sub_0805B0B0(object);
    object->flags |= 0x4000;
    object->screenX++;
    object->screenY++;
    ((u8 *)*contextAddress)[0x12] = 1;
    ((u8 *)*contextAddress)[0x13] = ((u8 *)*contextAddress)[0xC];
}


void sub_0805D4E0(void)
{
    if (sub_08041CA4())
        gUnknown_0300137C++;
}


void sub_0805D4FC(void)
{
    if (PHASE_WORK->phase <= 8)
    {
        sub_0803F684(0, PHASE_WORK->phase * 4, 0x3FFF);
        sub_0803F998(0, PHASE_WORK->phase * 4, 0xFFFF);
        PHASE_WORK->phase++;
    }
    else
    {
        DISPCNT &= 0xFDFF;
        DISPCNT &= 0xFBFF;
        sub_08040CD0(0, 128);
        gMainState = 0;
        gMainSubstate = 1;
        gUnknown_0300137C = 16;
    }
}


void sub_0805D580(void)
{
    if (sub_0803FB3C(gMain2ScriptSlots_0848521C[8]))
        gUnknown_0300137C++;
}


void sub_0805D5A4(void)
{
    if (gUnknown_0300058C[0] & 3)
    {
        sub_08074DE0(2);
        sub_0803FB0C();
        gUnknown_0300137C = 4;
    }
}


void sub_0805D5D0(void)
{
    BLDCNT = 0x02FF;
    gUnknown_0300137C++;
}


void sub_0805D5F0(void)
{
    u8 *context = CONTEXT;
    u32 step = context[0];
    if (step != 8)
    {
        volatile u16 *blend = (volatile u16 *)0x04000054;
        step++;
        context[0] = step;
        *blend = (u8)step * 2;
    }
    else
    {
        DISPCNT &= 0xFDFF;
        DISPCNT &= 0xFBFF;
        sub_08040CD0(0, 128);
        {
            u8 *finalContext = CONTEXT;
            u32 zero = 0;
            finalContext[6] = 1;
            gMainSubstate = 10;
            gUnknown_0300137C = zero;
        }
    }
}
