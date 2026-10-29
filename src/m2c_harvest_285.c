/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "later_graphics.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct FamilyWork49558 {u16 x,y,angle;};
struct FamilyKeys49558 {u8 low,high;};
struct FamilyBackground49558 {u8 pad0[0x18];u16 toggle,selection;};

extern struct FamilyBackground49558 gUnknown_03005310;
extern struct FamilyKeys49558 gFamilyKeyBytes49558_0300058C;
extern struct FamilyWork49558 gLaterBuffer_03006D40;
extern u8 gContinuedByte_03002B64;
extern void sub_08049318(void);

s32 sub_08049558(void);

s32 sub_08049558(void) {

    s32 temp_r0_4;
    s32 temp_r0_5;
    s32 temp_r0_6;
    s32 temp_r0_7;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;

    if (1 & gFamilyKeyBytes49558_0300058C.low) {
        gUnknown_03005310.toggle = (u16) (gUnknown_03005310.toggle ^ 1);
    }
    if (4 & gContinuedByte_03002B64) {
        if (0x40 & gContinuedByte_03002B64) {
            temp_r0 = gLaterBuffer_03006D40.y + 0x10;
            gLaterBuffer_03006D40.y = temp_r0;
            if ((s32) (s16) temp_r0 > 0x400) {
                gLaterBuffer_03006D40.y = 0x400U;
            }
        }
        if (0x80 & gContinuedByte_03002B64) {
            temp_r0_2 = gLaterBuffer_03006D40.y - 8;
            gLaterBuffer_03006D40.y = temp_r0_2;
            if ((s32) (s16) temp_r0_2 <= 0x3F) {
                gLaterBuffer_03006D40.y = 0x40U;
            }
        }
        if (0x20 & gContinuedByte_03002B64) {
            gLaterBuffer_03006D40.x = (u16) (gLaterBuffer_03006D40.x - 8);
        }
        if (0x10 & gContinuedByte_03002B64) {
            temp_r0_3 = gLaterBuffer_03006D40.x + 0x10;
            gLaterBuffer_03006D40.x = temp_r0_3;
            if ((s32) (s16) temp_r0_3 > 0x400) {
                gLaterBuffer_03006D40.x = 0x400U;
            }
            gLaterBuffer_03006D40.angle = (gLaterBuffer_03006D40.angle + 1) & 0xFFu;
        }
        if (0x20 & gContinuedByte_03002B64) {
            gLaterBuffer_03006D40.angle = (gLaterBuffer_03006D40.angle + 0xFF) & 0xFFu;
        }
    } else {
        if (0x40 & gContinuedByte_03002B64) {
            temp_r0_4 = (u16) gFrameObjects->screenY - 2;
            gFrameObjects->screenY = temp_r0_4;
            if ((s32)(s16) temp_r0_4 < -0x50) {
                gFrameObjects->screenY = -0x50;
            }
        }
        if (0x80 & gContinuedByte_03002B64) {
            temp_r0_5 = (u16) gFrameObjects->screenY + 2;
            gFrameObjects->screenY = temp_r0_5;
            if ((s32)(s16) temp_r0_5 > 0x50) {
                gFrameObjects->screenY = 0x50;
            }
        }
        if (0x10 & gContinuedByte_03002B64) {
            temp_r0_6 = (u16) gFrameObjects->screenX + 2;
            gFrameObjects->screenX = temp_r0_6;
            if ((s32)(s16) temp_r0_6 > 0x78) {
                gFrameObjects->screenX = 0x78;
            }
        }
        if (0x20 & gContinuedByte_03002B64) {
            temp_r0_7 = (u16) gFrameObjects->screenX - 2;
            gFrameObjects->screenX = temp_r0_7;
            if ((s32)(s16) temp_r0_7 < -0x78) {
                gFrameObjects->screenX = -0x78;
            }
        }
        if ((1 & gFamilyKeyBytes49558_0300058C.high) && ((u32) gUnknown_03005310.selection <= 0xEU)) {
            gUnknown_03005310.selection = (u16) (gUnknown_03005310.selection + 1);
        }
        if ((2 & gFamilyKeyBytes49558_0300058C.high) && (gUnknown_03005310.selection != 0)) {
            gUnknown_03005310.selection = (u16) (gUnknown_03005310.selection - 1);
        }
    }
    if (8 & gFamilyKeyBytes49558_0300058C.low) {
        sub_08049318();
    }
    return 0;
}
