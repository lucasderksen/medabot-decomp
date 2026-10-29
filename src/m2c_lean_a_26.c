/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_float_progress.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "graphics.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "serial.h"
#include "sprite_layouts.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct Setup150FC
{
    u8 flags00;
    u8 byte01;
    u8 unknown02[2];
    u8 byte04;
    u8 byte05;
    u8 byte06;
    u8 byte07;
    u8 unknown08;
    u8 byte09;
    u8 name0A[0xE];
    u8 digits18[8];
    u8 stats20[8];
    u8 unknown28[0xD8];
};
struct Setup187D4 { u8 unknown00[0x40]; u8 active40; u8 unknown41[0xBF]; };
struct Setup19348
{
    u8 unknown00[0xBB];
    u8 byteBB;
    u8 unknownBC;
    u8 flagsBD;
    u8 unknownBE[0x19];
    u8 valueD7;
    u8 unknownD8[2];
    u8 stepDA;
    u8 unknownDB[0x25];
};
struct Setup19440
{
    u8 unknown00[0xBB];
    u8 byteBB;
    u8 unknownBC;
    u8 flagsBD;
    u8 unknownBE[0x19];
    u8 valueD7;
    u8 unknownD8[2];
    u8 stepDA;
    u8 unknownDB[0x25];
};
struct Part1B894 { u8 unknown00[0xE]; u8 target0E; u8 byte0F; u8 unknown10[8]; };
struct Setup1B894 { u8 unknown00[0x48]; struct Part1B894 parts[3]; u8 unknown90[0x70]; };
struct Work1B894 { u8 pad[0x80]; u8 setup80; u8 pad81; u8 choice82; u8 pad83[0xD9]; u8 used15C[3]; };

extern const void *const gPostDispatchPointers_083BA658[];
extern const u8 *gState0NextCommands_083B6100[];
extern const u8 gUnknown_083AD380[];
extern const u8 gUnknown_083AD524[];
extern struct Setup150FC gSetup150FC[] asm("gSetupBuffer_03000590");
extern struct Setup187D4 gSetup187D4[] asm("gSetupBuffer_03000590");
extern struct Setup19348 gSetup19348[] asm("gSetupBuffer_03000590");
extern struct Setup19440 gSetup19440[] asm("gSetupBuffer_03000590");
extern struct Setup1B894 gSetup1B894[] asm("gSetupBuffer_03000590");
extern struct Work1B894 gWork1B894 asm("gCounter6ED08_03001800");
extern u8 gWork150FC[] asm("gCounter6ED08_03001800");
extern void sub_08017994(u32, u32, u32);
extern void sub_08017B24(void);
extern void sub_08017BD0(void);
extern void sub_08017D50(void);
extern void sub_08017D90(void);
extern void sub_08017E00(void);
extern void sub_08017EA8(void);
extern void sub_08017F9C(void);

void sub_080150FC(u32 selected);
u32 sub_080187D4(void);
void sub_08019348(u32 selected);
u32 sub_08019440(u32 selected);
void sub_0801B894(void);

