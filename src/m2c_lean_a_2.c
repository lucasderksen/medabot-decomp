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
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

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
    u8 unknown8C[0x1E];
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

extern const u8 gCompressedGraphics_084CE3E8[];
extern const u8 gPaletteBytes_0850F8F8[];
extern const u8 gUnknown_084CB9C8[];
extern const u8 gUnknown_084CBBBC[];
extern const u8 gUnknown_084CF274[];
extern const u8 gUnknown_084D2DC4[];
extern const u8 gUnknown_0850F598[];
extern const u8 gUnknown_0850F5B8[];
extern const u8 gUnknown_0850F718[];
extern const u8 gUnknown_0850F738[];
extern const u8 gUnknown_0850F938[];
extern struct LeanCounter1800 gCounter6ED08_03001800;
extern void sub_08036784(u32 kind, u32 group, s32 x, s32 y);
extern void sub_080368C4(u8 *text, u32 kind, u32 group, s32 x, s32 y);
extern void sub_080369C8(u8 *text, u32 kind, u32 index, s32 x, s32 y);
extern void sub_08036C20(u32 kind, u32 group, s32 x, s32 y, u32 duration);

void sub_0801AD48(u32 side);
extern void sub_0801E864(void);
void sub_0801EEE4(void);
extern void sub_0801F214(void);
extern void sub_0801F2DC(void);
extern void sub_08026924(void);
extern void sub_08026AF4(void);
void sub_08026D98(void);

void sub_0801AD48(u32 side) {

    u32 i;

    sub_08040CD0(0x78, 8);
    for (i = 0; i <= 7; i++) {
        gFrameObjects[i + 0x78].flags = 0xC404;
        gFrameObjects[i + 0x78].tableSelector = 0;
        gFrameObjects[i + 0x78].screenY = 0x78;
        gFrameObjects[i + 0x78].palette = 9;
        gFrameObjects[i + 0x78].priority = 0x80;
        gFrameObjects[i + 0x78].frameAndGroup = (i & 3) + 0x616;
        gFrameObjects[i + 0x78].unknown23[1] = 0;
        gFrameObjects[i + 0x78].unknown23[3] = 7 - i;
        gFrameObjects[i + 0x78].unknown23[5] = 0;
        gFrameObjects[i + 0x78].unknown23[4] = i * 2;
        gFrameObjects[i + 0x78].commandOffset = 0;
        gFrameObjects[i + 0x78].commandStopped = i & 3;
        if (side <= 2) {
            gFrameObjects[i + 0x78].flags |= 0x1000;
            gFrameObjects[i + 0x78].screenX = 0x5C;
        } else {
            gFrameObjects[i + 0x78].flags &= 0xEFFF;
            gFrameObjects[i + 0x78].screenX = 0x94;
        }
    }
}

void sub_0801E864(void) {

    u16 x, y;

    LeDecompress(gActionMotionAsset_084CDF48, (void *)0x06010800);
    CpuFastSet(gActionMotionPalette_0850F8D8, (void *)0x050003C0, 8);
    if (!(gCounter6ED08_03001800.flagsF8 & 2)) {
        x = gCounter6ED08_03001800.positions[2];
        y = gCounter6ED08_03001800.positions[3];
    } else {
        x = gCounter6ED08_03001800.positions[0];
        y = gCounter6ED08_03001800.positions[1];
    }
    sub_08036784(10, gCounter6ED08_03001800.group8B, (s16)x, (s16)y);
    gCounter6ED08_03001800.stepAA++;
}

void sub_0801EEE4(void) {

    LeDecompress(gUnknown_084CB9C8, (void *)0x06010000);
    CpuFastSet(gUnknown_0850F718, (void *)0x050003C0, 8);
    gFrameObjects[0xA].flags = 0xC404;
    gFrameObjects[0xA].tableSelector = 0;
    gFrameObjects[0xA].palette = 0xE;
    gFrameObjects[0xA].priority = 0x80;
    gFrameObjects[0xA].frameAndGroup = 0x1400;
    gFrameObjects[0xA].unknown23[0] = 0;
    if (!(gCounter6ED08_03001800.flagsF8 & 2)) {
        gFrameObjects[0xA].screenX = gCounter6ED08_03001800.positions[2];
        gFrameObjects[0xA].screenY = gCounter6ED08_03001800.positions[3] - 0x10;
        *(u16 *)&gFrameObjects[0xA].unknown2C[4] = gCounter6ED08_03001800.positions[3];
    } else {
        gFrameObjects[0xA].screenX = gCounter6ED08_03001800.positions[0];
        gFrameObjects[0xA].screenY = gCounter6ED08_03001800.positions[1] - 0x10;
        *(u16 *)&gFrameObjects[0xA].unknown2C[4] = gCounter6ED08_03001800.positions[1];
    }
    sub_08074DE0(0x2F);
    gCounter6ED08_03001800.stepAA++;
}

