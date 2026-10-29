/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "background_state.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "record_helpers.h"
#include "state0_work.h"

struct FrameObjectWords {
    u16 flags;
    s16 screenX;
    s16 screenY;
    u16 frameAndGroup;
    u8 scaleX;
    u8 scaleY;
    u8 palette;
    u8 priority;
    s32 positionX;
    s32 positionY;
    s32 positionZ;
    u16 angle;
    u16 unknown1A;
    u8 bytes1C[7];
    u8 byte23;
    u8 byte24;
    u8 bytes25[4];
    u8 byte29;
    u8 byte2A;
    u8 byte2B;
    u8 byte2C;
    u8 byte2D;
    u8 byte2E;
    u8 byte2F;
    u16 word30;
    s16 word32;
    u8 bytes34[0xC];
};
extern struct FrameObjectWords gFrameObjectWords[] asm("gFrameObjects");
extern void sub_0803D450(void);
extern void sub_0803D4AC(void);

void sub_080397B0(void);

void sub_080397B0(void) {

    u8 flag;

    sub_0803D450();
    gFrameObjectWords[3].byte2B = gCounter6ED08_03001800.value102;
    flag = gCounter6ED08_03001800.flagsF8 & 2;
    if (flag == 0) {
        gFrameObjectWords[3].byte2C = flag;
        gFrameObjectWords[3].word30 = gCounter6ED08_03001800.pos154[0];
    } else {
        gFrameObjectWords[3].byte2C = 1;
        gFrameObjectWords[3].word30 = gCounter6ED08_03001800.pos154[2];
    }
    gFrameObjectWords[3].byte29 = 8;
    sub_0803D4AC();
}
