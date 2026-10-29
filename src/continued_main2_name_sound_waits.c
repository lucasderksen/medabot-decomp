#include "global.h"
#include "gba.h"
#include "main.h"
#include "frame.h"
#include "object_helpers.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "effect_work.h"
#include "display_effects.h"
#include "input.h"


/* Partial observed access view, not an original or full allocation layout. */
struct Main2SoundContext
{
    u8 byte00;
    u8 unknown01;
    u16 half02;
    u8 unknown04;
    u8 byte05;
    u8 unknown06[0x25];
    u8 byte2B;
    u16 half2C;
    u8 unknown2E[0x1A];
    u8 byte48;
    u8 byte49;
    u8 byte4A;
    u8 byte4B;
};
#define CONTEXT ((struct Main2SoundContext *)gMainContextPointer_03006F74)
#define DISPCNT (*(volatile u16 *)0x04000000)
#define BG1CNT (*(volatile u16 *)0x0400000A)
#define BLDY (*(volatile u16 *)0x04000054)
#define REPEATED_BYTE (*(u8 *)&gRepeatedKeys)
#define NEW_BYTE (*(u8 *)&gNewKeys)

void sub_0805F8E0(void)
{
    if (CONTEXT->byte00 == 1)
        sub_08074DE0(CONTEXT->byte49 ? 5 : 4);
    if (CONTEXT->byte00 != 32)
    {
        CONTEXT->byte00++;
        BLDY = CONTEXT->byte00 >> 1;
    }
    else
    {
        DISPCNT &= 0xFDFF;
        gMainState = 3;
        gMainSubstate = 2;
        gUnknown_0300137C = 0;
        gMain2Byte_03007008 = 1;
    }
}

void sub_0805F960(void)
{
    if (sub_0803FB3C(gMain2ScriptSlots_0848521C[3]))
        gUnknown_0300137C++;
}

void sub_0805F984(void)
{
    if (sub_08041674())
    {
        CONTEXT->half02 = 0;
        sub_0803FB0C();
        if (gUnknown_03000440[0x2A] == 0)
            gUnknown_0300137C = 9;
        else
            gUnknown_0300137C++;
    }
}
