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

void sub_0805DBC4(void)
{
    u8 previous = CONTEXT_HALFWORDS[1]++;
    u16 result = 0;
    if (previous > 29 && !sub_08074FA4(4))
    {
        s8 attempt = 0;
        while (attempt <= 3)
        {
            result = sub_0805DDEC(0);
            if (!result)
                break;
            attempt = (u8)(attempt + 1);
        }
        sub_08074B88(6);
        if (!result)
        {
            sub_0803FB0C();
            CONTEXT_HALFWORDS[1] = result;
            gUnknown_0300137C++;
        }
        else
        {
            sub_0803FB0C();
            CONTEXT_HALFWORDS[1] = 0;
            gUnknown_0300137C = 12;
        }
    }
}
