/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_late_graphics.h"
#include "frame.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"


void sub_0805FF1C(void);

void sub_0805FF1C(void) {

    gFrameObjects[1].frameAndGroup = (4 & gFrameObjects[1].unknown1A) ? 0x109 : 0x10A;
    if ((u16)gFrameObjects[1].unknown1A < 0x78)
    {
        gFrameObjects[1].screenY = gFrameObjects[1].unknown1A * 0xA8 / 0x78 - 0x40;
        gFrameObjects[1].scaleX = -0x80 - (gFrameObjects[1].unknown1A << 6) / 0x78;
        gFrameObjects[1].scaleY = -0x80 - (gFrameObjects[1].unknown1A << 6) / 0x78;
        gFrameObjects[1].angle = (0x3F & gFrameObjects[1].unknown1A) * 16 + 0x340;
        gFrameObjects[1].unknown1A = gFrameObjects[1].unknown1A + 1;
        return;
    }
    *(volatile u16 *)0x04000000 |= 0x100;
    gFrameObjects[1].frameAndGroup = 0x10B;
    gFrameObjects[1].scaleX = 0x40;
    gFrameObjects[1].scaleY = 0x40;
    gFrameObjects[1].screenY = 0x68;
    gFrameObjects[1].angle = 0;
    gFrameObjects[1].unknown1A = 0;
    *(s16 *)((u8 *)gMainContextPointer_03006F74 + 0x3A) = 0;
    gUnknown_0300137C++;
}
