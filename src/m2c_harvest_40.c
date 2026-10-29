/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"

extern s32 sub_08072414(void *);
extern s32 sub_0807244C(void *);

void sub_08066574(void);
s32 sub_080724B0(void *arg0);

void sub_08066574(void) {
    s32 i;
    gUnknown_0300137C = 0;
    if ((*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x4A)) == 0) {
        i = 0;
        while (i <= 3 && sub_0805DDEC(0) != 0)
            i++;
    }
    sub_0805DD88();
}

s32 sub_080724B0(void *arg0) {
    if ((u32) (*(u8 *)((u8 *)(arg0) + 0x5D)) >= (u32) (*(u32 *)((u8 *)(arg0) + 0x28))) {
        sub_08072414(arg0);
        sub_0807244C(arg0);
        return 1;
    }
    return 0;
}
