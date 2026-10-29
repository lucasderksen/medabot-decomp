/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "battle_work.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "record_helpers.h"
#include "serial.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct SetupRecord33C20 {
    u8 pad0[0xBC];
    u8 flagsBC;
    u8 padBD[0xC];
    u8 kindC9;
    u8 padCA[0x36];
};
struct Frame3A760 {
    u8 pad00[0x2B];
    u8 byte2B;
    u8 byte2C;
    u8 byte2D;
    u8 pad2E[2];
    u16 word30;
    u8 pad32[0xE];
};
struct Words3A760 {
    u8 pad00[0x102];
    u16 words[8];
};

extern const u8 *const gState0NextCommands_083B6100[];
extern const u8 gUnknown_084DE4F4[];
extern const u8 gUnknown_085101F8[];
extern struct Frame3A760 gFrames3A760[] asm("gFrameObjects");
extern struct SetupRecord33C20 gSetupRecords33C20[] asm("gSetupBuffer_03000590");
extern struct Words3A760 gWords3A760 asm("gCounter6ED08_03001800");
extern void sub_08034F08(void);
extern void sub_0803D450(void);
extern void sub_0803D4AC(void);

void sub_0802B3CC(void);
void sub_0802C0DC(void);
void sub_08033C20(void);
void sub_0803A760(void);

void sub_0802B3CC(void) {

    u32 i;

    LeDecompress(gUnknown_084DE4F4, (void *)0x06016000);
    CpuFastSet(gUnknown_085101F8, (void *)0x050002E0, 8);
    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            gFrameObjects[i + 0x21].palette = 7;
            gFrameObjects[i + 0x21].flags &= 0xEFFF;
            sub_08040B90(gState0NextCommands_083B6100[0x66], i + 0x21);
        }
    }
    gCounter6ED08_03001800.counterAA++;
}

void sub_0802C0DC(void) {

    u32 i;

    gCounter6ED08_03001800.base60 = sub_08032FC4(gCounter6ED08_03001800.slot87);
    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0 && !(1 & gState0TypedWork.bytes[0x84]))
            gFrameObjects[i + 0x21].screenY--;
    }
    gCounter6ED08_03001800.base60 = sub_08032FB8(gCounter6ED08_03001800.slot87);
    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.valuesD6[i] != 0 && !(1 & gState0TypedWork.bytes[0x84]))
            gFrameObjects[i + 0x24].screenY++;
    }
    if (gState0TypedWork.bytes[0x84] == 0x20) {
        gState0TypedWork.widths.word86 = 0x3C;
        gCounter6ED08_03001800.counterAA++;
    } else {
        gState0TypedWork.bytes[0x84]++;
    }
}

void sub_08033C20(void) {

    u8 kind;
    u8 flags;

    if (gSetupRecords33C20[gCounter6ED08_03001800.value88].kindC9 == 0x2E)
        gSetupRecords33C20[gCounter6ED08_03001800.value88].flagsBC |= 4;
    if (gSetupRecords33C20[gCounter6ED08_03001800.value88].kindC9 == 0x2F)
        gSetupRecords33C20[gCounter6ED08_03001800.value88].flagsBC |= 8;
    kind = gSetupRecords33C20[gCounter6ED08_03001800.value88].kindC9;
    if (kind == 0xF)
        goto both;
    if (kind == 0x10) {
    both:
        gSetupRecords33C20[gCounter6ED08_03001800.value88].flagsBC |= 0xC;
    }
    if (1 & gSetupRecords33C20[gCounter6ED08_03001800.value88].flagsBC)
        gSetupRecords33C20[gCounter6ED08_03001800.value88].flagsBC |= 4;
    if (2 & gSetupRecords33C20[gCounter6ED08_03001800.value88].flagsBC)
        gSetupRecords33C20[gCounter6ED08_03001800.value88].flagsBC |= 8;
    sub_08034F08();
}

void sub_0803A760(void) {


    sub_0803D450();
    if (!(2 & gCounter6ED08_03001800.flagsF8)) {
        gFrames3A760[1].byte2B = 1;
        if (2 & gCounter6ED08_03001800.flagsF6)
            gFrames3A760[1].byte2C = *(u16 *)((u8 *)&gCounter6ED08_03001800.value102 + ((gCounter6ED08_03001800.index162 + 1) << 1));
        else
            gFrames3A760[1].byte2C = *(u16 *)((u8 *)&gCounter6ED08_03001800.value102 + ((gCounter6ED08_03001800.partA7 + 1) << 1));
        gFrames3A760[1].word30 = gWords3A760.words[0];
        gFrames3A760[1].byte2D = 1;
    } else {
        gFrames3A760[2].byte2B = 1;
        if (2 & gCounter6ED08_03001800.flagsF6)
            gFrames3A760[2].byte2C = *(u16 *)((u8 *)&gCounter6ED08_03001800.value102 + ((gCounter6ED08_03001800.index162 + 4) << 1));
        else
            gFrames3A760[2].byte2C = *(u16 *)((u8 *)&gCounter6ED08_03001800.value102 + ((gCounter6ED08_03001800.partA7 + 4) << 1));
        gFrames3A760[2].word30 = gWords3A760.words[0];
        gFrames3A760[2].byte2D = 1;
    }
    sub_0803D4AC();
}
