/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "continued_late_graphics.h"
#include "effect_work.h"
#include "frame.h"
#include "input.h"
#include "main.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct MenuContext66280 {
    u8 pad00[5];
    u8 cursor05;
    u8 pad06[0x74];
    s8 flag7A;
    s8 flag7B;
    s8 flag7C;
};

extern const u8 gUnknown_080AFCA8[];
extern const u8 gUnknown_080AFCB7[];
extern struct MenuContext66280 *gMenuContext66280 asm("gMainContextPointer_03006F74");

void sub_08066280(void);

void sub_08066280(void) {

    if ((0xFF00 & gMainSerialOutgoingWork.words[gUnknown_03000B90 == 0][1]) == 0xEF00) {
        gMenuContext66280->cursor05 = gMainSerialOutgoingWork.words[gUnknown_03000B90 == 0][1];
        gMenuContext66280->flag7A = 1;
        gUnknown_0300137C++;
        sub_08074DE0(4);
        gFrameObjects[0].screenY = gMenuContext66280->cursor05 * 16 + 0x1C;
        return;
    }
    sub_08041C14(0, gFrameCounter, 0xC);
    if (gMenuContext66280->cursor05 == 6)
        sub_0803FB3C(gUnknown_080AFCA8);
    else {
        u32 slots = (u32)gMain2ScriptSlots_08485678;
        u32 base = (u32)gUnknown_080AFCB7;
        u32 offset = gMenuContext66280->cursor05;
        u32 index = *(const u8 *)(base + offset);
        sub_0803FB3C(*(const void *const *)(slots + (index << 2)));
    }
    if (gMenuContext66280->cursor05 > 4) {
        if (0xC1 & (u8)gRepeatedKeys) {
            gMenuContext66280->cursor05 = gMenuContext66280->cursor05 == 5 ? 1 : 4;
            sub_0803FB0C();
        }
        return;
    }
    if (0x40 & (u8)gRepeatedKeys) {
        gMenuContext66280->cursor05 = gMenuContext66280->cursor05 != 0 ? gMenuContext66280->cursor05 - 1 : 4;
        sub_0803FB0C();
        sub_08074DE0(2);
    }
    if (0x80 & (u8)gRepeatedKeys) {
        gMenuContext66280->cursor05 = gMenuContext66280->cursor05 < 4 ? gMenuContext66280->cursor05 + 1 : 0;
        sub_0803FB0C();
        sub_08074DE0(2);
    }
    gFrameObjects[0].screenY = gMenuContext66280->cursor05 * 16 + 0x1C;
    if (1 & (u8)gRepeatedKeys) {
        if (gMenuContext66280->cursor05 == 1 && gMenuContext66280->flag7B == 0) {
            gMenuContext66280->cursor05 = 5;
            sub_0803FB0C();
            sub_08074DE0(6);
            return;
        }
        if (gMenuContext66280->cursor05 == 2 && gMenuContext66280->flag7C == 0) {
            sub_08074DE0(6);
            return;
        }
        gMenuContext66280->flag7A = 0;
        gMainSerialOutgoingWork.word06 = gMenuContext66280->cursor05 | 0xEF00;
        gUnknown_0300137C++;
        sub_08074DE0(4);
    }
}
