#include "global.h"
#include "continued_commands.h"
#include "fresh_helpers.h"
#include "object_helpers.h"
#include "background_state.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03006D20[];

void sub_0804E700(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        sub_08050358(work[0xC94], work[0xC95], work[0xC96], work[0xC97]);
        sub_080500BC(gLaterBuffer_03006D20[10], work[0xC98], 0);
        (*state)++;
        break;
    case 1:
        if (sub_0805018C(gLaterBuffer_03006D20[10], 0))
            sub_08050290();
        break;
    }
}

void sub_0804E784(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        sub_080500BC(gLaterBuffer_03006D20[10], work[0xC95], 0);
        (*state)++;
        break;
    case 1:
        if (sub_0805018C(gLaterBuffer_03006D20[10], 0))
            sub_08050290();
        break;
    }
}

void sub_0804E7DC(void) { }
void sub_0804E7E0(void) { }
void sub_0804E7E4(void) { }

void sub_0804E7E8(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        sub_08048000(0);
        goto increment;
    case 1:
        {
            u32 result = sub_08048038();
            if (!result)
                break;
            if (result & 0xF0)
            {
                const u16 *previous = (u16 *)(work + 0xC8C);
                const u8 *argument = work + 0xC94;
                u16 value = *previous + *argument;
                *(u16 *)(work + 0xC8A) = value;
            }
        }
increment:
        (*state)++;
        break;
    case 2:
        if (sub_08041CA4())
            sub_08050290();
        break;
    }
}

void sub_0804E860(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        sub_08048000(1);
        (*state)++;
        break;
    case 1:
        {
            u32 result = sub_08048038();
            if (!result)
                break;
            if (result & 0xF0)
            {
                const u16 *previous = (u16 *)(work + 0xC8C);
                const u8 *argument = work + 0xC94;
                u16 value = *previous + *argument;
                *(u16 *)(work + 0xC8A) = value;
            }
            sub_08050290();
            break;
        }
    }
}

struct BackgroundCommandView
{
    struct BackgroundState base;
    u8 unknown38;
    u8 unknown39;
};

void sub_0804E8C4(void)
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
        if (sub_08050CCC(32, 0))
        {
            u32 value = work[0xC4F];
            if (value == 1)
            {
                struct BackgroundCommandView *background =
                    (struct BackgroundCommandView *)&gBackgroundState_03005310;
                background->unknown39 = value;
            }
            else if (value == 2)
            {
                struct BackgroundCommandView *background =
                    (struct BackgroundCommandView *)&gBackgroundState_03005310;
                background->unknown39 = value;
            }
            sub_08050290();
        }
        break;
    }
}
