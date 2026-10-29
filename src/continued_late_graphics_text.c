#include "continued_late_graphics.h"
#include "continued_graphics.h"
#include "post_dispatch.h"

void sub_08057B6C(void)
{
    u8 *work = gContinuedCommandWork_030064A0;
    if (work[0x65] == 0)
    {
        u32 identifier = 85;
        switch (work[0x70])
        {
        case 0:
            sub_08047CE4(0, sub_08047BDC(identifier));
            break;
        case 1:
            sub_08047CE4(0, sub_08047BEC(0, identifier));
            break;
        case 2:
            sub_08047CE4(1, sub_08047BEC(1, identifier));
            break;
        case 3:
            sub_08047CE4(2, sub_08047BEC(2, identifier));
            break;
        case 4:
            sub_08047CE4(3, sub_08047BEC(3, identifier));
            break;
        case 5:
            sub_08047CE4(0, sub_08047BDC(identifier));
            break;
        }
    }
    else if (work[0x65] == 2)
    {
        u32 identifier = 11;
        switch (work[0x70])
        {
        case 0:
            sub_08047CE4(0, sub_08047BDC(identifier));
            break;
        case 1:
            sub_08047CE4(0, sub_08047BEC(0, identifier));
            break;
        case 2:
            sub_08047CE4(1, sub_08047BEC(1, identifier));
            break;
        case 3:
            sub_08047CE4(2, sub_08047BEC(2, identifier));
            break;
        case 4:
            sub_08047CE4(3, sub_08047BEC(3, identifier));
            break;
        case 5:
            sub_08047CE4(0, sub_08047BDC(identifier));
            break;
        }
    }
    else if (work[0x65] == 3)
    {
        u32 identifier = 107;
        switch (work[0x70])
        {
        case 0:
            sub_08047CE4(0, sub_08047BDC(identifier));
            break;
        case 1:
            sub_08047CE4(0, sub_08047BEC(0, identifier));
            break;
        case 2:
            sub_08047CE4(1, sub_08047BEC(1, identifier));
            break;
        case 3:
            sub_08047CE4(2, sub_08047BEC(2, identifier));
            break;
        case 4:
            sub_08047CE4(3, sub_08047BEC(3, identifier));
            break;
        case 5:
            sub_08047CE4(0, sub_08047BDC(identifier));
            break;
        }
    }
    if (gContinuedCommandWork_030064A0[0x70] == 0)
        sub_08047C00();
    sub_0804A210();
}
