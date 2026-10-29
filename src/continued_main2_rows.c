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

void sub_0805C2DC(void)
{
    s32 result;
    DISPLAY_CONTROL |= 0x100;
    DISPLAY_CONTROL |= 0x200;
    DISPLAY_CONTROL |= 0x800;
    DISPLAY_CONTROL |= 0x1000;
    result = MAIN_FLAGS_BYTE;
    result &= -2;
    MAIN_FLAGS_BYTE = result;
    result = sub_0805DEC8();
    if (result != 0)
    {
        if (result < 0)
        {
        gMainSubstate = 9;
        gUnknown_0300137C = 0;
        return;
    
        }
        else
        {
        s32 row;
        s32 count;
        for (row = 0; row <= 1; row++)
        {
            u16 *destination;
            u32 offset = ((*(volatile u16 *)0x04000008) >> 8 & 31) << 11;
            count = (row + 1) * 64;
            destination = (u16 *)(0x06000012 + offset + count);
            for (count = 11; count >= 0; count--)
                *destination++ = 0;
        }
        ((struct Main2StateContext *)gMainContextPointer_03006F74)->byte05 = 1;
        ((struct Main2StateContext *)gMainContextPointer_03006F74)->byte04 = 1;
        gMainByte_03001788 = 0;
        gMainByte_03001360 = 0;
        gMainByte_03000B94 = 0;
    
        }
    }
    else
    {
        ((struct Main2StateContext *)gMainContextPointer_03006F74)->byte05 = result;
        ((struct Main2StateContext *)gMainContextPointer_03006F74)->byte04 = result;
        MAIN_FLAGS_BYTE |= 1;
    
    }
    sub_0805BFEC(((struct Main2StateContext *)gMainContextPointer_03006F74)->byte05, gFrameCounter & 31);
    sub_0805BE0C(3);
    gUnknown_0300137C++;
}

