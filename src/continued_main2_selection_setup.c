#include "frame.h"
#include "global.h"
#include "gba.h"
#include "main.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "object_helpers.h"
#include "frame_objects.h"
#include "display_effects.h"
#include "equipment_helpers.h"
#include "main_callbacks.h"

#define CONTEXT ((u8 *)gMainContextPointer_03006F74)
#define DISPLAY_CONTROL (*(volatile u16 *)0x04000000)

void sub_0805CDAC(void)
{
    u32 zero;
    u8 *context;
    u8 *palette;
    {
        u8 *initial = CONTEXT;
        zero = 0;
        initial[6] = zero;
    }
    CONTEXT[0xC] = zero;
    CONTEXT[0x11] = zero;
    sub_0805AE4C();
    sub_0805AED0();
    if (CONTEXT[0x10])
    {
        gFrameObjects[83].flags |= 0x4000;
        sub_0805B0B0(&gFrameObjects[83]);
    }
    context = CONTEXT;
    if ((context[0x10] - 1) / 5)
    {
        gFrameObjects[81].flags |= 0x4000;
        gFrameObjects[82].flags |= 0x4000;
    }
    context[0x12] = zero;
    CpuFastSet((const void *)0x0850F298, (void *)0x0202F800, 128);
    CpuFastSet(gUnknownWords_084E43F8, (void *)0x0202F800, 8);
    CpuFastSet((const void *)0x080AF938, (void *)0x0202F9C0, 8);
    CpuFastSet((const void *)0x0878C088, gEquipmentPaletteShadow, 128);
    {
        u32 fill = zero;
        CpuFastSet(&fill, (void *)0x050001A0, 0x01000008);
    }
    gUnknown_03000440[0x84] = zero;
    DISPLAY_CONTROL |= 0x200;
    DISPLAY_CONTROL |= 0x400;
    DISPLAY_CONTROL |= 0x800;
    DISPLAY_CONTROL |= 0x1000;
    gUnknown_0300137C++;
}
