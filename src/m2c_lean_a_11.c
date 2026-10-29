/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Record21418 { u8 unknown0[2]; u8 active; u8 value; u8 count4; u8 count5; u8 unknown6[2]; };
struct Work21418
{
    u8 unknown00[0x28];
    struct Record21418 records[5];
    u8 unknown50;
    u8 mode51;
    u8 value52;
    u8 flag53;
    u8 unknown54[0x33];
    u8 setup87;
    u8 unknown88[2];
    u8 slot8A;
    u8 unknown8B[0x1F];
    u8 counterAA;
    u8 unknownAB[0x3D];
    u16 valueE8;
    u8 unknownEA[2];
    s16 valueEC;
};
struct Setup21418 { u8 unknown00[0xD5]; u8 byteD5; u8 unknownD6[0x2A]; };

extern struct Setup21418 gSetup21418[] asm("gSetupBuffer_03000590");
extern struct Work21418 gWork21418 asm("gCounter6ED08_03001800");
extern void sub_08035740(u8 *, s32, u32);

void sub_0801A144(const u8 *source, u32 selected);
void sub_08021418(void);

void sub_0801A144(const u8 *source, u32 selected) {

    u32 i;
    u32 root;
    struct FrameObject *ref;

    i = 0;
    root = (u32)gFrameObjects;
    for (; i < 3; i++) {
        if (source[i] == 0xFE) {
            ((struct FrameObject *)(root + ((selected * 4 + 10 + i) << 6)))->commandOffset = 0xFF;
            return;
        }
        ((struct FrameObject *)(root + ((selected * 4 + 10 + i) << 6)))->flags = 0xC224;
        ((struct FrameObject *)(root + ((selected * 4 + 10 + i) << 6)))->tableSelector = 0;
        ref = (struct FrameObject *)(((selected * 4 + 0x5D) << 6) + root);
        ((struct FrameObject *)(root + ((selected * 4 + 10 + i) << 6)))->screenY = ref->screenY + 4;
        ((struct FrameObject *)(root + ((selected * 4 + 10 + i) << 6)))->priority = 0x90;
        ((struct FrameObject *)(root + ((selected * 4 + 10 + i) << 6)))->frameAndGroup = source[i] + 0x800;
        ((struct FrameObject *)(root + ((selected * 4 + 10 + i) << 6)))->commandDelay = i * 4;
        ((struct FrameObject *)(root + ((selected * 4 + 10 + i) << 6)))->commandOffset = 0;
        ((struct FrameObject *)(root + ((selected * 4 + 10 + i) << 6)))->scaleY = 0x40;
        ((struct FrameObject *)(root + ((selected * 4 + 10 + i) << 6)))->scaleX = 0x40;
        ((struct FrameObject *)(root + ((selected * 4 + 10 + i) << 6)))->palette = source[0] + 1;
        switch (source[6]) {
        case 1:
            ((struct FrameObject *)(root + ((selected * 4 + 10 + i) << 6)))->screenX = ref->screenX + i * 8;
            break;
        case 2:
            ((struct FrameObject *)(root + ((selected * 4 + 10 + i) << 6)))->screenX = (u16)ref->screenX + (u16)-4 + i * 8;
            break;
        case 3:
            ((struct FrameObject *)(root + ((selected * 4 + 10 + i) << 6)))->screenX = (u16)ref->screenX + (u16)-8 + i * 8;
            break;
        case 4:
            ((struct FrameObject *)(root + ((selected * 4 + 10 + i) << 6)))->screenX = (u16)ref->screenX + (u16)-12 + i * 8;
            break;
        }
    }
}

void sub_08021418(void) {

    if (gWork21418.records[gWork21418.slot8A].active != 0
        && gWork21418.records[gWork21418.slot8A].value == gWork21418.value52) {
        gWork21418.flag53 = 1;
        if (gWork21418.mode51 != 2) {
            sub_08035740(&gWork21418.records[gWork21418.slot8A].count4, (s16)gWork21418.valueE8 >> 1, 0xFF);
            sub_08035740(&gWork21418.records[gWork21418.slot8A].count5,
                         (gWork21418.valueEC + gSetup21418[gWork21418.setup87].byteD5) >> 1, 0xFF);
            gWork21418.counterAA++;
        } else {
            gWork21418.records[gWork21418.slot8A].count4++;
            gWork21418.counterAA++;
        }
    } else {
        gWork21418.flag53 = 0;
        gWork21418.records[gWork21418.slot8A].active = 1;
        gWork21418.records[gWork21418.slot8A].value = gWork21418.value52;
        gWork21418.records[gWork21418.slot8A].count4 = 0;
        gWork21418.records[gWork21418.slot8A].count5 = 0;
        if (gWork21418.mode51 != 2) {
            sub_08035740(&gWork21418.records[gWork21418.slot8A].count4, (s16)gWork21418.valueE8, 0xFF);
            sub_08035740(&gWork21418.records[gWork21418.slot8A].count5,
                         gWork21418.valueEC + gSetup21418[gWork21418.setup87].byteD5, 0xFF);
        } else {
            gWork21418.records[gWork21418.slot8A].count4++;
        }
        gWork21418.counterAA++;
    }
}
