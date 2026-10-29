#include "continued_commands.h"
#include "input.h"
#include "continued_blend_work.h"

void sub_0804B5FC(void)
{
    u8 *keys = (u8 *)&gNewKeys;
    u8 high;
    u32 keyMask;
    if (keys[0] & 0x40)
    {
        struct ContinuedBlendWork *work = &gContinuedBlendWork_03006F40;
        u16 brightness;
        u32 value;
        volatile u16 *brightnessRegister;
        work->counter += 1.0f;
        work->counter = (float)(s32)((u32)work->counter & 15);
        brightnessRegister = (volatile u16 *)0x04000054;
        value = (u32)work->counter;
        brightness = 63;
        brightness &= value;
        *brightnessRegister = brightness;
    }
    high = keys[1];
    if (high & 1)
    {
        struct ContinuedBlendWork *work = &gContinuedBlendWork_03006F40;
        float first;
        volatile u16 *alpha;
        u32 value;
        work->first += 1.0f;
        first = (float)(s32)((u32)work->first & 15);
        work->first = first;
        alpha = (volatile u16 *)0x04000052;
        value = ((u32)work->second & 63) << 8;
        value |= (u32)first & 63;
        *alpha = value;
    }
    keyMask = 2;
    keyMask &= high;
    if (keyMask)
    {
        struct ContinuedBlendWork *work = &gContinuedBlendWork_03006F40;
        volatile u16 *alpha;
        u32 value;
        work->second += 1.0f;
        work->second = (float)(s32)((u32)work->second & 15);
        alpha = (volatile u16 *)0x04000052;
        value = ((u32)work->second & 63) << 8;
        value |= (u32)work->first & 63;
        *alpha = value;
    }
}
