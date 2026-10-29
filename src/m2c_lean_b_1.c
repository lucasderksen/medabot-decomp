/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "record_helpers.h"

 struct FrameF3FC {
    u16 flags;
    s16 screenX;
    s16 screenY;
    u8 pad6[0x1D];
    u8 byte23;
    u8 byte24;
    u8 pad25[0xB];
    u16 word30;
    s16 word32;
    u8 pad34[0xC];
};

extern struct FrameF3FC gFramesF3FC[] asm("gFrameObjects");

void sub_0802F3FC(void);

void sub_0802F3FC(void) {

    gFramesF3FC[0x21].word30 = gFramesF3FC[gCounter6ED08_03001800.slot87 * 4 + 0x5D].screenX;
    gFramesF3FC[0x21].word32 = gFramesF3FC[gCounter6ED08_03001800.slot87 * 4 + 0x5D].screenY - 4;
    gFramesF3FC[0x21].byte24 = 4;
    gFramesF3FC[0x21].byte23 = 0;
    gCounter6ED08_03001800.counterAA++;
}
