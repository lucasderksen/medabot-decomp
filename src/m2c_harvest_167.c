/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "record_helpers.h"

struct Audio73404Channel { u8 pad00[0x38]; s32 adjustment; u8 pad3C[0xA]; u16 base; u8 pad48[8]; u8 flags; u8 pad51[4]; u8 fine; };


void sub_08073404(void *arg0, volatile u16 *arg1);

void sub_08073404(void *arg0, volatile u16 *arg1) {
    s16 temp_r0;
    u8 *flags;
    u32 clearedFlags;
    s32 var_r3;
    u16 temp_r1_2;
    u16 var_r2;
    u8 temp_r1;

    var_r3 = 0;
    flags = &((struct Audio73404Channel *)arg0)->flags;
    temp_r1 = *flags;
    if (0x10 & temp_r1) {
        var_r3 = 0x8000;
        clearedFlags = 0xEF;
        clearedFlags &= temp_r1;
        *flags = clearedFlags;
    }
    if (1 & *flags) {
        temp_r1_2 = ((struct Audio73404Channel *)arg0)->base + ((struct Audio73404Channel *)arg0)->fine + ((s32) ((struct Audio73404Channel *)arg0)->adjustment >> 4);
        var_r2 = temp_r1_2;
        temp_r0 = (s16) temp_r1_2;
        if ((s32) temp_r0 < 0) {
            var_r2 = 0;
        } else if ((s32) temp_r0 > 0x7FF) {
            var_r2 = 0x7FF;
        }
        *arg1 = var_r3 | var_r2;
        *flags = (u8) (0xFE & *flags);
        return;
    }
    if (var_r3 != 0) {
        *arg1 = var_r3 | ((struct Audio73404Channel *)arg0)->base;
    }
}
