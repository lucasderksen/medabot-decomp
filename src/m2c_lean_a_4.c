/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_work.h"

struct LeanCounter1800 { u8 unknown00[0x60]; u8 firstObject; u8 unknown61[0x49]; u8 stepAA; u8 unknownAB[0x27]; u8 activeD2[3]; u8 unknownD5[0x23]; u8 flagsF8; };

extern const u8 *gState0NextCommands_083B6100[];
extern const u8 gUnknown_084D6B70[];
extern const u8 gUnknown_0850FC58[];
extern struct LeanCounter1800 gCounter6ED08_03001800;

void sub_08029680(void);

void sub_08029680(void) {

    u32 i;

    LeDecompress(gUnknown_084D6B70, (void *)0x06014800);
    CpuFastSet(gUnknown_0850FC58, (void *)0x050002E0, 8);
    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i]) {
            gFrameObjects[i + 0x21].flags = 0xC404;
            gFrameObjects[i + 0x21].tableSelector = 0;
            gFrameObjects[i + 0x21].screenX = gFrameObjects[(gCounter6ED08_03001800.firstObject + i) * 4 + 0x5D].screenX;
            gFrameObjects[i + 0x21].screenY = gFrameObjects[(gCounter6ED08_03001800.firstObject + i) * 4 + 0x5D].screenY - 4;
            gFrameObjects[i + 0x21].palette = 7;
            gFrameObjects[i + 0x21].priority = 0xF0;
            sub_08040B90(gState0NextCommands_083B6100[0x3C], i + 0x21);
            if (gCounter6ED08_03001800.flagsF8 & 1)
                gFrameObjects[i + 0x21].flags |= 0x1000;
        }
    }
    sub_08074DE0(0x37);
    gCounter6ED08_03001800.stepAA++;
}
