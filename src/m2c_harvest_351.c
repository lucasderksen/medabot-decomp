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
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_display.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinueInputCoordinates1BF78 {u16 x,y;};


void sub_0801BF78(const void *source, u32 mode, u32 index);

void sub_0801BF78(const void *source, u32 mode, u32 index) {


  u8 *typed = gState0TypedWork.bytes;
  u8 *root = (u8 *) ((((u32) index) << 3) + ((u32) typed));
  u8 *out = root + 0x64;
  u32 zero = 0;
  u32 address;
  u16 x;
  u16 y;
  u32 *addressReference;
  *out = zero;
  root[0x65] = 2;
  out = root + 0x66;
  *out = zero;
  address = (u32) out;
  x = ((const struct ContinueInputCoordinates1BF78 *) source)->x;
  address += 2;
  *((u16 *) (*(addressReference = &address))) = x;
  y = ((const struct ContinueInputCoordinates1BF78 *) source)->y;
  address += 2;
  *((u16 *) address) = y;
  root[0x67] = mode;
}
