/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "native_le_streams.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern const u8 gUnknown_0850FDD8[];

void sub_0802410C(void);
void sub_08027F84(void);

void sub_0802410C(void) {

    LeDecompress(gNativeLeStream_084D7A04, (void *)0x06014800);
    CpuFastSet(gUnknown_0850FDD8, (void *)0x050002E0, 8);
    gFrameObjects[0x21].flags |= 0x220;
    gFrameObjects[0x21].scaleX = 0x40;
    gFrameObjects[0x21].scaleY = 0x40;
    gFrameObjects[0x21].angle = 0;
    gFrameObjects[0x21].frameAndGroup = 0x4D00;
    gFrameObjects[0x21].value30 = gFrameObjects[0x5D + gCounter6ED08_03001800.value88 * 4].screenX;
    gFrameObjects[0x21].value32 = gFrameObjects[0x5D + gCounter6ED08_03001800.value88 * 4].screenY - 4;
    gFrameObjects[0x21].unknown23[1] = 6;
    if (1 & gCounter6ED08_03001800.flagsF8) {
        gFrameObjects[0x21].flags |= 0x1000;
    }
    gState0TypedWork.widths.word86 = 0x3C;
    gCounter6ED08_03001800.counterAA++;
}

void sub_08027F84(void) {

    LeDecompress(gNativeLeStream_084CAD2C, (void *)0x06014800);
    CpuFastSet(gActionKindPalette_0850F658, (void *)0x050002E0, 8);
    gFrameObjects[0x21].flags |= 0x220;
    gFrameObjects[0x21].scaleY = 0x40;
    gFrameObjects[0x21].scaleX = 8;
    gFrameObjects[0x21].screenY = 0x3C;
    gFrameObjects[0x21].frameAndGroup = 0xE00;
    if (1 & gCounter6ED08_03001800.flagsF8) {
        gFrameObjects[0x21].flags |= 0x1000;
        gFrameObjects[0x21].screenX--;
    }
    gCounter6ED08_03001800.counterAA++;
}