void sub_0801F214(void) {

    u16 x, y;

    LeDecompress(gUnknown_084CF274, (void *)0x06010800);
    CpuFastSet(gUnknown_0850F938, (void *)0x050003C0, 8);
    if (!(gCounter6ED08_03001800.flagsF8 & 2)) {
        x = gCounter6ED08_03001800.positions[2];
        y = gCounter6ED08_03001800.positions[3];
    } else {
        x = gCounter6ED08_03001800.positions[0];
        y = gCounter6ED08_03001800.positions[1];
    }
    sub_08036C20(10, gCounter6ED08_03001800.group8B, (s16)x, (s16)y, 0x20);
    gCounter6ED08_03001800.stepAA++;
}

void sub_0801F2DC(void) {

    u16 x, y;

    LeDecompress(gUnknown_084D2DC4, (void *)0x06010000);
    CpuFastSet(gUnknown_0850F598, (void *)0x050003C0, 8);
    if (!(gCounter6ED08_03001800.flagsF8 & 2)) {
        x = gCounter6ED08_03001800.positions[2];
        y = gCounter6ED08_03001800.positions[3];
    } else {
        x = gCounter6ED08_03001800.positions[0];
        y = gCounter6ED08_03001800.positions[1];
    }
    sub_0801A28C(gUnknown_0300052E, gCounter6ED08_03001800.valueC8, 0);
    sub_080368C4(gUnknown_0300052E, 10, gCounter6ED08_03001800.group8B, (s16)x, (s16)y);
    sub_08074DE0(0x5B);
    gCounter6ED08_03001800.stepAA++;
}

void sub_08026924(void) {

    u16 x, y;
    s16 sx, sy;

    LeDecompress(gUnknown_084D2DC4, (void *)0x06010000);
    CpuFastSet(gUnknown_0850F5B8, (void *)0x050003C0, 8);
    if (!(gCounter6ED08_03001800.flagsF8 & 2)) {
        x = gCounter6ED08_03001800.positions[2];
        y = gCounter6ED08_03001800.positions[3];
    } else {
        x = gCounter6ED08_03001800.positions[0];
        y = gCounter6ED08_03001800.positions[1];
    }
    sub_0801A28C(gDebugMenuTextBuffer, gCounter6ED08_03001800.valuesD6[0], 1);
    sub_080369C8(gDebugMenuTextBuffer, 10, 0, (s16)x, (s16)y);
    sub_0801A28C(gDebugMenuTextBuffer + 0x14, gCounter6ED08_03001800.valuesD6[1], 1);
    sub_080369C8(gDebugMenuTextBuffer + 0x14, 14, 1, (s16)x, (s16)y);
    sub_0801A28C(gDebugMenuTextBuffer + 0x28, gCounter6ED08_03001800.valuesD6[2], 1);
    sub_080369C8(gDebugMenuTextBuffer + 0x28, 18, 2, (s16)x, (s16)y);
    sub_0801A28C(gDebugMenuTextBuffer + 0x3C, gCounter6ED08_03001800.valuesD6[3], 1);
    sub_080369C8(gDebugMenuTextBuffer + 0x3C, 22, 3, (s16)x, (s16)y);
    sub_08074DE0(0x5B);
    gCounter6ED08_03001800.stepAA++;
}

void sub_08026AF4(void) {

    u16 x, y;
    u32 shown = 0;

    LeDecompress(gCompressedGraphics_084CE3E8, (void *)0x06010800);
    CpuFastSet(gPaletteBytes_0850F8F8, (void *)0x050003C0, 8);
    if (!(gCounter6ED08_03001800.flagsF8 & 2)) {
        x = gCounter6ED08_03001800.positions[2];
        y = gCounter6ED08_03001800.positions[3];
    } else {
        x = gCounter6ED08_03001800.positions[0];
        y = gCounter6ED08_03001800.positions[1];
    }
    if (gCounter6ED08_03001800.activeD2[0]) {
        sub_08036C20(10, 0, (s16)x, (s16)y, 0x1E);
        shown = 1;
    }
    if (gCounter6ED08_03001800.activeD2[1]) {
        sub_08036C20(11, 1, (s16)x, (s16)y, 0x1E);
        shown = 1;
    }
    if (gCounter6ED08_03001800.activeD2[2]) {
        sub_08036C20(12, 2, (s16)x, (s16)y, 0x1E);
        shown = 1;
    }
    if (gCounter6ED08_03001800.activeD2[3]) {
        sub_08036C20(13, 3, (s16)x, (s16)y, 0x1E);
        shown = 1;
    }
    if (shown) {
        sub_08035194(gCounter6ED08_03001800.byte88);
        gCounter6ED08_03001800.stepAA = 13;
    } else {
        gCounter6ED08_03001800.stepAA++;
    }
}

void sub_08026D98(void) {

    LeDecompress(gUnknown_084CBBBC, (void *)0x06010000);
    CpuFastSet(gUnknown_0850F738, (void *)0x050003C0, 8);
    gFrameObjects[0xA].frameAndGroup = 0x1500;
    sub_08074DE0(0x2A);
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
