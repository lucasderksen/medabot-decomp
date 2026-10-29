/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "frame.h"
#include "frame_objects.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_work.h"

struct ObservedActionWorkBacking { u8 unknown00[0xAA]; u8 stateAA; };
struct ObservedActionFrameBacking
{
    u8 unknown000[0x842];
    u16 screenX842;
    u8 unknown844[4];
    u8 scaleX848;
    u8 unknown849[0x19];
    u8 commandStopped862;
};


void sub_080213E4(void);

void sub_080213E4(void) {
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
