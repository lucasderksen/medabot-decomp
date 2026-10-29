#include "global.h"
#include "continued_commands.h"

extern u8 gUnknown_030057E0[];

void sub_08050290(void)
{
    u8 *work = gUnknown_030057E0;
    work[0xC93] = 0;
    work[0xC89] = 0;
}
