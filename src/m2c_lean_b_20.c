/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "battle_work.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct SetupRecA824 {
    u8 pad0[0x40];
    u8 byte40;
    u8 pad41[0x18];
    u8 byte59;
    u8 pad5A[0x61];
    u8 byteBB;
    u8 padBC;
    u8 flagsBD;
    u8 padBE[0x19];
    u8 byteD7;
    u8 padD8[2];
    u8 byteDA;
    u8 padDB[0x25];
};
struct FrameB258 {
    u16 flags;
    s16 screenX;
    s16 screenY;
    u16 frameAndGroup;
    u8 pad8[2];
    u8 palette;
    u8 priority;
    u8 padC[0x10];
    u8 tableSelector;
    u8 pad1D[6];
    u8 byte23;
    u8 byte24;
    u8 pad25[0xB];
    u16 word30;
    s16 word32;
    u8 pad34[0xC];
};
struct SetupRecC588 {
    u8 pad0[0xB8];
    u8 bytesB8[0x48];
};

extern const u8 *gState0NextCommands_083B6100[];
extern const u8 gUnknown_084D745C[];
extern const u8 gUnknown_084E1174[];
extern const u8 gUnknown_084E11B8[];
extern const u8 gUnknown_0850FD58[];
extern const u8 gUnknown_08510398[];
extern const u8 gUnknown_085103D8[];
extern s32 sub_08036D64(s32, s32);
extern struct FrameB258 gFramesB258[] asm("gFrameObjects");
extern struct SetupRecA824 gSetupRecA824[] asm("gSetupBuffer_03000590");
extern struct SetupRecC588 gSetupRecC588[] asm("gSetupBuffer_03000590");
extern u8 gUnknown_03001887;
extern u8 gUnknown_030018F8;
extern void sub_0803572C(u8 *, s32);
extern void sub_08035740(u8 *, s32, u32);
extern void sub_08037330(s32, u8, s32);
extern void sub_080373D4(s32);
extern void sub_0803836C(void);
extern void sub_080385D0(s32);

void sub_0802A824(void);
void sub_0802B258(void);
void sub_0802B4D8(void);
void sub_0802B8BC(void);
void sub_0802B980(void);
void sub_0802BA2C(void);
void sub_0802BF9C(void);
void sub_0802C2D4(void);
void sub_0802C4F8(void);
void sub_0802C588(void);

void sub_0802A824(void) {

    u32 i;

    sub_0803836C();
    gCounter6ED08_03001800.base60 = sub_08032FB8(gCounter6ED08_03001800.slot87);
    for (i = 0; i <= 2; i++) {
        if (gSetupRecA824[gCounter6ED08_03001800.base60 + i].byte40 != 0
            && gSetupRecA824[gCounter6ED08_03001800.base60 + i].byte59 != 0) {
            gSetupRecA824[gCounter6ED08_03001800.base60 + i].flagsBD |= 4;
            gCounter6ED08_03001800.activeD2[i] = 1;
            sub_080385D0(gCounter6ED08_03001800.base60 + i);
            gSetupRecA824[gCounter6ED08_03001800.base60 + i].byteD7 = 0;
            gSetupRecA824[gCounter6ED08_03001800.base60 + i].byteBB = 0x14;
            gSetupRecA824[gCounter6ED08_03001800.base60 + i].byteDA = 0;
            gFrameObjects[i + 0x22].flags = 0xC404;
            gFrameObjects[i + 0x22].tableSelector = 0;
            gFrameObjects[i + 0x22].screenX = gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenX;
            gFrameObjects[i + 0x22].screenY = gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenY - 0x10;
            gFrameObjects[i + 0x22].palette = 7;
            gFrameObjects[i + 0x22].priority = 0xE0;
            sub_08040B90(gState0NextCommands_083B6100[0x63], i + 0x22);
            if (1 & gCounter6ED08_03001800.flagsF8)
                gFrameObjects[i + 0x22].flags |= 0x1000;
        }
    }
    sub_0801A0D0();
    gState0TypedWork.widths.word86 = 0;
    gFrameObjects[0x21].flags &= 0xFDFF;
    gFrameObjects[0x2B].unknown23[6] = 1;
    gFrameObjects[0x2B].screenX = gFrameObjects[0x21].screenX;
    gFrameObjects[0x2B].screenY = gFrameObjects[0x21].screenY;
    sub_0801A5D8();
    gCounter6ED08_03001800.counterAA++;
}

