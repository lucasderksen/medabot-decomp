/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "frame.h"
#include "input.h"
#include "main.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"


void sub_0806E404(void);

void sub_0806E404(void) {
    u8 *work0;
    s32 temp_r0;

    work0 = (u8 *) &gState0TransferWork;
    temp_r0 = (*(s32 *)((u8 *)(work0) + 0x10)) - 1;
    (*(s32 *)((u8 *)(work0) + 0x10)) = temp_r0;
    if (temp_r0 == 0) {
        sub_08074B88(3U);
    }
    if ((gState0TransferWork.bytes[0xC] != 0) && (8 & (*(u8 *)&gNewKeys))) {
        gMainState = 3;
        gMainSubstate = 2;
        gUnknown_0300137C = 0;
        gMain2Byte_03007008 = 1;
    }
}
