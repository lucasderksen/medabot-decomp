/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "later_graphics.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Continued3279CWork {u8 prefix[0x5C];u8 owner,other,selected,found,cursor,slots[3];};

extern u32 sub_08032FD0(u32,u32);
extern u32 sub_08032FFC(void);
extern u32 sub_0803301C(void);
extern void sub_08033154(u32,u32);

void sub_0803279C(void);

void sub_0803279C(void) {

  /* Observed transfer bytes 5C..63; cursors use the whole work buffer. */
  u32 i;
  u8 *work = gState0TransferWork.bytes;
  work[0x60] = sub_08032FC4(work[0x5C]);
  i = 0;
  {
    u8 *setup = gSetupBuffer_03000590;
    u32 address = (u32) work;
    u8 *cursor = (u8 *) (address + 0x60);
    u8 *slots = (u8 *) (address + 0x61);
    do
    {
      u32 record = ((*cursor) << 8) + ((u32) setup);
      if (((*((u8 *) (record + 0x40))) && ((*cursor) != (*((u8 *) (address + 0x5C))))) && sub_08032FD0(*cursor, setup[((*((u8 *) (address + 0x5C))) << 8) + 6]))
      {
        *((u8 *) (i + ((u32) slots))) = (*cursor) + 1;
      }
      *cursor += 1;
      ++i;
    }
    while (i <= 2);
  }
  if (sub_08032FFC())
  {
    ((struct Continued3279CWork *) (&gState0TransferWork))->selected = sub_0803301C() + 1;
  }
  else
  {
    u8 *work = gState0TransferWork.bytes;
    work[0x60] = sub_08032FC4(((struct Continued3279CWork *) work)->owner);
    i = 0;
    {
      u8 *setup = gSetupBuffer_03000590;
      u32 address = (u32) work;
      u8 *cursor = (u8 *) (address + 0x60);
      u8 *slots = (u8 *) (address + 0x61);
      do
      {
        u32 record = ((*cursor) << 8) + ((u32) setup);
        if ((*((u8 *) (record + 0x40))) && ((*cursor) != (((struct Continued3279CWork *) work)->owner)))
        {
          *((u8 *) (i + ((u32) slots))) = (*cursor) + 1;
        }
        *cursor += 1;
        ++i;
      }
      while (i <= 2);
    }
    if (sub_08032FFC())
    {
      ((struct Continued3279CWork *) (&gState0TransferWork))->selected = sub_0803301C() + 1;
    }
    else
    {
      u8 *work = gState0TransferWork.bytes;
      work[0x60] = sub_08032FC4(work[0x5C]);
      ((struct Continued3279CWork *) work)->selected = sub_08033090(work[0x60]) + 1;
    }
  }
  {
    u8 *work = gState0TransferWork.bytes;
    sub_08033154(work[0x5C], work[0x5D]);
  }
}
