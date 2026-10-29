/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "bios_lz77.h"
#include "continued_scene_records.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_work.h"
#include "tile_text.h"


void sub_0805BD44(u32 firstArg);

void sub_0805BD44(u32 firstArg) {

    u8 first = firstArg;
    s32 i;
    s32 k;
    u16 *p;

    for (i = 0; i <= 2; i++) {
        p = (u16 *)(((*(volatile u16 *)0x04000008 >> 8) & 0x1F) * 0x800 + 0x0600028E + i * 0xC0);
        for (k = 0; k < 11; k++) {
            s32 v; s32 x;
            v = *p; v &= 0xFFF;
            if (i == first) x = v | 0x7000; else { v |= 0x6000; x = (u16)v; }
            do { *p = x; } while (0); p++;
        }
    }
}
