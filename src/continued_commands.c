#include "continued_commands.h"
extern u8 gUnknown_030057E0[];
extern void (*const gContinuedCommandCallbacks_083D222C[])(void);
void sub_0804B758(void);

u32 sub_0804B6E0(void)
{
    u32 result = sub_0805424C();
    if (result == 4)
        goto found;
    result = 0;
    goto complete;
found:
    result = 1;
complete:
    return result;
}

void sub_0804B6F4(void)
{
    u32 value = sub_0804D83C();
    u8 *work = gUnknown_030057E0;
    u8 *selector = work + 0xC92;
    u32 zero = 0;
    *selector = value;
    work[0xC89] = zero;
    work[0xC93] = zero;
    gContinuedCommandCallbacks_083D222C[*selector]();
}
u32 sub_0804B738(void) { return 0; }
void sub_0804B73C(void) { }
void sub_0804B740(void) { sub_0804B758(); }
void sub_0804B74C(void) { sub_0804B758(); }
void sub_0804B758(void)
{
    sub_0804D8CC(3);
    gUnknown_030057E0[0xC89] = 1;
}
void sub_0804B778(void) { gUnknown_030057E0[0xC89] = 1; }
void sub_0804B78C(void)
{
    u32 value = sub_0804D83C();
    u8 *work = gUnknown_030057E0;
    work[0xC94] = value;
    work[0xC89] = 1;
}
void sub_0804B7B4(void) { gUnknown_030057E0[0xC89] = 1; }
