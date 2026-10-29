/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern const u8 gUnknown_083AF620[];

u32 sub_08036AC4(u32 first, u32 second);

u32 sub_08036AC4(u32 first, u32 second) {
    struct FrameObject *frames=gFrameObjects;
    struct FrameObject *temp_r3;
    u32 temp_r0;

    temp_r3 = &frames[first];
    if (!(0x8000 & temp_r3->flags) || (temp_r3->unknown23[0] == 0x10)) {
        return 1U;
    }
    temp_r3->screenY = ((u16)temp_r3->screenY+gUnknown_083AF620[temp_r3->unknown23[0]])&0xFF;
    temp_r0 = temp_r3->unknown23[0] + 1;
    temp_r3->unknown23[0] = temp_r0;
    if (second != 0) {
        temp_r3->scaleY = (temp_r0 * 4) + 0x40;
    }
    return 0U;
}
