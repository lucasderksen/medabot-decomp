/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "audio.h"
#include "background_state.h"
#include "frame.h"
#include "state0_work.h"


void sub_08038258(void);

void sub_08038258(void) {


    if (gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown2C[1] == 0x46) {
        gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown23[6]++;
        return;
    }
    if (gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown2C[1] & 1)
        gFrameObjects[gState0TypedWork.bytes[0x12F]].screenY++;
    if (!(gCounter6ED08_03001800.flagsF8 & 1))
        gFrameObjects[gState0TypedWork.bytes[0x12F]].angle = (gFrameObjects[gState0TypedWork.bytes[0x12F]].angle - 0x10) & 0x3FF;
    else
        gFrameObjects[gState0TypedWork.bytes[0x12F]].angle = (gFrameObjects[gState0TypedWork.bytes[0x12F]].angle + 0x10) & 0x3FF;
    gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown2C[1]++;
}
