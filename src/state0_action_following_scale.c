#include "bg_scroll.h"
#include "main.h"
#include "input.h"
#include "display_helpers.h"
#include "frame_objects.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_next_helpers.h"
struct ObservedActionWorkBacking { u8 unknown00[0xAA]; u8 stateAA; };


/* Partial backing access model over canonical objects; no new data extent. */
struct ObservedActionFrameBacking
{
    u8 unknown000[0x842];
    u16 screenX842;
    u8 unknown844[4];
    u8 scaleX848;
    u8 unknown849[0x19];
    u8 commandStopped862;
};

void sub_0801CA2C(void)
{
    struct ObservedActionFrameBacking *objects = (void *)gFrameObjects;
    if (objects->scaleX848 == 8)
    {
        struct ObservedActionWorkBacking *work;
        sub_08040CD0(33, 1);
        work = (void *)&gState0TransferWork;
        work->stateAA++;
    }
    else
        objects->scaleX848 -= 8;
}
