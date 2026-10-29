#include "global.h"
#include "main.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "main_callbacks.h"

#define MAIN2_FIRST_BYTE (*(u8 *)gMainContextPointer_03006F74)
#define BLEND_BRIGHTNESS (*(volatile u16 *)0x04000054)

void sub_0805C950(void)
{
    u32 zero = 0;
    sub_08074B88(0);
    sub_08074DE0(0);
    gMainState = 1;
    gMainSubstate = 1;
    gUnknown_0300137C = zero;
    sub_080476E8(11);
}

void sub_0805C988(void)
{
    if (MAIN2_FIRST_BYTE != 32)
    {
        MAIN2_FIRST_BYTE++;
        BLEND_BRIGHTNESS = MAIN2_FIRST_BYTE >> 1;
    }
    else
    {
        gMainSubstate = 9;
        gUnknown_0300137C = 0;
    }
}
