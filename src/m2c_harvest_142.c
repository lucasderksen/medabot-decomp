/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"


void sub_08020EDC(void);

void sub_08020EDC(void) {

    sub_080353CC(0x21U);
    if (gFrameObjects[0x21].unknown23[4] == 0x20) {
        gFrameObjects[0x21].flags &= 0xFDFF;
        gFrameObjects[0x21].angle = 0;
        gState0TransferWork.bytes[0xAA]++;
    } else {
        if (!(1 & gState0TransferWork.bytes[0xF8])) {
            gFrameObjects[0x21].angle = (gFrameObjects[0x21].angle+0x20)&0x3FF;
        } else {
            gFrameObjects[0x21].angle = (gFrameObjects[0x21].angle-0x20)&0x3FF;
        }
        if (!(1 & gFrameObjects[0x21].unknown23[4])) {
            if (!(1 & gState0TransferWork.bytes[0xF8])) {
                gFrameObjects[0x21].screenX += 1;
            } else {
                gFrameObjects[0x21].screenX -= 1;
            }
        }
        gFrameObjects[0x21].unknown23[4]++;
    }
}
