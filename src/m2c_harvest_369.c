/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "main_callbacks.h"
#include "rom_libc.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct RevealScriptWork {
    /* Observed prefix only; row is compared as signed after incrementing. */
    u8 before5[5];
    u8 selection;
    u8 before3A[0x34];
    u16 row;
    u8 before7D[0x41];
    s8 commandLength;
    u8 beforeAC[0x2E];
    u8 *const *cursor;
};

extern s32 sub_080672F4(u8 *command);
extern s32 sub_08067524(s32 selection, s32 row);
extern u8 *const *const gRevealCommandLists_080B0014[3];
extern void sub_08066D8C(void);

void sub_080678D4(void);

void sub_080678D4(void) {

    u8 *const *commandLists[3];
    u32 nextRow;
    struct RevealScriptWork *context;
    struct RevealScriptWork *completed;
    u32 screenblock;
    s32 row;

    memcpy(commandLists, gRevealCommandLists_080B0014, 12);
    sub_08066D8C();
    context = gMainContextPointer_03006F74;
    nextRow = context->row + 1;
    context->row = (u16)nextRow;
    if ((s16)nextRow > 13) {
        if (sub_08067524(context->selection, (s16)context->row - 14) != 0) {
            completed = gMainContextPointer_03006F74;
            completed->cursor = commandLists[completed->selection];
            completed->row = 0;
            gUnknown_0300137C++;
            ((struct RevealScriptWork *)gMainContextPointer_03006F74)->commandLength =
                (s8)sub_080672F4(*completed->cursor);
        }
    } else {
        screenblock = (*(volatile u16 *)0x04000008 >> 8) & 0x1F;
        row = (s16)context->row;
        *(volatile u16 *)(0x06000080U + ((screenblock << 11) + ((u32)row << 6))) =
            *(volatile u16 *)0x0600D8C0;
    }
}
