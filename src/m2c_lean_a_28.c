/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "record_helpers.h"

struct Work1D06C { u8 pad[0x3C]; u8 side3C; u8 pad3D[0x14]; u8 mode51; u8 pad52[0x37]; u8 player89; u8 pad8A[0x20]; u8 counterAA; };

extern struct Work1D06C gWork1D06C asm("gCounter6ED08_03001800");

void sub_0801D06C(void);

void sub_0801D06C(void) {

    gFrameObjects[0x21].flags = ((gWork1D06C.side3C + 2) << 10) | 0xC204;
    gFrameObjects[0x21].tableSelector = 0;
    gFrameObjects[0x21].palette = 6;
    gFrameObjects[0x21].scaleY = 0x40;
    gFrameObjects[0x21].scaleX = 8;
    gFrameObjects[0x21].priority = 0xF0;
    gFrameObjects[0x21].screenY = 0x3C;
    if (gWork1D06C.player89 == 0) {
        gFrameObjects[0x21].flags |= 0x1000;
        gFrameObjects[0x21].screenX = 0x68;
    } else {
        gFrameObjects[0x21].screenX = 0x88;
    }
    switch (gWork1D06C.mode51) {
    case 0:
        gFrameObjects[0x21].frameAndGroup = 0xB00;
        break;
    case 1:
        gFrameObjects[0x21].frameAndGroup = 0xC00;
        break;
    case 2:
        gFrameObjects[0x21].frameAndGroup = 0xD00;
        break;
    case 3:
        gFrameObjects[0x21].frameAndGroup = 0xE00;
        break;
    }
    gWork1D06C.counterAA++;
}
