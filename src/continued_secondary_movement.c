#include "global.h"
#include "frame.h"
#include "continued_commands.h"

extern u8 gUnknown_030057E0[];

struct MovementFrameBytes
{
    u8 unknown00[47 * 64 + 0x2A];
    u8 primary;
    u8 unknownBEB[63];
    u8 secondary;
};

void sub_0805203C(u32 modeWord)
{
    u8 mode = modeWord;
    u8 *work = gUnknown_030057E0;
    if (work[0xC76] && work[0xC74])
    {
        switch (mode)
        {
        case 0:
        {
            u16 *position = (u16 *)(work + 0xC70);
            u16 previous = *position;
            if (previous != *(u16 *)(work + 0xC4A))
            {
                *position -= sub_08051940(48);
                sub_08050168(48);
            }
            break;
        }
        case 1:
        {
            u16 *position = (u16 *)(work + 0xC70);
            if (*position - *(u16 *)(work + 0xC4A) + 16 < *(u16 *)(work + 0x802) * 8)
            {
                *position += sub_08051940(48);
                sub_08050168(48);
            }
            break;
        }
        case 2:
        {
            u16 *position = (u16 *)(work + 0xC6E);
            u16 previous = *position;
            if (previous != *(u16 *)(work + 0xC48))
            {
                *position -= sub_08051940(48);
                sub_08050168(48);
            }
            break;
        }
        case 3:
        {
            u16 *position = (u16 *)(work + 0xC6E);
            if (*position - *(u16 *)(work + 0xC48) + 16 < *(u16 *)(work + 0x800) * 8)
            {
                *position += sub_08051940(48);
                sub_08050168(48);
            }
            break;
        }
        }
        {
            u8 *next = gUnknown_030057E0;
            u8 *count = next + 0xC74;
            (*count)--;
            if (*count == 0)
            {
                struct MovementFrameBytes *objects = (struct MovementFrameBytes *)gFrameObjects;
                objects->secondary = objects->primary;
                next[0xC72] = sub_0805273C(*(u16 *)(next + 0xC6E));
                next[0xC73] = sub_08052760(*(u16 *)(next + 0xC70));
            }
        }
    }
}
