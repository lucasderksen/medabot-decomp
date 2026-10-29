#include "global.h"
#include "gba.h"
#include "main.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "object_helpers.h"
#include "frame_objects.h"
#include "display_effects.h"
#include "equipment_helpers.h"
#include "main_callbacks.h"

#define CONTEXT ((u8 *)gMainContextPointer_03006F74)
#define DISPLAY_CONTROL (*(volatile u16 *)0x04000000)

void sub_0805CED0(void)
{
    if (gUnknown_03000440[0x84] <= 8)
    {
        if (CONTEXT[6] == 0)
            sub_0803F684(0, 32 - gUnknown_03000440[0x84] * 4, 0x3FFF);
        else
            sub_0803F684(0, 32 - gUnknown_03000440[0x84] * 4, 0xFFFF);
        sub_0803F998(0, 32 - gUnknown_03000440[0x84] * 4, 0xFFFF);
        gUnknown_03000440[0x84]++;
    }
    else
    {
        sub_0803FAA0(1, 2, 0);
        gUnknown_0300137C++;
    }
}

void sub_0805CF58(void)
{
    u8 *context;
    u32 identifier;
    sub_0805CB90(gFrameCounter);
    sub_08041C14(83, *(u8 *)&gFrameCounter, 84);
    context = CONTEXT;
    if (context[0x10])
    {
        const u8 *records = (const u8 *)0x02040000;
        u32 index = context[0xC];
        identifier = records[index * 4];
    }
    else
        identifier = 63;
    if (sub_0803FB3C(gMain2Scripts_08484C60[identifier]))
        gUnknown_0300137C++;
}