void sub_080150FC(u32 selected) {

    u8 index;
    u8 *record;
    u32 i;
    u32 value;
    u32 root;
    u8 scale;

    index = selected;
    root = (u32)gWork150FC;
    record = (u8 *)(root + index * 12);
    sub_08041D04(&gInventoryMetadata_083B62D8[record[8] * 16], &gState0TypedWork.bytes[0xEE], 16);
    gSetup150FC[index + 3].flags00 = 0x80;
    gSetup150FC[index + 3].byte01 = gState0TypedWork.bytes[0xEE];
    gSetup150FC[index + 3].byte04 = gState0TypedWork.bytes[0xEF];
    gSetup150FC[index + 3].byte05 = record[9];
    gSetup150FC[index + 3].byte06 = gState0TypedWork.bytes[0xF0];
    gSetup150FC[index + 3].byte07 = gState0TypedWork.bytes[0xF5];
    gSetup150FC[index + 3].byte09 = record[0xE];
    sub_08041D04(gPostDispatchPointers_083BA658[record[4]], gSetup150FC[index + 3].name0A, 14);
    for (i = 0; i < 4; i++) {
        gSetup150FC[index + 3].digits18[i * 2] = gWork150FC[index * 12 + 0xA + i] >> 4;
        gSetup150FC[index + 3].digits18[i * 2 + 1] = gWork150FC[index * 12 + 0xA + i] & 0xF;
    }
    for (i = 0; i < 8; i++) {
        value = gUnknown_083AD380[gSetup150FC[index + 3].byte04 * 8 + i];
        scale = gSetup150FC[index + 3].byte05 >> 1;
        if (scale != 0)
            value *= scale;
        if (value == 0)
            value = 1;
        else if (value > 100)
            value = 100;
        gSetup150FC[index + 3].stats20[i] = value;
    }
}

u32 sub_080187D4(void) {

    u32 i;
    u32 index;
    u32 root;
    u32 x;

    sub_08040D0C(4, 1);
    sub_08040D0C(5, 1);
    sub_08040D0C(6, 1);
    sub_08040D0C(7, 1);
    if (gState0TypedWork.bytes[0x3C] == 0) {
        for (i = 0, root = (u32)gSetup187D4; i < 3; i++) {
            index = gState0TypedWork.bytes[0x3C] * 3 + i;
            if (((struct Setup187D4 *)((index << 8) + root))->active40 != 0)
                {
                u32 base, offset;
                base = (u32)gUnknown_083AD524;
                offset = index * 2;
                x = *(const u8 *)(offset + base) - (13 - gState0TypedWork.bytes[0x40]) * 8;
                offset++;
                sub_08017994(index, x, *(const u8 *)(offset + base));
            }
        }
    } else {
        for (i = 0, root = (u32)gSetup187D4; i < 3; i++) {
            index = gState0TypedWork.bytes[0x3C] * 3 + i;
            if (((struct Setup187D4 *)((index << 8) + root))->active40 != 0)
                {
                u32 base, offset;
                base = (u32)gUnknown_083AD524;
                offset = index * 2;
                x = *(const u8 *)(offset + base) + (13 - gState0TypedWork.bytes[0x40]) * 8;
                offset++;
                sub_08017994(index, x, *(const u8 *)(offset + base));
            }
        }
    }
    if (++gState0TypedWork.bytes[0x40] == 14) {
        sub_08017B24();
        sub_08017BD0();
        sub_08017D50();
        sub_08017D90();
        sub_08017E00();
        sub_08017EA8();
        sub_08017F9C();
        return 1;
    }
    return 0;
}

void sub_08019348(u32 selected) {

    gSetup19348[selected].valueD7 += 0x20 - gSetup19348[selected].byteBB;
    gSetup19348[selected].stepDA = gSetup19348[selected].valueD7 / 16;
    gSetup19348[selected].valueD7 %= 16;
    if (selected <= 2) {
        if (!(gSetup19348[selected].flagsBD & 4)) {
            if (gFrameObjects[selected * 4 + 0x5D].screenX + gSetup19348[selected].stepDA > 0x68)
                gFrameObjects[selected * 4 + 0x5D].screenX = 0x68;
            else
                gFrameObjects[selected * 4 + 0x5D].screenX += gSetup19348[selected].stepDA;
        } else {
            if (gFrameObjects[selected * 4 + 0x5D].screenX - gSetup19348[selected].stepDA < 0x28)
                gFrameObjects[selected * 4 + 0x5D].screenX = 0x28;
            else
                gFrameObjects[selected * 4 + 0x5D].screenX -= gSetup19348[selected].stepDA;
        }
    } else {
        if (!(gSetup19348[selected].flagsBD & 4)) {
            if (gFrameObjects[selected * 4 + 0x5D].screenX - gSetup19348[selected].stepDA < 0x88)
                gFrameObjects[selected * 4 + 0x5D].screenX = 0x88;
            else
                gFrameObjects[selected * 4 + 0x5D].screenX -= gSetup19348[selected].stepDA;
        } else {
            if (gFrameObjects[selected * 4 + 0x5D].screenX + gSetup19348[selected].stepDA > 0xC8)
                gFrameObjects[selected * 4 + 0x5D].screenX = 0xC8;
            else
                gFrameObjects[selected * 4 + 0x5D].screenX += gSetup19348[selected].stepDA;
        }
    }
}

