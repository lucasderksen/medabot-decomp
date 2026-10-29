#ifndef GUARD_DISPLAY_EFFECTS_H
#define GUARD_DISPLAY_EFFECTS_H

#include "global.h"

/* Color/mask inputs are reduced to sixteen bits by these observed interfaces. */
void sub_0803F684(u32 color, u32 weight, u32 paletteMask);
void sub_0803F788(u32 color, u32 weight, u32 paletteMask);
void sub_0803F890(u32 color, u32 weight, u32 paletteMask);
void sub_0803F998(u32 color, u32 weight, u32 paletteMask);
void sub_0803FAA0(u32 first, u32 second, u32 mode);

#endif
