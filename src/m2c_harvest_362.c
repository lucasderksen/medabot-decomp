/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "state0_next_helpers.h"
#include "state0_work.h"


void sub_08039188(void);

void sub_08039188(void) {

  u8 *bankCursor;
  u32 value0;
  u32 value1;
  u32 workAddress;
  value1 = (u32) gSetupBuffer_03000590;
  workAddress = (u32) (&gState0TransferWork);
  bankCursor=(u8 *)workAddress;
  bankCursor+=0x88;
  value0=*bankCursor;
  value0 <<= 8;
  value0 += value1;
  value0 += 0xBC;
  value1 = (u32) (*((u8 *) value0));
  value0 = 0x10;
  value0 = 0x10 & value1;
  value0 <<= 0x18;
  value1 = value0 >> 0x18;
  if (value1 != 0)
  {
    value0 = workAddress;
    value0 += 0xAB;
    value1 = 1;
    *((s8 *) value0) = 1;
    value0 += 0xC;
  }
  else
  {
    value0 = workAddress;
    value0 += 0xAB;
  }
  *((s8 *) value0) = (s8) value1;
}
