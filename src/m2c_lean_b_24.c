/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "coordinate_helpers.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"
#include "utility_helpers.h"

struct SetupPart38D30 {
    u8 pad0[0x11];
    u8 byte11;
    u8 pad12[6];
};
struct SetupRecord38D30 {
    u8 pad0[0x48];
    struct SetupPart38D30 parts[3];
    u8 pad90[0x2C];
    u8 flagsBC;
    u8 flagsBD;
    u8 padBE[2];
    u8 flagsC0;
    u8 padC1[0x1D];
    u8 partDE;
    u8 padDF[0x21];
};
struct Frame39AC8 {
    u8 pad00[0x29];
    u8 byte29;
    u8 pad2A;
    u8 byte2B;
    u8 byte2C;
    u8 byte2D;
    u8 byte2E;
    u8 pad2F;
    u16 word30;
    u8 pad32[0xE];
};
struct SetupRecord39AC8 {
    u8 pad0[0x91];
    u8 byte91;
    u8 pad92[0x6E];
};

extern const u16 gState0MotionSteps_083AF7B0[32];
extern const u8 *const gState0NextCommands_083B6100[];
extern const u8 *const gUnknown_083AFA08[];
extern struct Frame39AC8 gFrames39AC8[] asm("gFrameObjects");
extern struct SetupRecord38D30 gSetupRecords38D30[] asm("gSetupBuffer_03000590");
extern struct SetupRecord39AC8 gSetupRecords39AC8[] asm("gSetupBuffer_03000590");
extern void sub_08035944(u32, u32);
extern void sub_08036120(s32);
extern void sub_08037A94(u32);
extern void sub_0803D450(void);
extern void sub_0803D4AC(void);

void sub_08037E2C(void);
void sub_080388A4(void);
void sub_08038AC0(void);
void sub_08038D30(void);
void sub_08039AC8(void);
void sub_08039E00(void);

void sub_08037E2C(void) {

    union {struct TileCoordinates coordinates;s32 word;} result4;
    union {struct TileCoordinates coordinates;s32 word;} result8;
    s32 packedPosition;
    struct FrameObject *radiusFrame;
    struct FrameObject *f;
    struct FrameObject *statusFrame;
    u32 frameRoot;

    sub_08040BD8(gState0NextCommands_083B6100[gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown2C[2]], gState0TypedWork.bytes[0x12F]);
    statusFrame = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
    if (statusFrame->unknown2C[1] == 0xFF) {
        statusFrame->unknown23[6] += 1;
        return;
    }
    if ((statusFrame->unknown2C[1]&0x3FU)==0) {
        switch (gCounter6ED08_03001800.frame51) {
        case 0:
            sub_08074DE0(0x5DU);
            break;
        case 1:
            sub_08074DE0(0x2EU);
            break;
        case 2:
            sub_08074DE0(0x4BU);
            break;
        }
    }
    frameRoot=(u32)gFrameObjects;
    radiusFrame=(struct FrameObject*)(frameRoot+((u32)gState0TypedWork.bytes[0x12F]<<6));
    radiusFrame->byte2B += gState0MotionSteps_083AF7B0[radiusFrame->unknown2C[1]&0x1Fu];
    if (1 & gCounter6ED08_03001800.flagsF8) {
        if (gCounter6ED08_03001800.frame51 == 0) {
            gFrameObjects[gState0TypedWork.bytes[0x12F]].angle = (gFrameObjects[gState0TypedWork.bytes[0x12F]].angle - 0x10) & 0x3FF;
        }
        gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown2C[0] -= 1;
        result4.coordinates=sub_08042BC0(gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown2C[0],gFrameObjects[gState0TypedWork.bytes[0x12F]].byte2B,0xB8U,0x34);
        packedPosition=result4.word;
    } else {
        if (gCounter6ED08_03001800.frame51 == 0) {
            gFrameObjects[gState0TypedWork.bytes[0x12F]].angle = (gFrameObjects[gState0TypedWork.bytes[0x12F]].angle + 0x10) & 0x3FF;
        }
        gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown2C[0] += 1;
        result8.coordinates=sub_08042BC0(gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown2C[0],gFrameObjects[gState0TypedWork.bytes[0x12F]].byte2B,0x38U,0x34);
        packedPosition=result8.word;
    }
    gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX = (s16) packedPosition;
    gFrameObjects[gState0TypedWork.bytes[0x12F]].screenY = (s16) (packedPosition >> 0x10);
    sub_08037A94(gState0TypedWork.bytes[0x12F]);
    gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown2C[1] += 1;
}

