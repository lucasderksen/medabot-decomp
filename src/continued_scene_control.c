#include "continued_commands.h"
#include "frame.h"
#include "later_graphics.h"
#include "continued_graphics.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "input.h"
struct TransitionInputBytes { u8 low, high; };
#include "main.h"
#include "post_dispatch.h"

struct TransitionSettings { u8 unknown00[0x1C]; u16 x[4], y[4]; };
extern s32 __divsi3(s32 first, s32 second);
extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03006D38[];
extern u32 gMainSubstate;
extern u32 gUnknown_0300137C;

void sub_08050F5C(void)
{
    switch (gBackgroundState_03005310.unknown00[1])
    {
    case 0:
        sub_0805196C();
        {
            u8 *work = gUnknown_030057E0;
            if (sub_08052C68(work[0xC56], work[0xC57]))
            {
                u8 *objects;
                u8 *first;
                work[0xC58] = __divsi3(16, sub_08051940(47));
                objects = (u8 *)gFrameObjects;
                first = objects + 47 * 64 + 0x20;
                sub_08052E0C(*first);
                sub_08049420(47, *first);
                if (work[0xC76])
                {
                    u16 value = *(u16 *)(work + 0xC52);
                    *(u16 *)(work + 0xC6E) = value;
                    value = *(u16 *)(work + 0xC54);
                    *(u16 *)(work + 0xC70) = value;
                    sub_08052E34(*first);
                    sub_08049420(48, (u8)(objects[48 * 64 + 0x2B] * 4 + objects[48 * 64 + 0x20]));
                }
                sub_08051EFC(3);
                gBackgroundState_03005310.unknown00[1] = 1;
            }
            else
            {
                if (gLaterBuffer_03006D38[3] == 4)
                    sub_08047BA8(0);
                gBackgroundState_03005310.unknown00[1] = 2;
            }
        }
        break;
    case 1:
        {
            u32 address = (u32)gFrameObjects;
            u32 offset = 47 * 64 + 0x20;
            sub_08051988(*(u8 *)(address + offset));
        }
        if (!gUnknown_030057E0[0xC58])
        {
            if (gLaterBuffer_03006D38[3] == 4)
                sub_08047BA8(0);
            gBackgroundState_03005310.unknown00[1]++;
        }
        break;
    case 2:
        {
            u32 blocked = 0;
            u32 faded = 0;
            u32 handled = 0;
            u8 *work = gUnknown_030057E0;
            if (!work[0xC58] && !work[0xC88])
            {
                sub_080521A8();
                if (sub_08052400())
                    blocked = 1;
                else
                {
                    if (sub_08052C68(work[0xC56], work[0xC57]))
                    {
                        gBackgroundState_03005310.unknown00[1] = 3;
                        if (gLaterBuffer_03006D38[3])
                            sub_08047BA8(gSetupByteLookup_083D2B66[gLaterBuffer_03006D38[3]]);
                        sub_08049D90(0x7FFF, 0.0f, 32.0f, 8.0f);
                        faded = 1;
                    }
                    if (!blocked && !faded)
                    {
                        if (((struct TransitionInputBytes *)&gHeldKeys)->low & 1)
                        {
                            u8 *objects = (u8 *)gFrameObjects;
                            objects[47 * 64 + 0x2A] = 1;
                            objects[48 * 64 + 0x2A] = 1;
                        }
                        else
                        {
                            u8 *objects = (u8 *)gFrameObjects;
                            u32 value = gFrameByteLookup_083D2A88[gUnknown_030057E0[0xC5C]];
                            objects[47 * 64 + 0x2A] = value;
                            objects[48 * 64 + 0x2A] = value;
                        }
                        if (((struct TransitionInputBytes *)&gNewKeys)->low & 1)
                        {
                            if (sub_08052284())
                                handled = 1;
                            else if (sub_08052624() != (u32)-1)
                            {
                                gUnknown_0300137C = 8;
                                handled = 1;
                            }
                        }
                        else if (((struct TransitionInputBytes *)&gNewKeys)->low & 2)
                        {
                            if (gUnknown_030057E0[0xC33])
                            {
                                u8 *work = gUnknown_030057E0;
                                u8 *objects;
                                sub_08047E4C();
                                gMainState = 0;
                                gMainSubstate = 1;
                                gUnknown_0300137C = 0;
                                {
                                    struct TransitionSettings *saved = (void *)&gBackgroundState_03005310;
                                    saved->x[0] = gBgScroll0.x;
                                    saved->y[0] = gBgScroll0.y;
                                    saved->x[1] = gBgScroll1.x;
                                    saved->y[1] = gBgScroll1.y;
                                    saved->x[2] = gBgScroll2.x;
                                    saved->y[2] = gBgScroll2.y;
                                    saved->x[3] = gBgScroll3.x;
                                    saved->y[3] = gBgScroll3.y;
                                }
                                gBgScroll0.x = 0;
                                gBgScroll0.y = 0;
                                objects = (u8 *)gFrameObjects;
                                { u32 value = objects[47 * 64 + 0x20]; u32 offset = 0xC67; u8 *stored = work + offset; *stored = value; }
                                { u32 value = objects[48 * 64 + 0x20]; u32 offset = 0xC83; u8 *stored = work + offset; *stored = value; }
                                { u32 value = objects[48 * 64 + 0x2B]; u32 offset = 0xC84; u8 *stored = work + offset; *stored = value; }
                                sub_080505FC();
                                work[0xCBA] = 2;
                                handled = 1;
                            }
                        }
                        else if (((struct TransitionInputBytes *)&gNewKeys)->high & 1)
                        {
                            if (gUnknown_030057E0[0xC5C] == 1)
                                sub_08047BA8(116);
                        }
                    }
                }
            }
            if (!handled && !blocked && !faded)
            {
                if (((struct TransitionInputBytes *)&gNewKeys)->high & 1)
                    if (gUnknown_030057E0[0xC5C] == 1)
                        sub_08047BA8(116);
                sub_08051CB8();
            }
            else
            {
                u8 *objects = (u8 *)gFrameObjects;
                sub_08052E0C(objects[47 * 64 + 0x20]);
                sub_08052E34(objects[48 * 64 + 0x20]);
            }
        }
        break;
    case 3:
        if (sub_08049E08(0x7FFF))
            gBackgroundState_03005310.unknown00[1] = 4;
        break;
    case 4:
        sub_08052E88();
        gBackgroundState_03005310.unknown00[1] = 0;
        gMainState = 1;
        gMainSubstate = 1;
        gUnknown_0300137C = 1;
        gUnknown_030057E0[0xCBA] = 1;
        break;
    }
    sub_08052B70();
    sub_08053108();
    sub_08052784();
}
