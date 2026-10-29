/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "eeprom.h"
#include "frame.h"
#include "later_graphics.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct SelectionBacking
{
  u8 prefix[0x5C];
  u8 owner;
  u8 other;
  u8 selected;
  u8 found;
  u8 cursor;
  u8 slots[3];
};
struct FrameInitBacking {
    u8 padding[0xC0];
    u16 flags;
    s16 x;
    s16 y;
    u16 frame;
    u8 scales[2];
    u8 palette;
    u8 priority;
    u8 gap[0x10];
    u8 table;
};
struct FrameCounterBacking {
    u8 prefix[0x14];
    s32 current;
    s32 extra;
    s32 saved;
    u8 gap[0x53 - 0x20];
    u8 count;
};

extern __typeof__(sub_08032FC4) sub_08032FB8;
extern s32 sub_08032FD0(u32, u32);
extern s32 sub_08032FFC(void);
extern s32 sub_0803301C(void);
extern s32 sub_080330E8(s32);
extern s32 sub_08033154(u32, u32);
extern u32 sub_08033184(u32);
extern u32 sub_08033224(u32);
extern u32 sub_08033240(u32);
extern u32 sub_0803325C(u32);
extern void sub_0807258C(void *);

void sub_08027964(void);
void sub_08029464(void);
void sub_08031BCC(void);
void sub_08032478(void);
void sub_080328B8(void);

void sub_08027964(void) {
    u8 *setup = gSetupBuffer_03000590;
    u8 *work = gState0TransferWork.bytes;
    u32 slot = work[0x87] << 8;
    u32 kind = *(u8 *) (slot + (u32) setup + 0xA8);
    switch (kind - 4) {
    case 0: work[0x51] = 0; break;
    case 1: work[0x51] = 1; break;
    case 2: work[0x51] = 2; break;
    case 3: work[0x51] = 3; break;
    case 4: work[0x51] = 4; break;
    default: work[0x51] = 5; break;
    }
    work[0xAA]++;
}

void sub_08029464(void) {
    u8 *work = gState0TransferWork.bytes;
    switch (work[0x51]) {
    case 0:
        work[0xA6] = 0x55;
        break;
    case 1:
        work[0xA6] = 0x58;
        break;
    case 2:
        work[0xA6] = 0x56;
        break;
    case 3:
        work[0xA6] = 0x57;
        break;
    }
    work[0xAA]++;
}

void sub_08031BCC(void) {
  u32 i;
  {
    u8 *work = gState0TransferWork.bytes;
    u8 *setup;
    u32 address;
    u8 *cursor;
    u8 *slots;
    work[0x60] = sub_08032FB8(work[0x5C]);
    i = 0;
    setup = gSetupBuffer_03000590;
    address = (u32) work;
    cursor = (u8 *) (address + 0x60);
    slots = (u8 *) (address + 0x61);
    do
    {
      u32 record = ((*cursor) << 8) + ((u32) setup);
      if ((((*((u8 *) (record + 0x40))) != 0) && ((*((u8 *) (record + 0x91))) == 0x64)) && (sub_08032FD0(*cursor, setup[((*((u8 *) (address + 0x5C))) << 8) + 6]) != 0))
        *((u8 *) (i + ((u32) slots))) = (*cursor) + 1;
      *cursor += 1;
      i++;
    }
    while (i <= 2);
  }
  if (sub_08032FFC() != 0)
  {
    ((struct SelectionBacking *) (&gState0TransferWork))->selected = sub_0803301C() + 1;
  }
  else
  {
    {
      u8 *work = gState0TransferWork.bytes;
      u8 *setup;
      u32 address;
      u8 *cursor;
      u8 *slots;
      work[0x60] = sub_08032FB8(work[0x5C]);
      i = 0;
      setup = gSetupBuffer_03000590;
      address = (u32) work;
      cursor = (u8 *) (address + 0x60);
      slots = (u8 *) (address + 0x61);
      do
      {
        u32 record = ((*cursor) << 8) + ((u32) setup);
        if (((*((u8 *) (record + 0x40))) != 0) && ((*((u8 *) (record + 0x91))) == 0x64))
          *((u8 *) (i + ((u32) slots))) = (*cursor) + 1;
        *cursor += 1;
        i++;
      }
      while (i <= 2);
    }
    if (sub_08032FFC() != 0)
    {
      ((struct SelectionBacking *) (&gState0TransferWork))->selected = sub_0803301C() + 1;
    }
    else
    {
      {
        u8 *work = gState0TransferWork.bytes;
        u8 *setup;
        u32 address;
        u8 *cursor;
        u8 *slots;
        work[0x60] = sub_08032FB8(work[0x5C]);
        i = 0;
        setup = gSetupBuffer_03000590;
        address = (u32) work;
        cursor = (u8 *) (address + 0x60);
        slots = (u8 *) (address + 0x61);
        do
        {
          u32 record = ((*cursor) << 8) + ((u32) setup);
          if (((*((u8 *) (record + 0x40))) != 0) && (sub_08032FD0(*cursor, setup[((*((u8 *) (address + 0x5C))) << 8) + 6]) != 0))
            *((u8 *) (i + ((u32) slots))) = (*cursor) + 1;
          *cursor += 1;
          i++;
        }
        while (i <= 2);
      }
      if (sub_08032FFC() != 0)
      {
        ((struct SelectionBacking *) (&gState0TransferWork))->selected = sub_0803301C() + 1;
      }
      else
      {
        u8 *work = gState0TransferWork.bytes;
        work[0x60] = sub_08032FB8(work[0x5C]);
        ((struct SelectionBacking *) work)->selected = sub_08033090(work[0x60]) + 1;
      }
    }
  }
  {
    u8 *work = gState0TransferWork.bytes;
    u8 *selected = &((struct SelectionBacking *) work)->selected;
    ((struct SelectionBacking *) work)->found = sub_080330E8((*selected) - 1) + 1;
  }
  {
    u8 *work = gState0TransferWork.bytes;
    sub_08033154(work[0x5C], work[0x5D]);
  }
}

