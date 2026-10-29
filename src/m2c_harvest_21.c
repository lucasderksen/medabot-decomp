/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

s32 sub_08015BF4(u32);

void sub_0801AD10(u32 arg0);

void sub_0801AD10(u32 arg0) {
    u8 *base0 = (u8 *) gSetupBuffer_03000590;
    if ((*(u8 *)((u8 *)((base0 + (arg0 << 8))) + 0xC1)) == 0x50) {
        sub_08015BF4(arg0);
    } else {
        sub_08015BA8(arg0);
    }
    sub_08015C40(arg0);
    sub_08015E68(arg0);
}
