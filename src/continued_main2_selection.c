#include "global.h"
#include "main.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "frame.h"
#include "main_callbacks.h"

/* Only accessed offsets are represented; no complete context extent is known. */
struct Main2SelectionContext
{
    u8 unknown00[2];
    u16 halfword02;
    u8 byte04, byte05;
    u8 unknown06[0x34];
    s16 halfword3A;
    u8 unknown3C[0x0C];
    u8 byte48;
};

#define MAIN2_CONTEXT ((struct Main2SelectionContext *)gMainContextPointer_03006F74)

void sub_0805C454(void)
{
    MAIN2_CONTEXT->halfword3A = sub_0805BC5C(MAIN2_CONTEXT->halfword3A);
    sub_0805BFEC(MAIN2_CONTEXT->byte05, gFrameCounter & 31);
    if (gUnknown_0300058C[0] & 0x40)
    {
        sub_08074DE0(2);
        if (MAIN2_CONTEXT->byte05 == MAIN2_CONTEXT->byte04)
            MAIN2_CONTEXT->byte05 = 2;
        else
            MAIN2_CONTEXT->byte05--;
    }
    if (gUnknown_0300058C[0] & 0x80)
    {
        sub_08074DE0(2);
        if (MAIN2_CONTEXT->byte05 == 2)
            MAIN2_CONTEXT->byte05 = MAIN2_CONTEXT->byte04;
        else
            MAIN2_CONTEXT->byte05++;
    }
    if (gUnknown_0300058C[0] & 1)
    {
        sub_08074DE0(4);
        if (MAIN2_CONTEXT->byte05 == 2)
        {
            MAIN2_CONTEXT->byte05 = 0;
            MAIN2_CONTEXT->halfword02 = 20;
            sub_0805BF14(gFrameCounter & 31);
            sub_0805BD44(MAIN2_CONTEXT->byte05);
            sub_0805BE0C(MAIN2_CONTEXT->byte05);
            sub_0805BFEC(3, 0);
            gFrameObjects[14].screenY = MAIN2_CONTEXT->byte05 * 24 + 80;
            gFrameObjects[14].flags |= 0x4000;
            gUnknown_0300137C++;
        }
        else
        {
            MAIN2_CONTEXT->byte48 = 45;
            gUnknown_0300137C = 6;
        }
    }
}
