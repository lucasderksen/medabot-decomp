/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "coordinate_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_work.h"
#include "tile_text.h"

extern const u8 gUnknown_083AD4F0[];

void sub_08015F90(u32 frameIndex);
void sub_08016080(u32 frameIndex);

void sub_08015F90(u32 frameIndex) {

    union { struct TileCoordinates coordinates; s32 word; } result;
    s16 y;
    struct FrameObject * frameBase;
    struct FrameObject *updatedFrame;
    struct FrameObject *frame;
    u32 heightY;
    u32 heightX;
    u32 selection;

    sub_08040CD0(frameIndex, 1U);
    frame = ((frameBase = gFrameObjects), frameBase + frameIndex);
    frame->flags = 0xC604;
    selection = frameIndex - gState0TransferWork.bytes[0x81];
    if (selection > 5U) {
        selection += 6;
    }
    result.coordinates = sub_08042CA0(*(const u8 *)((u32)gUnknown_083AD4F0 + selection), 24, 120, 128, 8, 0);
    frame->screenX = (s16) result.word;
    /* Keep the signed halfword stored to the frame for the palette tests. */
    y = (frame->screenY = (s16)(result.word >> 16));
    frame->frameAndGroup = frameIndex + 0x60C;
    if (y > 0x87) {
        frame->palette = 8;
    } else {
        if (y > 0x77) {
            frame->palette = 9;
        } else {
            frame->palette = 10;
        }

    }
    updatedFrame = ((frameBase = gFrameObjects), frameBase + frameIndex);
    updatedFrame->tableSelector = 0;
    /* Bias a negative word before the arithmetic shift: division toward zero. */
    heightY = 0x90 - updatedFrame->screenY;
    updatedFrame->scaleY = 0x40 - ((s32) (heightY + (heightY >> 0x1F)) >> 1);
    heightX = 0x90 - updatedFrame->screenY;
    updatedFrame->scaleX = 0x40 - ((s32) (heightX + (heightX >> 0x1F)) >> 1);
    updatedFrame->priority = (u8) updatedFrame->screenY - 0x70;
    updatedFrame->commandDelay = *(const u8 *)((u32)gUnknown_083AD4F0 + selection);
    updatedFrame->commandOffset = 0;
    updatedFrame->commandStopped = 0;
}

void sub_08016080(u32 frameIndex) {

    union { struct TileCoordinates coordinates; s32 word; } result;
    s16 y;
    struct FrameObject * frameBase;
    struct FrameObject *updatedFrame;
    struct FrameObject *frame;
    u32 selection;

    sub_08040CD0(frameIndex, 1U);
    frame = ((frameBase = gFrameObjects), frameBase + frameIndex);
    frame->flags = 0xC604;
    selection = frameIndex - gState0TransferWork.bytes[0x81];
    if (selection > 5U) {
        selection += 6;
    }
    result.coordinates = sub_08042CA0(*(const u8 *)((u32)gUnknown_083AD4F0 + selection), 24, 120, 128, 8, 0);
    frame->screenX = (s16) result.word;
    /* Keep the signed halfword stored to the frame for the palette tests. */
    y = (frame->screenY = (s16)(result.word >> 16));
    frame->frameAndGroup = frameIndex + 0x60C;
    if (y > 0x87) {
        frame->palette = 8;
    } else {
        if (y > 0x77) {
            frame->palette = 9;
        } else {
            frame->palette = 10;
        }

    }
    updatedFrame = ((frameBase = gFrameObjects), frameBase + frameIndex);
    updatedFrame->tableSelector = 0;
    updatedFrame->scaleY = 1;
    updatedFrame->scaleX = 1;
    updatedFrame->priority = (u8) updatedFrame->screenY - 0x70;
    updatedFrame->commandDelay = *(const u8 *)((u32)gUnknown_083AD4F0 + selection);
    updatedFrame->commandOffset = 0;
    updatedFrame->commandStopped = 0;
}