void sub_080388A4(void) {

    sub_08040BD8(gState0NextCommands_083B6100[109], gState0TypedWork.bytes[0x12F]);
    if (!(1 & gCounter6ED08_03001800.flagsF8)) {
        gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX = (gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX + 4) & 0x1FF;
        if (gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX > gFrameObjects[(gCounter6ED08_03001800.base60 + (gState0TypedWork.bytes[0x12F] - 0x21)) * 4 + 0x5D].screenX
            && gCounter6ED08_03001800.valuesD6[gState0TypedWork.bytes[0x12F] - 0x21] != 0
            && gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown23[5] == 0) {
            sub_08074DE0(0x54);
            gFrameObjects[gState0TypedWork.bytes[0x12F] + 3].flags = 0xC404;
            gFrameObjects[gState0TypedWork.bytes[0x12F] + 3].tableSelector = 0;
            gFrameObjects[gState0TypedWork.bytes[0x12F] + 3].screenX = gFrameObjects[(gCounter6ED08_03001800.base60 + (gState0TypedWork.bytes[0x12F] - 0x21)) * 4 + 0x5D].screenX;
            gFrameObjects[gState0TypedWork.bytes[0x12F] + 3].screenY = gFrameObjects[(gCounter6ED08_03001800.base60 + (gState0TypedWork.bytes[0x12F] - 0x21)) * 4 + 0x5D].screenY - 4;
            gFrameObjects[gState0TypedWork.bytes[0x12F] + 3].palette = 6;
            gFrameObjects[gState0TypedWork.bytes[0x12F] + 3].priority = 0xF1;
            gFrameObjects[gState0TypedWork.bytes[0x12F] + 3].unknown23[6] = 2;
            gFrameObjects[gState0TypedWork.bytes[0x12F] + 3].unknown23[5] = 0;
            sub_08040B90(gState0NextCommands_083B6100[110], gState0TypedWork.bytes[0x12F] + 3);
            gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown23[5] = 1;
        }
    } else {
        gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX = (gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX - 4) & 0x1FF;
        if (gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX < gFrameObjects[(gCounter6ED08_03001800.base60 + (gState0TypedWork.bytes[0x12F] - 0x21)) * 4 + 0x5D].screenX
            && gCounter6ED08_03001800.valuesD6[gState0TypedWork.bytes[0x12F] - 0x21] != 0
            && gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown23[5] == 0) {
            sub_08074DE0(0x54);
            gFrameObjects[gState0TypedWork.bytes[0x12F] + 3].flags = 0xD404;
            gFrameObjects[gState0TypedWork.bytes[0x12F] + 3].tableSelector = 0;
            gFrameObjects[gState0TypedWork.bytes[0x12F] + 3].screenX = gFrameObjects[(gCounter6ED08_03001800.base60 + (gState0TypedWork.bytes[0x12F] - 0x21)) * 4 + 0x5D].screenX;
            gFrameObjects[gState0TypedWork.bytes[0x12F] + 3].screenY = gFrameObjects[(gCounter6ED08_03001800.base60 + (gState0TypedWork.bytes[0x12F] - 0x21)) * 4 + 0x5D].screenY - 4;
            gFrameObjects[gState0TypedWork.bytes[0x12F] + 3].palette = 6;
            gFrameObjects[gState0TypedWork.bytes[0x12F] + 3].priority = 0xF1;
            gFrameObjects[gState0TypedWork.bytes[0x12F] + 3].unknown23[6] = 2;
            gFrameObjects[gState0TypedWork.bytes[0x12F] + 3].unknown23[5] = 0;
            sub_08040B90(gState0NextCommands_083B6100[110], gState0TypedWork.bytes[0x12F] + 3);
            gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown23[5] = 1;
        }
    }
    if (gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown23[4] > 0x28)
        sub_08040CD0(gState0TypedWork.bytes[0x12F], 1);
    else
        gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown23[4]++;
}

