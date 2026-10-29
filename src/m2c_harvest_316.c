/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "display_effects.h"
#include "frame.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s8 gUnknown_02023078;

void sub_080618B4(void);

void sub_080618B4(void) {

    s32 var_r3;
    s8 *var_r0;
    struct FrameObject *var_r2;
    struct FrameObject *objs;
    void **ctx;
    u32 *substate;
    u32 *state;
    s32 zero;
    s32 mask;
    u8 *cp;
    s32 zero2;

    if ((u32) gState0TypedWork.bytes[0x84] <= 8U) {
        sub_0803F684(0U, gState0TypedWork.bytes[0x84] * 4, 0xFFFEU);
        sub_0803F998(0U, gState0TypedWork.bytes[0x84] * 4, 0x7FFDU);
        gState0TypedWork.bytes[0x84] += 1;
        return;
    }
    ctx = &gMainContextPointer_03006F74;
    substate = &gMainSubstate;
    state = &gUnknown_0300137C;
    objs = gFrameObjects;
    mask = 0xBFFF;
    var_r2 = objs + 12;
    var_r3 = 3;
    do {
        var_r2->flags = mask & var_r2->flags;
        var_r2++;
        var_r3 -= 1;
    } while (var_r3 >= 0);
    cp = (u8 *)*ctx;
    zero = 0;
    cp[6] = 1;
    (*(s8 *)((u8 *)(*ctx) + 0x1A)) = zero;
    gUnknown_02023078 = zero;

    zero2 = 0;
    var_r3 = 0x77;
    var_r0 = &gUnknown_02023078 - 1;
    do {
        *var_r0 = zero2;
        var_r0 -= 1;
        var_r3 -= 1;
    } while (var_r3 >= 0);
    *substate = 0xC;
    *state = 0;
}
