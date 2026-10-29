#include "global.h"
#include "gba.h"
#include "main.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "object_helpers.h"
#include "frame_objects.h"
#include "display_effects.h"
#include "equipment_helpers.h"
#include "main_callbacks.h"

#define CONTEXT ((u8 *)gMainContextPointer_03006F74)
#define DISPLAY_CONTROL (*(volatile u16 *)0x04000000)

void sub_0805CB90(u32 frameWord)
{
    u8 *context = CONTEXT;
    if (context[0x12])
    {
        if (context[0x13] >= context[0x11] && context[0x13] < context[0x11] + 5)
        {
            if (frameWord & 1)
                gFrameObjects[84].flags &= 0xBFFF;
            else
                gFrameObjects[84].flags |= 0x4000;
        }
        else
            gFrameObjects[84].flags &= 0xBFFF;
    }
}
