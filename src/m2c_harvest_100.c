/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "display_effects.h"
#include "effect_work.h"
#include "input.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"


void sub_08065590(void);

void sub_08065590(void) {
    s32 waiting = 1;
    if (*((u8*)gMainContextPointer_03006F74 + 0x4C) != 0) {
        if (sub_08041CA4() != 0) {
            u32 zero;
            *((u8*)gMainContextPointer_03006F74 + 0x4C) = (zero = 0);
            sub_0803FAA0(1,zero,zero);
        }
    } else {
        const void *const *scripts = gMain2ScriptSlots_0848521C;
        if (sub_0803FB3C(scripts[15]) != 0) waiting = 0;
    }
    if (waiting == 0 && (*(u8*)&gNewKeys & 3)) {
        sub_0803FB0C();
        gUnknown_0300137C = 5;
    }
}
