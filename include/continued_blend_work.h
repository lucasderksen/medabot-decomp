#ifndef GUARD_CONTINUED_BLEND_WORK_H
#define GUARD_CONTINUED_BLEND_WORK_H

#include "global.h"

/* Partial observed blend-work layout; field roles remain provisional. */
struct ContinuedBlendWork
{
    u8 flags, mode, state, eva, evb, evy;
    u8 targetA, targetB, targetC, originalA, originalB, unknown0B;
    float first, second, counter, incrementA, incrementB, increment;
    float paletteWeight, paletteStart, paletteEnd, paletteStep;
};
extern struct ContinuedBlendWork gContinuedBlendWork_03006F40;

#endif
