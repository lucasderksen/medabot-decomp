#include "global.h"
#include "continued_commands.h"
#include "background_state.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03006D20[];

struct BackgroundCommandView
{
    struct BackgroundState known;
    u8 unknown38;
    u8 unknown39;
};

void sub_0804FB1C(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        sub_08047878(4, 0);
        (*state)++;
        break;
    case 1:
        if (gLaterBuffer_03006D20[12] == 7)
            *state = 2;
        else
            sub_08050290();
        break;
    case 2:
        sub_08050CC0();
        (*state)++;
        break;
    case 3:
        if (sub_08050CCC(5, 0))
            sub_08050290();
        break;
    }
}

void sub_0804FB8C(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    u32 stateValue = *state;
    switch (stateValue)
    {
    case 0:
        sub_08050CC0();
        (*state)++;
        break;
    case 1:
        if (sub_08050CCC(16, 0))
        {
            if (sub_0804B738())
                ((struct BackgroundCommandView *)&gBackgroundState_03005310)->unknown39 = stateValue;
            sub_08050290();
        }
        break;
    }
}

void sub_0804FBDC(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        sub_08050CC0();
        (*state)++;
        break;
    case 1:
        if (sub_08050CCC(18, 0))
        {
            sub_08050290();
        }
        break;
    }
}

void sub_0804FC1C(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    u32 stateValue = *state;
    switch (stateValue)
    {
    case 0:
        sub_08050CC0();
        (*state)++;
        break;
    case 1:
        if (sub_08050CCC(17, 0))
        {
            if (sub_0804B738())
                ((struct BackgroundCommandView *)&gBackgroundState_03005310)->unknown39 = stateValue;
            sub_08050290();
        }
        break;
    }
}

void sub_0804FC6C(void) { sub_0804E5F0(0, 0); }
