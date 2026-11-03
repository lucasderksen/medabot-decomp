#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_callbacks.h"
#include "frame.h"
#include "display_helpers.h"

extern void (*const gState0RowObjectCallbacks_083ACE14[])(void);

u32 sub_0801013C(void)
{
    void (*const *callbacks)(void) = gState0RowObjectCallbacks_083ACE14;
    u8 *objects = (u8 *)gFrameObjects;
    u8 *state = objects + 0x129;
    callbacks[*state]();
    if (*state == 3)
        return 1;
    return 0;
}

void sub_0801022C(void)
{
    FillTilemapRect(12, 8, 18, 5, *(volatile u16 *)0x04000008, 0);
    gFrameObjects[4].unknown23[6]++;
}

void sub_080102C0(void)
{
    *(volatile u16 *)0x04000008 |= 64;
    *(volatile u16 *)0x0400000A |= 64;
    *(volatile u16 *)0x0400000C |= 64;
    *(volatile u16 *)0x0400000E |= 64;
    PlayMusic(8);
    gState0TypedWork.bytes[0x85] = 0;
    gNestedCallbackIndex++;
}

void sub_0801030C(void)
{
    gState0TypedWork.bytes[0x84] = 0;
    gNestedCallbackIndex++;
}
