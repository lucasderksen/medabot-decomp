#include "interrupts.h"
#include "continued_graphics.h"
#include "continued_blend_work.h"

extern u8 gLaterBuffer_03005350[];
u32 sub_08049A6C(void);

u32 sub_08049E08(u32 input)
{
    u16 color = input;
    u32 result = 0;
    u32 address;
    u16 mask;
    u16 *firstMask, *secondMask;
    struct ContinuedBlendWork *work;
    sub_08049A6C();
    address = (u32)gLaterBuffer_03005350;
    firstMask = (u16 *)(address + 0x20A);
    mask = 0xFFFF;
    *firstMask = mask;
    secondMask = (u16 *)(address + 0x20C);
    mask = 0xBFFF;
    *secondMask = mask;
    work = &gContinuedBlendWork_03006F40;
    sub_08049EC0(color, (u32)work->paletteWeight, *firstMask);
    sub_08049ED4(color, (u32)work->paletteWeight, *secondMask);
    work->paletteWeight -= work->paletteStep;
    if (work->paletteStep > 0.0f)
    {
        if (!(work->paletteWeight < work->paletteEnd))
            goto done;
    }
    else if (!(work->paletteWeight > work->paletteEnd))
        goto done;
    gUnknownCallback_030017F0 = DummyInterruptHandler;
    result = 1;
done:
    return result;
}
