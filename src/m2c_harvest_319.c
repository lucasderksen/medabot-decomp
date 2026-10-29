/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "main_callbacks.h"
#include "state0_next_helpers.h"

extern struct { u8 b[0x400]; } gCounter6ED08_03001800;

void sub_0803512C(u32 row);

void sub_0803512C(u32 row) {

    s32 temp_r3;
    s32 idx;
    struct FrameObject *temp_r2;
    struct FrameObject *objs;
    u8 *temp_r3_2;

    objs = gFrameObjects;
    temp_r3 = row * 4;
    idx = temp_r3 + 0x5D;
    temp_r2 = &objs[idx];
    temp_r3_2 = gCounter6ED08_03001800.b + temp_r3;
    temp_r2->screenX = *(u16 *)(temp_r3_2 + 0x13C);
    temp_r2->screenY = *(u16 *)(temp_r3_2 + 0x13E) + 4;
    sub_080350E0(row);
}
