/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "compression.h"
#include "frame.h"
#include "gba.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Work276E8
{
    u8 unknown00[0x60];
    u8 base60;
    u8 unknown61[0x49];
    u8 counterAA;
    u8 unknownAB[0x27];
    u8 activeD2[3];
};

extern struct Work276E8 gWork276E8 asm("gCounter6ED08_03001800");

void sub_080276E8(void);

void sub_080276E8(void) {

    u32 found;
    u32 i;
    u32 root;
    u8 v;
    struct FrameObject *obj;

    found = 0;
    LeDecompress(gActionMotionAsset_084CF178, (void *)0x06014800);
    CpuFastSet(gActionMotionPalette_0850F918, (void *)0x050002E0, 8);

    for (i = 0; i < 3; i++) {
        if (gWork276E8.activeD2[i] & 0x80) {
            root = (u32)gFrameObjects;
            obj = (struct FrameObject *)((((gWork276E8.base60 + i) * 4 + (u8)((gWork276E8.activeD2[i] & 0x7F) + 0x5A)) << 6) + root);
            sub_08036FF8(0x21 + i * 4, obj->screenX, obj->screenY, 4);
            found = 1;
        }
    }
    if (found == 0)
        gWork276E8.counterAA += 1;
    else
        gWork276E8.counterAA += 3;
}