void sub_08032478(void) {
  u32 i;
  {
    u8 *work = gState0TransferWork.bytes;
    u8 *setup;
    u32 address;
    u8 *cursor;
    u8 *slots;
    work[0x60] = sub_08032FC4(work[0x5C]);
    i = 0;
    setup = gSetupBuffer_03000590;
    address = (u32) work;
    cursor = (u8 *) (address + 0x60);
    slots = (u8 *) (address + 0x61);
    do
    {
      if (((setup[((*cursor) << 8) + 0x40] != 0) && (sub_0803325C(*cursor) != 0)) && (sub_08032FD0(*cursor, setup[((*((u8 *) (address + 0x5C))) << 8) + 6]) != 0))
        *((u8 *) (i + ((u32) slots))) = (*cursor) + 1;
      *cursor += 1;
      i++;
    }
    while (i <= 2);
  }
  if (sub_08032FFC() != 0)
  {
    ((struct SelectionBacking *) (&gState0TransferWork))->selected = sub_0803301C() + 1;
  }
  else
  {
    {
      u8 *work = gState0TransferWork.bytes;
      u8 *setup;
      u32 address;
      u8 *cursor;
      u8 *slots;
      work[0x60] = sub_08032FC4(work[0x5C]);
      i = 0;
      setup = gSetupBuffer_03000590;
      address = (u32) work;
      cursor = (u8 *) (address + 0x60);
      slots = (u8 *) (address + 0x61);
      do
      {
        if ((setup[((*cursor) << 8) + 0x40] != 0) && (sub_0803325C(*cursor) != 0))
          *((u8 *) (i + ((u32) slots))) = (*cursor) + 1;
        *cursor += 1;
        i++;
      }
      while (i <= 2);
    }
    if (sub_08032FFC() != 0)
    {
      ((struct SelectionBacking *) (&gState0TransferWork))->selected = sub_0803301C() + 1;
    }
    else
    {
      {
        u8 *work = gState0TransferWork.bytes;
        u8 *setup;
        u32 address;
        u8 *cursor;
        u8 *slots;
        work[0x60] = sub_08032FC4(work[0x5C]);
        i = 0;
        setup = gSetupBuffer_03000590;
        address = (u32) work;
        cursor = (u8 *) (address + 0x60);
        slots = (u8 *) (address + 0x61);
        do
        {
          if ((setup[((*cursor) << 8) + 0x40] != 0) && (sub_08032FD0(*cursor, setup[((*((u8 *) (address + 0x5C))) << 8) + 6]) != 0))
            *((u8 *) (i + ((u32) slots))) = (*cursor) + 1;
          *cursor += 1;
          i++;
        }
        while (i <= 2);
      }
      if (sub_08032FFC() != 0)
      {
        ((struct SelectionBacking *) (&gState0TransferWork))->selected = sub_0803301C() + 1;
      }
      else
      {
        u8 *work = gState0TransferWork.bytes;
        work[0x60] = sub_08032FC4(work[0x5C]);
        ((struct SelectionBacking *) work)->selected = sub_08033090(work[0x60]) + 1;
      }
    }
  }
  {
    u8 *work = gState0TransferWork.bytes;
    u8 *selected = &((struct SelectionBacking *) work)->selected;
    u32 found = sub_0803325C((*selected) - 1);
    if (found != 0)
      ((struct SelectionBacking *) work)->found = found;
    else
      ((struct SelectionBacking *) work)->found = sub_080330E8((*selected) - 1) + 1;
  }
  {
    u8 *work = gState0TransferWork.bytes;
    sub_08033154(work[0x5C], work[0x5D]);
  }
}

