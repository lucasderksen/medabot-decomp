/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "input.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Work6DBFC { u16 mode; u16 selection; u16 status; u8 pad06[2]; s32 counter; };

extern struct Work6DBFC gGraphicsTransferCounter;
extern void sub_08068684(s32, s32, s32);
extern void sub_0806B718(u8);
extern void sub_0806E10C(s32, s32);

void sub_0806DBFC(void);

void sub_0806DBFC(void) {
    u32 temp_r4;

    temp_r4 = (u8)(8 & *(u8 *)&gNewKeys);
    if (temp_r4 != 0) {
        sub_0806E10C(6, 2);
        sub_08074DE0(3U);
        gGraphicsTransferCounter.counter = 0;
        gUnknown_0300137C += 1;
        return;
    }
    if ((s32) gGraphicsTransferCounter.counter > 0x547) {
        gGraphicsTransferCounter.counter = (s32) temp_r4;
        sub_0806B718(2);
        sub_08068684(4, 1, 0);
        gGraphicsTransferCounter.mode = 3;
        gGraphicsTransferCounter.selection = (s16) temp_r4;
        gGraphicsTransferCounter.status = (s16) temp_r4;
        gUnknown_0300137C = 2;
        return;
    }
    gGraphicsTransferCounter.counter = (s32) (gGraphicsTransferCounter.counter + 1);
}
