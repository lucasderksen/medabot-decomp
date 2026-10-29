/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "continued_commands.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "display_effects.h"
#include "display_helpers.h"
#include "effect_work.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern const void *const gUnknownPointers_083AC614[];
extern void sub_08067C04(void);

void sub_08024210(void);
void sub_08068298(void);

void sub_08024210(void) {
    u8 *frames = (u8 *)gFrameObjects;
    u8 *transfer;
    u8 *selected;
    u32 zero;
    u32 offset;
    u8 *source;
    frames[0x863] = (zero = 0);
    transfer = gState0TransferWork.bytes;
    selected = transfer + 0x88;
    offset = *selected << 8;
    source = frames + 0x1680;
    sub_0803F63C(offset + source, frames + 0x880, 0x40);
    offset = *selected << 8;
    source = frames + 0x16C0;
    sub_0803F63C(offset + source, frames + 0x8C0, 0x40);
    offset = *selected << 8;
    source = frames + 0x1700;
    sub_0803F63C(offset + source, frames + 0x900, 0x40);
    offset = *selected << 8;
    source = frames + 0x1740;
    sub_0803F63C(offset + source, frames + 0x940, 0x40);
    sub_08040D0C(0x22, 4);
    (frames + (*selected << 8))[0x16A3] = zero;
    (frames + (*selected << 8))[0x16E3] = zero;
    (frames + (*selected << 8))[0x1723] = zero;
    (frames + (*selected << 8))[0x1763] = zero;
    sub_08035694(*selected + 0x72);
    sub_08074DE0(0x34);
    transfer[0xAA] += 1;
}

void sub_08068298(void) {
    const void *const *scripts;
    const void *const *assets;
    struct InventoryRecord *records;
    u32 category;
    s16 temp_r1_2;
    s32 temp_r1_3;
    struct InventoryRecord *temp_r1_4;
    u16 temp_r1;

    sub_08067C04();
    scripts = gMain2ScriptSlots_0848521C;
    if ((sub_0803FB3C(scripts[17]) != 0) && (temp_r1 = (*(u16 *)((u8 *)(gMainContextPointer_03006F74) + 0x3A)), (*(u16 *)((u8 *)(gMainContextPointer_03006F74) + 0x3A)) = (u16) (temp_r1 + 1), temp_r1_2 = (s16) temp_r1, ((s32) temp_r1_2 > 0x77))) {
        temp_r1_3 = temp_r1_2 - 0x78;
        if (temp_r1_3 <= 0x80) {
            sub_0803F998(0x7FFFU, (u32) (temp_r1_3 >> 2), 1U);
            return;
        }
        records = gInventoryRecords;
        temp_r1_4 = &records[gQuantityResult_030017EC];
        category = temp_r1_4->byte1;
        assets = gUnknownPointers_083AC614;
        LeDecompress(assets[(category * 5) + temp_r1_4->unknown06[2]], (void *)0x06010000);
        (*(u16 *)((u8 *)(gMainContextPointer_03006F74) + 0x3A)) = 0U;
        gUnknown_0300137C += 1;
    }
}
