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
#include "coordinate_helpers.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_work.h"
#include "tile_text.h"
#include "utility_helpers.h"

struct Frame3A93C {
    u8 pad00[0x27];
    u8 byte27;
    u8 byte28;
    u8 byte29;
    u8 pad2A;
    u8 byte2B;
    u8 byte2C;
    u8 byte2D;
    u8 byte2E;
    u8 pad2F;
    u16 word30;
    u16 word32;
    u8 pad34[0xC];
};
struct Frame3B9A4 {
    u8 pad00[0x29];
    u8 byte29;
    u8 pad2A[2];
    u8 byte2C;
    u8 pad2D[3];
    u16 delay30;
    u8 pad32[0xE];
};
struct Frame3BBE0 {
    u8 pad00[0x29];
    u8 byte29;
    u8 pad2A[2];
    u8 byte2C;
    u8 byte2D;
    u8 pad2E[2];
    u16 delay30;
    u8 pad32[0xE];
};
struct SetupPart3EE10 {
    u8 pad0[0x17];
    u8 byte17;
};
struct SetupRecord3EE10 {
    u8 pad0[0x47];
    u8 byte47;
    struct SetupPart3EE10 parts[3];
    u8 pad90[0x2A];
    u8 activeBA;
    u8 padBB[0x45];
};

extern const u8 *const gState0NextCommands_083B6100[];
extern const u8 gUnknown_083AFE78[];
extern struct Frame3A93C gFrames3A93C[] asm("gFrameObjects");
extern struct Frame3B9A4 gFrames3B9A4[] asm("gFrameObjects");
extern struct Frame3BBE0 gFrames3BBE0[] asm("gFrameObjects");
extern struct SetupRecord3EE10 gSetupRecords3EE10[] asm("gSetupBuffer_03000590");
extern void sub_08036120(s32);
extern void sub_0803D450(void);
extern void sub_0803D4AC(void);

void sub_0803A93C(void);
void sub_0803AF2C(void);
void sub_0803B1EC(void);
void sub_0803B4F8(void);
void sub_0803B9A4(void);
void sub_0803BBE0(void);
void sub_0803EE10(void);

void sub_0803A93C(void) {

    u32 i;
    u32 slot;
    u32 root;
    struct Frame3A93C *f;

    sub_0803D450();
    for (i = 0; i <= 1; i++) {
        if (gFrames3A93C[i + 0xC].byte29 == 0) {
            slot = i + 0xC;
            break;
        }
    }
    sub_08040CD0(slot, 1);
    root = (u32)gFrames3A93C;
    f = (struct Frame3A93C *)(root + (slot << 6));
    f->byte2B = gCounter6ED08_03001800.value102;
    f->byte2E = gCounter6ED08_03001800.value104;
    f->word30 = gCounter6ED08_03001800.index106;
    f->word32 = gCounter6ED08_03001800.value108;
    f->byte2C = gCounter6ED08_03001800.value10A;
    f->byte2D = gCounter6ED08_03001800.value10C;
    f->byte27 = gCounter6ED08_03001800.value10E;
    f->byte28 = 0;
    f->byte29 = 0x22;
    sub_0803D4AC();
}

void sub_0803AF2C(void) {

    u32 i;
    union { struct TileCoordinates tile; s32 packed; } c;

    sub_0803D450();
    gFrameObjects[0xA].byte2B = gCounter6ED08_03001800.value102;
    gFrameObjects[0xA].screenY = gCounter6ED08_03001800.index106;
    gFrameObjects[0xA].unknown23[1] = gCounter6ED08_03001800.value10A;
    gFrameObjects[0xA].unknown2C[0] = gCounter6ED08_03001800.value10C;
    gFrameObjects[0xA].unknown23[6] = 0x30;
    if (!(2 & gCounter6ED08_03001800.flagsF8)) {
        gFrameObjects[0xA].screenX = gCounter6ED08_03001800.value104;
        gFrameObjects[0xA].unknown23[2] = gCounter6ED08_03001800.value108;
    } else {
        gFrameObjects[0xA].screenX = 0xF0 - gCounter6ED08_03001800.value104;
        gFrameObjects[0xA].unknown23[2] = (0x20 - gCounter6ED08_03001800.value108) & 0x1F;
    }
    for (i = 0; i <= 3; i++) {
        gFrameObjects[i + 0xB].flags = (gCounter6ED08_03001800.value10E << 10) | 0x4004;
        gFrameObjects[i + 0xB].tableSelector = 0;
        gFrameObjects[i + 0xB].palette = 0xE;
        gFrameObjects[i + 0xB].priority = 0x80;
        gFrameObjects[i + 0xB].unknown2C[1] = gCounter6ED08_03001800.value110;
        sub_08040B90(gState0NextCommands_083B6100[gFrameObjects[i + 0xB].unknown2C[1]], i + 0xB);
        gFrameObjects[i + 0xB].byte2B = gCounter6ED08_03001800.value102;
        gFrameObjects[i + 0xB].unknown2C[0] = gCounter6ED08_03001800.value10C;
        gFrameObjects[i + 0xB].unknown23[6] = 0x31;
        c.tile = sub_08042BC0(i << 6, 0x10, gFrameObjects[0xA].screenX, gFrameObjects[0xA].screenY);
        gFrameObjects[i + 0xB].screenX = c.packed;
        gFrameObjects[i + 0xB].screenY = c.packed >> 16;
        gFrameObjects[i + 0xB].unknown23[3] = (i << 6) - 0x20;
    }
    sub_0803D4AC();
}

