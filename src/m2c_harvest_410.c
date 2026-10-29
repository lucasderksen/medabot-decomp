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
#include "initialization.h"
#include "object_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"


void sub_08014EE8(void);

void sub_08014EE8(void) {

  u32 *valueSlot;
  u32 value;
  u32 records;
  u32 sourceOrDestination;
  u32 countOrSize;
  u32 index;

  u32 workAddress;
  u32 countAddress;
  index = 0x0U;
  value = (u32) (&gState0TransferWork);
  sourceOrDestination = value + 0x0U;
  sourceOrDestination = sourceOrDestination + 0x5aU;
  countOrSize = (u32) (*((const u8 *) sourceOrDestination));
  if (index >= countOrSize)
  {
    goto finish;
  }
  records = (u32)gUnknownRecords_030017A0;
  copyRecords:
  ;

  workAddress = sourceOrDestination - 0x5aU;
  countAddress = sourceOrDestination;
  copyNext:
  ;

  value = workAddress + 0x0U;
  valueSlot = &value;
  value = (*valueSlot) + 0x41U;
  value = index + (*valueSlot);
  sourceOrDestination = (u32) (*((const u8 *) (*valueSlot)));
  value = 0xfU;
  value = (*valueSlot) & sourceOrDestination;
  value = (*valueSlot) << 0x3U;
  sourceOrDestination = records;
  value = (*valueSlot) + sourceOrDestination;
  value = (u32)*(const u8 *)(*valueSlot + 2);
  value = sub_08041D3C((u8)*valueSlot);
  value = (*valueSlot) << 6;
  /* Use this symbol only as an integer bus-address alias.
   * Mapper zero selects the preceding 64-byte inventory sentinel. */
  sourceOrDestination = (u32)gIntrTable;
  value = (*valueSlot) + sourceOrDestination;
  sourceOrDestination = index << 0x8U;
  countOrSize = ((u32)gSetupBuffer_03000590);
  sourceOrDestination = sourceOrDestination + countOrSize;
  countOrSize = 0x40U;
  sub_0803F63C((const void *) (*valueSlot), (void *) sourceOrDestination, (u32) countOrSize);
  index = index + 0x1U;
  value = (u32) (*((const u8 *) countAddress));
  if (index < (*valueSlot))
  {
    goto copyNext;
  }
  finish:;

  return;
}
