/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"

struct ContinueBonusRow {u8 pad[0xA4];u8 bonus;u8 pad2[0x17];u8 flags;u8 tail[0x43];};
struct ContinueAmountWork {u8 pad[0x87];u8 bank;u8 target;u8 pad2[0x5F];s16 remaining;u8 pad3[4];s16 amount;u8 pad4[2];u16 saved;};

extern s32 sub_08039134(s32);
extern s32 sub_08039158(s32);
extern struct ContinueAmountWork gUnknown_03001800;
extern struct ContinueBonusRow gUnknown_03000590[];
extern u32 sub_08038E9C(void);
extern void sub_08035844(u32);
extern void sub_08035944(s32, s32);

void sub_08039068(void);

void sub_08039068(void) {
    s32 var_r1;
    struct ContinueBonusRow *temp_r1;

    gUnknown_03001800.amount = 0U;
    gUnknown_03001800.saved = (u16) gUnknown_03001800.remaining;
    if (!(8 & gUnknown_03000590[gUnknown_03001800.target].flags)) {
        sub_08035844(gUnknown_03001800.target);
        gUnknown_03001800.amount = (u16) (gUnknown_03001800.amount + gUnknown_03000590[gUnknown_03001800.target].bonus);
        if (!(4 & gUnknown_03000590[gUnknown_03001800.target].flags)) {
            sub_08035754(&gUnknown_03001800.amount, 8);
        }
        if ((sub_08038E9C() == 0) && ((s32) (s16) gUnknown_03001800.amount > 0x1F)) {
            sub_08035754(&gUnknown_03001800.remaining, (s32) (s16) gUnknown_03001800.amount);
            gUnknown_03001800.saved = (u16) gUnknown_03001800.remaining;
            temp_r1=&gUnknown_03000590[gUnknown_03001800.target];
            temp_r1->flags = (u8) (0x20 | temp_r1->flags);
            if (sub_08039134(gUnknown_03001800.target) == 1) {
                var_r1 = 1;
            } else {
                var_r1 = sub_08039158(gUnknown_03001800.target);
            }
            sub_08035944(gUnknown_03001800.bank, var_r1);
        }
    }
}
