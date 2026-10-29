#include "main_callbacks.h"
#include "main_callbacks.h"

u32 sub_0805BC5C(u32 first)
{
    u16 value = first;
    s32 normalized;
    const u32 *table;
    if (value > 160)
        value = 0;
    *(volatile u16 *)0x04000050 = 0x844;
    table = gBlendStepWords_080AF868;
    normalized = (s16)value;
    *(volatile u16 *)0x04000052 = *(const u32 *)((u32)table + (u32)(normalized / 8) * 4) | 0x1000;
    *(volatile u16 *)0x04000054 = 8;
    return (s16)(normalized + 1);
}
