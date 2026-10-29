/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"
#include "utility_helpers.h"

struct SetupPart3B7C {
    u8 byte0;
    u8 byte1;
    u8 byte2;
    u8 byte3;
    u8 byte4;
    u8 pad5[0xC];
    u8 byte11;
    u8 pad12[6];
};
struct SetupRec3B7C {
    u8 pad0[0x40];
    u8 byte40;
    u8 pad41[7];
    struct SetupPart3B7C parts[3];
    u8 pad90[0x2C];
    u8 flagsBC;
    u8 flagsBD;
    u8 padBE[0x42];
};
struct SetupPart3D30 {
    u8 byte0;
    u8 byte1;
    u8 byte2;
    u8 byte3;
    u8 byte4;
    u8 byte5;
    u8 byte6;
    u8 pad7[0x11];
};
struct SetupRec3D30 {
    u8 pad0[0x48];
    struct SetupPart3D30 parts[3];
    u8 pad90[0x12];
    u8 byteA2;
    u8 padA3[0x2D];
    u8 byteD0;
    u8 byteD1;
    u8 padD2;
    u8 byteD3;
    u8 byteD4;
    u8 padD5;
    u8 byteD6;
    u8 padD7;
    s16 wordD8;
    u8 padDA[0x26];
};
struct Rec3D30 {
    u8 pad0[3];
    u8 byte3;
    u8 pad4;
    u8 byte5;
    u8 pad6[2];
};
struct Work3D30 {
    u8 pad00[0x28];
    struct Rec3D30 recs28[5];
    u8 pad50[0x37];
    u8 slot87;
    u8 value88;
    u8 pad89;
    u8 byte8A;
    u8 pad8B[0x1C];
    u8 partA7;
    u8 padA8[0x36];
    u8 byteDE;
    u8 byteDF;
    u8 padE0[0xA];
    u16 wordEA;
    s16 valueEC;
};

extern const u8 gUnknown_084E2D80[];
extern const u8 gUnknown_084E3138[];
extern const u8 gUnknown_084E4658[];
extern const u8 gUnknown_085104B8[];
extern struct SetupRec3B7C gSetupRecs3B7C[] asm("gSetupBuffer_03000590");
extern struct SetupRec3D30 gSetupRecs3D30[] asm("gSetupBuffer_03000590");
extern struct Work3D30 gWork3D30 asm("gCounter6ED08_03001800");
extern void sub_08036120(s32 arg0);

void sub_0802EE14(void);
void sub_0802F9B8(void);
void sub_08033B7C(void);
void sub_08033D30(void);
void sub_08034FC8(u32 row, u32 frame, u32 kind);
void sub_08035C70(void);

void sub_0802EE14(void) {

    u32 i;

    if (gState0TypedWork.widths.word86 != 0) {
        gState0TypedWork.widths.word86--;
        return;
    }
    LeDecompress(gUnknown_084E2D80, (void *)0x06015400);
    CpuFastSet(gUnknown_084E4658, (void *)0x050002C0, 8);
    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            gFrameObjects[i + 0x24].flags = 0xC624;
            gFrameObjects[i + 0x24].tableSelector = 0;
            gFrameObjects[i + 0x24].screenX = gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenX;
            gFrameObjects[i + 0x24].screenY = gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenY - 4;
            gFrameObjects[i + 0x24].scaleX = 0x40;
            gFrameObjects[i + 0x24].scaleY = 0x40;
            gFrameObjects[i + 0x24].angle = 0;
            gFrameObjects[i + 0x24].palette = 6;
            gFrameObjects[i + 0x24].priority = 0xF0;
            gFrameObjects[i + 0x24].unknown23[0] = 0;
            gFrameObjects[i + 0x24].frameAndGroup = 0x8100;
        }
    }
    sub_08074DE0(0x2A);
    gCounter6ED08_03001800.counterAA++;
}

