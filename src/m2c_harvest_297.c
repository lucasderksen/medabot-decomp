/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct ScaleFrameView { u8 unknown00[0x848]; u8 scaleX; u8 scaleY; };


void sub_0802F2F4(void);

void sub_0802F2F4(void) {

    struct FrameObject *frame;
    struct FrameObject *laterBase;
    struct FrameObject *laterFrame;
    struct FrameObject *frameBase;
    s32 index;
    s16 coordinate;
    u8 *scaleX;
    s32 delta;
    s32 counter;
    sub_080353CC(gState0TypedWork.bytes[0x84] + 0x21);
    frameBase = gFrameObjects;
    index = gState0TypedWork.bytes[0x84] + 0x21;
    frame = &frameBase[index];
    if (frame->unknown23[4] == 0x20) {
        sub_08040CD0((u8)index, 1);
        scaleX = &((struct ScaleFrameView *)frameBase)->scaleX;
        counter = gState0TypedWork.bytes[0x84];
        delta = counter * 0x10;
        *scaleX += delta;
        ((struct ScaleFrameView *)frameBase)->scaleY += delta;
        gState0TypedWork.bytes[0x84] = ++counter;
        if ((u8)counter == 4) {
            gState0TransferWork.bytes[0xAA]++;
        } else {
            gState0TransferWork.bytes[0xAA] = 2;
        }
    } else {
        if (!(1 & gState0TransferWork.bytes[0xF8])) {
            frame->angle = (frame->angle + 0x20) & 0x3FF;
        } else {
            frame->angle = (frame->angle - 0x20) & 0x3FF;
        }
        laterBase = gFrameObjects;
        laterFrame = (struct FrameObject *)((u8 *)laterBase + ((gState0TypedWork.bytes[0x84] + 0x21) << 6));
        if (!(1 & laterFrame->unknown23[4])) {
            if (!(1 & gState0TransferWork.bytes[0xF8])) {
                coordinate = (u16)laterFrame->screenX + 1;
                laterFrame->screenX = coordinate;
            } else {
                coordinate = (u16)laterFrame->screenX - 1;
                laterFrame->screenX = coordinate;
            }
        }
        ((struct FrameObject *)((u8 *)gFrameObjects + ((gState0TypedWork.bytes[0x84] + 0x21) << 6)))->unknown23[4]++;
    }
}
