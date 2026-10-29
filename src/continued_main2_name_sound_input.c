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


/* Only physically accessed offsets and widths are modeled. */
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
#define BG1CNT (*(volatile u16 *)0x0400000A)
#define REPEATED_BYTE (*(u8 *)&gRepeatedKeys)
#define NEW_BYTE (*(u8 *)&gNewKeys)

void sub_0805F488(void)
{
    sub_08041C14(0, *(u8 *)&gFrameCounter, 20);
    if (CONTEXT->byte48)
    {
        u32 delay = CONTEXT->byte48;
        delay--;
        CONTEXT->byte48 = delay;
        if ((u8)delay == 0)
            sub_08074DE0(2);
    }
    if (REPEATED_BYTE & KEY_UP)
    {
        if (CONTEXT->byte05)
            CONTEXT->byte05--;
        else
            CONTEXT->byte05 = 3;
        sub_08074B88(0);
        CONTEXT->byte48 = 2;
    }
    if (REPEATED_BYTE & KEY_DOWN)
    {
        if (CONTEXT->byte05 <= 2)
            CONTEXT->byte05++;
        else
            CONTEXT->byte05 = 0;
        sub_08074B88(0);
        CONTEXT->byte48 = 2;
    }
    gFrameObjects[0].screenY = CONTEXT->byte05 * 16 + 32;
    switch (CONTEXT->byte05)
    {
    case 0:
        if (gFrameCounter & 8)
        {
            gFrameObjects[1].flags |= 0x4000;
            gFrameObjects[2].flags |= 0x4000;
        }
        else
        {
            gFrameObjects[1].flags &= 0xBFFF;
            gFrameObjects[2].flags &= 0xBFFF;
        }
        gFrameObjects[3].flags &= 0xBFFF;
        gFrameObjects[4].flags &= 0xBFFF;
        break;
    case 1:
        gFrameObjects[1].flags &= 0xBFFF;
        gFrameObjects[2].flags &= 0xBFFF;
        if (gFrameCounter & 8)
        {
            gFrameObjects[3].flags |= 0x4000;
            gFrameObjects[4].flags |= 0x4000;
        }
        else
        {
            gFrameObjects[3].flags &= 0xBFFF;
            gFrameObjects[4].flags &= 0xBFFF;
        }
        break;
    default:
        gFrameObjects[1].flags &= 0xBFFF;
        gFrameObjects[2].flags &= 0xBFFF;
        gFrameObjects[3].flags &= 0xBFFF;
        gFrameObjects[4].flags &= 0xBFFF;
        break;
    }
    switch (CONTEXT->byte05)
    {
    case 0:
        if (REPEATED_BYTE & KEY_LEFT)
        {
            if (CONTEXT->byte2B)
                CONTEXT->byte2B--;
            else
                CONTEXT->byte2B = 51;
            sub_08059F58(CONTEXT->byte2B, -2, 16, 4, 2, (BG1CNT >> 8) & 31);
        }
        if (REPEATED_BYTE & KEY_RIGHT)
        {
            if (CONTEXT->byte2B <= 50)
                CONTEXT->byte2B++;
            else
                CONTEXT->byte2B = 0;
            sub_08059F58(CONTEXT->byte2B, -2, 16, 4, 2, (BG1CNT >> 8) & 31);
        }
        break;
    case 1:
        if (REPEATED_BYTE & KEY_LEFT)
        {
            if (CONTEXT->half2C)
                CONTEXT->half2C--;
            else
                CONTEXT->half2C = 117;
            sub_08059F58(CONTEXT->half2C, -3, 15, 6, 2, (BG1CNT >> 8) & 31);
        }
        if (REPEATED_BYTE & KEY_RIGHT)
        {
            if (CONTEXT->half2C <= 116)
                CONTEXT->half2C++;
            else
                CONTEXT->half2C = 0;
            sub_08059F58(CONTEXT->half2C, -3, 15, 6, 2, (BG1CNT >> 8) & 31);
        }
        break;
    }
    if (CONTEXT->byte4B)
        CONTEXT->byte4B--;
    if (CONTEXT->byte4A && CONTEXT->byte4B == 0)
    {
        sub_08074DE0(CONTEXT->byte4A);
        CONTEXT->byte4A = 0;
    }
    if (NEW_BYTE & KEY_A)
    {
        switch (CONTEXT->byte05)
        {
        case 0:
            {
                u32 base = (u32)gMain2SoundTable_080AF9CC;
                u32 offset = CONTEXT->byte2B;
                sub_08074B88(*(const u8 *)(base + offset));
            }
            break;
        case 1:
            CONTEXT->byte4B = 2;
            {
                struct Main2SoundContext *context = CONTEXT;
                u32 base = (u32)gMain2SoundTable_080AFA00;
                u32 offset = context->half2C;
                context->byte4A = *(const u8 *)(base + offset);
            }
            sub_08074B88(0);
            sub_08074DE0(0);
            break;
        case 2:
            sub_08074DE0(4);
            sub_080415E8(1, 22, 7);
            sub_0803FAA0(1, 2, 0);
            gUnknown_0300137C = 6;
            break;
        case 3:
            CONTEXT->byte49 = 0;
            goto leave;
        }
    }
    else if (NEW_BYTE & KEY_B)
    {
        CONTEXT->byte49 = 1;
leave:
        sub_08074B88(0);
        CONTEXT->byte00 = 0;
        gUnknown_0300137C = 5;
        gFrameObjects[0].flags &= 0xBFFF;
        gFrameObjects[1].flags &= 0xBFFF;
        gFrameObjects[2].flags &= 0xBFFF;
        gFrameObjects[3].flags &= 0xBFFF;
        gFrameObjects[4].flags &= 0xBFFF;
    }
}
