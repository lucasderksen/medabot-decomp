#include "global.h"
#include "frame.h"
#include "continued_commands.h"
#include "later_graphics.h"

struct FlagFrameView
{
    u16 flags;
    u8 unknown02[0x30];
    u16 savedFlags;
    u8 unknown34[0x0C];
};

void sub_080507BC(u32 index, u32 value)
{
    struct FrameObject *base = gFrameObjects;
    base[index].priority = value;
}

void sub_080507CC(u32 indexWord, u32 value)
{
    u8 index = indexWord;
    s32 mapped = sub_0804DBF0(index);
    struct FrameObject *base = gFrameObjects;
    mapped += 79;
    base[mapped].priority = value;
}

void sub_080507EC(u32 index, u32 value)
{
    struct FlagFrameView *base = (struct FlagFrameView *)gFrameObjects;
    struct FlagFrameView *object = &base[index];
    u32 flags = (object->savedFlags & 0xF3FF) | (value << 10);
    object->flags = flags;
    object->savedFlags = flags;
}

void sub_0805080C(u32 indexWord, u32 valueWord)
{
    u8 index = indexWord;
    u8 value = valueWord;
    sub_080507EC(sub_0804DBF0(index) + 79, value);
}
