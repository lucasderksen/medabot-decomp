#include "global.h"
#include "frame.h"
#include "continued_commands.h"
#include "packed_fields.h"

void sub_0805076C(u32 indexWord, u32 valueWord)
{
    u8 index = indexWord;
    u8 value = valueWord;
    struct FrameObject *base;
    s32 mapped;
    {
        s32 first = sub_0804DBF0(index);
        base = gFrameObjects;
        first += 79;
        base[first].commandDelay = value;
    }
    mapped = sub_0804DBF0(index);
    {
        u32 frame = sub_08050320(index, value);
        mapped += 79;
        base[mapped].frameAndGroup = (u8)frame;
    }
}
