/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "equipment_helpers.h"
#include "interrupts.h"

extern void sub_0805AC8C(void);

void sub_0805AD98(u16 colorValue, s32 tintWeight);

void sub_0805AD98(u16 colorValue, s32 tintWeight) {

  u16 tintColor = colorValue;
  s32 sourceWeight;
  u32 colorIndex,lastColor;
  u32 byteOffset;
  u16 redMask;
  u16 greenMask;
  u16 blueMask;
  s32 weightedRed;
  s32 weightedGreen;
  s32 weightedBlue;
  u32 mixedColor;
  u32 greenComponent;
  u32 component;
  u16 sourceColor;
  u16 *destination;
  if (tintWeight < 0)
  {
    tintWeight = 0;
  }
  if (tintWeight > 32)
  {
    tintWeight = 32;
  }
  sourceWeight = 32 - tintWeight;
  colorIndex = 256;lastColor=511;
  redMask = 31;
  weightedRed = (tintColor & redMask) * tintWeight;
  greenMask = 0x3E0;
  blueMask = 0x7C00;
  weightedGreen = (tintColor & greenMask) * tintWeight;
  weightedBlue = (tintColor & blueMask) * tintWeight;
  do
  {
    byteOffset = colorIndex * 2U;
    destination = (u16 *) (byteOffset + 0x0202FC00U);
    sourceColor = *((u16 *) (byteOffset + ((u32)gEquipmentPaletteShadow-0x200U)));
    component = redMask & sourceColor;
    mixedColor = component;
    mixedColor *= sourceWeight;
    mixedColor += weightedRed;
    mixedColor >>= 5;
    greenComponent = greenMask & sourceColor;
    greenComponent *= sourceWeight;
    greenComponent += weightedGreen;
    greenComponent >>= 5;
    greenComponent &= greenMask;
    mixedColor |= greenComponent;
    component = blueMask & sourceColor;
    component *= sourceWeight;
    component += weightedBlue;
    component >>= 5;
    component &= blueMask;
    mixedColor |= component;
    *destination = mixedColor;
    colorIndex++;
  }
  while (colorIndex <= lastColor);
  gUnknownCallback_03000B98 = sub_0805AC8C;
}
