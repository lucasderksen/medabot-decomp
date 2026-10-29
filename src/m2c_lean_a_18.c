/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "coordinate_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "tile_text.h"

struct Work22648 { u8 pad[0x87]; u8 setup87; u8 pad88[0x22]; u8 counterAA; };

extern struct Work22648 gWork22648 asm("gCounter6ED08_03001800");
extern void sub_08074DE0(u32);

void sub_08022648(void);

void sub_08022648(void) {

    u32 i;
    union { struct TileCoordinates tile; s32 packed; } coords;

    for (i = 0; i < 2; i++) {
        coords.tile = sub_08042BC0(gFrameObjects[0x21 + i].unknown2C[0], gFrameObjects[0x21 + i].byte2B,
                                   gFrameObjects[gWork22648.setup87 * 4 + 0x5D].screenX,
                                   gFrameObjects[gWork22648.setup87 * 4 + 0x5D].screenY - 4);
        gFrameObjects[0x21 + i].screenX = coords.packed;
        gFrameObjects[0x21 + i].screenY = coords.packed >> 16;
        gFrameObjects[0x21 + i].unknown2C[0] += 8;
        gFrameObjects[0x21 + i].unknown2C[1]++;
        if ((gFrameObjects[0x21 + i].unknown2C[1] & 3) == 0)
            gFrameObjects[0x21 + i].byte2B--;
        if (gFrameObjects[0x21 + i].scaleX != 0x40) {
            gFrameObjects[0x21 + i].scaleX--;
            gFrameObjects[0x21 + i].scaleY--;
        }
    }
    if (gFrameObjects[0x21].byte2B == 0) {
        sub_08074DE0(0x30);
        sub_08040CD0(0x22, 1);
        gWork22648.counterAA++;
    }
}
