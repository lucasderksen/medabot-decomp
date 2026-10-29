#include "global.h"
#include "frame.h"
#include "continued_commands.h"
#include "post_dispatch.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03006D20[];
extern u8 gLaterBuffer_030055A0[];
extern u32 sub_080532D4(u32 value);

void sub_0804C1C0(void)
{
    u8 *work;
    u8 *action;
    sub_0804D8CC(2);
    work = gUnknown_030057E0;
    {
        s32 value = sub_0804DBF0(work[0xC94]);
        u32 zero;
        action = gLaterBuffer_03006D20;
        value += 79;
        zero = 0;
        action[10] = value;
        action[0] = work[0xC95];
        action[1] = zero;
    }
    action[2] = 8;
    action[3] = 8;
    work[0xC89] = 1;
}

void sub_0804C210(void)
{
    u8 *work;
    u8 *action;
    u32 zero;
    sub_0804D8CC(3);
    work = gUnknown_030057E0;
    { s32 value = sub_0804DBF0(work[0xC94]); action = gLaterBuffer_03006D20; value += 79; zero = 0; action[10] = value; }
    sub_08052D90(action[10], work[0xC95] & 15);
    action[0] = zero;
    action[2] = work[0xC96];
    work[0xC89] = 1;
}

void sub_0804C26C(void)
{
    u32 value = sub_0804D83C();
    u8 *work = gUnknown_030057E0;
    u8 *argument = work + 0xC94;
    u8 *action;
    u8 *objects;
    *argument = value;
    { s32 result = sub_0804DBF0(*argument); action = gLaterBuffer_03006D20; action[10] = result + 79; }
    objects = (u8 *)gFrameObjects;
    {
        s32 position = ((struct FrameObject *)(objects + action[10] * 64))->positionY >> 8;
        u32 zero = 0;
        *(u16 *)(action + 8) = position;
        objects[action[10] * 64 + 0x28] = zero;
    }
    sub_08047BA8(112);
    work[0xC89] = 1;
}

void sub_0804C4B4(void)
{
    u8 *work = gUnknown_030057E0;
    u32 previous = *(u16 *)(work + 0xC8A);
    u16 *saved = (u16 *)(work + 0xC8C);
    u32 zero = 0;
    *saved = previous;
    { u32 value = sub_0804D83C(); work[0xC94] = value; }
    work[0xCB5] = zero;
    work[0xC89] = 1;
}

void sub_0804C4F8(void)
{
    u8 *work = gUnknown_030057E0;
    u32 previous = *(u16 *)(work + 0xC8A);
    u16 *saved = (u16 *)(work + 0xC8C);
    *saved = previous;
    { u32 value = sub_0804D83C(); work[0xC94] = value; }
    work[0xCB5] = 1;
    work[0xC89] = 1;
}
