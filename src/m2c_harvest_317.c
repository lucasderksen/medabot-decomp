/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"

struct Ch { u8 pad[0x14]; s32 f14; };

extern u8 *gFamilySoundRoot74028;

s32 sub_08074CE0(void);

s32 sub_08074CE0(void) {

    u8 **g;
    g = &gFamilySoundRoot74028;
    if (*(s32 *)(*g + 0x14) != 0 || *(s32 *)(*g + 0x88) != 0 || ((struct Ch *)(*g + 0xE8))->f14 != 0
        || ((struct Ch *)(*g + 0x15C))->f14 != 0 || ((struct Ch *)(*g + 0x3A0))->f14 != 0 || ((struct Ch *)(*g + 0x414))->f14 != 0) {
        return *(u8 *)(*g + 0x72F);
    }
    return -1;
}
