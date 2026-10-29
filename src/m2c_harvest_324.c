/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "display_effects.h"
#include "frame.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Fade611E8 {u8 kind;u8 pad01;s16 timer;u8 pad04[2];u8 mode;u8 pad07[0x12];u8 selection;};

extern void sub_08060BE4(u32, s32);

void sub_080611E8(void);

void sub_080611E8(void) {

    u32 nextPhase;
    s32 *phase;

    if (((struct Fade611E8 *)gMainContextPointer_03006F74)->mode == 1) {
        sub_08060BE4(((struct Fade611E8 *)gMainContextPointer_03006F74)->selection, 8);
        if ((u32) gState0TypedWork.bytes[0x84] <= 8U) {
            sub_0803F684(0U, 0x20 - (gState0TypedWork.bytes[0x84] * 4), 0x7FFEU);
            sub_0803F998(0U, 0x20 - (gState0TypedWork.bytes[0x84] * 4), 0x7FFDU);
            gState0TypedWork.bytes[0x84] += 1;
            return;
        }
        ((struct Fade611E8 *)gMainContextPointer_03006F74)->timer = 0;
        sub_0803FAA0(1U, 0U, 0U);
        ((struct Fade611E8 *)gMainContextPointer_03006F74)->timer = 0;
        ((struct Fade611E8 *)gMainContextPointer_03006F74)->kind = 0;
        ((struct Fade611E8 *)gMainContextPointer_03006F74)->mode = 0U;
        phase = &gUnknown_0300137C;
        nextPhase = 9;
        goto store_phase;
    }
    if ((u32) gState0TypedWork.bytes[0x84] <= 8U) {
        sub_0803F684(0U, 0x20 - (gState0TypedWork.bytes[0x84] * 4), 0xFFFFU);
        sub_0803F998(0U, 0x20 - (gState0TypedWork.bytes[0x84] * 4), 0xFFFFU);
        gState0TypedWork.bytes[0x84] += 1;
        return;
    }
    ((struct Fade611E8 *)gMainContextPointer_03006F74)->timer = 0;
    gFrameObjects[8].flags |= 0x4000;
    sub_0803FAA0(1U, 0U, 0U);
    ((struct Fade611E8 *)gMainContextPointer_03006F74)->timer = 0;
    ((struct Fade611E8 *)gMainContextPointer_03006F74)->kind = 0;
    phase = &gUnknown_0300137C;
    nextPhase = (u32)*phase + 1;
store_phase:
    *phase = nextPhase;
}
