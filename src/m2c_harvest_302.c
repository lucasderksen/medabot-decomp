/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct CV { u8 p0[0x60]; u8 b60; u8 p61[0x87 - 0x61]; u8 b87; u8 p88[0xAA - 0x88]; u8 bAA; u8 pAB[0xD2 - 0xAB]; u8 bD2[3]; };

extern struct CV gCounter6ED08_03001800;
s32 sub_0803836C();

void sub_0802E010(void);

void sub_0802E010(void) {

    s32 var_r5;
    u32 var_r2;
    u8 *temp_r1;
    u8 *setup;

    var_r5 = 0;
    sub_0803836C();
    gCounter6ED08_03001800.b60 = (u8) sub_08032FB8((u32) gCounter6ED08_03001800.b87);
    var_r2 = 0;
    setup = gSetupBuffer_03000590;
    do {
        temp_r1 = (u8 *)(((gCounter6ED08_03001800.b60 + var_r2) << 8) + (u32)setup);
        if ((temp_r1[0x40] != 0) && (temp_r1[0x59] != 0) && (4 & temp_r1[0xBD])) {
            gCounter6ED08_03001800.bD2[var_r2] = 1;
            var_r5 = 1;
        }
        var_r2 += 1;
    } while (var_r2 <= 2U);
    if (var_r5 == 0) {
        gCounter6ED08_03001800.bAA = gCounter6ED08_03001800.bAA + 1;
    } else {
        gCounter6ED08_03001800.bAA = gCounter6ED08_03001800.bAA + 2;
    }
}
