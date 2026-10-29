#include "global.h"
#include "frame.h"
#include "continued_commands.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03005350[];
extern u8 gLaterBuffer_03006D20[];

struct CommandWordView
{
    u8 unknown00[0x1D4];
    u32 command;
};

struct FrameMapByteView
{
    u8 unknown00[0xBEA];
    u8 unknownBEA;
};

void sub_0804F6E0(void)
{
    u8 *initial = gUnknown_030057E0;
    u8 *state = initial + 0xC93;
    u8 phase = *state;
    u8 *work = initial;
    switch (phase)
    {
    case 0:
        {
            struct CommandWordView *context =
                (struct CommandWordView *)gLaterBuffer_03005350;
            u32 command = context->command & 63;
            if (command == 13 || command == 22)
            {
                if (!sub_08050BC8())
                    break;
                goto increment;
            }
            else
            {
                if (sub_08050BC8())
                    sub_08050290();
            }
            break;
        }
    case 1:
        {
            s32 divisor = sub_08051940(47);
            gLaterBuffer_03006D20[0] = 16 / divisor;
            sub_08050124(47, (u8)((work[0xC94] << 4) | work[0xC95]), 0);
        }
increment:
        (*state)++;
        break;
    case 2:
        {
            struct CommandWordView *context =
                (struct CommandWordView *)gLaterBuffer_03005350;
            const u8 *selected;
            if ((context->command & 63) == 13)
                work[0xC67] = phase;
            else
                work[0xC67] = 3;
            selected = work + 0xC67;
            if (sub_0804F188(*selected))
            {
                u8 *flag = work + 0xC5B;
                struct FrameMapByteView *objects;
                const u8 *lookup;
                u8 value;
                *flag = 1;
                objects = (struct FrameMapByteView *)gFrameObjects;
                lookup = gFrameByteLookup_083D2A88;
                value = lookup[work[0xC5C]];
                objects->unknownBEA = value;
                work[0xC56] = sub_0805273C(*(u16 *)(work + 0xC52));
                work[0xC57] = sub_08052760(*(u16 *)(work + 0xC54));
                sub_08052AA4();
                sub_08052BEC(*flag);
                sub_08052E0C(*selected);
                sub_08052B70();
                sub_08050C94();
                sub_08050290();
            }
            break;
        }
    }
}
