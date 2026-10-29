/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "frame.h"
#include "state0_work.h"

struct BattleView6BFEC { u8 pad00[0x41]; s8 value41; };

extern struct BattleView6BFEC gBattleView6BFEC asm("gCounter6ED08_03001800");
extern u8 gContinuedBytes6BFEC[] asm("gContinuedByte_03002B64");

void sub_0806BFEC(void);

void sub_0806BFEC(void) {

    s32 mode = 3 & gContinuedBytes6BFEC[1];

    if (mode == 1) {
        if (++gBattleView6BFEC.value41 > 8)
            gBattleView6BFEC.value41 = 8;
    } else if (mode == 2) {
        if (--gBattleView6BFEC.value41 < -8)
            gBattleView6BFEC.value41 = -8;
    } else {
        if (gBattleView6BFEC.value41 > 0)
            gBattleView6BFEC.value41--;
        if (gBattleView6BFEC.value41 < 0)
            gBattleView6BFEC.value41++;
    }
    gFrameObjects[0x1E].screenX = gBattleView6BFEC.value41 * 3 + 0x78;
}
