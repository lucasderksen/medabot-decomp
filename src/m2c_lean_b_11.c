/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "background_state.h"
#include "frame.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"


void sub_0802E820(void);

void sub_0802E820(void) {

    s32 done = 0;
    s32 active = 0;
    u32 i;

    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            active++;
            if (gCounter6ED08_03001800.flagsF8 & 1)
                gFrameObjects[i + 0xA].angle = (gFrameObjects[i + 0xA].angle - 0x40) & 0x3FF;
            else
                gFrameObjects[i + 0xA].angle = (gFrameObjects[i + 0xA].angle + 0x40) & 0x3FF;
            if (sub_080355F0(i + 0xA) != 0) {
                gFrameObjects[i + 0xA].angle = 0;
                done++;
            }
        }
    }
    if (done == active) {
        sub_08074DE0(0x2B);
        gCounter6ED08_03001800.counterAA++;
    }
}
