/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "gba.h"
#include "record_helpers.h"
#include "state0_display.h"


void sub_0800147C(const u16 *sourceArg, u16 *destinationArg, u16 colorValue, u32 tintWeight);

void sub_0800147C(const u16 *sourceArg, u16 *destinationArg, u16 colorValue, u32 tintWeight) {

    u16 tintColor = colorValue;
    s32 sourceWeight;
    u32 colorIndex;
    u16 redMask;
    u16 greenMask;
    u16 blueMask;
    u32 weightedRed;
    u32 weightedGreen;
    u32 weightedBlue;
    u32 mixedColor;
    u32 greenComponent;
    u32 component;
    u16 sourceColor;
    const u16 *source;
    u16 *destination;
    if (tintWeight > 32)
    {
        tintWeight = 32;
    }
    sourceWeight = 32 - tintWeight;
    colorIndex = 0;
    redMask = 31;
    weightedRed = (tintColor & redMask) * tintWeight;
    greenMask = 0x3E0;
    blueMask = 0x7C00;
    source = sourceArg;
    destination = destinationArg;
    weightedGreen = (tintColor & greenMask) * tintWeight;
    weightedBlue = (tintColor & blueMask) * tintWeight;
    do
    {
        sourceColor = *source;
        component = redMask & sourceColor;
        mixedColor = (weightedRed + component * sourceWeight) >> 5;
        greenComponent = greenMask & sourceColor;
        greenComponent *= sourceWeight;
        greenComponent += weightedGreen;
        greenComponent >>= 5;
        greenComponent &= greenMask;
        mixedColor |= greenComponent;
        component = blueMask & sourceColor;
        component *= sourceWeight;
        component = (weightedBlue + component) >> 5;
        component &= blueMask;
        mixedColor |= component;
        *destination = mixedColor;
        source++;
        destination++;
        colorIndex++;
    }
    while (colorIndex <= 15);
}
