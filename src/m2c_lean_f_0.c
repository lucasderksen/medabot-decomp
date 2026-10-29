/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "display_helpers.h"
#include "encounter_parts.h"
#include "object_helpers.h"
#include "sound_work.h"

extern u8 gObjectCountBytes[] asm("gObjectCountPairs");

void sub_08042318(u8 kind, u8 amount);

void sub_08042318(u8 kind, u8 amount) {

    u32 i, next;
    s32 left;

    kind &= 0x3F;
    for (i = 0; i <= 0x3F; i++) {
        if ((0x80 & gObjectCountBytes[i * 2]) && (0x7F & gObjectCountBytes[i * 2]) == kind) {
            left = gObjectCountBytes[i * 2 + 1] - amount;
            if (left <= 0) {
                gObjectCountBytes[i * 2] = 0;
                gObjectCountBytes[i * 2 + 1] = 0;
                next = i + 1;
                if (gObjectCountBytes[next * 2] != 0) {
                    do {
                        sub_0803F65C(&gObjectCountBytes[i * 2], &gObjectCountBytes[next * 2], 2);
                        i = next;
                        next = i + 1;
                    } while (gObjectCountBytes[next * 2] != 0);
                }
            } else {
                gObjectCountBytes[i * 2 + 1] = left;
                return;
            }
        }
    }
}