void sub_0802B258(void) {

    u32 i;

    LeDecompress(gUnknown_084E1174, (void *)0x06014800);
    CpuFastSet(gUnknown_08510398, (void *)0x050002C0, 0x10);
    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            gFramesB258[i + 0x21].flags = 0xC404;
            gFramesB258[i + 0x21].tableSelector = 0;
            gFramesB258[i + 0x21].screenX = gFramesB258[gCounter6ED08_03001800.slot87 * 4 + 0x5D].screenX;
            gFramesB258[i + 0x21].screenY = gFramesB258[gCounter6ED08_03001800.slot87 * 4 + 0x5D].screenY - 4;
            gFramesB258[i + 0x21].word30 = gFramesB258[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenX;
            gFramesB258[i + 0x21].word32 = gFramesB258[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenY - 4;
            gFramesB258[i + 0x21].byte24 = 6;
            gFramesB258[i + 0x21].byte23 = 0;
            gFramesB258[i + 0x21].priority = 0xF0;
            if (1 & gCounter6ED08_03001800.flagsF8)
                gFramesB258[i + 0x21].flags |= 0x1000;
            if (gCounter6ED08_03001800.activeD2[i] == 1) {
                gFramesB258[i + 0x21].palette = 6;
                gFramesB258[i + 0x21].frameAndGroup = 0x7B00;
            } else {
                gFramesB258[i + 0x21].palette = 7;
                gFramesB258[i + 0x21].frameAndGroup = 0x7B01;
            }
        }
    }
    sub_08074DE0(0x24);
    gCounter6ED08_03001800.counterAA++;
}

void sub_0802B4D8(void) {

    u32 i;

    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            gCounter6ED08_03001800.valuesD6[i] = sub_080424B8() & 7;
            switch (gCounter6ED08_03001800.valuesD6[i]) {
            case 0:
                if (sub_08036D64(gCounter6ED08_03001800.base60 + i, 0xD) != 0)
                    gCounter6ED08_03001800.valuesD6[i] = 5;
                break;
            case 1:
                if (sub_08036D64(gCounter6ED08_03001800.base60 + i, 0x11) != 0)
                    gCounter6ED08_03001800.valuesD6[i] = 5;
                break;
            case 2:
                if (sub_08036D64(gCounter6ED08_03001800.base60 + i, 0x13) != 0)
                    gCounter6ED08_03001800.valuesD6[i] = 5;
                break;
            case 3:
                if (sub_08036D64(gCounter6ED08_03001800.base60 + i, 0x10) != 0)
                    gCounter6ED08_03001800.valuesD6[i] = 5;
                break;
            }
            gFrameObjects[i + 0x21].frameAndGroup = gCounter6ED08_03001800.valuesD6[i] + 0x6F00;
            gFrameObjects[i + 0x21].unknown23[0] = 0;
        }
    }
    sub_08074DE0(0x5B);
    gCounter6ED08_03001800.counterAA++;
}

void sub_0802B8BC(void) {

    u32 i;

    LeDecompress(gUnknown_084E11B8, (void *)0x06014800);
    CpuFastSet(gUnknown_085103D8, (void *)0x050002C0, 0x10);
    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            gFrameObjects[i + 0x21].flags = 0xC404;
            gFrameObjects[i + 0x21].tableSelector = 0;
            gFrameObjects[i + 0x21].screenX = gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenX;
            gFrameObjects[i + 0x21].screenY = 0xF0;
            gFrameObjects[i + 0x21].palette = 6;
            gFrameObjects[i + 0x21].priority = 0xF0;
            sub_08040B90(gState0NextCommands_083B6100[0x67], i + 0x21);
        }
    }
    sub_08074DE0(0x2C);
    gCounter6ED08_03001800.counterAA++;
}

void sub_0802B980(void) {

    s32 done = 0;
    s32 active = 0;
    u32 i;

    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            active++;
            sub_08040BD8(gState0NextCommands_083B6100[0x67], i + 0x21);
            if (gFrameObjects[i + 0x21].screenY == gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenY - 4)
                done++;
            else
                gFrameObjects[i + 0x21].screenY = (gFrameObjects[i + 0x21].screenY + 1) & 0xFF;
        }
    }
    if (done == active)
        gCounter6ED08_03001800.counterAA++;
}

void sub_0802BA2C(void) {

    u32 i;

    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            gFrameObjects[i + 0x21].flags = 0xCC04;
            gFrameObjects[i + 0x21].priority = 0;
            sub_08040B90(gState0NextCommands_083B6100[0x68], i + 0x21);
        }
    }
    sub_08074DE0(0x30);
    gCounter6ED08_03001800.counterAA++;
}

