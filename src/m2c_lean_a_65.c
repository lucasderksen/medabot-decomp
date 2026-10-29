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
#include "frame_objects.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "state0_display.h"
#include "state0_work.h"

struct Counter712C { u8 pad00[0x41]; u8 cells41[3]; };

extern struct Counter712C gCounter712C asm("gCounter6ED08_03001800");

void sub_0800712C(void);

void sub_0800712C(void) {

    u32 i;

    switch (gState0TypedWork.bytes[0x50]) {
    case 1:
    case 2:
        for (i = 0; i <= 2; i++) {
            if (gCounter712C.cells41[i] != 0) {
                gFrameObjects[i + 4].flags = 0xC004;
                gFrameObjects[i + 4].screenX = gUnknownBytes_083AC5BB[(0xF & gCounter712C.cells41[i]) * 2];
                gFrameObjects[i + 4].screenY = gUnknownBytes_083AC5BB[(0xF & gCounter712C.cells41[i]) * 2 + 1];
                gFrameObjects[i + 4].frameAndGroup = i + 0x401;
                gFrameObjects[i + 4].palette = 0xF;
                gFrameObjects[i + 4].tableSelector = 0;
                gFrameObjects[i + 4].priority = 0xC0;
            } else {
                sub_08040D0C(i + 4, 1);
            }
        }
        break;
    case 3:
        for (i = 0; i <= 2; i++) {
            if (gCounter712C.cells41[i] != 0) {
                gFrameObjects[i + 4].flags = 0xC004;
                gFrameObjects[i + 4].screenX = gUnknownBytes_083AC5BB[(0xF & gCounter712C.cells41[i]) * 2];
                gFrameObjects[i + 4].screenY = gUnknownBytes_083AC5BB[(0xF & gCounter712C.cells41[i]) * 2 + 1];
                gFrameObjects[i + 4].frameAndGroup = i + 0x404;
                gFrameObjects[i + 4].palette = 0xF;
                gFrameObjects[i + 4].tableSelector = 0;
                gFrameObjects[i + 4].priority = 0xC0;
            } else {
                sub_08040D0C(i + 4, 1);
            }
        }
        break;
    }
}
