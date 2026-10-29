/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "main_menu_data.h"
#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "link_menu.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "tile_text.h"

struct CreditsContext67974 {
    u8 pad00[5];
    u8 index05;
    u8 pad06[0x34];
    s16 timer3A;
    u8 pad3C[0x41];
    u8 width7D;
    u8 pad7E[0x2E];
    u8 **listAC;
};

extern struct CreditsContext67974 *gCreditsContext67974 asm("gMainContextPointer_03006F74");
extern void sub_08067314(s8 width, s32 column);
extern void sub_080673AC(s32 row, s32 column);

void sub_08067974(void);

void sub_08067974(void) {

    struct CreditsContext67974 *ctx;
    s32 limit;
    s32 low;
    s8 row;

    sub_08066D8C();
    {
        const u8 *table = gUnknown_08483C10;
        ctx = gCreditsContext67974;
        limit = *(const u8 *)((u32)table + ctx->index05);
    }
    low = (u16)ctx->timer3A;
    row = 0x1F;
    low &= row;
    if (low == 0) {
        if (limit > ctx->timer3A / 32) {
            {
                u8 *str = *ctx->listAC;
                row = ctx->timer3A / 32 + 0x10;
                row &= 0x1F;
                sub_080674BC(str, row);
            }
            if (limit == gCreditsContext67974->timer3A / 32)
                gCreditsContext67974->width7D = low;
            else
                gCreditsContext67974->width7D = sub_080672F4(*gCreditsContext67974->listAC);
            gCreditsContext67974->listAC++;
        } else {
            gUnknown_0300137C++;
            ctx->timer3A = -1;
        }
    }
    sub_08067314(gCreditsContext67974->width7D, 0x1F & gCreditsContext67974->timer3A);
    sub_080673AC((gCreditsContext67974->timer3A / 32 + 5) & 0x1F, (gCreditsContext67974->timer3A + 2) & 0x1F);
    if (!(3 & gCreditsContext67974->timer3A))
        gBgScroll1.y++;
    gCreditsContext67974->timer3A++;
}
