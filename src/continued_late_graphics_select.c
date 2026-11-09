#include "continued_late_graphics.h"
#include "continued_graphics.h"
#include "input.h"
#include "object_numeric_helpers.h"
#include "post_dispatch.h"

void sub_080574D4(void)
{
    u8 *work = gContinuedCommandWork_030064A0;
    u8 *counter = work + 0x67;
    u32 choice;
    (*counter)++;
    sub_08057FD4();
    sub_08057F1C(4);
    if (*(u8 *)&gNewKeys & 1)
    {
        choice = sub_08057D80(work[0x65]);
        if (choice)
        {
            *counter = 0;
            sub_08057FD4();
            sub_08047BA8(6);
            switch (choice)
            {
            case 1:
                break;
            case 2:
                gContinuedCommandWork_030064A0[0x70] = 0;
                gNestedCallbackIndex = 11;
                break;
            case 3:
                gNestedCallbackIndex = 13;
                break;
            case 4: case 5: case 6:
                gNestedCallbackIndex = 15;
                break;
            }
        }
        else
        {
            sub_080492A8((const u16 *)0x06002800, (u16 *)(work + 0x72),
                0, 0, 30, 20, 32, 32, 0, 0);
            sub_08047BA8(4);
            gNestedCallbackIndex = 10;
        }
    }
    else if (*(u8 *)&gNewKeys & 2)
    {
        sub_08047BA8(5);
        ResetFrameObjectSlot(127);
        work[0x6F] = 16;
        sub_0804A210();
    }
}
