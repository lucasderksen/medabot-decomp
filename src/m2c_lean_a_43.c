/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "coordinate_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sprite_layouts.h"
#include "state0_work.h"
#include "tile_text.h"

struct Work22B40 { u8 pad[0x88]; u8 setup88; u8 pad89[0x21]; u8 counterAA; };

extern const u8 *gState0NextCommands_083B6100[];
extern struct Work22B40 gWork22B40 asm("gCounter6ED08_03001800");

void sub_08022B40(void);

void sub_08022B40(void) {

    u32 i;
    u32 root;
    u32 base;
    u32 count;
    u8 count8;
    union { struct TileCoordinates tile; s32 packed; } coords;

    sub_08040BD8(gState0NextCommands_083B6100[63], 0x25);
    for (i = 0, base = (u32)gFrameObjects; i < 5; i++) {
        if (i < 4) {
            coords.tile = sub_08042BC0(((struct FrameObject *)(((0x21 + i) << 6) + base))->unknown2C[0], ((struct FrameObject *)(((0x21 + i) << 6) + base))->byte2B,
                                       ((struct FrameObject *)(((gWork22B40.setup88 * 4 + 0x5D) << 6) + base))->screenX,
                                       ((struct FrameObject *)(((gWork22B40.setup88 * 4 + 0x5D) << 6) + base))->screenY - 4);
            ((struct FrameObject *)(((0x21 + i) << 6) + base))->screenX = coords.packed;
            ((struct FrameObject *)(((0x21 + i) << 6) + base))->screenY = coords.packed >> 16;
            ((struct FrameObject *)(((0x21 + i) << 6) + base))->unknown2C[0] += 4;
        }
        count = ((struct FrameObject *)(((0x21 + i) << 6) + base))->unknown2C[1] + 1;
        ((struct FrameObject *)(((0x21 + i) << 6) + base))->unknown2C[1] = count;
        count8 = count;
        root = (u32)gFrameObjects;
        if (count8 > 0x5A) {
            if (count & 1)
                ((struct FrameObject *)(((0x21 + i) << 6) + base))->byte2B++;
            ((struct FrameObject *)(((0x21 + i) << 6) + base))->scaleX -= 2;
            ((struct FrameObject *)(((0x21 + i) << 6) + base))->scaleY -= 2;
        }
    }
    if (*(u8 *)(root + 0x849) == 4) {
        sub_08040CD0(0x21, 5);
        gWork22B40.counterAA++;
    }
}
