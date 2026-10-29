#include "global.h"
#include "main.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "continued_late_graphics.h"
#include "main_callbacks.h"

#define DISPLAY_CONTROL (*(volatile u16 *)0x04000000)
#define MAIN_FLAGS_BYTE (*(u8 *)&gMainFlagsWord_03001784)

struct Main2StateContext
{
    u8 unknown00[4];
    u8 byte04, byte05;
    u8 unknown06[0x34];
    u16 halfword3A;
};

void sub_0805C410(void)
{
    if (sub_08065710((u8 *)gMainContextPointer_03006F74 + 0x50))
    {
        gUnknown_0300137C++;
        ((struct Main2StateContext *)gMainContextPointer_03006F74)->halfword3A = 0;
        ((struct Main2StateContext *)gMainContextPointer_03006F74)->halfword3A = sub_0805BC5C(0);
        DISPLAY_CONTROL |= 0x400;
    }
}
