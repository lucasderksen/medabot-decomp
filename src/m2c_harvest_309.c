/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct CV { u8 p0[0x60]; u8 b60; u8 p61[0xAA - 0x61]; u8 bAA; u8 pAB[0xD2 - 0xAB]; u8 bD2[4]; };

extern struct CV gCounter6ED08_03001800;

void sub_0802CD48(void);
void sub_0802DB3C(void);
void sub_0802E098(void);

void sub_0802CD48(void) {

    s32 sp0;
    s32 temp_r3;
    s32 var_r3;
    s32 var_sb;
    struct FrameObject *temp_r1;
    u16 temp_r2;
    u32 temp_r5;
    u32 var_r4;
    u32 off;
    u32 base;

    var_sb = 0;
    var_r3 = 0;
    var_r4 = 0;
    do {
        if (gCounter6ED08_03001800.bD2[var_r4] != 0) {
            temp_r3 = var_r3 + 1;
            sp0 = temp_r3;
            var_r3 = temp_r3;
            temp_r5 = var_r4 + 0x21;
            base = (u32)gFrameObjects;
            off = 0x1740;
            temp_r2 = ((struct FrameObject *)((((gCounter6ED08_03001800.b60 + var_r4) << 8) + off) + base))->screenY;
            if (sub_0803526C(temp_r5, (s32) (s16) (temp_r2 - 4), (s32) (s16) (temp_r2 + 0x10)) != 0) {
                off = 0x1740;
                temp_r1 = &gFrameObjects[temp_r5];
                (*(u16 *)((u8 *)(temp_r1) + 0x30)) = ((struct FrameObject *)((((gCounter6ED08_03001800.b60 + var_r4) << 8) + off) + base))->screenX;
                (*(s16 *)((u8 *)(temp_r1) + 0x32)) = ((struct FrameObject *)((((gCounter6ED08_03001800.b60 + var_r4) << 8) + off) + base))->screenY - 4;
                temp_r1->unknown23[1] = 6;
                var_sb += 1;
            }
        }
        var_r4 += 1;
    } while (var_r4 <= 2U);
    if (var_sb == var_r3) {
        gState0TypedWork.widths.word86 = 0x3C;
        gCounter6ED08_03001800.bAA = (u8) (gCounter6ED08_03001800.bAA + 1);
    }
}

void sub_0802DB3C(void) {

    u32 var_r2;
    u32 off;

    var_r2 = 0;
    do {
        if (gCounter6ED08_03001800.bD2[var_r2] != 0) {
            if (4 & gState0TypedWork.widths.word86) {
                off = 0x1740;
                gFrameObjects[0x21 + var_r2].screenX = ((struct FrameObject *)((((gCounter6ED08_03001800.b60 + var_r2) << 8) + off) + (u32)gFrameObjects))->screenX - 2;
            } else {
                off = 0x1740;
                gFrameObjects[0x21 + var_r2].screenX = ((struct FrameObject *)((((gCounter6ED08_03001800.b60 + var_r2) << 8) + off) + (u32)gFrameObjects))->screenX + 2;
            }
        }
        var_r2 += 1;
    } while (var_r2 <= 2U);
    if (gState0TypedWork.widths.word86 == 0x3C) {
        sub_08040CD0(0x21U, 6U);
        gCounter6ED08_03001800.bAA = (u8) (gCounter6ED08_03001800.bAA + 1);
        return;
    }
    gState0TypedWork.widths.word86 += 1;
}

void sub_0802E098(void) {

    u32 var_r2;
    u32 off;

    var_r2 = 0;
    do {
        off = 0x1740;
        if (gCounter6ED08_03001800.bD2[var_r2] != 0) {
            gFrameObjects[0x21 + var_r2].flags = 0xC624;
            gFrameObjects[0x21 + var_r2].tableSelector = 0;
            gFrameObjects[0x21 + var_r2].screenX = ((struct FrameObject *)((((gCounter6ED08_03001800.b60 + var_r2) << 8) + off) + (u32)gFrameObjects))->screenX;
            gFrameObjects[0x21 + var_r2].screenY = ((struct FrameObject *)((((gCounter6ED08_03001800.b60 + var_r2) << 8) + off) + (u32)gFrameObjects))->screenY - 4;
            gFrameObjects[0x21 + var_r2].scaleX = 0x80;
            gFrameObjects[0x21 + var_r2].scaleY = 0x80;
            gFrameObjects[0x21 + var_r2].palette = 7;
            gFrameObjects[0x21 + var_r2].priority = 0xF0;
            gFrameObjects[0x21 + var_r2].frameAndGroup = 0x7F03;
        }
        var_r2 += 1;
    } while (var_r2 <= 2U);
    sub_08074DE0(0x54U);
    gCounter6ED08_03001800.bAA = (u8) (gCounter6ED08_03001800.bAA + 1);
}
