/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "display_helpers.h"
#include "frame.h"
#include "graphics.h"
#include "state0_next_helpers.h"
#include "state0_work.h"


void sub_08014F44(void);

void sub_08014F44(void) {

  u32 *valueSlot;
u32 value;
  u32 sourceOrDestination;
  u32 countOrSize;
  u32 index;
  
  u32 workAddress;
  u32 countAddress;
  index  =  0x0U;
  value  =  (u32) (&gState0TransferWork);
  sourceOrDestination  =  value + 0x0U;
  sourceOrDestination  =  sourceOrDestination + 0x5aU;
  countOrSize  =  (u32) (*((const u8 *) sourceOrDestination));
  if (index >= countOrSize)
  {
    goto L8014F7E;
  }
  L8014F54:
  ;

  workAddress = sourceOrDestination - 0x5aU;countAddress = sourceOrDestination;
  L8014F58:
  ;

  value  =  workAddress + 0x0U;
  valueSlot  =  &value;
  value  =  (*valueSlot) + 0x41U;
  value  =  index + (*valueSlot);
  sourceOrDestination  =  (u32) (*((const u8 *) (*valueSlot)));
  value  =  0xfU;
  value  =  (*valueSlot) & sourceOrDestination;
  value  =  (*valueSlot) << 0x3U;
  sourceOrDestination  =  (u32) (&gUnknownRecords_030017A0);
  value  =  (*valueSlot) + sourceOrDestination;
  sourceOrDestination  =  index << 0x8U;
  countOrSize  =  ((u32)gSetupBuffer_03000590 + 0x40U);
  sourceOrDestination  =  sourceOrDestination + countOrSize;
  countOrSize  =  0x8U;
  sub_0803F63C((const void *) (*valueSlot), (void *) sourceOrDestination, (u32) countOrSize);
  index  =  index + 0x1U;
  value  =  (u32) (*((const u8 *) countAddress));
  if (index < (*valueSlot))
  {
    goto L8014F58;
  }
  L8014F7E:;

  return;
}
