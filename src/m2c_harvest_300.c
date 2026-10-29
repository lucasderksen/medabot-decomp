/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_work.h"

extern s32 gCounter6ED08_03001800;

void sub_08023328(void);

void sub_08023328(void) {

    struct FrameObject *var_r2;
    u32 var_r3;
    u8 *base;
    struct FrameObject *objs;

    if (gState0TypedWork.widths.word86 == 0x14) {
        gState0TypedWork.widths.word86 = 0x3C;
        base = (u8 *)&gCounter6ED08_03001800;
        base[0xAA] = base[0xAA] + 1;
        return;
    }
    gState0TypedWork.widths.word86 += 1;
    var_r3 = 0;
    objs = gFrameObjects;
    do {
        var_r2 = &objs[0x21 + var_r3];
        if (0x8000 & var_r2->flags) {
            var_r2->screenY = (u16) var_r2->screenY - 1;
        }
        var_r3 += 1;
    } while (var_r3 <= 2U);
}
