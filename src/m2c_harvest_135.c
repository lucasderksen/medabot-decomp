/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_work.h"

extern const u8 *const gState0NextCommands_083B6100[];
extern void sub_08040B90(const u8 *, u8);
extern void sub_08040CD0(u8, u8);

void sub_0803CBD0(void);

void sub_0803CBD0(void) {
    struct FrameObject *frames = gFrameObjects;
    u8 *work;
    u8 *selected;
    const u8 *const *commands;
    struct FrameObject *temp_r2;
    struct FrameObject *temp_r3;
    u8 temp_r0;
    u8 temp_r1;

    work = gState0TypedWork.bytes;
    selected = work + 0x12F;
    temp_r3 = &frames[*selected];
    temp_r0 = temp_r3->byte2B;
    if (temp_r0 != 0) {
        temp_r3->byte2B = temp_r0 - 1;
        return;
    }
    temp_r1 = temp_r3->unknown2C[2];
    temp_r2 = &frames[temp_r1];
    temp_r2->palette = temp_r3->palette;
    temp_r2->unknown2C[1] = frames[*selected].unknown2C[1];
    temp_r2->unknown23[6] = 0x21;
    commands = gState0NextCommands_083B6100;
    sub_08040B90(commands[temp_r2->unknown2C[1]], temp_r1);
    sub_08040CD0(*selected, 1U);
}
