/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"

struct RevealRowWork {u8 before3A[0x3A];s16 row;u8 before3E[2];u16 timer;};

extern void sub_08066D8C(void);

void sub_08067ACC(void);

void sub_08067ACC(void) {

 struct RevealRowWork *work;
 u32 next;
 sub_08066D8C();
 work=gMainContextPointer_03006F74;
 next=(u16)work->row+1U;
 work->row=(s16)next;
 if((s16)next>14){
  gUnknown_0300137C++;
  work->timer=0;
  sub_080750F0(0xC0);
 }else{
  u32 screenblock=(*(volatile u16 *)0x04000008>>8)&0x1F;
  s32 row=work->row;
  *(volatile u16 *)(0x06000080U+((screenblock<<11)+((u32)row<<6)))=0;
 }
}
