/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "bg_scroll.h"
#include "record_helpers.h"
#include "tile_text.h"

extern struct { u8 b[0x100]; } gCounter6ED08_03001800;

void sub_08035C3C(void);

void sub_08035C3C(void) {

    u16 var_r1;
    u16 *p;

    var_r1 = 1 & gCounter6ED08_03001800.b[0xF8];
    if (var_r1 != 0) {
        p = &gBgScroll2.x;
        var_r1 = 0x110;
    } else {
        p = &gBgScroll2.x;
    }
    *p = var_r1;
    gBgScroll3.x = var_r1;
}
