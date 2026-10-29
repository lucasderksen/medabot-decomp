/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_work.h"
#include "utility_helpers.h"

extern const s16 gUnknown_083AFC38[];
extern const u8 *const gState0NextCommands_083B6100[];
extern void sub_08040BD8(const u8 *, u8);
extern void sub_0804422C(u32);

void sub_0803C680(void);

void sub_0803C680(void) {
    struct FrameObject *firstFrames = gFrameObjects;
    struct FrameObject *secondFrames;
    u8 *work;
    u8 *selected;
    u8 *secondSelected;
    u8 *secondWork;
    const u8 *const *commands;
    const s16 *sines;
    struct FrameObject *temp_r0_2;
    struct FrameObject *temp_r0_4;
    struct FrameObject *temp_r1;
    struct FrameObject *temp_r2;
    u8 temp_r0;
    u8 temp_r0_3;

    work = gState0TypedWork.bytes;
    selected = work + 0x12F;
    temp_r2 = &firstFrames[*selected];
    temp_r0 = temp_r2->unknown2C[0];
    if (temp_r0 != 0) {
        temp_r2->unknown2C[0] = temp_r0 - 1;
    } else {
        temp_r2->flags |= 0x8000;
        commands = gState0NextCommands_083B6100;
        sub_08040BD8(commands[firstFrames[*selected].unknown2C[1]], *selected);
    }
    secondFrames = gFrameObjects;
    secondWork = gState0TypedWork.bytes;
    secondSelected = secondWork + 0x12F;
    temp_r0_2 = &secondFrames[*secondSelected];
    temp_r0_3 = temp_r0_2->byte2B;
    if (temp_r0_3 != 0) {
        temp_r0_2->byte2B = temp_r0_3 - 1;
        return;
    }
    sub_0804422C((u32)*secondSelected);
    temp_r1 = &secondFrames[*secondSelected];
    sines = gUnknown_083AFC38;
    temp_r1->screenY += sines[temp_r1->unknown23[0]];
    temp_r0_4 = &secondFrames[*secondSelected];
    temp_r0_4->unknown23[0] = (temp_r0_4->unknown23[0] + 1) & 0x1F;
}
