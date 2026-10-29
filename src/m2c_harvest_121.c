/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "display_effects.h"
#include "frame.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct ResetContext {
    u8 prefix[0x3C];
    s16 reset;
};

extern s32 sub_08062B48(u8, u8, s32);
extern s32 sub_08062C98(void);

void sub_080633FC(void);

void sub_080633FC(void) {
    u32 scaled;
    u8 zero;
    if ((scaled = (u32)gState0TypedWork.bytes[0x84] << 24), ((scaled >> 24)<=0x40U)) {
        sub_0803F998(0x7FFFU, scaled >> 25, 0xFFU);
        gState0TypedWork.bytes[0x84] += 1;
    } else {
        ((struct ResetContext*)gMainContextPointer_03006F74)->reset = 0;
        gState0TypedWork.bytes[0x84] = (zero = 0);
        gUnknown_0300137C += 1;
    }
    sub_08062B48(((u8 *)gMainContextPointer_03006F74)[0x31], ((u8 *)gMainContextPointer_03006F74)[0x33], 0);
    sub_08062B48(((u8 *)gMainContextPointer_03006F74)[0x32], ((u8 *)gMainContextPointer_03006F74)[0x34], 1);
    sub_08062C98();
}
