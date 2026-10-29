/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "audio.h"
#include "background_state.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_work.h"


void sub_0802F214(void);

void sub_0802F214(void) {

    gFrameObjects[gState0TypedWork.bytes[0x84] + 0x21].flags = 0xC604;
    gFrameObjects[gState0TypedWork.bytes[0x84] + 0x21].tableSelector = 0;
    gFrameObjects[gState0TypedWork.bytes[0x84] + 0x21].screenX = gFrameObjects[gCounter6ED08_03001800.slot87 * 4 + 0x5D].screenX;
    gFrameObjects[gState0TypedWork.bytes[0x84] + 0x21].screenY = gFrameObjects[gCounter6ED08_03001800.slot87 * 4 + 0x5D].screenY - 4;
    gFrameObjects[gState0TypedWork.bytes[0x84] + 0x21].palette = 7;
    gFrameObjects[gState0TypedWork.bytes[0x84] + 0x21].priority = 0xF0;
    gFrameObjects[gState0TypedWork.bytes[0x84] + 0x21].scaleX = 0x40;
    gFrameObjects[gState0TypedWork.bytes[0x84] + 0x21].scaleY = 0x40;
    gFrameObjects[gState0TypedWork.bytes[0x84] + 0x21].angle = 0;
    gFrameObjects[gState0TypedWork.bytes[0x84] + 0x21].frameAndGroup = 0x4100;
    gFrameObjects[gState0TypedWork.bytes[0x84] + 0x21].unknown23[0] = 0;
    gFrameObjects[gState0TypedWork.bytes[0x84] + 0x21].unknown23[4] = 0;
    sub_08074DE0(0x29);
    gCounter6ED08_03001800.counterAA++;
}
