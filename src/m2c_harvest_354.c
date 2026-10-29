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
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_next_helpers.h"
#include "tile_text.h"


void sub_080363E8(s32 x, u32 y, u32 numerator, u32 denominator, u32 scale);

void sub_080363E8(s32 x, u32 y, u32 numerator, u32 denominator, u32 scale) {

  u32 remainder;
  u32 blocks;
  u32 drawn;
  u32 padding;
  u32 column;
  s32 startCount;
  blocks = sub_08015DD0(numerator, denominator, scale);
  remainder = 0xFFFF & blocks;
  startCount = 0;
  blocks >>= 0x10;
  if (((scale != 0) && (blocks == 0)) && (remainder == 0))
  {
    remainder = 1;
  }
  column = 0;
  drawn = startCount;
  while (drawn < blocks)
  {
    sub_08042698(1U, 1U, x + column, y, (u32) (*((volatile u16 *) 0x0400000A)), 0xA328U);
    column += 1;
    drawn += 1;
  }

  if (remainder != 0)
  {
    sub_08042698(1U, 1U, x + column, y, (u32) (*((volatile u16 *) 0x0400000A)), ((remainder + 0xA320u) << 16) >> 16);
    column += 1;
  }
  padding = column;
  if (padding <= 7U)
  {
    do
    {
      sub_08042698(1U, 1U, x + column, y, (u32) (*((volatile u16 *) 0x0400000A)), 0xA320U);
      column += 1;
      padding += 1;
    }
    while (padding <= 7U);
  }
}
