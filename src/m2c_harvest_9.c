/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "tile_text.h"


void sub_08017D14(void);

void sub_08017D14(void) {
    u32 var_r4;
    u32 var_r5;

    var_r4 = 0;
    var_r5 = 2;
    do {
        sub_08042698(2U, 2U, 9U, var_r5, (u32) *(u16 *)0x0400000A, (u32) ((var_r4 << 0x12) + 0xC3700000) >> 0x10);
        var_r5 += 2;
        var_r4 += 1;
    } while (var_r4 <= 4U);
}
