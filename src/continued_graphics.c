#include "graphics.h"
#include "display_effects.h"

#include "continued_blend_work.h"
#include "continued_graphics.h"
extern u32 gUnknown_0300137C;

void sub_08049CC8(void)
{
    volatile u16 *blendAlpha = (volatile u16 *)0x04000052;
    struct ContinuedBlendWork *work = &gContinuedBlendWork_03006F40;
    *blendAlpha = ((work->evb & 63) << 8) | (work->eva & 63);
    *(volatile u16 *)0x04000054 = work->evy & 63;
}

void sub_08049CFC(u32 input, u32 weight, u32 unused2)
{
    u16 color = input;
    BlendPalettes(color, weight);
}

void sub_08049D0C(void)
{
    SnapshotPalettes();
}

void sub_08049EC0(u32 input, u32 weight, u32 maskInput)
{
    u16 color = input;
    u16 mask = maskInput;
    sub_0803F684(color, weight, mask);
}

void sub_08049ED4(u32 input, u32 weight, u32 maskInput)
{
    u16 color = input;
    u16 mask = maskInput;
    sub_0803F998(color, weight, mask);
}

void sub_0804A210(void)
{
    gUnknown_0300137C++;
}
