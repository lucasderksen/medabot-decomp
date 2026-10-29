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
#include "state0_next_helpers.h"

struct Work21038 { u8 pad[0x51]; u8 mode51; u8 pad52[0x58]; u8 counterAA; u8 padAB[0x4D]; u8 flagsF8; };

extern const u8 *gState0NextCommands_083B6100[];
extern const u8 gUnknown_084D66DC[];
extern const u8 gUnknown_0850FC18[];
extern struct Work21038 gWork21038 asm("gCounter6ED08_03001800");

void sub_08021038(void);

void sub_08021038(void) {

    switch (gWork21038.mode51) {
    case 0:
        LeDecompress(gActionKindAsset_084CA61C, (void *)0x06014800);
        CpuFastSet(gActionKindPalette_0850F5F8, (void *)0x050002E0, 8);
        gFrameObjects[0x21].screenY = 0x3C;
        sub_08040B90(gState0NextCommands_083B6100[25], 0x21);
        break;
    case 1:
        LeDecompress(gActionKindAsset_084CA828, (void *)0x06014800);
        CpuFastSet(gActionKindPalette_0850F618, (void *)0x050002E0, 8);
        gFrameObjects[0x21].screenY = 0x3C;
        sub_08040B90(gState0NextCommands_083B6100[26], 0x21);
        break;
    case 2:
        LeDecompress(gActionKindAsset_084CABC4, (void *)0x06014800);
        CpuFastSet(gActionKindPalette_0850F638, (void *)0x050002E0, 8);
        gFrameObjects[0x21].screenY = 0x3C;
        gFrameObjects[0x21].frameAndGroup = 0xD00;
        break;
    case 3:
        LeDecompress(gUnknown_084D66DC, (void *)0x06014800);
        CpuFastSet(gUnknown_0850FC18, (void *)0x050002E0, 8);
        sub_08040B90(gState0NextCommands_083B6100[56], 0x21);
        break;
    }
    gFrameObjects[0x21].flags |= 0x220;
    gFrameObjects[0x21].scaleY = 0x40;
    gFrameObjects[0x21].scaleX = 8;
    if (gWork21038.flagsF8 & 1) {
        gFrameObjects[0x21].flags |= 0x1000;
        gFrameObjects[0x21].screenX--;
    }
    gWork21038.counterAA++;
}
