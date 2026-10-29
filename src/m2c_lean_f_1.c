/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "object_helpers.h"
#include "sound_work.h"


void sub_080422B8(u8 kind, u8 amount);

void sub_080422B8(u8 kind, u8 amount) {

    u32 i;

    kind &= 0x3F;
    for (i = 0; i <= 63; i++) {
        if (0x80 & gObjectCountPairs[i][0]) {
            if ((0x7F & gObjectCountPairs[i][0]) == kind) {
                gObjectCountPairs[i][1] += amount;
                if (gObjectCountPairs[i][1] > 99)
                    gObjectCountPairs[i][1] = 99;
                return;
            }
        } else {
            gObjectCountPairs[i][0] = kind | 0x80;
            gObjectCountPairs[0][i * 2 + 1] = amount;
            return;
        }
    }
}
