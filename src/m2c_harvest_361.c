/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "frame_objects.h"
#include "state0_work.h"

extern const u8 *gState0NextCommands_083B6100[];

void sub_08038178(void);

void sub_08038178(void) {

  u8 *byteCursor;
  u32 value0;
  u32 value1;
  u32 value2;
  u32 framesAddress;
  u32 selectionAddress;
  value0 = (u32) gState0NextCommands_083B6100;
  value1 = 94U * 2U;
  value1 <<= 1;
  value0 += value1;
  value0 = (u32)*((const u8 *const *)value0);
  value1 = (u32) (&gState0TypedWork);
  value2 = 0x12F;
  selectionAddress = value1 + value2;
  value1 = (u32) (*((u8 *)selectionAddress));
  sub_08040BD8((const u8 *) value0, (u8) value1);
  framesAddress = (u32) gFrameObjects;
  value0 = (u32) (*((u8 *)selectionAddress));
  value0 <<= 6;
  value1 = value0 + framesAddress;
  byteCursor = (u8 *)value1;
  byteCursor += 0x2D;
  value2 = *byteCursor;
  if (value2 == 0x5A)
  {
    value1 += 0x29;
    value0 = (u32) (*((u8 *) value1));
    value0 += 1;
    *((u8 *) value1) = (u8) value0;
    return;
  }
  value0 = 7;
  value0 = 7 & value2;
  if (value0 == 0)
  {
    value0 = (u32) (*((u16 *) (value1 + 0x4U)));
    value0 -= 1;
    *((u16 *) (value1 + 0x4U)) = (u16) value0;
  }
  value0 = (u32) (*((u8 *)selectionAddress));
  value0 <<= 6;
  value0 += (u32) gFrameObjects;
  value0 += 0x2D;
  value1 = (u32) (*((u8 *) value0));
  value1 += 1;
  *((u8 *) value0) = (u8) value1;
}
