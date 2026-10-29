/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "battle_work.h"
#include "composite_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_command_data.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "state0_work.h"

extern const u8 gUnknown_083AE060[];

void sub_0802D198(void);

void sub_0802D198(void) {

    u32 i, j;

    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            for (j = 0; j <= 3; j++) {
                gFrameObjects[j + 0x30 + i * 4].flags = 0xC404;
                gFrameObjects[j + 0x30 + i * 4].tableSelector = 0;
                gFrameObjects[j + 0x30 + i * 4].screenX = gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5A].screenX;
                gFrameObjects[j + 0x30 + i * 4].screenY = gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5A].screenY + 4;
                gFrameObjects[j + 0x30 + i * 4].palette = 7;
                gFrameObjects[j + 0x30 + i * 4].priority = 0xF0;
                gFrameObjects[j + 0x30 + i * 4].unknown23[1] = 6;
                gFrameObjects[j + 0x30 + i * 4].unknown23[2] = gUnknown_083AE060[j];
                gFrameObjects[j + 0x30 + i * 4].frameAndGroup = 0x4D01;
            }
        }
    }
    gState0TypedWork.bytes[0x84] = 0;
    gCounter6ED08_03001800.counterAA++;
}
