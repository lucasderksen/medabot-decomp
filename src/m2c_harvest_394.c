/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "state0_work.h"


u32 sub_08018F0C(u32 bank, u32 part, u32 amount);

u32 sub_08018F0C(u32 bank, u32 part, u32 amount) {

    /* Clamp after word addition. Return combines (excess << 8) with
     * (amount - excess), retaining the ROM's unsigned wrap. */
    u8 *setup;
    u8 *current;
    u32 address;
    u32 sum;
    u32 excess;
    u8 limit;

    setup = gSetupBuffer_03000590;
    address = part * 24 + (bank << 8);
    address += (u32)setup;
    setup = (u8 *)address;
    current = setup + 0x59;
    sum = *current;
    sum += amount;
    limit = setup[0x4C];
    if (sum > limit) {
        excess = sum - limit;
        *current = limit;
        return (excess << 8) + (amount - excess);
    }
    *current = sum;
    return amount;
}
