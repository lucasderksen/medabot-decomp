#include "rom_libc.h"
#include "global.h"
#include "gba.h"
#include "main.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "object_helpers.h"
#include "frame_objects.h"
#include "compression.h"
#include "main_callbacks.h"

#define DISPLAY_CONTROL (*(volatile u16 *)0x04000000)

void sub_0805C9C4(void)
{
    u32 zero = 0;
    CpuFastSet(&zero, VRAM, 0x01006000);
    sub_08040CD0(0, 128);
    sub_080415BC();
    DISPLAY_CONTROL = 0x60;
    CpuFastSet((const void *)0x084E43D8, (void *)0x0202F9E0, 8);
    LeDecompress((const u8 *)0x084C8034, (void *)0x06017400);
    sub_0803FAA0(1, 2, 0);
    DISPLAY_CONTROL |= 0x1000;
    gUnknown_0300137C++;
}

void sub_0805CA3C(void)
{
    u8 message[83];
    memcpy(message, gMain2LocalMessage_080AF8CD, sizeof(message));
    if (sub_0803FB3C(message))
    {
        sub_080415E8(1, 22, 7);
        gUnknown_0300137C++;
    }
}

void sub_0805CA74(void)
{
    if (sub_08041674())
    {
        if (gUnknown_03000440[0x2A] == 0)
            gUnknown_0300137C++;
        else
            gUnknown_0300137C += 2;
    }
}

void sub_0805CAA8(void)
{
    if (sub_08041CA4())
        sub_080476E8(10);
}

void sub_0805CABC(void)
{
    if (sub_08041CA4())
    {
        gUnknown_0300137C++;
        sub_080656DC((u8 *)gMainContextPointer_03006F74 + 0x50, 0, 0, 1, 192);
    }
}

void sub_0805CAF4(void)
{
    if (sub_08065710((u8 *)gMainContextPointer_03006F74 + 0x50))
    {
        gMainSubstate = 3;
        gUnknown_0300137C = 0;
    }
}

void sub_0805CB20(void)
{
    struct Main2LocalCallbackView callbacks = gMain2LocalCallbackWords_080AF920;
    callbacks.items[gUnknown_0300137C]();
}
