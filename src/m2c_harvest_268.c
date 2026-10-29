/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "frame.h"
#include "object_numeric_helpers.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"

struct FamilyGraphicsWork {u8 pad0[4];u16 state;u8 pad6[2];s32 count;};

extern struct FamilyGraphicsWork gUnknown_03001800;
extern void sub_08068460(u8, u8, u16);
extern void sub_0806B718(u8);
extern void sub_0806E10C(s8, u32);

void sub_0806D8AC(void);

void sub_0806D8AC(void) {

    s32 temp_r4;
    u32 delay;

    temp_r4 = gUnknown_03001800.count;
    if (temp_r4 == 0) {
        sub_08048864(0U, 0xCC00U, 0x224U, 6U, 3U);
        gFrameObjects->screenX = 0x78;
        gFrameObjects->screenY = 0x3C;
        gFrameObjects->priority = 0x10;
        sub_0806E10C(1, 0);
        *(volatile u16 *)0x04000000 |= 0x1000;
    } else if (temp_r4 == 0x20) {
        sub_08048864(1U, 0xC400U, 0x200U, 0U, 3U);
        gFrameObjects[1].screenX = 0x78;
        gFrameObjects[1].screenY = 0x3C;
        gFrameObjects[1].priority = (u8) temp_r4;
        sub_0806E10C(2, 1);
    }
    delay = gFrameObjects->commandDelay;
    if (delay == 0) {
        gUnknown_03001800.state = 6;
        gUnknown_03001800.count = delay;
        sub_08068460(4, 4, 0x7FFF);
        sub_0806B718(1);
        sub_08048864(0U, 0xC400U, 0x21BU, 4U, 3U);
        *(volatile u16 *)0x04000000 = (u16) (*(volatile u16 *)0x04000000 | 0x300);
        gUnknown_0300137C = 1;
        return;
    }
    gUnknown_03001800.count = (s32) (gUnknown_03001800.count + 1);
}