void sub_0802F9B8(void) {

    LeDecompress(gUnknown_084E3138, (void *)0x06014800);
    CpuFastSet(gUnknown_085104B8, (void *)0x050002C0, 8);
    CpuFastSet(gUnknown_084E4658, (void *)0x050002E0, 8);
    gFrameObjects[0x21].flags = 0xC404;
    gFrameObjects[0x21].tableSelector = 0;
    gFrameObjects[0x21].screenY = gFrameObjects[gCounter6ED08_03001800.slot87 * 4 + 0x5D].screenY - 0x1C;
    gFrameObjects[0x21].palette = 6;
    gFrameObjects[0x21].priority = 0xF0;
    gFrameObjects[0x21].frameAndGroup = 0x8300;
    if (!(1 & gCounter6ED08_03001800.flagsF8))
        gFrameObjects[0x21].screenX = gFrameObjects[gCounter6ED08_03001800.slot87 * 4 + 0x5D].screenX - 0x18;
    else
        gFrameObjects[0x21].screenX = gFrameObjects[gCounter6ED08_03001800.slot87 * 4 + 0x5D].screenX + 0x18;
    gFrameObjects[0x22].flags = 0xC404;
    gFrameObjects[0x22].tableSelector = 0;
    gFrameObjects[0x22].screenY = gFrameObjects[gCounter6ED08_03001800.slot87 * 4 + 0x5D].screenY - 0x1C;
    gFrameObjects[0x22].palette = 7;
    gFrameObjects[0x22].priority = 0xF1;
    gFrameObjects[0x22].frameAndGroup = 0x8301;
    if (!(1 & gCounter6ED08_03001800.flagsF8)) {
        gFrameObjects[0x22].screenX = gFrameObjects[gCounter6ED08_03001800.slot87 * 4 + 0x5D].screenX + 0x18;
    } else {
        gFrameObjects[0x22].screenX = gFrameObjects[gCounter6ED08_03001800.slot87 * 4 + 0x5D].screenX - 0x18;
        gFrameObjects[0x22].flags |= 0x1000;
    }
    gState0TypedWork.widths.word86 = 0;
    sub_08074DE0(0x2B);
    gCounter6ED08_03001800.counterAA++;
}

void sub_08033B7C(void) {

    u8 kind = gSetupRecs3B7C[gCounter6ED08_03001800.slot87].parts[gCounter6ED08_03001800.partA7].byte2;

    if (kind == 0)
        goto both;
    if (kind == 1) {
    both:
        gSetupRecs3B7C[gCounter6ED08_03001800.slot87].flagsBC |= 2;
        if (gSetupRecs3B7C[gCounter6ED08_03001800.slot87].parts[gCounter6ED08_03001800.partA7].byte2 == 1)
            gSetupRecs3B7C[gCounter6ED08_03001800.slot87].flagsBC |= 1;
    } else if (kind == 3) {
        gSetupRecs3B7C[gCounter6ED08_03001800.slot87].flagsBC |= 1;
    }
    sub_08034F08();
}

void sub_08033D30(void) {

    gWork3D30.valueEC = 0;
    gWork3D30.valueEC = gSetupRecs3D30[gWork3D30.slot87].parts[gWork3D30.partA7].byte6 + gWork3D30.wordEA;
    gWork3D30.valueEC += gSetupRecs3D30[gWork3D30.slot87].byteD0;
    if (gSetupRecs3D30[gWork3D30.slot87].parts[gWork3D30.partA7].byte2 == 0)
        goto add_d3;
    if (gSetupRecs3D30[gWork3D30.slot87].parts[gWork3D30.partA7].byte2 == 1) {
    add_d3:
        gWork3D30.valueEC += gSetupRecs3D30[gWork3D30.slot87].byteD3;
    }
    if (gSetupRecs3D30[gWork3D30.slot87].parts[gWork3D30.partA7].byte2 == 2)
        goto add_d4;
    if (gSetupRecs3D30[gWork3D30.slot87].parts[gWork3D30.partA7].byte2 == 3) {
    add_d4:
        gWork3D30.valueEC += gSetupRecs3D30[gWork3D30.slot87].byteD4;
    }
    if (gSetupRecs3D30[gWork3D30.slot87].parts[gWork3D30.partA7].byte2 == 1)
        gWork3D30.valueEC += gSetupRecs3D30[gWork3D30.slot87].byteA2 / 2;
    if (gSetupRecs3D30[gWork3D30.slot87].parts[gWork3D30.partA7].byte1 == 4)
        goto add_part;
    if (gSetupRecs3D30[gWork3D30.slot87].parts[gWork3D30.partA7].byte1 == 5) {
    add_part:
        gWork3D30.valueEC += gSetupRecs3D30[gWork3D30.slot87].parts[gWork3D30.partA7].byte6;
    }
    if (1 & gSetupRecs3D30[gWork3D30.slot87].byteD6)
        gWork3D30.valueEC += gSetupRecs3D30[gWork3D30.slot87].parts[gWork3D30.partA7].byte6;
    if (gSetupRecs3D30[gWork3D30.slot87].parts[gWork3D30.partA7].byte1 == 0x34
        && gWork3D30.recs28[gWork3D30.byte8A].byte3 == 0x33)
        gWork3D30.valueEC += gWork3D30.recs28[gWork3D30.byte8A].byte5;
    sub_08035B9C(gWork3D30.slot87);
    sub_08035754(&gWork3D30.valueEC, gSetupRecs3D30[gWork3D30.value88].byteD1);
    if (gWork3D30.byteDE != 0 && gWork3D30.byteDF == 0x1B)
        sub_08035754(&gWork3D30.valueEC, gSetupRecs3D30[gWork3D30.value88].wordD8);
    sub_08034F08();
}

