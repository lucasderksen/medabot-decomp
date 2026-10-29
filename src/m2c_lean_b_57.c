/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_commands.h"
#include "render_work.h"

struct ContinuedWork4C8 {
    u8 unknown000[0x800];
    u16 width800;
    u16 height802;
    u16 width804;
    u16 height806;
    u8 unknown808[8];
    u8 buffer810[0x400];
    u8 unknownC10[0x46];
    u8 cellX;
    u8 cellY;
};

extern struct ContinuedWork4C8 gContinuedWork_030057E0;

u32 sub_080524C8(u32 directionArg);

u32 sub_080524C8(u32 directionArg) {

    u8 direction = directionArg;
    u8 result; /* unset for direction > 3, as in the reference; callers only pass 0-3 */

    switch (direction) {
    case 0:
        result = *((gContinuedWork_030057E0.cellY - 1) * (gContinuedWork_030057E0.width800 >> 1) + gContinuedWork_030057E0.cellX + gContinuedWork_030057E0.buffer810);
        break;
    case 1:
        result = *((gContinuedWork_030057E0.cellY + 1) * (gContinuedWork_030057E0.width800 >> 1) + gContinuedWork_030057E0.cellX + gContinuedWork_030057E0.buffer810);
        break;
    case 2:
        { s32 idx = gContinuedWork_030057E0.cellY * (gContinuedWork_030057E0.width800 >> 1) - 1; idx += gContinuedWork_030057E0.cellX; result = *(idx + gContinuedWork_030057E0.buffer810); }
        break;
    case 3:
        { s32 idx = gContinuedWork_030057E0.cellY * (gContinuedWork_030057E0.width800 >> 1) + 1; idx += gContinuedWork_030057E0.cellX; result = *(idx + gContinuedWork_030057E0.buffer810); }
        break;
    }
    return result;
}
