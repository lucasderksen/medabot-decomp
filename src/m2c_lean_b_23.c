/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "battle_work.h"
#include "continued_scene_records.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "record_helpers.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "utility_helpers.h"

struct SetupRec6E64 {
    u8 pad0[0xC9];
    u8 kindC9;
    u8 byteCA;
    u8 byteCB;
    u8 byteCC;
    u8 padCD[0x33];
};
struct SetupPart9158 {
    u8 byte0;
    u8 byte1;
    u8 byte2;
    u8 byte3;
    u8 byte4;
    u8 pad5[0xC];
    u8 byte11;
    u8 pad12[6];
};
struct SetupRec9158 {
    u8 pad0[0x40];
    u8 byte40;
    u8 pad41[7];
    struct SetupPart9158 parts[4];
    u8 padA8[0x14];
    u8 flagsBC;
    u8 flagsBD;
    u8 padBE[0x42];
};

extern const u8 *gState0NextCommands_083B6100[];
extern s16 gUnknown_083AF6A0[];
extern s32 sub_08035DD4(s32 arg0);
extern s8 sub_08036E54(s32);
extern struct SetupRec6E64 gSetupRecs6E64[] asm("gSetupBuffer_03000590");
extern struct SetupRec9158 gSetupRecs9158[] asm("gSetupBuffer_03000590");
extern void sub_08036120(s32 arg0);

void sub_08035DE8(void);
void sub_08035F20(void);
void sub_08036E64(s32 slot, u32 kind, u32 a, u32 b);
void sub_080378F0(s32 index);
s32 sub_08039158(s32 slot);

void sub_08035DE8(void) {

    if (1 & gCounter6ED08_03001800.flagsFF)
        gState0TypedWork.bytes[0x96] = 1;
    else
        gState0TypedWork.bytes[0x96] = 0;
    if (sub_08035DD4((s16)gCounter6ED08_03001800.pos154[0]) != 0) {
        sub_08036120(0);
        sub_080447EC(0, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1],
                     gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                     (s16)gCounter6ED08_03001800.pos154[0], (s16)gCounter6ED08_03001800.pos154[1],
                     gCounter6ED08_03001800.byte3C + 2, 4, 0, 1, 0, gCounter6ED08_03001800.byte114);
    }
    if (2 & gCounter6ED08_03001800.flagsFF)
        gState0TypedWork.bytes[0x96] = 1;
    else
        gState0TypedWork.bytes[0x96] = 0;
    if (sub_08035DD4((s16)gCounter6ED08_03001800.pos154[2]) != 0) {
        sub_08036120(1);
        sub_080447EC(1, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1],
                     gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                     (s16)gCounter6ED08_03001800.pos154[2], (s16)gCounter6ED08_03001800.pos154[3],
                     gCounter6ED08_03001800.byte3C + 2, 8, 1, 1, 1, gCounter6ED08_03001800.byte115);
    }
    gState0TypedWork.bytes[0x96] = 0;
}

void sub_08035F20(void) {

    if (1 & gCounter6ED08_03001800.flagsFF)
        gState0TypedWork.bytes[0x96] = 1;
    else
        gState0TypedWork.bytes[0x96] = 0;
    if (sub_08035DD4((s16)gCounter6ED08_03001800.pos154[0]) != 0) {
        sub_08036120(0);
        sub_080447EC(0, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1],
                     gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                     (s16)gCounter6ED08_03001800.pos154[0], (s16)gCounter6ED08_03001800.pos154[1],
                     gCounter6ED08_03001800.byte3C + 2, 4, 0, 2, 0, gCounter6ED08_03001800.byte114);
        sub_080447EC(0, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1],
                     gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                     (s16)gCounter6ED08_03001800.pos154[0], (s16)gCounter6ED08_03001800.pos154[1],
                     gCounter6ED08_03001800.byte3C + 2, 4, 0, 1, 0, gCounter6ED08_03001800.byte114);
    }
    if (2 & gCounter6ED08_03001800.flagsFF)
        gState0TypedWork.bytes[0x96] = 1;
    else
        gState0TypedWork.bytes[0x96] = 0;
    if (sub_08035DD4((s16)gCounter6ED08_03001800.pos154[2]) != 0) {
        sub_08036120(1);
        sub_080447EC(1, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1],
                     gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                     (s16)gCounter6ED08_03001800.pos154[2], (s16)gCounter6ED08_03001800.pos154[3],
                     gCounter6ED08_03001800.byte3C + 2, 8, 1, 2, 1, gCounter6ED08_03001800.byte115);
        sub_080447EC(1, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1],
                     gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                     (s16)gCounter6ED08_03001800.pos154[2], (s16)gCounter6ED08_03001800.pos154[3],
                     gCounter6ED08_03001800.byte3C + 2, 8, 1, 1, 1, gCounter6ED08_03001800.byte115);
    }
    gState0TypedWork.bytes[0x96] = 0;
}

