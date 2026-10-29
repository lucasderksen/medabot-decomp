#include "global.h"
#include "main.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "object_helpers.h"
#include "frame.h"
#include "main_callbacks.h"

/* Accessed offsets and widths only; no complete original layout is claimed. */
struct Main2ChoiceContext
{
    u8 unknown00[2];
    u16 halfword02;
    u8 byte04, byte05;
    u8 unknown06[0x34];
    s16 halfword3A;
};

#define MAIN2_CONTEXT ((struct Main2ChoiceContext *)gMainContextPointer_03006F74)

void sub_0805C574(void)
{
    u32 keys;
    MAIN2_CONTEXT->halfword3A = sub_0805BC5C(MAIN2_CONTEXT->halfword3A);
    sub_08041C14(14, *(u8 *)&gFrameCounter, 32);
    sub_0805BF14(gFrameCounter & 31);
    sub_0805BCB0(MAIN2_CONTEXT->byte05, (u8)(20 - *(u8 *)&MAIN2_CONTEXT->halfword02));
    if (MAIN2_CONTEXT->halfword02)
        MAIN2_CONTEXT->halfword02--;
    if (gUnknown_0300058C[0] & 0x40)
    {
        sub_08074B88(1);
        sub_08074DE0(2);
        if (MAIN2_CONTEXT->byte05 == 0)
            MAIN2_CONTEXT->byte05 = 2;
        else
            MAIN2_CONTEXT->byte05--;
    if (MAIN2_CONTEXT->byte05 == 2)
        sub_08074B88(gMain2SoundChoices_080AF8CA[gMainByte_03000B94]);
    MAIN2_CONTEXT->halfword02 = 20;
    }
    else if (gUnknown_0300058C[0] & 0x80)
    {
        sub_08074B88(1);
        sub_08074DE0(2);
        if (MAIN2_CONTEXT->byte05 == 2)
            MAIN2_CONTEXT->byte05 = 0;
        else
            MAIN2_CONTEXT->byte05++;
    if (MAIN2_CONTEXT->byte05 == 2)
        sub_08074B88(gMain2SoundChoices_080AF8CA[gMainByte_03000B94]);
    MAIN2_CONTEXT->halfword02 = 20;
    }
    else
    {
        switch (MAIN2_CONTEXT->byte05)
        {
        case 0:
            if (gUnknown_0300058C[0] & 0x20)
            {
                sub_08074DE0(2);
                if (gMainByte_03001788 == 0)
                    gMainByte_03001788 = 2;
                else
                    gMainByte_03001788--;
            }
            if (gUnknown_0300058C[0] & 0x10)
            {
                sub_08074DE0(2);
                if (gMainByte_03001788 == 2)
                    gMainByte_03001788 = 0;
                else
                    gMainByte_03001788++;
            }
            break;
        case 1:
            keys = *(u32 *)gUnknown_0300058C;
            if (((keys << 26) >> 31) | ((keys << 27) >> 31))
            {
                sub_08074DE0(2);
                gMainByte_03001360 ^= 1;
            }
            break;
        case 2:
            if (gUnknown_0300058C[0] & 0x20)
            {
                if (gMainByte_03000B94 == 0)
                    gMainByte_03000B94 = 2;
                else
                    gMainByte_03000B94--;
                sub_08074B88(gMain2SoundChoices_080AF8CA[gMainByte_03000B94]);
            }
            if (gUnknown_0300058C[0] & 0x10)
            {
                if (gMainByte_03000B94 == 2)
                    gMainByte_03000B94 = 0;
                else
                    gMainByte_03000B94++;
                sub_08074B88(gMain2SoundChoices_080AF8CA[gMainByte_03000B94]);
            }
            break;
        }
        if (gUnknown_0300058C[0] & 0x30)
            sub_0805BE0C(MAIN2_CONTEXT->byte05);
        keys = *(u32 *)gUnknown_0300058C;
        if (((keys << 31) >> 31) | ((keys << 30) >> 31))
        {
            sub_08074B88(1);
            sub_08074DE0(4);
            MAIN2_CONTEXT->byte05 = 2;
            gFrameObjects[14].flags &= 0xBFFF;
            gUnknown_0300137C--;
            sub_0805BD44(3);
            sub_0805BCB0(3, 0);
            sub_0805BE0C(3);
        }
        return;
    }
    sub_0805BD44(MAIN2_CONTEXT->byte05);
    sub_0805BE0C(MAIN2_CONTEXT->byte05);
    gFrameObjects[14].screenX = 32;
    gFrameObjects[14].screenY = MAIN2_CONTEXT->byte05 * 24 + 80;
}
