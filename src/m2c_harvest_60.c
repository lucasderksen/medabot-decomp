/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "frame.h"
#include "state0_callbacks.h"
#include "state0_work.h"


void sub_0801DD30(void);

void sub_0801DD30(void) {
    if (gFrameObjects[0x21].scaleX == 0x40) {
        sub_08074DE0(0x30);
        gState0TransferWork.bytes[0xAA]++;
    } else {
        gFrameObjects[0x21].scaleX -= 4;
        gFrameObjects[0x21].scaleY -= 4;
    }
}
