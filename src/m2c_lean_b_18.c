/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "background_state.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "record_helpers.h"

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
extern const u8 gUnknown_084D7ABC[];
extern const u8 gUnknown_0850FDF8[];
extern struct FrameObjectWords gFrameObjectWords[] asm("gFrameObjects");

void sub_0802D7EC(void);

void sub_0802D7EC(void) {

    u32 i;

    sub_08040CD0(0x21, 1);
    LeDecompress(gUnknown_084D7ABC, (void *)0x06014800);
    CpuFastSet(gUnknown_0850FDF8, (void *)0x050002E0, 8);
    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            gFrameObjectWords[i + 0x21].flags = 0xC624;
            gFrameObjectWords[i + 0x21].bytes1C[0] = 0;
            gFrameObjectWords[i + 0x21].screenX = 0x78;
            gFrameObjectWords[i + 0x21].screenY = 0x40;
            gFrameObjectWords[i + 0x21].palette = 7;
            gFrameObjectWords[i + 0x21].priority = 0xF0;
            gFrameObjectWords[i + 0x21].scaleX = 0x40;
            gFrameObjectWords[i + 0x21].scaleY = 0x40;
            gFrameObjectWords[i + 0x21].angle = 0;
            gFrameObjectWords[i + 0x21].word30 = gFrameObjectWords[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenX;
            gFrameObjectWords[i + 0x21].word32 = gFrameObjectWords[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenY - 4;
            gFrameObjectWords[i + 0x21].byte24 = 6;
            gFrameObjectWords[i + 0x21].frameAndGroup = 0x4E00;
        }
    }
    gCounter6ED08_03001800.counterAA++;
}
