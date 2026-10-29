/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "state0_next_helpers.h"
#include "state0_work.h"


void sub_080333E4(void) {
  u8 *root;
  u8 *setup;
  u32 cursor;
  u32 i;
  u32 count;
  u32 index;
  u32 step;
  root = gState0TransferWork.bytes;
  root[0x60] = sub_08032FC4(root[0x5C]);
  i = 0;
  count = 0;
  setup = gSetupBuffer_03000590;
  index = root[0x60] << 8;
  setup += 0x40;
  cursor = (u32)setup + index;
  step = 0x100;
  do
  {
    if (*(const u8 *)cursor)
    {
      count++;
    }
    cursor += step;
    i++;
  }
  while (i <= 2);
  /* This single-iteration store block preserves the original allocation. */
  if (count <= 1)
  {
    do
    {
      root[0x51] = 1;
    } while (0);
  }
}
