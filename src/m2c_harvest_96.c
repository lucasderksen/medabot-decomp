/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "dialogue_messages.h"
#include "continued_late_graphics.h"
#include "display_effects.h"
#include "effect_work.h"
#include "frame.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern void sub_0803E894(void);
extern void sub_0803ED6C(void);

void sub_0803E434(void);

void sub_0803E434(void) {
    const void *commands;
    u8 *work;
    sub_0803E894();
    sub_0803ED6C();
    work = gState0TypedWork.bytes;
    (*(u16 *) (work + 0x86))++;
    if (work[0x9C] == 1)
        commands = gUnknownPointers_083CF530[6];
    else
        commands = gUnknownPointers_083CF530[7];
    if (sub_0803FB3C(commands) != 0) {
        sub_0803FAA0(1, 0, 0);
        gUnknown_0300137C++;
    }
}
