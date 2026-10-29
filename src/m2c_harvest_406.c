/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "continued_selector_assets.h"
#include "frame.h"
#include "graphics.h"
#include "state0_debug_menu.h"


void sub_0805BAA0(u32 tileOffset,s32 paletteOffset,s32 screenBlock);

void sub_0805BAA0(u32 tileOffset,s32 paletteOffset,s32 screenBlock) {

  u16 entry;
  u32 value;
  u32 component;
  u32 tileAndFlipMask;
  u32 masked;
  u32 destination;
  u32 remaining;
  u16 tileMask;
  u32 paletteDelta;
  u32 tileDelta;
  u32 paletteMask;
  u32 attributesMask;

  /* Convert signed inputs before shifting; preserve the ROM low-bit masks. */
  value = tileOffset;
  component = paletteOffset;
  masked = screenBlock;

  value = value << 0x10U;
  tileDelta = value >> 0x10U;
  component = component << 0x18U;
  paletteDelta = component >> 0x18U;
  masked = masked << 0x18U;
  masked = masked >> 0xdU;
  value = 0xc0U;
  value = value << 0x13U;
  destination = masked + value;
  tileMask = 0x3ffU;
  value = 0xfcU;
  value = value << 0x8U;
  attributesMask = value;
  component = 0xf0U;
  component = component << 0x8U;
  paletteMask = component;
  remaining = tileMask + 0x1U;
  masked = 0xfffU;
  tileAndFlipMask = masked;
  /* The integer cursor forms only the original hardware bus addresses. */
  do
  {
    entry = *(const u16 *)destination;
    component = entry;
    value = component & tileMask;
    value = value + tileDelta;
    value = value & tileMask;
    masked = attributesMask;
    component = component & masked;
    value = value | component;
    masked = value + 0x0U;
    component = paletteMask;
    masked = masked & component;
    component = paletteDelta << 0xcU;
    masked = masked + component;
    component = tileAndFlipMask;
    value = value & component;
    value = value | masked;
    *(u16 *)(destination) = (u16)value;
    destination = destination + 0x2U;
    remaining = remaining - 0x1U;
  } while (remaining != 0);

  return;
}
