/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "continued_late_graphics.h"
#include "display_effects.h"
#include "effect_work.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct SwapContext63254 {
    u8 pad00[0x31];
    u8 firstA;
    u8 slot32;
    u8 firstB;
    u8 slot34;
};

extern struct SwapContext63254 *gSwapContext63254 asm("gMainContextPointer_03006F74");
extern u8 gUnknown_030004F2[];
extern void sub_08062A10(s32);
extern void sub_08062B48(u8, u8, s32);
extern void sub_08062BEC(s32, s32);

void sub_08063254(void);

void sub_08063254(void) {

    u16 w0;
    u16 w1;
    u16 mask;

    sub_0803FB3C(gMain2ScriptSlots_08485678[15]);
    gMainSerialOutgoingWork.word06 = gSwapContext63254->firstA | (gSwapContext63254->firstB << 8) | 0x4000;
    w0 = gMainSerialOutgoingWork.words[0][1];
    w1 = gMainSerialOutgoingWork.words[1][1];
    mask = w0 & 0xC000;
    if (mask == 0x4000 && (w1 & 0xC000) == mask) {
        if (gUnknown_03000B90 != 0) {
            gSwapContext63254->slot32 = w0 & 0x7F;
            gSwapContext63254->slot34 = (w0 >> 8) & 3;
        } else {
            gSwapContext63254->slot32 = w1 & 0x7F;
            gSwapContext63254->slot34 = (w1 >> 8) & 3;
        }
        sub_08062A10(1);
        sub_08062BEC(gSwapContext63254->slot32 * 4 + gSwapContext63254->slot34, 1);
        sub_08041020(gUnknown_030004F2, 0x10, 0xE, 0xA, 0x10, 0xD, 0, 1);
        sub_0803FAA0(1, 0, 1);
        gUnknown_0300137C++;
    }
    sub_08062B48(gSwapContext63254->firstA, gSwapContext63254->firstB, 0);
}
