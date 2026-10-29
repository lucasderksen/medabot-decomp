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

extern const u8 *const gState0NextCommands_083B6100[];
extern const void *const gUnknown_083CEDF4[];
extern void sub_0801BFB4(const void *, u32);
extern void sub_08040BD8(const u8 *, u8);
extern void sub_0804422C(u32);

void sub_0803C738(void);

void sub_0803C738(void) {
    struct FrameObject *firstFrames = gFrameObjects;
    struct FrameObject *secondFrames;
    u8 *work;
    u8 *selected;
    u8 *secondWork;
    u8 *secondSelected;
    const u8 *const *commands;
    const void *const *assets;
    struct FrameObject *temp_r0_2;
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
        assets = gUnknown_083CEDF4;
        sub_0801BFB4(assets[firstFrames[*selected].unknown2C[2]], 0);
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
}
