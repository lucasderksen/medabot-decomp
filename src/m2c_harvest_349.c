/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "render_work.h"
#include "sprite_layouts.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

extern void sub_08040D0C(u8, u8);
extern void sub_08040DB8(const u8 *, u32, s32, s32, u32, u32, u32, u32);
extern void sub_08041D04(const u8 *, u8 *, u8);
extern void sub_08042678(void *, u32);

void sub_0800EC44(void);

void sub_0800EC44(void) {

  const u8 *objects;
  const void * const **cursorAddress;
  u8 *work;
  u8 *buffer;
  u32 one;
  u32 bank;
  u32 bankOffset;
  u32 row;
  u32 rowFour;
  u32 offset;
  s32 y;
  u32 column;
  u32 displayPosition;
  sub_08040D0C(0xAU, 0x3CU);
  column = 0;
  objects = gObjectHalfwordBytes;
  work = gState0TypedWork.bytes;
  buffer = work + 0x9E;
  y = 5;
  displayPosition = 0x0A000000;
  one = 1;
  do
  {
    bank = work[0x3E];
    bankOffset = bank * 0xF0;
    row = work[0x3F];
    rowFour = row * 4;
    offset = bankOffset + (row * 8);
    offset += column * 2;
    if (objects[offset] != 0)
    {
      const void * const *cursor;
      u32 index;
      cursor = gPartTextPointers_083BBB4C;
      index = (((rowFour + column) * 4) + bank) * 4;
      cursor = (const void * const *) (index - (0U - ((u32) (*(cursorAddress = &cursor)))));
      sub_08041D04((const u8 *) (*cursor), buffer, 0xFU);
      sub_08040DB8(buffer, displayPosition >> 0x18, 0xB, y, 0xAU, 0xDU, one, one);
    }
    else
    {
      sub_08042678(buffer, 0xDU);
      sub_08040DB8(buffer, displayPosition >> 0x18, 0xB, y, 0xAU, 0xDU, one, one);
    }
    y += 2;
    displayPosition += 0x0F000000;
    column += 1;
  }
  while (column <= 3U);
}
