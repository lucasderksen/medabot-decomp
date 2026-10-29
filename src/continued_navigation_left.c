#include "continued_late_graphics.h"
#include "input.h"


/* Partial backing access view; the trailing mode extent remains unknown. */
struct OtherModeView {
    u8 unknown00[0x14];
    u8 selector;
    u8 unknown15;
    u8 modes[0];
};

struct HeldKeyBytes { u8 low; u8 high; };

void sub_08058A10(u32 index, s32 limit)
{
    u16 *value;
    u32 amount = 1;
    u8 keys;
    u8 left;
    if (((struct HeldKeyBytes *)&gHeldKeys)->high & 1)
        amount = 16;
    keys = *(u8 *)&gRepeatedKeys;
    left = keys & KEY_LEFT;
    if (left)
    {
        struct OtherModeView *work;
        value = gNavigationHalfwordPointers_083D625C[index];
        *value -= amount;
        if (*value == 0xFFFF)
            *value = limit - 1;
        work = (struct OtherModeView *)gContinuedOtherWork_030057A0;
        sub_080582B8(work->selector, (s8)work->modes[work->selector]);
    }
    else
    {
        u32 right = KEY_RIGHT;
        right &= keys;
        if (right)
        {
            struct OtherModeView *work;
            value = gNavigationHalfwordPointers_083D625C[index];
            *value += amount;
            if (*value >= limit)
                *value = 0;
            work = (struct OtherModeView *)gContinuedOtherWork_030057A0;
            sub_080582B8(work->selector, (s8)work->modes[work->selector]);
        }
    }
}
