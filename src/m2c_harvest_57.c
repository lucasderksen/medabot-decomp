/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "eeprom.h"
#include "frame.h"
#include "graphics.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_next_helpers.h"
#include "tile_text.h"

struct FrameInitBacking {
    u8 padding[0x80];
    u16 flags;
    s16 x;
    s16 y;
    u16 frame;
    u8 scales[2];
    u8 palette;
    u8 priority;
    u8 gap[0x10];
    u8 table;
};


void sub_08016804(u32 value);

void sub_08016804(u32 value) {
    struct FrameInitBacking *objects = (void *) gFrameObjects;
    s16 *coordinate;
    u8 *parameter;
    objects->flags = 0xC404;
    objects->table = 0;
    coordinate = &objects->x;
    *coordinate = 0x6C;
    coordinate++;
    *coordinate = 0x78;
    parameter = (u8 *) coordinate + 6;
    *parameter = 0xA;
    parameter++;
    *parameter = 0xC0;
    objects->frame = value * 4 + 0x605;
}
