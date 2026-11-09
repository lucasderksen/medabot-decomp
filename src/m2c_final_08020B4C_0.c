/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "utility_helpers.h"

extern void sub_08036120(u32);
extern void sub_08036D24(void *, u32, u32);

void sub_08020B4C(void);

void sub_08020B4C(void) {

    sub_08036D24(&gCounter6ED08_03001800.valueC8, gCounter6ED08_03001800.value88, gCounter6ED08_03001800.group8B);
    if (2 & gCounter6ED08_03001800.flagsF8) {
        sub_08036120(0);
        sub_080447EC(0, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1],
                     gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                     (s16)gCounter6ED08_03001800.pos154[0], (s16)gCounter6ED08_03001800.pos154[1],
                     gCounter6ED08_03001800.byte3C + 2, 4, 0, 2, 0, gCounter6ED08_03001800.byte114);
        sub_080447EC(0, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1],
                     gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                     (s16)gCounter6ED08_03001800.pos154[0], (s16)gCounter6ED08_03001800.pos154[1],
                     gCounter6ED08_03001800.byte3C + 2, 4, 0, 1, 0, gCounter6ED08_03001800.byte114);
    } else {
        sub_08036120(1);
        sub_080447EC(1, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1],
                     gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                     (s16)gCounter6ED08_03001800.pos154[2], (s16)gCounter6ED08_03001800.pos154[3],
                     gCounter6ED08_03001800.byte3C + 2, 8, 1, 2, 1, gCounter6ED08_03001800.byte115);
        sub_080447EC(1, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1],
                     gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                     (s16)gCounter6ED08_03001800.pos154[2], (s16)gCounter6ED08_03001800.pos154[3],
                     gCounter6ED08_03001800.byte3C + 2, 8, 1, 1, 1, gCounter6ED08_03001800.byte115);
    }
    gCounter6ED08_03001800.counterAA++;
}
