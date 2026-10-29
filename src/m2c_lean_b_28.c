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
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_work.h"

struct Frame2E4C8 {
    u16 flags;
    s16 screenX;
    s16 screenY;
    u16 frameAndGroup;
    u8 scaleX;
    u8 scaleY;
    u8 palette;
    u8 priority;
    u8 pad0C[0xC];
    u16 angle;
    u8 pad1A[2];
    u8 tableSelector;
    u8 pad1D[6];
    u8 byte23;
    u8 byte24;
    u8 pad25[0xB];
    u16 word30;
    s16 word32;
    u8 pad34[0xC];
};
struct SetupRecord37458 {
    u8 pad0[0x58];
    u8 uses58;
    u8 pad59[0xA7];
};

extern const u8 *const gState0NextCommands_083B6100[];
extern const u8 gUnknown_084D8528[];
extern const u8 gUnknown_0850FED8[];
extern struct Frame2E4C8 gFrames2E4C8[] asm("gFrameObjects");
extern struct SetupRecord37458 gSetupRecords37458[] asm("gSetupBuffer_03000590");

void sub_0802E4C8(void);
void sub_0802EC4C(void);
void sub_08037458(s32 slot, s32 amount);

void sub_0802E4C8(void) {

    u32 i;

    LeDecompress(gUnknown_084D8528, (void *)0x06014800);
    CpuFastSet(gUnknown_0850FED8, (void *)0x050002E0, 0x10);
    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            gFrames2E4C8[i + 0xA].flags = 0xC624;
            gFrames2E4C8[i + 0xA].tableSelector = 0;
            gFrames2E4C8[i + 0xA].screenX = 0x78;
            gFrames2E4C8[i + 0xA].screenY = 0x40;
            gFrames2E4C8[i + 0xA].scaleX = 4;
            gFrames2E4C8[i + 0xA].scaleY = 4;
            gFrames2E4C8[i + 0xA].angle = 0;
            gFrames2E4C8[i + 0xA].word30 = gFrames2E4C8[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenX;
            gFrames2E4C8[i + 0xA].word32 = gFrames2E4C8[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenY - 4;
            gFrames2E4C8[i + 0xA].byte24 = 6;
            gFrames2E4C8[i + 0xA].byte23 = 0;
            gFrames2E4C8[i + 0xA].palette = 7;
            gFrames2E4C8[i + 0xA].priority = 0xE0;
            gState0TypedWork.bytes[0x84] = 0x48;
            sub_08040B90(gState0NextCommands_083B6100[gState0TypedWork.bytes[0x84]], i + 0xA);
        }
    }
    sub_08074DE0(0x6A);
    gCounter6ED08_03001800.counterAA++;
}

void sub_0802EC4C(void) {

    u32 i;

    LeDecompress(gUnknown_084D8528, (void *)0x06014800);
    CpuFastSet(gUnknown_0850FED8, (void *)0x050002E0, 0x10);
    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            gFrameObjects[i + 0x21].flags = 0xC624;
            gFrameObjects[i + 0x21].tableSelector = 0;
            gFrameObjects[i + 0x21].screenX = gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenX;
            gFrameObjects[i + 0x21].screenY = gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenY - 4;
            gFrameObjects[i + 0x21].scaleX = 0x80;
            gFrameObjects[i + 0x21].scaleY = 0x80;
            gFrameObjects[i + 0x21].angle = 0;
            gFrameObjects[i + 0x21].palette = 7;
            gFrameObjects[i + 0x21].priority = 0xE0;
            gState0TypedWork.bytes[0x84] = 0x48;
            sub_08040B90(gState0NextCommands_083B6100[gState0TypedWork.bytes[0x84]], i + 0x21);
        }
    }
    sub_08074DE0(0x6A);
    gCounter6ED08_03001800.counterAA++;
}

void sub_08037458(s32 slot, s32 amount) {

    u8 uses = gSetupRecords37458[slot].uses58;

    if (uses > amount) {
        gCounter6ED08_03001800.valueC8 = amount;
        gCounter6ED08_03001800.valueCC = amount;
        gCounter6ED08_03001800.valueCA = 0;
    } else {
        gCounter6ED08_03001800.valueC8 = uses;
        gCounter6ED08_03001800.valueCC = uses;
        gCounter6ED08_03001800.valueCA = amount - uses;
    }
}
