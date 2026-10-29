/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "effect_work.h"
#include "input.h"
#include "main_callbacks.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

s32 sub_08062B48(u8, u8, s32);

void sub_08063840(void);

void sub_08063840(void) {
    sub_08062B48((*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x31)), (*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x33)), 0);
    sub_08062B48((*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x32)), (*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x34)), 1);
    if ((sub_0803FB3C(gMain2ScriptSlots_08485678[(*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x33)) + 0x14]) != 0) && (1 & *(u8 *) &gNewKeys)) {
        gMainSerialOutgoingWork.word06 = 0xFF07;
        sub_08074DE0(0xDU);
    }
    if ((gMainSerialOutgoingWork.words[0][1] == 0xFF07) || (gMainSerialOutgoingWork.words[1][1] == 0xFF07)) {
        sub_080656DC(gMainContextPointer_03006F74 + 0x50, 0U, 0U, 1U, 0xC0U);
        gUnknown_0300137C += 1;
    }
}
