/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "tile_text.h"

struct LeanCounter1800 {
    u8 unknown00[0x3C];
    u8 byte3C;
    u8 unknown3D[0x7];
    u8 byte44;
    u8 unknown45[0xC];
    u8 byte51;
    u8 unknown52[0xE];
    u8 firstObject;
    u8 unknown61[0x26];
    u8 byte87;
    u8 byte88;
    u8 unknown89[2];
    u8 group8B;
    u8 unknown8C[0x1B];
    u8 byteA7;
    u8 unknownA8[2];
    u8 stepAA;
    u8 unknownAB[0x1D];
    u16 valueC8;
    u8 unknownCA[6];
    u8 slotD0;
    u8 unknownD1;
    u8 activeD2[4];
    u16 valuesD6[4];
    u8 unknownDE[0x1A];
    u8 flagsF8;
    u8 unknownF9[0x5B];
    u16 positions[4];
};

extern const u8 *gState0NextCommands_083B6100[];
extern const u8 gUnknown_084CBE3C[];
extern const u8 gUnknown_084CF6F4[];
extern const u8 gUnknown_084CFBE4[];
extern const u8 gUnknown_084D04B4[];
extern const u8 gUnknown_084D08E0[];
extern const u8 gUnknown_0850F758[];
extern const u8 gUnknown_0850F958[];
extern const u8 gUnknown_0850F978[];
extern const u8 gUnknown_0850F998[];
extern const u8 gUnknown_0850F9B8[];
extern struct LeanCounter1800 gCounter6ED08_03001800;

void sub_0801F5BC(void);

void sub_0801F5BC(void) {

    u16 x, y;

    LeDecompress(gUnknown_084CBE3C, (void *)0x06010000);
    CpuFastSet(gUnknown_0850F758, (void *)0x050003C0, 8);
    if (!(gCounter6ED08_03001800.flagsF8 & 2)) {
        x = gCounter6ED08_03001800.positions[2];
        y = gCounter6ED08_03001800.positions[3];
    } else {
        x = gCounter6ED08_03001800.positions[0];
        y = gCounter6ED08_03001800.positions[1];
    }
    gFrameObjects[0xA].flags = 0xC624;
    gFrameObjects[0xA].tableSelector = 0;
    gFrameObjects[0xA].screenX = x;
    gFrameObjects[0xA].screenY = y;
    gFrameObjects[0xA].scaleX = 0x40;
    gFrameObjects[0xA].scaleY = 4;
    gFrameObjects[0xA].palette = 0xE;
    gFrameObjects[0xA].priority = 0xF0;
    gFrameObjects[0xA].frameAndGroup = 0x1600;
    gFrameObjects[0xA].commandDelay = 0;
    switch (gCounter6ED08_03001800.byte51) {
    case 0:
        LeDecompress(gUnknown_084CF6F4, (void *)0x06010800);
        CpuFastSet(gUnknown_0850F958, (void *)0x050003A0, 8);
        break;
    case 1:
        LeDecompress(gUnknown_084CFBE4, (void *)0x06010800);
        CpuFastSet(gUnknown_0850F978, (void *)0x050003A0, 8);
        break;
    case 2:
        LeDecompress(gUnknown_084D04B4, (void *)0x06010800);
        CpuFastSet(gUnknown_0850F998, (void *)0x050003A0, 8);
        break;
    case 3:
        LeDecompress(gUnknown_084D08E0, (void *)0x06010800);
        CpuFastSet(gUnknown_0850F9B8, (void *)0x050003A0, 8);
        break;
    }
    gFrameObjects[0xB].flags = 0xC404;
    gFrameObjects[0xB].tableSelector = 0;
    gFrameObjects[0xB].screenX = x;
    gFrameObjects[0xB].screenY = y;
    gFrameObjects[0xB].palette = 0xD;
    gFrameObjects[0xB].priority = 0x80;
    sub_08040B90(gState0NextCommands_083B6100[0x21], 0xB);
    sub_08074DE0(0x2F);
    gCounter6ED08_03001800.stepAA++;
}
