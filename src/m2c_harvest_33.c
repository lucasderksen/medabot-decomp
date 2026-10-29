/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"

u16 Sqrt(s32);

u16 sub_0805BBB4(s16 arg0, s16 arg1, s16 arg2, s16 arg3);

u16 sub_0805BBB4(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 temp_r2;
    s32 temp_r3;

    temp_r2 = arg2 - arg0;
    temp_r3 = arg3 - arg1;
    return Sqrt((temp_r2 * temp_r2) + (temp_r3 * temp_r3));
}
