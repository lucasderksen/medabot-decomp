/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_work.h"

struct Work28A38
{
    u8 unknown00[0x51];
    u8 mode51;
    u8 unknown52[0xE];
    u8 base60;
    u8 unknown61[0x49];
    u8 counterAA;
    u8 unknownAB[0x27];
    u8 activeD2[3];
};

extern const u8 gUnknown_084DE4F4[];
extern const u8 gUnknown_085101F8[];
extern struct Work28A38 gWork28A38 asm("gCounter6ED08_03001800");

void sub_08028A38(void);

void sub_08028A38(void) {

    u32 i;

    LeDecompress(gUnknown_084DE4F4, (void *)0x06016000);
    CpuFastSet(gUnknown_085101F8, (void *)0x050002E0, 8);
    for (i = 0; i < 3; i++) {
        if (gWork28A38.activeD2[i] != 0) {
            gFrameObjects[0x21 + i].flags = 0xC404;
            gFrameObjects[0x21 + i].tableSelector = 0;
            gFrameObjects[0x21 + i].screenX = gFrameObjects[(gWork28A38.base60 + i) * 4 + 0x5D].screenX;
            gFrameObjects[0x21 + i].screenY = gFrameObjects[(gWork28A38.base60 + i) * 4 + 0x5D].screenY - 4;
            gFrameObjects[0x21 + i].palette = 7;
            gFrameObjects[0x21 + i].priority = 0xF0;
            gFrameObjects[0x21 + i].unknown23[0] = 0;
            switch (gWork28A38.mode51) {
            case 0:
                gFrameObjects[0x21 + i].frameAndGroup = 0x6F00;
                break;
            case 1:
                gFrameObjects[0x21 + i].frameAndGroup = 0x6F03;
                break;
            case 2:
                gFrameObjects[0x21 + i].frameAndGroup = 0x6F01;
                break;
            case 3:
                gFrameObjects[0x21 + i].frameAndGroup = 0x6F02;
                break;
            case 4:
                gFrameObjects[0x21 + i].frameAndGroup = 0x6F05;
                break;
            case 5:
                gFrameObjects[0x21 + i].frameAndGroup = 0x6F04;
                break;
            }
        }
    }
    sub_08074DE0(0x5B);
    gWork28A38.counterAA++;
}
