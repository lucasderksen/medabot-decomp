/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "composite_graphics.h"
#include "continued_scene_records.h"
#include "fallback_map_assets.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "map_metadata.h"
#include "record_helpers.h"
#include "scene_view.h"
#include "sound_samples.h"
#include "sound_voice.h"
#include "sound_work.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"


void sub_0802D8D0(void);

void sub_0802D8D0(void) {

    s32 done = 0;
    s32 active = 0;
    u32 i;
    u32 root;
    struct FrameObject *dst;

    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            active++;
            do {
            if (!(1 & gCounter6ED08_03001800.flagsF8))
                gFrameObjects[i + 0x21].angle = (gFrameObjects[i + 0x21].angle - 0x40) & 0x3FF;
            else
                gFrameObjects[i + 0x21].angle = (gFrameObjects[i + 0x21].angle + 0x40) & 0x3FF;
            } while (0);
            if (sub_080355F0(i + 0x21) != 0)
                done++;
        }
    }
    if (done == active) {
        for (i = 0, root = (u32)gFrameObjects; i <= 2; i++) {
            if (gCounter6ED08_03001800.activeD2[i] != 0) {
                sub_08040D0C(i + 0x21, 1);
                gFrameObjects[i + 0x24].flags = 0xC404;
                ((struct FrameObject *)(root + ((i + 0x24) << 6)))->tableSelector = 0;
                dst = &gFrameObjects[i + 0x24];
                dst->screenX = ((struct FrameObject *)(root + ((i + 0x21) << 6)))->screenX;
                ((struct FrameObject *)(root + ((i + 0x24) << 6)))->screenY = ((struct FrameObject *)(root + ((i + 0x21) << 6)))->screenY;
                ((struct FrameObject *)(root + ((i + 0x24) << 6)))->palette = 7;
                ((struct FrameObject *)(root + ((i + 0x24) << 6)))->priority = 0xE0;
                ((struct FrameObject *)(root + ((i + 0x24) << 6)))->angle = 0;
                ((struct FrameObject *)(root + ((i + 0x24) << 6)))->unknown23[0] = 0;
                switch (gCounter6ED08_03001800.activeD2[i] & 0x7F) {
                case 1:
                    ((struct FrameObject *)(root + ((i + 0x24) << 6)))->frameAndGroup = 0x4E02;
                    break;
                case 2:
                    ((struct FrameObject *)(root + ((i + 0x24) << 6)))->frameAndGroup = 0x4E03;
                    break;
                default:
                    ((struct FrameObject *)(root + ((i + 0x24) << 6)))->frameAndGroup = 0x4E01;
                    break;
                }
            }
        }
        sub_08074DE0(0x6A);
        gCounter6ED08_03001800.counterAA++;
    }
}
