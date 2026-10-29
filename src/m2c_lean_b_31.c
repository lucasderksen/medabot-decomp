/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "display_effects.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"
#include "interrupts.h"
#include "record_helpers.h"
#include "state0_callbacks.h"

extern u16 gCopy6280C0202F800[];
extern u16 gUnknown_0202FC00[];
extern u16 gUnknown_0202FE00[];

void sub_0803F684(u32 rawColor, u32 weight, u32 paletteMask);
void sub_0803F788(u32 rawColor, u32 weight, u32 paletteMask);
void sub_0803F890(u32 rawColor, u32 weight, u32 paletteMask);
void sub_0803F998(u32 rawColor, u32 weight, u32 paletteMask);

void sub_0803F684(u32 rawColor, u32 weight, u32 paletteMask) {

    u32 color = (u16)rawColor;
    u16 mask = paletteMask;
    u32 i;
    u32 j;
    u16 bit = 1;
    u32 inverse;
    void *palette = (void *)0x05000000;

    if (weight > 0x20)
        weight = 0x20;
    inverse = 0x20 - weight;
    for (i = 0; i <= 0xF; i++) {
        if (mask & bit) {
            for (j = 0; j <= 0xF; j++) {
                gUnknown_0202FE00[i * 16 + j] = (((0x1F & gEquipmentPaletteShadow[i * 16 + j]) * inverse + (color & 0x1F) * weight) >> 5)
                    | ((((0x3E0 & gEquipmentPaletteShadow[i * 16 + j]) * inverse + (color & 0x3E0) * weight) >> 5) & 0x3E0)
                    | ((((0x7C00 & gEquipmentPaletteShadow[i * 16 + j]) * inverse + (color & 0x7C00) * weight) >> 5) & 0x7C00);
            }
        } else {
            for (j = 0; j <= 0xF; j++)
                gUnknown_0202FE00[i * 16 + j] = gEquipmentPaletteShadow[i * 16 + j];
        }
        bit <<= 1;
    }
    CpuFastSet(gUnknown_0202FE00, palette, 0x80);
}

void sub_0803F788(u32 rawColor, u32 weight, u32 paletteMask) {

  u32 color = (u16) rawColor;
  u16 mask = paletteMask;
  u16 *new_var;
  u32 i;
  u32 j;
  u16 bit = 1;
  u32 inverse;
  new_var = gEquipmentPaletteShadow;
  if (weight > 0x20)
  {
    weight = 0x20;
  }
  inverse = 0x20 - weight;
  for (i = 0; i <= 0xF; i++)
  {
    if (mask & bit)
    {
      for (j = 0; j <= 0xF; j++)
      {
        gUnknown_0202FE00[(i * 16) + j] = (((((0x1F & new_var[(i * 16) + j]) * inverse) + ((color & 0x1F) * weight)) >> 5) | (((((0x3E0 & new_var[(i * 16) + j]) * inverse) + ((color & 0x3E0) * weight)) >> 5) & 0x3E0)) | (((((0x7C00 & new_var[(i * 16) + j]) * inverse) + ((color & 0x7C00) * weight)) >> 5) & 0x7C00);
      }

    }
    else
    {
      for (j = 0; j <= 0xF; j++)
      {
        gUnknown_0202FE00[(i * 16) + j] = new_var[(i * 16) + j];
      }

    }
    bit <<= 1;
  }

  gUnknownCallback_03000B98 = ApplyBlendedPalettes;
}

void sub_0803F890(u32 rawColor, u32 weight, u32 paletteMask) {

    u32 color = (u16)rawColor;
    u16 mask = paletteMask;
    u32 i;
    u32 j;
    u16 bit = 1;
    u32 inverse;
    IntrFunc callback = ApplyBlendedPalettes;


    if (weight > 0x20)
        weight = 0x20;
    inverse = 0x20 - weight;
    for (i = 0; i <= 0xF; i++) {
        if (mask & bit) {
            for (j = 0; j <= 0xF; j++) {
                gUnknown_0202FC00[i * 16 + j] = (((0x1F & gCopy6280C0202F800[i * 16 + j]) * inverse + (color & 0x1F) * weight) >> 5)
                    | ((((0x3E0 & gCopy6280C0202F800[i * 16 + j]) * inverse + (color & 0x3E0) * weight) >> 5) & 0x3E0)
                    | ((((0x7C00 & gCopy6280C0202F800[i * 16 + j]) * inverse + (color & 0x7C00) * weight) >> 5) & 0x7C00);
            }
        } else {
            for (j = 0; j <= 0xF; j++)
                gUnknown_0202FC00[i * 16 + j] = gCopy6280C0202F800[i * 16 + j];
        }
        bit <<= 1;
    }
    gUnknownCallback_03000B98 = callback;
}

void sub_0803F998(u32 rawColor, u32 weight, u32 paletteMask) {

    u32 color = (u16)rawColor;
    u16 mask = paletteMask;
    u32 i;
    u32 j;
    u16 bit = 1;
    u32 inverse;
    void *palette = (void *)0x05000200;

    if (weight > 0x20)
        weight = 0x20;
    inverse = 0x20 - weight;
    for (i = 0; i <= 0xF; i++) {
        if (mask & bit) {
            for (j = 0; j <= 0xF; j++) {
                gUnknown_0202FC00[i * 16 + j] = (((0x1F & gCopy6280C0202F800[i * 16 + j]) * inverse + (color & 0x1F) * weight) >> 5)
                    | ((((0x3E0 & gCopy6280C0202F800[i * 16 + j]) * inverse + (color & 0x3E0) * weight) >> 5) & 0x3E0)
                    | ((((0x7C00 & gCopy6280C0202F800[i * 16 + j]) * inverse + (color & 0x7C00) * weight) >> 5) & 0x7C00);
            }
        } else {
            for (j = 0; j <= 0xF; j++)
                gUnknown_0202FC00[i * 16 + j] = gCopy6280C0202F800[i * 16 + j];
        }
        bit <<= 1;
    }
    CpuFastSet(gUnknown_0202FC00, palette, 0x80);
}
