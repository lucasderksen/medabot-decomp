/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_map_data.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"


void sub_0801AE70(void);

void sub_0801AE70(void) {

  u32 value;
  u32 address;
  u32 index;
  u32 mask;
  u32 phaseMask;
  u32 frameBase;

  /* Update only the final eight entries of gFrameObjects[128]. */
  index = 0x0U;
  value = (u32)&gFrameObjects;
  phaseMask = 0x3U;
  mask = 0x1e06U;
  address = value + mask;
  mask = 0x3U;
  L801AE7E:;
  value = (u32)*(const u8 *)(address + 0x1bU);
  value = value + 0x1U;
  *(u8 *)(address + 0x1bU) = (u8)value;
  value = value & mask;
  if (value != 0) goto L801AE98;
  L801AE8A:;
  value = (u32)*(const u8 *)(address + 0x1cU);
  value = value + 0x1U;
  value = value & phaseMask;
  *(u8 *)(address + 0x1cU) = (u8)value;
  frameBase = 0x616U;
  value = value + frameBase;
  *(u16 *)(address) = (u16)value;
  L801AE98:;
  /* This final unused advance remains an integer, not an out-of-bounds pointer. */
  address = address + 0x40U;
  index = index + 0x1U;
  if (index <= 7U) goto L801AE7E;



  return;
}
