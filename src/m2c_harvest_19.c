/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "display_helpers.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "interrupts.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"
#include "utility_helpers.h"

extern s8 gUnknown_03006F90;
extern u8 gUnknown_03006F84;

void sub_0803D6AC(void);
void sub_0803E870(void);
void sub_0804AF94(void);
void sub_08069490(void);

void sub_0803D6AC(void) {
    gState0TypedWork.bytes[0x84] = 0;
    gState0TransferWork.bytes[0x51] = 0;
    gState0TransferWork.bytes[0x52] = 0;
    gState0TransferWork.bytes[0x53] = 0;
    (*(s8 *)((u8 *)((&gState0TransferWork.bytes[0x52] + 1)) + 1)) = 0;
    gState0TransferWork.widths.words1A6[0] = 0;
    gState0TransferWork.widths.words1A6[1] = 0;
    gState0TransferWork.widths.words1A6[2] = 0;
    gState0TransferWork.widths.words1A6[3] = 0;
    gState0TransferWork.bytes[0x1AF] = 0;
    gState0TransferWork.bytes[0x1B0] = 1;
    gState0TypedWork.widths.word86 = 0;
    gUnknown_0300137C = 0x50;
}

void sub_0803E870(void) {
    sub_0803F63C(gState0ScrollControls_083C3C84[gState0TransferWork.bytes[0x38]], &gState0TransferWork.bytes[0x39], 8U);
}

void sub_0804AF94(void) {

}

void sub_08069490(void) {
    gUnknown_03006F90 = 1;
    (*(s16 *)((u8 *)((void *)0x0400000C) + 0)) = 0x1E0A;
    (*(s16 *)((u8 *)((void *)0x0400000C) + 2)) = 0x1F0B;
    gState0TransferWork.bytes[0x38] = gUnknown_03006F84;
    sub_08043B7C((u32) gState0TransferWork.bytes[0x38], 0U);
    sub_0803F63C(gState0ScrollControls_083C3C84[gState0TransferWork.bytes[0x38]], &gState0TransferWork.bytes[0x39], 8U);
    sub_08043DF8();
    sub_080441A8(gEquipmentAssets_083B2578[(gState0TransferWork.bytes[0x38] * 5) + 1]);
    gBgScroll2.x = 0;
    gBgScroll2.y = 0;
    gBgScroll3.x = 0;
    gBgScroll3.y = 0;
    gUnknownCallback_030017F0 = sub_08043E48 + 1;
}
