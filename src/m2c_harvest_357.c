/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s32 sub_0803725C(void);
extern void sub_0803579C(u32, s32);
extern void sub_08035814(s32);
extern void sub_08037280(u32, u32);

void sub_080223E4(void);

void sub_080223E4(void) {

 u8 *work;
 u8 *bank;
 u8 *item;
 s32 finished;
 u32 selectedBank;
 work = (u8 *)&gState0TransferWork;
 bank = &work[0x87];
 selectedBank = *bank;
 item = &work[0xA7];
 sub_0803579C(selectedBank, *item);
 sub_08035814(*bank);
 finished = sub_0803725C();
 if (finished != 0) {
  work[0xA6] = 0x1A;
  work[0xAA]++;
 } else {
  u8 recordKind;
  u8 *setup;
  sub_08036270();
  setup = gSetupBuffer_03000590;
  { u8 *record = (u8 *)(*item * 0x18 + (*bank << 8) + (u32)setup);
    recordKind = record[0x49]; }
  if (recordKind == 0x1B) goto zero_mode;
  if (recordKind == 0x1C) goto one_mode;
  work[0x51] = 2;
  goto mode_done;
zero_mode:
  work[0x51] = finished;
  goto mode_done;
one_mode:
  work[0x51] = 1;
mode_done:

  work = (u8 *)&gState0TransferWork;
  sub_08037280(work[0x87], work[0xA7]);
  work[0xAA] = 4;
 }
}
