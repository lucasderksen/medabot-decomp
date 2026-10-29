/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_work.h"


void sub_0802FBF4(void);

void sub_0802FBF4(void) {
    if (gState0TypedWork.widths.word86 == 0xC) {
        gState0TransferWork.bytes[0xAA] += 1;
        return;
    }
    gState0TypedWork.widths.word86 += 1;
    gFrameObjects[0x21].screenY = (u16) gFrameObjects[0x21].screenY + 2;
    gFrameObjects[0x22].screenY = (u16) gFrameObjects[0x22].screenY + 2;
}
