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
#include "gba.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_work.h"

struct LeanCounter1800 {
    u8 unknown00[0x3C];
    u8 byte3C;
    u8 unknown3D[0x7];
    u8 byte44;
    u8 unknown45[0x1B];
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

extern const u8 gUnknown_084CBBBC[];
extern const u8 gUnknown_084CDD68[];
extern const u8 gUnknown_0850F738[];
extern const u8 gUnknown_0850F8B8[];
extern struct LeanCounter1800 gCounter6ED08_03001800;

void sub_0801ED50(void);

void sub_0801ED50(void) {

    u8 *buf = gSetupBuffer_03000590;
    u32 slot = gCounter6ED08_03001800.byteA7 * 0x18;

    if (buf[slot + (gCounter6ED08_03001800.byte87 << 8) + 0x49] == 0x30) {
        LeDecompress(gUnknown_084CDD68, (void *)0x06010000);
        CpuFastSet(gUnknown_0850F8B8, (void *)0x050003C0, 8);
        gFrameObjects[0xA].frameAndGroup = 0x2100;
        sub_08074DE0(0x54);
    } else {
        LeDecompress(gUnknown_084CBBBC, (void *)0x06010000);
        CpuFastSet(gUnknown_0850F738, (void *)0x050003C0, 8);
        gFrameObjects[0xA].frameAndGroup = 0x1500;
        sub_08074DE0(0x2A);
    }
    gFrameObjects[0xA].flags = 0xC404;
    gFrameObjects[0xA].tableSelector = 0;
    gFrameObjects[0xA].palette = 0xE;
    gFrameObjects[0xA].priority = 0x80;
    gFrameObjects[0xA].unknown23[0] = 0;
    if (!(gCounter6ED08_03001800.flagsF8 & 2)) {
        if (gCounter6ED08_03001800.group8B == 2)
            gFrameObjects[0xA].screenX = gCounter6ED08_03001800.positions[2] - 0x10;
        else
            gFrameObjects[0xA].screenX = gCounter6ED08_03001800.positions[2];
        gFrameObjects[0xA].screenY = gCounter6ED08_03001800.positions[3];
    } else {
        if (gCounter6ED08_03001800.group8B == 1)
            gFrameObjects[0xA].screenX = gCounter6ED08_03001800.positions[0] + 0x10;
        else
            gFrameObjects[0xA].screenX = gCounter6ED08_03001800.positions[0];
        gFrameObjects[0xA].screenY = gCounter6ED08_03001800.positions[1];
    }
    gCounter6ED08_03001800.stepAA++;
}