void sub_08034FC8(u32 row, u32 frame, u32 kind) {

    if (kind == 0) {
        switch ((frame & 6) >> 1) {
        case 1:
            gFrameObjects[row * 4 + 0x5D].screenX = gCounter6ED08_03001800.pos13C[row].x + 1;
            gFrameObjects[row * 4 + 0x5D].screenY = gCounter6ED08_03001800.pos13C[row].y;
            break;
        case 3:
            gFrameObjects[row * 4 + 0x5D].screenX = gCounter6ED08_03001800.pos13C[row].x - 1;
            gFrameObjects[row * 4 + 0x5D].screenY = gCounter6ED08_03001800.pos13C[row].y;
            break;
        default:
            gFrameObjects[row * 4 + 0x5D].screenX = gCounter6ED08_03001800.pos13C[row].x;
            gFrameObjects[row * 4 + 0x5D].screenY = gCounter6ED08_03001800.pos13C[row].y;
            break;
        }
    } else {
        switch ((frame & 6) >> 1) {
        case 1:
            gFrameObjects[row * 4 + 0x5D].screenY = gCounter6ED08_03001800.pos13C[row].y - 2;
            break;
        case 3:
            gFrameObjects[row * 4 + 0x5D].screenY = gCounter6ED08_03001800.pos13C[row].y;
            break;
        default:
            gFrameObjects[row * 4 + 0x5D].screenY = gCounter6ED08_03001800.pos13C[row].y - 1;
            break;
        }
    }
    sub_080350E0(row);
}

void sub_08035C70(void) {

    sub_080445F4();
    if (!(1 & gCounter6ED08_03001800.flagsF8)) {
        gCounter6ED08_03001800.pos154[0] = 0x3C;
        gCounter6ED08_03001800.byte114 = 0;
    } else {
        gCounter6ED08_03001800.pos154[0] = 0x12C;
        gCounter6ED08_03001800.byte114 = 0x28;
        gCounter6ED08_03001800.flagsFF |= 1;
    }
    sub_08036120(0);
    gCounter6ED08_03001800.pos154[1] = 0x50;
    sub_080447EC(0, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1],
                 gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                 (s16)gCounter6ED08_03001800.pos154[0], 0x50, gCounter6ED08_03001800.byte3C + 2,
                 4, 0, 0, 0, gCounter6ED08_03001800.byte114);
    if (!(1 & gCounter6ED08_03001800.flagsF8)) {
        gCounter6ED08_03001800.pos154[2] = 0x1C4;
        gCounter6ED08_03001800.byte115 = 0x28;
        gCounter6ED08_03001800.flagsFF |= 2;
    } else {
        gCounter6ED08_03001800.pos154[2] = 0xB4;
        gCounter6ED08_03001800.byte115 = 0;
    }
    sub_08036120(1);
    gCounter6ED08_03001800.pos154[3] = 0x50;
    sub_080447EC(1, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1],
                 gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                 (s16)gCounter6ED08_03001800.pos154[2], 0x50, gCounter6ED08_03001800.byte3C + 2,
                 8, 1, 0, 1, gCounter6ED08_03001800.byte115);
}
