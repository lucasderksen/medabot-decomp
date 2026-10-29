#include "continued_commands.h"
#include "global.h"
#include "frame.h"
#include "palette_transfer_helpers.h"
#include "continued_blend_work.h"
#include "fresh_helpers.h"

extern u8 gUnknown_030057E0[];
extern const s16 gUnknownSines_083D6A2C[];
extern const u8 gActionPaletteSelector_083D2B18[];

struct ActionDmaRegisters { const void *source; u32 destination, control; };

void sub_0804DE74(void)
{
    u8 *objects = (u8 *)gFrameObjects;
    u8 *state = objects + 0xBE6;
    u32 stateValue = *state;
    switch (stateValue)
    {
    case 0:
        {
            u8 *counter = objects + 0xBE8;
            u32 count = *counter;
            if (count <= 15)
            {
                u32 address = (u32)gUnknown_030057E0;
                u8 *argument;
                u32 height;
                s32 value;
                s16 *position;
                address += 0xC94;
                argument = (u8 *)address;
                height = *argument;
                /* Models the second observed byte load, not an original qualifier claim. */
                value = gUnknownSines_083D6A2C[*(volatile u8 *)counter * 8] / 16;
                value = height - value;
                position = (s16 *)(objects + 0xBC4);
                *position = value;
                *counter = count + 1;
                if (*position / 4 <= ((s32)*argument - 16) / 4)
                    objects[0xBCB] = 255;
                else
                    sub_080487C8(47);
            }
            else
            {
                *state = 1;
                *counter = stateValue;
            }
            break;
        }
    case 1:
        sub_080487C8(47);
        { u32 height = gUnknown_030057E0[0xC94]; *(u16 *)(objects + 0xBC4) = height; }
        sub_08050290();
        break;
    }
}
