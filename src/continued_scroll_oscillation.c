#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_commands.h"

extern u8 gUnknown_030057E0[];

void sub_0804F3F8(void)
{
    u8 *initial = gUnknown_030057E0;
    u8 phase = initial[0xC93];
    u8 *work = initial;
    u8 *counter;
    switch (phase)
    {
    case 0:
        if (work[0xC94] == 0)
            gBackgroundState_03005310.scrollX[0] = gBgScroll1.x;
        else
            gBackgroundState_03005310.scrollY[0] = gBgScroll1.y;
        work[0xC96] = 0;
        {
            u8 value = work[0xC95];
            work[0xC98] = value;
        }
        counter = work + 0xC93;
        goto increment;
    case 1:
        {
            u8 *remaining = initial + 0xC95;
            if (*remaining)
            {
                s32 duration, count, index;
                (*remaining)--;
                duration = initial[0xC98];
                count = initial[0xC96];
                index = count * (256 / duration) / 2;
                if (initial[0xC94] == 0)
                {
                    s32 value = gScrollOscillationSines_083D6A2C[index];
                    u32 part = count & 3;
                    s32 divisor = 128 - ((part + 1) << 4);
                    u16 adjustment = value / divisor;
                    u16 position;
                    if (part <= 1)
                        position = gBackgroundState_03005310.scrollX[0] - adjustment;
                    else
                        position = adjustment + gBackgroundState_03005310.scrollX[0];
                    sub_08052A10(position);
                }
                else
                {
                    s32 value = gScrollOscillationSines_083D6A2C[index];
                    u32 part = count & 3;
                    s32 divisor = 128 - ((part + 1) << 4);
                    u16 adjustment = value / divisor;
                    if (part <= 1)
                        sub_08052A30((u16)(gBackgroundState_03005310.scrollY[0] - adjustment));
                    else
                        sub_08052A30((u16)(adjustment + gBackgroundState_03005310.scrollY[0]));
                }
                sub_08052B70();
                {
                    u8 *nextWork = gUnknown_030057E0;
                    if (nextWork[0xC76])
                        sub_08053108();
                    counter = nextWork + 0xC96;
                }
increment:
                (*counter)++;
                break;
            }
            else
            {
                if (initial[0xC94] == 0)
                    sub_08052A10(gBackgroundState_03005310.scrollX[0]);
                else
                    sub_08052A30(gBackgroundState_03005310.scrollY[0]);
                sub_08052B70();
                if (gUnknown_030057E0[0xC76])
                    sub_08053108();
                sub_08050290();
                break;
            }
        }
    }
}
