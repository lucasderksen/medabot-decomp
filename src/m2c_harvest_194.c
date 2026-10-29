/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_work.h"

struct Graphics6CD68 {u8 pad00[0x41];s8 selection;};
struct FrameWork6CD68 {u8 pad0[0x782];u16 x30;u16 y30;u16 frame30;u8 scaleX30;u8 scaleY30;u8 pad78A[0xE];u16 angle30;u16 timer30;u8 pad79C[0x4];u8 state30;u8 direction30;u8 result30;u8 pad7A3[0x9F];u16 x33;u16 y33;u8 pad846[0x600];u16 frame57;};

extern const u8 gWaveTable08485924[64];
extern s32 sub_0807CEC8(s32,s32);
extern struct Graphics6CD68 gGraphicsWork6CD6803001800;

void sub_0806CD68(void);

void sub_0806CD68(void) {
    s32 selection;
    u32 bit;
    u16 *var_r0_2;
    struct FrameWork6CD68 *mirror;
    u16 *sourceY;
    u16 *sourceTimer;
    u16 *var_r1_2;
    u32 var_r0;
    u16 var_r1;
    u16 var_r1_3;
    u16 var_r2;
    u16 var_r2_2;

    selection=gGraphicsWork6CD6803001800.selection;
    if (selection > 3) {
        struct FrameWork6CD68 *branchBase;
        var_r2=3;
        branchBase=(struct FrameWork6CD68 *)gFrameObjects;
        if (selection == 8) {
            var_r2 = 4;
        }
        branchBase->frame30 = var_r2;
    } else if (selection < -3) {
        struct FrameWork6CD68 *branchBase;
        branchBase=(struct FrameWork6CD68 *)gFrameObjects;
        var_r2_2=selection==-8?2:1;
        branchBase->frame30 = var_r2_2;
    } else {
        ((struct FrameWork6CD68 *)gFrameObjects)->frame30 = 0;
    }
    if (((struct FrameWork6CD68 *)gFrameObjects)->direction30 == 0) {
        return;
    }
    bit=8 & ((struct FrameWork6CD68 *)gFrameObjects)->timer30;
    var_r1 = 6;
    if (bit) {
        var_r1 = 5;
    }
    ((struct FrameWork6CD68 *)gFrameObjects)->frame30 = var_r1;
    if (((struct FrameWork6CD68 *)gFrameObjects)->result30 != 0) {
        var_r1_2 = &((struct FrameWork6CD68 *)gFrameObjects)->angle30;
        var_r0 = ((struct FrameWork6CD68 *)gFrameObjects)->angle30 + 0x20;
    } else {
        var_r1_2 = &((struct FrameWork6CD68 *)gFrameObjects)->angle30;
        var_r0 = ((struct FrameWork6CD68 *)gFrameObjects)->angle30 - 0x20;
    }
    *var_r1_2 = var_r0;
    mirror=(struct FrameWork6CD68 *)gFrameObjects;
    mirror->x33 = (s16) (u16) mirror->x30;
    sourceY=&mirror->y30;
    sourceTimer=&mirror->timer30;
    mirror->y33=sub_0807CEC8(*sourceTimer,0xA)+0xC+*sourceY;
    if ((u32) mirror->timer30 <= 0x1FU) {
        mirror->scaleX30 = ((s8)gWaveTable08485924[mirror->timer30]>>1) + 0x40;
        mirror->scaleY30 = ((s8)gWaveTable08485924[mirror->timer30]>>1) + 0x40;
        return;
    }
    if (mirror->state30 == 3) {
        bit=4 & mirror->timer30;
        var_r1_3 = 0x2C;
        if (bit) {
            var_r1_3 = 0x2B;
        }
        mirror->frame57=var_r1_3;
        return;
    }
    if (mirror->state30 == 2) {
        bit=4 & mirror->timer30;
        var_r1_3 = 0x2D;
        if (bit) {
            var_r1_3 = 0x2C;
        }
        ((struct FrameWork6CD68 *)gFrameObjects)->frame57=var_r1_3;
    }
}
