/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "bios_lz77.h"
#include "composite_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "record_helpers.h"
#include "scene_view.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct PartF4AC {
    u8 name[13];
    u8 pad0D[3];
    u8 byte10;
    u8 data11[6];
    u8 id17;
};
struct SetupF4AC {
    u8 pad00[0x48];
    struct PartF4AC parts[4];
    u8 padA8[0x58];
};

extern const u8 *gState0NextCommands_083B6100[];
extern struct SetupF4AC gSetupF4AC[] asm("gSetupBuffer_03000590");
extern u32 sub_08036D64(u32, u32);

void sub_0801C774(void);
void sub_0801F4AC(void);

void sub_0801C774(void) {

    gFrameObjects[0x21].flags = ((gCounter6ED08_03001800.byte3C + 2) << 10) | 0xC204;
    gFrameObjects[0x21].tableSelector = 0;
    gFrameObjects[0x21].palette = 6;
    gFrameObjects[0x21].scaleY = 0x40;
    if (gCounter6ED08_03001800.record89 == 0) {
        gFrameObjects[0x21].flags |= 0x1000;

        gFrameObjects[0x21].screenX = 0x68;
    } else {
        gFrameObjects[0x21].screenX = 0x88;
    }
    switch (gCounter6ED08_03001800.frame51) {
    case 0:
        gFrameObjects[0x21].priority = 5;
        gFrameObjects[0x21].scaleX = 8;
        gFrameObjects[0x21].screenY = 0x3C;
        gCounter6ED08_03001800.count52 = 0x19;
        sub_08040B90(gState0NextCommands_083B6100[25], 0x21);
        sub_08074DE0(0x3E);
        gCounter6ED08_03001800.counterAA++;
        break;
    case 1:
        gFrameObjects[0x21].priority = 5;
        gFrameObjects[0x21].scaleX = 8;
        gFrameObjects[0x21].screenY = 0x3C;
        gCounter6ED08_03001800.count52 = 0x1A;
        sub_08040B90(gState0NextCommands_083B6100[26], 0x21);
        sub_08074DE0(0x3E);
        gCounter6ED08_03001800.counterAA++;
        break;
    case 2:
        gFrameObjects[0x21].priority = 0xF0;
        gFrameObjects[0x21].scaleX = 0x40;
        gFrameObjects[0x21].screenY = -0x2C;
        gFrameObjects[0x21].frameAndGroup = 0xD00;
        gFrameObjects[0x21].unknown23[1] = 8;
        gFrameObjects[0x21].unknown23[2] = 0;
        gFrameObjects[0x21].value30 = 0;
        sub_08074DE0(0x61);
        gCounter6ED08_03001800.counterAA = 0x10;
        break;
    case 3:
        gFrameObjects[0x21].priority = 0xF0;
        gFrameObjects[0x21].scaleX = 0x40;
        gFrameObjects[0x21].screenY = -0x2C;
        gFrameObjects[0x21].frameAndGroup = 0xE00;
        gFrameObjects[0x21].commandDelay = 0;
        gFrameObjects[0x21].unknown23[1] = 8;
        gFrameObjects[0x21].unknown23[2] = 0;
        gFrameObjects[0x21].value30 = 0;
        sub_08074DE0(0x61);
        gCounter6ED08_03001800.counterAA = 0x10;
        break;
    }
}

void sub_0801F4AC(void) {

    u32 kind;

    if (1 & gCounter6ED08_03001800.byteB7) {
        gCounter6ED08_03001800.counterAA++;
        return;
    }
    if (2 & gCounter6ED08_03001800.padB8[0]) {
        gCounter6ED08_03001800.counterAA++;
        return;
    }
    if (4 & gCounter6ED08_03001800.padB8[0]) {
        gCounter6ED08_03001800.counterAA++;
        return;
    }
    if (gSetupF4AC[gCounter6ED08_03001800.value88].parts[0].data11[0] == 0) {
        gCounter6ED08_03001800.counterAA++;
        return;
    }
    if (sub_080331F8(gCounter6ED08_03001800.value88) == 0) {
        gCounter6ED08_03001800.counterAA++;
        return;
    }
    if (sub_08036D64(gCounter6ED08_03001800.value88, gSetupF4AC[gCounter6ED08_03001800.slot87].parts[gCounter6ED08_03001800.partA7].name[1]) != 0) {
        gCounter6ED08_03001800.counterAA++;
        return;
    }
    kind = gSetupF4AC[gCounter6ED08_03001800.slot87].parts[gCounter6ED08_03001800.partA7].name[1];
    if (kind == 13)
        goto first;
    if (kind == 14) {
    first:
        gCounter6ED08_03001800.frame51 = 0;
        gCounter6ED08_03001800.counterAA = 2;
        return;
    }
    if (kind == 15)
        goto second;
    if (kind == 16) {
    second:
        gCounter6ED08_03001800.frame51 = 1;
        gCounter6ED08_03001800.counterAA = 2;
        return;
    }
    if (kind == 17)
        goto third;
    if (kind == 18) {
    third:
        gCounter6ED08_03001800.frame51 = 2;
        gCounter6ED08_03001800.counterAA = 2;
        return;
    }
    if (kind == 19)
        goto fourth;
    if (kind == 20) {
    fourth:
        gCounter6ED08_03001800.frame51 = 3;
        gCounter6ED08_03001800.counterAA = 2;
        return;
    }
fail:
    gCounter6ED08_03001800.counterAA++;
}
