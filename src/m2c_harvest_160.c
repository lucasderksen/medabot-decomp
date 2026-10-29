/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_callbacks.h"

struct LocalMotionTransferWork { u8 pad00[8]; s32 counter8; u8 pad0C[4]; u8 phase10; };

extern struct LocalMotionTransferWork gGraphicsTransferCounter;
extern void sub_0806B718(u8);

s32 sub_08071E0C(void);

s32 sub_08071E0C(void) {
    s16 *var_r0;
    u32 var_r1;

    var_r1 = (u16)gFrameObjects[2].screenY;
    if ((s32) gFrameObjects[2].screenY <= 0x3D) {
        var_r1 += 2;
        gFrameObjects[2].screenY = var_r1;
        gFrameObjects[1].screenY = var_r1;
        return 0;
    }
    if ((s32) gFrameObjects[2].screenY <= 0x41) {
        var_r1 += 1;
        gFrameObjects[2].screenY = var_r1;
        gFrameObjects[1].screenY = var_r1;
        return 0;
    }
    if ((u32) gFrameObjects[2].unknown1A <= 0x1FU) {
        gFrameObjects[2].unknown1A += 1;
        goto block_10;
    }
    var_r1 = (u16)gFrameObjects[2].screenX;
    if ((s32) gFrameObjects[2].screenX <= 0x40) {
        sub_0806B718(6);
        sub_08074DE0(0x54U);
        gFrameObjects[2].unknown1A = 0;
        gGraphicsTransferCounter.phase10 += 1;
        return 1;
    }
    var_r1 -= 4;
    gFrameObjects[2].screenX = var_r1;
    var_r0 = &gFrameObjects[1].screenX;
block_9:
    *var_r0 = var_r1;
block_10:
    return 0;
}
