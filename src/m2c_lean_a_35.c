/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "battle_work.h"
#include "frame.h"
#include "frame_objects.h"
#include "input.h"
#include "state0_work.h"

extern const u8 *gState0NextCommands_083B6100[];

void sub_08028F4C(void);

void sub_08028F4C(void) {

    sub_08040BD8(gState0NextCommands_083B6100[gFrameObjects[0x21].unknown2C[2]], 0x21);
    if (1 & gCounter6ED08_03001800.flagsF8) {
        if (gCounter6ED08_03001800.frame51 != 3) {
            gFrameObjects[0x21].angle = (gFrameObjects[0x21].angle - 0x10) & 0x3FF;
        }
    } else if (gCounter6ED08_03001800.frame51 != 3) {
        gFrameObjects[0x21].angle = (gFrameObjects[0x21].angle + 0x10) & 0x3FF;
    }
    if ((gState0TypedWork.bytes[0x89] != 0 || !(1 & (u8)gRepeatedKeys)) && gState0TypedWork.widths.word86 != 0) {
        gState0TypedWork.widths.word86--;
        return;
    }
    gCounter6ED08_03001800.counterAA++;
}
