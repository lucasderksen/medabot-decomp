/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_scene_records.h"
#include "coordinate_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "tile_text.h"

struct Work22E14 { u8 pad[0x88]; u8 setup88; u8 pad89[0x21]; u8 counterAA; };

extern const u8 *gState0NextCommands_083B6100[];
extern struct Work22E14 gWork22E14 asm("gCounter6ED08_03001800");
extern void sub_08074DE0(u32);

void sub_08022E14(void);

void sub_08022E14(void) {

    u32 i;
    union { struct TileCoordinates tile; s32 packed; } coords;

    gFrameObjects[0x25].flags = 0xC604;
    gFrameObjects[0x25].tableSelector = 0;
    gFrameObjects[0x25].screenX = gFrameObjects[gWork22E14.setup88 * 4 + 0x5D].screenX;
    gFrameObjects[0x25].screenY = gFrameObjects[gWork22E14.setup88 * 4 + 0x5D].screenY - 4;
    gFrameObjects[0x25].palette = 7;
    gFrameObjects[0x25].scaleX = 0x40;
    gFrameObjects[0x25].scaleY = 0x40;
    gFrameObjects[0x25].priority = 0xF0;
    sub_08040B90(gState0NextCommands_083B6100[63], 0x25);
    for (i = 0; i < 4; i++) {
        gFrameObjects[0x21 + i].flags = 0xC604;
        coords.tile = sub_08042BC0(i << 6, 0x10,
                                   gFrameObjects[gWork22E14.setup88 * 4 + 0x5D].screenX,
                                   gFrameObjects[gWork22E14.setup88 * 4 + 0x5D].screenY - 4);
        gFrameObjects[0x21 + i].screenX = coords.packed;
        gFrameObjects[0x21 + i].screenY = coords.packed >> 16;
        gFrameObjects[0x21 + i].tableSelector = 0;
        gFrameObjects[0x21 + i].palette = 7;
        gFrameObjects[0x21 + i].priority = 0xF0;
        gFrameObjects[0x21 + i].frameAndGroup = 0x4604;
        gFrameObjects[0x21 + i].scaleX = 0x40;
        gFrameObjects[0x21 + i].scaleY = 0x40;
        gFrameObjects[0x21 + i].byte2B = 0x10;
        gFrameObjects[0x21 + i].unknown2C[0] = i << 6;
        gFrameObjects[0x21 + i].unknown2C[1] = 0;
    }
    sub_08074DE0(0x4B);
    gWork22E14.counterAA++;
}
