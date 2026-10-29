/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "frame_objects.h"
#include "input.h"
#include "state0_work.h"


void sub_08030624(void);
void sub_08030674(void);

void sub_08030624(void) {

    u32 keys;
    if (((gState0TypedWork.bytes[0x89] != 0) ||
         !((keys = *(u8 *)&gRepeatedKeys), (keys & 1u) & keys)) &&
        (gState0TypedWork.widths.word86 != 0)) {
        gState0TypedWork.widths.word86 -= 1;
        return;
    }
    sub_08040CD0(0xAU, 1U);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08030674(void) {

    u32 keys;
    if (((gState0TypedWork.bytes[0x89] != 0) ||
         !((keys = *(u8 *)&gRepeatedKeys), (keys & 1u) & keys)) &&
        (gState0TypedWork.widths.word86 != 0)) {
        gState0TypedWork.widths.word86 -= 1;
        return;
    }
    gState0TransferWork.bytes[0xAA] += 1;
}
