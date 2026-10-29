/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "continued_late_graphics.h"
#include "frame_objects.h"
#include "gba.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct ListContext64E18 {
    u8 pad00[0x30];
    u8 count30;
    u8 pad31[0x7F];
    u8 list_b0[0x20];
};

extern struct ListContext64E18 *gListContext64E18 asm("gMainContextPointer_03006F74");
extern u8 gUnknown_03000584;

void sub_08064E18(void);

void sub_08064E18(void) {

    u32 zero;
    s32 count;
    s32 i;

    zero = 0;
    CpuFastSet(&zero, (void *)0x06000000, 0x01006000);
    sub_08040CD0(0, 0x80);
    *(volatile u16 *)0x05000000 = 0;
    count = 0;
    for (i = 0; i <= 0x1D; i++) {
        if (0x80 & gInventoryRecords[i].byte0) {
            gListContext64E18->list_b0[count] = i;
            count++;
        }
    }
    gListContext64E18->count30 = count;
    if (gUnknown_03000584 != 2) {
        gMainSubstate = 6;
        gUnknown_0300137C = 0;
    } else {
        sub_080415BC();
        *(volatile u16 *)0x04000000 = 0x60;
        gUnknown_0300137C++;
    }
}
