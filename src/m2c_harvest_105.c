/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "frame.h"
#include "input.h"
#include "state0_callbacks.h"
#include "state0_work.h"


void sub_08027D24(void);

void sub_08027D24(void) {
    u8 *work = gState0TypedWork.bytes;
    gState0TypedWork.widths.word86 += 1;
    gFrameObjects[0x21].angle = (gFrameObjects[0x21].angle + 0x40) & 0x3FF;
    if (((work[0x89] != 0) || !(1 & *(u8 *)&gRepeatedKeys)) && (*(work += 0x84) != 0)) {
        *work -= 1;
        return;
    }
    sub_08074DE0(0x2BU);
    gState0TransferWork.bytes[0xAA] += 1;
}
