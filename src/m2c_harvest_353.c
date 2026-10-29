/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "display_effects.h"
#include "frame.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "state0_work.h"


void sub_0803CE18(void);

void sub_0803CE18(void) {

    u16 savedDelay;
    struct FrameObject *frames = gFrameObjects;
    u8 *work;
    u8 *selected;
    u32 highBits;
    struct FrameObject *frame;
    struct FrameObject *initialFrame;
    struct FrameObject *blendFrame;
    u8 delay;
    u8 weight;

    work = gState0TypedWork.bytes;
    selected = work + 0x12F;
    initialFrame = &frames[*selected];
    delay = initialFrame->byte2B;
    if ((savedDelay = delay) != 0) {
        initialFrame->byte2B = delay - 1;
        return;
    }
    highBits = (initialFrame->unknown2C[2] << 0xA) | (initialFrame->unknown2C[1] << 5);
    sub_0803F684((u16)(initialFrame->unknown2C[0] | highBits), (u32) initialFrame->unknown2C[3], 0xFDFFU);
    blendFrame = &frames[*selected];
    highBits = (blendFrame->unknown2C[2] << 0xA) | (blendFrame->unknown2C[1] << 5);
    sub_0803F998((u16)(blendFrame->unknown2C[0] | highBits), (u32) blendFrame->unknown2C[3], 0xB00FU);
    frame = &frames[*selected];
    weight = frame->unknown2C[3];
    if (weight == 0x10) {
        frame->unknown23[6] = savedDelay;
        return;
    }
    frame->unknown2C[3] = weight + 1;
}
