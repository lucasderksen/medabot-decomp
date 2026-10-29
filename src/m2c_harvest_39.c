/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern void *gUnknown_03007014;

void sub_0801EA5C(void);
void sub_0801EBF8(void);
void sub_080739F4(void);

void sub_0801EA5C(void) {
    __typeof__(&gState0TransferWork.bytes[0]) member0;
    u32 var_r0;

    member0 = gState0TransferWork.bytes;
    if (member0[0xD1] != 0) {
        sub_08035194((u32) member0[0x88]);
        var_r0 = member0[0xAA] + 3;
    } else {
        var_r0 = member0[0xAA] + 1;
    }
    member0[0xAA] = var_r0;
}

void sub_0801EBF8(void) {
    __typeof__(&gState0TransferWork.bytes[0]) member0;
    u8 *base0 = (u8 *) gSetupBuffer_03000590;
    u32 var_r0;

    member0 = gState0TransferWork.bytes;
    if ((*(u8 *)((u8 *)((base0 + (member0[0x88] << 8))) + 0x59)) != 0) {
        var_r0 = member0[0xAA] + 3;
    } else {
        sub_08035234((u32) member0[0x88]);
        var_r0 = member0[0xAA] + 1;
    }
    member0[0xAA] = var_r0;
}

void sub_080739F4(void) {
    u8 *p = gUnknown_03007014;
    if (p[0x72C] & 1) {
        *(volatile u16 *)0x04000080 = (p[0x72D] << 4) | 0xFF00 | p[0x72E];
        p[0x72C] &= 0xFE;
    }
}