void sub_0803B1EC(void) {

    u32 i;
    u32 slot;
    u32 root;
    struct FrameObject *f;

    sub_0803D450();
    for (i = 0; i <= 8; i++) {
        if (gFrameObjects[i + 0xA].flags == 0) {
            slot = i + 0xA;
            break;
        }
    }
    sub_08040CD0(slot, 1);
    root = (u32)gFrameObjects;
    f = (struct FrameObject *)(root + (slot << 6));
    f->flags = (gCounter6ED08_03001800.value10E << 10) | 0x4004;
    f->tableSelector = 0;
    f->palette = 0xE;
    f->priority = 0x80;
    f->unknown2C[1] = gCounter6ED08_03001800.value110;
    sub_08040B90(gState0NextCommands_083B6100[f->unknown2C[1]], slot);
    f->byte2B = gCounter6ED08_03001800.value102;
    f->screenY = gCounter6ED08_03001800.index106;
    f->unknown23[1] = gCounter6ED08_03001800.value10A;
    f->unknown2C[0] = gCounter6ED08_03001800.value10C;
    f->unknown23[6] = 0xE;
    if (!(2 & gCounter6ED08_03001800.flagsF8)) {
        f->screenX = gCounter6ED08_03001800.value104;
        f->unknown23[2] = gCounter6ED08_03001800.value108;
    } else {
        f->flags |= 0x1000;
        f->screenX = 0xF0 - gCounter6ED08_03001800.value104;
        f->unknown23[2] = (0x20 - gCounter6ED08_03001800.value108) & 0x1F;
    }
    sub_0803D4AC();
}

void sub_0803B4F8(void) {

    u32 i;
    union { struct TileCoordinates tile; s32 packed; } c;

    sub_0803D450();
    for (i = 0; i <= 7; i++) {
        gFrameObjects[i + 0xB].flags = 0xC604;
        gFrameObjects[i + 0xB].tableSelector = 0;
        c.tile = sub_08042BC0(i << 5, (s16)gCounter6ED08_03001800.value108,
                              gFrameObjects[gCounter6ED08_03001800.value102].screenX,
                              gFrameObjects[gCounter6ED08_03001800.value102].screenY);
        gFrameObjects[i + 0xB].screenX = c.packed;
        gFrameObjects[i + 0xB].screenY = c.packed >> 16;
        gFrameObjects[i + 0xB].scaleX = 8;
        gFrameObjects[i + 0xB].scaleY = 8;
        gFrameObjects[i + 0xB].palette = 0xE;
        gFrameObjects[i + 0xB].priority = 0x80;
        gFrameObjects[i + 0xB].unknown23[6] = 0x36;
        gFrameObjects[i + 0xB].unknown23[3] = i << 5;
        gFrameObjects[i + 0xB].unknown23[4] = gCounter6ED08_03001800.value108;
        gFrameObjects[i + 0xB].byte2B = 0;
        gFrameObjects[i + 0xB].unknown23[0] = gCounter6ED08_03001800.value104;
        gFrameObjects[i + 0xB].unknown2C[1] = gCounter6ED08_03001800.index106;
        sub_08040B90(gState0NextCommands_083B6100[gFrameObjects[i + 0xB].unknown2C[1]], i + 0xB);
    }
    sub_0803D4AC();
}

