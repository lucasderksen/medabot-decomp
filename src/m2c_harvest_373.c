/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_inventory.h"
#include "state0_inventory_rows.h"
#include "tile_text.h"

extern u8 gUnknown_0300047D;

void sub_0800AB0C(void);

void sub_0800AB0C(void) {

    u32 column;
    u32 x;

    column = 0;
    do {
        x = 6 + column * 2;
        if (column < (u32) gInventoryRecords[gUnknown_0300047D].unknown06[3]) {
            sub_08042698(2U, 2U, x, 7U, (u32) *(volatile u16 *)0x0400000A, (u32) ((((u8 *)&gInventoryRecords + 24)[column + ((u32) gUnknown_0300047D << 6)] << 0x12) + 0xB3400000) >> 0x10);
        } else {
            sub_08042698(2U, 2U, x, 7U, (u32) *(volatile u16 *)0x0400000A, (u32) ((((u8 *)&gInventoryRecords + 24)[column + ((u32) gUnknown_0300047D << 6)] << 0x12) + 0xA3400000) >> 0x10);
        }
        column += 1;
    } while (column <= 7U);
}
