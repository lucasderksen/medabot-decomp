#include "global.h"
#include "continued_commands.h"


void sub_08050168(u32 inputIndex)
{
    u8 index = inputIndex;
    s32 i;
    for (i = 0; i < sub_08051940(index); i++)
        sub_08049440(index);
}
