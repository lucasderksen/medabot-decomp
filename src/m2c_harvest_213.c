/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "state0_work.h"


s32 sub_08036D24(u8 *arg0, s32 arg1, s32 arg2);

s32 sub_08036D24(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *base=gSetupBuffer_03000590;
    u8 *current;
    u8 *maximum;
    u8 *temp_r0;
    u32 temp_r0_2;
    u8 temp_r1;

    temp_r0 = (u8 *)(((u32)arg2*0x18+((u32)arg1<<8))+(u32)base);
    current=temp_r0+0x59;
    maximum=temp_r0+0x4C;
    temp_r1=*current;
    if (temp_r1 != *maximum) {
        *current = (u8) (temp_r1 + 1);
        temp_r0_2 = (u32)*arg0 - 1;
        *arg0 = (u8)temp_r0_2;
        if ((temp_r0_2 << 0x18) != 0) {
            return 0;
        }
    }
    return 1;
}
