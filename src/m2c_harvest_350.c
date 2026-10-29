/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinueInputCoordinates1BD1C {u16 x,y;};
struct ContinueBrightnessWork6096C{u8 amount;u8 pad1[0x39];u16 delay;};


void sub_0801BD1C(const void *source, s32 mode, s32 index);
void sub_0806096C(void);

void sub_0801BD1C(const void *source, s32 mode, s32 index) {

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
  x = ((const struct ContinueInputCoordinates1BD1C *) source)->x;
  address += 2;
  *((u16 *) (*(addressReference = &address))) = x;
  y = ((const struct ContinueInputCoordinates1BD1C *) source)->y;
  address += 2;
  *((u16 *) address) = y;
  root[0x67] = mode;
}

void sub_0806096C(void) {

  volatile u16 *display = (volatile u16 *) 0x04000000;
  struct ContinueBrightnessWork6096C *work;
  u32 zero;
  volatile u16 *brightness;
  struct ContinueBrightnessWork6096C **workReference;
  display[0] |= 0x200;
  display[0] |= 0x400;
  display[0] |= 0x800;
  display[0] |= 0x1000;
  work = (struct ContinueBrightnessWork6096C *)gMainContextPointer_03006F74;
  zero = 0;
  work->amount = 8;
  brightness = (volatile u16 *) 0x04000054;
  work = (struct ContinueBrightnessWork6096C *)gMainContextPointer_03006F74;
  *brightness = (*(workReference = &work))->amount * 2;
  work->delay = zero;
  gUnknown_0300137C = (s32) (((u32) gUnknown_0300137C) + 1U);
}
