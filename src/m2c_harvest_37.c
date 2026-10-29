/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s32 sub_08036B1C(u8 *, s32);
extern u32 sub_08073BFC(u32, u8);

void sub_0801E9B0(void);
s32 sub_08032FFC(void);
u32 sub_08073C18(void *arg0, s32 arg1);

void sub_0801E9B0(void) {
    if (sub_08036B1C(gUnknown_0300052E, 0xA) != 0) {
        *(u16 *)(gUnknown_0300052E - 0x68) = 0x3C;
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

s32 sub_08032FFC(void) {
    u32 i;
    for (i = 0; i <= 2; i++) {
        if ((&gTransferByte_03001860 + 1)[i] != 0)
            return 1;
    }
    return 0;
}

u32 sub_08073C18(void *arg0, s32 arg1) {
    u32 var_r0;
    void *temp_r2;
    temp_r2 = (*(void **)((u8 *)(arg0) + 0));
    var_r0 = sub_08073BFC((u32) (arg1 * (*(u16 *)((u8 *)(temp_r2) + 4))) >> 0xC, (*(u8 *)((u8 *)(temp_r2) + 6)));
    if (var_r0 > 0x78000U) {
        var_r0 = 0x78000;
    }
    (*(u32 *)((u8 *)(arg0) + 4)) = var_r0;
    return var_r0;
}