void sub_08036E64(s32 slot, u32 kind, u32 a, u32 b) {

    if (kind == 0xD || kind == 0xE) {
        gSetupRecs6E64[slot].kindC9 = kind;
        gSetupRecs6E64[slot].byteCA = gCounter6ED08_03001800.group8B + 1;
        gSetupRecs6E64[slot].byteCB = sub_08036E54(a);
        gSetupRecs6E64[slot].byteCC = sub_08036E54(b * 2);
    } else if (kind == 0xF || kind == 0x10) {
        gSetupRecs6E64[slot].kindC9 = kind;
        gSetupRecs6E64[slot].byteCA = gCounter6ED08_03001800.group8B + 1;
        gSetupRecs6E64[slot].byteCB = sub_08036E54(b / 8);
        gSetupRecs6E64[slot].byteCC = 0;
    } else if (kind == 0x11 || kind == 0x12) {
        gSetupRecs6E64[slot].kindC9 = kind;
        gSetupRecs6E64[slot].byteCA = gCounter6ED08_03001800.group8B + 1;
        gSetupRecs6E64[slot].byteCB = sub_08036E54(a);
        gSetupRecs6E64[slot].byteCC = sub_08036E54(b / 4);
    } else if (kind == 0x13 || kind == 0x14) {
        gSetupRecs6E64[slot].kindC9 = kind;
        gSetupRecs6E64[slot].byteCA = gCounter6ED08_03001800.group8B + 1;
        gSetupRecs6E64[slot].byteCB = sub_08036E54(a);
        gSetupRecs6E64[slot].byteCC = sub_08036E54(b / 2);
    } else {
        gSetupRecs6E64[slot].kindC9 = kind;
        gSetupRecs6E64[slot].byteCA = gCounter6ED08_03001800.group8B;
        gSetupRecs6E64[slot].byteCB = sub_08036E54(a);
        gSetupRecs6E64[slot].byteCC = sub_08036E54(b);
    }
}

void sub_080378F0(s32 index) {

    u32 mask;
    u32 obj;

    switch (gCounter6ED08_03001800.frame51) {
    case 0:
        mask = 0xF;
        break;
    case 1:
        mask = 7;
        break;
    case 2:
        mask = 7;
        break;
    case 3:
        mask = 7;
        break;
    case 4:
        mask = 7;
        break;
    case 5:
        mask = 7;
        break;
    }
    if (gFrameObjects[index].unknown2C[1] & mask)
        return;
    obj = sub_08040D78(index + 1, 0x14);
    sub_08040CD0(obj, 1);
    gFrameObjects[obj].flags = 0xC604;
    gFrameObjects[obj].tableSelector = 0;
    gFrameObjects[obj].screenX = (gFrameObjects[index].screenX + gUnknown_083AF6A0[(sub_080424B8() & 3) * 2]) & 0x1FF;
    gFrameObjects[obj].screenY = (gFrameObjects[index].screenY + gUnknown_083AF6A0[(sub_080424B8() & 3) * 2 + 1]) & 0xFF;
    gFrameObjects[obj].scaleX = 0x40;
    gFrameObjects[obj].scaleY = 0x40;
    gFrameObjects[obj].palette = 6;
    gFrameObjects[obj].priority = 0xE0;
    switch (gCounter6ED08_03001800.frame51) {
    case 0:
        gFrameObjects[obj].frameAndGroup = (sub_080424B8() & 3) + 0x6B01;
        gFrameObjects[obj].unknown23[6] = 0x10;
        break;
    case 1:
        gFrameObjects[obj].frameAndGroup = 0x6C01;
        gFrameObjects[obj].unknown23[6] = 0x14;
        break;
    case 2:
        gFrameObjects[obj].frameAndGroup = 0x6D01;
        gFrameObjects[obj].unknown23[6] = 0x18;
        break;
    case 3:
        sub_08040B90(gState0NextCommands_083B6100[0x5E], obj);
        gFrameObjects[obj].unknown23[6] = 0x1C;
        break;
    case 4:
        gFrameObjects[obj].frameAndGroup = 0x7001;
        gFrameObjects[obj].unknown23[6] = 0x20;
        break;
    case 5:
        break;
    }
}

s32 sub_08039158(s32 slot) {

    u32 max = 0;
    s32 i;
    s32 best;

    for (i = 3; i != 0; i--) {
        if (gSetupRecs9158[slot].parts[i].byte11 != 0 && gSetupRecs9158[slot].parts[i].byte11 > max) {
            best = i;
            max = gSetupRecs9158[slot].parts[i].byte11;
        }
    }
    return best + 1;
}
