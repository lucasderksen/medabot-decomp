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
#include "frame_objects.h"
#include "gba.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Work291E0
{
    u8 unknown00[0x60];
    u8 base60;
    u8 unknown61[0x26];
    u8 setup87;
    u8 unknown88[0x22];
    u8 counterAA;
    u8 unknownAB[0x27];
    u8 activeD2[3];
};
struct Setup291E0 { u8 unknown00[0x40]; u8 active40; u8 unknown41[0x18]; u8 byte59; u8 unknown5A[0xA6]; };

extern const u8 *gState0NextCommands_083B6100[];
extern const u8 gUnknown_084DE9FC[];
extern const u8 gUnknown_08510238[];
extern struct Setup291E0 gSetup291E0[] asm("gSetupBuffer_03000590");
extern struct Work291E0 gWork291E0 asm("gCounter6ED08_03001800");
extern void sub_0803836C(void);

void sub_080291E0(void);

void sub_080291E0(void) {

    u32 i;

    LeDecompress(gUnknown_084DE9FC, (void *)0x06014800);
    CpuFastSet(gUnknown_08510238, (void *)0x050002E0, 8);
    sub_0803836C();
    gWork291E0.base60 = sub_08032FC4(gWork291E0.setup87);
    for (i = 0; i < 3; i++) {
        if (gSetup291E0[gWork291E0.base60 + i].active40 != 0 && gSetup291E0[gWork291E0.base60 + i].byte59 != 0) {
            gWork291E0.activeD2[i] = 1;
            gFrameObjects[0x21 + i].flags = 0xC404;
            gFrameObjects[0x21 + i].tableSelector = 0;
            gFrameObjects[0x21 + i].screenX = gFrameObjects[(gWork291E0.base60 + i) * 4 + 0x5D].screenX;
            gFrameObjects[0x21 + i].screenY = gFrameObjects[(gWork291E0.base60 + i) * 4 + 0x5D].screenY - 4;
            gFrameObjects[0x21 + i].palette = 7;
            gFrameObjects[0x21 + i].priority = 0xF0;
            sub_08040B90(gState0NextCommands_083B6100[95], i + 0x21);
        }
    }
    gWork291E0.counterAA++;
}
