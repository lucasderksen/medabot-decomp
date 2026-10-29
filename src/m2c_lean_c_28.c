/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "bios_lz77.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "record_helpers.h"
#include "scene_view.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_inventory.h"
#include "state0_work.h"

struct ListContext64C6C {
    u8 pad00[0x30];
    u8 count30;
    u8 pad31[5];
    u16 tile36;
    u8 pad38[0x20];
    u8 name58[0x58];
    u8 list_b0[0x10];
};
struct InventoryView64C6C {
    u8 byte0;
    u8 byte1;
    u8 pad02[8];
    u8 name0A[0x36];
};

extern struct InventoryView64C6C gInventoryView64C6C[] asm("gInventoryRecords");
extern struct ListContext64C6C *gListContext64C6C asm("gMainContextPointer_03006F74");

void sub_08064C6C(u8 first);

void sub_08064C6C(u8 first) {

    s32 count;
    s32 i;
    s32 k;
    u16 tile;
    u16 *dst;

    if (gListContext64C6C->count30 > 3)
        count = 4;
    else
        count = gListContext64C6C->count30;
    for (i = 0; i < count; i++) {
        for (k = 0; k < 11; k++)
            gFrameObjects[12 + i * 10 + k].flags &= 0xBFFF;
        for (k = 0; k <= 10; k++) {
            gListContext64C6C->name58[k] = gInventoryView64C6C[gListContext64C6C->list_b0[i + first]].name0A[k];
            if (gListContext64C6C->name58[k] == 0xFE)
                break;
        }
        sub_08040DB8(gListContext64C6C->name58, (u8)(i * 10 + 12), 6, i * 2 + 3, 10, 13, 1, 1);
        tile = gListContext64C6C->tile36 + (gInventoryView64C6C[gListContext64C6C->list_b0[i + first]].byte1 * 4 + 1);
        tile |= 0x6000;
        dst = (u16 *)(((*(volatile u16 *)0x0400000A >> 8) & 0x1F) << 11) + (((i * 2 + 3) << 5) + 0x03000003);
        *dst = tile;
        dst++;
        *dst = tile + 1;
        dst += 31;
        *dst = tile + 2;
        dst[1] = tile + 3;
    }
}
