#include "continued_commands.h"
#include "continued_callbacks.h"
#include "continued_graphics.h"
#include "background_state.h"
#include "fresh_helpers.h"
#include "equipment_helpers.h"
#include "post_dispatch.h"

extern u32 gUnknown_0300137C;
extern u8 gContinuedWork_030057E0[];
extern u8 gContinuedOtherWork_030057A0[];
extern const void *const gContinuedScripts_08411AE0[];
extern void sub_0804B248(void);
extern void sub_08058208(u32 value);
extern void sub_0805830C(u32 value);
extern u32 sub_080594C8(void);
extern void sub_08059578(void);

void sub_0804A6A0(void)
{
    sub_080480E4();
    sub_0804387C();
    sub_0804842C(0, 0);
    sub_0804A210();
}

void sub_0804A6BC(void) { sub_0804A210(); }

void sub_0804A6C8(void)
{
    if (sub_08049E08(32767))
        sub_0804A210();
}

void sub_0804A6E0(void) { sub_08050F5C(); }

void sub_0804A6EC(void) { sub_0804A210(); }

void sub_0804A6F8(void)
{
    sub_0804B248();
    sub_080506BC();
    sub_0804842C(5, 0);
    gBackgroundState_03005310.unknown00[1] = 0;
    gUnknown_0300137C = 5;
}

void sub_0804A724(void)
{
    sub_08047C00();
    sub_0804A210();
}

void sub_0804A734(void)
{
    u32 index = sub_08052624();
    const void *script = gContinuedScripts_08411AE0[index];
    if (sub_08047C24(0, 0, 0, script))
        gUnknown_0300137C = 5;
}

void sub_0804A900(void)
{
    if (sub_08049E08(32767))
    {
        gBackgroundState_03005310.unknown00[1] = 0;
        sub_080517F0();
        sub_08052B70();
        sub_08052E0C(gContinuedWork_030057E0[0xC67]);
        gUnknown_0300137C = 5;
    }
}

void sub_0804AA04(void)
{
    if (sub_08049E08(0))
    {
        gBackgroundState_03005310.unknown00[1] = 0;
        sub_080517F0();
        sub_08052B70();
        sub_08052E0C(gContinuedWork_030057E0[0xC67]);
        gUnknown_0300137C = 5;
    }
}

void sub_0804AB04(void)
{
    if (sub_08049E08(0))
        sub_0804A210();
}

void sub_0804AB18(void) { sub_0804A210(); }

void sub_0804AB24(void)
{
    gBackgroundState_03005310.unknown00[1] = 0;
    gUnknown_0300137C = 5;
}

void sub_0804AB3C(void) { sub_0804A210(); }

void sub_0804ABA8(void)
{
    gBackgroundState_03005310.unknown00[1] = 0;
    gUnknown_0300137C = 5;
}

void sub_0804ABC0(void) { sub_0804A210(); }

void sub_0804ACC8(void) { sub_0804A210(); }

void sub_0804AF98(void)
{
    if (gContinuedOtherWork_030057A0[17] == 0)
    {
        gContinuedOtherWork_030057A0[16] = 1;
        sub_08058208(0);
    }
    sub_0804A210();
}

void sub_0804AFB8(void)
{
    sub_0805830C(gContinuedOtherWork_030057A0[20]);
}

void sub_0804AFCC(void)
{
    if (sub_080594C8())
        sub_08059578();
}

void sub_0804AFE0(void)
{
    sub_08049D90(32767, 0.0f, 32.0f, 8.0f);
    sub_0804A210();
}
