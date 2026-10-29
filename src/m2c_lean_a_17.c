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
#include "tile_text.h"

struct Work222A8 { u8 pad[0x87]; u8 setup87; u8 pad88[0x22]; u8 counterAA; };

extern const u8 *gState0NextCommands_083B6100[];
extern struct Work222A8 gWork222A8 asm("gCounter6ED08_03001800");

void sub_080222A8(void);

void sub_080222A8(void) {

    u32 i;
    union { struct TileCoordinates tile; s32 packed; } coords;

    for (i = 0; i < 4; i++) {
        sub_08040BD8(gState0NextCommands_083B6100[61], i + 0x21);
        coords.tile = sub_08042BC0(gFrameObjects[0x21 + i].unknown2C[0], gFrameObjects[0x21 + i].byte2B,
                              gFrameObjects[gWork222A8.setup87 * 4 + 0x5D].screenX,
                              gFrameObjects[gWork222A8.setup87 * 4 + 0x5D].screenY - 4);
        gFrameObjects[0x21 + i].screenX = coords.packed;
        gFrameObjects[0x21 + i].screenY = coords.packed >> 16;
        gFrameObjects[0x21 + i].unknown2C[0] += 4;
        gFrameObjects[0x21 + i].unknown2C[1]++;
        if ((gFrameObjects[0x21 + i].unknown2C[1] & 3) == 0)
            gFrameObjects[0x21 + i].byte2B++;
        if (gFrameObjects[0x21 + i].unknown2C[1] > 0xB4) {
            gFrameObjects[0x21 + i].scaleX -= 4;
            gFrameObjects[0x21 + i].scaleY -= 4;
        }
    }
    if (gFrameObjects[0x21].scaleY == 4) {
        sub_08040CD0(0x21, 4);
        gWork222A8.counterAA++;
    }
}
