/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "frame.h"

struct SetupPart37728 {
    u8 pad0[0x11];
    u8 count11;
    u8 pad12[6];
};
struct SetupRecord37728 {
    u8 pad0[0x48];
    struct SetupPart37728 parts[3];
    u8 pad90[0x70];
};

extern struct SetupRecord37728 gSetupRecords37728[] asm("gSetupBuffer_03000590");

s32 sub_08037728(s32 slot, s32 part, u32 limit);

s32 sub_08037728(s32 slot, s32 part, u32 limit) {

    /* Falls off the end like the reference (r0 still holds slot); the only caller, sub_080268D4, ignores the result. */
    if (gSetupRecords37728[slot].parts[part].count11 == 0) {
        gCounter6ED08_03001800.valuesD6[part] = 0;
        gCounter6ED08_03001800.activeD2[part] = 0;
    } else if (gSetupRecords37728[slot].parts[part].count11 > limit) {
        gCounter6ED08_03001800.valuesD6[part] = limit;
        gCounter6ED08_03001800.activeD2[part] = 0;
    } else {
        gCounter6ED08_03001800.valuesD6[part] = gSetupRecords37728[slot].parts[part].count11;
        gCounter6ED08_03001800.activeD2[part] = 1;
    }
}
