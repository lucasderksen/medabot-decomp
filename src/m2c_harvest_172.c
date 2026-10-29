/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "state0_work.h"

struct ContinuedTieRecord { u8 pad[0xBA];u8 status;u8 tail[0x45]; };


s32 sub_0801B4F8(u32 arg0);

s32 sub_0801B4F8(u32 arg0) {
    u32 temp_r1;
    s32 var_r4;
    u32 var_r2;
    u32 var_r2_2;
    u8 *var_r1;

    var_r4 = 0;
    var_r2 = 0;
    do {
        temp_r1 = (arg0 + var_r2) << 8;
        if (((struct ContinuedTieRecord*)(temp_r1+gSetupBuffer_03000590))->status != 0) {
            var_r2_2 = 0;
            var_r1 = temp_r1 + (gSetupBuffer_03000590 + 0x59);
            do {
                if (*var_r1 == 0) {
                    var_r4 += 1;
                }
                var_r1 += 0x18;
                var_r2_2 += 1;
            } while (var_r2_2 <= 3U);
        }
        var_r2 += 1;
    } while (var_r2 <= 2U);
    return var_r4;
}
