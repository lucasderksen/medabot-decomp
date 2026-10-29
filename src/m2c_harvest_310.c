/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "frame_objects.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "utility_helpers.h"

extern u8 gUnknown_03001800[];
extern const u8 gUnknown_083AEB08[];

void sub_0802DE1C(void);

void sub_0802DE1C(void) {

    u8 temp_r2;
    u8 *b;
    u32 sequence;
    u32 sequenceOffset;
    if (!(0x1F & gState0TypedWork.widths.word86) && ((u32) gFrameObjects[0x21].unknown23[0] <= 7U)) {
        gUnknown_03001800[0xAA] = gUnknown_03001800[0xAA] + 1;
        gState0TypedWork.widths.word86 += 1;
        return;
    }
    gState0TypedWork.widths.word86 += 1;
    b = (u8 *)gUnknownPointers_083B6100;
    sub_08040BD8(*(u8 **)(b + 0x1A4), 0x21U);
    sub_0804422C(0x21U);
    gFrameObjects[0x21].unknown23[1] = 4;
    if (gFrameObjects[0x21].unknown23[5] != 0) {
        gFrameObjects[0x21].unknown23[5] -= 1;
        return;
    }
    sequence = (u32)gUnknown_083AEB08;
    sequenceOffset = gFrameObjects[0x21].unknown23[0] * 2;
    gFrameObjects[0x21].unknown23[2] = *(const u8 *)(sequence + sequenceOffset);
    if (gFrameObjects[0x21].unknown23[2] == 0xFF) {
        sub_08040CD0(0x21U, 1U);
        gUnknown_03001800[0xAA] = 0xAU;
        return;
    }
    if (1 & gUnknown_03001800[0xF8]) {
        gFrameObjects[0x21].unknown23[2] = (0x20 - gFrameObjects[0x21].unknown23[2]) & 0x1F;
    }
    sequenceOffset = gFrameObjects[0x21].unknown23[0] * 2 + 1;
    gFrameObjects[0x21].unknown23[5] = *(const u8 *)(sequence + sequenceOffset);
    gFrameObjects[0x21].unknown23[0] += 1;
}
