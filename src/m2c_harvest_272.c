/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "main_callbacks.h"
#include "post_dispatch.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "tile_text.h"

struct FamilyCallbacks {void (*items[7])(void);};

extern const struct FamilyCallbacks gUnknown_080B0020;
extern const struct FamilyCallbacks gUnknown_080B003C;
extern void sub_08060248(void);

void sub_0805FE84(void);
void sub_080604C4(void);
void sub_08067B9C(void);
void sub_08068400(void);

void sub_0805FE84(void) {

    *(volatile u16 *)0x04000000 |= 0x800;
    *(volatile u16 *)0x04000000 |= 0x1000;
    *(u8 *)gMainContextPointer_03006F74 = 0x20U;
    *(volatile u16 *)0x04000054 = (s16) ((u8) *(u8 *)gMainContextPointer_03006F74 >> 1);
    gUnknown_0300137C += 1;
}

void sub_080604C4(void) {

    u8 temp_r0;

    sub_08060248();
    temp_r0 = *(u8 *)gMainContextPointer_03006F74;
    if (temp_r0 != 0x20) {
        *(u8 *)gMainContextPointer_03006F74 = (u8) (temp_r0 + 1);
        *(volatile u16 *)0x04000054 = (s16) ((u8) *(u8 *)gMainContextPointer_03006F74 >> 1);
        return;
    }
    *(volatile u16 *)0x04000000 &= 0xFDFF;
    gUnknown_0300137C += 1;
}

void sub_08067B9C(void) {

 struct FamilyCallbacks callbacks=gUnknown_080B0020;
 callbacks.items[gUnknown_0300137C]();
 gBgScroll2.y -= 1;
}

void sub_08068400(void) {

 struct FamilyCallbacks callbacks=gUnknown_080B003C;
 callbacks.items[gUnknown_0300137C]();
 gBgScroll2.y += 1;
}
