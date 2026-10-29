/*
 * sub_08020B4C: not matching yet. The build assembles asm/non_matching/sub_08020B4C.inc
 * in its place; the C below is the closest attempt (docs/drafts/README.md).
 */

#include "global.h"
#include "battle_work.h"
#include "utility_helpers.h"

extern void sub_08036120(u32);
extern void sub_08036D24(void *, u32, u32);
extern u8 gC0 asm("gUnknown_03001864");
extern u8 gC1 asm("gUnknown_03001864+1");
extern u8 gC2 asm("gUnknown_03001864+2");
extern u8 gC3 asm("gUnknown_03001864+3");

NONMATCH("asm/non_matching/sub_08020B4C.inc", void sub_08020B4C(void))
{
    sub_08036D24(&gCounter6ED08_03001800.valueC8, gCounter6ED08_03001800.value88, gCounter6ED08_03001800.group8B);
    if (2 & gCounter6ED08_03001800.flagsF8) {
        sub_08036120(0);
        sub_080447EC(0, gC0, gC1, gC2, gC3,
                     (s16)gCounter6ED08_03001800.pos154[0], (s16)gCounter6ED08_03001800.pos154[1], gCounter6ED08_03001800.byte3C + 2, 4, 0, 2, 0, gCounter6ED08_03001800.byte114);
        sub_080447EC(0, gC0, gC1, gC2, gC3,
                     (s16)gCounter6ED08_03001800.pos154[0], (s16)gCounter6ED08_03001800.pos154[1], gCounter6ED08_03001800.byte3C + 2, 4, 0, 1, 0, gCounter6ED08_03001800.byte114);
    } else {
        sub_08036120(1);
        sub_080447EC(1, gC0, gC1, gC2, gC3,
                     (s16)gCounter6ED08_03001800.pos154[2], (s16)gCounter6ED08_03001800.pos154[3], gCounter6ED08_03001800.byte3C + 2, 8, 1, 2, 1, gCounter6ED08_03001800.byte115);
        sub_080447EC(1, gC0, gC1, gC2, gC3,
                     (s16)gCounter6ED08_03001800.pos154[2], (s16)gCounter6ED08_03001800.pos154[3], gCounter6ED08_03001800.byte3C + 2, 8, 1, 1, 1, gCounter6ED08_03001800.byte115);
    }
    gCounter6ED08_03001800.counterAA++;
}
END_NONMATCH
