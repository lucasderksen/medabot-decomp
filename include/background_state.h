#ifndef GUARD_BACKGROUND_STATE_H
#define GUARD_BACKGROUND_STATE_H

#include "global.h"

/* Partial view of the observed background work fields. */
struct BackgroundState
{
    u8 unknown00[8];
    s16 pa, pb, pc, pd;
    s32 dx, dy;
    u8 unknown18[4];
    u16 unknown1C;
    u16 scrollX[3];
    u16 unknown24;
    u16 scrollY[3];
    s16 x, y;
    u16 unknown30;
    s16 scaleX, scaleY;
    u16 angle;
};
extern struct BackgroundState gBackgroundState_03005310;

extern const s16 gAffineSineTable_080AE8F4[];

extern const s16 gScrollOscillationSines_083D6A2C[];

#endif
