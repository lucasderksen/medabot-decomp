/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "record_helpers.h"
#include "state0_work.h"

struct LeanCounter1800 { u8 unknown00[0x60]; u8 firstObject; u8 unknown61[0x49]; u8 stepAA; u8 unknownAB[0x27]; u8 activeD2[3]; };

extern struct LeanCounter1800 gCounter6ED08_03001800;

void sub_080297EC(void);

void sub_080297EC(void) {

    u32 i;

    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0)
            sub_08038394(gCounter6ED08_03001800.firstObject + i, 1);
    }
    gCounter6ED08_03001800.stepAA++;
}
