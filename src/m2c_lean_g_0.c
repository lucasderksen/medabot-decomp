/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "frame.h"
#include "frame_command_data.h"
#include "object_helpers.h"
#include "pose_channels.h"
#include "state0_inventory.h"
#include "state0_work.h"
#include "tile_text.h"


u32 sub_0804361C(volatile u32 index, volatile u32 backward);
u32 sub_080436AC(volatile u32 column, volatile u32 row, volatile u32 backward, volatile u32 side);

u32 sub_0804361C(volatile u32 index, volatile u32 backward) {
    /* volatile parameters reproduce the reference's store-then-reload of every parameter use. */

    if (backward != 0) {
        if (index != 0) {
            struct InventoryRecord *records = gInventoryRecords;

        previous:
            index--;
            if ((0x80 & records[index].byte0) && !(0x40 & gInventoryRecords[index].byte0))
                return index;
            if (index != 0)
                goto previous;
        }
    } else {
        for (;;) {
            index++;
            if (index == 0x1F)
                index = 0;
            if (index == 0x1E)
                goto none;
            if (!(0x80 & gInventoryRecords[index].byte0) || (0x40 & gInventoryRecords[index].byte0))
                continue;
            return index;
        }
    }
none:
    return 0x1E;
}

u32 sub_080436AC(volatile u32 column, volatile u32 row, volatile u32 backward, volatile u32 side) {
    /* volatile parameters reproduce the reference's store-then-reload of every parameter use. */

    if (backward != 0) {
        while (column != 0) {
            column--;
            if (column == 0x78)
                column--;
            sub_08042B58(column, row, &gState0TypedWork.bytes[0x10E]);
            if (side == gState0TypedWork.bytes[0x111]
                && gObjectHalfwordBytes[row * 0xF0 + column * 2] != 0
                && (s32)gObjectHalfwordBytes[row * 0xF0 + column * 2] - gObjectHalfwordBytes[row * 0xF0 + column * 2 + 1] != 0)
                goto found;
        }
        goto none;
    } else {
        for (;;) {
            column++;
            if (side != 0 && column == 0x78)
                column = 0x79;
            if (column == side + 0x79)
                column = 0;
            if (column == side + 0x78)
                goto none;
            sub_08042B58(column, row, &gState0TypedWork.bytes[0x10E]);
            if (side == gState0TypedWork.bytes[0x111]
                && gObjectHalfwordBytes[row * 0xF0 + column * 2] != 0
                && (s32)gObjectHalfwordBytes[row * 0xF0 + column * 2] - gObjectHalfwordBytes[row * 0xF0 + column * 2 + 1] != 0)
                return column;
        }
    }
found:
    return column;
none:
    return side + 0x78;
}
