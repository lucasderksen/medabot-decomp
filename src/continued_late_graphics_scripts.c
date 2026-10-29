#include "continued_late_graphics.h"
#include "post_dispatch.h"


void sub_08057CB0(void)
{
    const void *const *scripts = gStateScripts_084144B4;
    u8 *work = gContinuedCommandWork_030064A0;
    u8 *counter = work + 0x70;
    u32 index = *counter;
    index += 130;
    if (sub_08047C24(1, 1, 0, scripts[index]))
    {
        (*counter)++;
        if (*counter <= 5)
            gUnknown_0300137C--;
        else
            gUnknown_0300137C = 2;
    }
}
