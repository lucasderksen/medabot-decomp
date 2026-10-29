#include "continued_late_graphics.h"
#include "continued_graphics.h"
#include "object_numeric_helpers.h"
#include "post_dispatch.h"


void sub_08057AD0(void)
{
    if (sub_08049E08(0))
    {
        sub_08048864(127, 0xC004, 0x307, 12, 0);
        sub_08057FD4();
        gUnknown_0300137C = 2;
    }
}

void sub_08057D04(void)
{
    sub_08047C00();
    sub_0804A210();
}

void sub_08057D14(void)
{
    if (sub_08047C24(1, 1, 0, gStateScripts_084144B4[129]))
        gUnknown_0300137C = 2;
}

void sub_08057D40(void)
{
    sub_08047C00();
    sub_0804A210();
}

void sub_08057D50(void)
{
    if (sub_08047C24(1, 1, 0, gStateScripts_084144B4[128]))
        gUnknown_0300137C = 2;
}
