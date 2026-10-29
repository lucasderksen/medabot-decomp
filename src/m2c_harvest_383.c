/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "compression.h"
#include "gba.h"
#include "main_callbacks.h"

/* Clear the BG1 tile area and load the original 992-byte Le tile stream. */
void sub_08059EC8(void) {

    s32 zero;
    volatile u16 *background;
    s32 control;

    zero = 0;
    CpuFastSet(&zero, (void *)0x06004000, 0x01001000U);
    LeDecompress(gMain2AdditionalTiles_08785EC0, (void *)0x06004020);
    background = (volatile u16 *)0x0400000A;
    control = 0x1E04;
    *background = control;
    *(volatile u16 *)0x04000000 |= 0x200;
}

/* Clear the BG2 tile area before enabling it in DISPCNT. */
void sub_08059F18(void) {

    s32 zero;
    volatile u16 *background;
    s32 control;

    zero = 0;
    CpuFastSet(&zero, (void *)0x06008400, 0x01000F00U);
    background = (volatile u16 *)0x0400000C;
    control = 0x1608;
    *background = control;
    *(volatile u16 *)0x04000000 |= 0x400;
}
