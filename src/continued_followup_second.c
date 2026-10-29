#include "global.h"
#include "frame.h"
#include "continued_commands.h"
extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_030055A0[];

void sub_0804C7DC(void)
{
    u8 *work;
    sub_0804D8CC(2);
    work = gUnknown_030057E0;
    if (work[0xC94] == 0)
    {
        work[0xCBC] -= work[0xC95];
        if ((s8)work[0xCBC] < 0)
            work[0xCBC] = 0;
    }
    else
    {
        work[0xCBD] -= work[0xC95];
        if ((s8)work[0xCBD] < 0)
            work[0xCBD] = 0;
    }
}

void sub_0804C868(void)
{
    struct ObjectEntry { u16 value; u16 unknown; };
    u32 value = sub_0804D83C();
    u8 *work = gUnknown_030057E0;
    u8 *initial = work + 0xC94;
    s32 index;
    const struct ObjectEntry *entries;
    u8 *objects;
    u32 zero;
    u8 *argument;
    u32 eight;
    *initial = value;
    index = 0;
    entries = (const struct ObjectEntry *)gLaterBuffer_030055A0;
    objects = (u8 *)gFrameObjects;
    zero = 0;
    argument = initial;
    eight = 8;
    do
    {
        u8 selected = index;
        if (sub_0804DBF0(selected) != -1)
        {
            s32 entry = sub_0804DBF0(selected);
            entry += 79;
            if (entries[entry].value != 0)
            {
                {
                    s32 frame = sub_0804DBF0(selected);
                    u8 *object;
                    u32 argumentValue;
                    frame += 79;
                    object = (u8 *)(frame * 64 + (u32)objects);
                    argumentValue = *argument;
                    object[0x26] = argumentValue;
                }
                { s32 frame = sub_0804DBF0(selected); frame += 79; objects[frame * 64 + 0x27] = zero; }
                { s32 frame = sub_0804DBF0(selected); frame += 79; objects[frame * 64 + 0x28] = eight; }
                { s32 frame = sub_0804DBF0(selected); frame += 79; objects[frame * 64 + 0x29] = eight; }
            }
        }
        index++;
    } while (index <= 3);
    gUnknown_030057E0[0xC89] = 1;
}
