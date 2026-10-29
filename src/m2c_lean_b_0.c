/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_work.h"

 struct Record8394 {
    u8 pad0[0xC4];
    u8 bytesC4[4];
    u8 padC8;
    u8 bytesC9[3];
    u8 byteCC;
    u8 padCD[0x33];
};

extern struct Record8394 gSetupRecords8394[] asm("gSetupBuffer_03000590");

void sub_0802BB24(void);
void sub_080373D4(s32 arg0);
void sub_08038394(s32 arg0, s32 arg1);
void sub_0803D4EC(s32 arg0, s32 arg1);

void sub_0802BB24(void) {

    u32 i;

    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            gFrameObjects[i + 0x21].flags = 0xC404;
            gFrameObjects[i + 0x21].priority = 0xE0;
            gFrameObjects[i + 0x21].screenY += 8;
            gFrameObjects[i + 0x21].palette = 7;
            gFrameObjects[i + 0x21].frameAndGroup = gCounter6ED08_03001800.frame51 + 0x7C04;
        }
    }
    gState0TypedWork.widths.word86 = 0;
    sub_08074DE0(0x2E);
    gCounter6ED08_03001800.counterAA++;
}

void sub_080373D4(s32 arg0) {

    gFrameObjects[arg0 * 4 + 0x5A].flags |= 0x8000;
    gFrameObjects[arg0 * 4 + 0x5B].flags |= 0x8000;
    gFrameObjects[arg0 * 4 + 0x5C].flags |= 0x8000;
    gFrameObjects[arg0 * 4 + 0x5D].flags |= 0x8000;
}

void sub_08038394(s32 arg0, s32 arg1) {

    if (arg1 & 1) {
        gSetupRecords8394[arg0].bytesC9[0] = 0;
        gSetupRecords8394[arg0].bytesC9[1] = 0;
        gSetupRecords8394[arg0].bytesC9[2] = 0;
        gSetupRecords8394[arg0].byteCC = 0;
    }
    if (arg1 & 2) {
        gSetupRecords8394[arg0].bytesC4[0] = 0;
        gSetupRecords8394[arg0].bytesC4[1] = 0;
        gSetupRecords8394[arg0].bytesC4[2] = 0;
        gSetupRecords8394[arg0].bytesC4[3] = 0;
    }
}

void sub_0803D4EC(s32 arg0, s32 arg1) {

    u32 i;

    for (i = 0; i <= 0x13; i++) {
        if (gFrameObjects[i + 0xA].unknown23[6] != 0) {
            if (arg0 != 0)
                gFrameObjects[i + 0xA].screenX = (gFrameObjects[i + 0xA].screenX - arg1) & 0x1FF;
            else
                gFrameObjects[i + 0xA].screenX = (gFrameObjects[i + 0xA].screenX + arg1) & 0x1FF;
        }
    }
}
