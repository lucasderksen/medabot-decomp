/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "main_menu_data.h"
#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "main.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "tile_text.h"

extern const MainCallback gMainState1Callbacks[];
extern const MainCallback gMainState3Callbacks[];
extern const MainCallback gUnknownCallbacks_083AC3C8[];
extern const MainCallback gUnknown_084858FC[];
extern const MainCallback gUnknown_084859BC[];
extern u32 gUnknown_0300137C;

void sub_08060688(void);
void sub_08060D6C(void);
void sub_08061958(void);
void sub_08064DB4(void);
void sub_0806B744(void);
void sub_0806E130(void);

void sub_08060688(void) {
    gUnknown_08483834[gUnknown_0300137C]();
}

void sub_08060D6C(void) {
    gUnknown_084838A4[gUnknown_0300137C]();
    if (gFrameCounter & 1)
    {
        gBgScroll3.x++;
        gBgScroll3.y++;
    }
}

void sub_08061958(void) {
    gUnknown_08483920[gUnknown_0300137C]();
    if (gFrameCounter & 1)
    {
        gBgScroll3.x++;
        gBgScroll3.y++;
    }
}

void sub_08064DB4(void) {
    gUnknown_08483948[gUnknown_0300137C]();
    if (gFrameCounter & 1)
    {
        gBgScroll3.x++;
        gBgScroll3.y++;
    }
}

void sub_0806B744(void) {
    gUnknown_084858FC[gUnknown_0300137C]();
}

void sub_0806E130(void) {
    gUnknown_084859BC[gUnknown_0300137C]();
}
