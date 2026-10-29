#include "continued_commands.h"
#include "continued_graphics.h"
extern u8 gUnknown_030057E0[];

void sub_0804B858(void)
{
    u32 value = sub_0804D83C();
    u8 *work = gUnknown_030057E0;
    s32 steps;
    work[0xC94] = value;
    steps = work[0xC94];
    if (steps <= 1) steps = 1;
    if (steps > 15) steps = 16;
    sub_08049D90(0, 0.0f, 32.0f, (float)steps);
    work[0xC89] = 1;
}
void sub_0804B8AC(void)
{
    u32 value = sub_0804D83C();
    u8 *work = gUnknown_030057E0;
    s32 steps;
    work[0xC94] = value;
    steps = work[0xC94];
    if (steps <= 1) steps = 1;
    if (steps > 15) steps = 16;
    sub_08049D18(0, 32.0f, 0.0f, (float)steps);
    work[0xC89] = 1;
}
void sub_0804B900(void)
{
    u32 value = sub_0804D83C();
    u8 *work = gUnknown_030057E0;
    s32 steps;
    work[0xC94] = value;
    steps = work[0xC94];
    if (steps <= 1) steps = 1;
    if (steps > 15) steps = 16;
    sub_08049D90(32767, 0.0f, 32.0f, (float)steps);
    work[0xC89] = 1;
}
void sub_0804B958(void)
{
    u32 value = sub_0804D83C();
    u8 *work = gUnknown_030057E0;
    s32 steps;
    work[0xC94] = value;
    steps = work[0xC94];
    if (steps <= 1) steps = 1;
    if (steps > 15) steps = 16;
    sub_08049D18(32767, 32.0f, 0.0f, (float)steps);
    work[0xC89] = 1;
}
