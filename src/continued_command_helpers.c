#include "continued_commands.h"
#include "global.h"
#include "object_numeric_helpers.h"
#include "object_helpers.h"
#include "continued_graphics.h"

extern u8 gUnknown_030057E0[];
extern u8 gContinuedArguments_03006474[];
extern u8 gUnknown_0300058C[];
extern void (*const gContinuedStateCallbacks_083D2630[])(void);
extern void sub_0804DDCC(void);

void ReadBankedScriptArgs(u32 count)
{
    s32 i;
    u8 limit = count;
    for (i = 0; i < limit; i++)
        gContinuedArguments_03006474[i] = ReadBankedScriptByte();
}

void sub_0804DB80(void)
{
    u8 *work;
    u32 value;
    ResetFrameObjectSlot(48);
    ResetFrameObjectSlot(90);
    work = gUnknown_030057E0;
    work[0xC76] = 0;
    value = work[0xC5E];
    work[0xC5D] = value;
}

void ClearScriptObjectSlot(u32 index)
{
    u8 narrowed = index;
    u32 address = (u32)gUnknown_030057E0;
    address += 0xCA4;
    ((u8 *)address)[narrowed] = 0;
}

void SetScriptObjectSlot(u32 index, u32 value)
{
    u8 narrowedIndex = index;
    u8 narrowedValue = value;
    u32 address = (u32)gUnknown_030057E0;
    address += 0xCA4;
    ((u8 *)address)[narrowedIndex] = narrowedValue + 1;
}

s32 GetScriptObjectSlot(u32 index)
{
    u8 narrowed = index;
    u32 address = (u32)gUnknown_030057E0;
    address += 0xCA4;
    return ((u8 *)address)[narrowed] - 1;
}

void sub_0804DC0C(void)
{
    gContinuedStateCallbacks_083D2630[gUnknown_030057E0[0xC92]]();
}

void sub_0804DC34(void) { }
void sub_0804DCF8(void) { sub_08050290(); }
void sub_0804DD04(void)
{
    if (sub_08041CA4())
        sub_08050290();
}

void sub_0804DD18(void)
{
    u8 *work = gUnknown_030057E0;
    if (work[0xC94])
        work[0xC94]--;
    else
        sub_08050290();
}

struct InputBits
{
    u32 a : 1;
    u32 unknown1 : 2;
    u32 start : 1;
    u32 unknown4 : 28;
};

void sub_0804DD3C(void)
{
    struct InputBits keys = *(struct InputBits *)gUnknown_0300058C;
    u32 pressed = keys.a;
    pressed |= keys.start;
    if (pressed)
        sub_08050290();
}

void sub_0804DD5C(void)
{
    if (StepPaletteFadeToColor(0))
        sub_08050290();
}
void sub_0804DD70(void)
{
    if (StepPaletteFadeToColor(0))
        sub_08050290();
}
void sub_0804DD84(void)
{
    if (StepPaletteFadeToColor(0x7FFF))
        sub_08050290();
}
void sub_0804DD9C(void)
{
    if (StepPaletteFadeToColor(0x7FFF))
        sub_08050290();
}
void sub_0804DDB4(void) { sub_0804DDCC(); }
void sub_0804DDC0(void) { sub_0804DDCC(); }
