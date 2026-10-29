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
#include "state0_callbacks.h"

struct Counter221C8 { u8 pad[0xAA]; u8 counter; };

extern const u8 *gState0NextCommands_083B6100[];
extern const u8 gUnknown_084D6D28[];
extern const u8 gUnknown_0850FC78[];
extern struct Counter221C8 gCounter221C8 asm("gCounter6ED08_03001800");
extern u8 gUnknown_03001887;

void sub_080221C8(void);

void sub_080221C8(void) {

    u32 i;

    LeDecompress(gUnknown_084D6D28, (void *)0x06014800);
    CpuFastSet(gUnknown_0850FC78, (void *)0x050002E0, 8);
    for (i = 0; i < 4; i++) {
        gFrameObjects[0x21 + i].flags = 0xC604;
        gFrameObjects[0x21 + i].tableSelector = 0;
        gFrameObjects[0x21 + i].screenX = gFrameObjects[gUnknown_03001887 * 4 + 0x5D].screenX;
        gFrameObjects[0x21 + i].screenY = gFrameObjects[gUnknown_03001887 * 4 + 0x5D].screenY - 4;
        gFrameObjects[0x21 + i].palette = 7;
        gFrameObjects[0x21 + i].priority = 0xF0;
        gFrameObjects[0x21 + i].scaleX = 0x40;
        gFrameObjects[0x21 + i].scaleY = 0x40;
        gFrameObjects[0x21 + i].byte2B = 0;
        gFrameObjects[0x21 + i].unknown2C[0] = i << 6;
        gFrameObjects[0x21 + i].unknown2C[1] = 0;
        sub_08040B90(gState0NextCommands_083B6100[61], i + 0x21);
    }
    sub_08074DE0(0x5C);
    gCounter221C8.counter++;
}
