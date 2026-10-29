#include "graphics.h"
#include "interrupts.h"

extern u16 gSavedPalettes[512];
extern u16 gBlendedPalettes[512];

/* Blend the saved OBJ and BG RGB555 palettes, then queue their transfer. */
void BlendPalettes(u16 colorValue, u32 tintWeight)
{
    u16 tintColor = colorValue;
    s32 sourceWeight;
    u32 colorIndex;
    u32 lastColor;
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
    if (tintWeight > 32)
    {
        tintWeight = 32;
    }
    sourceWeight = 32 - tintWeight;
    colorIndex = 0;
    lastColor = 511;
    redMask = 31;
    weightedRed = (tintColor & redMask) * tintWeight;
    greenMask = 0x3E0;
    blueMask = 0x7C00;
    weightedGreen = (tintColor & greenMask) * tintWeight;
    weightedBlue = (tintColor & blueMask) * tintWeight;
    do
    {
        destination = &gBlendedPalettes[colorIndex];
        sourceColor = gSavedPalettes[colorIndex];
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
    gUnknownCallback_03000B98 = ApplyBlendedPalettes;
}
