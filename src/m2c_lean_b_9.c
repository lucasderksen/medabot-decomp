/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "background_state.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"


void sub_0802C1A4(void);
void sub_08037330(s32 arg0, s32 arg1, s32 arg2);

void sub_0802C1A4(void) {

    u32 i;

    gCounter6ED08_03001800.base60 = sub_08032FC4(gCounter6ED08_03001800.slot87);
    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            gFrameObjects[i + 0x21].scaleX -= 8;
            gFrameObjects[i + 0x21].scaleY += 8;
        }
    }
    gCounter6ED08_03001800.base60 = sub_08032FB8(gCounter6ED08_03001800.slot87);
    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.valuesD6[i] != 0) {
            gFrameObjects[i + 0x24].scaleX -= 8;
            gFrameObjects[i + 0x24].scaleY += 8;
        }
    }
    if (gFrameObjects[0x21].scaleX == 8) {
        sub_08040CD0(0x21, 6);
        gCounter6ED08_03001800.counterAA++;
    }
}

void sub_08037330(s32 arg0, s32 arg1, s32 arg2) {

    if (arg1 & arg2) {
        gFrameObjects[arg0 * 4 + 0x5A].flags |= 0x8000;
        gFrameObjects[arg0 * 4 + 0x5B].flags |= 0x8000;
        gFrameObjects[arg0 * 4 + 0x5C].flags |= 0x8000;
        gFrameObjects[arg0 * 4 + 0x5D].flags |= 0x8000;
    } else {
        gFrameObjects[arg0 * 4 + 0x5A].flags &= 0x7FFF;
        gFrameObjects[arg0 * 4 + 0x5B].flags &= 0x7FFF;
        gFrameObjects[arg0 * 4 + 0x5C].flags &= 0x7FFF;
        gFrameObjects[arg0 * 4 + 0x5D].flags &= 0x7FFF;
    }
}