void sub_08038AC0(void) {

    s32 row;

    gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown23[5]++;
    if (2 & gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown23[5]) {
        row = gCounter6ED08_03001800.base60 + (gState0TypedWork.bytes[0x12F] - 0x24);
        gFrameObjects[row * 4 + 0x5D].screenX = gCounter6ED08_03001800.pos13C[row].x + 2;
    } else {
        row = gCounter6ED08_03001800.base60 + (gState0TypedWork.bytes[0x12F] - 0x24);
        gFrameObjects[row * 4 + 0x5D].screenX = gCounter6ED08_03001800.pos13C[row].x - 2;
    }
    sub_080350E0(gCounter6ED08_03001800.base60 + (gState0TypedWork.bytes[0x12F] - 0x24));
    sub_08040BD8(gState0NextCommands_083B6100[110], gState0TypedWork.bytes[0x12F]);
    if (gFrameObjects[gState0TypedWork.bytes[0x12F]].commandStopped == 0xFF) {
        gFrameObjects[(gCounter6ED08_03001800.base60 + (gState0TypedWork.bytes[0x12F] - 0x24)) * 4 + 0x5D].screenX = gCounter6ED08_03001800.pos13C[(gCounter6ED08_03001800.base60 + (gState0TypedWork.bytes[0x12F] - 0x24))].x;
        sub_080350E0(gCounter6ED08_03001800.base60 + (gState0TypedWork.bytes[0x12F] - 0x24));
        sub_08040CD0(gState0TypedWork.bytes[0x12F], 1);
    }
}

void sub_08038D30(void) {

    gSetupRecords38D30[gCounter6ED08_03001800.value88].flagsBC &= 3;
    gSetupRecords38D30[gCounter6ED08_03001800.value88].flagsBD |= 2;
    if (gCounter6ED08_03001800.flagDE != 0) {
        gSetupRecords38D30[gCounter6ED08_03001800.value88].flagsBC |= 0xC;
        gCounter6ED08_03001800.valueF2 = gCounter6ED08_03001800.valueE8;
        gCounter6ED08_03001800.flagAB = 1;
        if ((1 & gSetupRecords38D30[gCounter6ED08_03001800.value88].flagsC0) && (sub_080424B8() & 1)) {
            gCounter6ED08_03001800.flagsF6 = 1;
            gCounter6ED08_03001800.byteB7 = 3;
        }
    } else {
        if (!(4 & gSetupRecords38D30[gCounter6ED08_03001800.slot87].flagsC0)
            && (0x10 & gSetupRecords38D30[gCounter6ED08_03001800.value88].flagsBD)
            && gSetupRecords38D30[gCounter6ED08_03001800.value88].parts[gSetupRecords38D30[gCounter6ED08_03001800.value88].partDE - 1].byte11 != 0) {
            gSetupRecords38D30[gCounter6ED08_03001800.value88].flagsBC |= 0xC;
            gCounter6ED08_03001800.valueF2 = gCounter6ED08_03001800.valueE8;
            sub_08035944(gCounter6ED08_03001800.slot87, gSetupRecords38D30[gCounter6ED08_03001800.value88].partDE);
            gCounter6ED08_03001800.flagsF6 = 1;
            gCounter6ED08_03001800.flagAB = 1;
            return;
        }
        gCounter6ED08_03001800.flagAB = 0;
    }
}

