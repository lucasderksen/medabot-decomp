#include "global.h"
#include "main.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "graphics.h"
#include "main_callbacks.h"

#define DISPLAY_CONTROL (*(volatile u16 *)0x04000000)
#define MAIN_FLAGS_BYTE (*(u8 *)&gMainFlagsWord_03001784)

/* Only observed member offsets; no complete original work structure claimed. */
struct Main2CountdownContext
{
    u8 unknown00[5];
    u8 byte05;
    u8 unknown06[0x42];
    u8 byte48;
};
#define MAIN2_CONTEXT ((struct Main2CountdownContext *)gMainContextPointer_03006F74)

void sub_0805C7F8(void)
{
    if (MAIN2_CONTEXT->byte48)
    {
        u32 value = MAIN2_CONTEXT->byte48;
        u8 countdown;
        value--;
        MAIN2_CONTEXT->byte48 = value;
        countdown = value;
        if (countdown != 0)
        {
            u32 selection = MAIN2_CONTEXT->byte05;
            s32 phase = (MAIN2_CONTEXT->byte48 * 4) & 31;
            sub_0805BFEC(selection, phase > 15 ? 0 : 32);
        }
        else
        {
            SnapshotPalettes();
            gUnknown_03000440[0x84] = countdown;
        }
    }
    else if (sub_08074FA4(4) == 0)
    {
        if (gUnknown_03000440[0x84] <= 8)
        {
            u32 component = 31;
            u32 white = (component << 10) | (component << 5) | component;
            sub_0803F684(white, gUnknown_03000440[0x84] * 4, 0xFFFF);
            sub_0803F998(white, gUnknown_03000440[0x84] * 4, 0xFFFF);
            gUnknown_03000440[0x84]++;
        }
        else
        {
            DISPLAY_CONTROL &= 0xFDFF;
            switch (MAIN2_CONTEXT->byte05)
            {
            case 0:
                MAIN_FLAGS_BYTE |= 1;
                gUnknown_0300137C = 8;
                break;
            case 1:
            {
                s32 flags = MAIN_FLAGS_BYTE;
                s32 mask = -3;
                mask &= flags;
                MAIN_FLAGS_BYTE = mask;
                gUnknown_0300137C = 7;
                break;
            }
            }
        }
    }
}


void sub_0805C8EC(void)
{
    s8 index;
    sub_08074B88(0);
    sub_08074DE0(0);
    Unknown_0805DEB0();
    for (index = 0; index <= 15; index++)
        gUnknown_03002B74[index] = 0xFE;
    if (MAIN_FLAGS_BYTE & 1)
    {
        gMainSubstate = 28;
        gUnknown_0300137C = 0;
    }
    else
        sub_080476E8(10);
}
