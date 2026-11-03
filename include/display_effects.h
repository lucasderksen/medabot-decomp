#ifndef GUARD_DISPLAY_EFFECTS_H
#define GUARD_DISPLAY_EFFECTS_H

#include "global.h"

/* Color/mask inputs are reduced to sixteen bits by these observed interfaces. */
void BlendBgPaletteBanksNow(u32 color, u32 weight, u32 paletteMask);
void BlendBgPaletteBanks(u32 color, u32 weight, u32 paletteMask);
void BlendObjPaletteBanks(u32 color, u32 weight, u32 paletteMask);
void BlendObjPaletteBanksNow(u32 color, u32 weight, u32 paletteMask);
void InitDialogue(u32 first, u32 second, u32 mode);

#endif
