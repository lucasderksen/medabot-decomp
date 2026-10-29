/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"

extern u8 *gUnknown_083B6190;

u32 sub_080370AC(u32 index, u32 count);

u32 sub_080370AC(u32 index, u32 count) {

    struct FrameObject *temp_r4;
    u32 temp_r2;
    u32 var_r6;
    u32 var_r8;
    u8 temp_r0;
    u32 temp_r3;
    u8 **tab;
    struct FrameObject *objs;

    var_r8 = 1;
    for (var_r6 = 0; var_r6 < count; var_r6++) {
        tab = &gUnknown_083B6190;
        objs = gFrameObjects;
        temp_r3 = index + var_r6;
        temp_r4 = &objs[temp_r3];
        temp_r2 = temp_r4->flags;
        if (temp_r2 != 0) {
            temp_r0 = temp_r4->unknown2C[0];
            if (temp_r0 != 0) {
                temp_r4->unknown2C[0] = temp_r0 - 1;
                var_r8 = 0;
            } else {
                temp_r4->flags = 0x8000 | temp_r2;
                sub_08040BD8(*tab, temp_r3);
                if (temp_r4->commandStopped == 0xFF) {
                    sub_08040CD0(temp_r3, 1U);
                } else {
                    var_r8 = 0;
                }
            }
        }
    }
    return var_r8;
}
