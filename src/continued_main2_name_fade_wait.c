#include "gba.h"
#include "frame.h"
#include "frame_objects.h"
#include "object_helpers.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "record_helpers.h"
#include "compression.h"


/* Only observed accessed fields; original and complete layout unknown. */
struct Main2NextContext
{
    u8 byte00;
    u8 unknown01;
    u16 half02;
    u8 unknown04;
    u8 byte05;
    u8 byte06;
    u8 unknown07[0x24];
    u8 byte2B;
    u16 half2C;
    u8 unknown2E[8];
    u16 half36;
    u8 unknown38[0x10];
    u8 byte48;
    u8 byte49;
    u8 byte4A;
    u8 byte4B;
};
#define CONTEXT ((struct Main2NextContext *)gMainContextPointer_03006F74)
#define DISPCNT (*(volatile u16 *)0x04000000)
#define BG1CNT (*(volatile u16 *)0x0400000A)
#define BG2CNT (*(volatile u16 *)0x0400000C)
#define BG3CNT (*(volatile u16 *)0x0400000E)
#define BLDCNT (*(volatile u16 *)0x04000050)
#define BLDY (*(volatile u16 *)0x04000054)

void sub_0805F414(void)
{
    if (CONTEXT->byte00)
    {
        BLDY = CONTEXT->byte00-- >> 1;
    }
    else
    {
        CONTEXT->half02 = 0;
        CONTEXT->byte00 = 0;
        CONTEXT->byte06 = 0;
        CONTEXT->byte48 = 0;
        CONTEXT->byte49 = 0;
        CONTEXT->byte4A = 0;
        CONTEXT->byte4B = 0;
        gFrameObjects[0].flags |= 0x4000;
        gFrameObjects[1].flags |= 0x4000;
        gUnknown_0300137C++;
    }
}
