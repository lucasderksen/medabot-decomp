/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "frame.h"
#include "state0_work.h"

struct SetupPart {
    u8 pad0[2];
    u8 byte2;
    u8 pad3;
    u8 byte4;
    u8 pad5[0xC];
    u8 byte11;
    u8 pad12[6];
};
struct SetupRecord {
    u8 pad0[0x48];
    struct SetupPart parts[3];
    u8 pad90[0x70];
};
extern s32 sub_08035880(u8, u8, u8);
extern s32 sub_080358B8(u8, u8, u8);
extern s32 sub_08038F34(s16);
extern struct SetupRecord gSetupRecords[] asm("gSetupBuffer_03000590");

s32 sub_08038E9C(void);

s32 sub_08038E9C(void) {

    u8 kind;

    if (sub_08035880(gCounter6ED08_03001800.slot87, gCounter6ED08_03001800.partA7, gCounter6ED08_03001800.value88))
        {
        if (sub_08038F34(gCounter6ED08_03001800.valueEE) != 0)
            return 1;
        return 0;
    }
    if (sub_080358B8(gCounter6ED08_03001800.slot87, gCounter6ED08_03001800.partA7, gCounter6ED08_03001800.value88))
        {
        if (sub_08038F34(gCounter6ED08_03001800.valueEE) != 0)
            return 1;
        return 0;
    }
    kind = gSetupRecords[gCounter6ED08_03001800.slot87].parts[gCounter6ED08_03001800.partA7].byte2;
    if (kind == 3)
        {
        if (sub_08038F34(gCounter6ED08_03001800.valueEE << 1) != 0)
            return 1;
        return 0;
    }
    if (kind == 0)
        {
        if (sub_08038F34(gCounter6ED08_03001800.valueEE << 2) != 0)
            return 1;
        return 0;
    }
    {
        if (sub_08038F34(gCounter6ED08_03001800.valueEE << 3) != 0)
            return 1;
        return 0;
    }
}
