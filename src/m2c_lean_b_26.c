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
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "record_helpers.h"
#include "serial.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct SetupPart30A24 {
    u8 pad0;
    u8 kind1;
    u8 pad2[0xE];
    u8 uses10;
    u8 count11;
    u8 pad12[6];
};
struct SetupRecord30A24 {
    u8 pad0[0x40];
    u8 active40;
    u8 pad41[7];
    struct SetupPart30A24 parts[3];
    u8 pad90[0x2D];
    u8 flagsBD;
    u8 padBE[0xB];
    u8 kindC9;
    u8 partCA;
    u8 padCB[0x12];
    u8 partDD;
    u8 padDE[2];
    u8 targetE0;
    u8 targetPartE1;
    u8 padE2[0x1E];
};
struct Frame395E8 {
    u8 pad00[0x2B];
    u8 byte2B;
    u8 byte2C;
    u8 byte2D;
    u8 pad2E[2];
    u16 word30;
    u8 pad32[0xE];
};
struct Words395E8 {
    u8 pad00[0x102];
    u16 words[8];
};

extern const u8 *const gState0NextCommands_083B6100[];
extern s32 sub_08016E5C(u32, s32);
extern struct Frame395E8 gFrames395E8[] asm("gFrameObjects");
extern struct SetupRecord30A24 gSetupRecords30A24[] asm("gSetupBuffer_03000590");
extern struct Words395E8 gWords395E8 asm("gCounter6ED08_03001800");
extern void sub_0801B67C(u32);
extern void sub_0801B69C(u32);
extern void sub_0803D450(void);
extern void sub_0803D4AC(void);

void sub_08030A24(void);
void sub_08038700(void);
void sub_080395E8(void);

void sub_08030A24(void) {

    u8 kind;

    sub_0801B67C(gCounter6ED08_03001800.slot87);
    if (1 & gSetupRecords30A24[gCounter6ED08_03001800.slot87].flagsBD) {
        gCounter6ED08_03001800.resultA6 = 4;
        gUnknown_0300137C = 0x20;
        return;
    }
    if (gSetupRecords30A24[gCounter6ED08_03001800.slot87].partDD <= 3
        && gSetupRecords30A24[gCounter6ED08_03001800.slot87].parts[gSetupRecords30A24[gCounter6ED08_03001800.slot87].partDD - 1].count11 == 0) {
        gCounter6ED08_03001800.resultA6 = 5;
        gUnknown_0300137C = 0x20;
        return;
    }
    if (gSetupRecords30A24[gCounter6ED08_03001800.slot87].kindC9 == 0x2B
        && gSetupRecords30A24[gCounter6ED08_03001800.slot87].partCA == gSetupRecords30A24[gCounter6ED08_03001800.slot87].partDD) {
        gCounter6ED08_03001800.resultA6 = 6;
        gUnknown_0300137C = 0x20;
        return;
    }
    if (gSetupRecords30A24[gCounter6ED08_03001800.slot87].partDD > 3) {
        gCounter6ED08_03001800.partA7 = gSetupRecords30A24[gCounter6ED08_03001800.slot87].partDD - 4;
        gUnknown_0300137C = 0x30;
        return;
    }
    gCounter6ED08_03001800.flag164 = 1;
    sub_0801B69C(gCounter6ED08_03001800.slot87);
    if (sub_08016E5C(gCounter6ED08_03001800.slot87, gSetupRecords30A24[gCounter6ED08_03001800.slot87].partDD - 1) != 0) {
        gCounter6ED08_03001800.resultA6 = 7;
        gUnknown_0300137C = 0x20;
        return;
    }
    if (gSetupRecords30A24[gCounter6ED08_03001800.slot87].partDD == 1 && gCounter6ED08_03001800.flag118 != 1) {
        if (gSetupRecords30A24[gCounter6ED08_03001800.slot87].parts[0].uses10 == 0) {
            gCounter6ED08_03001800.resultA6 = 8;
            gUnknown_0300137C = 0x20;
            return;
        }
        gSetupRecords30A24[gCounter6ED08_03001800.slot87].parts[0].uses10--;
    }
    if (gSetupRecords30A24[gCounter6ED08_03001800.slot87].targetE0 != 0) {
        if (gSetupRecords30A24[gCounter6ED08_03001800.slot87].parts[gSetupRecords30A24[gCounter6ED08_03001800.slot87].partDD - 1].kind1 == 0x21) {
            if (gSetupRecords30A24[gSetupRecords30A24[gCounter6ED08_03001800.slot87].targetE0 - 1].active40 != 0) {
                gCounter6ED08_03001800.resultA6 = 9;
                gUnknown_0300137C = 0x20;
                return;
            }
        } else if (gSetupRecords30A24[gSetupRecords30A24[gCounter6ED08_03001800.slot87].targetE0 - 1].active40 == 0) {
            gCounter6ED08_03001800.resultA6 = 0xA;
            gUnknown_0300137C = 0x20;
            return;
        }
    }
    if (gSetupRecords30A24[gCounter6ED08_03001800.slot87].targetPartE1 != 0) {
        kind = gSetupRecords30A24[gCounter6ED08_03001800.slot87].parts[gSetupRecords30A24[gCounter6ED08_03001800.slot87].partDD - 1].kind1;
        if (kind == 0x20) {
            if (gSetupRecords30A24[gSetupRecords30A24[gCounter6ED08_03001800.slot87].targetE0 - 1].parts[gSetupRecords30A24[gCounter6ED08_03001800.slot87].targetPartE1 - 1].count11 != 0) {
                gCounter6ED08_03001800.resultA6 = 0xB;
                gUnknown_0300137C = kind;
                return;
            }
        } else if (gSetupRecords30A24[gSetupRecords30A24[gCounter6ED08_03001800.slot87].targetE0 - 1].parts[gSetupRecords30A24[gCounter6ED08_03001800.slot87].targetPartE1 - 1].count11 == 0) {
            gCounter6ED08_03001800.resultA6 = 0xC;
            gUnknown_0300137C = 0x20;
            return;
        }
    }
    gCounter6ED08_03001800.kindA8 = gSetupRecords30A24[gCounter6ED08_03001800.slot87].parts[gSetupRecords30A24[gCounter6ED08_03001800.slot87].partDD - 1].kind1;
    gCounter6ED08_03001800.partA7 = gSetupRecords30A24[gCounter6ED08_03001800.slot87].partDD - 1;
    gMainSubstate = 9;
    gUnknown_0300137C = 0;
}

