/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "battle_work.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "input.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_inventory.h"
#include "state0_inventory_rows.h"
#include "state0_work.h"


u32 sub_0800AE54(void);
void sub_08024C94(void);
void sub_080271C4(void);

u32 sub_0800AE54(void) {

    u8 left;

    left = 0x20 & (u8)gRepeatedKeys;
    if (left) {
        sub_08074DE0(2);
        if (gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[3] == 0) {
            gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[3] = 7;
        } else {
            gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[3]--;
        }
        return 1;
    }
    if (0x10 & (u8)gRepeatedKeys) {
        sub_08074DE0(2);
        if (gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[3] == 7) {
            gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[3] = 0;
        } else {
            gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[3]++;
        }
        return 1;
    }
    return 0;
}

void sub_08024C94(void) {

    if (gState0TypedWork.widths.word86 == 0x3C) {
        sub_08040CD0(0x21, 2);
        gCounter6ED08_03001800.counterAA++;
        return;
    }
    gState0TypedWork.widths.word86++;
    if (gState0TypedWork.widths.word86 & 4) {
        gFrameObjects[0x21].screenX = gFrameObjects[0x5D + gCounter6ED08_03001800.value88 * 4].screenX - 2;
    } else {
        gFrameObjects[0x21].screenX = gFrameObjects[0x5D + gCounter6ED08_03001800.value88 * 4].screenX + 2;
    }
}

void sub_080271C4(void) {

    if (gFrameObjects[0x21].scaleX != 0x40) {
        gFrameObjects[0x21].scaleX -= 8;
        gFrameObjects[0x21].scaleY -= 8;
        if (gFrameObjects[0x21].scaleX == 0x40) {
            sub_08074DE0(0x30);
        }
        return;
    }
    gFrameObjects[0x22].flags |= 0x8000;
    if (gFrameObjects[0x22].scaleX != 0x40) {
        gFrameObjects[0x22].scaleX -= 8;
        gFrameObjects[0x22].scaleY -= 8;
        if (gFrameObjects[0x22].scaleX == 0x40) {
            sub_08074DE0(0x30);
        }
        return;
    }
    gState0TypedWork.widths.word86 = 0x3C;
    gCounter6ED08_03001800.counterAA++;
}
