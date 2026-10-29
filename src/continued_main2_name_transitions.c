#include "gba.h"
#include "main.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "state0_inventory.h"
#include "display_effects.h"
#include "continued_commands.h"
#include "bg_scroll.h"


/* Only the physically accessed fields are modeled. */
struct NameTransitionContext
{
    u8 unknown00[2];
    u16 halfword02;
    u8 unknown04[2];
    u8 byte06;
    u8 unknown07[0x51];
    u8 bytes58[16];
};
struct NameTransitionPhase { u8 unknown00[0x84]; u8 byte84; };
#define NAME_CONTEXT ((struct NameTransitionContext *)gMainContextPointer_03006F74)
#define NAME_PHASE ((struct NameTransitionPhase *)gUnknown_03000440)
#define DISPLAY_CONTROL (*(volatile u16 *)0x04000000)

void sub_0805E9E0(void)
{
    if (NAME_PHASE->byte84 <= 8)
    {
        sub_0803F684(0, 32 - NAME_PHASE->byte84 * 4, 0xFFFF);
        sub_0803F998(0, 32 - NAME_PHASE->byte84 * 4, 0xFFFF);
        NAME_PHASE->byte84++;
    }
    else
    {
        struct NameTransitionContext *context = NAME_CONTEXT;
        context->halfword02 = 0;
        context->byte06 = 0;
        gUnknown_0300137C++;
    }
}

void sub_0805EFD4(void)
{
    if (sub_08074FA4(7) == 0)
    {
        NAME_PHASE->byte84 = 0;
        gUnknown_0300137C++;
    }
}

void sub_0805EFFC(void)
{
    if (NAME_PHASE->byte84 <= 8)
    {
        sub_0803F684(0, NAME_PHASE->byte84 * 4, 0xFFFF);
        sub_0803F998(0, NAME_PHASE->byte84 * 4, 0xFFFF);
        NAME_PHASE->byte84++;
    }
    else
    {
        DISPLAY_CONTROL &= 0xFDFF;
        {
            u32 fill = 0;
            CpuFastSet(&fill, (void *)0x06000000, 0x01006000);
        }
        switch (*(u8 *)0x03000584)
        {
        case 0:
            CpuSet(NAME_CONTEXT->bytes58, gUnknown_03002B74, 8);
            sub_080476E8(0);
            break;
        case 1:
            CpuSet(NAME_CONTEXT->bytes58, gInventoryNames[gQuantityResult_030017EC], 7);
            sub_080476E8(1);
            break;
        case 2:
            CpuSet(NAME_CONTEXT->bytes58, gInventoryNames[gQuantityResult_030017EC], 7);
            gMainSubstate = 18;
            gUnknown_0300137C = 10;
            break;
        }
    }
}

void sub_0805F104(void)
{
    gMain2NameCallbacks_08483700[gUnknown_0300137C]();
    if (gFrameCounter & 1)
    {
        gBgScroll3.x++;
        gBgScroll3.y++;
    }
}
