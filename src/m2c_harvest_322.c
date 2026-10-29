/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"

struct CV { u8 pad[0xF8]; u8 bF8; u8 padF9[0x102 - 0xF9]; s16 h102; };

extern s32 sub_0803D450();
extern s32 sub_0803D4AC();
extern struct CV gCounter6ED08_03001800;

void sub_0803981C(void);

void sub_0803981C(void) {

    u8 *p;
    u8 *c;

    sub_0803D450();
    c = (u8 *)&gCounter6ED08_03001800;
    switch (gCounter6ED08_03001800.h102) {
    case 0:
        if (2 & gCounter6ED08_03001800.bF8) {
            p = c + 0x160;
        } else {
            p = c + 0x15F;
        }
        if (*p != 0) {
            sub_0803D4AC();
        }
        break;
    case 1:
        if (2 & gCounter6ED08_03001800.bF8) {
            p = c + 0x15F;
        } else {
            p = c + 0x160;
        }
        if (*p != 0) {
            sub_0803D4AC();
        }
        break;
    default:
        if ((c[0x15F] != 0) && (c[0x160] != 0)) {
            sub_0803D4AC();
        }
        break;
    }
    gFrameObjects->unknown23[7] = 1;
}
