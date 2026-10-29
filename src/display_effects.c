#include "display_effects.h"
#include "display_helpers.h"
#include "graphics.h"
#include "state0_callbacks.h"

extern IntrFunc gUnknownCallback_03000B98;

struct EffectWorkPrefix
{
    u8 first;
    u8 second;
    u8 mode;
    u8 unknown03[12];
    u8 unknown0F;
    s8 unknown10;
    s8 unknown11;
};

void sub_0803FAA0(u32 inputFirst, u32 inputSecond, u32 inputMode)
{
    u8 first = inputFirst;
    u8 second = inputSecond;
    u8 mode = inputMode;
    struct EffectWorkPrefix *work = (struct EffectWorkPrefix *)gUnknown_03000440;
    sub_0803F624(gUnknown_03000440, 0x28, 0);
    work->first = first;
    work->second = second;
    work->mode = mode;
    work->unknown0F = 0xFF;
    work->unknown10 = -1;
    work->unknown11 = -1;
    sub_0803F3A8();
    CpuFastSet((const void *)0x084C7F34, (void *)0x050001C0, 8);
    if (mode == 1)
        sub_0803F3E0();
}
