/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Part12234 { u8 unknown00[0x17]; u8 byte17; };
struct Setup12234 { u8 unknown00[0x48]; struct Part12234 parts[4]; u8 unknownA8[0x12]; u8 activeBA; u8 unknownBB[0x45]; };
struct Work12234 { u8 pad[0x168]; u8 slot168; u8 part169; };

extern const u8 gUnknown_083AD070[];
extern struct Setup12234 gSetup12234[] asm("gSetupBuffer_03000590");
extern struct Work12234 gWork12234 asm("gCounter6ED08_03001800");

u32 sub_08012234(void);

u32 sub_08012234(void) {

    u32 tries;
    u32 record;
    u32 slot;
    u32 j;

    record = gUnknown_083AD070[sub_080424B8() & 0xF];
    for (tries = 0; tries < 3; tries++) {
        if (gSetup12234[record + 3].activeBA != 0) {
            slot = sub_080424B8() & 3;
            for (j = 0; j < 4; j++) {
                if (sub_08042114(gSetup12234[record + 3].parts[slot].byte17, slot) == 0) {
                    gWork12234.slot168 = slot;
                    gWork12234.part169 = gSetup12234[record + 3].parts[slot].byte17;
                    return 1;
                }
                slot = (slot + 1) & 3;
            }
        }
        if (record == 2)
            record = 0;
        else
            record++;
    }
    return 0;
}
