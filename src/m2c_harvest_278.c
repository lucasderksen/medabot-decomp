/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "coordinate_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

union PackedCoordinates41 {struct TileCoordinates coordinates;u32 word;};
struct MotionTail41 {u8 beforeF8[0xF8];u8 flags;};

extern const u8 *const gState0NextCommands_083B6100[];
extern struct MotionTail41 gGraphicsTransferCounter;

void sub_0803CFC8(void);

void sub_0803CFC8(void) {

    union PackedCoordinates41 output;
    struct FrameObject *firstFrames;
    struct FrameObject *frames;
    struct FrameObject *temp_r0_3;
    struct FrameObject *temp_r0_4;
    struct FrameObject *temp_r1;
    struct FrameObject *temp_r2;
    u8 *var_r0;
    u8 temp_r0;
    u8 temp_r0_2;
    s32 var_r1;

    firstFrames=gFrameObjects;
    temp_r2=&firstFrames[gState0TypedWork.bytes[0x12F]];
    temp_r0 = temp_r2->unknown2C[0];
    if (temp_r0 != 0) {
        temp_r2->unknown2C[0] = temp_r0 - 1;
    } else {
        temp_r2->flags |= 0x8000;
        sub_08040BD8(gState0NextCommands_083B6100[firstFrames[gState0TypedWork.bytes[0x12F]].unknown2C[1]], gState0TypedWork.bytes[0x12F]);
    }
    frames=gFrameObjects;
    temp_r1=&frames[gState0TypedWork.bytes[0x12F]];
    temp_r0_2 = temp_r1->byte2B;
    if (temp_r0_2 != 0) {
        temp_r1->byte2B = temp_r0_2 - 1;
        return;
    }
    output.coordinates=sub_08042BC0((u32) temp_r1->unknown23[3], 0x10U, (u32) (*(s16 *)((u8 *)(frames) + 0x282)), (s32) (*(s16 *)((u8 *)(frames) + 0x284)));
    frames[gState0TypedWork.bytes[0x12F]].screenX = (s16)output.word;
    frames[gState0TypedWork.bytes[0x12F]].screenY = (s16) ((s32)output.word >> 0x10);
    if (!(2 & gGraphicsTransferCounter.flags)) {
        var_r1=frames[gState0TypedWork.bytes[0x12F]].unknown23[3]+0x10;
        var_r0=&frames[gState0TypedWork.bytes[0x12F]].unknown23[3];
    } else {
        var_r1=frames[gState0TypedWork.bytes[0x12F]].unknown23[3]-0x10;
        var_r0=&frames[gState0TypedWork.bytes[0x12F]].unknown23[3];
    }
    *var_r0 = var_r1;
}
