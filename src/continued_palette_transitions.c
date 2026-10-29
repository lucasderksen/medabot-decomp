#include "gba.h"

/* The observed call converts float to double and supplies R1/R2, although the
 * callee consumes only the low word. An unprototyped declaration models that
 * ABI here; the original declaration history is not established. */
void BlendPalettes();
void sub_08049D0C(void);
void sub_080497E0(u8 control, u16 targets, u8 type, u8 frames, u8 frames2, u8 frames3, u8 first, u8 second, u8 third);

#include "continued_blend_work.h"
#include "continued_graphics.h"

void sub_08049D18(u32 input, float start, float end, float steps)
{
    u16 color = input;
    BlendPalettes(color, start);
    gContinuedBlendWork_03006F40.paletteWeight = start;
    gContinuedBlendWork_03006F40.paletteStart = start;
    gContinuedBlendWork_03006F40.paletteEnd = end;
    gContinuedBlendWork_03006F40.paletteStep = (start - end) / steps;
    sub_080497E0(64, 0x2F00, 5, (u8)steps, (u8)steps, (u8)steps, 12, 10, 0);
}

void sub_08049D90(u32 input, float start, float end, float steps)
{
    u16 color = input;
    sub_08049D0C();
    BlendPalettes(color, start);
    gContinuedBlendWork_03006F40.paletteWeight = start;
    gContinuedBlendWork_03006F40.paletteStart = start;
    gContinuedBlendWork_03006F40.paletteEnd = end;
    gContinuedBlendWork_03006F40.paletteStep = (start - end) / steps;
    sub_080497E0(64, 0x2F00, 4, (u8)steps, (u8)steps, (u8)steps, 16, 16, 0);
}