u32 sub_08019440(u32 selected) {

    u32 clamped;

    clamped = 0;
    gSetup19440[selected].valueD7 += 0x20 - gSetup19440[selected].byteBB;
    gSetup19440[selected].stepDA = gSetup19440[selected].valueD7 / 16;
    gSetup19440[selected].valueD7 %= 16;
    if (selected <= 2) {
        if (gSetup19440[selected].flagsBD & 4) {
            if (gFrameObjects[selected * 4 + 0x5D].screenX + gSetup19440[selected].stepDA > 0x68) {
                gFrameObjects[selected * 4 + 0x5D].screenX = 0x68;
                clamped = 1;
            } else
                gFrameObjects[selected * 4 + 0x5D].screenX += gSetup19440[selected].stepDA;
        } else {
            if (gFrameObjects[selected * 4 + 0x5D].screenX - gSetup19440[selected].stepDA < 0x28) {
                gFrameObjects[selected * 4 + 0x5D].screenX = 0x28;
                clamped = 1;
            } else
                gFrameObjects[selected * 4 + 0x5D].screenX -= gSetup19440[selected].stepDA;
        }
    } else {
        if (gSetup19440[selected].flagsBD & 4) {
            if (gFrameObjects[selected * 4 + 0x5D].screenX - gSetup19440[selected].stepDA < 0x88) {
                gFrameObjects[selected * 4 + 0x5D].screenX = 0x88;
                clamped = 1;
            } else
                gFrameObjects[selected * 4 + 0x5D].screenX -= gSetup19440[selected].stepDA;
        } else {
            if (gFrameObjects[selected * 4 + 0x5D].screenX + gSetup19440[selected].stepDA > 0xC8) {
                gFrameObjects[selected * 4 + 0x5D].screenX = 0xC8;
                clamped = 1;
            } else
                gFrameObjects[selected * 4 + 0x5D].screenX += gSetup19440[selected].stepDA;
        }
    }
    return clamped;
}

void sub_0801B894(void) {

    sub_08040CD0(9, 1);
    if (gWork1B894.choice82 == 0)
        return;
    if (gWork1B894.used15C[gWork1B894.choice82 - 1] != 0)
        return;
    if (gSetup1B894[gWork1B894.setup80].parts[gWork1B894.choice82 - 1].target0E == 0)
        return;
    gFrameObjects[9].flags = 0xC404;
    gFrameObjects[9].tableSelector = 0;
    gFrameObjects[9].screenY = gFrameObjects[gSetup1B894[gWork1B894.setup80].parts[gWork1B894.choice82 - 1].target0E * 4 + 0x59].screenY - 4;
    gFrameObjects[9].screenX = gFrameObjects[gSetup1B894[gWork1B894.setup80].parts[gWork1B894.choice82 - 1].target0E * 4 + 0x59].screenX;
    gFrameObjects[9].palette = 6;
    gFrameObjects[9].priority = 0xF0;
    gFrameObjects[9].unknown23[1] = gSetup1B894[gWork1B894.setup80].parts[gWork1B894.choice82 - 1].byte0F;
    gFrameObjects[9].unknown23[2] = gSetup1B894[gWork1B894.setup80].parts[gWork1B894.choice82 - 1].target0E;
    gFrameObjects[9].unknown23[3] = 0;
    gFrameObjects[9].unknown23[4] = 0;
    sub_08040B90(gState0NextCommands_083B6100[24], 9);
}
