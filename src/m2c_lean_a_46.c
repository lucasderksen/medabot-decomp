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
#include "frame_command_data.h"
#include "input.h"
#include "pose_channels.h"
#include "state0_work.h"


void sub_08030780(void);

void sub_08030780(void) {

    union State0TypedWork *w;
    u8 busy;
    u16 *word;
    if (!(1 & gCounter6ED08_03001800.flagsF8))
        gFrameObjects[0x21].angle = (gFrameObjects[0x21].angle - 0x40) & 0x3FF;
    else
        gFrameObjects[0x21].angle = (gFrameObjects[0x21].angle + 0x40) & 0x3FF;
    busy = gState0TypedWork.bytes[0x89];
    w = &gState0TypedWork;
    if ((busy != 0 || !(1 & *(u8 *)&gRepeatedKeys)) && (word = &w->widths.word86, *word != 0)) {
        (*word)--;
        return;
    }
    gCounter6ED08_03001800.counterAA++;
}
