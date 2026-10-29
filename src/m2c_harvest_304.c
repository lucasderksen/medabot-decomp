/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "frame.h"
#include "main.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"


void sub_08061860(void);

void sub_08061860(void) {

    u32 v;
    u8 w;
    sub_08060BE4((*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x19)), gFrameCounter * 2);
    v = (*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x48));
    w = v;
    if (w != 0) {
        (*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x48)) = (u8) (v - 1);
        return;
    }
    if (sub_08041CA4() != 0) {
        gState0TypedWork.bytes[0x84] = w;
        gUnknown_0300137C += 1;
    }
}
