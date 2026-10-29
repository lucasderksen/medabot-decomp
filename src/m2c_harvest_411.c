/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern void sub_08039250(void);
extern void sub_0803934C(void);

void sub_0803713C(void);

void sub_0803713C(void) {

  u32 value;
  u32 address;
  u32 offset;
  u32 bankOrSide;
  u32 workAddress;
  /* This alias refers to the local address value and never escapes. */
  u32 *workAddressValue = &workAddress;
  u32 zero;
  offset = (u32) (&gSetupBuffer_03000590);
  workAddress = (u32) (&gState0TransferWork);
  bankOrSide = (*workAddressValue);
  bankOrSide = bankOrSide + 0x87U;
  address = (u32) (*((const u8 *) bankOrSide));
  value = address << 0x8U;
  value = value + offset;
  address = address + 0x1U;
  value = value + 0xe0U;
  zero = 0x0U;
  *((u8 *) value) = (u8) address;
  value = (u32) (*((const u8 *) bankOrSide));
  value = value << 0x8U;
  value = value + offset;
  address = (*workAddressValue);
  address = address + 0xa7U;
  address = (u32) (*((const u8 *) address));
  address = address + 0x1U;
  value = value + 0xe1U;
  *((u8 *) value) = (u8) address;
  value = (*workAddressValue);
  value = value + 0x8bU;
  value = (u32) (*((const u8 *) value));
  offset = 0xb1U;
  offset = offset << 0x1U;
  address = (*workAddressValue) + offset;
  *((u8 *) address) = (u8) value;
  value = value << 0x18U;
  value = value >> 0x18U;
  if (value != 3U)
    goto selectionSaved;

  *((u8 *) address) = (u8) zero;
  selectionSaved:
  ;

  value = (*workAddressValue);
  value = value + 0x88U;
  value = (u32) (*((const u8 *) value));
  offset = 0x161U;
  address = (*workAddressValue) + offset;
  *((u8 *) address) = (u8) value;
  value = (u32) (*((const u8 *) bankOrSide));
  sub_080355C4((u32) value);
  offset = (*workAddressValue);
  offset = offset + 0xf8U;
  value = (u32) (*((const u8 *) offset));
  address = 0x2U;
  value = value ^ address;
  *((u8 *) offset) = (u8) value;
  address = (*workAddressValue);
  address = address + 0xb7U;
  *((u8 *) address) = (u8) zero;
  offset = offset - 0x2U;
  address = 0x2U;
  *((u8 *) offset) = (u8) address;
  value = value & address;
  value = value << 0x18U;
  bankOrSide = value >> 0x18U;
  if (bankOrSide != 0)
    goto leftSide;

  address = 0x8aU;
  address = address << 0x1U;
  value = (*workAddressValue) + address;
  *((u8 *) value) = (u8) bankOrSide;
  goto updateOtherSide;
  leftSide:
  ;

  offset = 0x8aU;
  offset = offset << 0x1U;
  address = (*workAddressValue) + offset;
  value = 0x28U;
  *((u8 *) address) = (u8) value;
  offset = (*workAddressValue);
  offset = offset + 0xffU;
  value = (u32) (*((const u8 *) offset));
  address = 0x1U;
  value = value | address;
  *((u8 *) offset) = (u8) value;
  updateOtherSide:
  ;

  offset = (u32) (&gState0TransferWork);
  address=(u32)*(const u8 *)(offset+0xF8U);
  value = 0x2U;
  value = value & address;
  if (value != 0)
    goto clearOtherSide;

  value = 0x115U;
  address = offset + value;
  value = 0x28U;
  *((u8 *) address) = (u8) value;
  bankOrSide = offset + 0x0U;
  bankOrSide = bankOrSide + 0xffU;
  address = (u32) (*((const u8 *) bankOrSide));
  value = 0x2U;
  value = value | address;
  *((u8 *) bankOrSide) = (u8) value;
  goto dispatchPredicates;
  clearOtherSide:
  ;

  value = 0x115U;
  address = offset + value;
  value = 0x0U;
  *((u8 *) address) = (u8) value;
  dispatchPredicates:
  ;

  address = offset + 0x0U;
  address = address + 0xb8U;
  value = 0x0U;
  *((u8 *) address) = (u8) value;
  sub_08039250();
  sub_0803934C();
  return;
}
