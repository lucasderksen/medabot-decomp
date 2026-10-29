#include "frame.h"
#include "global.h"
#include "gba.h"
#include "main.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "object_helpers.h"
#include "frame_objects.h"
#include "continued_late_graphics.h"
#include "selector_helpers.h"
#include "graphics.h"
#include "input.h"
#include "main_callbacks.h"

#define CONTEXT ((u8 *)gMainContextPointer_03006F74)

/* Only this observed byte offset is modeled; backing extent is unknown. */
struct Main2CommandWork
{
    u8 unknown00[0xC5C];
    u8 byteC5C;
};
#define COMMAND_WORK ((struct Main2CommandWork *)gUnknown_030057E0)

void sub_0805CFB4(void)
{
    u32 pageSize = 5;
    u8 *context;
    u8 *selectionContext;
    u8 *confirmContext;
    sub_08041C14(83, *(u8 *)&gFrameCounter, 84);
    if ((CONTEXT[0x10] - 1) / 5)
    {
        if ((gFrameCounter >> 4) & 1)
        {
            gFrameObjects[81].flags |= 0x4000;
            gFrameObjects[82].flags |= 0x4000;
        }
        else
        {
            gFrameObjects[81].flags &= 0xBFFF;
            gFrameObjects[82].flags &= 0xBFFF;
        }
    }
    context = CONTEXT;
    if (context[0x10] > 1)
    {
        u8 keys = *(u8 *)&gRepeatedKeys;
        if (keys & 0x40)
        {
            if (context[0xC] == context[0x11])
            {
                u8 first = context[0x11];
                u32 firstPage = (u32)first / pageSize;
                u8 count = context[0x10];
                if ((u8)firstPage == (u8)((u32)count / pageSize))
                    context[0xC] = first + (u32)count % pageSize - 1;
                else
                {
                    u32 next = pageSize;
                    next += first;
                    context[0xC] = next - 1;
                }
            }
            else
                context[0xC]--;
            goto changed;
        }
        else if (keys & 0x80)
        {
            u8 first = context[0x11];
            u32 firstPage = (u32)first / pageSize;
            u8 count = context[0x10];
            if ((u8)firstPage == (u8)((u32)count / pageSize))
            {
                if (context[0xC] == first + (u8)((u32)count % pageSize) - 1)
                    context[0xC] = first;
                else
                    context[0xC]++;
            }
            else
            {
                if (context[0xC] == first + pageSize - 1)
                    context[0xC] = first;
                else
                    context[0xC]++;
            }
            goto changed;
        }
        else if (context[0x10] >= (s32)pageSize + 1)
        {
            u32 direction = 0x10;
            direction &= keys;
            if (direction)
            {
                if ((s32)(context[0x11] + pageSize) < context[0x10])
                    context[0x11] += pageSize;
                else
                    context[0x11] = 0;
            }
            else
            {
                direction = 0x20;
                direction &= keys;
                keys = direction;
                if (keys)
                {
                    if (context[0x11] >= pageSize)
                        context[0x11] -= pageSize;
                    else if ((u8)((u32)context[0x10] % pageSize) == 0)
                        context[0x11] = context[0x10] - pageSize;
                    else
                        context[0x11] = ((u32)context[0x10] / pageSize) * pageSize;
                }
                else
                    goto selection;
            }
            CONTEXT[0xC] = CONTEXT[0x11];
            sub_0805AED0();
            sub_0805B5BC(&gFrameObjects[84]);
            goto changed;
        }
    }
selection:
    selectionContext = CONTEXT;
    if (selectionContext[0x12])
    {
        sub_0805CB90(gFrameCounter);
        if (gUnknown_0300058C[0] & 2)
        {
            gFrameObjects[84].flags &= 0xBFFF;
            CONTEXT[0x12] = 0;
            goto changed;
        }
        else if (gUnknown_0300058C[0] & 5)
        {
            gFrameObjects[84].flags &= 0xBFFF;
            CONTEXT[0x12] = 0;
            sub_0805B594();
            sub_0805AE4C();
            sub_0805AED0();
            goto changed;
        }
        else
            return;
    }
    else
    {
        if (selectionContext[0x10] > 1 && (gUnknown_0300058C[0] & 4))
        {
            *(u16 *)(selectionContext + 2) = 0;
            sub_08074DE0(2);
            sub_0805D4A0();
        }
    }
    confirmContext = CONTEXT;
    if (confirmContext[0x12])
        return;
    if (gUnknown_0300058C[0] & 1)
    {
        if (confirmContext[0x10])
        {
            s32 kind;
            u8 *destination = gLaterBuffer_03006D38;
            u32 source = 0x02040000;
            u32 offset = confirmContext[0xC];
            offset *= 4;
            destination[4] = *(const u16 *)(offset + source);
            offset = confirmContext[0xC];
            offset *= 4;
            kind = sub_08048960(*(const u16 *)(offset + source));
            switch (kind)
            {
            case 1:
                sub_08074DE0(4);
                switch (*(const u16 *)(0x02040000 + CONTEXT[0xC] * 4))
                {
                case 0:
                    CONTEXT[0] = 0;
                    gUnknown_0300137C = 11;
                    return;
                case 1:
                    COMMAND_WORK->byteC5C = 3;
                    break;
                case 5:
                    COMMAND_WORK->byteC5C = 4;
                    break;
                case 12:
                    COMMAND_WORK->byteC5C = 5;
                    break;
                case 13:
                    COMMAND_WORK->byteC5C = 8;
                    break;
                case 19:
                    COMMAND_WORK->byteC5C = 6;
                    break;
                case 39:
                    COMMAND_WORK->byteC5C = 7;
                    break;
                case 40:
                    COMMAND_WORK->byteC5C = 13;
                    break;
                default:
                    sub_080476E8(4);
                    return;
                }
                gUnknown_03000440[0x84] = 0;
                gUnknown_0300137C = 13;
                return;
            case 2:
            case 3:
            case 4:
                sub_0803FB0C();
                sub_08074DE0(6);
                gFrameObjects[81].flags &= 0xBFFF;
                gFrameObjects[82].flags &= 0xBFFF;
                gUnknown_0300137C = 9;
                return;
            case 0:
                sub_08074DE0(6);
                return;
            }
        }
        else
            goto leave;
    }
    if (gUnknown_0300058C[0] & 2)
    {
leave:
        sub_08074DE0(5);
        SnapshotPalettes();
        gUnknown_03000440[0x84] = 0;
        gUnknown_0300137C = 7;
    }
    return;
changed:
    sub_08074DE0(2);
    sub_0803FB0C();
    sub_0805B0B0(&gFrameObjects[83]);
    gUnknown_0300137C = 4;
    sub_0805CB90(gFrameCounter);
}