void sub_0803B9A4(void) {

    if (gFrames3B9A4[gState0TypedWork.bytes[0x12F]].delay30 != 0) {
        gFrames3B9A4[gState0TypedWork.bytes[0x12F]].delay30 -= 1;
        return;
    }
    if (gState0TypedWork.bytes[0x12F] == 1) {
        if (1 & gCounter6ED08_03001800.flagsFF) {
            sub_08036120(0);
            sub_080447EC(0, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1], gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                         (s16)gCounter6ED08_03001800.pos154[0], (s16)gCounter6ED08_03001800.pos154[1], gCounter6ED08_03001800.byte3C + 2, 4, 0, 0, 0, gCounter6ED08_03001800.byte114);
            sub_080447EC(0, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1], gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                         (s16)gCounter6ED08_03001800.pos154[0], (s16)gCounter6ED08_03001800.pos154[1], gCounter6ED08_03001800.byte3C + 2, 4, 0, 1, 0, gCounter6ED08_03001800.byte114);
        }
        gCounter6ED08_03001800.flagsFF &= 0xFE;
        gCounter6ED08_03001800.sideCommand112[0] = gFrames3B9A4[gState0TypedWork.bytes[0x12F]].byte2C;
    } else {
        if (2 & gCounter6ED08_03001800.flagsFF) {
            sub_08036120(1);
            sub_080447EC(1, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1], gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                         (s16)gCounter6ED08_03001800.pos154[2], (s16)gCounter6ED08_03001800.pos154[3], gCounter6ED08_03001800.byte3C + 2, 8, 1, 0, 1, gCounter6ED08_03001800.byte115);
            sub_080447EC(1, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1], gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                         (s16)gCounter6ED08_03001800.pos154[2], (s16)gCounter6ED08_03001800.pos154[3], gCounter6ED08_03001800.byte3C + 2, 8, 1, 1, 1, gCounter6ED08_03001800.byte115);
        }
        gCounter6ED08_03001800.flagsFF &= 0xFD;
        gCounter6ED08_03001800.sideCommand112[1] = gFrames3B9A4[gState0TypedWork.bytes[0x12F]].byte2C;
    }
    gFrames3B9A4[gState0TypedWork.bytes[0x12F]].byte29 = 1;
}

void sub_0803BBE0(void) {

    if (gFrames3BBE0[gState0TypedWork.bytes[0x12F]].delay30 != 0) {
        gFrames3BBE0[gState0TypedWork.bytes[0x12F]].delay30 -= 1;
        return;
    }
    if (gState0TypedWork.bytes[0x12F] == 1) {
        if (gCounter6ED08_03001800.active15F[0] != 0) {
        if (1 & gCounter6ED08_03001800.flagsFF) {
            sub_08036120(0);
            sub_080447EC(0, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1], gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                         (s16)gCounter6ED08_03001800.pos154[0], (s16)gCounter6ED08_03001800.pos154[1], gCounter6ED08_03001800.byte3C + 2, 4, 0, 0, 0, gCounter6ED08_03001800.byte114);
            sub_080447EC(0, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1], gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                         (s16)gCounter6ED08_03001800.pos154[0], (s16)gCounter6ED08_03001800.pos154[1], gCounter6ED08_03001800.byte3C + 2, 4, 0, 1, 0, gCounter6ED08_03001800.byte114);
        }
        gCounter6ED08_03001800.flagsFF &= 0xFE;
        gCounter6ED08_03001800.sideCommand112[0] = gFrames3BBE0[gState0TypedWork.bytes[0x12F]].byte2C;
    }
    } else {
        if (gCounter6ED08_03001800.active15F[1] != 0) {
        if (2 & gCounter6ED08_03001800.flagsFF) {
            sub_08036120(1);
            sub_080447EC(1, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1], gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                         (s16)gCounter6ED08_03001800.pos154[2], (s16)gCounter6ED08_03001800.pos154[3], gCounter6ED08_03001800.byte3C + 2, 8, 1, 0, 1, gCounter6ED08_03001800.byte115);
            sub_080447EC(1, gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1], gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
                         (s16)gCounter6ED08_03001800.pos154[2], (s16)gCounter6ED08_03001800.pos154[3], gCounter6ED08_03001800.byte3C + 2, 8, 1, 1, 1, gCounter6ED08_03001800.byte115);
        }
        gCounter6ED08_03001800.flagsFF &= 0xFD;
        gCounter6ED08_03001800.sideCommand112[1] = gFrames3BBE0[gState0TypedWork.bytes[0x12F]].byte2C;
        }
    }
    if (gFrames3BBE0[gState0TypedWork.bytes[0x12F]].byte2D == 0)
        gFrames3BBE0[gState0TypedWork.bytes[0x12F]].byte29 = 1;
}

void sub_0803EE10(void) {

    u32 base;
    u32 k;
    u32 i;

    if (gState0TypedWork.bytes[0x9C] == 1)
        base = 3;
    else
        base = 0;
    k = gUnknown_083AFE78[sub_080424B8() & 0xF];
    for (i = 0; i <= 2; i++) {
        if (gSetupRecords3EE10[base + k].activeBA != 0) {
            gCounter6ED08_03001800.result1A4 = gSetupRecords3EE10[base + k].byte47;
            gCounter6ED08_03001800.result1A5 = gSetupRecords3EE10[base + k].parts[gCounter6ED08_03001800.list19A[gCounter6ED08_03001800.index1A2]].byte17;
            return;
        }
        if (k == 2)
            k = 0;
        else
            k++;
    }
}
