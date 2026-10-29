/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_commands.h"
#include "equipment_helpers.h"

extern u8 gContinuedWork_030057E0[];

/* Kept as a helper: its 0/1 result in r0 reproduces the reference test. */
static inline u32 ContinuedRollChance(void) {
    if ((0x1F & sub_080424B8()) == 0x1F)
        return 1;
    return 0;
}

u32 sub_080438C4(void) {
    u8 count;

    if (gContinuedWork_030057E0[0xC2D] != 0)
        return 0;
    if (gContinuedWork_030057E0[0xC5F] != 0)
        return 0;
    if (gContinuedWork_030057E0[0xC29] == 0)
        return 0;
    if (1 & gContinuedWork_030057E0[0xC2C])
        return 0;
    count = ++gContinuedWork_030057E0[0xC2B];
    if (count > 0x10) {
        if (count > 0x1F || ContinuedRollChance()) {
            gContinuedWork_030057E0[0xC2B] = 0;
            gContinuedWork_030057E0[0xC2E] = 0;
            gContinuedWork_030057E0[0xC2F] = 0;
            return 1;
        }
    }
    return 0;
}