void sub_08039AC8(void) {

    s32 column;
    const u8 *row;
    u32 rowSlots;
    u32 rowOffset;

    sub_0803D450();
    gFrames39AC8[gCounter6ED08_03001800.value102 + 5].word30 = gCounter6ED08_03001800.value104;
    gFrames39AC8[gCounter6ED08_03001800.value102 + 5].byte2C = 0;
    gFrames39AC8[gCounter6ED08_03001800.value102 + 5].byte2D = gCounter6ED08_03001800.value108;
    gFrames39AC8[gCounter6ED08_03001800.value102 + 5].byte2E = gCounter6ED08_03001800.value10A;
    gFrames39AC8[gCounter6ED08_03001800.value102 + 5].byte29 = 0x18;
    if (2 & gCounter6ED08_03001800.flagsF6)
        sub_08015838(gCounter6ED08_03001800.value161, gCounter6ED08_03001800.buffer64);
    else
        sub_08015838(gCounter6ED08_03001800.slot87, gCounter6ED08_03001800.buffer64);
    if (gCounter6ED08_03001800.buffer64[3] > 0x77) {
        column = 3;
    } else {
        if (2 & gCounter6ED08_03001800.flagsF6)
            column = gSetupRecords39AC8[gCounter6ED08_03001800.value161].byte91 - 0x64;
        else
            column = gSetupRecords39AC8[gCounter6ED08_03001800.slot87].byte91 - 0x64;
    }
    rowSlots = (u32)gUnknown_083AFA08;
    rowOffset = (u32)gCounter6ED08_03001800.index106 << 2;
    row = *(const u8 *const *)(rowSlots + rowOffset);
    gFrames39AC8[gCounter6ED08_03001800.value102 + 5].byte2B = row[column];
    sub_0803D4AC();
}

void sub_08039E00(void) {

    u8 side;

    side = 2 & gCounter6ED08_03001800.flagsF8;
    if (side == 0) {
        gCounter6ED08_03001800.pos154[0] = 0x12C;
        gCounter6ED08_03001800.pos154[1] = 0x50;
        sub_08036120(0);
        sub_080447EC(0, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1], gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                     (s16)gCounter6ED08_03001800.pos154[0], (s16)gCounter6ED08_03001800.pos154[1], gCounter6ED08_03001800.byte3C + 2, 4, side, 2, side, gCounter6ED08_03001800.byte114);
        sub_080447EC(0, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1], gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                     (s16)gCounter6ED08_03001800.pos154[0], (s16)gCounter6ED08_03001800.pos154[1], gCounter6ED08_03001800.byte3C + 2, 4, side, 1, side, gCounter6ED08_03001800.byte114);
        gCounter6ED08_03001800.sideCommand112[0] = 0x29;
        sub_08044A3C(0, 0x29, gCounter6ED08_03001800.buffer64[3]);
    } else {
        gCounter6ED08_03001800.pos154[2] = 0x1C4;
        gCounter6ED08_03001800.pos154[3] = 0x50;
        sub_08036120(1);
        sub_080447EC(1, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1], gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                     (s16)gCounter6ED08_03001800.pos154[2], (s16)gCounter6ED08_03001800.pos154[3], gCounter6ED08_03001800.byte3C + 2, 8, 1, 2, 1, gCounter6ED08_03001800.byte115);
        sub_080447EC(1, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1], gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                     (s16)gCounter6ED08_03001800.pos154[2], (s16)gCounter6ED08_03001800.pos154[3], gCounter6ED08_03001800.byte3C + 2, 8, 1, 1, 1, gCounter6ED08_03001800.byte115);
        gCounter6ED08_03001800.sideCommand112[1] = 0x29;
        sub_08044A3C(1, 0x29, gCounter6ED08_03001800.buffer64[3]);
    }
    sub_0803D4AC();
}