void sub_0802BF9C(void) {

    u32 i;

    gCounter6ED08_03001800.base60 = sub_08032FC4(gCounter6ED08_03001800.slot87);
    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            gFrameObjects[i + 0x21].flags = 0xC624;
            gFrameObjects[i + 0x21].tableSelector = 0;
            gFrameObjects[i + 0x21].screenX = gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenX;
            gFrameObjects[i + 0x21].screenY = gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenY;
            gFrameObjects[i + 0x21].palette = 7;
            gFrameObjects[i + 0x21].priority = 0xF0;
            gFrameObjects[i + 0x21].scaleX = 0x40;
            gFrameObjects[i + 0x21].scaleY = 0x40;
            gFrameObjects[i + 0x21].frameAndGroup = 0x4801;
        }
    }
    gCounter6ED08_03001800.base60 = sub_08032FB8(gCounter6ED08_03001800.slot87);
    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.valuesD6[i] != 0) {
            gFrameObjects[i + 0x24].flags = 0xC624;
            gFrameObjects[i + 0x24].tableSelector = 0;
            gFrameObjects[i + 0x24].screenX = gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenX;
            gFrameObjects[i + 0x24].screenY = gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenY - 0x10;
            gFrameObjects[i + 0x24].palette = 7;
            gFrameObjects[i + 0x24].priority = 0xF0;
            gFrameObjects[i + 0x24].scaleX = 0x40;
            gFrameObjects[i + 0x24].scaleY = 0x40;
            gFrameObjects[i + 0x24].frameAndGroup = 0x4802;
        }
    }
    gState0TypedWork.bytes[0x84] = 0;
    sub_08074DE0(0x2E);
    gCounter6ED08_03001800.counterAA++;
}

void sub_0802C2D4(void) {

    u32 i;

    LeDecompress(gUnknown_084D745C, (void *)0x06014800);
    CpuFastSet(gUnknown_0850FD58, (void *)0x050002E0, 8);
    gCounter6ED08_03001800.base60 = sub_08032FC4(gCounter6ED08_03001800.slot87);
    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            gFrameObjects[i + 0x21].flags = 0xC404;
            gFrameObjects[i + 0x21].tableSelector = 0;
            gFrameObjects[i + 0x21].screenX = gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenX;
            gFrameObjects[i + 0x21].screenY = gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenY - 4;
            gFrameObjects[i + 0x21].palette = 7;
            gFrameObjects[i + 0x21].priority = 0xF0;
            sub_08040B90(gState0NextCommands_083B6100[0x40], i + 0x21);
        }
    }
    gCounter6ED08_03001800.base60 = sub_08032FB8(gCounter6ED08_03001800.slot87);
    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.valuesD6[i] != 0) {
            gFrameObjects[i + 0x24].flags = 0xC404;
            gFrameObjects[i + 0x24].tableSelector = 0;
            gFrameObjects[i + 0x24].screenX = gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenX;
            gFrameObjects[i + 0x24].screenY = gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenY - 4;
            gFrameObjects[i + 0x24].palette = 7;
            gFrameObjects[i + 0x24].priority = 0xF0;
            sub_08040B90(gState0NextCommands_083B6100[0x41], i + 0x24);
        }
    }
    sub_08074DE0(0x4D);
    gCounter6ED08_03001800.counterAA++;
}

void sub_0802C4F8(void) {

    u32 i;

    gState0TypedWork.bytes[0x84]++;
    gCounter6ED08_03001800.base60 = sub_08032FC4(gCounter6ED08_03001800.slot87);
    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0)
            sub_08037330(gCounter6ED08_03001800.base60 + i, gState0TypedWork.bytes[0x84], 2);
    }
    if (gState0TypedWork.bytes[0x84] == 0x3C) {
        for (i = 0; i <= 2; i++) {
            if (gCounter6ED08_03001800.activeD2[i] != 0)
                sub_080373D4(gCounter6ED08_03001800.base60 + i);
        }
        gCounter6ED08_03001800.counterAA++;
    }
}

void sub_0802C588(void) {

    u32 i;

    gCounter6ED08_03001800.base60 = sub_08032FC4(gCounter6ED08_03001800.slot87);
    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0)
            sub_08035740(&gSetupRecC588[gCounter6ED08_03001800.base60 + i].bytesB8[1], gCounter6ED08_03001800.valueEC, 0x78);
    }
    gCounter6ED08_03001800.base60 = sub_08032FB8(gCounter6ED08_03001800.slot87);
    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.valuesD6[i] != 0)
            sub_0803572C(&gSetupRecC588[gCounter6ED08_03001800.base60 + i].bytesB8[1], gCounter6ED08_03001800.valueEC);
    }
    gCounter6ED08_03001800.counterAA++;
}
