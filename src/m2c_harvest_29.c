/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

s32 sub_080158D0(u32);

void sub_08015438(void);
void sub_080158F8(void);
void sub_080189EC(void);

void sub_08015438(void) {
    __typeof__(&(gSetupBuffer_03000590)[0]) offset0;
    u32 var_r4;
    u8 *var_r5;

    var_r4 = 0;
    offset0 = gSetupBuffer_03000590;
    var_r5 = offset0 + 0x40;
    do {
        if (*var_r5 != 0) {
            sub_08015414(var_r4);
        }
        var_r5 += 0x100;
        var_r4 += 1;
    } while (var_r4 <= 5U);
}

void sub_080158F8(void) {
    __typeof__(&(gSetupBuffer_03000590)[0]) offset0;
    u32 var_r4;
    u8 *var_r5;

    var_r4 = 0;
    offset0 = gSetupBuffer_03000590;
    var_r5 = offset0 + 0x40;
    do {
        if (*var_r5 != 0) {
            sub_080158D0(var_r4);
        }
        var_r5 += 0x100;
        var_r4 += 1;
    } while (var_r4 <= 5U);
}

void sub_080189EC(void) {
    __typeof__(&(gSetupBuffer_03000590)[0]) offset0;
    u32 var_r4;
    u8 *var_r5;

    var_r4 = 0;
    offset0 = gSetupBuffer_03000590;
    var_r5 = offset0 + 0x40;
    do {
        if (*var_r5 != 0) {
            sub_08018900(var_r4);
        }
        var_r5 += 0x100;
        var_r4 += 1;
    } while (var_r4 <= 2U);
}
