/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "gba.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "tile_text.h"


void sub_08044FB4(void *dst, const void *src, s32 shape, s32 size, s32 rows, s32 columns, s32 mode);

void sub_08044FB4(void *dst, const void *src, s32 shape, s32 size, s32 rows, s32 columns, s32 mode) {

  u16 d[2];
  s32 y;
  s32 x;
  s32 k;
  const u8 *rowStart;
  const u8 *nextRow;
  const u8 *colStart;
  u32 t;
  s32 rowScale;
  t = sub_08044E64(shape, size);
  d[0] = t >> 0x10;
  d[1] = t;
  d[0] = (d[0] >> 1) >> 2;
  d[1] = d[1] >> 3;
  rowScale = Div(0x40, 2 - mode);
  d[1] = d[1] * rowScale;
  for (y = 0; y < rows; y++)
  {
    rowStart = src;
    for (x = 0; x < columns; x++)
    {
      colStart = src;
      for (k = 0; k < d[0]; k++)
      {
        CpuSet(src, dst, (d[1] >> 2) | 0x04000000);
        src = (const u8 *)src + d[1] * columns;
        dst = (u8 *)dst + d[1];
      }

      src = colStart + d[1];
    }

    nextRow = rowStart + (columns * (d[0] * d[1]));
    src = nextRow;
  }

}
