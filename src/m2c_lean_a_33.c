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
#include "display_helpers.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "record_helpers.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct Part121F0 {
    u8 name[13];
    u8 pad0D[3];
    u8 byte10;
    u8 data11[6];
    u8 id17;
};
struct Setup121F0 {
    u8 pad00[0x48];
    struct Part121F0 parts[4];
    u8 padA8[0x12];
    u8 byteBA;
    u8 padBB[0x45];
};
struct Setup170D4 {
    u8 pad00[0xDD];
    u8 partDD;
    u8 padDE[0x22];
};
struct Part2A360 {
    u8 name[13];
    u8 pad0D[3];
    u8 byte10;
    u8 data11[6];
    u8 id17;
};
struct Setup2A360 {
    u8 pad00[0x40];
    u8 active40;
    u8 pad41[7];
    struct Part2A360 parts[4];
    u8 padA8[0x58];
};

extern const u8 *gState0NextCommands_083B6100[];
extern struct Setup121F0 gSetup121F0[] asm("gSetupBuffer_03000590");
extern struct Setup170D4 gSetup170D4[] asm("gSetupBuffer_03000590");
extern struct Setup2A360 gSetup2A360[] asm("gSetupBuffer_03000590");
extern void sub_0803836C(void);

void sub_0800508C(void);
s32 sub_080121F0(void);
void sub_080170D4(void);
void sub_080277DC(void);
void sub_0802A360(void);

void sub_0800508C(void) {

    u32 i;

    for (i = 0; i <= 8; i++) {
        if (gUnknownRecords_030017A0[i].unknown00[0] != 0) {
            if (gUnknownRecords_030017A0[i].byte6 <= 0x77) {
                sub_08042B58(gUnknownRecords_030017A0[i].byte6, 3, gUnknown_0300052E);
                sub_080435B0(gUnknown_0300052E[1] - 0x64, gUnknownBytes_083AC5CD[i * 2], gUnknownBytes_083AC5CD[i * 2 + 1], *(volatile u16 *)0x0400000A, 0x8300);
            } else {
                sub_080435B0(0xFF, gUnknownBytes_083AC5CD[i * 2], gUnknownBytes_083AC5CD[i * 2 + 1], *(volatile u16 *)0x0400000A, 0x8300);
            }
        } else {
            sub_080435B0(0xFF, gUnknownBytes_083AC5CD[i * 2], gUnknownBytes_083AC5CD[i * 2 + 1], *(volatile u16 *)0x0400000A, 0x8300);
        }
    }
}

s32 sub_080121F0(void) {

    s32 score;
    u32 i;
    u32 k;

    score = 0;
    for (i = 0; i <= 2; i++) {
        if (gSetup121F0[i + 3].byteBA == 0) {
            goto done;
        }
        for (k = 1; k <= 3; k++) {
            if (gSetup121F0[i + 3].parts[k].data11[0] == 0) {
                score += 10;
            }
        }
    }
done:
    return score;
}

void sub_080170D4(void) {

    u32 part;

    part = gSetup170D4[gCounter6ED08_03001800.buffer64[0x1C]].partDD;
    if (part <= 3) {
        part = 0;
    } else {
        part -= 5;
    }
    gCounter6ED08_03001800.buffer64[0x1E] = part;
}

void sub_080277DC(void) {

    u32 i;

    LeDecompress(gActionMotionAsset_084CDF48, (void *)0x06014800);
    CpuFastSet(gActionMotionPalette_0850F8D8, (void *)0x050002E0, 8);
    for (i = 0; i <= 2; i++) {
        if (0x80 & gCounter6ED08_03001800.activeD2[i]) {
            gFrameObjects[0x21 + i].flags = 0xC004;
            gFrameObjects[0x21 + i].tableSelector = 0;
            gFrameObjects[0x21 + i].screenX = gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + (u8)((0x7F & gCounter6ED08_03001800.activeD2[i]) + 0x5A)].screenX;
            gFrameObjects[0x21 + i].screenY = gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + (u8)((0x7F & gCounter6ED08_03001800.activeD2[i]) + 0x5A)].screenY;
            gFrameObjects[0x21 + i].palette = 7;
            gFrameObjects[0x21 + i].priority = 0xF0;
            sub_08040B90(gState0NextCommands_083B6100[34], i + 0x21);
        }
    }
    gCounter6ED08_03001800.counterAA++;
}

void sub_0802A360(void) {

    u32 i;

    sub_0803836C();
    gCounter6ED08_03001800.base60 = sub_08032FC4(gCounter6ED08_03001800.slot87);
    for (i = 0; i <= 2; i++) {
        if (gSetup2A360[gCounter6ED08_03001800.base60 + i].active40 != 0
            && gSetup2A360[gCounter6ED08_03001800.base60 + i].parts[0].data11[0] != 0) {
            sub_0803F63C(&gFrameObjects[0x22], &gFrameObjects[0x23 + i], 0x40);
            gFrameObjects[0x23 + i].value30 = gFrameObjects[0x5D + (gCounter6ED08_03001800.base60 + i) * 4].screenX;
            gFrameObjects[0x23 + i].value32 = gFrameObjects[0x5D + (gCounter6ED08_03001800.base60 + i) * 4].screenY - 4;
            gFrameObjects[0x23 + i].unknown23[1] = 3;
            gFrameObjects[0x23 + i].unknown23[0] = 0;
            gCounter6ED08_03001800.activeD2[i] = 1;
        }
    }
    sub_08040CD0(0x22, 1);
    gCounter6ED08_03001800.counterAA++;
}
