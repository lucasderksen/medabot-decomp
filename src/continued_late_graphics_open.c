#include "continued_late_graphics.h"
#include "continued_map_data.h"
#include "continued_graphics.h"
#include "object_numeric_helpers.h"
#include "post_dispatch.h"

void sub_08057440(void)
{
    u8 *work = gContinuedCommandWork_030064A0;
    u8 *cleared = work + 0x66;
    u32 zero = 0;
    *cleared = zero;
    if (work[0x6F] <= 15)
    {
        work[0x6F]++;
        sub_080492A8((const u16 *)((u8 *)gSetupPointer_03006D14 + 0x800),
            (u16 *)0x06002800, 2, 30 - work[0x6F], work[0x6F], 10,
            32, 32, zero, zero);
        sub_08058070(0);
    }
    else
    {
        sub_08048864(127, 0xC004, 0x307, 12, zero);
        sub_08057FD4();
        work[0x65] = zero;
        sub_08047C00();
        sub_0804A210();
    }
}
