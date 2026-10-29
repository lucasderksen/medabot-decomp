/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_late_graphics.h"
#include "frame.h"
#include "interrupts.h"
#include "main.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct LocalRestoreTransferWork { u16 mainState0; u16 substate2; u16 state4; u8 pad6[2]; s32 counter8; };
struct LocalRestoreDmaRegisters { const void *volatile source; void *volatile destination; volatile u32 control; };

extern s32 sub_0803725C(void);
extern struct LocalRestoreTransferWork gGraphicsTransferCounter;
extern u8 gUnknown_030018D2[3];
extern void sub_0803579C(u32, u32);
extern void sub_08035814(s32);
extern void sub_08036270(void);
extern void sub_08074DE0(u32);
s32 sub_080688E0(void);

void sub_080218E4(void);
void sub_0802DAD0(void);
void sub_0806D600(void);

void sub_080218E4(void) {
 u8 *work = gState0TransferWork.bytes;
 u8 *selected = work + 0x87;
 sub_0803579C(*selected, work[0xA7]);
 sub_08035814(*selected);
 if (sub_0803725C() != 0) {
  u8 *status = work + 0xA6;
  *status = 0x1A;
  status += 4;
  *status += 1;
 } else {
  u8 *record = work + work[0x89] * 8;
  record += 0x2A;
  if (*record == 0) {
   u8 *status = work + 0xA6;
   *status = 0x24;
   status += 4;
   *status += 1;
  } else {
   sub_08036270();
   work[0xAA] = 4;
  }
 }
}

void sub_0802DAD0(void) {
    s32 var_r3;
    s32 var_r4;
    struct FrameObject *var_r1;
    u32 var_r2;
    u8 temp_r0;
    u8 *selection;

    var_r4 = 0;
    var_r3 = 0;
    var_r2 = 0;
    selection = gUnknown_030018D2;
    var_r1 = (struct FrameObject *)(((var_r2 + 0x21u) * 0x40u) + (u32)gFrameObjects);
    do {
        if (*(u8 *)(var_r2 + (u32)selection) != 0) {
            var_r3 += 1;
            temp_r0 = var_r1->scaleX;
            if (temp_r0 == 0x40) {
                var_r4 += 1;
            } else {
                var_r1->scaleX = temp_r0 - 8;
                var_r1->scaleY -= 8;
            }
        }
        var_r1 += 1;
        var_r2 += 1;
    } while (var_r2 <= 2U);
    if (var_r4 == var_r3) {
        sub_08074DE0(0x3CU);
        gState0TypedWork.widths.word86 = 0;
        gState0TransferWork.bytes[0xAA] = (u8) (gState0TransferWork.bytes[0xAA] + 1);
    }
}

void sub_0806D600(void) {
    s32 sp0;
    struct LocalRestoreDmaRegisters *dma;

    if (sub_080688E0() != 0) {
        sp0 = 0;
        dma = (struct LocalRestoreDmaRegisters *)0x040000D4;
        dma->source = &sp0;
        dma->destination = gFrameObjects;
        dma->control = 0x85000800;
        (void)dma->control;
        *(volatile u16 *)0x04000000 &= 0x80FF;
        gMainState = (u32) gGraphicsTransferCounter.mainState0;
        gMainSubstate = (u32) gGraphicsTransferCounter.substate2;
        gUnknown_0300137C = (u32) gGraphicsTransferCounter.state4;
        *(volatile u16 *)0x04000000 &= 0xFBFF;
        *(volatile u16 *)0x04000200 &= 0xFFFD;
        *(volatile u16 *)0x04000004 &= 0xFFEF;
        gUnknownCallback_03002C20 = DummyInterruptHandler;
        sub_08074B88(0U);
    }
}
