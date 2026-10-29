/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "effect_work.h"
#include "frame.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"


void sub_080614DC(void);

void sub_080614DC(void) {

    u16 temp_r0;
    u8 temp_r4;

    temp_r0 = (*(u16 *)((u8 *)(gMainContextPointer_03006F74) + 2));
    (*(u16 *)((u8 *)(gMainContextPointer_03006F74) + 2)) = (u16) (temp_r0 + 1);
    temp_r4 = (u8) temp_r0;
    if ((u32) gFrameObjects[8].scaleX > 4U) {
        gFrameObjects[8].scaleX -= 4;
        gFrameObjects[8].scaleY -= 4;
    } else {
        gFrameObjects[8].flags &= 0xBFFF;
    }
    if ((u32) temp_r4 <= 0x10U) {
        *(volatile u16 *)0x04000052 = (temp_r4 << 8) | (0x10 - temp_r4);
    } else {
        *(volatile u16 *)0x04000052 = 0x1000;
        *(volatile u16 *)0x04000000 &= 0xFDFF;
        gFrameObjects[8].flags &= 0xBFFF;
        sub_0803FB0C();
        gUnknown_0300137C=(u32)gUnknown_0300137C+1U;
    }
    (*(s8 *)((u8 *)(gMainContextPointer_03006F74) + 0x19)) = 0;
}
