#include "global.h"
#include "continued_commands.h"

void sub_0805218C(u32 indexWord, u32 valueWord, void *record)
{
    u8 index = indexWord;
    u8 value = valueWord;
    sub_08052D90(index, value);
    ((u8 *)record)[5] = value;
}
