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
#include "graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "serial.h"
#include "sprite_layouts.h"
#include "state0_next_helpers.h"
#include "tile_text.h"

extern const u8 gSpriteSetupMetadataBytes_083AD502[]; /* Four-byte records; full extent unrecovered. */

void sub_08016370(u32 value);

void sub_08016370(u32 value) {

  s8 phase;
  struct FrameObject *frame;
  u8 *base;
  u32 index;
  u32 flags;
  u32 zero;
  u8 *fields;
  u32 inputValue = value;
  u8 count = gSpriteSetupMetadataBytes_083AD502[value * 4];
  u8 kind = gSpriteSetupMetadataBytes_083AD502[(value * 4) + 1];
  u8 x = gSpriteSetupMetadataBytes_083AD502[(value * 4) + 2];
  u8 y = gSpriteSetupMetadataBytes_083AD502[(value * 4) + 3];
  sub_08040CD0(0x3CU, 0xAU);
  index = 0;
  if (index < ((u32) count))
  {
    base = (u8 *) gFrameObjects;
    zero = 0;
    flags = 0xC404;
    frame = (struct FrameObject *) (base + 0xF00);
    fields = base + 0xF0A;
    do
    {
      frame->flags = flags;
      *((u8 *) (((s8 *) fields) + 0x12)) = zero;
      frame->screenX = (s16) x;
      frame->screenY = (s16) y;
      *((u8 *) (((s8 *) fields) + 0)) = 8;
      *((u8 *) (((s8 *) fields) + 1)) = 0x80;
      phase = index & 3;
      frame->frameAndGroup = phase + 0x616;
      *((u8 *) (((s8 *) fields) + 0x1B)) = kind;
      *((u8 *) (((s8 *) fields) + 0x1C)) = (s8) ((count - 1) - index);
      *((u8 *) (((s8 *) fields) + 0x1A)) = zero;
      *((u8 *) (((s8 *) fields) + 0x1D)) = (s8) (index * 2);
      *((u8 *) (((s8 *) fields) + 0x1E)) = zero;
      *((u8 *) (((s8 *) fields) + 0x17)) = zero;
      *((u8 *) (((s8 *) fields) + 0x18)) = phase;
      if (inputValue > 2U)
      {
        frame->flags |= 0x1000;
      }
      frame++;
      fields += 0x40;
      index += 1;
    }
    while (index < ((u32) count));
  }
}
