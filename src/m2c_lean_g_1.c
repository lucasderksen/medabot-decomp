/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sprite_layouts.h"
#include "state0_display.h"
#include "state0_work.h"
#include "tile_text.h"

extern u8 gScratch6030C02030000[];

void sub_0804545C(const void *source, const u32 *header, u16 tile, u32 useCpu);

void sub_0804545C(const void *source, const u32 *header, u16 tile, u32 useCpu) {

    u16 dims[2];
    u32 value;

    value = sub_08044E64(((*header << 26) >> 30) << 14, ((*header << 24) >> 30) << 30);
    dims[0] = value >> 16;
    dims[1] = value;
    value = dims[0] * dims[1];
    if (!(0xF & *(const u8 *)header))
        value >>= 1;
    {
        u32 descriptor = *header;
        u32 t;
        u32 x;

        t = (descriptor << 20) >> 28;
        x = value * t;
        t = (descriptor << 16) >> 28;
        value = x * (u16)t;
        x = descriptor << 26;
        x >>= 30;
        t = descriptor;
        sub_08045084(source, x << 14, ((t << 24) >> 30) << 30, (t << 20) >> 28, (t << 16) >> 28,
                     (descriptor << 28) >> 28, tile, value, gScratch6030C02030000, useCpu);
    }
}
