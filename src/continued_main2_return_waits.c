#include "global.h"
#include "gba.h"
#include "main.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "object_helpers.h"
#include "frame_objects.h"
#include "graphics.h"
#include "display_effects.h"
#include "effect_work.h"
#include "audio.h"
#include "serial.h"
#include "main_callbacks.h"

/* Partial access view only; backing extent/original declaration is unknown. */
struct Main2ReturnWork
{
    u8 unknown00[0x2A];
    u8 byte2A;
    u8 unknown2B[0x59];
    u8 phase;
};
#define WORK ((struct Main2ReturnWork *)gUnknown_03000440)
#define CONTEXT_HALFWORDS ((u16 *)gMainContextPointer_03006F74)
#define MAIN_FLAGS_BYTE (*(u8 *)&gMainFlagsWord_03001784)
#define DISPCNT (*(volatile u16 *)0x04000000)

void sub_0805DB20(void)
{
    if (sub_0803FB3C(gMain2ScriptSlots_08485678[18]))
    {
        sub_080415E8(1, 22, 7);
        gUnknown_0300137C++;
    }
}

void sub_0805DB4C(void)
{
    if (sub_08041674())
    {
        sub_0803FB0C();
        if (!WORK->byte2A)
            gUnknown_0300137C = 6;
        else
            gUnknown_0300137C = 9;
    }
}

void sub_0805DB84(void)
{
    if (sub_0803FB3C(gMain2ScriptSlots_0848521C[10]))
    {
        sub_08074B88(0);
        sub_08074DE0(0);
        Unknown_0805DEB0();
        CONTEXT_HALFWORDS[1] = 0;
        gUnknown_0300137C++;
    }
}

void sub_0805DC4C(void)
{
    u8 previous = CONTEXT_HALFWORDS[1]++;
    if (sub_0803FB3C(gMain2ScriptSlots_0848521C[11]) && previous > 60)
        gUnknown_0300137C++;
}

void sub_0805DC88(void)
{
    sub_0803FB0C();
    SnapshotPalettes();
    WORK->phase = 0;
    gUnknown_0300137C++;
}

void sub_0805DCB0(void)
{
    if (sub_08041CA4())
        gUnknown_0300137C++;
}

void sub_0805DCCC(void)
{
    if (WORK->phase <= 8)
    {
        sub_0803F684(0, WORK->phase * 4, 0x3FFF);
        sub_0803F998(0, WORK->phase * 4, 0xFFFF);
        WORK->phase++;
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

void sub_0805DD50(void)
{
    u8 previous = CONTEXT_HALFWORDS[1]++;
    if (sub_0803FB3C(gMain2ScriptSlots_0848521C[12]) && previous > 60)
        gUnknown_0300137C = 9;
}
