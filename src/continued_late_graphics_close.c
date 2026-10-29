#include "continued_late_graphics.h"
#include "continued_map_data.h"
#include "continued_graphics.h"
#include "compression.h"

void sub_080575DC(void)
{
    u32 address = (u32)gContinuedCommandWork_030064A0;
    u8 *counter = (u8 *)(address + 0x6F);
    if (*counter)
    {
        void **setup = &gSetupPointer_03006D14;
        const u16 *source = (const u16 *)((u8 *)*setup + 0x1000);
        u16 *destination = (u16 *)0x06002800;
        sub_080492A8(source, destination,
            2, 30 - *counter, 1, 10, 32, 32, 0, 0);
        sub_080492A8((const u16 *)((u8 *)*setup + 0x800), destination,
            2, 31 - *counter, *counter, 10, 32, 32, 0, 0);
        sub_08058070(1);
        (*counter)--;
    }
    else
    {
        LeDecompress(gUnknownBytes_084C22E8, (void *)0x06002100);
        sub_0804A210();
    }
}
