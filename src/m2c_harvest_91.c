/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "state0_next_helpers.h"

extern u32 sub_08036AC4(u32, u32);

s32 sub_08036B1C(u32 values, u32 slot);
s32 sub_08036B50(u32 values, u32 slot);

s32 sub_08036B1C(u32 values, u32 slot) {
    s32 found = 0;
    u32 i = 0;
    goto check;
loop:
    i++;
check:
    if (i <= 4 && *(u8 *)(values + i) != 0xFE) {
        do {
            if (sub_08036AC4(slot + i, 1) != 0)
                found = 1;
        } while (0);
        goto loop;
    }
    return found;
}

s32 sub_08036B50(u32 values, u32 slot) {
    s32 found = 0;
    u32 i = 0;
    goto check;
loop:
    i++;
check:
    if (i <= 4 && *(u8 *)(values + i) != 0xFE) {
        do {
            if (sub_08036AC4(slot + i, 0) != 0)
                found = 1;
        } while (0);
        goto loop;
    }
    return found;
}
