/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct LinkedSetupMode334E0 { u8 prefix[0xC9]; u8 mode; };


void sub_080334E0(void);

void sub_080334E0(void) {

  /* Preserve word-address wrapping of the ROM's linked-record lookup. */
  struct LinkedSetupMode334E0 *setup = (struct LinkedSetupMode334E0 *) gSetupBuffer_03000590;
  u8 *work = gState0TransferWork.bytes;
  u32 linked;
  u32 partOffset;
  u32 bankOffset;
  u8 *part = work + 0x5D;
  u8 *bank;
  partOffset = (*part) * 0x18;
  bank = work + 0x5C;
  bankOffset = (*bank) << 8;
  linked = (*((u8 *) (((partOffset + bankOffset) + ((u32) setup)) + 0x56))) - 1;
  if (((struct LinkedSetupMode334E0 *) ((linked << 8) + ((u32) setup)))->mode != 0)
  {
    work[0x51] = 1;
  }
  partOffset = (*part) * 0x18;
  bankOffset = (*bank) << 8;
  if ((sub_080331F8((*((u8 *) (((bankOffset + ((*part) * 0x18)) + ((u32) setup)) + 0x56))) - 1) == 0))
  {
    work[0x51] = 1;
  }
}