void sub_08038700(void) {

    s32 row;

    gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown23[5]++;
    if (2 & gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown23[5]) {
        row = gCounter6ED08_03001800.base60 + (gState0TypedWork.bytes[0x12F] - 0x21);
        gFrameObjects[row * 4 + 0x5D].screenY = gCounter6ED08_03001800.pos13C[row].y + 2;
    } else {
        row = gCounter6ED08_03001800.base60 + (gState0TypedWork.bytes[0x12F] - 0x21);
        gFrameObjects[row * 4 + 0x5D].screenY = gCounter6ED08_03001800.pos13C[row].y + 4;
    }
    sub_080350E0(gCounter6ED08_03001800.base60 + (gState0TypedWork.bytes[0x12F] - 0x21));
    sub_08040BD8(gState0NextCommands_083B6100[107], gState0TypedWork.bytes[0x12F]);
    if (gFrameObjects[gState0TypedWork.bytes[0x12F]].commandStopped == 0xFF) {
        gFrameObjects[(gCounter6ED08_03001800.base60 + (gState0TypedWork.bytes[0x12F] - 0x21)) * 4 + 0x5D].screenY = gCounter6ED08_03001800.pos13C[(gCounter6ED08_03001800.base60 + (gState0TypedWork.bytes[0x12F] - 0x21))].y + 4;
        sub_080350E0(gCounter6ED08_03001800.base60 + (gState0TypedWork.bytes[0x12F] - 0x21));
        sub_08040CD0(gState0TypedWork.bytes[0x12F], 1);
    }
}

void sub_080395E8(void) {


    sub_0803D450();
    if (!(2 & gCounter6ED08_03001800.flagsF8)) {
        gFrames395E8[1].byte2B = 1;
        if (2 & gCounter6ED08_03001800.flagsF6)
            gFrames395E8[1].byte2C = *(u16 *)((u8 *)&gCounter6ED08_03001800.value102 + ((gCounter6ED08_03001800.index162 + 1) << 1));
        else
            gFrames395E8[1].byte2C = *(u16 *)((u8 *)&gCounter6ED08_03001800.value102 + ((gCounter6ED08_03001800.partA7 + 1) << 1));
        gFrames395E8[1].word30 = gWords395E8.words[0];
        gFrames395E8[1].byte2D = 0;
    } else {
        gFrames395E8[2].byte2B = 1;
        if (2 & gCounter6ED08_03001800.flagsF6)
            gFrames395E8[2].byte2C = *(u16 *)((u8 *)&gCounter6ED08_03001800.value102 + ((gCounter6ED08_03001800.index162 + 4) << 1));
        else
            gFrames395E8[2].byte2C = *(u16 *)((u8 *)&gCounter6ED08_03001800.value102 + ((gCounter6ED08_03001800.partA7 + 4) << 1));
        gFrames395E8[2].word30 = gWords395E8.words[0];
        gFrames395E8[2].byte2D = 0;
    }
    sub_0803D4AC();
}
