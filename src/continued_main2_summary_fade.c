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
#include "record_helpers.h"
#include "compression.h"
#include "state0_inventory.h"
#include "equipment_helpers.h"
#include "main_callbacks.h"
struct Main2PhaseWork { u8 unknown00[0x84]; u8 phase; };
#define PHASE_WORK ((struct Main2PhaseWork *)gUnknown_03000440)
#define CONTEXT ((u8 *)gMainContextPointer_03006F74)
#define DISPCNT (*(volatile u16 *)0x04000000)

void sub_0805DA14(void)
{
    if (PHASE_WORK->phase <= 8)
    {
        u32 scaledPhase = PHASE_WORK->phase * 4;
        u32 weight = 32;
        sub_0803F684(0, weight - scaledPhase, 0x3FFF);
        weight -= PHASE_WORK->phase * 4;
        sub_0803F998(0, weight, 0xFFFF);
        PHASE_WORK->phase++;
        if (PHASE_WORK->phase == 1)
        {
            DISPCNT |= 0x0200;
            DISPCNT |= 0x0400;
            DISPCNT |= 0x0800;
            DISPCNT |= 0x1000;
        }
    }
    else
    {
        sub_0803FAA0(1, 2, 0);
        gUnknown_0300137C++;
    }
}