void sub_080328B8(void) {
  u32 i;
  {
    u8 *work = gState0TransferWork.bytes;
    u8 *setup;
    u32 address;
    u8 *cursor;
    u8 *slots;
    work[0x60] = sub_08032FB8(work[0x5C]);
    i = 0;
    setup = gSetupBuffer_03000590;
    address = (u32) work;
    cursor = (u8 *) (address + 0x60);
    slots = (u8 *) (address + 0x61);
    do
    {
      if ((((setup[((*cursor) << 8) + 0x40] != 0) && (sub_080331F8(*cursor) != 0)) && (sub_08033240(*cursor) != 0)) && (sub_08032FD0(*cursor, setup[((*((u8 *) (address + 0x5C))) << 8) + 6]) != 0))
        *((u8 *) (i + ((u32) slots))) = (*cursor) + 1;
      *cursor += 1;
      i++;
    }
    while (i <= 2);
  }
  if (sub_08032FFC() != 0)
  {
    ((struct SelectionBacking *) (&gState0TransferWork))->selected = sub_0803301C() + 1;
  }
  else
  {
    {
      u8 *work = gState0TransferWork.bytes;
      u8 *setup;
      u32 address;
      u8 *cursor;
      u8 *slots;
      work[0x60] = sub_08032FB8(work[0x5C]);
      i = 0;
      setup = gSetupBuffer_03000590;
      address = (u32) work;
      cursor = (u8 *) (address + 0x60);
      slots = (u8 *) (address + 0x61);
      do
      {
        if (((setup[((*cursor) << 8) + 0x40] != 0) && (sub_080331F8(*cursor) != 0)) && (sub_08033240(*cursor) != 0))
          *((u8 *) (i + ((u32) slots))) = (*cursor) + 1;
        *cursor += 1;
        i++;
      }
      while (i <= 2);
    }
    if (sub_08032FFC() != 0)
    {
      ((struct SelectionBacking *) (&gState0TransferWork))->selected = sub_0803301C() + 1;
    }
    else
    {
      {
        u8 *work = gState0TransferWork.bytes;
        u8 *setup;
        u32 address;
        u8 *cursor;
        u8 *slots;
        work[0x60] = sub_08032FB8(work[0x5C]);
        i = 0;
        setup = gSetupBuffer_03000590;
        address = (u32) work;
        cursor = (u8 *) (address + 0x60);
        slots = (u8 *) (address + 0x61);
        do
        {
          if ((setup[((*cursor) << 8) + 0x40] != 0) && (sub_08032FD0(*cursor, setup[((*((u8 *) (address + 0x5C))) << 8) + 6]) != 0))
            *((u8 *) (i + ((u32) slots))) = (*cursor) + 1;
          *cursor += 1;
          i++;
        }
        while (i <= 2);
      }
      if (sub_08032FFC() != 0)
      {
        ((struct SelectionBacking *) (&gState0TransferWork))->selected = sub_0803301C() + 1;
      }
      else
      {
        u8 *work = gState0TransferWork.bytes;
        work[0x60] = sub_08032FB8(work[0x5C]);
        ((struct SelectionBacking *) work)->selected = sub_08033090(work[0x60]) + 1;
      }
    }
  }
  {
    u8 *work = gState0TransferWork.bytes;
    sub_08033154(work[0x5C], work[0x5D]);
  }
}
