/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "link_menu.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"


void sub_080421B4(u32 identifier, u32 selector);

void sub_080421B4(u32 identifier, u32 selector) {

    u8 id = identifier;
    u8 sel = selector;
    u32 i;
    u8 cell;

    for (i = 0; i <= 8; i++) {
        if (gUnknownRecords_030017A0[i].byte7 == id) {
            u8 *slot = &gUnknownRecords_030017A0[i].byte3;
            cell = slot[sel];
            slot[sel] = gUnknownRecords_030017A0[i].unknown00[1] + 0x78;
            gUnknownRecords_030017A0[i].unknown00[0] = 2;
            gObjectHalfwordBytes[cell * 2 + sel * 0xF0]--;
            gObjectHalfwordBytes[cell * 2 + sel * 0xF0 + 1]--;
            return;
        }
    }
}
