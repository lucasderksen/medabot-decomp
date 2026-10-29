/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_commands.h"
#include "continued_late_graphics.h"


void sub_0804C778(void);

void sub_0804C778(void) {
  u32 root;
  u32 address;
  u32 value;
  u32 offset;
  sub_0804D8CC(2);
  root = (u32) gUnknown_030057E0;
  value = *((u8 *) (root + 0xC94));
  if (value == 0)
  {
    /* This single-iteration block preserves the observed constant lifetimes. */
    do
    {
      offset = 0xCBC;
      address = root + offset;
      offset = 0xC95;
      value = *((u8 *) (root + offset));
      offset = *((u8 *) address);
      value += offset;
      *((u8 *) address) = value;
      value = 0xCBD;
      address = root + value;
      value = (u32) (*((s8 *) address));
    }
    while (0);
  }
  else
  {
    offset = 0xCBD;
    address = root + offset;
    offset = 0xC95;
    value = *((u8 *) (root + offset));
    /* The work address is dead here; reuse its temporary for the old byte. */
    root = *((u8 *) address);
    value += root;
    *((s8 *) address) = value;
    value <<= 24;
    value = (u32) (((s32) value) >> 24);
  }
  if (((s32) value) > 32)
  {
    *((s8 *) address) = 32;
  }
}
