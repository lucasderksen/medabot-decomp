#include "continued_late_graphics.h"
#include "continued_commands.h"
#include "continued_map.h"
#include "object_numeric_helpers.h"


void sub_08057B0C(void)
{
    u8 *work = gContinuedCommandWork_030064A0;
    u8 *selected = work + 0x65;
    if (*selected != 2)
    {
        sub_0804B248();
        sub_08057FB4();
    }
    sub_08048888(127);
    if (*selected == 0)
        sub_08047878(65, 0);
    else if (*selected == 1)
        sub_08047878(67, 0);
    else if (*selected == 2)
        gUnknown_0300137C = 5;
    else if (*selected == 3)
        sub_08047878(66, 0);
}
